
ifeq ($(bsp_PATH), )

#Default build environment, windows or linux
ifeq ($(OS), )
  OS := Windows_NT
endif

bsp_RELPATH = bsp_01_04_00_08
starterware_RELPATH = starterware_01_04_00_10

ifeq ($(OS),Windows_NT)
#Paths for windows machine
  CODEGEN_PATH_M4 := C:/ti/ti-cgt-arm_5.2.5
  CODEGEN_PATH_M3 := C:/ti/ti-cgt-arm_5.2.5
  CODEGEN_PATH_A15 := C:/tools/gcc-arm-none-eabi-4_7-2013q3
  CODEGEN_PATH_DSP := C:/ti/C6000_7.4.2
  bsp_PATH := C:/ti/$(bsp_RELPATH)
  bios_PATH := C:/ti/bios_6_42_02_29
  xdc_PATH := C:/ti/xdctools_3_31_02_38_core
  starterware_PATH := C:/ti/starterware/$(starterware_RELPATH)
  edma3_lld_PATH := C:/ti/edma3_lld_02_12_00_20
else
#Paths for linux machine
  CODEGEN_PATH_M4 := /opt/tools/cgtools/ti-cgt-arm_5.2.5
  CODEGEN_PATH_M3 := /opt/tools/cgtools/ti-cgt-arm_5.2.5
  CODEGEN_PATH_A15 := /opt/tools/gcc-arm-none-eabi-4_7-2013q3
  CODEGEN_PATH_DSP := /opt/tools/cgtools/C6000_7.4.2
  bsp_PATH := /opt/ti/bsp/$(bsp_RELPATH)
  bios_PATH := /opt/tools/bios6/bios_6_42_02_29
  xdc_PATH := /opt/tools/xdc/xdctools_3_31_02_38_core
  starterware_PATH := /opt/ti/starterware/$(starterware_RELPATH)
  edma3_lld_PATH := /opt/tools/edma3/edma3_lld_02_12_00_20
endif

ROOTDIR := $(bsp_PATH)
XDCPATH = $(bios_PATH)/packages;$(xdc_PATH)/packages;$(edma3_lld_PATH)/packages;$(starterware_PATH);$(bsp_PATH)/examples;

# Default platform
# Supported values: tda2xx-evm, tda2xx-virtio, tda2xx-sim, tda2xx-zebu, tda2xx-interposer, tda2xx-mc,
#                   dra7xx-evm, tda2ex-evm,
#                   tda3xx-evm, tda3xx-sim, tda3xx-zebu,
#                   ti814x-evm, ti8149-evm, ti811x-evm, omap5430-evm
ifeq ($(PLATFORM), )
  PLATFORM := tda2xx-evm
endif

# Default to m3/m4 build depending on platform selected!!
ifeq ($(CORE), )
  CORE := m4vpss
  ifeq ($(PLATFORM),ti814x-evm)
    CORE := m3vpss
  endif
  ifeq ($(PLATFORM),ti8149-evm)
    CORE := m3vpss
  endif
  ifeq ($(PLATFORM),ti811x-evm)
    CORE := m3vpss
  endif
endif

# Default Profile
# Supported Values: debug | release | prod_release
ifeq ($(PROFILE), )
  PROFILE := release
endif

# Set Core Profile depending on PROFILE value
ifeq ($(PROFILE_$(CORE)), )
  PROFILE_$(CORE) := $(PROFILE)
endif

# Default PACKAGE_SELECT build flag
# Supported values: all, vps-hal-only, vps-vip-only, vps-vpe-only, vps-dss-only, vps-vip-dss, vps-vip-vpe
ifeq ($(PACKAGE_SELECT), )
  PACKAGE_SELECT := all
endif

# Default klockwork build flag, yes or no
ifeq ($(KW_BUILD), )
  KW_BUILD := no
endif

# Default C++ build flag, yes or no
ifeq ($(CPLUSPLUS_BUILD), )
  CPLUSPLUS_BUILD := no
endif

export OS
export PLATFORM
export CORE
export PROFILE_$(CORE)
export CODEGEN_PATH_M4
export CODEGEN_PATH_M3
export CODEGEN_PATH_A15
export CODEGEN_PATH_DSP
export bios_PATH
export xdc_PATH
export bsp_RELPATH
export bsp_PATH
export starterware_PATH
export edma3_lld_PATH
export ROOTDIR
export XDCPATH
export PACKAGE_SELECT
export KW_BUILD
export CPLUSPLUS_BUILD

endif

ifeq ($(MAKERULEDIR), )
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif

include $(MAKERULEDIR)/build_config.mk
include $(MAKERULEDIR)/platform.mk
include $(MAKERULEDIR)/env.mk
include $(MAKERULEDIR)/component.mk
