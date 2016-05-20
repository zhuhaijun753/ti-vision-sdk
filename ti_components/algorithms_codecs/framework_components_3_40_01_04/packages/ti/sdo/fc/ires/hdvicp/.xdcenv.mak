#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages;/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages;/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages;/datalocal1/ti_components/drivers/edma3_lld_02_12_00_20/packages;/datalocal1/user/shiju/ADAS/vision_sdk/../ti_components/drivers/vayu_drivers/bspdrivers_;/datalocal1/user/shiju/ADAS/vision_sdk/../ti_components/drivers/starterware/starterware_;/datalocal1/ti_components/algorithms_codecs/framework_components_3_40_01_04/packages;/datalocal1/user/shiju/ADAS/vision_sdk;/datalocal1/ti_components/algorithms_codecs/xdais_7_24_00_04/packages;/datalocal1/ti_components/algorithms_codecs/ivahd_hdvicp20api_01_00_00_23_production/packages;/datalocal1/ti_components/algorithms_codecs/ivahd_jpegvdec_01_00_13_01_production/packages;/datalocal1/ti_components/algorithms_codecs/ivahd_jpegvenc_01_00_16_01_production/packages;/datalocal1/ti_components/networking/ndk_2_24_02_31/packages;/datalocal1/ti_components/networking/nsp_gmacsw_4_13_00_00/packages;/datalocal1/ti_components/networking/avbtp_0_09_00_01/packages;
override XDCROOT = /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core
override XDCBUILDCFG = /datalocal1/user/shiju/ADAS/vision_sdk/build/tda2xx/config_m4.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = profile=release
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages;/datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages;/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages;/datalocal1/ti_components/drivers/edma3_lld_02_12_00_20/packages;/datalocal1/user/shiju/ADAS/vision_sdk/../ti_components/drivers/vayu_drivers/bspdrivers_;/datalocal1/user/shiju/ADAS/vision_sdk/../ti_components/drivers/starterware/starterware_;/datalocal1/ti_components/algorithms_codecs/framework_components_3_40_01_04/packages;/datalocal1/user/shiju/ADAS/vision_sdk;/datalocal1/ti_components/algorithms_codecs/xdais_7_24_00_04/packages;/datalocal1/ti_components/algorithms_codecs/ivahd_hdvicp20api_01_00_00_23_production/packages;/datalocal1/ti_components/algorithms_codecs/ivahd_jpegvdec_01_00_13_01_production/packages;/datalocal1/ti_components/algorithms_codecs/ivahd_jpegvenc_01_00_16_01_production/packages;/datalocal1/ti_components/networking/ndk_2_24_02_31/packages;/datalocal1/ti_components/networking/nsp_gmacsw_4_13_00_00/packages;/datalocal1/ti_components/networking/avbtp_0_09_00_01/packages;/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages;../../../../..
HOSTOS = Linux
endif
