# Makefile for audio Sample application

APP_NAME = bsp_examples_audio_loopback

SRCDIR = src
INCDIR = . ../common

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc edma starterware starterware_hal bsp sys_config i2c_lib

# List all the components required by the application
COMP_LIST_c6xdsp = bsp_i2c bsp_platforms bsp_common bsp_osal starterware_common i2c_lib sys_config \
                   bsp_audio bsp_devices bsp_mcasp starterware_hal \
                   edma3_lld_drv edma3_lld_drv_sample edma3_lld_rm edma3_lld_rm_sample

COMP_LIST_c66xdsp = bsp_i2c bsp_platforms bsp_common bsp_osal starterware_common i2c_lib sys_config \
                    bsp_audio bsp_devices bsp_boards bsp_mcasp starterware_hal \
                    edma3_lld_drv edma3_lld_drv_sample edma3_lld_rm edma3_lld_rm_sample

COMP_LIST_m4vpss = bsp_i2c bsp_platforms bsp_common bsp_osal starterware_common i2c_lib sys_config \
                    bsp_audio bsp_devices bsp_boards bsp_mcasp bsp_examples_utility starterware_hal \
                   edma3_lld_drv edma3_lld_drv_sample edma3_lld_rm edma3_lld_rm_sample

COMP_LIST_COMMON =

# XDC CFG File
XDC_CFG_FILE_c6xdsp = audioLoopbacksample.cfg
XDC_CFG_FILE_c66xdsp = audioLoopbacksampleTda2xx.cfg
XDC_CFG_FILE_m4vpss = audioLoopbackSampleTda2xxM4.cfg

SRCS_c6xdsp = audioLoopbackSample_io.c audioLoopbackSample_main.c
CFLAGS_LOCAL_c6xdsp = $(BSP_CFLAGS)

SRCS_c66xdsp = audioLoopbackSample_io.c audioLoopbackSample_main.c audioLoopbackSample_xbar.c
CFLAGS_LOCAL_c66xdsp = $(BSP_CFLAGS)

SRCS_m4vpss = audioLoopbackSample_io.c audioLoopbackSample_main.c audioLoopbackSample_xbar.c
CFLAGS_LOCAL_m4vpss = $(BSP_CFLAGS)

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
