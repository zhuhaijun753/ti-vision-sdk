#
# Device StarterWare
#

# Setting environmental variable 'ROOTDIR' is not required
# Override ROOTDIR with current working directory path
ifeq ($(ROOTDIR),)
ROOTDIR := $(abspath .)
export ROOTDIR
endif

ifeq ($(starterware_PATH),)
starterware_PATH := $(ROOTDIR)
export starterware_PATH
endif

ifeq ($(MAKERULEDIR),)
MAKERULEDIR := $(ROOTDIR)/build/makerules
export MAKERULEDIR
endif

include $(MAKERULEDIR)/build_config.mk
include $(MAKERULEDIR)/platform.mk
include $(MAKERULEDIR)/env.mk
include $(MAKERULEDIR)/component.mk

CLEANALL_TARGETS = $(addsuffix _clean, $(starterware_PKG_LIST_ALL))
CLEANALL_EXAMPLES = $(addsuffix _clean, $(starterware_EXAMPLES_LIST))

.PHONY :
all: version libs examples sbl_all_opps sbl_multicore_app profiler_apps

libs: $(starterware_PKG_LIST_ALL)

examples: $(starterware_EXAMPLES_LIST)

sbl_multicore_app: sbl_multicore_mbx sbl_multicore_mbx_1 sbl_multicore_mbx_2 sbl_multicore_mbx_3

profiler_apps: norProfiler qspiProfiler sdProfiler

.PHONY : allclean
allclean:
	$(RM) -rf $(DEST_ROOT)

clean: libs_clean examples_clean sbl_all_opps_clean sbl_multicore_app_clean profiler_apps_clean

libs_clean: $(CLEANALL_TARGETS)

examples_clean: $(CLEANALL_EXAMPLES)

sbl_multicore_app_clean: sbl_multicore_mbx_clean sbl_multicore_mbx_1_clean sbl_multicore_mbx_2_clean sbl_multicore_mbx_3_clean

profiler_apps_clean: norProfiler_clean qspiProfiler_clean sdProfiler_clean

#=================================================================
# Rule to build and clean all modules and examples
# Library targets
version:
	$(ECHO) ------------------------------------------------------
	$(ECHO) \# Starterware 01.04.00.10
	$(ECHO) ------------------------------------------------------

starterware_hal:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

starterware_hal_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

sys_config:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

sys_config_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

utils_platform:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

utils_platform_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

starterware_boards:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

starterware_boards_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

starterware_devices:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

starterware_devices_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

i2c_lib:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

i2c_lib_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

uartConsole:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

uartConsole_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

qspi_flashlib:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

qspi_flashlib_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

norflash_lib:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

norflash_lib_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

fat_lib:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

fat_lib_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

fat_lib_edma:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

fat_lib_edma_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

starterware_common:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

starterware_common_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

starterware_vpslib:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4vpss
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4vpss
endif

starterware_vpslib_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4vpss
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4vpss
endif

starterware_osal:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4vpss
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4vpss
endif

starterware_osal_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4vpss
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4vpss
endif

starterware_examples_utility:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

starterware_examples_utility_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

starterware_pm_hal:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

starterware_pm_hal_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

starterware_pm_hal_arp32:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=arp32_1
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=arp32_1
endif

starterware_pm_hal_arp32_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=arp32_1
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=arp32_1
endif

starterware_pm_lib:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

starterware_pm_lib_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

starterware_pm_lib_arp32:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=arp32_1
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=arp32_1
endif

starterware_pm_lib_arp32_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=arp32_1
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=arp32_1
endif

#=================================================================
# Examples

mailbox_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

mailbox_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

timer_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

timer_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

i2c_driver_led_blink_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

i2c_driver_led_blink_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

gpio_output_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

gpio_output_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

qspi_test_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

qspi_test_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

spinlock_test:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

spinlock_test_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

ocmc_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=c66x
	$(MAKE) -C $($@_PATH) CORE=m4
endif

ocmc_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif


edma_test_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

edma_test_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

sensor_config_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

sensor_config_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

qspiFlashWriter:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

qspiFlashWriter_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

nor_flash_writer:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

nor_flash_writer_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

mmu_tlb_twl_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=arp32_1
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=c66x
	$(MAKE) -C $($@_PATH) CORE=arp32_1
endif

mmu_tlb_twl_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c674x
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=arp32_1
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=arp32_1
endif

DssApp:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(PLATFORM),tda3xx-sim)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(PLATFORM),tda3xx-zebu)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

DssApp_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean  CORE=m4
endif
ifeq ($(PLATFORM),tda3xx-sim)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean  CORE=m4
endif
ifeq ($(PLATFORM),tda3xx-zebu)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean  CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean  CORE=m4
endif

vipCapt:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

vipCapt_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean  CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean  CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean  CORE=m4
endif

mcaspTransmit_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

mcaspTransmit_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

nor_edma_read:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

nor_edma_read_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

nor_read_write:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

nor_read_write_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

mmcsd_fileIO_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

mmcsd_fileIO_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

mmc_raw_access:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

mmc_raw_access_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

mcspi_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
	$(MAKE) -C $($@_PATH) CORE=m3vpss
endif

mcspi_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m3vpss
endif

uart1_test_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

uart1_test_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

uart2_test_app:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

uart2_test_app_clean:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

uart3_test_app:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

uart3_test_app_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

uart_test:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

uart_test_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

eeprom_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

eeprom_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

pmic_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

pmic_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

temp_sensor_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

temp_sensor_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

i2c_test_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

i2c_test_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

edid_programmer:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

edid_programmer_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

gpio_exp_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

gpio_exp_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

boot_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

boot_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

ddr_test_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

ddr_test_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

uart_edma_test:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

uart_edma_test_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

uart_intr_test:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

uart_intr_test_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

i2c_eeprom_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

i2c_eeprom_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

mmu_translation_fault_handle_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

mmu_translation_fault_handle_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

gpio_input_interrupt_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

gpio_input_interrupt_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

mcspiMasterSlave_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

mcspiMasterSlave_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

wdtimer_app:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($@_PATH) CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

wdtimer_app_clean:
ifeq ($(SOCFAMILY),ti814x)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a8host
endif
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

mcaspBurstTransmit_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif

mcaspBurstTransmit_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

mcasp_sinetone_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

mcasp_sinetone_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

videoLoopback:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

videoLoopback_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

pcie_app_rc_write_loopback:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

pcie_app_rc_write_loopback_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

pcie_app_ep_write_loopback:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

pcie_app_ep_write_loopback_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

pm_cpuidle_test_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

pm_cpuidle_test_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

pm_arp32_cpuidle_test_app:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=arp32_1
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=arp32_1
endif

pm_arp32_cpuidle_test_app_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=arp32_1
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=arp32_1
endif

pm_systemconfig_test_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

pm_systemconfig_test_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

rti_app:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

rti_app_clean:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

crc_app:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

crc_app_clean:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

dcan_app_loopback:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

dcan_app_loopback_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

pm_junctiontemp_test_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

pm_junctiontemp_test_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

dcan_app_evm_loopback:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

dcan_app_evm_loopback_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

pm_clkrate_test_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

pm_clkrate_test_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

dcc_app:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

dcc_app_clean:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

xmc_mpu_app:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

xmc_mpu_app_clean:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

esm_app:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

esm_app_clean:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

adc_app:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

adc_app_clean:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

l3fw_app:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

l3fw_app_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

ecc_app:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

ecc_app_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

mmu_a15_data_validation_app:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

mmu_a15_data_validation_app_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

#=================================================================
# SBL

sbl_lib:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

sbl_lib_clean:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

sbl_utils:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

sbl_utils_clean:
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

sbl:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

sbl_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

sbl_all:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=sd
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=qspi
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=nor
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=qspi_sd
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=qspi
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=nor
endif

sbl_all_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=sd
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=qspi
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=nor
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=qspi_sd
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=qspi
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=nor
endif

sbl_all_opps:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=sd OPPMODE=opp_nom
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=sd OPPMODE=opp_od
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=sd OPPMODE=opp_high
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=qspi OPPMODE=opp_nom
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=qspi OPPMODE=opp_od
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=qspi OPPMODE=opp_high
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=nor OPPMODE=opp_nom
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=nor OPPMODE=opp_od
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=nor OPPMODE=opp_high
endif
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=sd OPPMODE=opp_low
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=qspi OPPMODE=opp_low
	$(MAKE) -C $($@_PATH) CORE=a15host BOOTMODE=nor OPPMODE=opp_low
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=qspi_sd OPPMODE=opp_nom
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=qspi OPPMODE=opp_nom
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=nor OPPMODE=opp_nom
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=qspi_sd OPPMODE=opp_od
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=qspi OPPMODE=opp_od
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=nor OPPMODE=opp_od
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=qspi_sd OPPMODE=opp_high
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=qspi OPPMODE=opp_high
	$(MAKE) -C $($@_PATH) CORE=m4 BOOTMODE=nor OPPMODE=opp_high
endif

sbl_all_opps_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=sd OPPMODE=opp_nom
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=sd OPPMODE=opp_od
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=sd OPPMODE=opp_high
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=qspi OPPMODE=opp_nom
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=qspi OPPMODE=opp_od
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=qspi OPPMODE=opp_high
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=nor OPPMODE=opp_nom
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=nor OPPMODE=opp_od
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=nor OPPMODE=opp_high
endif
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=sd OPPMODE=opp_low
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=qspi OPPMODE=opp_low
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host BOOTMODE=nor OPPMODE=opp_low
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=qspi_sd OPPMODE=opp_nom
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=qspi OPPMODE=opp_nom
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=nor OPPMODE=opp_nom
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=qspi_sd OPPMODE=opp_od
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=qspi OPPMODE=opp_od
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=nor OPPMODE=opp_od
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=qspi_sd OPPMODE=opp_high
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=qspi OPPMODE=opp_high
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4 BOOTMODE=nor OPPMODE=opp_high
endif

#=================================================================
# SBL multicore app

sbl_multicore_mbx:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

sbl_multicore_mbx_clean:
ifeq ($(SOCFAMILY),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

sbl_multicore_mbx_1:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
	$(MAKE) -C $($@_PATH) CORE=c66x
endif

sbl_multicore_mbx_1_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=c66x
endif

sbl_multicore_mbx_2:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

sbl_multicore_mbx_2_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

sbl_multicore_mbx_3:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

sbl_multicore_mbx_3_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

#=================================================================
# Profiler apps

norProfiler:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

norProfiler_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

qspiProfiler:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

qspiProfiler_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

sdProfiler:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif

sdProfiler_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif

safety_lib:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($@_PATH) CORE=a15host
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($@_PATH) CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($@_PATH) CORE=m4
endif

safety_lib_clean:
ifeq ($(SOC),tda2xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=a15host
endif
ifeq ($(SOC),tda2ex)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif
ifeq ($(SOCFAMILY),tda3xx)
	$(MAKE) -C $($(subst _clean,,$@)_PATH) clean CORE=m4
endif

#Below is used only for checking c++ build errors during development, not to be used for any other purpose
cplusplus_build:
	$(MAKE) all PROFILE=debug CPLUSPLUS_BUILD=yes

# Nothing beyond this point
