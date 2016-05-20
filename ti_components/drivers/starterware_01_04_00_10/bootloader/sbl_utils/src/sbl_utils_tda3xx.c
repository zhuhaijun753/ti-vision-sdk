/**
 *  \file     sbl_utils_tda3xx.c
 *
 *  \brief    This file contains the SBL Utility layer valid for tda3xx platform
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include "common/stw_types.h"
#include "hw_types.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "edma.h"
#include "crc.h"
#include "ammu.h"
#include "unicache.h"
#include "hw_ipu_unicache_mmu.h"
#include "hw_ctrl_core_sec.h"
#include "sbl_lib/sbl_lib.h"
#include "sbl_lib_config.h"
#include "sbl_utils/sbl_utils_common.h"
#include "sbl_utils/sbl_utils_tda3xx.h"
#include "sbl_utils_tda3xx_ammu_config.h"
#include "pmhal_prcm.h"
#include "pm/pm_utils.h"
#include "emif.h"
#include "pmhal_cm.h"
#include "pmhal_mm.h"
#include "pmhal_vm.h"
#include "pmhal_pdm.h"
#include "pmhal_pmic.h"
#include "pmhal_pmicComm.h"
#include "pmhal_tps65917.h"
#include "pmhal_l8731.h"
#include "hsi2c.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Macro indicating IPU1 Core0 is Up */
#define SBL_LIB_RBL_MASTER_CORE_STATUS                 ((uint32_t) 0x10U)

#define SBL_UTILS_NUM_ENTRIES_POWER_DOMAIN_TABLE \
    (sizeof (gPowerDomainTable) / sizeof (gPowerDomainTable[0]))

#define SBL_UTILS_NUM_ENTRIES_POWER_DOMAIN_STATE_TABLE \
    (sizeof (gPowerDomainStateTable) / sizeof (gPowerDomainStateTable[0]))

#define SBL_UTILS_NUM_ENTRIES_CLOCK_DOMAIN_TABLE \
    (sizeof (gClockDomainTable) / sizeof (gClockDomainTable[0]))

#define SBL_UTILS_NUM_ENTRIES_CLOCK_DOMAIN_STATE_TABLE \
    (sizeof (gClockDomainStateTable) / sizeof (gClockDomainStateTable[0]))

#define SBL_UTILS_NUM_ENTRIES_MODULE_TABLE \
    (sizeof (gModuleTable) / sizeof (gModuleTable[0]))

#define SBL_UTILS_NUM_ENTRIES_MODULE_ENABLE_TABLE \
    (sizeof (gModuleEnableTable) / sizeof (gModuleEnableTable[0]))

/** I2C System Clock - PER_96M_CLK:  96 MHz */
#define SBL_UTILS_I2C_SYSTEM_CLOCK       (96000000U)

/** I2C Internal Clock -  9.6 MHz , Fast Mode of Communication is
 *  is used here. A pre-scaler of 23 would be calculated here. Refer
 *  TRM for details on the different I2C modes.
 */
#define SBL_UTILS_I2C_INTERNAL_CLOCK     (9600000U)

/** I2C Output Clock -  400 KHz, This complies with the Fast Mode
 *  of the I2C operation of 100 Kbps.
 */
#define SBL_UTILS_I2C_OUTPUT_CLOCK       (400000U)

/**
 * When checking for I2C IRQSTATUS setting this count is used to
 * repeatedly check the status. This number is empirically derived.
 */
#define SBL_UTILS_I2C_TIMEOUT_COUNT      (4000U)

/** Write Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_WRITE              (1U)

/** Read Flag used when checking for the transfer status. */
#define SBL_UTILS_I2C_READ               (2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function sends the event instruction i.e. SEV.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblUtilsSendEvent(void);

/**
 * \brief   This function performs the I2C initialization to talk to PMIC.
 *
 * \param   None.
 *
 * \retval  None.
 */
static int32_t SblUtilsI2cInit(void);

/**
 * \brief   This function reads a byte from the PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be read.
 * \param   regValue    Pointer to the location where the read value will be
 *                      placed.
 * \param   numRegs     Number of registers to be read.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                   const uint8_t *regAddr,
                                   uint8_t *regValue,
                                   uint32_t numRegs);

/**
 * \brief   This function writes a byte of data to the register of PMIC via I2C
 *
 * \param   i2cNum   Instance Id of the I2C. 1 - for I2C1, 2 - for I2C2
 * \param   i2cDevAddr  I2C Slave address for the PMIC
 * \param   regAddr     Pointer to the register address which is to be written.
 * \param   regValue    Pointer to the location where the write value will be
 *                      placed.
 * \param   numRegs     Number of registers to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                    const uint8_t *regAddr,
                                    const uint8_t *regValue,
                                    uint32_t numRegs);
/**
 * \brief   Poll for Bus Busy and return when bus is not busy or timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWaitForBB(uint32_t i2cNum);

/**
 * \brief  Poll for the given flags and return when any of the flags is set or
 *         timed out.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   flags       Flag to be waited for.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags);

/**
 * \brief  Write the given number of bytes to the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   data        Data to be written.
 * \param   count       Number of Bytes to be written.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cWrite(uint32_t i2cNum,
                                uint8_t slaveAddr, const uint8_t data[],
                                uint8_t count);

/**
 * \brief  Read one byte from the given slave address.
 *
 * \param   i2cNum      The I2C number used on the board to connect to the
 *                      desired PMIC.
 * \param   slaveAddr   Address to which the data should be written.
 * \param   value       Data to be read is returned.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cRead(uint32_t i2cNum,
                               uint8_t  slaveAddr,
                               uint8_t *value);

/**
 * \brief Check the status of the transfer and handle the error conditions.
 *
 * \param   i2cNum  The I2C number used on the board to connect to the
 *                  desired PMIC.
 * \param   xfr     Transfer Type. Can be any one of SBL_UTILS_I2C_WRITE or
 *                  SBL_UTILS_I2C_READ.
 *
 * \retval  status      Pass or fail value of the operations. STW_SOK - If Pass
 *                      STW_EFAIL - If Fail
 */
static int32_t SblUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr);

/**
 * \brief   This function pre-fills the ECC memory with the known pattern
 *          present at source address.
 *
 * \param   eccMemStartAddr Start address of memory for which ECC is enabled
 * \param   srcBuffAddr     Address of the source buffer
 * \param   memSize         Size of the memory
 *
 * \return  None
 *
 * \note    This API does not initialize and de-initialize the EDMA. This
 *          should be taken care by caller. Also the srcBuffer size should be
 *          equal to EDMA ACount value used in this API's implementation which
 *           is 128 bytes currently.
 */
static void SBLUtilsPreFillECCMemory(void       *eccMemStartAddr,
                                     const void *srcBuffAddr,
                                     uint32_t    memSize);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * Table containing Power Domain enable Configuration which should be configured
 * for different Power Domains
 */
static const sblutilsPowerDomainStateConfig_t gPowerDomainStateTable[] = {
    {PMHAL_PRCM_PD_CAM,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "CAM"      },
    {PMHAL_PRCM_PD_CORE,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "CORE"     },
    {PMHAL_PRCM_PD_CUSTEFUSE, PMHAL_PRCM_PD_STATE_ON_ACTIVE, "CUSTEFUSE"},
    {PMHAL_PRCM_PD_DSP1,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "DSP1"     },
    {PMHAL_PRCM_PD_DSP2,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "DSP2"     },
    {PMHAL_PRCM_PD_DSS,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "DSS"      },
    {PMHAL_PRCM_PD_EVE1,      PMHAL_PRCM_PD_STATE_ON_ACTIVE, "EVE1"     },
    {PMHAL_PRCM_PD_IPU,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "IPU"      },
    {PMHAL_PRCM_PD_L3INIT,    PMHAL_PRCM_PD_STATE_ON_ACTIVE, "L3INIT"   },
    {PMHAL_PRCM_PD_L4PER,     PMHAL_PRCM_PD_STATE_ON_ACTIVE, "L4PER"    },
    {PMHAL_PRCM_PD_ISS,       PMHAL_PRCM_PD_STATE_ON_ACTIVE, "ISS"      },
};

/*
 * Table containing Clock Domain State Configuration which should be
 * configured for different clock domains
 * L4PER1 is already enabled during AVS voltage configuration in function
 * SBLUtilsConfigAllVoltageRails
 * IPU1 is already enabled by RBL
 * EMU is required to be in SW_WKUP to ensure DSP powers down correctly.
 */
static const sblutilsClockDomainStateConfig_t gClockDomainStateTable[] = {
    {PMHAL_PRCM_CD_L4CFG,     PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP,
     "L4CFG"},
    {PMHAL_PRCM_CD_CRC,       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "CRC"},
    {PMHAL_PRCM_CD_L3MAIN1,   PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
     "L3MAIN1"},
    {PMHAL_PRCM_CD_L3INSTR,   PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
     "L3INSTR"},
    {PMHAL_PRCM_CD_EMIF,      PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "EMIF"},
    {PMHAL_PRCM_CD_COREAON,   PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "COREAON"},
    {PMHAL_PRCM_CD_IPU,       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "IPU"},
    {PMHAL_PRCM_CD_CUSTEFUSE, PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "CUSTEFUSE"},
    {PMHAL_PRCM_CD_CAM,       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "CAM"},
    {PMHAL_PRCM_CD_DSS,       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "DSS"},
    {PMHAL_PRCM_CD_L3INIT,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "L3INIT"},
    {PMHAL_PRCM_CD_GMAC,      PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "GMAC"},
    {PMHAL_PRCM_CD_L4PER2,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "L4PER2"},
    {PMHAL_PRCM_CD_L4PER3,    PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "L4PER3"},
    {PMHAL_PRCM_CD_ISS,       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "ISS"},
    {PMHAL_PRCM_CD_WKUPAON,   PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "WKUPAON"},
    {PMHAL_PRCM_CD_EMU,       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "EMU"},
    {PMHAL_PRCM_CD_DSP1,      PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "DSP1"},
    {PMHAL_PRCM_CD_DSP2,      PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "DSP2"},
    {PMHAL_PRCM_CD_EVE1,      PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
     "EVE1"}
};

/*
 * Table containing Module enable Configuration which should be configured
 * for different modules
 * I2C1 is already enabled during AVS voltage configuration in function
 * SBLUtilsConfigAllVoltageRails.
 */
static const sblutilsModuleEnableConfig_t     gModuleEnableTable[] =
{
    {PMHAL_PRCM_MOD_VIP1,      PMHAL_PRCM_MODULE_MODE_AUTO,    "VIP1"    },
    {PMHAL_PRCM_MOD_DSS,       PMHAL_PRCM_MODULE_MODE_ENABLED, "DSS"     },
    {PMHAL_PRCM_MOD_ISS,       PMHAL_PRCM_MODULE_MODE_AUTO,    "ISS"     },
    {PMHAL_PRCM_MOD_OCMC_RAM1, PMHAL_PRCM_MODULE_MODE_AUTO,
     "OCMC RAM1"},
    {PMHAL_PRCM_MOD_I2C2,      PMHAL_PRCM_MODULE_MODE_ENABLED, "I2C2"    },
    {PMHAL_PRCM_MOD_MCASP1,    PMHAL_PRCM_MODULE_MODE_ENABLED, "MCASP1"  },
    {PMHAL_PRCM_MOD_MCSPI1,    PMHAL_PRCM_MODULE_MODE_ENABLED, "MCSPI1"  },
    {PMHAL_PRCM_MOD_MCSPI2,    PMHAL_PRCM_MODULE_MODE_ENABLED, "MCSPI2"  },
    {PMHAL_PRCM_MOD_MCSPI3,    PMHAL_PRCM_MODULE_MODE_ENABLED, "MCSPI3"  },
    {PMHAL_PRCM_MOD_MCSPI4,    PMHAL_PRCM_MODULE_MODE_ENABLED, "MCSPI4"  },
    {PMHAL_PRCM_MOD_UART1,     PMHAL_PRCM_MODULE_MODE_ENABLED, "UART1"   },
    {PMHAL_PRCM_MOD_UART2,     PMHAL_PRCM_MODULE_MODE_ENABLED, "UART2"   },
    {PMHAL_PRCM_MOD_QSPI,      PMHAL_PRCM_MODULE_MODE_ENABLED, "QSPI"    },
    {PMHAL_PRCM_MOD_DCAN1,     PMHAL_PRCM_MODULE_MODE_ENABLED, "DCAN1"   },
    {PMHAL_PRCM_MOD_DCAN2,     PMHAL_PRCM_MODULE_MODE_ENABLED, "DCAN2"   },
    {PMHAL_PRCM_MOD_GPMC,      PMHAL_PRCM_MODULE_MODE_AUTO,    "GPMC"    },
    {PMHAL_PRCM_MOD_MMU_EDMA,  PMHAL_PRCM_MODULE_MODE_AUTO,    "MMU_EDMA"},
    {PMHAL_PRCM_MOD_TPCC,      PMHAL_PRCM_MODULE_MODE_AUTO,    "TPCC"    },
    {PMHAL_PRCM_MOD_TPTC1,     PMHAL_PRCM_MODULE_MODE_AUTO,    "TPTC1"   },
    {PMHAL_PRCM_MOD_TPTC2,     PMHAL_PRCM_MODULE_MODE_AUTO,    "TPTC2"   },
    {PMHAL_PRCM_MOD_EMIF1,     PMHAL_PRCM_MODULE_MODE_AUTO,    "EMIF1"   },
    {PMHAL_PRCM_MOD_L3_MAIN_1, PMHAL_PRCM_MODULE_MODE_AUTO,    "L3MAIN1" },
    {PMHAL_PRCM_MOD_L3_MAIN_2, PMHAL_PRCM_MODULE_MODE_AUTO,    "L3MAIN2" },
    {PMHAL_PRCM_MOD_L4_CFG,    PMHAL_PRCM_MODULE_MODE_AUTO,    "L4CFG"   },
    {PMHAL_PRCM_MOD_L4_PER2,   PMHAL_PRCM_MODULE_MODE_AUTO,    "L4PER2"  },
    {PMHAL_PRCM_MOD_L4_PER3,   PMHAL_PRCM_MODULE_MODE_AUTO,    "L4PER3"  },
    {PMHAL_PRCM_MOD_MAILBOX1,  PMHAL_PRCM_MODULE_MODE_AUTO,    "MAILBOX1"},
    {PMHAL_PRCM_MOD_MAILBOX2,  PMHAL_PRCM_MODULE_MODE_AUTO,    "MAILBOX2"},
    {PMHAL_PRCM_MOD_SPINLOCK,  PMHAL_PRCM_MODULE_MODE_AUTO,    "SPINLOCK"},
    {PMHAL_PRCM_MOD_TIMER1,    PMHAL_PRCM_MODULE_MODE_ENABLED, "TIMER1"  },
    {PMHAL_PRCM_MOD_TIMER2,    PMHAL_PRCM_MODULE_MODE_ENABLED, "TIMER2"  },
    {PMHAL_PRCM_MOD_TIMER3,    PMHAL_PRCM_MODULE_MODE_ENABLED, "TIMER3"  },
    {PMHAL_PRCM_MOD_TIMER4,    PMHAL_PRCM_MODULE_MODE_ENABLED, "TIMER4"  },
    {PMHAL_PRCM_MOD_TIMER5,    PMHAL_PRCM_MODULE_MODE_ENABLED, "TIMER5"  },
    {PMHAL_PRCM_MOD_TIMER6,    PMHAL_PRCM_MODULE_MODE_ENABLED, "TIMER6"  },
    {PMHAL_PRCM_MOD_TIMER7,    PMHAL_PRCM_MODULE_MODE_ENABLED, "TIMER7"  },
    {PMHAL_PRCM_MOD_TIMER8,    PMHAL_PRCM_MODULE_MODE_ENABLED, "TIMER8"  },
    {PMHAL_PRCM_MOD_GPIO1,     PMHAL_PRCM_MODULE_MODE_AUTO,    "GPIO1"   },
    {PMHAL_PRCM_MOD_GPIO2,     PMHAL_PRCM_MODULE_MODE_AUTO,    "GPIO2"   },
    {PMHAL_PRCM_MOD_GPIO3,     PMHAL_PRCM_MODULE_MODE_AUTO,    "GPIO3"   },
    {PMHAL_PRCM_MOD_GPIO4,     PMHAL_PRCM_MODULE_MODE_AUTO,    "GPIO4"   },
    {PMHAL_PRCM_MOD_MMC4,      PMHAL_PRCM_MODULE_MODE_ENABLED, "MMC4"    },
    {PMHAL_PRCM_MOD_CPGMAC,    PMHAL_PRCM_MODULE_MODE_ENABLED, "GMAC"    },
    {PMHAL_PRCM_MOD_TESOC,     PMHAL_PRCM_MODULE_MODE_AUTO,    "TESOC"   },
    {PMHAL_PRCM_MOD_CRC,       PMHAL_PRCM_MODULE_MODE_ENABLED, "CRC"     },
    {PMHAL_PRCM_MOD_ESM,       PMHAL_PRCM_MODULE_MODE_ENABLED, "ESM"     },
    {PMHAL_PRCM_MOD_DCC1,      PMHAL_PRCM_MODULE_MODE_ENABLED, "DCC1"    },
    {PMHAL_PRCM_MOD_DCC2,      PMHAL_PRCM_MODULE_MODE_ENABLED, "DCC2"    },
    {PMHAL_PRCM_MOD_DCC3,      PMHAL_PRCM_MODULE_MODE_ENABLED, "DCC3"    },
    {PMHAL_PRCM_MOD_DCC4,      PMHAL_PRCM_MODULE_MODE_ENABLED, "DCC4"    },
    {PMHAL_PRCM_MOD_DCC5,      PMHAL_PRCM_MODULE_MODE_ENABLED, "DCC5"    },
    {PMHAL_PRCM_MOD_DCC6,      PMHAL_PRCM_MODULE_MODE_ENABLED, "DCC6"    },
    {PMHAL_PRCM_MOD_DCC7,      PMHAL_PRCM_MODULE_MODE_ENABLED, "DCC7"    },
    {PMHAL_PRCM_MOD_DSP1,      PMHAL_PRCM_MODULE_MODE_AUTO,    "DSP1"    },
    {PMHAL_PRCM_MOD_DSP2,      PMHAL_PRCM_MODULE_MODE_AUTO,    "DSP2"    },
    {PMHAL_PRCM_MOD_EVE1,      PMHAL_PRCM_MODULE_MODE_AUTO,    "EVE1"    }
};

/*
 * Table containing pointers to the functions to program I2C to talk to PMIC IC.
 */
static const pmhalPmicCommI2cOperations_t     gPmicI2cfunc = {
    &SblUtilsI2cInit,
    &SblUtilsI2cReadByte,
    &SblUtilsI2cWriteByte
};

static volatile uint32_t emifEccInitBuff[32U] = {0U};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t SBLUtilsGetDDRAppCopyAddress(void)
{
    uint32_t siliconPackageType, ddrAddress;

    siliconPackageType = PlatformGetSiliconPackageType();

    if (PLATFORM_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
    {
        ddrAddress = SBL_LIB_APP_IMAGE_DDR_ADDRESS_12X12;
    }
    else /* PLATFORM_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType */
    {
        ddrAddress = SBL_LIB_APP_IMAGE_DDR_ADDRESS_15X15;
    }

    return ddrAddress;
}

int32_t SBLUtilsUartPrcm(UART_INST_t uartInstance)
{
    int32_t retVal = STW_SOK;

    if (UART1_INST == uartInstance)
    {
        /* Enable UART1 module */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_UART1,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
    }
    else if (UART3_INST == uartInstance)
    {
        /* Enable UART3 module */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_UART3,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

void SBLUtilsWakeUpIPU1Core1(uint32_t startAddr)
{
    /* Set address where Core1 should jump after wake up */
    HW_WR_REG32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_ROM_AUXBOOT1,
                startAddr);

    /* Set state register */
    HW_WR_REG32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_ROM_AUXBOOT0,
                SBL_LIB_RBL_MASTER_CORE_STATUS);

    /* Wakeup Core 1 */
    SblUtilsSendEvent();
}

void SBLUtilsEnableIPU1Unicache(void)
{
    UNICACHEEnable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
}

void SBLUtilsEvictIPU1Unicache(void)
{
    UNICACHEWriteBackAll(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                         UNICACHE_WAIT_INFINITE);
}

void SBLUtilsDisableIPU1Unicache(void)
{
    UNICACHEDisable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
}

void SBLUtilsInvalidateIPU1Unicache(void)
{
    UNICACHEInvalidateAll(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                          UNICACHE_WAIT_INFINITE);
}

void SBLUtilsDisableIPU1AMMU(void)
{
    ammuPolicyRegParams_t pagePolicyParams = {0U};
    ammuPageConfig_t      pageConfig       = {0U};
    uint32_t index, policyReg;

    /* Remove Mapping for large pages done by SBL */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.policyRegVal    = 0U;
    pageConfig.physicalAddress = 0U;
    pageConfig.logicalAddress  = 0U;
    for (index = 1U; index <= 3U; index++)
    {
        pageConfig.ammuPageNum = index;
        AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);
    }

    /* Remove Mapping for medium pages done by SBL */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.ammuPageNum     = 1U;
    pageConfig.policyRegVal    = 0U;
    pageConfig.physicalAddress = 0U;
    pageConfig.logicalAddress  = 0U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* Remove Mapping for small pages done by SBL */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = 0U;
    pageConfig.physicalAddress = 0U;
    pageConfig.logicalAddress  = 0U;
    for (index = 0U; index <= 8U; index++)
    {
        if (1U != index)
        {
            pageConfig.ammuPageNum = index;
            AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);
        }
    }

    /* Set Policy Params for medium page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable    = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize      = AMMU_PAGE_SIZE_256KB;
    pagePolicyParams.l1CacheEnable = AMMU_L1_CACHE_ENABLED;
    pagePolicyParams.l1PostedWrite = AMMU_L1_POSTED_WRITE_ENABLED;
    policyReg = AMMUMakePolicyReg(&pagePolicyParams);

    /* 1st medium page mapping: P.A. 0x40340000U V.A. 0x00040000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.ammuPageNum     = 1U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = 0x40340000U;
    pageConfig.logicalAddress  = 0x00040000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* Set Policy Params for small page */
    AMMUInitPolicyParams(&pagePolicyParams);
    pagePolicyParams.pageEnable     = AMMU_PAGE_ENABLED;
    pagePolicyParams.pageSize       = AMMU_PAGE_SIZE_16KB;
    pagePolicyParams.volatileEnable = AMMU_VOLATILE_ENABLED;
    pagePolicyParams.l1CacheEnable  = AMMU_L1_CACHE_ENABLED;
    policyReg = AMMUMakePolicyReg(&pagePolicyParams);

    /* 0th small page mapping: P.A. 0x55020000U V.A. 0x00000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.ammuPageNum     = 0U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = 0x55020000U;
    pageConfig.logicalAddress  = 0x00000000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 2nd small page mapping: P.A. 0x55024000U V.A. 0x00004000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.ammuPageNum     = 2U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = 0x55024000U;
    pageConfig.logicalAddress  = 0x00004000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 3rd small page mapping: P.A. 0x55028000U V.A. 0x00008000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.ammuPageNum     = 3U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = 0x55028000U;
    pageConfig.logicalAddress  = 0x00008000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 4th small page mapping: P.A. 0x5502C000U V.A. 0x0000C000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.ammuPageNum     = 4U;
    pageConfig.policyRegVal    = policyReg;
    pageConfig.physicalAddress = 0x5502C000U;
    pageConfig.logicalAddress  = 0x0000C000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);
}

int32_t SBLUtilsComputeIPUTesocROMCRC(crcSignature_t *crcSignVal)
{
    EDMA3CCPaRAMEntry     crcEdmaParams;
    crcSignatureRegAddr_t crcSignRegAddr;
    uint32_t crcPatternSize, crcPatternCount, crcSectorCount;
    uint32_t edmaChNum = 1U, edmaTccNum = 1U, edmaEvtqNum = 0U;
    int32_t  retVal    = STW_SOK;

    /* Initialize CRC signature value to zero */
    crcSignVal->regL = 0U;
    crcSignVal->regH = 0U;

    /* Enable CRC module */
    retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_CRC,
                                 PMHAL_PRCM_MODULE_MODE_ENABLED,
                                 PM_TIMEOUT_INFINITE);

    /* Enable EDMA TPTC and TPTC modules */
    retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_TPCC,
                                 PMHAL_PRCM_MODULE_MODE_AUTO,
                                 PM_TIMEOUT_INFINITE);
    retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_TPTC1,
                                 PMHAL_PRCM_MODULE_MODE_AUTO,
                                 PM_TIMEOUT_INFINITE);
    retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_TPTC2,
                                 PMHAL_PRCM_MODULE_MODE_AUTO,
                                 PM_TIMEOUT_INFINITE);

    /* Get CRC PSA signature register address */
    CRCGetPSASigRegAddr(SOC_CRC_BASE, CRC_CHANNEL_1, &crcSignRegAddr);

    crcPatternSize  = 8U;
    crcSectorCount  = 1U;
    crcPatternCount = TESOC_ROM_IPU_SIZE / crcPatternSize;

    /* Max CRC pattern count value can be 0xFFFF */
    if (0xFFFFU < crcPatternCount)
    {
        retVal += STW_EFAIL;
    }

    /* Initialize the EDMA */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE, 0);

    /* Set EDMA parameters */
    crcEdmaParams.srcAddr  = (uint32_t) (SOC_TESOC_BASE + TESOC_ROM(0U));
    crcEdmaParams.destAddr = crcSignRegAddr.regL;
    crcEdmaParams.aCnt     = crcPatternSize;
    crcEdmaParams.bCnt     = TESOC_ROM_IPU_SIZE / crcEdmaParams.aCnt;
    crcEdmaParams.cCnt     = 1U;
    crcEdmaParams.srcBIdx  = crcPatternSize;
    crcEdmaParams.destBIdx = 0U;
    crcEdmaParams.srcCIdx  = crcEdmaParams.aCnt * crcEdmaParams.bCnt;
    crcEdmaParams.destCIdx = 0U;
    crcEdmaParams.linkAddr = 0xFFFFU;
    crcEdmaParams.opt      =
        (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
         EDMA3_OPT_ITCINTEN_MASK |
         ((edmaTccNum << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

    /* Initialize CRC channel */
    retVal += CRCInitialize(SOC_CRC_BASE, CRC_CHANNEL_1, 0x0U, 0x0U);

    /* Request EDMA Channel */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChNum,
                        edmaTccNum,
                        edmaEvtqNum);

    /* Reset CRC Channel */
    CRCChannelReset(SOC_CRC_BASE, CRC_CHANNEL_1);

    /* Configure CRC channel */
    retVal += CRCConfigure(SOC_CRC_BASE,
                           CRC_CHANNEL_1,
                           crcPatternCount,
                           crcSectorCount,
                           CRC_OPERATION_MODE_SEMICPU);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edmaChNum, &crcEdmaParams);

    /* Trigger the EDMA */
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE,
                        edmaChNum,
                        EDMA3_TRIG_MODE_MANUAL);

    /* Wait for transfer to complete */
    while (0U == (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                  ((uint32_t) 1U << edmaChNum)))
    {
        /* Do Nothing */
    }

    /* Clear EDMA completion interrupt */
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaTccNum);

    /* Fetch CRC signature and clear interrupt status */
    if (0x0U != CRCGetIntrStatus(SOC_CRC_BASE, CRC_CHANNEL_1))
    {
        /* Fetch CRC signature value */
        CRCGetPSASectorSig(SOC_CRC_BASE, CRC_CHANNEL_1, crcSignVal);

        /* Clear CRC Interrupt Status */
        CRCClearIntr(SOC_CRC_BASE,
                     CRC_CHANNEL_1,
                     CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);
    }
    else
    {
        retVal += STW_EFAIL;
    }

    /* De-initialize EDMA */
    EDMA3Deinit(SOC_EDMA_TPCC_BASE, 0);

    return retVal;
}

int32_t SBLUtilsDDRReadEdma(void       *dstAddr,
                            const void *srcAddr,
                            uint32_t    length)
{
    int32_t retVal = STW_SOK;

    if (NULL == dstAddr)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        EDMA3CCPaRAMEntry edmaParam;
        uint32_t          edmaChNum = 1U;
        uint32_t          bCntValue = 1U;
        uint32_t          remBytes  = 0;
        uint32_t          aCntValue = length;
        uint32_t          addr      = (uint32_t) (dstAddr);
        uint32_t          maxACnt   = 0x7FFFU;
        if (length > maxACnt)
        {
            bCntValue = (length / maxACnt);
            remBytes  = (length % maxACnt);
            aCntValue = maxACnt;
        }

        /* Assign EDMA Params for AB sync transfer */
        edmaParam.opt      = 0;
        edmaParam.srcAddr  = (uint32_t) srcAddr;
        edmaParam.destAddr = addr;
        edmaParam.aCnt     = aCntValue;
        edmaParam.bCnt     = bCntValue;
        edmaParam.cCnt     = 1;
        edmaParam.srcBIdx  = aCntValue;
        edmaParam.destBIdx = aCntValue;
        edmaParam.srcCIdx  = 0;
        edmaParam.destCIdx = 0;
        edmaParam.linkAddr = 0xFFFF;
        edmaParam.opt     |=
            (EDMA_TPCC_OPT_TCINTEN_MASK |
             ((edmaChNum <<
               EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK) |
             EDMA_TPCC_OPT_SYNCDIM_MASK);

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edmaChNum, &edmaParam);
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edmaChNum,
                            EDMA3_TRIG_MODE_MANUAL);

        while (0U ==
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                ((uint32_t) 1U << edmaChNum)))
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaChNum);
        if (0U != remBytes)
        {
            /* Assign EDMA Params for remaining bytes */
            edmaParam.opt      = 0;
            edmaParam.srcAddr  = (bCntValue * maxACnt) + (uint32_t) srcAddr;
            edmaParam.destAddr = (addr + (maxACnt * bCntValue));
            edmaParam.aCnt     = remBytes;
            edmaParam.bCnt     = 1;
            edmaParam.cCnt     = 1;
            edmaParam.srcBIdx  = remBytes;
            edmaParam.destBIdx = remBytes;
            edmaParam.srcCIdx  = 0;
            edmaParam.destCIdx = 0;
            edmaParam.linkAddr = 0xFFFF;
            edmaParam.opt     |=
                (EDMA_TPCC_OPT_TCINTEN_MASK |
                 ((edmaChNum <<
                   EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));

            EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edmaChNum, &edmaParam);
            EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edmaChNum,
                                EDMA3_TRIG_MODE_MANUAL);

            while (0U ==
                   (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                    ((uint32_t) 1U << edmaChNum)))
            {
                /* Busy Loop */
            }
            EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaChNum);
        }
    }

    /* Ensure that the M4 does not have a stale copy of the region
     * to which the copy is being made.
     */
    UNICACHEInvalidate(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                       (uint32_t) (dstAddr),
                       length,
                       UNICACHE_WAIT_INFINITE);

    return retVal;
}

int32_t SBLUtilsComputeCRC(const void     *crcSrcAddr,
                           uint32_t        crcDataSize,
                           crcSignature_t *crcSignVal)
{
    EDMA3CCPaRAMEntry     crcEdmaParams;
    crcSignatureRegAddr_t crcSignRegAddr;
    uint32_t crcPatternSize  = 0U, crcPatternCount = 0U, crcSectorCount = 0U;
    uint32_t edmaChNum       = 1U, edmaTccNum = 1U, edmaEvtqNum = 0U;
    uint32_t edmaACnt        = 0U, edmaBCnt = 0U, edmaCCnt = 0U;
    uint32_t remBytes        = 0U, index = 0U;
    uint32_t maxPatternCount = 0xFFFFFU, maxBCnt = 0xFFFU;
    uint32_t origDataSize    = 0U, remPatternCount = 0U;
    uint32_t iterCount       = 0U, iterIndex = 0U, dataRead = 0U;
    int32_t  retVal          = STW_SOK;

    /* Initialize CRC signature value to zero */
    crcSignVal->regL = 0U;
    crcSignVal->regH = 0U;

    /* Get CRC PSA signature register address */
    CRCGetPSASigRegAddr(SOC_CRC_BASE, CRC_CHANNEL_1, &crcSignRegAddr);

    /* Initialize CRC channel */
    retVal += CRCInitialize(SOC_CRC_BASE, CRC_CHANNEL_1, 0x0U, 0x0U);

    /* Request EDMA Channel */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChNum,
                        edmaTccNum,
                        edmaEvtqNum);

    /* Set CRC signature Seed value to Zero */
    CRCSetPSASeedSig(SOC_CRC_BASE, CRC_CHANNEL_1, crcSignVal);

    crcPatternSize  = 8U;
    crcSectorCount  = 1U;
    crcPatternCount = crcDataSize / crcPatternSize;

    /* Max CRC pattern count value can be 0xFFFFFU */
    if (maxPatternCount < crcPatternCount)
    {
        origDataSize    = crcDataSize;
        iterCount       = origDataSize / (maxPatternCount * crcPatternSize);
        remPatternCount =
            (origDataSize -
             (iterCount * (maxPatternCount * crcPatternSize))) / crcPatternSize;
        crcPatternCount = maxPatternCount;
    }

    for (iterIndex = 0U; iterIndex <= iterCount; iterIndex++)
    {
        if ((iterIndex == iterCount) && (0U < iterCount))
        {
            crcPatternCount = remPatternCount;
        }

        if (0U < iterIndex)
        {
            /* Fetch CRC signature and clear interrupt status */
            while (0x0U == CRCGetIntrStatus(SOC_CRC_BASE, CRC_CHANNEL_1))
            {
                /* Do Nothing */
            }

            /* Fetch CRC signature value */
            CRCGetPSASectorSig(SOC_CRC_BASE, CRC_CHANNEL_1, crcSignVal);

            /* Clear CRC Interrupt Status */
            CRCClearIntr(SOC_CRC_BASE,
                         CRC_CHANNEL_1,
                         CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);

            /* Set CRC signature Seed value */
            CRCSetPSASeedSig(SOC_CRC_BASE, CRC_CHANNEL_1, crcSignVal);
        }

        crcDataSize = crcPatternCount * crcPatternSize;

        /* Configure CRC channel */
        retVal += CRCConfigure(SOC_CRC_BASE,
                               CRC_CHANNEL_1,
                               crcPatternCount,
                               crcSectorCount,
                               CRC_OPERATION_MODE_SEMICPU);

        edmaACnt = crcPatternSize;
        edmaBCnt = crcDataSize / edmaACnt;
        edmaCCnt = 1U;
        if (edmaBCnt > maxBCnt)
        {
            edmaCCnt = crcDataSize / (maxBCnt * edmaACnt);
            edmaBCnt = maxBCnt;
            remBytes = crcDataSize - (edmaACnt * (edmaBCnt * edmaCCnt));
        }

        /* Set EDMA parameters */
        crcEdmaParams.srcAddr  = (uint32_t) crcSrcAddr + dataRead;
        crcEdmaParams.destAddr = crcSignRegAddr.regL;
        crcEdmaParams.aCnt     = edmaACnt;
        crcEdmaParams.bCnt     = edmaBCnt;
        crcEdmaParams.cCnt     = edmaCCnt;
        crcEdmaParams.srcBIdx  = crcEdmaParams.aCnt;
        crcEdmaParams.destBIdx = 0U;
        crcEdmaParams.srcCIdx  = crcEdmaParams.aCnt * crcEdmaParams.bCnt;
        crcEdmaParams.destCIdx = 0U;
        crcEdmaParams.linkAddr = 0xFFFFU;
        crcEdmaParams.opt      =
            (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
             EDMA3_OPT_ITCINTEN_MASK |
             ((edmaTccNum << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edmaChNum, &crcEdmaParams);

        for (index = 0; index < edmaCCnt; index++)
        {
            /* Trigger the EDMA */
            EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE,
                                edmaChNum,
                                EDMA3_TRIG_MODE_MANUAL);
            dataRead += crcEdmaParams.aCnt * crcEdmaParams.bCnt;

            /* Wait for transfer to complete */
            while (0U == (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                          ((uint32_t) 1U << edmaChNum)))
            {
                /* Do Nothing */
            }

            /* Clear EDMA completion interrupt */
            EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaTccNum);
        }

        if (0U != remBytes)
        {
            /* Set EDMA parameters */
            crcEdmaParams.opt      = 0;
            crcEdmaParams.srcAddr  = (uint32_t) crcSrcAddr + dataRead;
            crcEdmaParams.destAddr = crcSignRegAddr.regL;
            crcEdmaParams.aCnt     = edmaACnt;
            crcEdmaParams.bCnt     = remBytes / edmaACnt;
            crcEdmaParams.cCnt     = 1U;
            crcEdmaParams.srcBIdx  = crcEdmaParams.aCnt;
            crcEdmaParams.destBIdx = 0U;
            crcEdmaParams.srcCIdx  = crcEdmaParams.aCnt * crcEdmaParams.bCnt;
            crcEdmaParams.destCIdx = 0U;
            crcEdmaParams.linkAddr = 0xFFFFU;
            crcEdmaParams.opt      =
                (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
                 EDMA3_OPT_ITCINTEN_MASK |
                 ((edmaTccNum << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

            EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edmaChNum, &crcEdmaParams);

            /* Trigger the EDMA */
            EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE,
                                edmaChNum,
                                EDMA3_TRIG_MODE_MANUAL);
            dataRead += crcEdmaParams.aCnt * crcEdmaParams.bCnt;

            /* Wait for transfer to complete */
            while (0U == (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                          ((uint32_t) 1U << edmaChNum)))
            {
                /* Do Nothing */
            }

            /* Clear EDMA completion interrupt */
            EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaTccNum);

            remBytes = 0U;
        }
    }

    /* Fetch CRC signature and clear interrupt status */
    while (0x0U == CRCGetIntrStatus(SOC_CRC_BASE, CRC_CHANNEL_1))
    {
        /* Do Nothing */
    }

    /* Fetch CRC signature value */
    CRCGetPSASectorSig(SOC_CRC_BASE, CRC_CHANNEL_1, crcSignVal);

    /* Clear CRC Interrupt Status */
    CRCClearIntr(SOC_CRC_BASE,
                 CRC_CHANNEL_1,
                 CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);

    if ((dataRead != origDataSize) && (maxPatternCount < crcPatternCount))
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n CRC Not Calculated Correctly \n");
    }

    return retVal;
}

void SBLUtilsConfigIPU1DefaultAMMU(void)
{
    ammuPageConfig_t pageConfig = {0U};
    uint32_t         index;

    /* Large Page Translations
     * Pages mapped by RBL: 0th page: P.A. 0x08000000 to V.A. 0x08000000
     * SBL re-maps 1st large page, so clear 1st page mapping by RBL
     */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum     = 1U;
    pageConfig.policyRegVal    = 0U;
    pageConfig.physicalAddress = 0U;
    pageConfig.logicalAddress  = 0U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 1st large page mapping: P.A. 0x40000000U V.A 0x40000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum     = 1U;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE1_POLICY;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE1_PHY_ADDR;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE1_VIRTUAL_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 2nd large page mapping: P.A. 0x80000000U V.A 0x80000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum     = 2U;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE2_POLICY;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE2_PHY_ADDR;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE2_VIRTUAL_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 3rd large page mapping: P.A. 0x80000000U V.A 0xA0000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum     = 3U;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE3_POLICY;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE3_PHY_ADDR;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_LARGE_PAGE3_VIRTUAL_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* Medium Page Translations
     * Pages mapped by RBL 0th page: P.A. 0x40300000 to V.A. 0x00300000
     * SBL re-maps 1st medium page, so clear 1st page mapping by RBL
     */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.ammuPageNum     = 1U;
    pageConfig.policyRegVal    = 0U;
    pageConfig.physicalAddress = 0U;
    pageConfig.logicalAddress  = 0U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 1st medium page mapping: P.A. 0x55020000U V.A 0x00000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_MEDIUM;
    pageConfig.ammuPageNum     = 1U;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_MED_PAGE1_POLICY;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_MED_PAGE1_PHY_ADDR;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_MED_PAGE1_VIRTUAL_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* Small Page Translations
     * Pages mapped by design 1st page: P.A. 0x55080000 to V.A. 0x40000000
     * Change policy of this page for mapping 16 KB instead of 4 KB
     * SBL re-maps IPU RAM in 1st medium page. Clear ROM and RAM mappings done
     * by RBL
     */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = 0U;
    pageConfig.physicalAddress = 0U;
    pageConfig.logicalAddress  = 0U;
    for (index = 0U; index <= 6U; index++)
    {
        if (1U != index)
        {
            pageConfig.ammuPageNum = index;
            AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);
        }
    }

    /* 0th small page mapping: P.A. 0x43300000U V.A. 0x63300000U  */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE0_POLICY;
    pageConfig.ammuPageNum     = 0;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE0_VIRTUAL_ADDR;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE0_PHY_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 1st small page mapping: P.A. 0x55080000U V.A. 0x40000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE1_POLICY;
    pageConfig.ammuPageNum     = 1;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE1_VIRTUAL_ADDR;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE1_PHY_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 2nd small page mapping: P.A. 0x43304000U V.A. 0x63304000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE2_POLICY;
    pageConfig.ammuPageNum     = 2;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE2_VIRTUAL_ADDR;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE2_PHY_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 3rd small page mapping: P.A. 0x42081000U V.A. 0x62081000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE3_POLICY;
    pageConfig.ammuPageNum     = 3;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE3_VIRTUAL_ADDR;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE3_PHY_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 4th small page mapping: P.A. 0x4208B000U V.A. 0x6208B000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE4_POLICY;
    pageConfig.ammuPageNum     = 4;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE4_VIRTUAL_ADDR;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE4_PHY_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 5th small page mapping: P.A. 0x4208C000U V.A. 0x6208C000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE5_POLICY;
    pageConfig.ammuPageNum     = 5;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE5_VIRTUAL_ADDR;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE5_PHY_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 6th small page mapping: P.A. 0x4883A000U  V.A. 0x6883A000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE6_POLICY;
    pageConfig.ammuPageNum     = 6;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE6_VIRTUAL_ADDR;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE6_PHY_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 7th small page mapping: P.A. 0x420A0000U V.A. 0x620A0000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE7_POLICY;
    pageConfig.ammuPageNum     = 7;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE7_VIRTUAL_ADDR;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE7_PHY_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 8th small page mapping: P.A. 0x42086000U V.A. 0x62086000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE8_POLICY;
    pageConfig.ammuPageNum     = 8;
    pageConfig.logicalAddress  = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE8_VIRTUAL_ADDR;
    pageConfig.physicalAddress = SBL_UTILS_TDA3XX_AMMU_SMALL_PAGE8_PHY_ADDR;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);
}

int32_t SBLUtilsConfigPowerDomains(void)
{
    int32_t  retVal   = STW_SOK;
    uint32_t tblIndex = 0U;

    for (tblIndex = 0U;
         tblIndex < SBL_UTILS_NUM_ENTRIES_POWER_DOMAIN_STATE_TABLE;
         tblIndex++)
    {
        retVal += PMHALPdmSetPDState(
            (pmhalPrcmPdId_t) gPowerDomainStateTable[tblIndex].domainId,
            (pmhalPrcmPdState_t) gPowerDomainStateTable[tblIndex].
            powerDomainState,
            PM_TIMEOUT_NOWAIT);
    }
    return retVal;
}

void SBLUtilsConfigDpll(uint32_t oppId)
{
    pmhalPrcmDpllConfig_t *dpllParams;
    int32_t retVal = STW_SOK;
    pmhalPrcmSysClkVal_t   sysClkFreq = PMHALCMGetSysClockFreqEnum();

    /* Configure DPLL GMAC */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_DSP_GMAC,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_DSP_GMAC,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL GMAC not configured Correctly \n");
        SBLLibAbortBoot();
    }
    /* The EVE VID DSP DPLL sources the DSP clock only in OPP HIGH. Hence
     * configure this DPLL only when the OPP chosen is OPP_HIGH.
     */
    if (SBLLIB_PRCM_DPLL_OPP_HIGH == oppId)
    {
        /* Configure DPLL EVE_VID_DSP */
        retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_EVE_VID_DSP,
                                         sysClkFreq,
                                         oppId,
                                         &dpllParams);

        retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_EVE_VID_DSP,
                                       dpllParams,
                                       PM_TIMEOUT_INFINITE);
    }
    /* Configure DPLL DDR */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_DDR,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_DDR,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DPLL DDR not configured Correctly \n");
        SBLLibAbortBoot();
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n DPLL Configuration Completed \n");
}

void SBLUtilsConfigClockDomains(void)
{
    int32_t  retVal   = STW_SOK;
    uint32_t tblIndex = 0U;

    for (tblIndex = 0U;
         tblIndex < SBL_UTILS_NUM_ENTRIES_CLOCK_DOMAIN_STATE_TABLE;
         tblIndex++)
    {
        retVal = PMHALCMSetCdClockMode(
            (pmhalPrcmCdId_t) gClockDomainStateTable[tblIndex].domainId,
            (pmhalPrcmCdClkTrnModes_t) gClockDomainStateTable[tblIndex].
            clockDomainState,
            PM_TIMEOUT_NOWAIT);

        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Clock Domain Config Error - ");
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         gClockDomainStateTable[tblIndex].clockDomainName);
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR, " \n");
        }
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n Clock Domain Configuration Completed \n");
}

void SBLUtilsConfigModules(void)
{
    int32_t  retVal   = STW_SOK;
    uint32_t tblIndex = 0U;

    for (tblIndex = 0U;
         tblIndex < SBL_UTILS_NUM_ENTRIES_MODULE_ENABLE_TABLE;
         tblIndex++)
    {
        if ((PMHAL_PRCM_MOD_DSS == gModuleEnableTable[tblIndex].moduleId) &&
            (PMHAL_PRCM_MODULE_MODE_ENABLED ==
             gModuleEnableTable[tblIndex].moduleEnableMode))
        {
            PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_DSS);
        }

        /* Set clock frequency to 48 MHz for MMC4 */
        if ((PMHAL_PRCM_MOD_MMC4 == gModuleEnableTable[tblIndex].moduleId) &&
            (PMHAL_PRCM_MODULE_MODE_ENABLED ==
             gModuleEnableTable[tblIndex].moduleEnableMode))
        {
            PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_MMC4_GFCLK_MUX,
                                   PMHAL_PRCM_DIV_FUNC_48M_FCLK);
        }

        retVal = PMHALModuleModeSet(
            (pmhalPrcmModuleId_t) gModuleEnableTable[tblIndex].moduleId,
            (pmhalPrcmModuleSModuleMode_t) gModuleEnableTable[tblIndex].
            moduleEnableMode,
            PM_TIMEOUT_INFINITE);

        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Module Enable Error - ");
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         gModuleEnableTable[tblIndex].moduleName);
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR, " \n");
        }
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n Module Enable Configuration Completed \n");
}

int32_t SBLUtilsConfigAllVoltageRails(uint32_t oppId)
{
    int32_t  retVal = PM_SUCCESS;
    int32_t  vdId;
    const pmhalPmicOperations_t *pmicOps;
    uint32_t siliconPackageType;

    /* Register the I2C functions with the PMIC Communication to ensure the
     * PMIC can be communicated with I2C driver specific to SBL
     */
    PMHALPmicCommI2CRegister(&gPmicI2cfunc);

    /*
     * Set the OPP for which the voltage would be configured.
     * Only OPP_NOM supported.
     */

    siliconPackageType = PlatformGetSiliconPackageType();
    /*
     * Get the pmic ops and register with the pmic interface.
     */
    if (PLATFORM_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType)
    {
        pmicOps = PMHALTps65917GetPMICOps();
    }
    else
    {
        /* NOTE : Additionally need to program PRCM for I2C2 if configuring more
         * voltage rails than CORE and DSPEVE.
         */
        pmicOps = PMHALL8731GetPMICOps();
    }
    retVal = PMHALPmicRegister(pmicOps);

    /* Set the voltage for PMHAL_PRCM_VD_CORE and PMHAL_PRCM_VD_DSPEVE. */
    for (vdId = (int32_t) PMHAL_PRCM_VD_MIN;
         vdId < (int32_t) PMHAL_PRCM_VD_COUNT;
         vdId++)
    {
        retVal += PMHALVMSetOpp((pmhalPrcmVdId_t) vdId,
                                (pmhalVmOppId_t) oppId, PM_TIMEOUT_INFINITE);
    }
    return retVal;
}

int32_t SBLUtilsEmifECCConfigure(void)
{
    int32_t                  retVal = STW_SOK;
    uint32_t                 siliconPackageType, emifSize;
    emifEccCfgPrm_t          eccConfigParams     = {0};
    emifEccAddrRangeCfgPrm_t addrRangeParams[2U] = {0U};
    uint32_t                 range1Type, range1StartAddr, range1EndAddr;
    uint32_t                 range2Type, range2StartAddr, range2EndAddr;
    uint32_t                 edmaStartAddr1, edmaEndAddr1;
    uint32_t                 edmaStartAddr2, edmaEndAddr2;
    uint32_t                 edmaStartAddr3, edmaEndAddr3;
    uint32_t                 srcBuffAddr, intrStatus;

    /* Before configuring ECC EMIF, make sure ECC is enabled in control module
     * i.e. register CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT
     */
    siliconPackageType = PlatformGetSiliconPackageType();

    if (PLATFORM_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
    {
        range1Type      = SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_12X12;
        range1StartAddr = SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_12X12;
        range1EndAddr   = SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_12X12;
        range2Type      = SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_12X12;
        range2StartAddr = SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_12X12;
        range2EndAddr   = SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_12X12;
        emifSize        = SBL_LIB_CONFIG_EMIF_SIZE_12X12;
    }
    else /* PLATFORM_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType */
    {
        range1Type      = SBL_LIB_CONFIG_EMIF_ECC_REG1_RANGE_TYPE_15X15;
        range1StartAddr = SBL_LIB_CONFIG_EMIF_ECC_START_ADDR1_15X15;
        range1EndAddr   = SBL_LIB_CONFIG_EMIF_ECC_END_ADDR1_15X15;
        range2Type      = SBL_LIB_CONFIG_EMIF_ECC_REG2_RANGE_TYPE_15X15;
        range2StartAddr = SBL_LIB_CONFIG_EMIF_ECC_START_ADDR2_15X15;
        range2EndAddr   = SBL_LIB_CONFIG_EMIF_ECC_END_ADDR2_15X15;
        emifSize        = SBL_LIB_CONFIG_EMIF_SIZE_15X15;
    }

    /* Configure EMIF ECC address parameters */
    addrRangeParams[0U].addrRangeType   = range1Type;
    addrRangeParams[0U].enableAddrRange = TRUE;
    addrRangeParams[0U].startAddr       = range1StartAddr;
    addrRangeParams[0U].endAddr         = range1EndAddr;
    addrRangeParams[0U].addrRangeNum    = EMIF_ECC_ADDR_RANGE_NUM_1;

    addrRangeParams[1U].addrRangeType   = range2Type;
    addrRangeParams[1U].enableAddrRange = TRUE;
    addrRangeParams[1U].startAddr       = range2StartAddr;
    addrRangeParams[1U].endAddr         = range2EndAddr;
    addrRangeParams[1U].addrRangeNum    = EMIF_ECC_ADDR_RANGE_NUM_2;

    /* Configure EMIF ECC parameters common for region1 and region 2 */
    eccConfigParams.thresholdVal  = 0x1U;
    eccConfigParams.emifStartAddr = SBL_LIB_CONFIG_EMIF_START_ADDR;

    /* Enable ECC for Region1 */
    eccConfigParams.addrRangeCfgPrm = &addrRangeParams[0U];
    if ((0U != eccConfigParams.addrRangeCfgPrm->startAddr) &&
        (0U != eccConfigParams.addrRangeCfgPrm->endAddr))
    {
        retVal += EMIFConfigECCInitECCParams(SOC_EMIF1_CONF_REGS_BASE,
                                             &eccConfigParams);
    }

    /* Enable ECC for Region2 */
    eccConfigParams.addrRangeCfgPrm = &addrRangeParams[1U];
    if ((0U != eccConfigParams.addrRangeCfgPrm->startAddr) &&
        (0U != eccConfigParams.addrRangeCfgPrm->endAddr))
    {
        retVal += EMIFConfigECCInitECCParams(SOC_EMIF1_CONF_REGS_BASE,
                                             &eccConfigParams);
    }

    /* Enable EMIF ECC */
    EMIFConfigECCEnableEcc(SOC_EMIF1_CONF_REGS_BASE);

    /* Initialize the EDMA */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE, 0);

    srcBuffAddr = (uint32_t) (emifEccInitBuff) + 0x40000000U;

    /* Initialize ECC EMIF Regions */
    if ((EMIF_ECC_ADDR_RANGE_WITHIN == range1Type) &&
        (EMIF_ECC_ADDR_RANGE_WITHIN == range2Type))
    {
        SBLUtilsPreFillECCMemory((void *) range1StartAddr,
                                 (const void *) srcBuffAddr,
                                 ((range1EndAddr - range1StartAddr) + 1U));

        SBLUtilsPreFillECCMemory((void *) range2StartAddr,
                                 (const void *) srcBuffAddr,
                                 ((range2EndAddr - range2StartAddr) + 1U));
    }
    else if ((EMIF_ECC_ADDR_RANGE_WITHIN != range1Type) &&
             (EMIF_ECC_ADDR_RANGE_WITHIN == range2Type))
    {
        edmaStartAddr1 = SBL_LIB_CONFIG_EMIF_START_ADDR;
        edmaEndAddr1   = range1StartAddr;
        if (edmaStartAddr1 != edmaEndAddr1)
        {
            SBLUtilsPreFillECCMemory((void *) edmaStartAddr1,
                                     (const void *) srcBuffAddr,
                                     ((edmaEndAddr1 - edmaStartAddr1) + 1U));
        }
        edmaStartAddr2 = range1EndAddr;
        edmaEndAddr2   = emifSize + SBL_LIB_CONFIG_EMIF_START_ADDR;
        SBLUtilsPreFillECCMemory((void *) edmaStartAddr2,
                                 (const void *) srcBuffAddr,
                                 ((edmaEndAddr2 - edmaStartAddr2) + 1U));
    }
    else if ((EMIF_ECC_ADDR_RANGE_WITHIN == range1Type) &&
             (EMIF_ECC_ADDR_RANGE_WITHIN != range2Type))
    {
        edmaStartAddr1 = SBL_LIB_CONFIG_EMIF_START_ADDR;
        edmaEndAddr1   = range2StartAddr;
        if (edmaStartAddr1 != edmaEndAddr1)
        {
            SBLUtilsPreFillECCMemory((void *) edmaStartAddr1,
                                     (const void *) srcBuffAddr,
                                     ((edmaEndAddr1 - edmaStartAddr1) + 1U));
        }
        edmaStartAddr2 = range2EndAddr;
        edmaEndAddr2   = emifSize + SBL_LIB_CONFIG_EMIF_START_ADDR;
        SBLUtilsPreFillECCMemory((void *) edmaStartAddr2,
                                 (const void *) srcBuffAddr,
                                 ((edmaEndAddr2 - edmaStartAddr2) + 1U));
    }
    else /*(EMIF_ECC_ADDR_RANGE_WITHIN != range1Type) &&
          * (EMIF_ECC_ADDR_RANGE_WITHIN != range2Type) */
    {
        edmaStartAddr1 = SBL_LIB_CONFIG_EMIF_START_ADDR;
        edmaEndAddr1   = range1StartAddr;
        if (edmaStartAddr1 != edmaEndAddr1)
        {
            SBLUtilsPreFillECCMemory((void *) edmaStartAddr1,
                                     (const void *) srcBuffAddr,
                                     ((edmaEndAddr1 - edmaStartAddr1) + 1U));
        }
        edmaStartAddr2 = range1EndAddr;
        edmaEndAddr2   = range2StartAddr;
        SBLUtilsPreFillECCMemory((void *) edmaStartAddr2,
                                 (const void *) srcBuffAddr,
                                 ((edmaEndAddr2 - edmaStartAddr2) + 1U));
        edmaStartAddr3 = range2EndAddr;
        edmaEndAddr3   = emifSize + SBL_LIB_CONFIG_EMIF_START_ADDR;
        SBLUtilsPreFillECCMemory((void *) edmaStartAddr3,
                                 (const void *) srcBuffAddr,
                                 ((edmaEndAddr3 - edmaStartAddr3) + 1U));
    }

    /* De-initialize EDMA */
    EDMA3Deinit(SOC_EDMA_TPCC_BASE, 0);

    /* Check for ECC errors before loading app image */
    intrStatus = EMIFGetIntrRawStatus(SOC_EMIF1_CONF_REGS_BASE);
    if (0U != intrStatus)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "EMIF ECC violation occurred before loading app image, aborting boot");
        SBLLibAbortBoot();
    }

    return retVal;
}

int32_t SBLUtilsConfigureDspEveMux(uint32_t oppId,
                                   uint32_t siliconPackageType)
{
    int32_t retVal = STW_SOK;
    /* In case of 15X15 Silicon, DSP and EVE are sourced from DPLL GMAC.
     * Configure PRCM and Control Module registers before configuring DPLL.
     */
    if (PLATFORM_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType)
    {
        /* Select DSP Clock Source */
        switch (oppId)
        {
            case SBLLIB_PRCM_DPLL_OPP_NOM:
                retVal += PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_DSP_GFCLK_MUX,
                                                 PMHAL_PRCM_DPLL_DSP_GMAC);
                break;
            case SBLLIB_PRCM_DPLL_OPP_OD:
                retVal += PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_DSP_GFCLK_MUX,
                                                 PMHAL_PRCM_DPLL_CORE);
                break;
            case SBLLIB_PRCM_DPLL_OPP_HIGH:
                retVal += PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_DSP_GFCLK_MUX,
                                                 PMHAL_PRCM_DPLL_EVE_VID_DSP);
                break;
            default:
                retVal = STW_EFAIL;
                break;
        }
        /* Select EVE Clock Source */
        retVal += PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_EVE_GCLK_MUX,
                                         PMHAL_PRCM_DPLL_DSP_GMAC);
        retVal += PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_EVE_CLK_MUX,
                                         PMHAL_PRCM_MUX_EVE_GCLK_MUX);
    }
    else
    {
        /* Select DSP Clock Source */
        retVal += PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_DSP_GFCLK_MUX,
                                         PMHAL_PRCM_DPLL_CORE);

        /* Select EVE Clock Source */
        retVal += PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_EVE_GCLK_MUX,
                                         PMHAL_PRCM_DPLL_CORE);
        retVal += PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_EVE_CLK_MUX,
                                         PMHAL_PRCM_MUX_EVE_GCLK_MUX);
    }
    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void SblUtilsSendEvent(void)
{
    asm (" SEV");
}

static int32_t SblUtilsI2cInit(void)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t baseAddr = SOC_I2C1_BASE;

    /* Force Wake-up clock domain L4PER1 */
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER1,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_NOWAIT);

    /* Enable I2C1 for PMIC Communication */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_I2C1,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);

    /*
     * Do a soft reset so we can clear any incorrect state and
     * configure to suit the PMIC communication.
     */
    I2CSoftReset(baseAddr);

    /*
     * Ensure that the reset is completed. The RDONE bit is set
     * only when the I2C is enabled, so enable I2C before
     * checking for the reset completion.
     */
    I2CMasterEnable(baseAddr);

    timeout = 50U;  /* Approximately 50ms */
    while ((I2CSystemStatusGet(baseAddr) !=
            I2C_SYSS_RDONE_RSTCOMP)
           && (timeout > 0))
    {
        PMUtilsMinDelayMS((uint32_t) 1U);
        timeout--;
    }

    if (timeout == 0)
    {
        status = STW_EFAIL;
    }

    if (status == STW_SOK)
    {
        /* Disable I2C so we can configure for the PMIC communication. */
        I2CMasterEnable(baseAddr);

        /* Configure the I2C BUS clock frequency (I2C_SCL). */
        I2CMasterInitExpClk(baseAddr,
                            SBL_UTILS_I2C_SYSTEM_CLOCK,
                            SBL_UTILS_I2C_INTERNAL_CLOCK,
                            SBL_UTILS_I2C_OUTPUT_CLOCK);

        /*
         * The PMIC communication is always as a master so we don't have
         * to configure the I2C own address. However, it doesn't hurt.
         */
        I2COwnAddressSet(baseAddr, 0,
                         I2C_OWN_ADDR_0);

        /*
         * Make sure the I2C is not in Forced Idle Mode by setting it to No
         * Idle mode.
         */
        I2CSyscInit(baseAddr,
                    (uint32_t) (I2C_AUTOIDLE_DISABLE |
                                I2C_CUT_OFF_BOTH_CLK |
                                I2C_ENAWAKEUP_DISABLE |
                                I2C_NO_IDLE_MODE));

        /*
         * Configure the I2C:
         *    Select Fast/Standard Mode
         *    Select normal mode (vs. start byte mode)
         *    Select 7-bit slave address mode
         *
         * Note that this API writes the 32-bit value passed to the I2C_CON
         * register; the config bits not mentioned below is set to zero.
         */
        I2CConfig(baseAddr, I2C_CFG_N0RMAL_MODE |
                  I2C_CFG_7BIT_SLAVE_ADDR |
                  I2C_OPMODE_FAST_STAND_MODE);

        /* PMIC Comm uses polling mode; disable all the interrupts. */
        I2CMasterIntDisableEx(baseAddr, I2C_INT_ALL);

        /*
         * Bypass the Tx/Rx FIFO. For PRCM access we always read one byte
         * at a time so FIFO is bypassed.
         */
        I2CFIFOThresholdConfig(baseAddr,
                               0, I2C_TX_MODE);
        I2CFIFOThresholdConfig(baseAddr,
                               0, I2C_RX_MODE);
        I2CFIFOClear(baseAddr, I2C_TX_MODE);
        I2CFIFOClear(baseAddr, I2C_RX_MODE);

        /* Enable I2C module. */
        I2CMasterEnable(baseAddr);

        /*
         * This is required to ensure that the I2C communication continues
         * even if A15 (the master core) is debug halted on a breakpoint.
         */
        I2CMasterEnableFreeRun(baseAddr);
    }

    /* Clear status register  */
    I2CMasterIntClearEx(baseAddr, I2C_INT_ALL);

    return status;
}

static int32_t SblUtilsI2cReadByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                   const uint8_t *regAddr,
                                   uint8_t *regValue,
                                   uint32_t numRegs)
{
    int32_t status = STW_SOK;
    status = SblUtilsI2cWrite(i2cNum, (uint8_t) i2cDevAddr, regAddr, 1U);

    /* Then read the value sent by the slave.  */
    if (status == STW_SOK)
    {
        status = SblUtilsI2cRead(i2cNum, (uint8_t) i2cDevAddr, regValue);
    }
    else
    {
        *regValue = 0U;
    }
    return status;
}

static int32_t SblUtilsI2cWriteByte(uint32_t i2cNum, uint32_t i2cDevAddr,
                                    const uint8_t *regAddr,
                                    const uint8_t *regValue,
                                    uint32_t numRegs)
{
    uint8_t  data[2];
    uint8_t  count       = (uint8_t) 2U;
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    data[0] = *regAddr;
    data[1] = *regValue;
    status  = SblUtilsI2cWrite(i2cNum, (uint8_t) i2cDevAddr, data, count);

    if (status == STW_SOK)
    {
        /*
         * Generate a stop condition and ensure the
         * bus is free before returning.
         */
        I2CMasterStop(baseAddress);

        status = SblUtilsI2cWaitForFlags(i2cNum,
                                         I2C_INT_BUS_FREE |
                                         I2C_INT_ADRR_READY_ACESS);

        I2CFlushFifo(baseAddress);

        /* Clear the data count and all the flags. */
        I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
        I2CSetDataCount(baseAddress, (uint32_t) 0U);
    }
    return status;
}

static int32_t SblUtilsI2cRead(uint32_t i2cNum,
                               uint8_t  slaveAddr,
                               uint8_t *value)
{
    int32_t  status      = STW_SOK;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /* Set the slave address */
    I2CMasterSlaveAddrSet(baseAddress,
                          (uint32_t) slaveAddr);

    /* Configure to read 1 data word from the PMIC register.  */
    I2CSetDataCount(baseAddress, (uint32_t) 1U);

    /*
     * Configure i2c as master-receive and enable.
     * Make sure stop condition is generated after the transaction.
     */
    I2CMasterControl(baseAddress,
                     (uint32_t) (I2C_CFG_MST_RX | I2C_CFG_START | I2C_CFG_STOP));

    /* Read the data if the data is ready. */
    status = SblUtilsI2cCheckXfrStatus(i2cNum,
                                       (uint32_t) SBL_UTILS_I2C_READ);
    if (status == STW_SOK)
    {
        *value = I2CMasterDataGet(baseAddress);
    }
    else
    {
        *value = 0U;
    }

    /* Wait for I2C access ready before returning. */
    if (status == STW_SOK)
    {
        uint32_t flags = I2C_INT_ADRR_READY_ACESS |
                         I2C_INT_BUS_FREE;
        status = SblUtilsI2cWaitForFlags(i2cNum, flags);
    }

    /* Clear the status of the I2C  */
    I2CFlushFifo(baseAddress);
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);
    I2CSetDataCount(baseAddress, (uint32_t) 0U);

    return status;
}

static int32_t SblUtilsI2cWrite(uint32_t i2cNum,
                                uint8_t slaveAddr, const uint8_t data[],
                                uint8_t count)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint8_t  i;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    status = SblUtilsI2cWaitForBB(i2cNum);

    if (status == STW_SOK)
    {
        /* Set the slave address */
        I2CMasterSlaveAddrSet(baseAddress,
                              (uint32_t) slaveAddr);

        /* Configure to send 'count' data words */
        I2CSetDataCount(baseAddress, (uint32_t) count);

        /*
         * Configure i2c as master-transmitter, enable and set start condition.
         * Stop condition is NOT generated as this could be a part of write
         * followed by read (combined format).
         */
        I2CMasterControl(baseAddress,
                         I2C_CFG_MST_TX | I2C_CFG_START);

        /* Transmit 'count' bytes.  */
        for (i = 0; ((i < count) && (status == STW_SOK)); i++)
        {
            /*
             * Check the status to see if the data can be transferred and
             * send data.
             */
            status = SblUtilsI2cCheckXfrStatus(
                i2cNum,
                (uint32_t)
                SBL_UTILS_I2C_WRITE);
            if (status == PM_SUCCESS)
            {
                I2CMasterDataPut(baseAddress, data[i]);
            }

            /* Clear XRDY flags */
            rawSt = I2CMasterIntRawStatus(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_TRANSMIT_READY);
        }

        /*
         * Once we complete writing the 'count' bytes, wait for the
         * ARDY flag to be set. This flag indicates that the I2C
         * is access ready for next transmission. ARDY can also be
         * set if we received NACK so ensure it is not the case.
         */
        if (status == STW_SOK)
        {
            status = SblUtilsI2cWaitForFlags(i2cNum, I2C_INT_ADRR_READY_ACESS);
            if (status == STW_SOK)
            {
                rawSt = I2CMasterIntRawStatus(baseAddress);
                if ((rawSt & I2C_INT_NO_ACK) != 0)
                {
                    status = STW_EFAIL;
                    /* Clear the NACK flag. */
                    I2CMasterIntClearEx(baseAddress,
                                        rawSt & I2C_INT_NO_ACK);
                }

                /* Clear the ARDY flag. */
                I2CMasterIntClearEx(baseAddress,
                                    rawSt & I2C_INT_ADRR_READY_ACESS);
            }
        }
    }

    return status;
}

static int32_t SblUtilsI2cCheckXfrStatus(uint32_t i2cNum, uint32_t xfr)
{
    int32_t  status = STW_SOK;
    uint32_t rawSt;
    uint32_t flags = I2C_INT_ADRR_READY_ACESS | I2C_INT_NO_ACK |
                     I2C_INT_ARBITRATION_LOST;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    if (xfr == SBL_UTILS_I2C_WRITE)
    {
        flags |= I2C_INT_TRANSMIT_READY;
    }
    else if (xfr == SBL_UTILS_I2C_READ)
    {
        flags |= I2C_INT_RECV_READY;
    }
    else
    {
        status = STW_EFAIL;
    }

    /*
     * Wait for any of the following conditions to occur and
     * handle them in the loop before transmitting data.
     * NACK, AL, XRDY/RRDY, ARDY
     */
    if (status == STW_SOK)
    {
        status = SblUtilsI2cWaitForFlags(i2cNum, flags);
    }

    if (status == STW_SOK)
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);

        /*
         * When I2C is configured as master-transmitter and didn't
         * receive ACK from slave, NACK condition is generated. The
         * following could cause this situation:
         * 1. No receiver is present on the bus with the transmitted
         *    address; board issue
         * 2. Receiver is not ready to communicate with the master
         *    (probably a board/pmic device issue).
         * 3. Receiver gets data or commands it doesn't understand
         *    (incorrect PMIC)
         * 4. Receiver can't receive any more data bytes.
         *
         * NACK can be handled by a master by either generating a
         * STOP condition or a repeated START condition to start
         * a new transfer. In PMIC COMM we generate a STOP
         * condition to abort the transfer and clear the NACK
         * flag.
         *
         * I2C HW clears STT and STP bits in I2C_CON registers.
         */
        if ((rawSt & I2C_INT_NO_ACK) != 0)
        {
            I2CMasterStop(baseAddress);
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_NO_ACK);
            status = STW_EFAIL;
        }
        /*
         * Arbitration loss occurs when multiple masters initiate
         * transfer at the same time. Only one master wins and others
         * loose the arbitration. The arbitration loss flag is set
         * if this local host lost the arbitration. After an
         * arbitration loss, the local host can continue to generate
         * clock till the end of the byte transfer on the bus and
         * must restart the transmission. Recovering from arbitration
         * loss slightly complicates the code and this can be added
         * if there is a need. At present we clear the flag  and
         * return error.
         *
         * When arbitration loss occurs, the I2C HW clears the
         * STT, STP and MST bits. The local host switches to the
         * slave mode.
         */
        else if ((rawSt & I2C_INT_ARBITRATION_LOST) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ARBITRATION_LOST);
            status = STW_EFAIL;
        }
        /*
         * ARDY flag is set to indicate that the local host is access
         * ready. We are in the middle of a data transfer and hence
         * it is bad if we get ARDY flag set. For example, if we
         * get NACKed, the ARDY flag is set in the middle of data
         * transfer.
         */
        else if ((rawSt & I2C_INT_ADRR_READY_ACESS) != 0)
        {
            I2CMasterIntClearEx(baseAddress,
                                rawSt & I2C_INT_ADRR_READY_ACESS);
            status = STW_EFAIL;
        }
        /*
         * XRDY flag is set when the TX FIFO is empty or the TX FIFO
         * threshold is not reached. This means the local host can
         * transmit now.
         *
         * RRDY flag is set when the RX FIFO is empty or the RX FIFO
         * threshold is not reached. This means the local host can
         * receive now.
         */
        else if (((xfr == SBL_UTILS_I2C_WRITE) &&
                  ((rawSt & I2C_INT_TRANSMIT_READY) != 0)) ||
                 ((xfr == SBL_UTILS_I2C_READ) &&
                  ((rawSt & I2C_INT_RECV_READY) != 0)))
        {
            /*
             * Return success so that the caller can send/receive the data
             * Note that the caller needs to clear the XRDY/RRDY flag as
             * needed.
             */
            status = STW_SOK;
        }
        else
        {
            /*
             * We should not get here...
             */
            status = STW_EFAIL;
        }
    }

    return status;
}

static int32_t SblUtilsI2cWaitForFlags(uint32_t i2cNum, uint32_t flags)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t rawSt;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    timeout = SBL_UTILS_I2C_TIMEOUT_COUNT;

    rawSt = I2CMasterIntRawStatus(baseAddress);

    while (((rawSt & flags) == 0) && (timeout > 0U))
    {
        rawSt = I2CMasterIntRawStatus(baseAddress);
        timeout--;
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    return status;
}

static int32_t SblUtilsI2cWaitForBB(uint32_t i2cNum)
{
    int32_t  status = STW_SOK;
    uint32_t timeout;
    uint32_t baseAddress = (i2cNum == 0U) ? (SOC_I2C1_BASE) : (SOC_I2C2_BASE);

    /*
     * Clear all current interrupts first.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    /*
     * Poll the BUS BUSY bit to ensure the bus is not busy before initiating
     * the transaction on the bus.
     */
    for (timeout = SBL_UTILS_I2C_TIMEOUT_COUNT; timeout > 0U; --timeout)
    {
        if (I2CMasterBusBusy(baseAddress) == 0)
        {
            break;
        }
        I2CMasterIntClearEx(baseAddress, I2C_INT_BUS_BUSY);
    }

    if (timeout == 0U)
    {
        status = STW_EFAIL;
    }

    /*
     * Clear all current interrupts.
     */
    I2CMasterIntClearEx(baseAddress, I2C_INT_ALL);

    return status;
}

static void SBLUtilsPreFillECCMemory(void       *eccMemStartAddr,
                                     const void *srcBuffAddr,
                                     uint32_t    memSize)
{
    EDMA3CCPaRAMEntry edmaParams;
    uint32_t          edmaACnt, edmaBCnt, edmaCCnt;
    uint32_t          edmaChannelNum = 1U, edmaTccNum = 1U;
    uint32_t          edmaEvtqNum    = 0U, paramSetNum = 1U;
    uint32_t          tempdataSize   = memSize;
    uint32_t          remDataSize    = 0U, maxBCnt = 0xFFU;
    uint32_t          index, remBytes = 0U;

    /*
     * EDMA transfer is of type AB synchronized for better throughput.
     * Set ACnt as 128 bytes and calculate BCnt & CCnt.
     */
    /* remDataSize takes care of data which is multiple of 128 bytes and
     * remBytes take of the remaining Bytes
     */
    edmaACnt = 128U;
    edmaBCnt = tempdataSize / edmaACnt;
    remBytes = tempdataSize % edmaACnt;
    edmaCCnt = 1U;
    if (edmaBCnt > maxBCnt)
    {
        edmaCCnt    = tempdataSize / (maxBCnt * edmaACnt);
        edmaBCnt    = maxBCnt;
        remDataSize = tempdataSize - (edmaACnt * (edmaBCnt * edmaCCnt));
    }

    /* Request EDMA Channel */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNum,
                        edmaTccNum,
                        edmaEvtqNum);

    /* Set EDMA parameters */
    edmaParams.opt      = 0U;
    edmaParams.srcAddr  = (uint32_t) srcBuffAddr;
    edmaParams.destAddr = (uint32_t) eccMemStartAddr;
    edmaParams.aCnt     = edmaACnt;
    edmaParams.bCnt     = edmaBCnt;
    edmaParams.cCnt     = edmaCCnt;
    edmaParams.srcBIdx  = 0U;
    edmaParams.destBIdx = edmaACnt;
    edmaParams.srcCIdx  = 0U;
    edmaParams.destCIdx = edmaACnt * edmaBCnt;
    edmaParams.linkAddr = 0xFFFFU;
    /* Program the TCC */
    edmaParams.opt |=
        ((edmaTccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK);
    /* Enable Intermediate & Final transfer completion interrupt */
    edmaParams.opt |= (EDMA3_OPT_ITCINTEN_MASK);
    edmaParams.opt |= (EDMA3_OPT_TCINTEN_MASK);
    /* AB Sync Transfer Mode */
    edmaParams.opt |= EDMA_TPCC_OPT_SYNCDIM_MASK;

    /* Map Param Set to Channel */
    EDMA3ChannelToParamMap(SOC_EDMA_TPCC_BASE, edmaChannelNum, paramSetNum);

    /* Set Params in EDMA registers */
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, paramSetNum, &edmaParams);

    /*
     * Transfer is done in AB sync mode
     * Number of triggers required are edmaCCnt
     */
    for (index = 0U; index < edmaCCnt; index++)
    {
        /* Enable transfer manually */
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE,
                            edmaChannelNum,
                            EDMA3_TRIG_MODE_MANUAL);

        /* Wait for transfer to complete */
        while (((uint32_t) 0x1U << edmaTccNum) !=
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                ((uint32_t) 0x1U << edmaTccNum)))
        {
            /* Busy Loop */
        }

        /* Clear EDMA completion interrupt */
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaTccNum);
    }

    if (0U != remDataSize)
    {
        edmaParams.opt      = 0U;
        edmaParams.srcAddr  = (uint32_t) srcBuffAddr;
        edmaParams.destAddr = (uint32_t) eccMemStartAddr +
                              ((edmaACnt * edmaBCnt) * edmaCCnt);
        edmaParams.aCnt     = edmaACnt;
        edmaParams.bCnt     = remDataSize / edmaACnt;
        edmaParams.cCnt     = 1U;
        edmaParams.srcBIdx  = 0U;
        edmaParams.destBIdx = edmaACnt;
        edmaParams.srcCIdx  = 0U;
        edmaParams.destCIdx = 0U;
        edmaParams.linkAddr = 0xFFFFU;
        edmaParams.opt      =
            (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
             EDMA3_OPT_ITCINTEN_MASK |
             ((edmaTccNum << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, paramSetNum, &edmaParams);

        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edmaChannelNum,
                            EDMA3_TRIG_MODE_MANUAL);

        while (((uint32_t) 0x1U << edmaTccNum) !=
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                ((uint32_t) 0x1U << edmaTccNum)))
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaTccNum);
    }

    if (0U != remBytes)
    {
        edmaParams.opt      = 0U;
        edmaParams.srcAddr  = (uint32_t) srcBuffAddr;
        edmaParams.destAddr = (uint32_t) eccMemStartAddr +
                              ((edmaACnt * edmaBCnt) * edmaCCnt) +
                              (edmaParams.aCnt * edmaParams.bCnt);
        edmaParams.aCnt     = remBytes;
        edmaParams.bCnt     = 1U;
        edmaParams.cCnt     = 1U;
        edmaParams.srcBIdx  = 0U;
        edmaParams.destBIdx = 0U;
        edmaParams.srcCIdx  = 0U;
        edmaParams.destCIdx = 0U;
        edmaParams.linkAddr = 0xFFFFU;
        edmaParams.opt      =
            (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
             EDMA3_OPT_ITCINTEN_MASK |
             ((edmaTccNum << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, paramSetNum, &edmaParams);

        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edmaChannelNum,
                            EDMA3_TRIG_MODE_MANUAL);

        while (((uint32_t) 0x1U << edmaTccNum) !=
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                ((uint32_t) 0x1U << edmaTccNum)))
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edmaTccNum);
    }
}

