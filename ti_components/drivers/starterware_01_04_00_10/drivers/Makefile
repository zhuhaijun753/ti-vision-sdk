MODULE_NAME = starterware_hal

SRCDIR = .
INCDIR = .

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES =

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = starterware_hal starterware_common

# Common source files and CFLAGS across all platforms and cores

#Include src files for only the modules defined under starterware_hal_COMP_LIST
ifeq ($(findstring mailbox,$(starterware_hal_COMP_LIST)),mailbox)
SRCS_COMMON += mailbox.c
endif
ifeq ($(findstring hsi2c,$(starterware_hal_COMP_LIST)),hsi2c)
SRCS_COMMON += hsi2c.c
endif
ifeq ($(findstring uart,$(starterware_hal_COMP_LIST)),uart)
SRCS_COMMON += uart.c
endif
ifeq ($(findstring gpio,$(starterware_hal_COMP_LIST)),gpio)
SRCS_COMMON += gpio_v2.c
endif
ifeq ($(findstring spinlock,$(starterware_hal_COMP_LIST)),spinlock)
SRCS_COMMON += spinlock.c
endif
ifeq ($(findstring mcspi,$(starterware_hal_COMP_LIST)),mcspi)
SRCS_COMMON += mcspi.c
endif
ifeq ($(findstring ocmc,$(starterware_hal_COMP_LIST)),ocmc)
SRCS_tda2xx += ocmc_ecc_l1.c ocmc_ecc_l2.c
SRCS_tda3xx += ocmc_ecc_l1.c ocmc_ecc_l2.c
endif
ifeq ($(findstring gpmc,$(starterware_hal_COMP_LIST)),gpmc)
SRCS_COMMON += gpmc.c
endif
ifeq ($(findstring qspi,$(starterware_hal_COMP_LIST)),qspi)
SRCS_tda2xx += qspi.c
SRCS_tda3xx += qspi.c
endif
ifeq ($(findstring edma,$(starterware_hal_COMP_LIST)),edma)
SRCS_COMMON += edma.c
endif
ifeq ($(findstring mmu,$(starterware_hal_COMP_LIST)),mmu)
SRCS_COMMON += mmu.c
endif
ifeq ($(findstring mcasp,$(starterware_hal_COMP_LIST)),mcasp)
SRCS_COMMON += mcasp.c
endif
ifeq ($(findstring mmcsd,$(starterware_hal_COMP_LIST)),mmcsd)
SRCS_COMMON += hs_mmcsd.c
endif
ifeq ($(findstring timer,$(starterware_hal_COMP_LIST)),timer)
SRCS_COMMON += timer.c
endif
ifeq ($(findstring wdtimer,$(starterware_hal_COMP_LIST)),wdtimer)
SRCS_COMMON += wd_timer.c
endif
ifeq ($(findstring pcie,$(starterware_hal_COMP_LIST)),pcie)
SRCS_tda2xx += pcie.c
endif
ifeq ($(findstring rti,$(starterware_hal_COMP_LIST)),rti)
SRCS_tda3xx += rti.c
endif
ifeq ($(findstring crc,$(starterware_hal_COMP_LIST)),crc)
SRCS_tda3xx += crc.c
endif
ifeq ($(findstring dcan,$(starterware_hal_COMP_LIST)),dcan)
SRCS_tda2xx += dcan.c
SRCS_tda3xx += dcan.c
endif
ifeq ($(findstring tesoc,$(starterware_hal_COMP_LIST)),tesoc)
SRCS_tda3xx += tesoc.c
endif
ifeq ($(findstring dcc,$(starterware_hal_COMP_LIST)),dcc)
SRCS_tda3xx += dcc.c
endif
ifeq ($(findstring esm,$(starterware_hal_COMP_LIST)),esm)
SRCS_tda3xx += esm.c
endif
ifeq ($(findstring adc,$(starterware_hal_COMP_LIST)),adc)
SRCS_tda3xx += adc.c
endif
ifeq ($(findstring l3fw,$(starterware_hal_COMP_LIST)),l3fw)
SRCS_tda2xx += l3fw.c
SRCS_tda3xx += l3fw.c
endif
ifeq ($(findstring emif,$(starterware_hal_COMP_LIST)),emif)
SRCS_tda2xx += emif.c
SRCS_tda3xx += emif.c
endif

PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(STARTERWARE_CFLAGS)

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
