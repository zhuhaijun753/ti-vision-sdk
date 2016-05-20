/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
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

/*
 * main.c
 */
#include <stdio.h>
#include "stdint.h"
#include <common/stw_types.h>
#include <common/stw_dataTypes.h>
#include "soc_defines.h"
#include "soc.h"
#include "uartStdio.h"
#include "interrupt.h"
#include "platform.h"
#include "stw_platformEcc.h"
#include "irq_xbar.h"
#include "hw_types.h"
#include "hw_emif.h"
#include "ocmc_ecc_l1.h"
#include "emif.h"
#include "edma.h"
#include "hw_ipu_unicache_cfg.h"
#include "hw_ipu_unicache_mmu.h"

#if defined (BUILD_A15)
#include "cache_a15.h"
#endif

#ifdef TDA3XX_FAMILY_BUILD
#include "ipu_ecc.h"
#include "unicache.h"
#endif

#ifdef TDA3XX_FAMILY_BUILD
#define IPU_ECC_TEST                   ('3')

#define IPU_L2RAM_SEC_ERR_TEST         ('1')
#define IPU_L2RAM_DED_ERR_TEST         ('2')
#define IPU_L1DATA_SEC_ERR_TEST        ('3')
#define IPU_L1DATA_DED_ERR_TEST        ('4')

/** \brief IPU instance used */
#define IPU_APP_INST                      (SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE)
#define IPU_L2RAM_ECC_START_ADDR                (0x55020000)
#define IPU_L2RAM_ECC_END_ADDR                  (0x55030000)

#define IPU_L1DATA_ECC_START_ADDR               (0x90000000)
#define IPU_L1DATA_ECC_END_ADDR                 (0x90008000)

#define IPU_L2RAM_SEC_ERR_INT             (84U)
#define IPU_L1DATA_SEC_ERR_INT            (82U)

#define IPU_L2RAM_ECC_TEST_ADDR               (0x55024015)
#define IPU_L1DATA_ECC_TEST_ADDR              (0x90000014)

#endif

#define EMIF_ECC_TEST                  ('1')
#define OCMC_RAM_ECC_TEST              ('2')

#define EMIF_ECC_NON_QUANTA_ALIGN_ADDR_ERR_TEST                          ('1')
#define EMIF_ECC_BYTECOUNT_WRITEACCESS_NOTMULTIPLE_ECCQUANTA_ERR_TEST    ('2')
#define EMIF_ECC_SEC_ERR_TEST                                            ('3')
#define EMIF_ECC_DED_ERR_TEST                                            ('4')

#define OCMC_RAM_ECC_SEC_TEST                    ('1')
#define OCMC_RAM_ECC_DED_TEST                    ('2')
#define OCMC_RAM_ECC_ADDR_ERR_TEST               ('3')

#define OCMC_RAM_FULL_ECC_MODE                   ('1')
#define OCMC_RAM_BLOCK_ECC_MODE                  ('2')

#define EXIT(opt)      (('x' == opt) || ('X' == opt))

/** \brief EMIF instance used */
#define EMIF_APP_INST                     (SOC_EMIF1_CONF_REGS_BASE)
#define EMIF_START_ADDR                   (0x80000000)
#define EMIF_ECC_START_ADDR               (0x90000000)
#define EMIF_ECC_END_ADDR                 (0x9001FFFF)
/** \brief As Err address log FIFO size is 4 so EMIF_ECC_1B_ERR_THRSH_VAL is set
 *         as 2 to avoid missing of Err address log
 */
#define EMIF_ECC_1B_ERR_THRSH_VAL         (0x2)

#if defined (BUILD_A15)
#define EMIF_ECC_ERR_INT                  (13U)
#elif defined (BUILD_M4)
#define EMIF_ECC_ERR_INT                  (35U)
#endif

#define EMIF_ECC_TEST_ADDR                (EMIF_ECC_START_ADDR + 0x100)
#define EMIF_ECC_TEST_ADDR_1              (EMIF_ECC_START_ADDR + 0x200)
#define EMIF_ECC_TEST_ADDR_2              (EMIF_ECC_START_ADDR + 0x3)

/** \brief OCMC instance used */
#define OCMC_RAM_APP_INST                 (SOC_OCMC_RAM1_CFG_BASE)
#define OCMC_RAM_START_ADDR               (0x40300000)
#define OCMC_RAM_ECC_START_ADDR           (0x40311100)
#define OCMC_RAM_ECC_END_ADDR             (0x403111FF)

#define OCMC_RAM_ECC_1B_ERR_THRSH_VAL     (0x1)
#define OCMC_RAM_ECC_2B_ERR_THRSH_VAL     (0x1)
#define OCMC_RAM_ECC_ADDR_ERR_THRSH_VAL   (0x1)

#if defined (BUILD_A15)
#define OCMC_RAM_ECC_ERR_INT              (24U)
#elif defined (BUILD_M4)
#define OCMC_RAM_ECC_ERR_INT              (25U)
#endif

#define PATTERN_DATA                      (0xFFFFFFFF)
#define L2RAM_PATTERN_DATA                (0xFF)

#define EDMA3_CC_REGION                  (1U)

#if defined (BUILD_M4)
/* EDMA region 0x43300000 mappped to 0xA0000000 */
#define SOC_EDMA_TPCC_BASE               (0x63300000U)
#endif

#define BUFFER_SIZE                      (16)  /*aCnt*bCnt*cCnt */

#define EDMA_APP_INST                    (SOC_EDMA_TPCC_BASE)

#if defined (BUILD_M4)
#define HARD_FAULT_INT                   (EXCEPTION_M4_HARD_FAULT_NUM_3)
#elif defined (BUILD_A15)
#define ABORT_INT                        (160U)
#endif

static void mainMenu(char *option);

#ifdef TDA3XX_FAMILY_BUILD
static void mainSubMenuIpuEccTest(char *option);
int32_t ipuEccTest(void);
static int32_t ipuL2RamSecErrTest(char option);
static int32_t ipuL2RamDedErrTest(char option);
static int32_t ipuL1DataSecErrTest(char option);
static int32_t ipuL1DataDedErrTest(char option);

static void ipuEccConfig(uint32_t memType);
static void ipuEccInit();
void isrIpuL2RamSecErr();
void isrIpuL2RamDedErr();
void isrIpuL1DataSecErr();
void isrIpuL1DataDedErr();

eccIpuMemErrInfo_t gIpuErrInfo;
#endif

static void mainSubMenuEmifEccTest(char *option);
int32_t emifEccTest(void);
static int32_t emifSecErrTest();
static int32_t emifDedErrTest();
static int32_t emifNonEccQuantaAlignAddrErrTest();
static int32_t emifByteCntWRAccessNotMultEccQuantaErrTest();

static void emifEccConfig();
static void emifEccInit(char option);

void isrEmifSecErr();
void isrEmifDedErr();
void isrEmifNonEccQuantaAlignAddrErr();
void isrEmifByteCntWRAccessNotMultEccQuantaErr();

static void mainSubMenuOcmcRamEccTest(char *option, char *mode);

int32_t ocmcRamEccTest(void);
static int32_t ocmcRamSecErrTest(char ocmcEccMode);
static int32_t ocmcRamDedErrTest(char ocmcEccMode);
static int32_t ocmcRamAddrErrTest(char ocmcEccMode);

static int32_t ocmcRamInitEccMem();

void isrOcmcRamSecErr();
void isrOcmcRamDedErr();
void isrOcmcRamAddrErr();

void ipuAmmuConfig(void);

volatile uint32_t  gErrStatus = 0;
emifEccErrInfo_t   gEmifErrInfo;
volatile uint32_t  gEccErrAddr       = 0;
uint32_t           gEccErrBitMask[4] = {0};
uint32_t           gOcmcEccMode;
uint32_t           gOcmcTestVal;

uint32_t           srcBuff[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

#if defined (BUILD_M4)
uint32_t           gInterruptNum = HARD_FAULT_INT;
#elif defined (BUILD_A15)
uint32_t           gInterruptNum = ABORT_INT;
#endif

extern void CPUDisableCPSRABit(void);

volatile uint32_t *gTest_Addr    = NULL;
volatile uint32_t *gTest_Addr1   = NULL;
volatile uint8_t  *gIpuTest_Addr = NULL;
volatile uint32_t  gTestVal      = 0;

int main(void)
{
    volatile uint32_t testDone = 1;
    int32_t           retVal   = STW_SOK;
    char mainMenuOption;

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();

    while (1)
    {
        mainMenu(&mainMenuOption);

        if (EMIF_ECC_TEST == mainMenuOption)
        {
            retVal = emifEccTest();
        }
        else if (OCMC_RAM_ECC_TEST == mainMenuOption)
        {
            retVal = ocmcRamEccTest();
        }
#ifdef TDA3XX_FAMILY_BUILD
        else if (IPU_ECC_TEST == mainMenuOption)
        {
            ipuAmmuConfig();
            retVal = ipuEccTest();
        }
#endif
        else
        {
            UARTPuts("\n  ECC test exiting...", -1);
            break;
        }
    }
    while (testDone) ;
    return retVal;
}

#ifdef TDA3XX_FAMILY_BUILD
int32_t ipuEccTest(void)
{
    int32_t retVal = STW_SOK;
    char    mainSubMenuOption;

    while (1)
    {
        mainSubMenuIpuEccTest(&mainSubMenuOption);

        ipuEccInit();

        if (IPU_L2RAM_SEC_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL2RamSecErrTest(mainSubMenuOption);
        }
        else if (IPU_L2RAM_DED_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL2RamDedErrTest(mainSubMenuOption);
        }
        else if (IPU_L1DATA_SEC_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL1DataSecErrTest(mainSubMenuOption);
        }
        else if (IPU_L1DATA_DED_ERR_TEST == mainSubMenuOption)
        {
            retVal = ipuL1DataDedErrTest(mainSubMenuOption);
        }
        else
        {
            UARTPuts("\n IPU L2RAM ECC test exiting...", -1);
            break;
        }
    }
    return retVal;
}

#endif

static void mainMenu(char *option)
{
    while (1)
    {
        UARTPuts("\n\n**** ECC TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. EMIF ECC TEST", -1);
        UARTPuts("\n2. OCMC RAM ECC TEST", -1);
#ifdef TDA3XX_FAMILY_BUILD
        UARTPuts("\n3. IPU L2RAM ECC TEST", -1);
#endif
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect ECC TEST : ", -1);
        /* Get option */
        UARTGets(option, 1);

        if (EMIF_ECC_TEST == *option ||
            OCMC_RAM_ECC_TEST == *option ||
#ifdef TDA3XX_FAMILY_BUILD
            IPU_ECC_TEST == *option ||
#endif
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

#ifdef TDA3XX_FAMILY_BUILD
static void mainSubMenuIpuEccTest(char *option)
{
    while (1)
    {
        UARTPuts("\n\n**** IPU ECC TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. IPU L2RAM SEC test", -1);
        UARTPuts("\n2. IPU L2RAM DED test", -1);
        UARTPuts("\n3. IPU L1DATA SEC test", -1);
        UARTPuts("\n4. IPU L1DATA DED test", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect IPU ECC TEST : ", -1);
        /* Get option */
        UARTGets(option, 1);

        if (IPU_L2RAM_SEC_ERR_TEST == *option ||
            IPU_L2RAM_DED_ERR_TEST == *option ||
            IPU_L1DATA_SEC_ERR_TEST == *option ||
            IPU_L1DATA_DED_ERR_TEST == *option ||
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

void isrIpuL2RamSecErr()
{
    int32_t retVal = STW_SOK;

    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST, ECC_IPU_MEM_TYPE_L2RAM);
    retVal     = ECCIPUMemGetErrInfo(IPU_APP_INST,
                                     &gIpuErrInfo,
                                     ECC_IPU_MEM_TYPE_L2RAM);
    if (retVal != STW_SOK)
    {
        UARTPuts("\n NULL Pointer Detected : gIpuErrInfo", -1);
    }
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ONEBIT,
                          ECC_IPU_MEM_TYPE_L2RAM);
}

void isrIpuL2RamDedErr()
{
    uint8_t           i;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gIpuTest_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.errIntrEnable        = TRUE;
    cfgPrm.dataMaskEnable       = FALSE;
    cfgPrm.eccCodeMaskEnable    = FALSE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L2RAM;

    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST, ECC_IPU_MEM_TYPE_L2RAM);
    retVal     = ECCIPUMemGetErrInfo(IPU_APP_INST,
                                     &gIpuErrInfo,
                                     ECC_IPU_MEM_TYPE_L2RAM);
    if (retVal != STW_SOK)
    {
        UARTPuts("\n NULL Pointer Detected : gIpuErrInfo", -1);
    }

    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_TWOBIT,
                          ECC_IPU_MEM_TYPE_L2RAM);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    gIpuTest_Addr = (uint8_t *) (gIpuErrInfo.errAddr);
    for (i = 0; i < 8; i++)
    {
        gIpuTest_Addr[i] = L2RAM_PATTERN_DATA;
    }
}

void isrIpuL1DataSecErr()
{
    int32_t retVal = STW_SOK;

    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST, ECC_IPU_MEM_TYPE_L1DATA);
    retVal     = ECCIPUMemGetErrInfo(IPU_APP_INST,
                                     &gIpuErrInfo,
                                     ECC_IPU_MEM_TYPE_L1DATA);
    if (retVal != STW_SOK)
    {
        UARTPuts("\n NULL Pointer Detected : gIpuErrInfo", -1);
    }
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ONEBIT,
                          ECC_IPU_MEM_TYPE_L1DATA);
}

void isrIpuL1DataDedErr()
{
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gTest_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.errIntrEnable        = TRUE;
    cfgPrm.dataMaskEnable       = FALSE;
    cfgPrm.eccCodeMaskEnable    = FALSE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L1DATA;

    gErrStatus = ECCIPUMemGetErrStatus(IPU_APP_INST, ECC_IPU_MEM_TYPE_L1DATA);
    retVal     = ECCIPUMemGetErrInfo(IPU_APP_INST,
                                     &gIpuErrInfo,
                                     ECC_IPU_MEM_TYPE_L1DATA);
    if (retVal != STW_SOK)
    {
        UARTPuts("\n NULL Pointer Detected : gIpuErrInfo", -1);
    }

    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_TWOBIT,
                          ECC_IPU_MEM_TYPE_L1DATA);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    gTest_Addr    = (uint32_t *) (gIpuErrInfo.errAddr);
    gTest_Addr[0] = PATTERN_DATA;
}

static void ipuEccInit()
{
    /* Clear older IPU L2RAM ECC Err status */
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L2RAM);

    /* Clear older IPU L1DATA ECC Err status */
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1DATA);

    /* Clear older IPU L1TAG ECC Err status */
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1TAG);

    /* Disable ECC for IPU L2RAM */
    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L2RAM);

    /* Disable ECC for IPU L1DATA */
    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1DATA);

    /* Disable ECC for IPU L1TAG */
    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1TAG);
}

static void ipuEccConfig(uint32_t memType)
{
    uint32_t i;

    UNICACHEInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    UNICACHEEnable(IPU_APP_INST);

    /* Enable ECC for IPU L2RAM / L1DATA / L1TAG */
    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L2RAM);
    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L1DATA);
    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L1TAG);

    if (memType == ECC_IPU_MEM_TYPE_L1DATA)
    {
        for (i = IPU_L1DATA_ECC_START_ADDR; i < IPU_L1DATA_ECC_END_ADDR; i += 4)
        {
            *(uint32_t *) i = PATTERN_DATA;
        }
    }
    else
    {
        for (i = IPU_L2RAM_ECC_START_ADDR; i < IPU_L2RAM_ECC_END_ADDR; i += 4)
        {
            *(uint32_t *) i = PATTERN_DATA;
        }
    }

    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    /* Clear IPU L2RAM/ L1DATA / L1TAG ECC Err status which is caused during
     * intialisation*/
    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L2RAM);

    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1DATA);

    ECCIPUMemClrErrStatus(IPU_APP_INST,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1TAG);
}

static int32_t ipuL2RamSecErrTest(char option)
{
    uint8_t           testVal, i;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus    = 0;
    gIpuTest_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = TRUE;
    cfgPrm.errIntrEnable        = FALSE;
    cfgPrm.dataMaskEnable       = FALSE;
    cfgPrm.eccCodeMaskEnable    = FALSE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L2RAM;

    /* Enable The L2 RAM SEC ERR interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(IPU_L2RAM_SEC_ERR_INT, (IntrFuncPtr) isrIpuL2RamSecErr,
                     NULL);

    Intc_IntPrioritySet(IPU_L2RAM_SEC_ERR_INT, 1, 0);
    Intc_SystemEnable(IPU_L2RAM_SEC_ERR_INT);

    ipuEccConfig(ECC_IPU_MEM_TYPE_L2RAM);

    UNICACHEDisable(IPU_APP_INST);
    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    gIpuTest_Addr = (uint8_t *) (IPU_L2RAM_ECC_TEST_ADDR);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L2RAM);

    testVal          = gIpuTest_Addr[0];
    testVal          = testVal & 0xEF;
    gIpuTest_Addr[0] = testVal;

    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L2RAM);

    testVal = gIpuTest_Addr[0];

    while (gErrStatus == 0) ;

    /* Disable the interrupt */
    Intc_SystemDisable(IPU_L2RAM_SEC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_L2RAM_SEC_ERR_INT);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\nECC -- SEC ERR Test Fail!! \n", -1);
    }
    else
    {
        UARTPuts("\nECC -- SEC ERR Test Pass!! \n", -1);
        UARTPuts("\nECC -- SEC ERR Occured at Address \n ", -1);
        for (i = 0; i < 8; i++)
        {
            UARTPutHexNum(gIpuErrInfo.errAddr + i);
            UARTPuts("\n", -1);
        }
        /* UARTPuts("\nECC -- 1BIT ERR Occured at Bit Mask : ", -1);*/
        /* UARTPutHexNum(gIpuErrInfo.errBitLoc); */
    }

    return retVal;
}

static int32_t ipuL2RamDedErrTest(char option)
{
    uint8_t           testVal, i;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus    = 0;
    gIpuTest_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.errIntrEnable        = TRUE;
    cfgPrm.dataMaskEnable       = FALSE;
    cfgPrm.eccCodeMaskEnable    = TRUE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L2RAM;

    Intc_Init();
    Intc_IntEnable(0);

    /* Register The HF interrupt */
    Intc_IntRegister(gInterruptNum,
                     (IntrFuncPtr) isrIpuL2RamDedErr,
                     NULL);

    ipuEccConfig(ECC_IPU_MEM_TYPE_L2RAM);

    UNICACHEDisable(IPU_APP_INST);
    UNICACHEWriteBackAndInvalidateAll(IPU_APP_INST, UNICACHE_WAIT_INFINITE);

    gIpuTest_Addr = (uint8_t *) (IPU_L2RAM_ECC_TEST_ADDR);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    testVal          = gIpuTest_Addr[0];
    testVal          = testVal & 0xCF;
    gIpuTest_Addr[0] = testVal;

    testVal = gIpuTest_Addr[0];

    while (gErrStatus == 0) ;

    /* Unregister the interrupt */
    Intc_IntUnregister(gInterruptNum);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\nECC -- DED ERR Test Fail!! \n", -1);
    }
    else
    {
        UARTPuts("\nECC -- DED ERR Test Pass!! \n", -1);
        UARTPuts("\nECC -- DED ERR Occured at Address \n ", -1);
        for (i = 0; i < 8; i++)
        {
            UARTPutHexNum(gIpuErrInfo.errAddr + i);
            UARTPuts("\n", -1);
        }
    }

    return retVal;
}

static int32_t ipuL1DataSecErrTest(char option)
{
    uint32_t          testVal;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus = 0;
    gTest_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = TRUE;
    cfgPrm.errIntrEnable        = FALSE;
    cfgPrm.dataMaskEnable       = FALSE;
    cfgPrm.eccCodeMaskEnable    = FALSE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L1DATA;

    /* Enable The L2 RAM SEC ERR interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(IPU_L1DATA_SEC_ERR_INT, (IntrFuncPtr) isrIpuL1DataSecErr,
                     NULL);

    Intc_IntPrioritySet(IPU_L1DATA_SEC_ERR_INT, 1, 0);
    Intc_SystemEnable(IPU_L1DATA_SEC_ERR_INT);

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1DATA);

    gTest_Addr = (uint32_t *) (IPU_L1DATA_ECC_TEST_ADDR);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    ECCIPUMemEnableEcc(IPU_APP_INST, FALSE, ECC_IPU_MEM_TYPE_L1DATA);

    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFEFFFF;
    gTest_Addr[0] = testVal;

    ECCIPUMemEnableEcc(IPU_APP_INST, TRUE, ECC_IPU_MEM_TYPE_L1DATA);

    testVal = gTest_Addr[0];

    while (gErrStatus == 0) ;

    /* Disable the interrupt */
    Intc_SystemDisable(IPU_L1DATA_SEC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(IPU_L1DATA_SEC_ERR_INT);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\nECC -- SEC ERR Test Fail!! \n", -1);
    }
    else
    {
        UARTPuts("\nECC -- SEC ERR Test Pass!! \n", -1);
        UARTPuts("\nECC -- SEC ERR Occured at Address \n ", -1);
        UARTPutHexNum(gIpuErrInfo.errAddr);
        UARTPuts("\n", -1);
        /* UARTPuts("\nECC -- 1BIT ERR Occured at Bit Mask : ", -1);*/
        /* UARTPutHexNum(gIpuErrInfo.errBitLoc);*/
    }

    return retVal;
}

static int32_t ipuL1DataDedErrTest(char option)
{
    uint32_t          testVal;
    int32_t           retVal = STW_SOK;
    eccIpuMemCfgPrm_t cfgPrm;

    gErrStatus = 0;
    gTest_Addr = NULL;

    cfgPrm.errAutoCorrectEnable = FALSE;
    cfgPrm.errIntrEnable        = TRUE;
    cfgPrm.dataMaskEnable       = TRUE;
    cfgPrm.eccCodeMaskEnable    = FALSE;
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L1DATA;

    Intc_Init();
    Intc_IntEnable(0);

    /* Register The HF interrupt */
    Intc_IntRegister(gInterruptNum,
                     (IntrFuncPtr) isrIpuL1DataDedErr,
                     NULL);

    ipuEccConfig(ECC_IPU_MEM_TYPE_L1DATA);

    gTest_Addr = (uint32_t *) (IPU_L1DATA_ECC_TEST_ADDR);

    ECCIPUMemConfig(IPU_APP_INST, (const eccIpuMemCfgPrm_t *) &cfgPrm);

    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFCFFFF;
    gTest_Addr[0] = testVal;

    testVal = gTest_Addr[0];

    while (gErrStatus == 0) ;

    /* Unregister the interrupt */
    Intc_IntUnregister(gInterruptNum);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\nECC -- DED ERR Test Fail!! \n", -1);
    }
    else
    {
        UARTPuts("\nECC -- DED ERR Test Pass!! \n", -1);
        UARTPuts("\nECC -- DED ERR Occured at Address \n ", -1);
        UARTPutHexNum(gIpuErrInfo.errAddr);
        UARTPuts("\n", -1);
    }

    return retVal;
}

#endif

void isrEmifSecErr()
{
    int32_t retVal = STW_SOK;
    gErrStatus = EMIFGetIntrStatus(EMIF_APP_INST);
    retVal     = EMIFConfigECCGetEccErrInfo(EMIF_APP_INST,
                                            EMIF_ERR_ECC_ONEBIT,
                                            &gEmifErrInfo);
    if (retVal != STW_SOK)
    {
        UARTPuts("\n NULL Pointer Detected : gEmifErrInfo", -1);
    }

    EMIFClearIntrStatus(
        EMIF_APP_INST,
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_MASK);
}

void isrEmifDedErr()
{
    int32_t retVal = STW_SOK;

    gTest_Addr = NULL;

    gErrStatus = EMIFGetIntrStatus(EMIF_APP_INST);
    retVal     = EMIFConfigECCGetEccErrInfo(EMIF_APP_INST,
                                            EMIF_ERR_ECC_TWOBIT,
                                            &gEmifErrInfo);
    if (retVal != STW_SOK)
    {
        UARTPuts("\n NULL Pointer Detected : gEmifErrInfo", -1);
    }

    EMIFClearIntrStatus(
        EMIF_APP_INST,
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_TWOBIT_ECC_ERR_SYS_MASK);
    EMIFConfigECCDisableEcc(EMIF_APP_INST);
    gTest_Addr    = (uint32_t *) (gEmifErrInfo.errAddr[0] + EMIF_START_ADDR);
    gTest_Addr[0] = PATTERN_DATA;
    EMIFConfigECCEnableEcc(EMIF_APP_INST);
}

void isrEmifNonEccQuantaAlignAddrErr()
{
    gErrStatus = EMIFGetIntrStatus(EMIF_APP_INST);
    EMIFClearIntrStatus(
        EMIF_APP_INST,
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_WR_ECC_ERR_SYS_MASK);
}

void isrEmifByteCntWRAccessNotMultEccQuantaErr()
{
    gErrStatus = EMIFGetIntrStatus(EMIF_APP_INST);
    EMIFClearIntrStatus(
        EMIF_APP_INST,
        EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_WR_ECC_ERR_SYS_MASK);
}

static void mainSubMenuEmifEccTest(char *option)
{
    while (1)
    {
        UARTPuts("\n\n**** EMIF ECC TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. EMIF NON ECC QUANTA ALIGNED ADDRESS test", -1);
        UARTPuts(
            "\n2. EMIF BYTE COUNT WRITE ACCESS NOT MULTIPLE OF ECC QUANTA test",
            -1);
        UARTPuts("\n3. EMIF SEC ERR ECC test", -1);
        UARTPuts("\n4. EMIF DED ERR ECC test", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect EMIF ECC TEST : ", -1);
        /* Get option */
        UARTGets(option, 1);

        if (EMIF_ECC_SEC_ERR_TEST == *option ||
            EMIF_ECC_DED_ERR_TEST == *option ||
            EMIF_ECC_NON_QUANTA_ALIGN_ADDR_ERR_TEST == *option ||
            EMIF_ECC_BYTECOUNT_WRITEACCESS_NOTMULTIPLE_ECCQUANTA_ERR_TEST
            == *option || EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

int32_t emifEccTest(void)
{
    int32_t retVal = STW_SOK;
    char    mainSubMenuOption;

    while (1)
    {
        mainSubMenuEmifEccTest(&mainSubMenuOption);

        emifEccInit(mainSubMenuOption);

        if (EMIF_ECC_NON_QUANTA_ALIGN_ADDR_ERR_TEST == mainSubMenuOption)
        {
            retVal = emifNonEccQuantaAlignAddrErrTest();
        }
        else if (EMIF_ECC_BYTECOUNT_WRITEACCESS_NOTMULTIPLE_ECCQUANTA_ERR_TEST
                 == mainSubMenuOption)
        {
            retVal = emifByteCntWRAccessNotMultEccQuantaErrTest();
        }
        else if (EMIF_ECC_SEC_ERR_TEST == mainSubMenuOption)
        {
            retVal = emifSecErrTest();
        }
        else if (EMIF_ECC_DED_ERR_TEST == mainSubMenuOption)
        {
            retVal = emifDedErrTest();
        }
        else
        {
            UARTPuts("\nEMIF ECC test exiting...", -1);
            break;
        }
    }
    return retVal;
}

static void emifEccInit(char option)
{
    emifEccCfgPrm_t          cfgPrm;
    int32_t                  retVal = STW_SOK;
    emifEccAddrRangeCfgPrm_t addrRangeCfgPrm;

    cfgPrm.addrRangeCfgPrm = &addrRangeCfgPrm;

    cfgPrm.emifStartAddr = EMIF_START_ADDR;
    cfgPrm.addrRangeCfgPrm->startAddr       = EMIF_ECC_START_ADDR;
    cfgPrm.addrRangeCfgPrm->endAddr         = EMIF_ECC_END_ADDR;
    cfgPrm.addrRangeCfgPrm->addrRangeNum    = EMIF_ECC_ADDR_RANGE_NUM_1;
    cfgPrm.addrRangeCfgPrm->addrRangeType   = EMIF_ECC_ADDR_RANGE_WITHIN;
    cfgPrm.addrRangeCfgPrm->enableAddrRange = FALSE;
    cfgPrm.thresholdVal = EMIF_ECC_1B_ERR_THRSH_VAL;

#if defined (BUILD_M4)
    /* Disable cache to ensure writes are completed */
    HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE + IPU_UNICACHE_CONFIG,
                  IPU_UNICACHE_CONFIG_BYPASS,
                  IPU_UNICACHE_CONFIG_BYPASS_BYPASS);

    if ((option == EMIF_ECC_NON_QUANTA_ALIGN_ADDR_ERR_TEST) ||
        (option
         == EMIF_ECC_BYTECOUNT_WRITEACCESS_NOTMULTIPLE_ECCQUANTA_ERR_TEST))
    {
        /* To disable L1 cache, posted and write policy
         * which is enabled in gel by default
         */
        HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_BASE + IPU_LARGE_POLICY(1U),
                      IPU_LARGE_POLICY_L1_CACHEABLE,
                      IPU_LARGE_POLICY_L1_CACHEABLE_DISABLE);

        HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_BASE + IPU_LARGE_POLICY(1U),
                      IPU_LARGE_POLICY_L1_POSTED,
                      IPU_LARGE_POLICY_L1_POSTED_NON_POSTED);

        HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_BASE + IPU_LARGE_POLICY(1U),
                      IPU_LARGE_POLICY_L1_WR_POLICY,
                      IPU_LARGE_POLICY_L1_WR_POLICY_WT);
    }
#endif

    /* Clear older EMIF interrupts */

    EMIFClearIntrStatus(EMIF_APP_INST, EMIF_INTR_ALL);

    retVal = EMIFConfigECCInitECCParams(EMIF_APP_INST, &cfgPrm);
    if (retVal != STW_SOK)
    {
        UARTPuts("\n NULL Pointer Detected : cfgPrm", -1);
    }

    EMIFConfigECCDisableEcc(EMIF_APP_INST);
}

static void emifEccConfig()
{
    uint32_t                 i;
    int32_t                  retVal = STW_SOK;
    emifEccCfgPrm_t          cfgPrm;
    emifEccAddrRangeCfgPrm_t addrRangeCfgPrm;

    cfgPrm.addrRangeCfgPrm = &addrRangeCfgPrm;

    cfgPrm.emifStartAddr = EMIF_START_ADDR;
    cfgPrm.addrRangeCfgPrm->startAddr       = EMIF_ECC_START_ADDR;
    cfgPrm.addrRangeCfgPrm->endAddr         = EMIF_ECC_END_ADDR;
    cfgPrm.addrRangeCfgPrm->addrRangeNum    = EMIF_ECC_ADDR_RANGE_NUM_1;
    cfgPrm.addrRangeCfgPrm->addrRangeType   = EMIF_ECC_ADDR_RANGE_WITHIN;
    cfgPrm.addrRangeCfgPrm->enableAddrRange = TRUE;
    cfgPrm.thresholdVal = EMIF_ECC_1B_ERR_THRSH_VAL;

    if (EMIF_ECC_1B_ERR_THRSH_VAL > EMIF_ECC_FIFO_BUF_SIZE)
    {
        UARTPuts
            ("\nEMIF ECC FIFO Err address log buffer will get overflowed", -1);
    }

    /* Before configuring ECC EMIF, make sure ECC is enabled in
     * CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT ctrl module register as this will be
     * done in GEL files / SBL before doing EMIF configuration
     */

    retVal = EMIFConfigECCInitECCParams(EMIF_APP_INST, &cfgPrm);

    if (retVal != STW_SOK)
    {
        UARTPuts("\n NULL Pointer Detected : cfgPrm", -1);
    }

    EMIFConfigECCEnableEcc(EMIF_APP_INST);

    for (i = EMIF_ECC_START_ADDR; i < EMIF_ECC_END_ADDR; i += 4)
    {
        *(uint32_t *) i = PATTERN_DATA;
    }
}

static int32_t emifSecErrTest()
{
    uint32_t testVal, fifoIdx = 0;
    int32_t  retVal = STW_SOK;

    gErrStatus  = 0;
    gTest_Addr  = NULL;
    gTest_Addr1 = NULL;

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

#if defined (BUILD_M4)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1, 13,
                   EMIF1_IRQ);
#elif defined (BUILD_A15)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS, 8,
                   EMIF1_IRQ);
#endif

    /* Enable The EMIF interrupt */
    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(EMIF_ECC_ERR_INT, (IntrFuncPtr) isrEmifSecErr, NULL);

    Intc_IntPrioritySet(EMIF_ECC_ERR_INT, 1, 0);
    Intc_SystemEnable(EMIF_ECC_ERR_INT);

    emifEccConfig();

    gTest_Addr  = (uint32_t *) (EMIF_ECC_TEST_ADDR);
    gTest_Addr1 = (uint32_t *) (EMIF_ECC_TEST_ADDR_1);

    EMIFEnableIntr(EMIF_APP_INST,
                   EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET_ONEBIT_ECC_ERR_SYS_MASK);

    EMIFConfigECCClrAllEccErrInfo(EMIF_APP_INST);

    EMIFConfigECCDisableEcc(EMIF_APP_INST);

    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFEFFFF;
    gTest_Addr[0] = testVal;

    testVal        = gTest_Addr1[0];
    testVal        = testVal & 0xEFFFFFFF;
    gTest_Addr1[0] = testVal;

    EMIFConfigECCEnableEcc(EMIF_APP_INST);

    testVal = gTest_Addr[0];
    testVal = gTest_Addr1[0];

    while (gErrStatus == 0) ;

    /* Disable the interrupt */
    Intc_SystemDisable(EMIF_ECC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(EMIF_ECC_ERR_INT);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\n EMIF ECC -- SEC ERR Test Fail!! ", -1);
    }
    else
    {
        UARTPuts("\nEMIF ECC -- SEC ERR Test Pass!! ", -1);
        UARTPuts("\nEMIF ECC -- SEC ERR Occured at Address \n ", -1);
        while (gEmifErrInfo.numValidErrAddr--)
        {
            UARTPutHexNum((gEmifErrInfo.errAddr[fifoIdx] + EMIF_START_ADDR));
            UARTPuts("\n", -1);
            fifoIdx++;
        }
        UARTPuts("\n EMIF ECC -- SEC ERR Occured at Bit Mask : ", -1);
        UARTPutHexNum(gEmifErrInfo.errBitLoc);
    }

    return retVal;
}

static int32_t emifDedErrTest()
{
    uint32_t testVal;
    int32_t  retVal = STW_SOK;

    gErrStatus = 0;
    gTest_Addr = NULL;

#if defined (BUILD_A15)
    CPUDisableCPSRABit();
#endif

    Intc_Init();
    Intc_IntEnable(0);

    Intc_IntRegister(gInterruptNum, (IntrFuncPtr) isrEmifDedErr, NULL);

    emifEccConfig();

    gTest_Addr = (uint32_t *) (EMIF_ECC_TEST_ADDR);

    EMIFEnableIntr(EMIF_APP_INST,
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK);

    EMIFConfigECCClrAllEccErrInfo(EMIF_APP_INST);

    EMIFConfigECCDisableEcc(EMIF_APP_INST);
    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFCFFFF;
    gTest_Addr[0] = testVal;

    EMIFConfigECCEnableEcc(EMIF_APP_INST);
    testVal = gTest_Addr[0];

    while (gErrStatus == 0) ;

    /* Unregister the interrupt */
    Intc_IntUnregister(gInterruptNum);

    Intc_IntDisable();

    if (gErrStatus != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_SOK)
    {
        UARTPuts("\n EMIF ECC -- DED ERR Test Pass!! ", -1);
        UARTPuts("\n EMIF ECC -- DED ERR Occured at Address : \n ", -1);
        UARTPutHexNum(gEmifErrInfo.errAddr[0] + EMIF_START_ADDR);
    }
    else
    {
        UARTPuts("\n EMIF ECC -- DED ERR Test Fail!! ", -1);
    }

    return retVal;
}

static int32_t emifNonEccQuantaAlignAddrErrTest()
{
    int32_t  retVal  = STW_SOK;
    uint32_t testVal = 0;
    uint32_t intEnable;

    gErrStatus = 0;
    gTest_Addr = NULL;

#if defined (TDA2XX_FAMILY_BUILD) && defined (BUILD_A15)
    intEnable = FALSE;
#else
    intEnable = TRUE;
#endif

    if (intEnable)
    {
        Intc_Init();
        Intc_IntEnable(0);

        Intc_IntRegister(gInterruptNum,
                         (IntrFuncPtr) isrEmifNonEccQuantaAlignAddrErr,
                         NULL);
    }

    emifEccConfig();

    EMIFEnableIntr(EMIF_APP_INST,
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK);

    EMIFConfigECCClrAllEccErrInfo(EMIF_APP_INST);

    gTest_Addr = (volatile uint32_t *) (EMIF_ECC_TEST_ADDR_2);
    testVal    = 0xFFFFFFFF;

    *(uint8_t *) (gTest_Addr) = testVal;

    if (!intEnable)
    {
        gErrStatus = EMIFGetIntrStatus(EMIF_APP_INST);
        EMIFClearIntrStatus(
            EMIF_APP_INST,
            EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK);
    }

    while (gErrStatus == 0) ;

    gErrStatus = ((gErrStatus &
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK) >>
                  EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_SHIFT);

    if (gErrStatus == 1)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (intEnable)
    {
        /* Unregister the interrupt */
        Intc_IntUnregister(gInterruptNum);

        Intc_IntDisable();
    }

    if (retVal == STW_SOK)
    {
        UARTPuts
            ("\n EMIF ECC -- Non EccQuanta Align Address Err Test Pass!! ",
            -1);
    }
    else
    {
        UARTPuts
            ("\n EMIF ECC -- Non EccQuanta Align Address Err Test Fail!! ",
            -1);
    }

    return retVal;
}

static int32_t emifByteCntWRAccessNotMultEccQuantaErrTest()
{
    int32_t  retVal = STW_SOK;
    uint8_t  testVal;
    uint32_t intEnable;

    gErrStatus = 0;
    gTest_Addr = NULL;

#if defined (TDA2XX_FAMILY_BUILD) && defined (BUILD_A15)
    intEnable = FALSE;
#else
    intEnable = TRUE;
#endif

    if (intEnable)
    {
        Intc_Init();
        Intc_IntEnable(0);

        Intc_IntRegister(
            gInterruptNum,
            (IntrFuncPtr)
            isrEmifByteCntWRAccessNotMultEccQuantaErr,
            NULL);
    }

    emifEccConfig();

    EMIFEnableIntr(EMIF_APP_INST,
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK);

    EMIFConfigECCClrAllEccErrInfo(EMIF_APP_INST);

    gTest_Addr = (uint32_t *) (EMIF_ECC_TEST_ADDR);
    testVal    = 0xFF;

    *(uint8_t *) gTest_Addr = testVal;

    if (!intEnable)
    {
        gErrStatus = EMIFGetIntrStatus(EMIF_APP_INST);
        EMIFClearIntrStatus(
            EMIF_APP_INST,
            EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK);
    }

    while (gErrStatus == 0) ;

    gErrStatus = ((gErrStatus &
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK) >>
                  EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_SHIFT);

    if (gErrStatus == 1)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (intEnable)
    {
        /* Unregister the interrupt */
        Intc_IntUnregister(gInterruptNum);

        Intc_IntDisable();
    }

    if (retVal == STW_SOK)
    {
        UARTPuts(
            "\nEMIF ECC-ByteCnt WRAccess Not Multiple of EccQuanta Err Test Pass!!",
            -1);
    }
    else
    {
        UARTPuts(
            "\nEMIF ECC-ByteCnt WRAccess Not Multiple of EccQuanta Err Test Fail!!",
            -1);
    }

    return retVal;
}

static void mainSubMenuOcmcRamEccTest(char *option, char *mode)
{
    while (1)
    {
        UARTPuts("\n\n**** OCMC RAM ECC TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. OCMC RAM SEC ERR ECC test", -1);
        UARTPuts("\n2. OCMC RAM DED ERR ECC test", -1);
        UARTPuts("\n3. OCMC RAM ADDRESS ERR ECC test", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect OCMC RAM ECC TEST : ", -1);
        /* Get option */
        UARTGets(option, 1);

        if (OCMC_RAM_ECC_SEC_TEST == *option ||
            OCMC_RAM_ECC_DED_TEST == *option ||
            OCMC_RAM_ECC_ADDR_ERR_TEST == *option ||
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }

    while (1)
    {
        UARTPuts("\n\n**** OCMC RAM ECC MODE ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. OCMC FULL ECC Mode", -1);
        UARTPuts("\n2. OCMC BLOCK ECC Mode", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect OCMC RAM ECC MODE : ", -1);
        /* Get option */
        UARTGets(mode, 1);

        if (OCMC_RAM_FULL_ECC_MODE == *mode ||
            OCMC_RAM_BLOCK_ECC_MODE == *mode ||
            EXIT(*mode))
        {
            gOcmcEccMode = *mode;
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

void isrOcmcRamSecErr()
{
    gEccErrAddr = OCMCEccErrTraceAddrGet(OCMC_RAM_APP_INST,
                                         OCMC_ECC_SEC_ERR);

    gEccErrBitMask[0] = OCMCSecEccErrDistributionStatusGet(
        OCMC_RAM_APP_INST,
        OCMC_ECC_SEC_ERR_DIST_0);
    gEccErrBitMask[1] = OCMCSecEccErrDistributionStatusGet(
        OCMC_RAM_APP_INST,
        OCMC_ECC_SEC_ERR_DIST_1);
    gEccErrBitMask[2] = OCMCSecEccErrDistributionStatusGet(
        OCMC_RAM_APP_INST,
        OCMC_ECC_SEC_ERR_DIST_2);
    gEccErrBitMask[3] = OCMCSecEccErrDistributionStatusGet(
        OCMC_RAM_APP_INST,
        OCMC_ECC_SEC_ERR_DIST_3);

    OCMCEccErrClearTraceHist(OCMC_RAM_APP_INST,
                             OCMC_CLEAR_SEC_ERROR_HIST |
                             OCMC_CLEAR_SEC_BIT_DIST_HIST);

    OCMCIntStatusEnableClear(OCMC_RAM_APP_INST,
                             0,
                             OCMC_ECC_SEC_ERROR_FOUND);
}

void isrOcmcRamDedErr()
{
    gTest_Addr = NULL;

    gEccErrAddr = OCMCEccErrTraceAddrGet(SOC_OCMC_RAM1_CFG_BASE,
                                         OCMC_ECC_DED_ERR);

    OCMCEccErrClearTraceHist(SOC_OCMC_RAM1_CFG_BASE,
                             OCMC_CLEAR_DED_ERROR_HIST);

    OCMCIntStatusEnableClear(SOC_OCMC_RAM1_CFG_BASE, 0,
                             OCMC_ECC_DED_ERROR_FOUND);

    OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_NON_ECC_DATA_ACCESS, 0, 0, 0);

    gTest_Addr    = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x18);
    gTest_Addr[0] = PATTERN_DATA;

    if (OCMC_RAM_FULL_ECC_MODE == gOcmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_FULL_ECC_ENABLE, 0, 1, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == gOcmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_BLOCK_ECC_ENABLE, 0, 1, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(SOC_OCMC_RAM1_CFG_BASE, 1, 0);
    }
}

void isrOcmcRamAddrErr()
{
    gTest_Addr = NULL;

    gEccErrAddr = OCMCEccErrTraceAddrGet(SOC_OCMC_RAM1_CFG_BASE,
                                         OCMC_ECC_ADDR_ERR);

    OCMCEccErrClearTraceHist(SOC_OCMC_RAM1_CFG_BASE,
                             CLEAR_ADDR_ERR_HIST);

    OCMCIntStatusEnableClear(SOC_OCMC_RAM1_CFG_BASE, 0,
                             OCMC_ECC_ADDR_ERROR_FOUND);

    OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_NON_ECC_CODE_ACCESS, 0, 0, 0);

    gTest_Addr    = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x10);
    gTest_Addr[0] = gOcmcTestVal;

    if (OCMC_RAM_FULL_ECC_MODE == gOcmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_FULL_ECC_ENABLE, 0, 1, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == gOcmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_BLOCK_ECC_ENABLE, 0, 1, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(SOC_OCMC_RAM1_CFG_BASE, 1, 0);
    }
}

int32_t ocmcRamEccTest(void)
{
    int32_t retVal = STW_SOK;
    char    mainSubMenuOption, ocmcEccMode;

    while (1)
    {
        mainSubMenuOcmcRamEccTest(&mainSubMenuOption, &ocmcEccMode);

        gEccErrAddr       = 0;
        gEccErrBitMask[0] = 0;
        gEccErrBitMask[1] = 0;
        gEccErrBitMask[2] = 0;
        gEccErrBitMask[3] = 0;

        if (OCMC_RAM_ECC_SEC_TEST == mainSubMenuOption)
        {
            retVal = ocmcRamSecErrTest(ocmcEccMode);
        }
        else if (OCMC_RAM_ECC_DED_TEST == mainSubMenuOption)
        {
            retVal = ocmcRamDedErrTest(ocmcEccMode);
        }
        else if (OCMC_RAM_ECC_ADDR_ERR_TEST == mainSubMenuOption)
        {
            retVal = ocmcRamAddrErrTest(ocmcEccMode);
        }
        else
        {
            UARTPuts("\n OCMC RAM ECC test exiting...", -1);
            break;
        }
    }
    return retVal;
}

static int32_t ocmcRamInitEccMem()
{
    volatile uint32_t i;
    EDMA3CCPaRAMEntry edmaParam;
    static uint32_t   blk_size = 0xFF;
    static int32_t    buf_size = BUFFER_SIZE;
    signed char      *srcBuff1;
    signed char      *dstBuff1;
    uint32_t          edma_ch_num   = 1;
    uint32_t          edma_evtq_num = 0;
    uint32_t          edma_tcc_num  = 1;
    uint32_t          aCnt          = 16;
    uint32_t          bCnt          = 1;
    uint32_t          cCnt          = 1;
    int32_t           retVal        = STW_SOK;

    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();

    EDMAsetRegion(EDMA3_CC_REGION);

    /* Do EDMA init Done once in the beginning of application */
    EDMA3Init(EDMA_APP_INST, 0);

    srcBuff1 = (signed char *) (srcBuff);
    dstBuff1 = (signed char *) (OCMC_RAM_ECC_START_ADDR);

    while (blk_size != 0)
    {
        EDMA3RequestChannel(EDMA_APP_INST, EDMA3_CHANNEL_TYPE_DMA, edma_ch_num,
                            edma_tcc_num, edma_evtq_num);

        edmaParam.opt      = 0;
        edmaParam.srcAddr  = (uint32_t) srcBuff1;
        edmaParam.destAddr = (uint32_t) dstBuff1;
        edmaParam.aCnt     = aCnt;
        edmaParam.bCnt     = bCnt;
        edmaParam.cCnt     = cCnt;
        edmaParam.srcBIdx  = aCnt;
        edmaParam.destBIdx = aCnt;
        edmaParam.srcCIdx  = aCnt;
        edmaParam.destCIdx = aCnt;
        edmaParam.linkAddr = 0xFFFFU;
        edmaParam.opt     |=
            (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK |
             ((edma_tcc_num << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

        EDMA3SetPaRAM(EDMA_APP_INST, edma_ch_num, &edmaParam);

        /*
         * Transfer is done in a sync mode
         * Number of triggers required are bCnt * cCnt
         */
        for (i = 0; i < (bCnt * cCnt); i++)
        {
            EDMA3EnableTransfer(EDMA_APP_INST, edma_ch_num,
                                EDMA3_TRIG_MODE_MANUAL);

            while (0U == (EDMA3GetIntrStatus(EDMA_APP_INST) &
                          ((uint32_t) 1U << edma_ch_num)))
            {
                /* Busy Loop */
            }
            EDMA3ClrIntr(EDMA_APP_INST, edma_ch_num);
        }

        for (i = 0; i < (aCnt * bCnt * cCnt); i++)
        {
            if (srcBuff1[i] != dstBuff1[i])
            {
                retVal = STW_EFAIL;
                UARTPuts("\nError matching value at src and dst address", -1);
                break;
            }
        }
        dstBuff1 += buf_size;
        blk_size -= buf_size;

        if ((blk_size < BUFFER_SIZE) && (blk_size % BUFFER_SIZE) != 0)
        {
            aCnt     = blk_size;
            buf_size = blk_size;
        }
    }
    return retVal;
}

static int32_t ocmcRamSecErrTest(char ocmcEccMode)
{
    uint32_t testVal;
    uint32_t secAutoCorrectEn = 1;
    uint32_t eccErrIntEn      = 0;
    uint32_t i;
    uint32_t eccErrAddr;
    int32_t  retVal = STW_SOK;

    gEccErrAddr = 0;
    gTest_Addr  = NULL;

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

#if defined (BUILD_M4)
    /*XBAR Configuration for OCMC*/
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_IPU1,
                   3, OCMC_RAM1_IRQ);
#elif defined (BUILD_A15)
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS, 19,
                   OCMC_RAM1_IRQ);
#endif

    Intc_Init();
    Intc_IntEnable(0);

    /* Enable OCMC interrupt*/
    Intc_IntRegister(OCMC_RAM_ECC_ERR_INT,
                     (IntrFuncPtr) isrOcmcRamSecErr,
                     NULL);

    Intc_IntPrioritySet(OCMC_RAM_ECC_ERR_INT, 1, 0);
    Intc_SystemEnable(OCMC_RAM_ECC_ERR_INT);

    OCMCSoftReset(OCMC_RAM_APP_INST);

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    retVal = ocmcRamInitEccMem();
    if (retVal == STW_EFAIL)
    {
        UARTPuts("\nECC Memory Intialisation failure", -1);
    }

    OCMCIntEnable(OCMC_RAM_APP_INST, 0, OCMC_ECC_SEC_ERROR_FOUND);

    /*Configure ERR count to trigger an interrupt*/
    OCMCEccErrTraceConfig(OCMC_RAM_APP_INST,
                          OCMC_RAM_ECC_1B_ERR_THRSH_VAL,
                          0,
                          0,
                          0);

    OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_NON_ECC_DATA_ACCESS, 0, 0, 0);

    gTest_Addr    = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x4);
    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFEFFFF;
    gTest_Addr[0] = testVal;

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    gTest_Addr = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x4);
    testVal    = gTest_Addr[0];

    while (gEccErrAddr == 0) ;

    OCMCIntDisable(OCMC_RAM_APP_INST, 0, OCMC_INTERRUPT_ALL);

    /* Disable the interrupt */
    Intc_SystemDisable(OCMC_RAM_ECC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(OCMC_RAM_ECC_ERR_INT);

    Intc_IntDisable();

    if (gEccErrAddr != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\n OCMC ECC SEC test Fail!! \n", -1);
    }
    else
    {
        UARTPuts("\n OCMC ECC SEC test successful", -1);
        for (i = 0; i < 4; i++)
        {
            if (gEccErrBitMask[i])
            {
                eccErrAddr = ((gEccErrAddr << 4) +
                              OCMC_RAM_START_ADDR + (i * 4));
                UARTPuts("\nECC -- SEC ECC ERR Occured at Address : ", -1);
                UARTPutHexNum(eccErrAddr);
                UARTPuts("\nECC -- SEC ECC ERR Occured at Bit Mask ", -1);
                UARTPutNum(i);
                UARTPuts(" : ", -1);
                UARTPutHexNum(gEccErrBitMask[i]);
            }
        }
    }

    return 0;
}

static int32_t ocmcRamDedErrTest(char ocmcEccMode)
{
    uint32_t testVal;
    uint32_t secAutoCorrectEn = 0;
    uint32_t eccErrIntEn      = 1;
    int32_t  retVal           = STW_SOK;

    gEccErrAddr = 0;
    gTest_Addr  = NULL;

#if defined (BUILD_A15)
    CPUDisableCPSRABit();
#endif

    Intc_Init();
    Intc_IntEnable(0);

    /* Enable OCMC interrupt*/
    Intc_IntRegister(gInterruptNum,
                     (IntrFuncPtr) isrOcmcRamDedErr,
                     NULL);

    OCMCSoftReset(OCMC_RAM_APP_INST);

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    retVal = ocmcRamInitEccMem();
    if (retVal == STW_EFAIL)
    {
        UARTPuts("\nECC Memory Intialisation failure", -1);
    }

    OCMCIntEnable(OCMC_RAM_APP_INST, 0, OCMC_ECC_DED_ERROR_FOUND);

    /*Configure ERR count to trigger an interrupt*/
    OCMCEccErrTraceConfig(OCMC_RAM_APP_INST, 0, OCMC_RAM_ECC_2B_ERR_THRSH_VAL,
                          0,
                          0);

    OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_NON_ECC_DATA_ACCESS, 0, 0, 0);

    gTest_Addr    = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x18);
    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFCFFFF;
    gTest_Addr[0] = testVal;

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    testVal = gTest_Addr[0];

    while (gEccErrAddr == 0) ;

    OCMCIntDisable(OCMC_RAM_APP_INST, 0, OCMC_INTERRUPT_ALL);

    /* Unregister the interrupt */
    Intc_IntUnregister(gInterruptNum);

    Intc_IntDisable();

    if (gEccErrAddr != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\n OCMC ECC DED Error Test Fail!! \n", -1);
    }
    else
    {
        UARTPuts("\n OCMC ECC DED Error test successful", -1);
        UARTPuts("\nECC -- DED ERR occured at one of these addresses \n ", -1);
        UARTPutHexNum(((gEccErrAddr << 4) + OCMC_RAM_START_ADDR));
        UARTPuts("\n", -1);
        UARTPutHexNum(((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0x4));
        UARTPuts("\n", -1);
        UARTPutHexNum(((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0x8));
        UARTPuts("\n", -1);
        UARTPutHexNum(((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0xc));
    }

    return 0;
}

static int32_t ocmcRamAddrErrTest(char ocmcEccMode)
{
    uint32_t secAutoCorrectEn = 0;
    uint32_t eccErrIntEn      = 1;
    int32_t  retVal           = STW_SOK;

    gEccErrAddr = 0;
    gTest_Addr  = NULL;

#if defined (BUILD_A15)
    CPUDisableCPSRABit();
#endif

    Intc_Init();
    Intc_IntEnable(0);

    /* Enable OCMC interrupt*/
    Intc_IntRegister(gInterruptNum,
                     (IntrFuncPtr) isrOcmcRamAddrErr,
                     NULL);

    OCMCSoftReset(OCMC_RAM_APP_INST);

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    retVal = ocmcRamInitEccMem();
    if (retVal == STW_EFAIL)
    {
        UARTPuts("\nECC Memory Intialisation failure", -1);
    }

    OCMCIntEnable(OCMC_RAM_APP_INST, 0, OCMC_ECC_ADDR_ERROR_FOUND);

    /*Configure ERR count to trigger an interrupt*/
    OCMCEccErrTraceConfig(OCMC_RAM_APP_INST, 0, OCMC_RAM_ECC_ADDR_ERR_THRSH_VAL,
                          0,
                          0);

    OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_NON_ECC_CODE_ACCESS, 0, 0, 0);

    gTest_Addr = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x10);

    gOcmcTestVal = *(uint32_t *) (gTest_Addr);
    /* Address err addr[0] = 137( 0x89) : 0x112 = 0x89 << 1. This Modifies Bit 0
     * 0f ECC bits
     */
    gTestVal = gOcmcTestVal ^ 0x112;
    *(uint32_t *) (gTest_Addr) = gTestVal;

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    gTestVal = *(uint32_t *) (gTest_Addr);

    while (gEccErrAddr == 0) ;

    OCMCIntDisable(OCMC_RAM_APP_INST, 0, OCMC_INTERRUPT_ALL);

    /* Unregister the interrupt */
    Intc_IntUnregister(gInterruptNum);

    Intc_IntDisable();

    if (gEccErrAddr != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTPuts("\n OCMC ECC Address Error test Fail!! \n", -1);
    }
    else
    {
        UARTPuts("\n OCMC ECC Address Error test successful", -1);
        UARTPuts("\nECC -- Address ERR occured at one of these addresses \n ",
                 -1);
        UARTPutHexNum(((gEccErrAddr << 4) + OCMC_RAM_START_ADDR));
        UARTPuts("\n", -1);
        UARTPutHexNum(((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0x4));
        UARTPuts("\n", -1);
        UARTPutHexNum(((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0x8));
        UARTPuts("\n", -1);
        UARTPutHexNum(((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0xc));
    }

    return 0;
}

#ifdef TDA3XX_FAMILY_BUILD
void ipuAmmuConfig(void)
{
    /* Small Page*/
    /* Logical Address */
    /* Default gel map 0x00000000 (vector table) to IPU L2 RAM . For IPU ECC
     *test 0x00000000 is mapped to ocmc addr (0x40300000)*/
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x120U, 0x00000000);
    /* Map 64KB IPU L2 RAM memory as cacheable*/
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x128U, 0x55020000);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x12CU, 0x55024000);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x130U, 0x55028000);

    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x134U, 0x90000000);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x138U, 0x90004000);

    /* Physical Address */
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x1A0U, 0x40300000);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x1A8U, 0x55020000);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x1ACU, 0x55024000);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x1B0U, 0x55028000);

    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x1B4U, 0x90000000);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x1B8U, 0x90004000);

    /* Policy Register */
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x220U, 0x00000003);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x228U, 0x000F0003);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x22CU, 0x000F0003);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x230U, 0x000F0003);

    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x234U, 0x000F0003);
    HW_WR_REG32(SOC_IPU1_UNICACHE_MMU_BASE + 0x238U, 0x000F0003);

    UARTPuts("\n A-MMU config for IPU ECC Test completed", -1);
}

#endif
