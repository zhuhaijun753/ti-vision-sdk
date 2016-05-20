# Makefile for UART sample app

APP_NAME = bsp_examples_uart

SRCDIR = src
INCDIR = .

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc edma starterware starterware_hal bsp bsp_examples

# List all the components required by the application
COMP_LIST_COMMON = starterware_common starterware_hal i2c_lib sys_config \
                   edma3_lld_drv edma3_lld_drv_sample edma3_lld_rm edma3_lld_rm_sample \
                   bsp_uart bsp_common bsp_osal bsp_platforms bsp_boards bsp_devices bsp_fvid2 bsp_i2c bsp_examples_utility

# XDC CFG File
XDC_CFG_FILE_m4vpss = uartSample.cfg
XDC_CFG_FILE_m3vpss = uartSampleM3.cfg
XDC_CFG_FILE_a15_0  = uartSampleA15.cfg

# Common source files and CFLAGS across all platforms and cores
SRCS_m4vpss = uartSample_io.c uartSample_main.c
CFLAGS_LOCAL_m4vpss = $(BSP_CFLAGS)
SRCS_a15_0 = uartSample_io.c uartSample_main.c
CFLAGS_LOCAL_a15_0 = $(BSP_CFLAGS)
SRCS_m3vpss = uartSample_io.c uartSample_main.c
CFLAGS_LOCAL_m3vpss = $(BSP_CFLAGS)

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
