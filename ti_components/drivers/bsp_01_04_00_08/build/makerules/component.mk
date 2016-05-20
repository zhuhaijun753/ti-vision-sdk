#*******************************************************************************
#                                                                              *
# Copyright (c) 2013 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# File: component.mk
#       This file is component include make file of BSP.
# List of variables set in this file and their purpose:
# <mod>_RELPATH        - This is the relative path of the module, typically from
#                        top-level directory of the package
# <mod>_PATH           - This is the absolute path of the module. It derives from
#                        absolute path of the top-level directory (set in env.mk)
#                        and relative path set above
# <mod>_INCLUDE        - This is the path that has interface header files of the
#                        module. This can be multiple directories (space separated)
# <mod>_PKG_LIST       - Names of the modules (and sub-modules) that are a part
#                        part of this module, including itself.
# <mod>_PLATFORM_DEPENDENCY - "yes": means the code for this module depends on
#                             platform and the compiled obj/lib has to be kept
#                             under <platform> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no platform dependent code and hence
#                             the obj/libs are not kept under <platform> dir.
# <mod>_CORE_DEPENDENCY     - "yes": means the code for this module depends on
#                             core and the compiled obj/lib has to be kept
#                             under <core> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no core dependent code and hence
#                             the obj/libs are not kept under <core> dir.
# <mod>_APP_STAGE_FILES     - List of source files that belongs to the module
#                             <mod>, but that needs to be compiled at application
#                             build stage (in the context of the app). This is
#                             primarily for link time configurations or if the
#                             source file is dependent on options/defines that are
#                             application dependent. This can be left blank or
#                             not defined at all, in which case, it means there
#                             no source files in the module <mod> that are required
#                             to be compiled in the application build stage.
#

bsp_PKG_LIST = bsp_boards bsp_common bsp_osal bsp_devices bsp_fvid2 bsp_i2c bsp_mcspi bsp_platforms bsp_uart bsp_vps bsp_audio bsp_mcasp bsp_examples_utility

#
# BSP Modules
#

# Board Drivers
bsp_boards_RELPATH = src/boards
bsp_boards_PATH = $(bsp_PATH)/$(bsp_boards_RELPATH)
bsp_boards_INCLUDE = $(bsp_PATH)/$(bsp_boards_RELPATH)
bsp_boards_PKG_LIST = bsp_boards
bsp_boards_PLATFORM_DEPENDENCY = yes

# BSP Common
bsp_common_RELPATH = src/common
bsp_common_PATH = $(bsp_PATH)/$(bsp_common_RELPATH)
bsp_common_INCLUDE = $(bsp_PATH)/$(bsp_common_RELPATH)
bsp_common_PKG_LIST = bsp_common
bsp_common_PLATFORM_DEPENDENCY = yes

# BSP Osal
bsp_osal_RELPATH = src/osal
bsp_osal_PATH = $(bsp_PATH)/$(bsp_osal_RELPATH)
bsp_osal_INCLUDE = $(bsp_PATH)/$(bsp_osal_RELPATH)
bsp_osal_PKG_LIST = bsp_osal
bsp_osal_PLATFORM_DEPENDENCY = yes

# External Device Drivers
bsp_devices_RELPATH = src/devices
bsp_devices_PATH = $(bsp_PATH)/$(bsp_devices_RELPATH)
bsp_devices_INCLUDE = $(bsp_PATH)/$(bsp_devices_RELPATH)
bsp_devices_PKG_LIST = bsp_devices
bsp_devices_PLATFORM_DEPENDENCY = yes

# FVID2 Driver Layer
bsp_fvid2_RELPATH = src/fvid2
bsp_fvid2_PATH = $(bsp_PATH)/$(bsp_fvid2_RELPATH)
bsp_fvid2_INCLUDE = $(bsp_PATH)/$(bsp_fvid2_RELPATH)
bsp_fvid2_PKG_LIST = bsp_fvid2
bsp_fvid2_PLATFORM_DEPENDENCY = yes

# I2C Driver
bsp_i2c_RELPATH = src/i2c
bsp_i2c_PATH = $(bsp_PATH)/$(bsp_i2c_RELPATH)
bsp_i2c_INCLUDE = $(bsp_PATH)/$(bsp_i2c_RELPATH)
bsp_i2c_PKG_LIST = bsp_i2c
bsp_i2c_PLATFORM_DEPENDENCY = yes

# AUDIO Driver
bsp_audio_RELPATH = src/audio
bsp_audio_PATH = $(bsp_PATH)/$(bsp_audio_RELPATH)
bsp_audio_INCLUDE = $(bsp_PATH)/$(bsp_audio_RELPATH)
bsp_audio_PKG_LIST = bsp_audio
bsp_audio_PLATFORM_DEPENDENCY = yes

# MCASP Driver
bsp_mcasp_RELPATH = src/mcasp
bsp_mcasp_PATH = $(bsp_PATH)/$(bsp_mcasp_RELPATH)
bsp_mcasp_INCLUDE = $(bsp_PATH)/$(bsp_mcasp_RELPATH)
bsp_mcasp_PKG_LIST = bsp_mcasp
bsp_mcasp_PLATFORM_DEPENDENCY = yes

# MCSPI Driver
bsp_mcspi_RELPATH = src/mcspi
bsp_mcspi_PATH = $(bsp_PATH)/$(bsp_mcspi_RELPATH)
bsp_mcspi_INCLUDE = $(bsp_PATH)/$(bsp_mcspi_RELPATH)
bsp_mcspi_PKG_LIST = bsp_mcspi
bsp_mcspi_PLATFORM_DEPENDENCY = yes

# Platform Drivers
bsp_platforms_RELPATH = src/platforms
bsp_platforms_PATH = $(bsp_PATH)/$(bsp_platforms_RELPATH)
bsp_platforms_INCLUDE = $(bsp_PATH)/$(bsp_platforms_RELPATH)
bsp_platforms_PKG_LIST = bsp_platforms
bsp_platforms_PLATFORM_DEPENDENCY = yes

# UART Driver
bsp_uart_RELPATH = src/uart
bsp_uart_PATH = $(bsp_PATH)/$(bsp_uart_RELPATH)
bsp_uart_INCLUDE = $(bsp_PATH)/$(bsp_uart_RELPATH)
bsp_uart_PKG_LIST = bsp_uart
bsp_uart_PLATFORM_DEPENDENCY = yes

# BSP VPS Drivers
bsp_vps_RELPATH = src/vps
bsp_vps_PATH = $(bsp_PATH)/$(bsp_vps_RELPATH)
bsp_vps_INCLUDE = $(bsp_PATH)/$(bsp_vps_RELPATH)
bsp_vps_PKG_LIST = bsp_vps
bsp_vps_PLATFORM_DEPENDENCY = yes

# BSP VPS Capture Driver
bsp_vps_captdrv_RELPATH = src/vps/captdrv
bsp_vps_captdrv_PATH = $(bsp_PATH)/$(bsp_vps_captdrv_RELPATH)
bsp_vps_captdrv_INCLUDE = $(bsp_PATH)/$(bsp_vps_captdrv_RELPATH)
bsp_vps_captdrv_PKG_LIST = bsp_vps_captdrv
bsp_vps_captdrv_PLATFORM_DEPENDENCY = yes

# BSP VPS VPE Driver
bsp_vps_vpedrv_RELPATH = src/vps/vpedrv
bsp_vps_vpedrv_PATH = $(bsp_PATH)/$(bsp_vps_vpedrv_RELPATH)
bsp_vps_vpedrv_INCLUDE = $(bsp_PATH)/$(bsp_vps_vpedrv_RELPATH)
bsp_vps_vpedrv_PKG_LIST = bsp_vps_vpedrv
bsp_vps_vpedrv_PLATFORM_DEPENDENCY = yes

# BSP VPS Display Driver
bsp_vps_dispdrv_RELPATH = src/vps/dispdrv
bsp_vps_dispdrv_PATH = $(bsp_PATH)/$(bsp_vps_dispdrv_RELPATH)
bsp_vps_dispdrv_INCLUDE = $(bsp_PATH)/$(bsp_vps_dispdrv_RELPATH)
bsp_vps_dispdrv_PKG_LIST = bsp_vps_dispdrv
bsp_vps_dispdrv_PLATFORM_DEPENDENCY = yes

# BSP VPS M2M Driver
bsp_vps_m2mdrv_RELPATH = src/vps/m2mdrv
bsp_vps_m2mdrv_PATH = $(bsp_PATH)/$(bsp_vps_m2mdrv_RELPATH)
bsp_vps_m2mdrv_INCLUDE = $(bsp_PATH)/$(bsp_vps_m2mdrv_RELPATH)
bsp_vps_m2mdrv_PKG_LIST = bsp_vps_m2mdrv
bsp_vps_m2mdrv_PLATFORM_DEPENDENCY = yes

# Example Utility
bsp_examples_utility_RELPATH = examples/utility
bsp_examples_utility_PATH = $(bsp_PATH)/$(bsp_examples_utility_RELPATH)
bsp_examples_utility_INCLUDE = $(bsp_PATH)/$(bsp_examples_utility_RELPATH)
bsp_examples_utility_PKG_LIST = bsp_examples_utility
bsp_examples_utility_PLATFORM_DEPENDENCY = yes

# Links
bsp_examples_links_RELPATH = examples/common/vps/chains/links
bsp_examples_links_PATH = $(bsp_PATH)/$(bsp_examples_links_RELPATH)
bsp_examples_links_INCLUDE = $(bsp_PATH)/$(bsp_examples_links_RELPATH)
bsp_examples_links_PKG_LIST = bsp_examples_links
bsp_examples_links_PLATFORM_DEPENDENCY = yes

# Component specific CFLAGS
CFLAGS_COMP_COMMON +=

ifeq ($(PLATFORM),tda2xx-mc)
  BSP_CFLAGS = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI -DTDA2XX_MC_BUILD
endif
ifeq ($(PLATFORM),tda2xx-evm)
  BSP_CFLAGS = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda2xx-interposer)
  BSP_CFLAGS = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI -DTDA3XX_INTERPOSER_BUILD
endif
ifeq ($(PLATFORM),dra7xx-evm)
  BSP_CFLAGS = -DDRA7XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda2ex-evm)
  BSP_CFLAGS = -DTDA2EX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda3xx-evm)
  BSP_CFLAGS = -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),ti814x-evm)
  BSP_CFLAGS = -DTI814X_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda2xx-virtio)
  BSP_CFLAGS = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_VIRTIO
endif
ifeq ($(PLATFORM),tda2xx-sim)
  BSP_CFLAGS = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_SIM
endif
ifeq ($(PLATFORM),tda2xx-zebu)
  BSP_CFLAGS = -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_ZEBU
endif
ifeq ($(PLATFORM),tda3xx-sim)
  BSP_CFLAGS = -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_SIM
endif
ifeq ($(PLATFORM),tda3xx-zebu)
  BSP_CFLAGS = -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_ZEBU
endif
ifeq ($(PLATFORM),ti8149-evm)
  BSP_CFLAGS = -DTI8149_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),ti811x-evm)
  BSP_CFLAGS = -DTI811X_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),omap5430-evm)
  BSP_CFLAGS = -DOMAP5430_BUILD -DOMAP5X_FAMILY_BUILD -DPLATFORM_EVM_SI
endif

#Enable trace only for non-Klockwork build and for all profiles
ifeq ($(KW_BUILD),no)
  BSP_CFLAGS += -DTRACE_ENABLE
endif

# Enable standard asserts for klockwork build
ifeq ($(KW_BUILD),yes)
  BSP_CFLAGS += -DUSE_STD_ASSERT -DASSERT_ENABLE -DTRACE_ENABLE
endif

ifeq ($(CORE),a15_0)
  BSP_CFLAGS += -DBUILD_A15
endif

# Set default packaging for differenet moduels, select none
PACKAGE_VIP = no
PACKAGE_VPE = no
PACKAGE_DSS = no
PACKAGE_M2M = no
PACKAGE_ISS_DEF = no
PACKAGE_ISS = no
PACKAGE_SIMCOP = no

#Default to all if not set from rules.make or command line
ifeq ($(PACKAGE_SELECT), )
  PACKAGE_SELECT := all
endif

#Use PACKAGE_SELECT input
ifeq ($(PACKAGE_SELECT),all)
  BSP_CFLAGS += -DVPS_VIP_BUILD
  BSP_CFLAGS += -DVPS_CAPT_BUILD
  PACKAGE_VIP = yes
  BSP_CFLAGS += -DVPS_VPE_BUILD
  PACKAGE_VPE = yes
  BSP_CFLAGS += -DVPS_DSS_BUILD
  BSP_CFLAGS += -DVPS_DISP_BUILD
  PACKAGE_DSS = yes

  ifeq ($(SOCFAMILY),tda3xx)
    BSP_CFLAGS += -DVPS_ISS_ISP_DEF
    PACKAGE_ISS_DEF = yes
    BSP_CFLAGS += -DVPS_ISS_BUILD
    PACKAGE_ISS = yes
    BSP_CFLAGS += -DVPS_M2M_BUILD
    PACKAGE_M2M = yes
    BSP_CFLAGS += -DVPS_SIMCOP_BUILD
    PACKAGE_SIMCOP = yes
  endif
endif
ifeq ($(PACKAGE_SELECT),vps-hal-only)
  BSP_CFLAGS += -DVPS_VIP_BUILD
  BSP_CFLAGS += -DVPS_CAPT_BUILD
  PACKAGE_VIP = yes
  BSP_CFLAGS += -DVPS_VPE_BUILD
  PACKAGE_VPE = yes
  BSP_CFLAGS += -DVPS_DSS_BUILD
  BSP_CFLAGS += -DVPS_DISP_BUILD
  PACKAGE_DSS = yes
  ifeq ($(SOCFAMILY),tda3xx)
    BSP_CFLAGS += -DVPS_ISS_ISP_DEF
    PACKAGE_ISS_DEF = yes
    BSP_CFLAGS += -DVPS_ISS_BUILD
    PACKAGE_ISS = yes
    BSP_CFLAGS += -DVPS_SIMCOP_BUILD
    PACKAGE_SIMCOP = yes
  endif
endif
ifeq ($(PACKAGE_SELECT),vps-vip-only)
  BSP_CFLAGS += -DVPS_VIP_BUILD
  BSP_CFLAGS += -DVPS_CAPT_BUILD
  PACKAGE_VIP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vpe-only)
  BSP_CFLAGS += -DVPS_VPE_BUILD
  PACKAGE_VPE = yes
endif
ifeq ($(PACKAGE_SELECT),vps-dss-only)
  BSP_CFLAGS += -DVPS_DSS_BUILD
  BSP_CFLAGS += -DVPS_DISP_BUILD
  PACKAGE_DSS = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vip-dss)
  BSP_CFLAGS += -DVPS_VIP_BUILD
  BSP_CFLAGS += -DVPS_CAPT_BUILD
  PACKAGE_VIP = yes
  BSP_CFLAGS += -DVPS_DSS_BUILD
  BSP_CFLAGS += -DVPS_DISP_BUILD
  PACKAGE_DSS = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vip-vpe)
  BSP_CFLAGS += -DVPS_VIP_BUILD
  BSP_CFLAGS += -DVPS_CAPT_BUILD
  PACKAGE_VIP = yes
  BSP_CFLAGS += -DVPS_VPE_BUILD
  PACKAGE_VPE = yes
endif

ifeq ($(PACKAGE_SELECT),vps-iss-only)
  ifeq ($(SOCFAMILY),tda3xx)
    BSP_CFLAGS += -DVPS_ISS_ISP_DEF
    PACKAGE_ISS_DEF = yes
    BSP_CFLAGS += -DVPS_CAPT_BUILD
    BSP_CFLAGS += -DVPS_M2M_BUILD
    PACKAGE_M2M = yes
    BSP_CFLAGS += -DVPS_ISS_BUILD
    PACKAGE_ISS = yes
    BSP_CFLAGS += -DVPS_SIMCOP_BUILD
    PACKAGE_SIMCOP = yes
  endif
endif

ifeq ($(PACKAGE_SELECT), vps-iss-dss-only)
  ifeq ($(SOCFAMILY),tda3xx)
    BSP_CFLAGS += -DVPS_ISS_ISP_DEF
    PACKAGE_ISS_DEF = yes
    BSP_CFLAGS += -DVPS_CAPT_BUILD
    BSP_CFLAGS += -DVPS_M2M_BUILD
    PACKAGE_M2M = yes
    BSP_CFLAGS += -DVPS_ISS_BUILD
    PACKAGE_ISS = yes
    BSP_CFLAGS += -DVPS_SIMCOP_BUILD
    PACKAGE_SIMCOP = yes
    BSP_CFLAGS += -DVPS_DSS_BUILD
    BSP_CFLAGS += -DVPS_DISP_BUILD
    PACKAGE_DSS = yes
  endif
endif

ifneq ($(SOCFAMILY),$(filter $(SOCFAMILY), tda3xx))
  PACKAGE_ISS_DEF = no
  PACKAGE_SIMCOP = no
  PACKAGE_ISS = no
  BSP_CFLAGS += -UVPS_ISS_BUILD -UVPS_SIMCOP_BUILD -UVPS_ISS_ISP_DEF
endif

ifneq ($(SOCFAMILY),$(filter $(SOCFAMILY), tda2xx tda3xx ti814x ti8149 ti811x))
  PACKAGE_VIP = no
  BSP_CFLAGS += -UVPS_VIP_BUILD
  BSP_CFLAGS += -UVPS_CAPT_BUILD
endif

ifneq ($(SOCFAMILY),$(filter $(SOCFAMILY), tda2xx ti814x ti8149 ti811x))
  PACKAGE_VPE = no
  BSP_CFLAGS += -UVPS_VPE_BUILD
endif

ifneq ($(SOCFAMILY),$(filter $(SOCFAMILY), tda2xx tda3xx omap5430))
  PACKAGE_DSS = no
  BSP_CFLAGS += -UVPS_DSS_BUILD
  BSP_CFLAGS += -UVPS_DISP_BUILD
endif

# user can set these through command line while building
# usage gmake -s <target> PACKAGE_VIP1_BUILD=<yes/no> PACKAGE_VIP2_BUILD=<yes/no> PACKAGE_VIP3_BUILD=<yes/no>
# if $(PACKAGE_VIP)=no (i.e. PACKAGE_SELECT=<non-vip build>, then these variables are all set to "no" internally
ifeq ($(PACKAGE_VIP),yes)
  ifeq ($(PACKAGE_VIP1_BUILD),)
    PACKAGE_VIP1_BUILD = yes
  endif
  ifeq ($(PACKAGE_VIP2_BUILD),)
    PACKAGE_VIP2_BUILD = yes
  endif
  ifeq ($(PACKAGE_VIP3_BUILD),)
    PACKAGE_VIP3_BUILD = yes
  endif
endif
ifeq ($(PACKAGE_VIP),no)
  PACKAGE_VIP1_BUILD = no
  PACKAGE_VIP2_BUILD = no
  PACKAGE_VIP3_BUILD = no
endif

# Set compiler build macros
ifeq ($(PACKAGE_VIP1_BUILD),yes)
  BSP_CFLAGS += -DVPS_VIP1_BUILD
endif
ifeq ($(PACKAGE_VIP2_BUILD),yes)
  BSP_CFLAGS += -DVPS_VIP2_BUILD
endif
ifeq ($(PACKAGE_VIP3_BUILD),yes)
  BSP_CFLAGS += -DVPS_VIP3_BUILD
endif

ifeq ($(PROFILE_$(CORE)),debug)
  BSP_CFLAGS += -DDEBUG_BUILD
# Enable asserts for debug build
  BSP_CFLAGS += -DASSERT_ENABLE
endif

ifeq ($(PROFILE_$(CORE)),release)
  BSP_CFLAGS += -DRELEASE_BUILD
# Enable asserts for release build
  BSP_CFLAGS += -DASSERT_ENABLE
endif

ifeq ($(PROFILE_$(CORE)),prod_release)
  BSP_CFLAGS += -DPROD_RELEASE_BUILD
# Disable asserts for production release
#  BSP_CFLAGS += -DASSERT_ENABLE
endif

ifeq ($(CORE),m3vpss)
  BSP_CFLAGS += -DTI814x_M3
endif

ifeq ($(CORE),m3vpss)
  BSP_CFLAGS += -DBUILD_M3
endif

ifeq ($(CORE),m3video)
  BSP_CFLAGS += -DBUILD_M3
endif

ifeq ($(CORE),m4vpss)
  BSP_CFLAGS += -DBUILD_M4 -DMcasp_LOOPJOB_ENABLED
endif

ifeq ($(CORE),m4video)
  BSP_CFLAGS += -DBUILD_M4
endif

ifeq ($(CORE),a8host)
  BSP_CFLAGS += -DBUILD_A8
endif

ifeq ($(CORE),a15host)
  BSP_CFLAGS += -DBUILD_A15
endif

ifeq ($(CORE),c66x)
  BSP_CFLAGS += -DBUILD_DSP
endif

ifeq ($(CORE),arp32_1)
  BSP_CFLAGS += -DBUILD_ARP32
endif

ifeq ($(CORE),c6xdsp)
  BSP_CFLAGS += -DBUILD_DSP -DBIOS_PSP_DM8148_BASE_BOARD_AUDIO -DAIC_MASTER -DMcasp_LOOPJOB_ENABLED -DPSP_DISABLE_INPUT_PARAMETER_CHECK
endif

ifeq ($(CORE),c66xdsp)
  BSP_CFLAGS += -DBUILD_DSP -DBIOS_PSP_DM8148_BASE_BOARD_AUDIO -DMcasp_LOOPJOB_ENABLED -DPSP_DISABLE_INPUT_PARAMETER_CHECK
endif

# Enable custom frame buffer memory size
ifneq ($(CUSTOM_MEM_FRAME_HEAP_SIZE), )
  BSP_CFLAGS += -DCUSTOM_MEM_FRAME_HEAP_SIZE=$(CUSTOM_MEM_FRAME_HEAP_SIZE)
endif

ifeq ($(INCLUDE_WDR_LDC), )
  INCLUDE_WDR_LDC := no
endif

export BSP_LIBS
export BSP_EXAMPLE_LIBS
export BSP_CFLAGS
export PACKAGE_VIP
export PACKAGE_VPE
export PACKAGE_DSS
export PACKAGE_M2M
export PACKAGE_ISS_DEF
export PACKAGE_ISS
export PACKAGE_SIMCOP
export PACKAGE_VIP1_BUILD
export PACKAGE_VIP2_BUILD
export PACKAGE_VIP3_BUILD
export INCLUDE_WDR_LDC

# Nothing beyond this point
