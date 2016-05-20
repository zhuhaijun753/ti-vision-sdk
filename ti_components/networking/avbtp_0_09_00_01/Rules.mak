# Dependency Versions
XDC_VERSION=3_25_05_94
NDK_VERSION=2_24_00_11
BIOS_VERSION=6_37_03_30
UIA_VERSION=1_04_00_06
EDMA3_VERSION=02_11_14_18
NSP_VERSION=4_12_00_00

ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR    = ;
  TOOLS_DIR         ?= "C:/CCSv5.4.0"
else
  # else, assume it is linux
  PATH_SEPARATOR    = :
  TOOLS_DIR         ?= /opt/ti
endif
COMPILER_DIR    ?= $(TOOLS_DIR)/ccsv5/tools/compiler

#
# Dependency components paths
#
XDC_ROOT        ?= $(TOOLS_DIR)/xdctools_$(XDC_VERSION)
NDK_ROOT        ?= $(TOOLS_DIR)/ndk_$(NDK_VERSION)
BIOS_ROOT       ?= $(TOOLS_DIR)/bios_$(BIOS_VERSION)
UIA_ROOT        ?= $(TOOLS_DIR)/uia_$(UIA_VERSION)
EDMA3_ROOT      ?= $(TOOLS_DIR)/edma3_lld_$(EDMA3_VERSION)
NSP_ROOT        ?= $(TOOLS_DIR)/nsp_gmacsw_$(NSP_VERSION)

#
# CodeGen/Compiler tools paths
#
TIARMCGT_ROOT   ?= $(COMPILER_DIR)/arm_5.0.7
GCC_ROOT        ?= $(COMPILER_DIR)/gcc-arm-none-eabi-4_7-2012q4
CGT6X_ROOT      ?= $(COMPILER_DIR)/c6000_7.4.4
