# Dependency Versions
XDC_VERSION=3_30_03_47_core
NDK_VERSION=2_24_00_11
BIOS_VERSION=6_40_03_39
UIA_VERSION=2_00_00_28

ifeq ($(OS),Windows_NT)
  PATH_SEPARATOR    = ;
  TOOLS_DIR         ?= "C:/CCSv6.0.0"
else
  # else, assume it is linux
  PATH_SEPARATOR    = :
  TOOLS_DIR         ?= /opt/ti
endif
COMPILER_DIR    ?= $(TOOLS_DIR)/ccsv6/tools/compiler

#
# Dependency components paths
#
XDC_ROOT        ?= $(TOOLS_DIR)/xdctools_$(XDC_VERSION)
NDK_ROOT        ?= $(TOOLS_DIR)/ndk_$(NDK_VERSION)
BIOS_ROOT       ?= $(TOOLS_DIR)/bios_$(BIOS_VERSION)
UIA_ROOT        ?= $(TOOLS_DIR)/uia_$(UIA_VERSION)

#
# CodeGen/Compiler tools paths
#
TIARMCGT_ROOT   ?= $(COMPILER_DIR)/arm_5.1.7
GCC_ROOT        ?= $(COMPILER_DIR)/gcc-arm-none-eabi-4_7-2013q3
CGT6X_ROOT      ?= $(COMPILER_DIR)/c6000_7.4.8

export XDC_ROOT
export NDK_ROOT
export BIOS_ROOT
export UIA_ROOT
export TIARMCGT_ROOT
export GCC_ROOT
export CGT6X_ROOT
