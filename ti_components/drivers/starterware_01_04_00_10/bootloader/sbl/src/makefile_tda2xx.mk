# Makefile for device starterware hal mailbox app

ifeq ($(OPPMODE),)
APP_NAME = sbl_$(BOOTMODE)
else ifeq ($(OPPMODE),opp_nom)
APP_NAME = sbl_$(BOOTMODE)
else
APP_NAME = sbl_$(BOOTMODE)_$(OPPMODE)
endif

SRCDIR = .
INCDIR = . $(starterware_PATH)/bootloader/sbl/include

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = uartConsole utils_platform sys_config starterware_hal starterware_pm_hal starterware_pm_lib

# List all the components required by the application
COMP_LIST_COMMON = uartConsole utils_platform

CFLAGS_LOCAL_COMMON += $(STARTERWARE_CFLAGS)

ifeq ($(BOOTMODE),qspi)
	COMP_LIST_COMMON += qspi_flashlib
	INCLUDE_EXTERNAL_INTERFACES += qspi_flashlib
else ifeq ($(BOOTMODE),nor)
	COMP_LIST_COMMON +=
else ifeq ($(BOOTMODE),sd)
	COMP_LIST_COMMON += fat_lib fat_lib_edma starterware_osal
	INCLUDE_EXTERNAL_INTERFACES += fat_lib fat_lib_edma
else ifeq ($(BOOTMODE), regression)
	COMP_LIST_COMMON += fat_lib fat_lib_edma starterware_osal
	INCLUDE_EXTERNAL_INTERFACES += fat_lib fat_lib_edma
endif

COMP_LIST_COMMON += starterware_hal sys_config starterware_pm_hal starterware_pm_lib

#-----------------------------------------------------------------------------#
# Common compile flags                                                        #
#-----------------------------------------------------------------------------#

# Common source files and CFLAGS across all platforms and cores

SRCS_COMMON +=
SRCS_a15host += sbl_tda2xx_main.c sbl_tda2xx_rprc_parse.c sbl_tda2xx_image_copy.c sbl_tda2xx_slavecore_boot.c sbl_tda2xx_soc_init.c sbl_tda2xx_sr0.c \
				sbl_tda2xx_wakeup_ddr3.c sbl_tda2xx_wd_timer.c sbl_tda2xx_prcm_dpll.c
SRCS_a8host +=
ASMS_a8host +=

ifeq ($(BOOTMODE),nor)
SRCS_ASM_a15host += sbl_tda2xx_nor_init.asm
endif

SRCS_ASM_a15host += sbl_tda2xx_init.asm

# Common source files and CFLAGS across all platforms and cores
ifeq ($(BOOTMODE),qspi)
	CFLAGS_LOCAL_COMMON += -DQSPI
else ifeq ($(BOOTMODE),sd)
	CFLAGS_LOCAL_COMMON += -DMMCSD
else ifeq ($(BOOTMODE),nor)
	CFLAGS_LOCAL_COMMON += -DNOR
	ASMFLAGS_LOCAL_COMMON = -Wa,--defsym,NOR=1
else ifeq ($(BOOTMODE),ddr3)
	CFLAGS_LOCAL_COMMON += -DZEBU_DDR3
else ifeq ($(BOOTMODE),regression)
	CFLAGS_LOCAL_COMMON += -DSBL_REGRESSION
endif

# Flag to set EMIF MODE( DUAL_EMIF_2X512MB = 0, DUAL_EMIF_1GB_512MB = 1, SINGLE_EMIF_256MB = 2)
ifeq ($(EMIFMODE),)
	CFLAGS_LOCAL_COMMON += -DEMIF_MODE=0
else ifeq ($(EMIFMODE), DUAL_EMIF_2X512MB)
	CFLAGS_LOCAL_COMMON += -DEMIF_MODE=0
else ifeq ($(EMIFMODE),DUAL_EMIF_1GB_512MB)
	CFLAGS_LOCAL_COMMON += -DEMIF_MODE=1
else ifeq ($(EMIFMODE),SINGLE_EMIF_256MB)
	CFLAGS_LOCAL_COMMON += -DEMIF_MODE=2
endif

#Flags for forcing opp mode irrespective of fd/sample revision
ifeq ($(FORCE_OPPMODE),TRUE)
       CFLAGS_LOCAL_COMMON += -DFORCE_OPP_MODE=1
else
       CFLAGS_LOCAL_COMMON += -DFORCE_OPP_MODE=0
endif

ifeq ($(SOCFAMILY),tda2xx)
	CFLAGS_LOCAL_COMMON += -DDEBUG_TRACE_LEVEL=1
endif

ifeq ($(PLATFORM),tda2xx-mc)
    CFLAGS_LOCAL_COMMON += -DTDA2XX_MC_BUILD
endif

#Flags for SBL opp_nom, opp_od and opp_high
ifeq ($(OPPMODE),)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=1
else ifeq ($(OPPMODE),opp_low)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=0
else ifeq ($(OPPMODE),opp_nom)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=1
else ifeq ($(OPPMODE),opp_od)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=2
else ifeq ($(OPPMODE),opp_high)
       CFLAGS_LOCAL_COMMON += -DOPP_MODE=3
endif

# a15host
ifeq ($(SOCFAMILY),tda2xx)
ifeq ($(BOOTMODE),sd)
	LNKCMD_FILE = ../lnk_tda2xx_a15.cmd
	LNKFLAGS_LOCAL_a15host += --entry SBL_Start
else ifeq ($(BOOTMODE),nor)
	LNKCMD_FILE = ../lnk_tda2xx_a15_nor.cmd
	LNKFLAGS_LOCAL_a15host += --entry nor_lowlevel_init
else ifeq ($(BOOTMODE),qspi)
	LNKCMD_FILE = ../lnk_tda2xx_a15.cmd
	LNKFLAGS_LOCAL_a15host += --entry SBL_Start
else ifeq ($(BOOTMODE),ddr3)
	LNKCMD_FILE = ../lnk_tda2xx_a15.cmd
	LNKFLAGS_LOCAL_a15host += --entry SBL_Start
else ifeq ($(BOOTMODE),regression)
	LNKCMD_FILE = ../lnk_tda2xx_a15.cmd
	LNKFLAGS_LOCAL_a15host += --entry SBL_Start
endif
endif



# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
