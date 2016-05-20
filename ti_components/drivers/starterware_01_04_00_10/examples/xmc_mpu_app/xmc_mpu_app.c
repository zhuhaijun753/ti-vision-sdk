/**
 *  \file     xmc_mpu_app.c
 *
 *  \brief    This file contains example usage for Extended Memory Controller
 *            (XMC) and Memory Protection Unit (MPU) in C66x device on TDA2x
 *            and TDA3x platform
 *
 *  \details  This will demonstrate implementation of access restrictions
 *            to different memory regions from C66x DSP.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated =
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
#include "common/stw_dataTypes.h"
#include "common/stw_types.h"
#include "hw_types.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "dsp_xmc.h"
#include "dsp_icfg.h"
#include "osal/bsp_osal.h"
#include "interrupt.h"
#include "edma.h"
#include "string.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* Supported arguments for switchCpuMode() API in swe.asm */
#define CPU_MODE_PRV                    (0x0U)
#define CPU_MODE_USR                    (0x1U)

/* Memory region labelled ASIL will be read-only (RO) for USER mode.
 * Memory region labelled QM will be read-write (RW) for USER mode.
 * All memory will be read-write (RW) for SUPERVISOR mode
 */
/* DDR Memory used for Memory access checks  */
#define QM_REGION_EMIF_START     (0x80010000U)
#define QM_REGION_EMIF_END       (0x80020000U)
#define ASIL_REGION_EMIF_START   (0x80020000U)
#define ASIL_REGION_EMIF_END     (0x80030000U)

/* OCMC Memory used for Memory access checks  */
#define QM_REGION_L3OCMC_START   (0x40300000U)
#define QM_REGION_L3OCMC_END     (0x40310000U)
#define ASIL_REGION_L3OCMC_START (0x40310000U)
#define ASIL_REGION_L3OCMC_END   (0x40320000U)

/* L2 Memory used for Memory access checks  */
#define QM_L2RAM_START         (SOC_DSP_L2_BASE)
#define QM_L2RAM_END           (QM_L2RAM_START + DSPICFG_L2_PGSZ)
#define ASIL_L2RAM_START       (QM_L2RAM_END)
#define ASIL_L2RAM_END         (ASIL_L2RAM_START + DSPICFG_L2_PGSZ)

#define DSPXMC_USR_RO_PRV_RW (DSPXMC_ALLOW_SR | \
                              DSPXMC_ALLOW_SW | \
                              DSPXMC_ALLOW_SX | \
                              DSPXMC_ALLOW_UR | \
                              DSPXMC_ALLOW_UX)

#define DSPXMC_USR_RW_PRV_RW (DSPXMC_USR_RO_PRV_RW | DSPXMC_ALLOW_UW)

#define DSPICFG_USR_RO_PRV_RW (DSPICFG_L2MPPA_LOCAL | \
                               DSPICFG_L2MPPA_SR |    \
                               DSPICFG_L2MPPA_SW |    \
                               DSPICFG_L2MPPA_SX |    \
                               DSPICFG_L2MPPA_UR |    \
                               DSPICFG_L2MPPA_UX)

#define DSPICFG_USR_RW_PRV_RW (DSPICFG_USR_RO_PRV_RW | DSPICFG_L2MPPA_UW)

#define EDMA3_CC_REGION_DSP              (2U)

/* Keys to lock/unlock MPU and XMC registers
 * Default state is unlocked. Locking is optional.
 * Keys can be changed by user.
 */
#define MPLK_KEY0   0xABCD1234U
#define MPLK_KEY1   0x1234ABCDU
#define MPLK_KEY2   0xA1B2C3D4U
#define MPLK_KEY3   0x4D3C2B1AU

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define MEM_CHK_BUF_SZ 0x40U
#ifdef __cplusplus
#pragma DATA_ALIGN(32)
#pragma DATA_SECTION(".scratch_section");
#else
#pragma DATA_ALIGN(scratchBuffer, 32)
#pragma DATA_SECTION(scratchBuffer,".scratch_section");
#endif
volatile uint32_t scratchBuffer[MEM_CHK_BUF_SZ >> 2U];
#ifdef __cplusplus
#pragma DATA_ALIGN(32)
#pragma DATA_SECTION(".scratch_section");
#else
#pragma DATA_ALIGN(randomNums, 32)
#pragma DATA_SECTION(randomNums,".scratch_section");
#endif
volatile uint32_t randomNums[MEM_CHK_BUF_SZ >> 2U] =
{
    0xAAAAAAAAU,
    0x55555555U,
    0xBBBBBBBBU,
    0xCCCCCCCCU,
    0x80808080U,
    0xA0A0A0A0U,
    0x50505050U,
    0x12345678U,
    0x22222222U,
    0xDDDDDDDDU,
    0x11111111U,
    0xEEEEEEEEU,
    0x00000000U,
    0x33331111U,
    0x99997777U,
    0x05050505U
};

/* ========================================================================== */
/*                 External Function Declarations                             */
/* ========================================================================== */
#ifdef __cplusplus
extern "C" {
#endif
/**
 *******************************************************************************
 *
 * \brief   Prototype for ASM function from swe.asm setup SWENR handler
 *
 *******************************************************************************
 */
extern void swenr_rep_setup();

/**
 *******************************************************************************
 *
 * \brief   Prototype for ASM function from swe.asm to do a CPU mode switch
 *
 * \param   mode     Mode requested
 *                       0 => Supervisor
 *                       1 => User
 *
 *******************************************************************************
 */
extern void switchCpuMode_asm(uint32_t mode);
#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 *******************************************************************************
 *
 * \brief   Request CPU mode switch
 *
 * \param   mode     Mode requested
 *                       0 => Supervisor
 *                       1 => User
 *
 *******************************************************************************
 */
void switchCpuMode(uint32_t mode);

/**
 * \brief   Initialize memory region specified by startAddr and endAddr
 *
 */
void initMem(uint32_t startAddr, uint32_t endAddr);

/**
 * \brief   Initialize memory regions under test
 *
 */
static void initAllMemory();

/**
 * \brief   Sets up different regions in XMC with different access permissions
 *
 */
static void setupXMC();

/**
 * \brief   Sets up different regions in L2RAM with different access permissions
 *
 */
static void setupL2MPU();

/**
 *******************************************************************************
 *
 * \brief   Validate CPU Read Access
 *
 * \param   startAddr       Start Address of region to check
 * \param   endAddr         End Address of region to check
 *
 * \return  errorOccured    1 if failure to read, 0 otherwise
 *
 *******************************************************************************
 */
uint32_t validateCpuReadAccess(uint32_t startAddr, uint32_t endAddr);

/**
 *******************************************************************************
 *
 * \brief   Validate CPU Write Access
 *
 * \param   startAddr       Start Address of region to check
 * \param   endAddr         End Address of region to check
 *
 * \return  errorOccured    1 if failure to read, 0 otherwise
 *
 *******************************************************************************
 */
uint32_t validateCpuWriteAccess(uint32_t startAddr, uint32_t endAddr);

/**
 *******************************************************************************
 *
 * \brief   Common implementation to check access permissions with specified
 *          CPU mode
 *
 * \return  errorOccured    >0 if unexpected failure to read/write, 0 otherwise
 *
 *******************************************************************************
 */
uint32_t validateAccessPermissions(uint32_t cpuMode);

/**
 *******************************************************************************
 *
 * \brief   Configure EDMA to transfer a 2D block
 *          Function will configure, trigger and wait for transfer completion.
 *
 * \param   dst     Source Address of the block
 * \param   src     Source Address of the block
 * \param   x       Width of the block in 32bit words
 * \param   y       Height of the block
 *
 *******************************************************************************
 */
static void edmaTransfer2d(uint32_t dst, uint32_t src, uint32_t x, uint32_t y)
{
    uint32_t          base_address  = SOC_DSP_EDMA_CC_BASE;
    uint32_t          edma_ch_num   = 0;
    uint32_t          edma_tcc_num  = 0;
    uint32_t          edma_evtq_num = 0;
    uint32_t          i;
    uint32_t          aCnt = x * 4;
    uint32_t          bCnt = y;
    uint32_t          cCnt = 1U;
    EDMA3CCPaRAMEntry edmaParam;

    EDMA3RequestChannel(base_address,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edma_ch_num,
                        edma_tcc_num,
                        edma_evtq_num);

    edmaParam.opt      = 0;
    edmaParam.srcAddr  = src;
    edmaParam.destAddr = dst;
    edmaParam.aCnt     = aCnt;
    edmaParam.bCnt     = bCnt;
    edmaParam.cCnt     = cCnt;
    edmaParam.srcBIdx  = aCnt;
    edmaParam.destBIdx = aCnt;
    edmaParam.srcCIdx  = aCnt;
    edmaParam.destCIdx = aCnt;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                          EDMA3_OPT_ITCINTEN_MASK |
                          ((edma_tcc_num << EDMA3_OPT_TCC_SHIFT) &
                       EDMA3_OPT_TCC_MASK));

    EDMA3SetPaRAM(base_address, edma_ch_num, &edmaParam);

    /*
     * Transfer is done in a sync mode
     * Number of triggers required are bCnt * cCnt
     */
    for (i = 0; i < (bCnt * cCnt); i++)
    {
        EDMA3EnableTransfer(base_address, edma_ch_num, EDMA3_TRIG_MODE_MANUAL);
        while ((EDMA3GetIntrStatus(base_address) & (0x1 << edma_tcc_num)) !=
               (0x1 << edma_tcc_num)) ;
        EDMA3ClrIntr(base_address, edma_tcc_num);
    }
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t main(void)
{
    uint32_t errorOccured = 0U;
    int32_t  status;

    /* Configure UARTStdioInit */
    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\nStarting application...\n", -1);

    /* EDMA setup */
    EDMAsetRegion(EDMA3_CC_REGION_DSP);
    EDMA3Init(SOC_DSP_EDMA_CC_BASE, 0);

    /* Enable interrupts */
    Intc_Init();
    swenr_rep_setup();

    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_64K);

    /* CPU mode switch is redundant - done only to indicate dependency of
     * setupXMC() and setupL2MPU() on CPU mode */
    switchCpuMode(CPU_MODE_PRV);
    setupXMC();
    setupL2MPU();

    /* CPU mode switch is redundant - done only to indicate dependency of
     * initAllMemory() on CPU mode */
    switchCpuMode(CPU_MODE_PRV);
    /* Initialize all memories to allow access permissions check */
    initAllMemory();

    /* Verify access permissions in SUPERVISOR mode */
    errorOccured += validateAccessPermissions(CPU_MODE_PRV);

    /* CPU mode switch is redundant - done only to indicate dependency of
     * initAllMemory() on CPU mode */
    switchCpuMode(CPU_MODE_PRV);
    /* Initialize all memories to allow access permissions check */
    initAllMemory();

    /* Verify access permissions in USER mode */
    errorOccured += validateAccessPermissions(CPU_MODE_USR);

    if (0U == errorOccured)
    {
        UARTPuts("Testcase PASS\n", -1);
    }
    else
    {
        UARTPuts("Testcase FAIL\n", -1);
    }

    /* Unlock all memory at the end of test-case */
    switchCpuMode(CPU_MODE_PRV);
    status = DSPICFGMemoryProtectionUnlock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTPuts("Unable to unlock XMC registers\n", -1);
    }

    UARTPuts("Exiting application...\n", -1);
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
/**
 *******************************************************************************
 *
 * \brief   Request CPU mode switch
 *
 * \param   mode     Mode requested
 *                       0 => Supervisor
 *                       1 => User
 *
 *******************************************************************************
 */
void switchCpuMode(uint32_t mode)
{
    uint32_t cookie;

    if (CPU_MODE_PRV == mode)
    {
        UARTPuts("Entering SUPERVISOR mode\n", -1);
    }
    else
    {
        UARTPuts("Entering USER mode\n", -1);
    }

    cookie = BspOsal_disableInterrupt();
    switchCpuMode_asm(mode);
    BspOsal_restoreInterrupt(cookie);
}

/**
 * \brief   Initialize memory region specified by startAddr and endAddr
 *
 */
void initMem(uint32_t startAddr, uint32_t endAddr)
{
    uint32_t addr;
    for (addr = startAddr; addr < endAddr; addr += 4)
    {
        HW_WR_REG32(addr, addr);
    }
}

/**
 * \brief   Initialize memory regions under test
 *
 */
static void initAllMemory()
{
    initMem(QM_REGION_EMIF_START, QM_REGION_EMIF_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          QM_REGION_EMIF_START,
                          (QM_REGION_EMIF_END - QM_REGION_EMIF_START));

    initMem(ASIL_REGION_EMIF_START, ASIL_REGION_EMIF_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          ASIL_REGION_EMIF_START,
                          (ASIL_REGION_EMIF_END - ASIL_REGION_EMIF_START));

    initMem(QM_REGION_L3OCMC_START, QM_REGION_L3OCMC_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          QM_REGION_L3OCMC_START,
                          (QM_REGION_L3OCMC_END - QM_REGION_L3OCMC_START));

    initMem(ASIL_REGION_L3OCMC_START, ASIL_REGION_L3OCMC_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          ASIL_REGION_L3OCMC_START,
                          (ASIL_REGION_L3OCMC_END - ASIL_REGION_L3OCMC_START));

    initMem(QM_L2RAM_START, QM_L2RAM_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          QM_L2RAM_START,
                          (QM_L2RAM_END - QM_L2RAM_START));

    initMem(ASIL_L2RAM_START, ASIL_L2RAM_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          ASIL_L2RAM_START,
                          (ASIL_L2RAM_END - ASIL_L2RAM_START));
}

/**
 * \brief   Sets up different regions in XMC with different access permissions
 *
 */
static void setupXMC()
{
    int32_t status;
    /* In case you are using breakpoints for debugging, ensure that
     * code region has full access permissions
     */
    status = DSPICFGMemoryProtectionUnlock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTPuts("Unable to unlock XMC registers\n", -1);
    }

    DSPXMCSetMPAXSegment(SOC_DSP_XMC_CTRL_BASE,    /* baseAddress   */
                         0x2U,                     /* segmentId     */
                         DSPXMC_SEGSZ_64KB,        /* segmentSize   */
                         QM_REGION_EMIF_START,     /* inpBAddress   */
                         QM_REGION_EMIF_START,     /* repAddressL   */
                         0x0U,                     /* repAddressH   */
                         DSPXMC_USR_RW_PRV_RW);    /* permsFieldVal */

    DSPXMCSetMPAXSegment(SOC_DSP_XMC_CTRL_BASE,    /* baseAddress   */
                         0x3U,                     /* segmentId     */
                         DSPXMC_SEGSZ_64KB,        /* segmentSize   */
                         ASIL_REGION_EMIF_START,   /* inpBAddress   */
                         ASIL_REGION_EMIF_START,   /* repAddressL   */
                         0x0U,                     /* repAddressH   */
                         DSPXMC_USR_RO_PRV_RW);    /* permsFieldVal */

    DSPXMCSetMPAXSegment(SOC_DSP_XMC_CTRL_BASE,    /* baseAddress   */
                         0x4U,                     /* segmentId     */
                         DSPXMC_SEGSZ_64KB,        /* segmentSize   */
                         QM_REGION_L3OCMC_START,   /* inpBAddress   */
                         QM_REGION_L3OCMC_START,   /* repAddressL   */
                         0x0U,                     /* repAddressH   */
                         DSPXMC_USR_RW_PRV_RW);    /* permsFieldVal */

    DSPXMCSetMPAXSegment(SOC_DSP_XMC_CTRL_BASE,    /* baseAddress   */
                         0x5U,                     /* segmentId     */
                         DSPXMC_SEGSZ_64KB,        /* segmentSize   */
                         ASIL_REGION_L3OCMC_START, /* inpBAddress   */
                         ASIL_REGION_L3OCMC_START, /* repAddressL   */
                         0x0U,                     /* repAddressH   */
                         DSPXMC_USR_RO_PRV_RW);    /* permsFieldVal */

    status = DSPICFGMemoryProtectionLock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTPuts("Unable to lock XMC registers\n", -1);
    }
}

/**
 * \brief   Sets up different regions in L2RAM with different access permissions
 *
 */
static void setupL2MPU()
{
    int32_t status;
    /* In case you are using breakpoints for debugging, ensure that
     * code region has full access permissions
     */
    status = DSPICFGMemoryProtectionUnlock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTPuts("Unable to unlock XMC registers\n", -1);
    }

    DSPICFGSetAttribute(SOC_DSP_ICFG_BASE,
                        DSPICFG_MEM_L2,
                        QM_L2RAM_START,
                        DSPICFG_USR_RW_PRV_RW);

    DSPICFGSetAttribute(SOC_DSP_ICFG_BASE,
                        DSPICFG_MEM_L2,
                        ASIL_L2RAM_START,
                        DSPICFG_USR_RO_PRV_RW);

    status = DSPICFGMemoryProtectionLock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTPuts("Unable to lock XMC registers\n", -1);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Validate CPU Read Access
 *
 * \param   startAddr       Start Address of region to check
 * \param   endAddr         End Address of region to check
 *
 * \return  errorOccured    1 if failure to read, 0 otherwise
 *
 *******************************************************************************
 */
uint32_t validateCpuReadAccess(uint32_t startAddr, uint32_t endAddr)
{
    uint32_t errorOccured = 0U, addr, val;

    for (addr = startAddr; addr < endAddr; addr += sizeof (uint32_t))
    {
        val = HW_RD_REG32(addr);
        if (val != addr)
        {
            errorOccured = 1U;
        }
    }

    if (0U != errorOccured)
    {
        UARTPuts("Error occurred in READ\n", -1);
    }

    return errorOccured;
}

/**
 *******************************************************************************
 *
 * \brief   Validate CPU Write Access
 *
 * \param   startAddr       Start Address of region to check
 * \param   endAddr         End Address of region to check
 *
 * \return  errorOccured    1 if failure to read, 0 otherwise
 *
 *******************************************************************************
 */
uint32_t validateCpuWriteAccess(uint32_t startAddr, uint32_t endAddr)
{
    uint32_t errorOccured = 0U, addr, i, wval, rval;

    for (addr = startAddr; addr < endAddr; addr += MEM_CHK_BUF_SZ)
    {
        memset((void *) (&scratchBuffer[0]), 0x0, MEM_CHK_BUF_SZ);
        memcpy((void *) addr, (void *) (&randomNums[0]), MEM_CHK_BUF_SZ);

        DSPICFGCacheWriteBackInvalidateAll(SOC_DSP_ICFG_BASE, DSPICFG_MEM_L2);

        if ((QM_L2RAM_START == startAddr) ||
            (ASIL_L2RAM_START == startAddr))
        {
            memcpy((void *) (&scratchBuffer[0]), (void *) addr, MEM_CHK_BUF_SZ);
        }
        else
        {
            /* Use EDMA read to avoid cache */
            edmaTransfer2d((uint32_t) (&scratchBuffer[0]),
                           addr,
                           (MEM_CHK_BUF_SZ >> 2),
                           1U);
        }
        for (i = 0; i < (MEM_CHK_BUF_SZ >> 2); i++)
        {
            wval = randomNums[i];
            rval = scratchBuffer[i];
            if (rval != wval)
            {
                errorOccured = 1U;
            }
        }
    }

    if (0U != errorOccured)
    {
        UARTPuts("Error occurred in WRITE\n", -1);
    }

    return errorOccured;
}

/**
 *******************************************************************************
 *
 * \brief   Common implementation to check access permissions with specified
 *          CPU mode
 *
 * \return  errorOccured    >0 if unexpected failure to read/write, 0 otherwise
 *
 *******************************************************************************
 */
uint32_t validateAccessPermissions(uint32_t cpuMode)
{
    uint32_t errorOccured = 0U, retVal;

    switchCpuMode(cpuMode);

    UARTPuts("Checking CPU DDR/OCMC READ Access for USR_RW region\n", -1);
    errorOccured += validateCpuReadAccess(QM_REGION_EMIF_START,
                                          QM_REGION_EMIF_END);
    errorOccured += validateCpuReadAccess(QM_REGION_L3OCMC_START,
                                          QM_REGION_L3OCMC_END);

    UARTPuts("Checking CPU DDR/OCMC READ Access for USR_RO region\n", -1);
    errorOccured += validateCpuReadAccess(ASIL_REGION_EMIF_START,
                                          ASIL_REGION_EMIF_END);
    errorOccured += validateCpuReadAccess(ASIL_REGION_L3OCMC_START,
                                          ASIL_REGION_L3OCMC_END);

    UARTPuts("Checking CPU L2 RAM READ Access for USR_RW region\n", -1);
    errorOccured += validateCpuReadAccess(QM_L2RAM_START,
                                          QM_L2RAM_END);
    UARTPuts("Checking CPU L2 RAM READ Access for USR_RO region\n", -1);
    errorOccured += validateCpuReadAccess(ASIL_L2RAM_START,
                                          ASIL_L2RAM_END);

    UARTPuts("Checking CPU DDR/OCMC WRITE Access for USR_RW region\n", -1);
    errorOccured += validateCpuWriteAccess(QM_REGION_EMIF_START,
                                           QM_REGION_EMIF_END);
    errorOccured += validateCpuWriteAccess(QM_REGION_L3OCMC_START,
                                           QM_REGION_L3OCMC_END);

    UARTPuts("Checking CPU DDR/OCMC WRITE Access for USR_RO region\n", -1);

    if (CPU_MODE_USR == cpuMode)
    {
        UARTPuts("Expecting errors\n", -1);
    }
    retVal = validateCpuWriteAccess(ASIL_REGION_EMIF_START,
                                    ASIL_REGION_EMIF_END);
    if (CPU_MODE_PRV == cpuMode)
    {
        errorOccured += retVal;
    }
    else
    {
        if (0U == retVal)
        {
            errorOccured = 1U;
        }
    }

    if (CPU_MODE_USR == cpuMode)
    {
        UARTPuts("Expecting errors\n", -1);
    }
    retVal = validateCpuWriteAccess(ASIL_REGION_L3OCMC_START,
                                    ASIL_REGION_L3OCMC_END);
    if (CPU_MODE_PRV == cpuMode)
    {
        errorOccured += retVal;
    }
    else
    {
        if (0U == retVal)
        {
            errorOccured = 1U;
        }
    }

    UARTPuts("Checking CPU L2 RAM WRITE Access for USR_RW region\n", -1);
    errorOccured += validateCpuWriteAccess(QM_L2RAM_START,
                                           QM_L2RAM_END);

    UARTPuts("Checking CPU L2 RAM WRITE Access for USR_RO region\n", -1);
    if (CPU_MODE_USR == cpuMode)
    {
        UARTPuts("Expecting errors\n", -1);
    }
    retVal = validateCpuWriteAccess(ASIL_L2RAM_START,
                                    ASIL_L2RAM_END);
    if (CPU_MODE_PRV == cpuMode)
    {
        errorOccured += retVal;
    }
    else
    {
        if (0U == retVal)
        {
            errorOccured = 1U;
        }
    }

    return errorOccured;
}

