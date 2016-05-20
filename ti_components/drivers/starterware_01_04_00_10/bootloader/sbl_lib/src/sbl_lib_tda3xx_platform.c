/**
 *  \file     sbl_lib_tda3xx_platform.c
 *
 *  \brief    This file contains the SBL Library layer for tda3xx platform.
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
#include "hw_types.h"
#include "common/stw_types.h"
#include "hw_ctrl_core.h"
#include "hw_ctrl_core_sec.h"
#include "hw_ipu_m4_nvic.h"
#include "hw_ipu_mmu.h"
#include "hw_ipu_wugen_local_prcm.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "edma.h"
#include "mmu.h"
#include "timer.h"
#include "tesoc.h"
#include "sbl_lib_config.h"
#include "sbl_lib/sbl_lib.h"
#include "sbl_lib_tda3xx_priv.h"
#include "pm/pmhal/pmhal_cm.h"
#include "pm/pmhal/pmhal_rm.h"
#include "pm/pmhal/pmhal_mm.h"
#include "pm/pmhal/pmhal_sd.h"
#include "pm/pmhal/pmhal_pdm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Timer Start Count Value */
#define SBL_LIB_TIMER_START_COUNT                      ((uint32_t) 0x00000000U)

/* Timer count at which IPU is powered down. 0x2D0 -> 36 micro-seconds */
#define SBL_LIB_TIMER_IPU_POWER_DOWN_COUNT             ((uint32_t) 0x000002D0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API manually triggers the IPU TESOC Test by setting dummy
 *          triggers.
 *
 * \param   None
 *
 * \return  None
 */
static void SblLibTriggerIPUTesocTest(void);

/**
 * \brief   This API does a sequence of writes after which IPU can be put in
 *          IDLE state by sending WFI.
 *
 * \param   None
 *
 * \return  None
 *
 * \note    This API will only prepare IPU to be put in IDLE state. To actually
 *          put IPU in IDLE state send "WFI" instruction immediately after
 *          calling this API.
 */
static void SblLibSetIPUIdle(void);

/**
 * \brief   This API configures Timer3 for one-shot and compare mode.
 *
 * \param   waitCount        Required wait time count value.
 *
 * \return  None
 *
 * \note    This API is used to have timed power down for IPU as IPU can't be
 *          powered down due to TESOC IP issues.
 */
static void SblLibConfigTimer3(uint32_t waitCount);

/**
 * \brief   This function waits for the interrupt i.e. WFI.
 *
 * \param   None.
 *
 * \return  None.
 */
static inline void SblLibWaitForInterrupt(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Global variable for referencing the Boot Media App Image Read function */
static SBLLibMediaReadFxn    gMediaReadFxn;

/* Global variable for referencing the DDR App Image Read function */
static SBLLibDDRReadFxn      gDDRReadFxn;

/*
 * Global variable for referencing the location upto which App Image has been
 * read
 */
static SBLLibSeekFxn         gSeekFxn;

/* Global variable for referencing the CRC Calculation function */
static SBLLibCalculateCRCFxn gCalculateCRCFxn;

/*
 * Global variable for SBL initialization parameters
 */
static sbllibInitParams_t    gSBLLibInitParams;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SBLLibInit(const sbllibInitParams_t *sbllibInitPrms)
{
    if (NULL != sbllibInitPrms)
    {
        gSBLLibInitParams.printFxn = sbllibInitPrms->printFxn;
    }
}

void SBLLibPrintf(uint32_t traceLevel, const char *message)
{
    if (NULL != gSBLLibInitParams.printFxn)
    {
        switch (traceLevel)
        {
            case SBLLIB_TRACE_LEVEL_ERROR:
                gSBLLibInitParams.printFxn(message);
                break;
            case SBLLIB_TRACE_LEVEL_IMP_INFO:
                gSBLLibInitParams.printFxn(message);
                break;
#if (SBL_OPT_LEVEL < SBLLIB_OPT_LEVEL_HIGH)
    #if (TRACE_LEVEL >= SBLLIB_TRACE_LEVEL_LOW)
            case SBLLIB_TRACE_LEVEL_INFO:
                gSBLLibInitParams.printFxn(message);
                break;
    #endif
    #if (SBL_OPT_LEVEL < SBLLIB_OPT_LEVEL_MEDIUM)
        #if (TRACE_LEVEL >= SBLLIB_TRACE_LEVEL_MEDIUM)
            case SBLLIB_TRACE_LEVEL_INFO1:
                gSBLLibInitParams.printFxn(message);
                break;
        #endif
        #if (TRACE_LEVEL >= SBLLIB_TRACE_LEVEL_HIGH)
            case SBLLIB_TRACE_LEVEL_DEBUG:
                gSBLLibInitParams.printFxn(message);
                break;
        #endif
    #endif
#endif
            default:
                /* To remove MISRA C error */
                break;
        }
    }
}

void SBLLibAppImageParamsInit(sbllibAppImageParseParams_t *imageParams)
{
    imageParams->appImgMetaHeader   = NULL;
    imageParams->appImgRPRCHeader   = NULL;
    imageParams->entryPoints        = NULL;
    imageParams->appImageOffset     = 0U;
    imageParams->ddrAppImageAddress = 0U;
    imageParams->enableCrc          = (uint32_t) FALSE;
}

int32_t SBLLibMultiCoreImageParse(sbllibAppImageParseParams_t *imageParams)
{
    uint32_t       fileNo, entryPoint = 0U;
    uint32_t       magicStr         = SBLLIB_META_HEADER_MAGIC_STR;
    uint32_t       currAppImageAddr = imageParams->appImageOffset;
    int32_t        retVal           = STW_SOK;
    uint32_t       crcDataSize      = 0U, tempAddr = 0U;
    uint32_t       crcSrcAddr       = 0U;
    uint32_t       tempHeaderAddr   = 0U, isHeaderAppended = 0U;
    crcSignature_t crcSignValue     = {0U};
    crcSignature_t validCrcSign[SBLLIB_MAX_RPRC_IMAGES + 1U];
    uint32_t       loopCnt = 0U;
    char           coreIdStr[8U] = {0};

    for(loopCnt = 0U ; loopCnt <= SBLLIB_MAX_RPRC_IMAGES ; loopCnt++)
    {
        validCrcSign[loopCnt].regL = 0U;
        validCrcSign[loopCnt].regH = 0U;
    }
    if ((NULL == gMediaReadFxn) ||
        (NULL == gDDRReadFxn) ||
        (NULL == gSeekFxn) ||
        (NULL == imageParams->appImgMetaHeader) ||
        (NULL == imageParams->appImgRPRCHeader) ||
        (NULL == imageParams->entryPoints) ||
        (0U == imageParams->ddrAppImageAddress))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Read meta header start and get the number of RPRC Images */
        gMediaReadFxn(&imageParams->appImgMetaHeader->metaHeaderStart,
                      currAppImageAddr,
                      sizeof (sbllibMetaHeaderStart_t));
        currAppImageAddr += sizeof (sbllibMetaHeaderStart_t);

        if ((uint32_t) magicStr !=
            imageParams->appImgMetaHeader->metaHeaderStart.magicStr)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\nInvalid Magic String in MultiCore Image\r\n");
            retVal = STW_EFAIL;
        }
        else
        {
            if (imageParams->appImgMetaHeader->metaHeaderStart.devId !=
                SBLLibGetDeviceId())
            {
                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                             "\nWARNING: Device Id Does not Match\r\n");
            }

            /* Read all the core offset addresses */
            for (fileNo = 0U;
                 fileNo <
                 imageParams->appImgMetaHeader->metaHeaderStart.numFiles;
                 fileNo++)
            {
                gMediaReadFxn(
                    &imageParams->appImgMetaHeader->metaHeaderCore[fileNo],
                    currAppImageAddr,
                    sizeof (sbllibMetaHeaderCore_t));
                currAppImageAddr += sizeof (sbllibMetaHeaderCore_t);
            }

            /* Read meta header end */
            gMediaReadFxn(&imageParams->appImgMetaHeader->metaHeaderEnd,
                          currAppImageAddr,
                          sizeof (sbllibMetaHeaderEnd_t));
            currAppImageAddr += sizeof (sbllibMetaHeaderEnd_t);

            if ((uint32_t) TRUE == imageParams->enableCrc)
            {
                /* Assign signatures before modifying header */
                /* Assign meta header signature */
                validCrcSign[0].regL =
                    imageParams->appImgMetaHeader->
                    metaHeaderStart.metaHeaderCrcL;
                validCrcSign[0].regH =
                    imageParams->appImgMetaHeader->
                    metaHeaderStart.metaHeaderCrcH;

                imageParams->appImgMetaHeader->metaHeaderStart.metaHeaderCrcL
                    = 0x0U;
                imageParams->appImgMetaHeader->metaHeaderStart.metaHeaderCrcH
                    = 0x0U;

                /* Assign RPRC Signatures */
                for (fileNo = 0U;
                     fileNo <
                     imageParams->appImgMetaHeader->metaHeaderStart.numFiles;
                     fileNo++)
                {
                    validCrcSign[fileNo + 1U].regL =
                        imageParams->appImgMetaHeader->
                        metaHeaderCore[fileNo].rprcImageCrcL;

                    validCrcSign[fileNo + 1U].regH =
                        imageParams->appImgMetaHeader->
                        metaHeaderCore[fileNo].rprcImageCrcH;

                    imageParams->appImgMetaHeader->
                    metaHeaderCore[fileNo].rprcImageCrcH = 0x0U;

                    imageParams->appImgMetaHeader->
                    metaHeaderCore[fileNo].rprcImageCrcL = 0x0U;
                }

                if (NULL == gMediaReadFxn)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "CRC callback is not registered, aborting boot\r\n");
                    SBLLibAbortBoot();
                }

                /* Check if Meta Header contains 0x00000000 in the end for 8
                 * byte alignment
                 */
                if (currAppImageAddr !=
                    imageParams->appImgMetaHeader->
                    metaHeaderCore[0].imageOffset)
                {
                    tempAddr = (currAppImageAddr - imageParams->appImageOffset)
                               + (uint32_t) (&imageParams->appImgMetaHeader->
                                             metaHeaderStart.magicStr);
                    *(volatile uint32_t *) tempAddr = 0x0U;

                    currAppImageAddr += 0x4U;
                    isHeaderAppended  = 1U;
                }

                crcDataSize = currAppImageAddr - imageParams->appImageOffset;
                crcSrcAddr  =
                    (uint32_t) (&imageParams->appImgMetaHeader->
                                metaHeaderStart.magicStr);

                if (SBLLIB_MAX_RPRC_IMAGES !=
                    imageParams->appImgMetaHeader->metaHeaderStart.numFiles)
                {
                    if (1U == isHeaderAppended)
                    {
                        tempHeaderAddr = (crcSrcAddr + crcDataSize) - 0xCU;
                        *(volatile uint32_t *) tempHeaderAddr = 0x0U;
                        tempHeaderAddr = (crcSrcAddr + crcDataSize) - 0x8U;
                        *(volatile uint32_t *) tempHeaderAddr =
                            imageParams->appImgMetaHeader->metaHeaderEnd.
                            magicStringEnd;
                    }
                    else
                    {
                        tempHeaderAddr = (crcSrcAddr + crcDataSize) - 0x8U;
                        *(volatile uint32_t *) tempHeaderAddr = 0x0U;
                        tempHeaderAddr = (crcSrcAddr + crcDataSize) - 0x4U;
                        *(volatile uint32_t *) tempHeaderAddr =
                            imageParams->appImgMetaHeader->metaHeaderEnd.
                            magicStringEnd;
                    }
                }

                /* Calculate CRC */
                gCalculateCRCFxn((const void *) crcSrcAddr,
                                 crcDataSize,
                                 &crcSignValue);

                if ((validCrcSign[0].regL != crcSignValue.regL) ||
                    (validCrcSign[0].regH != crcSignValue.regH))
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n Multi-Core Header CRC Match Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }
            }

            /* Add base offset address with core image start offset for all
             * cores
             */
            for (fileNo = 0U;
                 fileNo <
                 imageParams->appImgMetaHeader->metaHeaderStart.numFiles;
                 fileNo++)
            {
                imageParams->appImgMetaHeader->
                metaHeaderCore[fileNo].imageOffset +=
                    imageParams->appImageOffset;
            }

            /* Now parse individual RPRC files */
            for (fileNo = 0U;
                 fileNo <
                 imageParams->appImgMetaHeader->metaHeaderStart.numFiles;
                 fileNo++)
            {
                if ((1U == imageParams->appImgMetaHeader->
                     metaHeaderCore[fileNo].isRprcImageValid) &&
                    (((uint32_t) 0xFFFFFFFFU) !=
                     imageParams->appImgMetaHeader->
                     metaHeaderCore[fileNo].coreId))
                {
                    gSeekFxn(&currAppImageAddr,
                             imageParams->appImgMetaHeader->
                             metaHeaderCore[fileNo].imageOffset);
                    gMediaReadFxn(
                        (void *) imageParams->ddrAppImageAddress,
                        currAppImageAddr,
                        imageParams->appImgMetaHeader->
                        metaHeaderCore[fileNo].rprcImageSize);

                    if ((uint32_t) TRUE == imageParams->enableCrc)
                    {
                        crcDataSize = imageParams->appImgMetaHeader->
                                      metaHeaderCore[fileNo].rprcImageSize;
                        crcSrcAddr = (uint32_t) imageParams->ddrAppImageAddress;

                        /* Calculate CRC */
                        gCalculateCRCFxn((const void *) crcSrcAddr,
                                         crcDataSize,
                                         &crcSignValue);

                        if ((validCrcSign[fileNo + 1U].regL !=
                             crcSignValue.regL) ||
                            (validCrcSign[fileNo + 1U].regH !=
                             crcSignValue.regH))
                        {
                            snprintf(coreIdStr,
                                     (size_t) 8,
                                     "%d",
                                     imageParams->appImgMetaHeader->
                                     metaHeaderCore[fileNo].coreId);

                            SBLLibPrintf(
                                SBLLIB_TRACE_LEVEL_ERROR,
                                "\n CRC Match Failed for Core ID:");
                            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR, coreIdStr);
                            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                         ", Aborting Boot\n");
                            SBLLibAbortBoot();
                        }
                    }

                    if (STW_SOK !=
                        SBLLibRprcImageParse(imageParams->appImgRPRCHeader,
                                             (void *) imageParams->
                                             ddrAppImageAddress,
                                             &entryPoint,
                                             imageParams->
                                             appImgMetaHeader->
                                             metaHeaderCore[fileNo].
                                             coreId))
                    {
                        /* Error occurred parsing the RPRC file. Continue
                         * parsing the next
                         * image and skip booting the particular core.
                         */
                        retVal = STW_EFAIL;
                    }
                    else
                    {
                        SBLLibBootCore(
                            entryPoint,
                            imageParams->appImgMetaHeader->
                            metaHeaderCore[fileNo].coreId,
                            imageParams->entryPoints);
                    }
                }
            }
        }
    }
    return retVal;
}

int32_t SBLLibRprcImageParse(sbllibRPRCImageHeader_t *rprcHeader,
                             const void              *rprcImageAddr,
                             uint32_t                *entryPoint,
                             uint32_t                 coreId)
{
    uint32_t numSections;
    int32_t  retVal = STW_SOK;

    uint32_t currRprcImageAddr = (uint32_t) rprcImageAddr;

    if (NULL == rprcHeader)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Read RPRC image header */
        gDDRReadFxn(&rprcHeader->rprcFileHeader,
                    (const void *) currRprcImageAddr,
                    sizeof (sbllibRprcFileHeader_t));
        currRprcImageAddr += sizeof (sbllibRprcFileHeader_t);

        /* Check magic string */
        if (SBLLIB_RPRC_MAGIC_STRING != rprcHeader->rprcFileHeader.magicStr)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "Invalid Magic String in Boot Image\r\n");
            retVal = STW_EFAIL;
        }
        else
        {
            /* Set the entry point */
            *entryPoint = rprcHeader->rprcFileHeader.entryPoint;

            /* Read entrypoint and copy sections to memory */
            for (numSections = 0;
                 numSections < rprcHeader->rprcFileHeader.sectionCount;
                 numSections++)
            {
                /* Read new section header */
                gDDRReadFxn(
                    &rprcHeader->rprcSectionHeader,
                    (const void *) currRprcImageAddr,
                    sizeof (sbllibRprcSectionHeader_t));
                currRprcImageAddr += sizeof (sbllibRprcSectionHeader_t);

                /* Copy section to memory */
                /* Check for section mapped into CPU internal memories */
                if ((rprcHeader->rprcSectionHeader.loadAddr >=
                     SOC_OCMC_RAM1_BASE) &&
                    (rprcHeader->rprcSectionHeader.loadAddr <
                     (SOC_OCMC_RAM1_BASE + SBLLIB_SOC_OCMC_RAM1_SIZE)))
                {
                    /* Internal OCMC RAM Space for all the cores */
                }
                else if (rprcHeader->rprcSectionHeader.loadAddr < 0x80000000U)
                {
                    switch (coreId)
                    {
                        case SBLLIB_CORE_ID_IPU1_CPU0:
                        case SBLLIB_CORE_ID_IPU1_CPU1:
                            if (rprcHeader->rprcSectionHeader.loadAddr <
                                0x10000U)
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_IPU_RAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            break;

                        case SBLLIB_CORE_ID_DSP1:
                            if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                 SBLLIB_SOC_DSP_L2_BASE) &&
                                (rprcHeader->rprcSectionHeader.loadAddr <
                                 (SBLLIB_SOC_DSP_L2_BASE + 0x48000U)))
                            {
                                /* L2 RAM: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L2_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP1_L2_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_DSP_L1P_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_DSP_L1P_BASE + 0x8000U)))
                            {
                                /* SOC_DSP1_L1P_SRAM_BASE: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L1P_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP1_L1P_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_DSP_L1D_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_DSP_L1D_BASE + 0x8000U)))
                            {
                                /* SOC_DSP1_L1D_SRAM_BASE: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L1D_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP1_L1D_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "DSP1 - Invalid Memory section");
                            }
                            break;

                        case SBLLIB_CORE_ID_DSP2:
                            if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                 SBLLIB_SOC_DSP_L2_BASE) &&
                                (rprcHeader->rprcSectionHeader.loadAddr <
                                 (SBLLIB_SOC_DSP_L2_BASE + 0x48000U)))
                            {
                                /* L2 RAM: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L2_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP2_L2_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_DSP_L1P_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_DSP_L1P_BASE + 0x8000U)))
                            {
                                /* SOC_DSP2_L1P_SRAM_BASE: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L1P_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP2_L1P_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_DSP_L1D_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_DSP_L1D_BASE + 0x8000U)))
                            {
                                /* SOC_DSP2_L1D_SRAM_BASE: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L1D_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP2_L1D_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "DSP2 - Invalid Memory section");
                            }
                            break;

                        case SBLLIB_CORE_ID_EVE1:
                            /*DMEM*/
                            if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                 SBLLIB_SOC_EVE_DMEM_BASE) &&
                                (rprcHeader->rprcSectionHeader.loadAddr <
                                 (SBLLIB_SOC_EVE_DMEM_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_DMEM_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_IPU_EVE_DMEM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*WMEM*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_WBUF_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_WBUF_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_WBUF_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_IPU_EVE_WBUF_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLA*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_IPU_EVE_IBUF_LA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLH*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_IPU_EVE_IBUF_HA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_IPU_EVE_IBUF_LB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFHB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_IPU_EVE_IBUF_HB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "EVE1 - Invalid Memory section");
                            }
                            break;
                        default:
                            /* To remove MISRA C error */
                            break;
                    }
                }
                else
                {
                    /* To remove MISRA C error */
                }
                gDDRReadFxn(
                    (void *) rprcHeader->rprcSectionHeader.loadAddr,
                    (const void *) currRprcImageAddr,
                    rprcHeader->rprcSectionHeader.sectionSize);
                currRprcImageAddr += rprcHeader->rprcSectionHeader.sectionSize;
            }
        }
    }
    return retVal;
}

int32_t SBLLibGetDeviceId(void)
{
    int32_t deviceId;

    deviceId = 77;

    return deviceId;
}

int32_t SBLLibBootCore(uint32_t             entryPoint,
                       uint32_t             coreId,
                       sbllibEntryPoints_t *entryPoints)
{
    int32_t retVal = STW_SOK;

    switch (coreId)
    {
        case SBLLIB_CORE_ID_IPU1_CPU0:
            /* IPU1 CPU0 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU1 CPU0 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU0] =
                entryPoint;
            break;

        case SBLLIB_CORE_ID_IPU1_CPU1:
            /* IPU1 CPU1 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU1 CPU1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU1] =
                entryPoint;
            /* In case of Fully Optimized SBL, IPU Core1 needs to be booted up
             * before loading other cores for responding to CAN
             */
            #if (SBL_OPT_LEVEL >= SBLLIB_OPT_LEVEL_HIGH)
            /* Set the entry point for IPU1 Core 1 */
            if (0U != entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU1])
            {
                SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                             "\n Jumping to IPU1 CPU1 App \n");
                HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS,
                            entryPoints->entryPoint[
                                SBLLIB_CORE_ID_IPU1_CPU1]);
            }
            else
            {
                /* Set while(1) loop */
                HW_WR_REG32((SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE - 1U),
                            0xE7FEE7FEU);

                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_IMP_INFO,
                    "\n No IPU1 CPU1 App Found, Switching to while Loop \n");
                HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS,
                            SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE);
            }
            #endif
            break;

        case SBLLIB_CORE_ID_DSP1:
            /* DSP1 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n DSP1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_DSP1] = entryPoint;
            break;

        case SBLLIB_CORE_ID_DSP2:
            /* DSP2 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n DSP2 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_DSP2] = entryPoint;
            break;

        case SBLLIB_CORE_ID_EVE1:
            /* EVE1 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n EVE1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_EVE1] = entryPoint;
            break;
        case SBLLIB_CORE_ID_IPU1:
            /* IPU1 SMP */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU1 CPU0 and CPU1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU0] =
                entryPoint;
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU1] =
                entryPoint;
            break;
        default:
            retVal = STW_EFAIL;
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Wrong Core Id: Cannot Assign entry point \n");
            break;
    }
    return retVal;
}

void SBLLibResetAllSlaveCores(void)
{
    /* Reset DSP1 */
    SBLLibCPUReset(SBLLIB_CORE_ID_DSP1);

    /* Reset DSP2 */
    SBLLibCPUReset(SBLLIB_CORE_ID_DSP2);

    /* Reset EVE1 */
    SBLLibCPUReset(SBLLIB_CORE_ID_EVE1);
}

void SBLLibCPUReset(uint32_t cpuId)
{
    pmhalPrcmResetGroupId_t systemReset = PMHAL_PRCM_RG_LOWER_BOUND;
    pmhalPrcmResetGroupId_t localReset  = PMHAL_PRCM_RG_LOWER_BOUND;
    int32_t  retVal    = STW_SOK;
    uint32_t rstStatus = 0U;

    switch (cpuId)
    {
        case SBLLIB_CORE_ID_DSP1:
            systemReset = PMHAL_PRCM_RG_DSP1_SYS_RST;
            localReset  = PMHAL_PRCM_RG_DSP1_RST;
            break;

        case SBLLIB_CORE_ID_DSP2:
            systemReset = PMHAL_PRCM_RG_DSP2_SYS_RST;
            localReset  = PMHAL_PRCM_RG_DSP2_RST;
            break;

        case SBLLIB_CORE_ID_EVE1:
            systemReset = PMHAL_PRCM_RG_EVE1_RST;
            localReset  = PMHAL_PRCM_RG_EVE1_CPU_RST;
            break;

        default:
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Tried to reset Wrong Slave Core \n");
            break;
    }

    /* Check the reset status and clear */
    retVal = PMHALResetGetStatus(localReset, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get Local Reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(localReset);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Failed to clear Local Reset Status \n");
        }
        rstStatus = 0U;
    }
    retVal = PMHALResetGetStatus(systemReset, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get System Reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(systemReset);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Failed to clear System Reset status \n");
        }
        rstStatus = 0U;
    }

    /* Assert the reset */
    retVal = PMHALResetAssert(systemReset);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert System Reset \n");
    }
    retVal = PMHALResetAssert(localReset);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert Local Reset \n");
    }

    /* Clear reset for MMU, Cache and Slave interface OCP port */
    retVal = PMHALResetRelease(systemReset, PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to release System Reset \n");
    }
}

int32_t SBLLibRunTesocTest(uint32_t              testId,
                           const tesocTestCfg_t *tesocTestConfig)
{
    int32_t retVal = STW_SOK;
    pmhalPrcmModuleSIdleState_t idleState;
    pmhalPrcmModuleMStbyState_t standbyState;

    switch (testId)
    {
        case TESOC_TEST_ID_IPU_LBIST:
        case TESOC_TEST_ID_IPU_MBIST:
            if (TRUE == tesocTestConfig->completionIntrEnable)
            {
                /* Configure TESOC Interrupt */
                TESOCIntrEnable(SOC_TESOC_BASE, TESOC_INTR_FLAG_TEST_COMPLETION);
            }

            /* Clear TESOC status registers */
            retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                         tesocTestConfig->domainLabel);

            if (TESOC_TEST_ID_IPU_MBIST == testId)
            {
                /* Set RAM as source of slice execution */
                retVal += TESOCSetSliceSrc(SOC_TESOC_BASE, TESOC_SLICE_SRC_RAM);
            }

            /* Configure TESOC and start the test */
            retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);

            if (STW_SOK != retVal)
            {
                if (TESOC_TEST_ID_IPU_LBIST == testId)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC IPU LBIST Configuration Failed, Aborting Boot\n");
                }
                else
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC IPU MBIST Configuration Failed, Aborting Boot\n");
                }
                SBLLibAbortBoot();
            }

            /* Power down IPU for TESOC to start test */
            retVal = PMHALPdmSetPDState(PMHAL_PRCM_PD_IPU,
                                        PMHAL_PRCM_PD_STATE_OFF,
                                        PM_TIMEOUT_NOWAIT);

            retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU,
                                            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                            PM_TIMEOUT_NOWAIT);

            retVal += PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU1,
                                            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                            PM_TIMEOUT_NOWAIT);
            /*
             * This is required as the force override bit
             * CTRL_CORE_SEC_IPU_WAKEUP does not set the right values for the
             * PRCM registers and when the override is lifted then cores are
             * left in a bad power and reset state.
             */
            retVal += PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU0_RST,
                                        PM_TIMEOUT_NOWAIT);
            retVal += PMHALResetRelease(PMHAL_PRCM_RG_IPU1_RST,
                                        PM_TIMEOUT_NOWAIT);
            retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU1,
                                         PMHAL_PRCM_MODULE_MODE_AUTO,
                                         PM_TIMEOUT_NOWAIT);

            retVal += PMHALPdmSetLastPDStatus(PMHAL_PRCM_PD_IPU,
                                              PMHAL_PRCM_PD_STATE_ON_ACTIVE);

            retVal += PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU1_RST);

            if (PM_SUCCESS != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n PRCM Failed to Power Down IPU, Aborting Boot\n");
                SBLLibAbortBoot();
            }
            /*
             * Set last reset indicator as 0xA to identify TESOC reset
             * 0xA: TESOC Reset
             * TESOC reset indicator should be set after all test
             * configuration is done to avoid async reset issue (warm
             * reset asserted  after TESOC is configured for IPU field
             * test or when test is running). This will minimise false
             * partial boot window due to setting of reset indicator bit.
             */
            HW_WR_FIELD32(
                SOC_SEC_EFUSE_REGISTERS_BASE +
                CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR,
                CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_IPU,
                0xA);

            /* Trigger IPU TESOC test */
            SblLibTriggerIPUTesocTest();
            break;

        case TESOC_TEST_ID_EVE:
            /* Power down EVE for TESOC to start test */
            retVal = PMHALModuleModeSet(
                PMHAL_PRCM_MOD_EVE1,
                PMHAL_PRCM_MODULE_MODE_DISABLED,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMSetCdClockMode(
                (pmhalPrcmCdId_t) PMHAL_PRCM_CD_EVE1,
                PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                PM_TIMEOUT_NOWAIT);

            retVal += PMHALResetAssert(PMHAL_PRCM_RG_EVE1_CPU_RST);
            retVal += PMHALResetAssert(PMHAL_PRCM_RG_EVE1_RST);

            retVal += PMHALPdmSetPDState(
                PMHAL_PRCM_PD_EVE1,
                PMHAL_PRCM_PD_STATE_OFF,
                PM_TIMEOUT_NOWAIT);

            if (PM_SUCCESS != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n PRCM Failed to Power Down EVE, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            if (TRUE == tesocTestConfig->completionIntrEnable)
            {
                /* Configure TESOC Interrupt */
                TESOCIntrEnable(SOC_TESOC_BASE, TESOC_INTR_FLAG_TEST_COMPLETION);
            }

            /* Clear TESOC status registers */
            retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                         tesocTestConfig->domainLabel);

            /* Configure TESOC and start the test */
            retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);

            /* Wait for TESOC to start test */
            retVal += TESOCWaitUntilBusy(SOC_TESOC_BASE,
                                         TESOC_TIMEOUT_TEST_START);
            if (STW_SOK != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n TESOC Start EVE Configuration Failed, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            /* Wait for TESOC test to complete */
            retVal = TESOCWaitUntilNotBusy(SOC_TESOC_BASE,
                                           TESOC_TIMEOUT_TEST_END);
            if (STW_SOK != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n TESOC End EVE Configuration Failed, Aborting Boot\n");
                SBLLibAbortBoot();
            }
            break;

        case TESOC_TEST_ID_DSP1:
            /*
             * For TDA3xx ES1.0 device, DSP has timing issues thus TESOC should
             * be run at lower frequency rather than 48MHz. Hence application
             * should set TESOC_EXT_CLK_DIV as 2.
             */
            /*Power down DSP1 for TESOC to start test */
            retVal = PMHALModuleModeSet(
                PMHAL_PRCM_MOD_DSP1,
                PMHAL_PRCM_MODULE_MODE_DISABLED,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMSetCdClockMode(
                (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP1,
                PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                PM_TIMEOUT_NOWAIT);

            retVal += PMHALResetAssert(PMHAL_PRCM_RG_DSP1_RST);
            retVal += PMHALResetAssert(PMHAL_PRCM_RG_DSP1_SYS_RST);

            retVal += PMHALPdmSetPDState(
                PMHAL_PRCM_PD_DSP1,
                PMHAL_PRCM_PD_STATE_OFF,
                PM_TIMEOUT_NOWAIT);
            if (PM_SUCCESS != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n PRCM Failed to Power Down DSP1, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            if (TRUE == tesocTestConfig->completionIntrEnable)
            {
                /* Configure TESOC Interrupt */
                TESOCIntrEnable(SOC_TESOC_BASE, TESOC_INTR_FLAG_TEST_COMPLETION);
            }

            /* Clear TESOC status registers */
            retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                         tesocTestConfig->domainLabel);

            /* Configure TESOC and start the test */
            retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);

            /* Wait for TESOC to start test */
            retVal += TESOCWaitUntilBusy(SOC_TESOC_BASE,
                                         TESOC_TIMEOUT_TEST_START);
            if (STW_SOK != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n TESOC Start DSP1 Configuration Failed, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            /* Wait for TESOC test to complete */
            retVal = TESOCWaitUntilNotBusy(SOC_TESOC_BASE,
                                           TESOC_TIMEOUT_TEST_END);
            if (STW_SOK != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n TESOC End DSP1 Configuration Failed, Aborting Boot\n");
                SBLLibAbortBoot();
            }
            break;

        case TESOC_TEST_ID_DSP2:
            /*
             * For TDA3xx ES1.0 device, DSP has timing issues thus TESOC should
             * be run at lower frequency rather than 48MHz. Hence application
             * should set TESOC_EXT_CLK_DIV as 2.
             */
            /*Power down DSP2 for TESOC to start test */
            retVal = PMHALModuleModeSet(
                PMHAL_PRCM_MOD_DSP2,
                PMHAL_PRCM_MODULE_MODE_DISABLED,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMSetCdClockMode(
                (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP2,
                PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                PM_TIMEOUT_NOWAIT);

            retVal += PMHALResetAssert(PMHAL_PRCM_RG_DSP2_RST);
            retVal += PMHALResetAssert(PMHAL_PRCM_RG_DSP2_SYS_RST);

            retVal += PMHALPdmSetPDState(
                PMHAL_PRCM_PD_DSP2,
                PMHAL_PRCM_PD_STATE_OFF,
                PM_TIMEOUT_NOWAIT);
            if (PM_SUCCESS != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n PRCM Failed to Power Down DSP2, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            if (TRUE == tesocTestConfig->completionIntrEnable)
            {
                /* Configure TESOC Interrupt */
                TESOCIntrEnable(SOC_TESOC_BASE, TESOC_INTR_FLAG_TEST_COMPLETION);
            }

            /* Clear TESOC status registers */
            retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                         tesocTestConfig->domainLabel);

            /* Configure TESOC and start the test */
            retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);

            /* Wait for TESOC to start test */
            retVal += TESOCWaitUntilBusy(SOC_TESOC_BASE,
                                         TESOC_TIMEOUT_TEST_START);
            if (STW_SOK != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n TESOC Start DSP2 Configuration Failed, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            /* Wait for TESOC test to complete */
            retVal = TESOCWaitUntilNotBusy(SOC_TESOC_BASE,
                                           TESOC_TIMEOUT_TEST_END);
            if (STW_SOK != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n TESOC End DSP2 Configuration Failed, Aborting Boot\n");
                SBLLibAbortBoot();
            }
            break;

        case TESOC_TEST_ID_ISSDSSVIP:
        case TESOC_TEST_ID_ISS:
        case TESOC_TEST_ID_DSS:
        case TESOC_TEST_ID_VIP:
            /* Power down ISS for TESOC to start test */
            retVal = PMHALModuleModeSet(
                PMHAL_PRCM_MOD_ISS,
                PMHAL_PRCM_MODULE_MODE_AUTO,
                PM_TIMEOUT_INFINITE);
            retVal += PMHALCMSetCdClockMode(
                (pmhalPrcmCdId_t) PMHAL_PRCM_CD_ISS,
                PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALPdmSetPDState(
                PMHAL_PRCM_PD_ISS,
                PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALStaticDepDisable(
                PMHAL_PRCM_CD_IPU1,
                PMHAL_PRCM_CD_ISS);
            retVal += PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_ISS, &idleState);
            if (PM_SUCCESS == retVal)
            {
                if (PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL == idleState)
                {
                    PMHALModuleSIdleModeSet(
                        PMHAL_PRCM_MOD_ISS,
                        PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE,
                        PM_TIMEOUT_NOWAIT);
                }
            }

            retVal = PMHALModuleStandbyStatusGet(PMHAL_PRCM_MOD_ISS,
                                                 &standbyState);
            if (PM_SUCCESS == retVal)
            {
                if (PMHAL_PRCM_MODULE_MSTANDBYSTATE_FUNCTIONAL == standbyState)
                {
                    PMHALModuleStandbyModeSet(
                        PMHAL_PRCM_MOD_ISS,
                        PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY,
                        PM_TIMEOUT_NOWAIT);
                }
            }

            retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_ISS,
                                         PMHAL_PRCM_MODULE_MODE_DISABLED,
                                         PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMSetCdClockMode((pmhalPrcmCdId_t) PMHAL_PRCM_CD_ISS,
                                            PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                            PM_TIMEOUT_NOWAIT);
            if (PM_SUCCESS != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n PRCM Failed to Power Down ISS, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            /* Power down DSS for TESOC to start test */
            retVal = PMHALPdmSetPDState(
                PMHAL_PRCM_PD_DSS,
                PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMSetCdClockMode(
                (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSS,
                PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                PM_TIMEOUT_NOWAIT);
            /* Disable clock dependency of modules in DSS_CM_CORE domain */
            retVal += PMHALCMModuleClockEnable(
                PMHAL_PRCM_MOD_DSS,
                PMHAL_PRCM_CLK_DSS_GFCLK,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_DSS,
                                         PMHAL_PRCM_MODULE_MODE_ENABLED,
                                         PM_TIMEOUT_INFINITE);

            retVal += PMHALStaticDepDisableAllSlaveDep(PMHAL_PRCM_CD_DSS);
            retVal += PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_DSS, &idleState);
            if (PM_SUCCESS == retVal)
            {
                if (PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL == idleState)
                {
                    PMHALModuleSIdleModeSet(
                        PMHAL_PRCM_MOD_DSS,
                        PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE,
                        PM_TIMEOUT_NOWAIT);
                }
            }

            retVal = PMHALModuleStandbyStatusGet(PMHAL_PRCM_MOD_DSS,
                                                 &standbyState);
            if (PM_SUCCESS == retVal)
            {
                if (PMHAL_PRCM_MODULE_MSTANDBYSTATE_FUNCTIONAL == standbyState)
                {
                    PMHALModuleStandbyModeSet(
                        PMHAL_PRCM_MOD_DSS,
                        PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY,
                        PM_TIMEOUT_NOWAIT);
                }
            }

            retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_DSS,
                                         PMHAL_PRCM_MODULE_MODE_DISABLED,
                                         PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMSetCdClockMode((pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSS,
                                            PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                                            PM_TIMEOUT_NOWAIT);
            /* Disable clock dependency of modules in DSS_CM_CORE domain */
            retVal += PMHALCMModuleClockDisable(
                PMHAL_PRCM_MOD_DSS,
                PMHAL_PRCM_CLK_HDMI_CEC_GFCLK,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMModuleClockDisable(
                PMHAL_PRCM_MOD_DSS,
                PMHAL_PRCM_CLK_HDMI_PHY_GFCLK,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMModuleClockDisable(
                PMHAL_PRCM_MOD_DSS,
                PMHAL_PRCM_CLK_DSS_GFCLK,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMModuleClockDisable(
                PMHAL_PRCM_MOD_DSS,
                PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMModuleClockDisable(
                PMHAL_PRCM_MOD_DSS,
                PMHAL_PRCM_CLK_HDMI_DPLL_CLK,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMModuleClockDisable(
                PMHAL_PRCM_MOD_DSS,
                PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK,
                PM_TIMEOUT_NOWAIT);
            if (PM_SUCCESS != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n PRCM Failed to Power Down DSS, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            /*Power down VIP for TESOC to start test */
            retVal = PMHALModuleModeSet(
                PMHAL_PRCM_MOD_VIP1,
                PMHAL_PRCM_MODULE_MODE_AUTO,
                PM_TIMEOUT_INFINITE);
            retVal += PMHALCMSetCdClockMode(
                (pmhalPrcmCdId_t) PMHAL_PRCM_CD_CAM,
                PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALPdmSetPDState(
                PMHAL_PRCM_PD_CAM,
                PMHAL_PRCM_PD_STATE_ON_ACTIVE,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_VIP1, &idleState);
            if (PM_SUCCESS == retVal)
            {
                if (PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL == idleState)
                {
                    PMHALModuleSIdleModeSet(
                        PMHAL_PRCM_MOD_VIP1,
                        PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE,
                        PM_TIMEOUT_NOWAIT);
                }
            }

            retVal = PMHALModuleStandbyStatusGet(PMHAL_PRCM_MOD_VIP1,
                                                 &standbyState);
            if (PM_SUCCESS == retVal)
            {
                if (PMHAL_PRCM_MODULE_MSTANDBYSTATE_FUNCTIONAL == standbyState)
                {
                    PMHALModuleStandbyModeSet(
                        PMHAL_PRCM_MOD_VIP1,
                        PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY,
                        PM_TIMEOUT_NOWAIT);
                }
            }

            retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_VIP1,
                                         PMHAL_PRCM_MODULE_MODE_DISABLED,
                                         PM_TIMEOUT_NOWAIT);
            retVal += PMHALCMSetCdClockMode((pmhalPrcmCdId_t) PMHAL_PRCM_CD_CAM,
                                            PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                                            PM_TIMEOUT_NOWAIT);
            if (PM_SUCCESS != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n PRCM Failed to Power Down VIP, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            if (TRUE == tesocTestConfig->completionIntrEnable)
            {
                /* Configure TESOC Interrupt */
                TESOCIntrEnable(SOC_TESOC_BASE, TESOC_INTR_FLAG_TEST_COMPLETION);
            }

            /* Clear TESOC status registers */
            retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                         tesocTestConfig->domainLabel);

            /* Configure TESOC and start the test */
            retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);

            /*
             * Dummy Trigger to start TESOC without powering down ISS/VIP/DSS
             */
            /* Unlock TESOC MMR */
            TESOCUnlockMMR(SOC_TESOC_BASE);
            HW_WR_FIELD32(SOC_TESOC_BASE + TESOC_MISC_CONFIG,
                          TESOC_MISC_CONFIG_DUMMY_TRIGGER17, 0x1);
            HW_WR_FIELD32(SOC_TESOC_BASE + TESOC_MISC_CONFIG,
                          TESOC_MISC_CONFIG_DUMMY_TRIGGER18, 0x1);
            HW_WR_FIELD32(SOC_TESOC_BASE + TESOC_MISC_CONFIG,
                          TESOC_MISC_CONFIG_DUMMY_TRIGGER17, 0x0);
            /* Lock TESOC MMR */
            TESOCLockMMR(SOC_TESOC_BASE);

            /* Wait for TESOC to start test */
            retVal += TESOCWaitUntilBusy(SOC_TESOC_BASE,
                                         TESOC_TIMEOUT_TEST_START);

            if (STW_SOK != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n TESOC Start ISS/DSS/VIP Configuration Failed, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            /* Wait for TESOC test to complete */
            retVal = TESOCWaitUntilNotBusy(SOC_TESOC_BASE,
                                           TESOC_TIMEOUT_TEST_END);
            if (STW_SOK != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n TESOC End ISS/DSS/VIP Configuration Failed, Aborting Boot\n");
                SBLLibAbortBoot();
            }

            /* Power down modules after TESOC test */
            retVal = PMHALPdmSetPDState(
                PMHAL_PRCM_PD_ISS,
                PMHAL_PRCM_PD_STATE_OFF,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALPdmSetPDState(
                PMHAL_PRCM_PD_DSS,
                PMHAL_PRCM_PD_STATE_OFF,
                PM_TIMEOUT_NOWAIT);
            retVal += PMHALPdmSetPDState(
                PMHAL_PRCM_PD_CAM,
                PMHAL_PRCM_PD_STATE_OFF,
                PM_TIMEOUT_NOWAIT);
            if (PM_SUCCESS != retVal)
            {
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_ERROR,
                    "\n PRCM Failed to Disable ISS/DSS/VIP, Aborting Boot\n");
                SBLLibAbortBoot();
            }
            break;

        default:
            /* To remove MISRA C error */
            break;
    }

    return retVal;
}

int32_t SBLLibCheckTesocTestResult(const tesocTestCfg_t *tesocTestConfig)
{
    /* Return  TESOC test results */
    return TESOCCheckTestResult(SOC_TESOC_BASE, tesocTestConfig);
}

int32_t SBLLibRegisterImageCopyCallback(SBLLibMediaReadFxn mediaReadFxn,
                                        SBLLibDDRReadFxn   ddrReadFxn,
                                        SBLLibSeekFxn      seekFxn)
{
    int32_t retVal = STW_SOK;
    if ((mediaReadFxn != NULL) && (ddrReadFxn != NULL) && (seekFxn != NULL))
    {
        gMediaReadFxn = mediaReadFxn;
        gDDRReadFxn   = ddrReadFxn;
        gSeekFxn      = seekFxn;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

int32_t SBLLibRegisterCRCCallback(SBLLibCalculateCRCFxn calculateCRCFxn)
{
    int32_t retVal = STW_SOK;
    if (calculateCRCFxn != NULL)
    {
        gCalculateCRCFxn = calculateCRCFxn;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static inline void SblLibWaitForInterrupt(void)
{
    asm (" WFI");
}

static void SblLibConfigTimer3(uint32_t waitCount)
{
    /* Force Wake-up clock domain L4PER1 */
    PMHALCMSetCdClockMode(PMHAL_PRCM_CD_L4PER1,
                          PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                          PM_TIMEOUT_INFINITE);

    /* Enable TIMER3 module */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER3,
                       PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);

    /* Reset the TIMER3 module */
    TIMERReset(SOC_TIMER3_BASE);

    /* Enable suspension in emulation mode */
    TIMEREmuModeConfigure(SOC_TIMER3_BASE, TIMER_FROZEN);

    /* Load the counter with the initial count value */
    TIMERCounterSet(SOC_TIMER3_BASE, SBL_LIB_TIMER_START_COUNT);

    /* Load the compare register with the wait count value */
    TIMERCompareSet(SOC_TIMER3_BASE, waitCount);

    /* Configure the Timer for One-shot and compare mode */
    TIMERModeConfigure(SOC_TIMER3_BASE, TIMER_ONESHOT_CMP_ENABLE);

    /* Enable the Timer Match Interrupt */
    TIMERIntEnable(SOC_TIMER3_BASE, TIMER_INT_MAT_EN_FLAG);
}

static void SblLibSetIPUIdle(void)
{
    /*
     * PRCM Override should be removed to allow the IPU to go to low power
     * state.
     */
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_IPU_WAKEUP,
                  CTRL_CORE_SEC_IPU_WAKEUP_WKUP_EN,
                  0x00);

    /* Set IPU in deep sleep to set CM standby */
    HW_WR_FIELD32(SOC_IPU1_C0_INTC_BASE + IPU_M4_NVIC_SYSTEM_CONTROL,
                  IPU_M4_NVIC_SYSTEM_CONTROL_SLEEPDEEP,
                  0x01);

    HW_WR_FIELD32(SOC_IPU1_MMU_BASE + IPU_MMU_SYSCONFIG,
                  IPU_MMU_SYSCONFIG_IDLEMODE,
                  IPU_MMU_SYSCONFIG_IDLEMODE_SSIDLE);

    /* Set StandBy Core Sysconfig  */
    HW_WR_FIELD32(SOC_IPU1_WUGEN_BASE + IPU_STANDBY_CORE_SYSCONFIG,
                  IPU_STANDBY_CORE_SYSCONFIG_STANDBYMODE,
                  0x3);

    /* Set Idle Core Sysconfig */
    HW_WR_FIELD32(SOC_IPU1_WUGEN_BASE + IPU_IDLE_CORE_SYSCONFIG,
                  IPU_IDLE_CORE_SYSCONFIG_IDLEMODE,
                  0x3);
}

static void SblLibTriggerIPUTesocTest(void)
{
    /* Put IPU in IDLE state */
    SblLibSetIPUIdle();

    /* Configure Timer3 */
    SblLibConfigTimer3(SBL_LIB_TIMER_IPU_POWER_DOWN_COUNT);

    /* Unlock TESOC MMR */
    TESOCUnlockMMR(SOC_TESOC_BASE);

    /* Set Dummy Triggers to Start Test */
    HW_WR_FIELD32((SOC_TESOC_BASE +
                   TESOC_DOMAIN_EN_DOM(TESOC_DOMAIN_LABEL_ISSDSSVIP)),
                  TESOC_DOMAIN_EN_DOM_START,
                  TESOC_DOMAIN_EN_DOM_START_TO_START);
    HW_WR_FIELD32(SOC_TESOC_BASE + TESOC_MISC_CONFIG,
                  TESOC_MISC_CONFIG_DUMMY_TRIGGER17, 0x1);
    HW_WR_FIELD32(SOC_TESOC_BASE + TESOC_MISC_CONFIG,
                  TESOC_MISC_CONFIG_DUMMY_TRIGGER18, 0x1);
    HW_WR_FIELD32(SOC_TESOC_BASE + TESOC_MISC_CONFIG,
                  TESOC_MISC_CONFIG_DUMMY_TRIGGER17, 0x0);

    /* Lock TESOC MMR */
    TESOCLockMMR(SOC_TESOC_BASE);

    /* Start the Timer */
    TIMEREnable(SOC_TIMER3_BASE);

    /* Wait for Timer Interrupt */
    while (TIMER_INT_MAT_IT_FLAG != TIMERIntRawStatusGet(SOC_TIMER3_BASE))
    {
        /* Busy Loop */
    }

    SblLibWaitForInterrupt();
}

