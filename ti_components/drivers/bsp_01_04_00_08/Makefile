
include Rules.make

BSP_PKG_LIST_CLEAN = $(addsuffix _clean, $(bsp_PKG_LIST))
BSP_PKG_LIST_PACKAGE  = $(addsuffix _package, $(bsp_PKG_LIST))

.PHONY : clean all allclean help

#=================================================================
#LIBS
$(bsp_PKG_LIST):
	$(MAKE) -C $($@_PATH)

$(BSP_PKG_LIST_CLEAN):
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean

$(BSP_PKG_LIST_PACKAGE):
	$(MAKE) -C $($(subst _package,,$@)_PATH) package

bsp: $(bsp_PKG_LIST)

clean: $(BSP_PKG_LIST_CLEAN)
	$(MAKE) examples_target BUILD_TARGET=clean

all: clean examples

allclean:
	$(RM) -rf $(DEST_ROOT)

package: $(BSP_PKG_LIST_PACKAGE)

packagehal: bsp_common_package bsp_platforms_package bsp_fvid2_package bsp_vps_package

help:
	$(ECHO) ------------------------------------------------------
	$(ECHO) \# BSP make help
	$(ECHO) ------------------------------------------------------
	$(ECHO) gmake -s [OPTIONAL MAKE VARIABLES]
	$(ECHO)
	$(ECHO) "Supported targets:"
	$(ECHO) "all: Default - Build all libraries and examples"
	$(ECHO) "clean: Clean all libraries and examples"
	$(ECHO) "allclean: Remove the binary directory"
	$(ECHO) "examples: Build all examples"
	$(ECHO) ""
	$(ECHO) "Optional make variables:"
	$(ECHO) "PLATFORM=[tda2xx-evm / dra7xx-evm / tda2ex-evm / tda3xx-evm / ti814x-evm]"
	$(ECHO) "    Default: tda2xx-evm"
	$(ECHO) "CORE=[m4vpss / m3vpss / c6xdsp / c66xdsp]"
	$(ECHO) "    Default: m4vpss"
	$(ECHO) "PROFILE=[debug / release / prod_release]"
	$(ECHO) "    Default: release"
	$(ECHO) "OS=[Windows_NT / linux]"
	$(ECHO) "    Default: Windows_NT"
	$(ECHO) "PACKAGE_SELECT=[all / vps-vip-only / vps-vpe-only / vps-dss-only / vps-vip-dss / vps-vip-vpe / vps-iss-only (tda3xx) / vps-iss-dss-only (tda3xx) ]"
	$(ECHO) "    Default: all"

#Below is used only for checking c++ build errors during development, not to be used for any other purpose
cplusplus_build:
	$(MAKE) bsp PROFILE=debug CPLUSPLUS_BUILD=yes

#=================================================================

#=================================================================
#Examples

BSP_EXAMPLES = $(bsp_PATH)/examples

SOCFAMILY_LIST_DEFAULT = tda2xx tda3xx
SOCFAMILY_LIST_VIP = tda2xx tda3xx
SOCFAMILY_LIST_VPE = tda2xx
SOCFAMILY_LIST_ISS = tda3xx
SOCFAMILY_LIST_DSS = tda2xx tda3xx omap5430
SOCFAMILY_LIST_SERIAL = tda2xx tda3xx ti814x
SOCFAMILY_LIST_AUDIO = tda2xx ti814x
SOCFAMILY_LIST_ULTRASONIC = tda2xx
SOCFAMILY_LIST_MCSPI_FLASH = ti814x

CORE_LIST_DEFAULT = m3vpss m4vpss
CORE_LIST_AUDIO = c6xdsp c66xdsp m4vpss
CORE_LIST_ISS = m4vpss
CORE_LIST_I2C = m3vpss m4vpss m4video
CORE_LIST_UART = m3vpss m4vpss a15_0

captIss: captureIss captureIssOtf

capture: captureVip subFrmCaptureVip captIss

iss: m2mIssWdr m2mIss loopbackIss m2mSimcopLdcVtnf captIss

display: displayDss displayDssWb

audio: bsp_examples_audio bsp_examples_audio_loopback

video: loopback capture display m2mVpe iss

serial: bsp_examples_i2c bsp_examples_i2cUtility bsp_examples_mcspi bsp_examples_mcspiMasterSlave bsp_examples_uart

examples: audio video serial

examples_target:
	$(MAKE) loopback_target
	$(MAKE) captureVip_target
	$(MAKE) subFrmCaptureVip_target
	$(MAKE) displayDss_target
	$(MAKE) displayDssWb_target
	$(MAKE) m2mVpe_target
	$(MAKE) bsp_examples_i2c_target
	$(MAKE) bsp_examples_i2cUtility_target
	$(MAKE) bsp_examples_mcspi_target
	$(MAKE) bsp_examples_uart_target
	$(MAKE) bsp_examples_mcspiLoopback_target
	$(MAKE) bsp_examples_spi1tospi2_target

platforms:
	$(MAKE) examples PLATFORM=tda2xx-evm
	$(MAKE) examples PLATFORM=tda2xx-virtio
	$(MAKE) examples PLATFORM=tda2xx-zebu
	$(MAKE) examples PLATFORM=tda3xx-evm
	$(MAKE) examples PLATFORM=tda3xx-sim
	$(MAKE) examples PLATFORM=tda3xx-zebu

platformsclean:
	$(MAKE) clean PLATFORM=tda2xx-evm
	$(MAKE) clean PLATFORM=tda2xx-virtio
	$(MAKE) clean PLATFORM=tda2xx-zebu
	$(MAKE) clean PLATFORM=tda3xx-evm
	$(MAKE) clean PLATFORM=tda3xx-sim
	$(MAKE) clean PLATFORM=tda3xx-zebu

profiles:
	$(MAKE) examples PROFILE_$(CORE)=debug
	$(MAKE) examples PROFILE_$(CORE)=release

profilesclean:
	$(MAKE) clean PROFILE_$(CORE)=debug
	$(MAKE) clean PROFILE_$(CORE)=release

allall:
	$(MAKE) platforms PROFILE_$(CORE)=debug
	$(MAKE) platforms PROFILE_$(CORE)=release

loopback_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_DEFAULT)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/loopback $(BUILD_TARGET)
  endif
endif

loopback:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_DEFAULT)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) loopback_target BUILD_TARGET=xdc_configuro
	$(MAKE) loopback_target
  endif
endif

captureIss_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/iss/captureIss $(BUILD_TARGET)
  endif
endif

captureIss:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) captureIss_target BUILD_TARGET=xdc_configuro
	$(MAKE) captureIss_target
  endif
endif

captureIssOtf_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/iss/captureIssOtf $(BUILD_TARGET)
  endif
endif

captureIssOtf:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) captureIssOtf_target BUILD_TARGET=xdc_configuro
	$(MAKE) captureIssOtf_target
  endif
endif

captureVip_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_VIP)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/capture/captureVip $(BUILD_TARGET)
  endif
endif

captureVip:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_VIP)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) captureVip_target BUILD_TARGET=xdc_configuro
	$(MAKE) captureVip_target
  endif
endif

subFrmCaptureVip_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_VIP)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/capture/subFrmCaptureVip $(BUILD_TARGET)
  endif
endif

subFrmCaptureVip:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_VIP)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) subFrmCaptureVip_target BUILD_TARGET=xdc_configuro
	$(MAKE) subFrmCaptureVip_target
  endif
endif

displayDss_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_DSS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/display/displayDss $(BUILD_TARGET)
  endif
endif

displayDss:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_DSS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) displayDss_target BUILD_TARGET=xdc_configuro
	$(MAKE) displayDss_target
  endif
endif

displayDssWb_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_DSS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/display/displayDssWb $(BUILD_TARGET)
  endif
endif

displayDssWb:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_DSS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) displayDssWb_target BUILD_TARGET=xdc_configuro
	$(MAKE) displayDssWb_target
  endif
endif

m2mVpe_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_VPE)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/vpe/m2mVpeScale $(BUILD_TARGET)
  endif
endif

m2mVpe:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_VPE)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) m2mVpe_target BUILD_TARGET=xdc_configuro
	$(MAKE) m2mVpe_target
  endif
endif

m2mIssWdr_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/iss/m2mWdr $(BUILD_TARGET)
  endif
endif

m2mSimcopLdcVtnf_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/iss/m2mSimcopLdcVtnf $(BUILD_TARGET)
  endif
endif

m2mIssWdr:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) m2mIssWdr_target BUILD_TARGET=xdc_configuro
	$(MAKE) m2mIssWdr_target
  endif
endif

m2mIss_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/iss/m2mIss $(BUILD_TARGET)
  endif
endif

m2mIss:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) m2mIss_target BUILD_TARGET=xdc_configuro
	$(MAKE) m2mIss_target
  endif
endif

loopbackIss_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) -C $(BSP_EXAMPLES)/vps/iss/loopback $(BUILD_TARGET)
  endif
endif

loopbackIss:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) loopbackIss_target BUILD_TARGET=xdc_configuro
	$(MAKE) loopbackIss_target
  endif
endif

m2mSimcopLdcVtnf:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ISS)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_ISS)))
	$(MAKE) m2mSimcopLdcVtnf_target BUILD_TARGET=xdc_configuro
	$(MAKE) m2mSimcopLdcVtnf_target
  endif
endif

bsp_examples_audio_sinetone_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_AUDIO)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_AUDIO)))
	$(MAKE) -C $(BSP_EXAMPLES)/audio/sinetone $(BUILD_TARGET)
  endif
endif

bsp_examples_audio_loopback_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_AUDIO)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_AUDIO)))
	$(MAKE) -C $(BSP_EXAMPLES)/audio/loopback $(BUILD_TARGET)
  endif
endif

bsp_examples_audio:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_AUDIO)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_AUDIO)))
	$(MAKE) bsp_examples_audio_sinetone_target BUILD_TARGET=xdc_configuro
	$(MAKE) bsp_examples_audio_sinetone_target
  endif
endif

bsp_examples_audio_loopback:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_AUDIO)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_AUDIO)))
	$(MAKE) bsp_examples_audio_loopback_target BUILD_TARGET=xdc_configuro
	$(MAKE) bsp_examples_audio_loopback_target
  endif
endif

bsp_examples_i2c_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_SERIAL)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_I2C)))
	$(MAKE) -C $(BSP_EXAMPLES)/i2c $(BUILD_TARGET)
  endif
endif

bsp_examples_i2c:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_SERIAL)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_I2C)))
	$(MAKE) bsp_examples_i2c_target BUILD_TARGET=xdc_configuro
	$(MAKE) bsp_examples_i2c_target
  endif
endif

bsp_examples_i2cUtility_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_SERIAL)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_I2C)))
	$(MAKE) -C $(BSP_EXAMPLES)/misc/i2cUtility $(BUILD_TARGET)
  endif
endif

bsp_examples_i2cUtility:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_SERIAL)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_I2C)))
	$(MAKE) bsp_examples_i2cUtility_target BUILD_TARGET=xdc_configuro
	$(MAKE) bsp_examples_i2cUtility_target
  endif
endif

bsp_examples_mcspi_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_MCSPI_FLASH)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/mcspi $(BUILD_TARGET)
  endif
endif

bsp_examples_mcspi:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_MCSPI_FLASH)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) bsp_examples_mcspi_target BUILD_TARGET=xdc_configuro
	$(MAKE) bsp_examples_mcspi_target
  endif
endif

bsp_examples_mcspiMasterSlave: bsp_examples_mcspiLoopback bsp_examples_spi1tospi2

bsp_examples_spi1tospi2_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_DEFAULT)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/mcspiMasterSlave/spi1tospi2 $(BUILD_TARGET)
  endif
endif

bsp_examples_spi1tospi2:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_DEFAULT)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) bsp_examples_spi1tospi2_target BUILD_TARGET=xdc_configuro
	$(MAKE) bsp_examples_spi1tospi2_target
  endif
endif

bsp_examples_uart_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_SERIAL)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_UART)))
	$(MAKE) -C $(BSP_EXAMPLES)/uart $(BUILD_TARGET)
  endif
endif

bsp_examples_uart:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_SERIAL)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_UART)))
	$(MAKE) bsp_examples_uart_target BUILD_TARGET=xdc_configuro
	$(MAKE) bsp_examples_uart_target
  endif
endif

bsp_examples_ultrasonic_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ULTRASONIC)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/misc/ultrasonic $(BUILD_TARGET)
  endif
endif

bsp_examples_ultrasonic:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_ULTRASONIC)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) bsp_examples_ultrasonic_target BUILD_TARGET=xdc_configuro
	$(MAKE) bsp_examples_ultrasonic_target
  endif
endif

bsp_examples_mcspiLoopback_target:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_SERIAL)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) -C $(BSP_EXAMPLES)/mcspiMasterSlave/loopback $(BUILD_TARGET)
  endif
endif

bsp_examples_mcspiLoopback:
ifeq ($(SOCFAMILY),$(filter $(SOCFAMILY), $(SOCFAMILY_LIST_SERIAL)))
  ifeq ($(CORE),$(filter $(CORE), $(CORE_LIST_DEFAULT)))
	$(MAKE) bsp_examples_mcspiLoopback_target BUILD_TARGET=xdc_configuro
	$(MAKE) bsp_examples_mcspiLoopback_target
  endif
endif

