#*******************************************************************************
#                                                                              *
# Copyright (c) 2013 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# File: component.mk
#       This file is component include make file of starterware.
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

############################
# device starterware package
############################

starterware_PKG_LIST_ALL = starterware_hal sys_config utils_platform starterware_boards starterware_devices i2c_lib uartConsole qspi_flashlib norflash_lib fat_lib fat_lib_edma starterware_common starterware_vpslib starterware_osal sbl_lib sbl_utils starterware_pm_hal starterware_pm_lib starterware_examples_utility safety_lib

############################
# device starterware hal
# List of components included under starterware hal
# The components included here are built and will be part of starterware hal library
# List below all components as exaples values
# mailbox i2c
# starterware HW files will be included in this order :
# 1. SOC specific HW file - $(starterware_PATH)/include/$(SOCFAMILY)/$(SOC)/hw
# 2. SOC Family specific HW file - $(starterware_PATH)/include/$(SOCFAMILY)/hw
# 3. Common HW file - $(starterware_PATH)/include/hw
############################
starterware_hal_COMP_LIST = hsi2c uart spinlock ocmc gpmc timer edma mcspi qspi mailbox mcasp gpio mmu mmcsd wdtimer pcie rti crc dcan tesoc dcc esm adc l3fw emif

starterware_hal_RELPATH = drivers
starterware_hal_PATH = $(starterware_PATH)/$(starterware_hal_RELPATH)
starterware_hal_PLATFORM_DEPENDENCY = yes
export starterware_hal_COMP_LIST
export starterware_hal_PLATFORM_DEPENDENCY
starterware_hal_PKG_LIST = starterware_hal
starterware_hal_INCLUDE = $(starterware_PATH)/include $(starterware_PATH)/include/$(SOCFAMILY)/$(SOC)/hw $(starterware_PATH)/include/$(SOCFAMILY)/hw $(starterware_PATH)/include/hw $(starterware_PATH)/include/$(ARCH)/$(SOCFAMILY) $(starterware_PATH)/include/$(ARCH)  $(starterware_PATH)/include/$(SOCFAMILY)/$(SOC) $(starterware_PATH)/include/$(SOCFAMILY)

####################################
# List of All PM Components
####################################

starterware_pm_hal_RELPATH = pm/pmhal
starterware_pm_hal_PATH = $(starterware_PATH)/$(starterware_pm_hal_RELPATH)
starterware_pm_hal_PLATFORM_DEPENDENCY = yes
export starterware_pm_hal_PLATFORM_DEPENDENCY
starterware_pm_hal_PKG_LIST = starterware_pm_hal
starterware_pm_hal_INCLUDE = $(starterware_PATH)/include/$(starterware_pm_hal_RELPATH) $(starterware_pm_hal_PATH) $(starterware_PATH)/include/pm

starterware_pm_hal_arp32_RELPATH = pm/pmhal
starterware_pm_hal_arp32_PATH = $(starterware_PATH)/$(starterware_pm_hal_arp32_RELPATH)
starterware_pm_hal_arp32_PLATFORM_DEPENDENCY = yes
export starterware_pm_hal_arp32_PLATFORM_DEPENDENCY
starterware_pm_hal_arp32_PKG_LIST = starterware_pm_hal
starterware_pm_hal_arp32_INCLUDE = $(starterware_PATH)/include/$(starterware_pm_hal_arp32_RELPATH) $(starterware_pm_hal_arp32_PATH) $(starterware_PATH)/include/pm

starterware_pm_lib_RELPATH = pm/pmlib
starterware_pm_lib_PATH = $(starterware_PATH)/$(starterware_pm_lib_RELPATH)
starterware_pm_lib_PLATFORM_DEPENDENCY = yes
export starterware_pm_lib_PLATFORM_DEPENDENCY
starterware_pm_lib_PKG_LIST = starterware_pm_lib
starterware_pm_lib_INCLUDE = $(starterware_PATH)/include/$(starterware_pm_lib_RELPATH) $(starterware_pm_lib_PATH) $(starterware_PATH)/include/pm $(starterware_pm_lib_PATH)/$(SOCFAMILY) $(starterware_pm_lib_PATH)

starterware_pm_lib_arp32_RELPATH = pm/pmlib
starterware_pm_lib_arp32_PATH = $(starterware_PATH)/$(starterware_pm_lib_arp32_RELPATH)
starterware_pm_lib_arp32_PLATFORM_DEPENDENCY = yes
export starterware_pm_lib_arp32_PLATFORM_DEPENDENCY
starterware_pm_lib_arp32_PKG_LIST = starterware_pm_lib
starterware_pm_lib_arp32_INCLUDE = $(starterware_PATH)/include/$(starterware_pm_lib_arp32_RELPATH) $(starterware_pm_lib_arp32_PATH) $(starterware_PATH)/include/pm $(starterware_pm_lib_arp32_PATH)/$(SOCFAMILY) $(starterware_pm_lib_arp32_PATH)

####################################
# End of PM Components
####################################

############################
# device starterware utils
# List of components included under starterware utils
# The components included here are built and will be part of starterware utils
# List below all components as examples values
############################
sys_config_RELPATH = system_config
sys_config_PATH = $(starterware_PATH)/$(sys_config_RELPATH)
sys_config_PLATFORM_DEPENDENCY = yes
export sys_config_PLATFORM_DEPENDENCY
sys_config_INCLUDE = $(sys_config_PATH)/$(SOCFAMILY)_common $(sys_config_PATH)/$(ARCH)/$(SOCFAMILY)
sys_config_PKG_LIST = sys_config

############################
# device starterware utils
# List of components included under starterware utils
# The components included here are built and will be part of starterware utils
# List below all components as exaples values
############################
utils_platform_RELPATH = platform
utils_platform_PATH = $(starterware_PATH)/$(utils_platform_RELPATH)
utils_platform_PLATFORM_DEPENDENCY = yes
export utils_platform_PLATFORM_DEPENDENCY
utils_platform_INCLUDE = $(utils_platform_PATH)/$(SOCFAMILY) $(utils_platform_PATH)
utils_platform_PKG_LIST = utils_platform

starterware_boards_RELPATH = boards
starterware_boards_PATH = $(starterware_PATH)/$(starterware_boards_RELPATH)
starterware_boards_PLATFORM_DEPENDENCY = yes
export starterware_boards_PLATFORM_DEPENDENCY
starterware_boards_INCLUDE = $(starterware_boards_PATH)
starterware_boards_PKG_LIST = starterware_boards

starterware_devices_RELPATH = devices
starterware_devices_PATH = $(starterware_PATH)/$(starterware_devices_RELPATH)
starterware_devices_PLATFORM_DEPENDENCY = yes
export starterware_devices_PLATFORM_DEPENDENCY
starterware_devices_INCLUDE = $(starterware_devices_PATH)
starterware_devices_PKG_LIST = starterware_devices

############################
# device starterware lld i2c_master
# List of components included under starterware hal
# The component included here is built and will be part of starterware lld i2c_master library
############################
starterware_vpslib_RELPATH = vpslib
starterware_vpslib_PATH = $(starterware_PATH)/$(starterware_vpslib_RELPATH)
starterware_vpslib_PLATFORM_DEPENDENCY = yes
export starterware_vpslib_PLATFORM_DEPENDENCY
starterware_vpslib_PKG_LIST = starterware_vpslib
starterware_vpslib_INCLUDE = $(starterware_vpslib_PATH)

starterware_osal_RELPATH = utils/osal
starterware_osal_PATH = $(starterware_PATH)/$(starterware_osal_RELPATH)
starterware_osal_PLATFORM_DEPENDENCY = yes
export starterware_osal_PLATFORM_DEPENDENCY
starterware_osal_PKG_LIST = starterware_osal
starterware_osal_INCLUDE = $(starterware_osal_PATH)

starterware_common_RELPATH = utils/common
starterware_common_PATH = $(starterware_PATH)/$(starterware_common_RELPATH)
starterware_common_PLATFORM_DEPENDENCY = yes
export starterware_common_PLATFORM_DEPENDENCY
starterware_common_PKG_LIST = starterware_common
starterware_common_INCLUDE = $(starterware_common_PATH)

i2c_lib_RELPATH = i2clib
i2c_lib_PATH = $(starterware_PATH)/$(i2c_lib_RELPATH)
i2c_lib_PLATFORM_DEPENDENCY = yes
export i2c_lib_PLATFORM_DEPENDENCY
i2c_lib_PKG_LIST = i2c_lib
i2c_lib_INCLUDE = $(i2c_lib_PATH)

safety_lib_RELPATH = safetylib
safety_lib_PATH = $(starterware_PATH)/$(safety_lib_RELPATH)
safety_lib_PLATFORM_DEPENDENCY = yes
export safety_lib_PLATFORM_DEPENDENCY
safety_lib_PKG_LIST = safety_lib
safety_lib_INCLUDE = $(safety_lib_PATH) $(starterware_PATH)/include/$(safety_lib_RELPATH)

uartConsole_RELPATH = utils/uart_console
uartConsole_PATH = $(starterware_PATH)/$(uartConsole_RELPATH)
uartConsole_PLATFORM_DEPENDENCY = yes
export uartConsole_PLATFORM_DEPENDENCY
uartConsole_PKG_LIST = uartConsole
uartConsole_INCLUDE = $(uartConsole_PATH)

qspi_flashlib_RELPATH = qspilib/qspi_flash
qspi_flashlib_PATH = $(starterware_PATH)/$(qspi_flashlib_RELPATH)
qspi_flashlib_PLATFORM_DEPENDENCY = yes
export qspi_flashlib_PLATFORM_DEPENDENCY
qspi_flashlib_PKG_LIST = qspi_flashlib
qspi_flashlib_INCLUDE = $(qspi_flashlib_PATH)

norflash_lib_RELPATH = norflashlib
norflash_lib_PATH = $(starterware_PATH)/$(norflash_lib_RELPATH)
norflash_lib_PLATFORM_DEPENDENCY = yes
export norflash_lib_PLATFORM_DEPENDENCY
norflash_lib_PKG_LIST = norflash_lib
norflash_lib_INCLUDE = $(norflash_lib_PATH)/inc

fat_lib_RELPATH = fatlib
fat_lib_PATH = $(starterware_PATH)/$(fat_lib_RELPATH)
fat_lib_PLATFORM_DEPENDENCY = yes
export fat_lib_PLATFORM_DEPENDENCY
fat_lib_PKG_LIST = fat_lib
fat_lib_INCLUDE = $(fat_lib_PATH)

fat_lib_edma_RELPATH = fatlib/fatlib_edma
fat_lib_edma_PATH = $(starterware_PATH)/$(fat_lib_edma_RELPATH)
fat_lib_edma_PLATFORM_DEPENDENCY = yes
export fat_lib_edma_PLATFORM_DEPENDENCY
fat_lib_edma_PKG_LIST = fat_lib_edma
fat_lib_edma_INCLUDE = $(fat_lib_edma_PATH)

sbl_lib_RELPATH = bootloader/sbl_lib
sbl_lib_PATH = $(starterware_PATH)/$(sbl_lib_RELPATH)
sbl_lib_PLATFORM_DEPENDENCY = yes
export sbl_lib_PLATFORM_DEPENDENCY
sbl_lib_PKG_LIST = sbl_lib
sbl_lib_INCLUDE = $(sbl_lib_PATH)

sbl_utils_RELPATH = bootloader/sbl_utils
sbl_utils_PATH = $(starterware_PATH)/$(sbl_utils_RELPATH)
sbl_utils_PLATFORM_DEPENDENCY = yes
export sbl_utils_PLATFORM_DEPENDENCY
sbl_utils_PKG_LIST = sbl_utils
sbl_utils_INCLUDE = $(sbl_utils_PATH)

qspiFlashWriter_RELPATH = tools/flashtools/qspi_flash_writer
qspiFlashWriter_PATH = $(starterware_PATH)/$(qspiFlashWriter_RELPATH)
qspiFlashWriter_PLATFORM_DEPENDENCY = yes
export qspiFlashWriter_PLATFORM_DEPENDENCY

nor_flash_writer_RELPATH = tools/flashtools/nor_flash_writer
nor_flash_writer_PATH = $(starterware_PATH)/$(nor_flash_writer_RELPATH)
nor_flash_writer_PLATFORM_DEPENDENCY = yes
export nor_flash_writer_PLATFORM_DEPENDENCY

##SBL
sbl_RELPATH = bootloader/sbl/src
sbl_PATH = $(starterware_PATH)/$(sbl_RELPATH)
sbl_PLATFORM_DEPENDENCY = yes
export sbl_PLATFORM_DEPENDENCY

sbl_all_RELPATH = bootloader/sbl/src
sbl_all_PATH = $(starterware_PATH)/$(sbl_all_RELPATH)
sbl_all_PLATFORM_DEPENDENCY = yes
export sbl_all_PLATFORM_DEPENDENCY

sbl_all_opps_RELPATH = bootloader/sbl/src
sbl_all_opps_PATH = $(starterware_PATH)/$(sbl_all_opps_RELPATH)
sbl_all_opps_PLATFORM_DEPENDENCY = yes
export sbl_all_opps_PLATFORM_DEPENDENCY

starterware_examples_utility_RELPATH = examples/utility
starterware_examples_utility_PATH = $(starterware_PATH)/$(starterware_examples_utility_RELPATH)
starterware_examples_utility_PLATFORM_DEPENDENCY = yes
export starterware_examples_utility_PLATFORM_DEPENDENCY
starterware_examples_utility_INCLUDE = $(starterware_examples_utility_PATH)
starterware_examples_utility_PKG_LIST = starterware_examples_utility

############################
#device starterware examples
# List of examples under starterware (hal and lld)
# All the examples mentioned in list are built when we example target is called
# List below all examples for allowed values
# mailbox_app
############################

starterware_EXAMPLES_LIST = mailbox_app timer_app i2c_driver_led_blink_app gpio_output_app qspi_test_app spinlock_test ocmc_app edma_test_app sensor_config_app qspiFlashWriter nor_flash_writer mmu_tlb_twl_app DssApp vipCapt mcaspTransmit_app nor_edma_read nor_read_write mmcsd_fileIO_app mcspi_app uart1_test_app uart3_test_app uart_test uart2_test_app eeprom_app pmic_app temp_sensor_app i2c_test_app gpio_exp_app boot_app ddr_test_app uart_edma_test uart_intr_test i2c_eeprom_app mmu_translation_fault_handle_app gpio_input_interrupt_app mcspiMasterSlave_app wdtimer_app mcaspBurstTransmit_app mcasp_sinetone_app videoLoopback pcie_app_rc_write_loopback pcie_app_ep_write_loopback edid_programmer pm_cpuidle_test_app rti_app dcan_app_loopback pm_junctiontemp_test_app dcan_app_evm_loopback pm_systemconfig_test_app mmc_raw_access pm_clkrate_test_app adc_app crc_app dcc_app esm_app ecc_app l3fw_app mmu_a15_data_validation_app xmc_mpu_app

DssApp_RELPATH = examples/DssApp
DssApp_PATH = $(starterware_PATH)/$(DssApp_RELPATH)
DssApp_PLATFORM_DEPENDENCY = yes
export DssApp_PLATFORM_DEPENDENCY

i2c_test_app_RELPATH = examples/i2c_diag_test/i2c_all
i2c_test_app_PATH = $(starterware_PATH)/$(i2c_test_app_RELPATH)
i2c_test_app_PLATFORM_DEPENDENCY = yes
export i2c_test_app_PLATFORM_DEPENDENCY

gpio_exp_app_RELPATH = examples/i2c_diag_test/i2c_gpio_expander
gpio_exp_app_PATH = $(starterware_PATH)/$(gpio_exp_app_RELPATH)
gpio_exp_app_PLATFORM_DEPENDENCY = yes
export gpio_exp_app_PLATFORM_DEPENDENCY

edid_programmer_RELPATH = examples/i2c_diag_test/edid_programmer
edid_programmer_PATH = $(starterware_PATH)/$(edid_programmer_RELPATH)
edid_programmer_PLATFORM_DEPENDENCY = yes
export edid_programmer_PLATFORM_DEPENDENCY

boot_app_RELPATH = examples/boot
boot_app_PATH = $(starterware_PATH)/$(boot_app_RELPATH)
boot_app_PLATFORM_DEPENDENCY = yes
export boot_app_PLATFORM_DEPENDENCY

temp_sensor_app_RELPATH = examples/i2c_diag_test/i2c_temp_sensor
temp_sensor_app_PATH = $(starterware_PATH)/$(temp_sensor_app_RELPATH)
temp_sensor_app_PLATFORM_DEPENDENCY = yes
export temp_sensor_app_PLATFORM_DEPENDENCY

pmic_app_RELPATH = examples/i2c_diag_test/pmic_i2c
pmic_app_PATH = $(starterware_PATH)/$(pmic_app_RELPATH)
pmic_app_PLATFORM_DEPENDENCY = yes
export pmic_app_PLATFORM_DEPENDENCY

eeprom_app_RELPATH = examples/i2c_diag_test/eeprom_i2c
eeprom_app_PATH = $(starterware_PATH)/$(eeprom_app_RELPATH)
eeprom_app_PLATFORM_DEPENDENCY = yes
export eeprom_app_PLATFORM_DEPENDENCY

vipCapt_RELPATH = examples/vipCapt
vipCapt_PATH = $(starterware_PATH)/$(vipCapt_RELPATH)
vipCapt_PLATFORM_DEPENDENCY = yes
export vipCapt_PLATFORM_DEPENDENCY

videoLoopback_RELPATH = examples/videoLoopback
videoLoopback_PATH = $(starterware_PATH)/$(videoLoopback_RELPATH)
videoLoopback_PLATFORM_DEPENDENCY = yes
export videoLoopback_PLATFORM_DEPENDENCY

mailbox_app_RELPATH = examples/mailbox
mailbox_app_PATH = $(starterware_PATH)/$(mailbox_app_RELPATH)
mailbox_app_PLATFORM_DEPENDENCY = yes
export mailbox_app_PLATFORM_DEPENDENCY

timer_app_RELPATH = examples/timer
timer_app_PATH = $(starterware_PATH)/$(timer_app_RELPATH)
timer_app_PLATFORM_DEPENDENCY = yes
export timer_app_PLATFORM_DEPENDENCY

wdtimer_app_RELPATH = examples/wdtimer
wdtimer_app_PATH = $(starterware_PATH)/$(wdtimer_app_RELPATH)
wdtimer_app_PLATFORM_DEPENDENCY = yes
export wdtimer_app_PLATFORM_DEPENDENCY

nor_edma_read_RELPATH = examples/nor/nor_edma_read
nor_edma_read_PATH = $(starterware_PATH)/$(nor_edma_read_RELPATH)
nor_edma_read_PLATFORM_DEPENDENCY = yes
export nor_edma_read_PLATFORM_DEPENDENCY

nor_read_write_RELPATH = examples/nor/nor_read_write
nor_read_write_PATH = $(starterware_PATH)/$(nor_read_write_RELPATH)
nor_read_write_PLATFORM_DEPENDENCY = yes
export nor_read_write_PLATFORM_DEPENDENCY

sbl_multicore_mbx_RELPATH = examples/sbl_multicore_mbx
sbl_multicore_mbx_PATH = $(starterware_PATH)/$(sbl_multicore_mbx_RELPATH)
sbl_multicore_mbx_PLATFORM_DEPENDENCY = yes
export sbl_multicore_mbx_PLATFORM_DEPENDENCY

sbl_multicore_mbx_1_RELPATH = examples/sbl_multicore_mbx_1
sbl_multicore_mbx_1_PATH = $(starterware_PATH)/$(sbl_multicore_mbx_1_RELPATH)
sbl_multicore_mbx_1_PLATFORM_DEPENDENCY = yes
export sbl_multicore_mbx_1_PLATFORM_DEPENDENCY

sbl_multicore_mbx_2_RELPATH = examples/sbl_multicore_mbx_2
sbl_multicore_mbx_2_PATH = $(starterware_PATH)/$(sbl_multicore_mbx_2_RELPATH)
sbl_multicore_mbx_2_PLATFORM_DEPENDENCY = yes
export sbl_multicore_mbx_2_PLATFORM_DEPENDENCY

sbl_multicore_mbx_3_RELPATH = examples/sbl_multicore_mbx_3
sbl_multicore_mbx_3_PATH = $(starterware_PATH)/$(sbl_multicore_mbx_3_RELPATH)
sbl_multicore_mbx_3_PLATFORM_DEPENDENCY = yes
export sbl_multicore_mbx_3_PLATFORM_DEPENDENCY

norProfiler_RELPATH = examples/profilerApps/norProfiler
norProfiler_PATH = $(starterware_PATH)/$(norProfiler_RELPATH)
norProfiler_PLATFORM_DEPENDENCY = yes
export norProfiler_PLATFORM_DEPENDENCY

sdProfiler_RELPATH = examples/profilerApps/sdProfiler
sdProfiler_PATH = $(starterware_PATH)/$(sdProfiler_RELPATH)
sdProfiler_PLATFORM_DEPENDENCY = yes
export sdProfiler_PLATFORM_DEPENDENCY

qspiProfiler_RELPATH = examples/profilerApps/qspiProfiler
qspiProfiler_PATH = $(starterware_PATH)/$(qspiProfiler_RELPATH)
qspiProfiler_PLATFORM_DEPENDENCY = yes
export qspiProfiler_PLATFORM_DEPENDENCY


i2c_driver_led_blink_app_RELPATH = examples/i2c/i2c_driver_led
i2c_driver_led_blink_app_PATH = $(starterware_PATH)/$(i2c_driver_led_blink_app_RELPATH)
i2c_driver_led_blink_app_PLATFORM_DEPENDENCY = yes
export i2c_driver_led_blink_app_PLATFORM_DEPENDENCY

mmcsd_fileIO_app_RELPATH = examples/sd_fileIO
mmcsd_fileIO_app_PATH = $(starterware_PATH)/$(mmcsd_fileIO_app_RELPATH)
mmcsd_fileIO_app_PLATFORM_DEPENDENCY = yes
export mmcsd_fileIO_app_PLATFORM_DEPENDENCY

mmc_raw_access_RELPATH = examples/mmc_raw_access
mmc_raw_access_PATH = $(starterware_PATH)/$(mmc_raw_access_RELPATH)
mmc_raw_access_PLATFORM_DEPENDENCY = yes
export mmc_raw_access_PLATFORM_DEPENDENCY

sensor_config_app_RELPATH = examples/ov10630_sensor
sensor_config_app_PATH = $(starterware_PATH)/$(sensor_config_app_RELPATH)
sensor_config_app_PLATFORM_DEPENDENCY = yes
export sensor_config_app_PLATFORM_DEPENDENCY

gpio_output_app_RELPATH = examples/gpio/gpio_output
gpio_output_app_PATH = $(starterware_PATH)/$(gpio_output_app_RELPATH)
gpio_output_app_PLATFORM_DEPENDENCY = yes
export gpio_output_app_PLATFORM_DEPENDENCY

gpio_input_interrupt_app_RELPATH = examples/gpio/gpio_input_interrupt
gpio_input_interrupt_app_PATH = $(starterware_PATH)/$(gpio_input_interrupt_app_RELPATH)
gpio_input_interrupt_app_PLATFORM_DEPENDENCY = yes
export gpio_intput_interrupt_app_PLATFORM_DEPENDENCY

qspi_test_app_RELPATH = examples/qspi_test
qspi_test_app_PATH = $(starterware_PATH)/$(qspi_test_app_RELPATH)
qspi_test_app_PLATFORM_DEPENDENCY = yes
export qspi_test_app_PLATFORM_DEPENDENCY

mcspi_app_RELPATH = examples/mcspi
mcspi_app_PATH = $(starterware_PATH)/$(mcspi_app_RELPATH)
mcspi_app_PLATFORM_DEPENDENCY = yes
export mcspi_app_PLATFORM_DEPENDENCY

mcspiMaster_app_RELPATH = examples/mcspiMasterSlave/master
mcspiMaster_app_PATH = $(starterware_PATH)/$(mcspiMaster_app_RELPATH)
mcspiMaster_app_PLATFORM_DEPENDENCY = yes
export mcspiMaster_app_PLATFORM_DEPENDENCY

mcspiSlave_app_RELPATH = examples/mcspiMasterSlave/slave
mcspiSlave_app_PATH = $(starterware_PATH)/$(mcspiSlave_app_RELPATH)
mcspiSlave_app_PLATFORM_DEPENDENCY = yes
export mcspiSlave_app_PLATFORM_DEPENDENCY

mcspiMasterSlave_app_RELPATH = examples/mcspiMasterSlave/masterslave
mcspiMasterSlave_app_PATH = $(starterware_PATH)/$(mcspiMasterSlave_app_RELPATH)
mcspiMasterSlave_app_PLATFORM_DEPENDENCY = yes
export mcspiMasterSlave_app_PLATFORM_DEPENDENCY

spinlock_test_RELPATH = examples/spinlock_test
spinlock_test_PATH = $(starterware_PATH)/$(spinlock_test_RELPATH)
spinlock_test_PLATFORM_DEPENDENCY = yes
export spinlock_test_PLATFORM_DEPENDENCY

ocmc_app_RELPATH = examples/ocmc/ocmc_basic
ocmc_app_PATH = $(starterware_PATH)/$(ocmc_app_RELPATH)
ocmc_app_PLATFORM_DEPENDENCY = yes
export ocmc_app_PLATFORM_DEPENDENCY

uart1_test_app_RELPATH = examples/uart/uart1
uart1_test_app_PATH = $(starterware_PATH)/$(uart1_test_app_RELPATH)
uart1_test_app_PLATFORM_DEPENDENCY = yes
export uart1_test_app_PLATFORM_DEPENDENCY

uart2_test_app_RELPATH = examples/uart/uart2
uart2_test_app_PATH = $(starterware_PATH)/$(uart2_test_app_RELPATH)
uart2_test_app_PLATFORM_DEPENDENCY = yes
export uart2_test_app_PLATFORM_DEPENDENCY

uart3_test_app_RELPATH = examples/uart/uart3
uart3_test_app_PATH = $(starterware_PATH)/$(uart3_test_app_RELPATH)
uart3_test_app_PLATFORM_DEPENDENCY = yes
export uart3_test_app_PLATFORM_DEPENDENCY

uart_edma_test_RELPATH = examples/uart/uart_edma
uart_edma_test_PATH = $(starterware_PATH)/$(uart_edma_test_RELPATH)
uart_edma_test_PLATFORM_DEPENDENCY = yes
export uart_edma_test_PLATFORM_DEPENDENCY

uart_intr_test_RELPATH = examples/uart/uart_intr
uart_intr_test_PATH = $(starterware_PATH)/$(uart_intr_test_RELPATH)
uart_intr_test_PLATFORM_DEPENDENCY = yes
export uart_intr_test_PLATFORM_DEPENDENCY

uart_test_RELPATH = examples/uart/uart_test
uart_test_PATH = $(starterware_PATH)/$(uart_test_RELPATH)
uart_test_PLATFORM_DEPENDENCY = yes
export uart_test_PLATFORM_DEPENDENCY

edma_test_app_RELPATH = examples/edma_test
edma_test_app_PATH = $(starterware_PATH)/$(edma_test_app_RELPATH)
edma_test_app_PLATFORM_DEPENDENCY = yes
export edma_test_app_PLATFORM_DEPENDENCY

ddr_test_app_RELPATH = examples/ddr_stress_test
ddr_test_app_PATH = $(starterware_PATH)/$(ddr_test_app_RELPATH)
ddr_test_app_PLATFORM_DEPENDENCY = yes
export ddr_test_app_PLATFORM_DEPENDENCY

mmu_tlb_twl_app_RELPATH = examples/mmu/tlb_twl
mmu_tlb_twl_app_PATH = $(starterware_PATH)/$(mmu_tlb_twl_app_RELPATH)
mmu_tlb_twl_app_PLATFORM_DEPENDENCY = yes
export mmu_tlb_twl_app_PLATFORM_DEPENDENCY

mmu_translation_fault_handle_app_RELPATH = examples/mmu/translation_fault_handle
mmu_translation_fault_handle_app_PATH = $(starterware_PATH)/$(mmu_translation_fault_handle_app_RELPATH)
mmu_translation_fault_handle_app_PLATFORM_DEPENDENCY = yes
export mmu_translation_fault_handle_app_PLATFORM_DEPENDENCY

mcaspTransmit_app_RELPATH = examples/mcasp/mcasp_transmit
mcaspTransmit_app_PATH = $(starterware_PATH)/$(mcaspTransmit_app_RELPATH)
mcaspTransmit_app_PLATFORM_DEPENDENCY = yes
export mcaspTransmit_app_PLATFORM_DEPENDENCY

mcasp_sinetone_app_RELPATH = examples/mcasp/mcasp_sinetone
mcasp_sinetone_app_PATH = $(starterware_PATH)/$(mcasp_sinetone_app_RELPATH)
mcasp_sinetone_app_PLATFORM_DEPENDENCY = yes
export mcasp_sinetone_app_PLATFORM_DEPENDENCY

mcaspBurstTransmit_app_RELPATH = examples/mcasp/mcasp_bursttransmit
mcaspBurstTransmit_app_PATH = $(starterware_PATH)/$(mcaspBurstTransmit_app_RELPATH)
mcaspBurstTransmit_app_PLATFORM_DEPENDENCY = yes
export mcaspBurstTransmit_app_PLATFORM_DEPENDENCY

i2c_eeprom_app_RELPATH = examples/i2c/i2c_eeprom_app
i2c_eeprom_app_PATH = $(starterware_PATH)/$(i2c_eeprom_app_RELPATH)
i2c_eeprom_app_PLATFORM_DEPENDENCY = yes
export i2c_100kbps_app_PLATFORM_DEPENDENCY

pcie_app_rc_write_loopback_RELPATH = examples/pcie/write_loopback/rc
pcie_app_rc_write_loopback_PATH = $(starterware_PATH)/$(pcie_app_rc_write_loopback_RELPATH)
pcie_app_rc_write_loopback_PLATFORM_DEPENDENCY = yes
export pcie_app_rc_write_loopback_PLATFORM_DEPENDENCY

pcie_app_ep_write_loopback_RELPATH = examples/pcie/write_loopback/ep
pcie_app_ep_write_loopback_PATH = $(starterware_PATH)/$(pcie_app_ep_write_loopback_RELPATH)
pcie_app_ep_write_loopback_PLATFORM_DEPENDENCY = yes
export pcie_app_ep_write_loopback_PLATFORM_DEPENDENCY

mmu_a15_data_validation_app_RELPATH = examples/mmu/a15/
mmu_a15_data_validation_app_PATH = $(starterware_PATH)/$(mmu_a15_data_validation_app_RELPATH)
mmu_a15_data_validation_app_PLATFORM_DEPENDENCY = yes
export mmu_a15_data_validation_app_PLATFORM_DEPENDENCY

pm_cpuidle_test_app_RELPATH = examples/pm/cpuidle
pm_cpuidle_test_app_PATH = $(starterware_PATH)/$(pm_cpuidle_test_app_RELPATH)
pm_cpuidle_test_app_PLATFORM_DEPENDENCY = yes
export pm_cpuidle_test_app_PLATFORM_DEPENDENCY

pm_systemconfig_test_app_RELPATH = examples/pm/systemconfig
pm_systemconfig_test_app_PATH = $(starterware_PATH)/$(pm_systemconfig_test_app_RELPATH)
pm_systemconfig_test_app_PLATFORM_DEPENDENCY = yes
export pm_systemconfig_test_app_PLATFORM_DEPENDENCY

pm_arp32_cpuidle_test_app_RELPATH = examples/pm/arp32_cpuidle
pm_arp32_cpuidle_test_app_PATH = $(starterware_PATH)/$(pm_arp32_cpuidle_test_app_RELPATH)
pm_arp32_cpuidle_test_app_PLATFORM_DEPENDENCY = yes
export pm_arp32_cpuidle_test_app_PLATFORM_DEPENDENCY

rti_app_RELPATH = examples/rti
rti_app_PATH = $(starterware_PATH)/$(rti_app_RELPATH)
rti_app_PLATFORM_DEPENDENCY = yes
export rti_app_PLATFORM_DEPENDENCY

crc_app_RELPATH = examples/crc
crc_app_PATH = $(starterware_PATH)/$(crc_app_RELPATH)
crc_app_PLATFORM_DEPENDENCY = yes
export crc_app_PLATFORM_DEPENDENCY

adc_app_RELPATH = examples/adc_app
adc_app_PATH = $(starterware_PATH)/$(adc_app_RELPATH)
adc_app_PLATFORM_DEPENDENCY = yes
export adc_app_PLATFORM_DEPENDENCY

dcan_app_loopback_RELPATH = examples/dcan/dcanLoopback
dcan_app_loopback_PATH = $(starterware_PATH)/$(dcan_app_loopback_RELPATH)
dcan_app_loopback_PLATFORM_DEPENDENCY = yes
export dcan_app_loopback_PLATFORM_DEPENDENCY

pm_junctiontemp_test_app_RELPATH = examples/pm/junction_temp_sensor
pm_junctiontemp_test_app_PATH = $(starterware_PATH)/$(pm_junctiontemp_test_app_RELPATH)
pm_junctiontemp_test_app_PLATFORM_DEPENDENCY = yes
export pm_junctiontemp_test_app_PLATFORM_DEPENDENCY

dcan_app_evm_loopback_RELPATH = examples/dcan/dcanEvmLoopback
dcan_app_evm_loopback_PATH = $(starterware_PATH)/$(dcan_app_evm_loopback_RELPATH)
dcan_app_evm_loopback_PLATFORM_DEPENDENCY = yes
export dcan_app_evm_loopback_PLATFORM_DEPENDENCY

pm_clkrate_test_app_RELPATH = examples/pm/clkrate_manager
pm_clkrate_test_app_PATH = $(starterware_PATH)/$(pm_clkrate_test_app_RELPATH)
pm_clkrate_test_app_PLATFORM_DEPENDENCY = yes
export pm_clkrate_test_app_PLATFORM_DEPENDENCY

xmc_mpu_app_RELPATH = examples/xmc_mpu_app
xmc_mpu_app_PATH = $(starterware_PATH)/$(xmc_mpu_app_RELPATH)
xmc_mpu_app_PLATFORM_DEPENDENCY = yes
export xmc_mpu_app_PLATFORM_DEPENDENCY

dcc_app_RELPATH = examples/dcc_app
dcc_app_PATH = $(starterware_PATH)/$(dcc_app_RELPATH)
dcc_app_PLATFORM_DEPENDENCY = yes
export dcc_app_PLATFORM_DEPENDENCY

esm_app_RELPATH = examples/esm_app
esm_app_PATH = $(starterware_PATH)/$(esm_app_RELPATH)
esm_app_PLATFORM_DEPENDENCY = yes
export esm_app_PLATFORM_DEPENDENCY

l3fw_app_RELPATH = examples/l3fw_app
l3fw_app_PATH = $(starterware_PATH)/$(l3fw_app_RELPATH)
l3fw_app_PLATFORM_DEPENDENCY = yes
export l3fw_app_PLATFORM_DEPENDENCY

ecc_app_RELPATH = examples/ecc_app
ecc_app_PATH = $(starterware_PATH)/$(ecc_app_RELPATH)
ecc_app_test_PLATFORM_DEPENDENCY = yes
export ecc_app_PLATFORM_DEPENDENCY

# Component specific CFLAGS
CFLAGS_COMP_COMMON +=

ifeq ($(CORE),)
else
# CFLAGS based on example/demo/application properties
ifeq ($(PLATFORM),tda2xx)
  STARTERWARE_CFLAGS += -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),dra7xx)
  STARTERWARE_CFLAGS += -DDRA7XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda2ex)
  STARTERWARE_CFLAGS += -DTDA2EX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda2xx-evm)
  STARTERWARE_CFLAGS += -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda2xx-mc)
  STARTERWARE_CFLAGS += -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI -DTDA2XX_MC_BUILD
endif
ifeq ($(PLATFORM),dra7xx-evm)
  STARTERWARE_CFLAGS += -DDRA7XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda2ex-evm)
  STARTERWARE_CFLAGS += -DTDA2EX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),omap5430-evm)
  STARTERWARE_CFLAGS += -DOMAP5430_BUILD -DOMAP5X_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda2xx-virtio)
  STARTERWARE_CFLAGS += -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_VIRTIO
endif
ifeq ($(PLATFORM),tda2xx-sim)
  STARTERWARE_CFLAGS += -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_SIM
endif
ifeq ($(PLATFORM),tda2xx-zebu)
  STARTERWARE_CFLAGS += -DTDA2XX_BUILD -DTDA2XX_FAMILY_BUILD -DPLATFORM_ZEBU
endif
ifeq ($(PLATFORM),ti814x)
  STARTERWARE_CFLAGS += -DTI814X_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),ti814x-evm)
  STARTERWARE_CFLAGS += -DTI814X_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),ti8149-evm)
  STARTERWARE_CFLAGS += -DTI8149_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),ti811x-evm)
  STARTERWARE_CFLAGS += -DTI811X_BUILD -DTI814X_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda3xx-sim)
  STARTERWARE_CFLAGS += -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_SIM
endif
ifeq ($(PLATFORM),tda3xx-zebu)
  STARTERWARE_CFLAGS += -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_ZEBU
endif
ifeq ($(PLATFORM),tda3xx-evm)
  STARTERWARE_CFLAGS += -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif
ifeq ($(PLATFORM),tda3xx)
  STARTERWARE_CFLAGS += -DTDA3XX_BUILD -DTDA3XX_FAMILY_BUILD -DPLATFORM_EVM_SI
endif

ifeq ($(CORE),m3vpss)
  STARTERWARE_CFLAGS += -DBUILD_M3 -DBUILD_M3VPSS
endif

ifeq ($(CORE),m3video)
  STARTERWARE_CFLAGS += -DBUILD_M3 -DBUILD_M3VIDEO
endif

ifeq ($(CORE),m4)
  STARTERWARE_CFLAGS += -DBUILD_M4
endif

ifeq ($(CORE),m4vpss)
  STARTERWARE_CFLAGS += -DBUILD_M4 -DBUILD_M4VPSS
endif

ifeq ($(CORE),m4video)
  STARTERWARE_CFLAGS += -DBUILD_M4 -DBUILD_M4VIDEO
endif

ifeq ($(CORE),a8host)
  STARTERWARE_CFLAGS += -DBUILD_A8
endif

ifeq ($(CORE),a15host)
  STARTERWARE_CFLAGS += -DBUILD_A15
endif

ifeq ($(CORE),a15_0)
  STARTERWARE_CFLAGS += -DBUILD_A15
endif

ifeq ($(CORE),c674x)
  STARTERWARE_CFLAGS += -DBUILD_DSP
endif

ifeq ($(CORE),c66x)
  STARTERWARE_CFLAGS += -DBUILD_DSP
endif

ifeq ($(CORE),arp32_1)
  STARTERWARE_CFLAGS += -DBUILD_EVE
endif

ifeq ($(CORE),arp32_2)
  STARTERWARE_CFLAGS += -DBUILD_EVE
endif

ifeq ($(CORE),arp32_3)
  STARTERWARE_CFLAGS += -DBUILD_EVE
endif

ifeq ($(CORE),arp32_4)
  STARTERWARE_CFLAGS += -DBUILD_EVE
endif
endif

#Added CFLAG for gcc tool chain, other toolchain cflags can be added here if required

ifeq ($(TOOLCHAIN_$(ISA)),gcc)
STARTERWARE_CFLAGS += -DBUILD_GCC
endif

#Enable trace only for non-Klockwork build and for all profiles
ifeq ($(KW_BUILD),no)
  STARTERWARE_CFLAGS += -DTRACE_ENABLE
endif

# Enable standard asserts for klockwork build
ifeq ($(KW_BUILD),yes)
  STARTERWARE_CFLAGS += -DUSE_STD_ASSERT -DASSERT_ENABLE -DTRACE_ENABLE
endif

# Set default packaging for differenet moduels, select none
PACKAGE_VIP = no
PACKAGE_VPE = no
PACKAGE_DSS = no
PACKAGE_ISS_DEF = no
PACKAGE_SIMCOP = no
PACKAGE_ISS = no

#Use PACKAGE_SELECT input
ifeq ($(PACKAGE_SELECT),all)
  STARTERWARE_CFLAGS += -DVPS_VIP_BUILD
  PACKAGE_VIP = yes
  STARTERWARE_CFLAGS += -DVPS_VPE_BUILD
  PACKAGE_VPE = yes
  ifneq ($(SOCFAMILY),ti814x)
    STARTERWARE_CFLAGS += -DVPS_DSS_BUILD
    PACKAGE_DSS = yes
  endif
  ifeq ($(SOCFAMILY),tda3xx)
    STARTERWARE_CFLAGS += -DVPS_ISS_ISP_DEF
    PACKAGE_ISS_DEF = yes
    STARTERWARE_CFLAGS += -DVPS_ISS_BUILD
    PACKAGE_ISS = yes
    STARTERWARE_CFLAGS += -DVPS_SIMCOP_BUILD
    PACKAGE_SIMCOP = yes
  endif
endif

ifeq ($(PACKAGE_SELECT),vps-hal-only)
  STARTERWARE_CFLAGS += -DVPS_VIP_BUILD
  PACKAGE_VIP = yes
  STARTERWARE_CFLAGS += -DVPS_VPE_BUILD
  PACKAGE_VPE = yes
  STARTERWARE_CFLAGS += -DVPS_DSS_BUILD
  PACKAGE_DSS = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vip-only)
  STARTERWARE_CFLAGS += -DVPS_VIP_BUILD
  PACKAGE_VIP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vpe-only)
  STARTERWARE_CFLAGS += -DVPS_VPE_BUILD
  PACKAGE_VPE = yes
endif
ifeq ($(PACKAGE_SELECT),vps-dss-only)
  STARTERWARE_CFLAGS += -DVPS_DSS_BUILD
  PACKAGE_DSS = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vip-dss)
  STARTERWARE_CFLAGS += -DVPS_VIP_BUILD
  PACKAGE_VIP = yes
  STARTERWARE_CFLAGS += -DVPS_DSS_BUILD
  PACKAGE_DSS = yes
endif
ifeq ($(PACKAGE_SELECT),vps-vip-vpe)
  STARTERWARE_CFLAGS += -DVPS_VIP_BUILD
  PACKAGE_VIP = yes
  STARTERWARE_CFLAGS += -DVPS_VPE_BUILD
  PACKAGE_VPE = yes
endif

ifeq ($(SOCFAMILY),tda3xx)
ifeq ($(PACKAGE_SELECT),vps-iss-only)
  STARTERWARE_CFLAGS += -DVPS_ISS_ISP_DEF
  PACKAGE_ISS_DEF = yes
  STARTERWARE_CFLAGS += -DVPS_ISS_BUILD
  PACKAGE_ISS = yes
  STARTERWARE_CFLAGS += -DVPS_SIMCOP_BUILD
  PACKAGE_SIMCOP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-simcop-only)
  STARTERWARE_CFLAGS += -DVPS_ISS_ISP_DEF
  PACKAGE_ISS_DEF = yes
  STARTERWARE_CFLAGS += -DVPS_SIMCOP_BUILD
  PACKAGE_SIMCOP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-isp-only)
  STARTERWARE_CFLAGS += -DVPS_ISS_ISP_DEF
  PACKAGE_ISS_DEF = yes
  STARTERWARE_CFLAGS += -DVPS_ISS_BUILD
  PACKAGE_SIMCOP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-hal-only)
  STARTERWARE_CFLAGS += -DVPS_ISS_ISP_DEF
  PACKAGE_ISS_DEF = yes
  STARTERWARE_CFLAGS += -DVPS_ISS_BUILD
  PACKAGE_ISS = yes
  STARTERWARE_CFLAGS += -DVPS_SIMCOP_BUILD
  PACKAGE_SIMCOP = yes
endif
ifeq ($(PACKAGE_SELECT),vps-iss-dss-only)
  STARTERWARE_CFLAGS += -DVPS_ISS_ISP_DEF
  PACKAGE_ISS_DEF = yes
  STARTERWARE_CFLAGS += -DVPS_ISS_BUILD
  PACKAGE_ISS = yes
  STARTERWARE_CFLAGS += -DVPS_SIMCOP_BUILD
  PACKAGE_SIMCOP = yes
  STARTERWARE_CFLAGS += -DVPS_DSS_BUILD
  PACKAGE_DSS = yes
endif
endif

ifneq ($(SOCFAMILY),$(filter $(SOCFAMILY), tda2xx tda3xx ti814x ti8149 ti811x))
  PACKAGE_VIP = no
  STARTERWARE_CFLAGS += -UVPS_VIP_BUILD
endif

ifneq ($(SOCFAMILY),$(filter $(SOCFAMILY), tda2xx ti814x ti8149 ti811x))
  PACKAGE_VPE = no
  STARTERWARE_CFLAGS += -UVPS_VPE_BUILD
endif

ifneq ($(SOCFAMILY),$(filter $(SOCFAMILY), tda2xx tda3xx omap5430))
  PACKAGE_DSS = no
  STARTERWARE_CFLAGS += -UVPS_DSS_BUILD
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
  STARTERWARE_CFLAGS += -DVPS_VIP1_BUILD
endif
ifeq ($(PACKAGE_VIP2_BUILD),yes)
  STARTERWARE_CFLAGS += -DVPS_VIP2_BUILD
endif
ifeq ($(PACKAGE_VIP3_BUILD),yes)
  STARTERWARE_CFLAGS += -DVPS_VIP3_BUILD
endif

ifeq ($(PROFILE_$(CORE)),debug)
  STARTERWARE_CFLAGS += -DDEBUG_BUILD
# Enable asserts for debug build
  STARTERWARE_CFLAGS += -DASSERT_ENABLE
endif

ifeq ($(PROFILE_$(CORE)),release)
  STARTERWARE_CFLAGS += -DRELEASE_BUILD
# Enable asserts for release build
  STARTERWARE_CFLAGS += -DASSERT_ENABLE
endif

ifeq ($(PROFILE_$(CORE)),prod_release)
  STARTERWARE_CFLAGS += -DPROD_RELEASE_BUILD
# Disable asserts for production release
#  STARTERWARE_CFLAGS += -DASSERT_ENABLE
endif

# Enable custom frame buffer memory size
ifneq ($(CUSTOM_MEM_FRAME_HEAP_SIZE), )
  STARTERWARE_CFLAGS += -DCUSTOM_MEM_FRAME_HEAP_SIZE=$(CUSTOM_MEM_FRAME_HEAP_SIZE)
endif

ifeq ($(SOCFAMILY),tda3xx)
ifeq ($(BOOTMODE),qspi)
    STARTERWARE_CFLAGS += -DBOOTMODE_QSPI
endif
ifeq ($(BOOTMODE),qspi_sd)
    STARTERWARE_CFLAGS += -DBOOTMODE_QSPI_SD
endif
ifeq ($(BOOTMODE),nor)
    STARTERWARE_CFLAGS += -DBOOTMODE_NOR
endif
endif

#default to default SBL config
ifeq ($(SBL_CONFIG), )
    SBL_CONFIG=default
endif
ifeq ($(SBL_CONFIG), default)
    STARTERWARE_CFLAGS += -DSBL_CONFIG_DEFAULT
endif
ifeq ($(SBL_CONFIG), custom1)
    STARTERWARE_CFLAGS += -DSBL_CONFIG_CUSTOM1
endif
ifeq ($(SBL_CONFIG), disable_safety)
    STARTERWARE_CFLAGS += -DSBL_CONFIG_DISABLE_SAFETY_FEATURES
endif

ifeq ($(SBL_OPT_MODE), )
    SBL_OPT_MODE=low
endif

ifeq ($(TRACE_MODE), )
    TRACE_MODE=low
endif

# SBL optimization level
ifeq ($(SBL_OPT_MODE), low)
    STARTERWARE_CFLAGS += -DSBL_OPT_LEVEL=0
    TRACE_MODE=medium
else ifeq ($(SBL_OPT_MODE), medium)
    STARTERWARE_CFLAGS += -DSBL_OPT_LEVEL=1
    STARTERWARE_CFLAGS+= -DPM_OPTIMIZE
    TRACE_MODE=low
else ifeq ($(SBL_OPT_MODE), high)
    STARTERWARE_CFLAGS += -DSBL_OPT_LEVEL=2
    STARTERWARE_CFLAGS+= -DPM_OPTIMIZE
    TRACE_MODE=imp_info
else
    STARTERWARE_CFLAGS += -DSBL_OPT_LEVEL=0
endif

ifeq ($(SBL_BUILD_MODE), )
    SBL_BUILD_MODE=prod
endif

ifeq ($(SBL_BUILD_MODE), prod)
    STARTERWARE_CFLAGS+= -DSBL_PROD_BUILD
endif

ifeq ($(SBL_BUILD_MODE), dev)
    STARTERWARE_CFLAGS+= -DSBL_DEV_BUILD
endif

# Trace mode Mapping:
# low:    SBLLIB_TRACE_LEVEL_INFO
# medium: SBLLIB_TRACE_LEVEL_INFO1
# high:   SBLLIB_TRACE_LEVEL_DEBUG
# For prints Trace levels medium and high are considered only when optimization
# level is low in current implementation.
ifeq ($(TRACE_MODE), high)
    STARTERWARE_CFLAGS += -DTRACE_LEVEL=4
else ifeq ($(TRACE_MODE), medium)
    STARTERWARE_CFLAGS += -DTRACE_LEVEL=3
else ifeq ($(TRACE_MODE), low)
    STARTERWARE_CFLAGS += -DTRACE_LEVEL=2
else
    STARTERWARE_CFLAGS += -DTRACE_LEVEL=1
endif

ifeq ($(INCLUDE_WDR_LDC), )
  INCLUDE_WDR_LDC := no
endif

export STARTERWARE_LIBS
export STARTERWARE_EXAMPLE_LIBS
export STARTERWARE_CFLAGS
export PACKAGE_VIP
export PACKAGE_VPE
export PACKAGE_DSS
export PACKAGE_ISS_DEF
export PACKAGE_SIMCOP
export PACKAGE_ISS
export PACKAGE_VIP1_BUILD
export PACKAGE_VIP2_BUILD
export PACKAGE_VIP3_BUILD
export INCLUDE_WDR_LDC
export SBL_BUILD_MODE
export BOOTMODE

# Nothing beyond this point
