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
/**
 *   Component:         SBL
 *
 *   Filename:          sbl_rprc_parse.c
 *
 *   Description:      This file contains functions to parse the multi-core
 *                     image file & loads into CPU internal memory & enternal
 *                     memory.
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include "soc_defines.h"
#include "sbl_rprc_parse.h"
#include "sbl_tda2xx_platform.h"
#include "platform.h"
#include "cp15.h"
#include "edma.h"
#include "uartStdio.h"

#if defined (MMCSD) || defined (SBL_REGRESSION)
#include "hsmmcsd_API.h"
#elif defined (NOR)

#elif defined (QSPI)
#include "qspi.h"
#include "qspi_flash.h"
#elif defined (ZEBU_DDR3)

#else
#error Unsupported boot mode !!
#endif

/* ============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

#ifdef SBL_REGRESSION
extern uint32_t           SBL_REGRESSION_LOG_BFR_SEG;
sbl_regression_log_bfr_t *sbl_regression_log_bfr_ptr;

#endif

#if defined (MMCSD) || defined (SBL_REGRESSION)
FIL gAppImageSDFilePtr;
#endif
/* ============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */

extern uint32_t           entryPoint_MPU_CPU0, entryPoint_MPU_CPU1;
extern uint32_t           entryPoint_IPU1_CPU0, entryPoint_IPU1_CPU1;
extern uint32_t           entryPoint_IPU2_CPU0, entryPoint_IPU2_CPU1;
extern uint32_t           entryPoint_DSP1, entryPoint_DSP2;
extern uint32_t           entryPoint_EVE1, entryPoint_EVE2, entryPoint_EVE3,
                          entryPoint_EVE4;

/* ============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */
#if defined (MMCSD) || defined (SBL_REGRESSION)
uint32_t My_FileRead(void *buff, uint32_t fileAddr, uint32_t btr);
void My_FileSeek(uint32_t *fileptr, uint32_t location);
#elif defined (NOR)
void NOR_seek(uint32_t *srcAddr, uint32_t location);
uint32_t NORReadLocal(void *dstAddr, uint32_t srcOffsetAddr, uint32_t length);
void SBL_NORRead_word(void *dst1, uint32_t offsetPtr, uint32_t length);
void SBL_NORRead_edma(const void *dstAddr, uint32_t srcOffsetAddr,
                      uint32_t length,
                      uint32_t edma_ch_num);
#elif defined (QSPI)
extern uint32_t QSPI_ReadSectors(void *dstAddr, uint32_t srcOffsetAddr,
                                 uint32_t length);
uint32_t SBL_QSPI_ReadSectors(void *dstAddr, uint32_t srcOffsetAddr,
                              uint32_t length);
#endif

int32_t MulticoreImageParse(uint32_t ImageOffset);
static int32_t RprcImageParse(uint32_t srcAddr, uint32_t *entryPoint,
                              int32_t CoreId);
void BootCore(uint32_t entry, uint32_t CoreID);
char *my_itoa(int32_t i);

uint32_t (*fp_readData)(void *dstAddr, uint32_t srcAddr,
                        uint32_t length) = NULL;
void     (*fp_seek)(uint32_t *srcAddr, uint32_t location) = NULL;

/* ============================================================================
 *                          Local function
 * =============================================================================
 */
#define INT_DIGITS 19       /* enough for 64 bit integer */

char *my_itoa(int32_t i)
{
    /* Room for INT_DIGITS digits, - and '\0' */
    static char buf[INT_DIGITS + 2];
    char       *p = buf + INT_DIGITS + 1; /* points to terminating '\0' */
    if (i >= 0)
    {
        do {
            --p;
            *p = (int32_t) '0' + (i % 10);
            i /= 10;
        } while (i != 0);
    }
    else              /* i < 0 */
    {
        do {
            --p;
            *p = (int32_t) '0' - (i % 10);
            i /= 10;
        } while (i != 0);
        --p;
        *p = (int32_t) '-';
    }
    return p;
}

/* ============================================================================
 *                          MMCSD RPRC parse functions
 * =============================================================================
 */
#if defined (MMCSD) || defined (SBL_REGRESSION)

/**
 * \brief       My_FileRead function reads N bytes from SD card and
 *              advances the cursor.
 *
 * \param[out]  value - Pointer to data buffer
 * \param[in]       srcAddr - Read head pointer
 * \param[in]       size - Number of bytes to read
 *
 *
 * \return            Error code on file error
 */
uint32_t My_FileRead(void    *buff,
                     uint32_t fileAddr,
                     uint32_t btr)
{
    uint8_t *buffptr    = (uint8_t *) buff;
    uint32_t bytes_read = 0;
    FRESULT  fresult    = FR_OK;

    fresult = f_read(&gAppImageSDFilePtr, (void *) buffptr, btr,
                     (UINT *) &bytes_read);
    if ((fresult != FR_OK) || (btr != bytes_read))
    {
        fresult = FR_INVALID_DRIVE;
    }

    return fresult;
}

/**
 * \brief       My_FileSeek function to move the read head by n bytes
 *
 * \param[in]  srcAddr - Read head pointer
 * \param[in]   location - Move the read head pointer by n bytes
 *
 *
 * \return  none
 */
void My_FileSeek(uint32_t *fileptr, uint32_t location)
{
    f_lseek(&gAppImageSDFilePtr, location);
}

/**
 * \brief       MMCSDBootRprc function parse the multi-core app
 *              image stored in the SD card. It Parses the AppImage
 *              file & copies the section
 *              into CPU internal memory & external memory.
 *              CPU entry locations are stored into entry point
 *              global pointers.
 *
 *
 * \param               none
 *
 *
 * \return      error status.If error has occured it returns a non zero
 *                value.
 *              If no error has occured then return status will be
 *              zero.
 */
int32_t MMCSDBootRprc(void)
{
    int32_t    ret;
    char      *filename = "AppImage";
    FRESULT    fresult;
    MMC_INST_t num;

    SBL_PRINTF(TRACE_LOW, "\n SD Boot - SD Init \n");

    num = MMC1_INST;

    if (HSMMCSDInit(num) != 0)
    {
        SBL_PRINTF(TRACE_HIGH, "\n No valid SD card \n");
        ret = -1;
    }
    else
    {
        SBL_PRINTF(TRACE_LOW, "\n SD Boot - file open \n");

        fresult = f_open(&gAppImageSDFilePtr, filename, (uint8_t) FA_READ);
        if (fresult != FR_OK)
        {
            SBL_PRINTF(TRACE_HIGH, "\n SD Boot - File open fails \n");
            ret = E_FAIL;
        }
        else
        {
            SBL_PRINTF(TRACE_LOW,
                       "\n SD Boot - file open completed sucessfully \n");

            fp_readData = &My_FileRead;
            fp_seek     = &My_FileSeek;

            ret = MulticoreImageParse(0);

            f_close(&gAppImageSDFilePtr);
        }
    }
    return ret;
}

/**
 * \brief                   MMCSDBootRprc_Regression function
 *
 *
 * \param               none
 *
 *
 * \return            error status.If error has occured it returns a non zero
 *                  value.
 *                 If no error has occured then return status will be
 *                 zero.
 */
#ifdef  SBL_REGRESSION
int32_t MMCSDBootRprc_Regression(void)
{
    int32_t    ret;
    char       filename[50] = "TC";
    char      *str_dv_test_no;
    int32_t    dv_test_no, dv_prev_no;
    int32_t    dv_prev_test_result;
    FIL        fp;
    FRESULT    fresult;
    uint32_t   regval;
    uint8_t    isPOR = 0;
    MMC_INST_t num;

    SBL_PRINTF(TRACE_LOW, "\n SD Boot - SD Init \n");

    num = MMC1_INST;

    if (HSMMCSDInit(num) != 0)
    {
        SBL_PRINTF(TRACE_REG, "\n No valid SD card \n");
        return -1;
    }

    SBL_PRINTF(TRACE_LOW, "\n SD Boot - file open \n");

    /*Point the SBL regression log bfr to SBL_REGRESSION_LOG_BFR_SEG*/
    sbl_regression_log_bfr_ptr =
        (sbl_regression_log_bfr_t *) SBL_REGRESSION_LOG_BFR_SEG;

    /*Read the pattern - If Magic string breaks it is a POR reset*/

    if (sbl_regression_log_bfr_ptr->sbl_regression_magic_string_r1 !=
        SBL_REGRESSION_MAGIC_STRING_P1)
    {
        isPOR = 1;
    }
    else if (sbl_regression_log_bfr_ptr->sbl_regression_magic_string_r2 !=
             SBL_REGRESSION_MAGIC_STRING_P2)
    {
        isPOR = 1;
    }
    else if (sbl_regression_log_bfr_ptr->sbl_regression_magic_string_r3 !=
             SBL_REGRESSION_MAGIC_STRING_P3)
    {
        isPOR = 1;
    }
    else if (sbl_regression_log_bfr_ptr->sbl_regression_magic_string_r4 !=
             SBL_REGRESSION_MAGIC_STRING_P4)
    {
        isPOR = 1;
    }

    /*Start of regression test - Print Die info & RST the count to 0*/
    if (isPOR)
    {
        SBL_PRINTF(TRACE_REG, "\n SBL Regression Ver 1.3 \n");
        SBL_PRINTF(TRACE_REG, "\n Device Die ID \n");
        regval = HW_RD_REG32(DV_DIE_ID0);
        SBL_PRINTF(TRACE_REG, "DIE_ID0: ");
        UARTPutHexNum(regval);
        SBL_PRINTF(TRACE_REG, "\n");

        regval = HW_RD_REG32(DV_DIE_ID1);
        SBL_PRINTF(TRACE_REG, "DIE_ID1: ");
        UARTPutHexNum(regval);
        SBL_PRINTF(TRACE_REG, "\n");

        regval = HW_RD_REG32(DV_DIE_ID2);
        SBL_PRINTF(TRACE_REG, "DIE_ID2: ");
        UARTPutHexNum(regval);
        SBL_PRINTF(TRACE_REG, "\n");

        regval = HW_RD_REG32(DV_DIE_ID3);
        SBL_PRINTF(TRACE_REG, "DIE_ID3: ");
        UARTPutHexNum(regval);
        SBL_PRINTF(TRACE_REG, "\n");

        /* Set the count to zero */
        sbl_regression_log_bfr_ptr->sbl_regression_tc_track_reg = 0x0;
    }

    /*Read the test case number*/
    dv_test_no  = sbl_regression_log_bfr_ptr->sbl_regression_tc_track_reg;
    dv_test_no &= 0xffff;

    dv_prev_no = dv_test_no - 1;

    /**Open the testcase ***/
    str_dv_test_no = my_itoa(dv_test_no);
    strcat(filename, str_dv_test_no);

    fresult = f_open(&fp, filename, FA_READ);
    if (fresult != FR_OK)
    {
        SBL_PRINTF(TRACE_REG, "\n SD Boot - File open fails \n");
        ret = E_FAIL;
        goto regression_end;
    }

    SBL_PRINTF(TRACE_REG, "\n DV test case # ");
    SBL_PRINTF(TRACE_REG, filename);

    fp_readData = My_FileRead;
    fp_seek     = My_FileSeek;

    ret = MulticoreImageParse(0);

    f_close(&fp);

    if (ret == 0)
    {
        ++dv_test_no;
        sbl_regression_log_bfr_ptr->sbl_regression_tc_track_reg = dv_test_no;

        /*Read the previous test result*/
        dv_prev_test_result =
            sbl_regression_log_bfr_ptr->sbl_regression_tc_result_reg;
        dv_prev_test_result &= 0xffff;

        if (dv_prev_no >= 0)
        {
            SBL_PRINTF(TRACE_REG, "\n DV test case result #    ");
            UARTPutNum(dv_prev_no);
            SBL_PRINTF(TRACE_REG, "    : ");
            UARTPutHexNum(dv_prev_test_result);
        }
    }

    /*Write the Magic String into OCMC RAM*/
    sbl_regression_log_bfr_ptr->sbl_regression_magic_string_r1 =
        SBL_REGRESSION_MAGIC_STRING_P1;
    sbl_regression_log_bfr_ptr->sbl_regression_magic_string_r2 =
        SBL_REGRESSION_MAGIC_STRING_P2;
    sbl_regression_log_bfr_ptr->sbl_regression_magic_string_r3 =
        SBL_REGRESSION_MAGIC_STRING_P3;
    sbl_regression_log_bfr_ptr->sbl_regression_magic_string_r4 =
        SBL_REGRESSION_MAGIC_STRING_P4;

regression_end:
    if (ret == E_FAIL)
    {
        /*Last test result*/
        dv_prev_no = dv_test_no - 1;

        /*Read the previous test result*/
        dv_prev_test_result =
            sbl_regression_log_bfr_ptr->sbl_regression_tc_result_reg;
        dv_prev_test_result &= 0xffff;

        SBL_PRINTF(TRACE_REG, "\n DV test case result #  ");
        UARTPutNum(dv_prev_no);
        SBL_PRINTF(TRACE_REG, "  : ");
        UARTPutHexNum(dv_prev_test_result);

        SBL_PRINTF(TRACE_REG, "\n ========================================\n");
        SBL_PRINTF(TRACE_REG, "    Successful Completion of regression test ");
        SBL_PRINTF(TRACE_REG, "\n ========================================\n");
    }

    return ret;
}

#endif

/******************************************************************************
**                       NOR RPRC parse functions
*******************************************************************************/
#elif defined (NOR)

void SBL_NORRead_word(void *dst1, uint32_t offsetPtr, uint32_t length)
{
    uint32_t  i;
    uint32_t *psrc = (uint32_t *) (NOR_BASE_ADDRESS + offsetPtr);
    uint32_t *pdst = (uint32_t *) dst1;

    for (i = 0; i < length / 4; i++)
    {
        *pdst = *psrc;
        pdst++;
        psrc++;
    }
}

void SBL_NORRead_edma(const void *dstAddr, uint32_t srcOffsetAddr,
                      uint32_t length,
                      uint32_t edma_ch_num)
{
    EDMA3CCPaRAMEntry edmaParam;
    uint32_t          bCntValue = 1U;
    uint32_t          remBytes  = 0;
    uint32_t          aCntValue = length;
    uint32_t          addr      = (uint32_t) (dstAddr);
    uint32_t          max_acnt  = 0x7FFFU;

    if (length > max_acnt)
    {
        bCntValue = (length / max_acnt);
        remBytes  = (length % max_acnt);
        aCntValue = max_acnt;
    }

    /* Compute QSPI address and size */
    edmaParam.opt      = 0;
    edmaParam.srcAddr  = NOR_BASE_ADDRESS + srcOffsetAddr;
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
         ((edma_ch_num <<
           EDMA_TPCC_OPT_TCC_SHIFT) &
          EDMA_TPCC_OPT_TCC_MASK) | EDMA_TPCC_OPT_SYNCDIM_MASK);

    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edma_ch_num, &edmaParam);
    EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edma_ch_num, EDMA3_TRIG_MODE_MANUAL);

    while ((EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
            ((uint32_t) 1 << edma_ch_num)) == 0)
    {
        /* Busy Loop */
    }
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edma_ch_num);
    if (remBytes != 0)
    {
        /* Compute QSPI address and size */
        edmaParam.opt     = 0;
        edmaParam.srcAddr =
            (NOR_BASE_ADDRESS +
             ((bCntValue * max_acnt) + srcOffsetAddr));
        edmaParam.destAddr = (addr + (max_acnt * bCntValue));
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
             ((edma_ch_num << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE, edma_ch_num, &edmaParam);
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE, edma_ch_num,
                            EDMA3_TRIG_MODE_MANUAL);

        while ((EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE) &
                ((uint32_t) 1 << edma_ch_num)) == 0)
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE, edma_ch_num);
    }
}

/**
 * \brief       NORReadLocal function reads N bytes from NOR memory
 *              and advances the cursor.
 *
 * \param[out]      dstAddr - Pointer to data buffer
 * \param[in]       srcOffsetAddr - NOR memory Offset address
 * \param[in]       length - Number of bytes to read
 *
 *
 * \return            Error code on NOR read
 */
uint32_t NORReadLocal(void *dstAddr, uint32_t srcOffsetAddr, uint32_t length)
{
    /* Read from QSPI */
    if (length < 64U)
    {
        SBL_NORRead_word(dstAddr, srcOffsetAddr, length);
    }
    else  /*DMA Mode*/
    {
        SBL_NORRead_edma(dstAddr, srcOffsetAddr, length, 1U);
    }

    return 1U;
}

/**
 * \brief               NOR_seek function to move the read head by n bytes
 *
 * \param[in]  srcAddr - Read head pointer
 * \param[in]   location - Move the read head pointer by n bytes
 *
 *
 * \return  none
 */
void NOR_seek(uint32_t *srcAddr, uint32_t location)
{
    *srcAddr = location;
}

/**
 * \brief            NORBootRprc function parse the multi-core app image
 *                   stored in the NOR Flash.
 *                   It Parses the AppImage & copies the section into CPU
 *                   internal memory & external memory.
 *                   CPUs entry loctions are stored into entry point
 *                   global pointers.
 *
 *
 * \param               none
 *
 *
 * \return            error status.If error has occured it returns a non zero
 *                    value.
 *                    If no error has occured then return status will be
 *                     zero.
 */
int32_t NORBootRprc(void)
{
    fp_readData = &NORReadLocal;

    fp_seek = &NOR_seek;

    return (MulticoreImageParse(NOR_OFFSET_SI));
}

/******************************************************************************
**                       QSPI RPRC parse functions
*******************************************************************************/
#elif defined (QSPI)

uint32_t SBL_QSPI_ReadSectors(void *dstAddr, uint32_t srcOffsetAddr,
                              uint32_t length)
{
    /* Read from QSPI */
    if (length < 64U)
    {
        QSPI_ReadSectors(dstAddr, srcOffsetAddr, length);
    }
    else  /*DMA Mode*/
    {
        QSPI_ReadSectors_edma(dstAddr,
                              srcOffsetAddr,
                              length,
                              (uint32_t) 1);
    }

    return 1U;
}

/**
 * \brief           QSPIBootRprc function parse the multi-core app image
 *                  stored in the QSPI serial flash.
 *                  It Parses the AppImage & copies the section into CPU
 *                  internal memory & external memory.
 *                  CPUs entry loctions are stored into entry point
 *                  global pointers.
 *
 *
 * \param               none
 *
 *
 * \return          error status.If error has occured it returns a non zero
 *                  value.
 *                  If no error has occured then return status will be
 *                  zero.
 */

int32_t QSPIBootRprc(void)
{
    qspi_DeviceType_e DeviceType = DEVICE_TYPE_QSPI4;
    uint32_t          device_Id;

    QSPI_Initialize(DeviceType);

    /*Print the Dev ID & Mfg ID*/

    device_Id = QSPI_GetDeviceId();

    UARTPuts("\nMID - ", -1);
    UARTPutHexNum(device_Id & 0xFFU);
    UARTPuts("\nDID - ", -1);
    UARTPutHexNum((device_Id & 0xFF0000U) >> 16);

    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
    QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                        QSPI_CS0);

    fp_readData = &SBL_QSPI_ReadSectors;
    fp_seek     = &QSPI_seek;

    return (MulticoreImageParse(QSPI_OFFSET_SI));
}

/******************************************************************************
**                       ZEBU RPRC parse functions
*******************************************************************************/
#elif defined (ZEBU_DDR3)

/**
 * \brief       DDR3ReadLocal function reads N bytes from DDR memory
 *              and advances the cursor.
 *
 * \param[out]  dst1 - Pointer to data buffer
 * \param[in]       offsetPtr - Read head pointer
 * \param[in]       length - Number of bytes to read
 *
 *
 * \return            Error code
 */
uint32_t DDR3ReadLocal(void *dst1, void *offsetPtr, uint32_t length)
{
    uint32_t  i;
    uint16_t *psrc8 = (uint16_t *) 0x80000000;
    uint16_t *pdst8 = (uint16_t *) dst1;

    /*Make the application images are word aligned*/
    psrc8 += *((uint32_t *) (offsetPtr)) >> 1;

    for (i = 0; i < length; )
    {
        *pdst8++ = *psrc8++;
        i        = i + 2;
    }

    return 0;
}

/**
 * \brief       DR3_seek function to move the read head by n bytes
 *
 * \param[in]  srcAddr - Read head pointer
 * \param[in]   location - Move the read head pointer by n bytes
 *
 *
 * \return  none
 */
void DDR3_seek(void *srcAddr, uint32_t location)
{
    *((uint32_t *) srcAddr) = location;
}

/**
 * \brief       DDR3BootRprc function parse the multi-core app image
 *              stored in the DDR.
 *              It Parses the AppImage & copies the section into CPU
 *              internal memory & external memory.
 *              CPUs entry loctions are stored into entry point
 *              global pointers.
 *
 *
 * \param               none
 *
 *
 * \return         error status.If error has occured it returns a non zero
 *                 value.
 *                 If no error has occured then return status will be
 *                 zero.
 */
int32_t DDR3BootRprc(void)
{
    uint32_t offset = 0x0;

    fp_readData = DDR3ReadLocal;

    fp_seek = DDR3_seek;

    return (MulticoreImageParse(0x0));
}

#endif

/**
 * \brief                   MulticoreImageParse function parses the multi-core
 *                          app image.
 *                          Read the image header & check for AppImage.
 *                          Device ID field confirms the boot device ID.
 *                          parses the meta header & finds the number
 *                          executables
 *                          Parses & load each section into CPU internal memory
 *                          & external memory
 *
 * \param[in]       srcAddr - Start address of AppImage
 *                          ImageOffset - Dummy
 *
 * \return            error status.If error has occured it returns a non zero
 *                     value.
 *                     If no error has occured then return status will be
 *                     zero.
 */

int32_t MulticoreImageParse(uint32_t ImageOffset)
{
    uint32_t            i;
    uint32_t            entryPoint = 0;
    meta_header_start_t mHdrStr;
    meta_header_core_t  mHdrCore[MAX_INPUT_FILES];
    meta_header_end_t   mHdrEnd;
    int32_t magic_str = META_HDR_MAGIC_STR;
    int32_t retVal    = E_PASS;
    uint32_t            currAppImageAddr = ImageOffset;

    if ((fp_readData == NULL) || (fp_seek == NULL))
    {
        retVal = E_FAIL;
    }
    else
    {
        /* Read Meta Header Start and get the Number of Input RPRC Files */
        fp_readData(&mHdrStr, currAppImageAddr, sizeof (meta_header_start_t));
        currAppImageAddr += sizeof (meta_header_start_t);
        if (mHdrStr.magic_str != (uint32_t) magic_str)
        {
            UARTPuts("Invalid magic number in Single image header\r\n", -1);
            retVal = E_FAIL;
        }
        else
        {
            if (mHdrStr.dev_id != GetDeviceId())
            {
                SBL_PRINTF(TRACE_HIGH, "\nWARNING: Device Id Doesnot match\r\n");
            }

            /* Read all the Core offset addresses */
            for (i = 0; i < mHdrStr.num_files; i++)
            {
                fp_readData(&mHdrCore[i], currAppImageAddr,
                            sizeof (meta_header_core_t));
                currAppImageAddr += sizeof (meta_header_core_t);
            }

            /* Add Base Offset address for All core Image start offset */
            for (i = 0; i < mHdrStr.num_files; i++)
            {
                mHdrCore[i].image_offset += ImageOffset;
            }

            /* Read Meta Header End */
            fp_readData(&mHdrEnd, currAppImageAddr, sizeof (meta_header_end_t));
            currAppImageAddr += sizeof (meta_header_end_t);
            /* Now Parse Individual RPRC files */

            for (i = 0; i < mHdrStr.num_files; i++)
            {
                if (mHdrCore[i].core_id != (0xFFFFFFFFU))
                {
                    fp_seek(&currAppImageAddr, mHdrCore[i].image_offset);
                    if (RprcImageParse(currAppImageAddr, &entryPoint,
                                       mHdrCore[i].core_id) != E_PASS)
                    {
                        /* Error occurred parsing the RPRC file continue to
                         * parsing next
                         * image and skip booting the particular core */
                        retVal = E_FAIL;
                    }
                    else
                    {
                        BootCore(entryPoint, mHdrCore[i].core_id);
                    }
                }
            }
        }
    }
    return retVal;
}

/**
 * \brief           RprcImageParse function parse the RPRC executable image.
 *                  Copies individual section into destination location
 *
 * \param[in]    srcAddr - Pointer RPRC image
 * \param[out] entryPoint - CPU entry point address
 * \param[in]    CoreId - CPU ID to identify the CPU core
 *
 *
 * \return uint32_t: Status (success or failure)
 */
static int32_t RprcImageParse(uint32_t srcAddr, uint32_t *entryPoint,
                              int32_t CoreId)
{
    rprcFileHeader_t    header;
    rprcSectionHeader_t section;
    int32_t  i;
    int32_t  retVal = E_PASS;
    uint32_t currRprcImageAddr = srcAddr;

    /*read application image header*/
    fp_readData(&header, currRprcImageAddr, sizeof (rprcFileHeader_t));
    currRprcImageAddr += sizeof (rprcFileHeader_t);

    /*check magic number*/
    if (header.magic != RPRC_MAGIC_NUMBER)
    {
        UARTPuts("Invalid magic number in boot image\r\n", -1);
        retVal = E_FAIL;
    }
    else
    {
        /* Set the Entry Point */
        *entryPoint = header.entry;

        /*read entrypoint and copy sections to memory*/
        for (i = 0; i < header.SectionCount; i++)
        {
            /*read new section header*/
            fp_readData(&section, currRprcImageAddr,
                        sizeof (rprcSectionHeader_t));
            currRprcImageAddr += sizeof (rprcSectionHeader_t);
#if defined (TDA2XX_BUILD)
            if (((section.addr >= SOC_OCMC_RAM1_BASE) &&
                 (section.addr < (SOC_OCMC_RAM1_BASE + SOC_OCMC_RAM1_SIZE))) ||
                ((section.addr >= SOC_OCMC_RAM2_BASE) &&
                 (section.addr < (SOC_OCMC_RAM2_BASE + SOC_OCMC_RAM2_SIZE))) ||
                ((section.addr >= SOC_OCMC_RAM3_BASE) &&
                 (section.addr < (SOC_OCMC_RAM3_BASE + SOC_OCMC_RAM3_SIZE))))
#elif defined (TDA2EX_BUILD)
            if ((section.addr >= SOC_OCMC_RAM1_BASE) &&
                (section.addr < (SOC_OCMC_RAM1_BASE + SOC_OCMC_RAM1_SIZE)))
#endif
            {
                /* Internal OCMC RAM Space for all the cores */
            }
            /*copy section to memory*/
            /*check for section mapped into CPU internal memories*/
            else if (section.addr < 0x80000000U)
            {
                switch (CoreId)
                {
                    case MPU_CPU0_ID:
                        /*No action*/
                        break;
#ifdef TDA2XX_BUILD
                    case MPU_CPU1_ID:
                        /*No action*/
                        break;
                    case MPU_SMP_ID:
                        /* No action */
                        break;
#endif
                    case IPU1_CPU0_ID:
                    case IPU1_CPU1_ID:
                    case IPU1_CPU_SMP_ID:

                        if (((section.addr >= SOC_IPU1_BOOT_SPACE_BASE) &&
                             (section.addr <
                              (SOC_IPU1_BOOT_SPACE_BASE + 0x10000U))) ||
                            ((section.addr >= SOC_IPU1_RAM_BASE) &&
                             (section.addr < (SOC_IPU1_RAM_BASE + 0x10000))))
                        {
                            section.addr = section.addr & 0x000FFFFFU;
                            section.addr = MPU_IPU1_RAM + section.addr;
                        }
                        else
                        {
                            UARTPuts("IPU1 - Invalid Memory section", -1);
                        }

                        break;
#ifdef TDA2XX_BUILD
                    case IPU2_CPU0_ID:
                    case IPU2_CPU1_ID:
                    case IPU2_CPU_SMP_ID:
                        if (((section.addr >= SOC_IPU1_BOOT_SPACE_BASE) &&
                             (section.addr <
                              (SOC_IPU1_BOOT_SPACE_BASE + 0x10000U)))
                            ||
                            ((section.addr >= SOC_IPU1_RAM_BASE) &&
                             (section.addr < (SOC_IPU1_RAM_BASE + 0x10000))))
                        {
                            section.addr = section.addr & 0x000FFFFFU;
                            section.addr = MPU_IPU2_RAM + section.addr;
                        }
                        else
                        {
                            UARTPuts("IPU2  - Invalid Memory section", -1);
                        }

                        break;
#endif
                    case DSP1_ID:

                        if ((section.addr >= SOC_DSP_L2_BASE) &&
                            (section.addr < (SOC_DSP_L2_BASE + 0x48000)))
                        {
                            /* L2 RAM Read the offset */
                            section.addr = section.addr - SOC_DSP_L2_BASE;
                            section.addr = MPU_DSP1_L2_RAM + section.addr;
                        }
                        else if ((section.addr >= SOC_DSP_L1P_BASE) &&
                                 (section.addr < (SOC_DSP_L1P_BASE + 0x8000)))
                        {
                            /* MPU_DSP1_L1P_CACHE Read the offset */
                            section.addr = section.addr - SOC_DSP_L1P_BASE;
                            section.addr = MPU_DSP1_L1P_CACHE + section.addr;
                        }
                        else if ((section.addr >= SOC_DSP_L1D_BASE) &&
                                 (section.addr < (SOC_DSP_L1D_BASE + 0x8000)))
                        {
                            /* MPU_DSP1_L1D_CACHE */
                            section.addr = section.addr - SOC_DSP_L1D_BASE;
                            section.addr = MPU_DSP1_L1D_CACHE + section.addr;
                        }
                        else
                        {
                            UARTPuts("DSP1 - Invalid Memory section", -1);
                        }

                        break;
#ifdef TDA2XX_BUILD
                    case DSP2_ID:

                        if ((section.addr >= SOC_DSP_L2_BASE) &&
                            (section.addr < (SOC_DSP_L2_BASE + 0x48000)))
                        {
                            /* DSP2 L2 RAM Read the offset */
                            section.addr = section.addr - SOC_DSP_L2_BASE;
                            section.addr = MPU_DSP2_L2_RAM + section.addr;
                        }
                        else if ((section.addr >= SOC_DSP_L1P_BASE) &&
                                 (section.addr < (SOC_DSP_L1P_BASE + 0x8000)))
                        {
                            /* MPU_DSP2_L1P_CACHE Read the offset */
                            section.addr = section.addr - SOC_DSP_L1P_BASE;
                            section.addr = MPU_DSP2_L1P_CACHE + section.addr;
                        }
                        else if ((section.addr >= SOC_DSP_L1D_BASE) &&
                                 (section.addr < (SOC_DSP_L1D_BASE + 0x8000)))
                        {
                            /* MPU_DSP2_L1D_CACHE */
                            section.addr = section.addr - SOC_DSP_L1D_BASE;
                            section.addr = MPU_DSP2_L1D_CACHE + section.addr;
                        }
                        else
                        {
                            UARTPuts("DSP2 - Invalid Memory section", -1);
                        }

                        break;

                    case EVE1_ID:

                        /*DMEM*/
                        if ((section.addr >= SOC_EVE_DMEM_BASE) &&
                            (section.addr < (SOC_EVE_DMEM_BASE + 0x8000)))
                        {
                            section.addr = section.addr - SOC_EVE_DMEM_BASE;
                            section.addr = MPU_EVE1_DMEM_BASE + section.addr;
                        }
                        /*WMEM*/
                        else if ((section.addr >= SOC_EVE_WBUF_BASE) &&
                                 (section.addr < (SOC_EVE_WBUF_BASE + 0x8000)))
                        {
                            section.addr = section.addr - SOC_EVE_WBUF_BASE;
                            section.addr = MPU_EVE1_WBUF_BASE + section.addr;
                        }
                        /*IBUFLA*/
                        else if ((section.addr >= SOC_EVE_IBUF_LA_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_LA_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_LA_BASE;
                            section.addr = MPU_EVE1_IBUF_LA_BASE + section.addr;
                        }
                        /*IBUFLH*/
                        else if ((section.addr >= SOC_EVE_IBUF_HA_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_HA_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_HA_BASE;
                            section.addr = MPU_EVE1_IBUF_HA_BASE + section.addr;
                        }
                        /*IBUFLB*/
                        else if ((section.addr >= SOC_EVE_IBUF_LB_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_LB_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_LB_BASE;
                            section.addr = MPU_EVE1_IBUF_LB_BASE + section.addr;
                        }
                        /*IBUFHB*/
                        else if ((section.addr >= SOC_EVE_IBUF_HB_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_HB_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_HB_BASE;
                            section.addr = MPU_EVE1_IBUF_HB_BASE + section.addr;
                        }
                        else
                        {
                            UARTPuts("EVE1 - Invalid Memory section", -1);
                        }

                        break;

                    case EVE2_ID:
                        /* DMEM */
                        if ((section.addr >= SOC_EVE_DMEM_BASE) &&
                            (section.addr < (SOC_EVE_DMEM_BASE + 0x8000)))
                        {
                            section.addr = section.addr - SOC_EVE_DMEM_BASE;
                            section.addr = MPU_EVE2_DMEM_BASE + section.addr;
                        }
                        /* WMEM */
                        else if ((section.addr >= SOC_EVE_WBUF_BASE) &&
                                 (section.addr < (SOC_EVE_WBUF_BASE + 0x8000)))
                        {
                            section.addr = section.addr - SOC_EVE_WBUF_BASE;
                            section.addr = MPU_EVE2_WBUF_BASE + section.addr;
                        }
                        /* IBUFLA */
                        else if ((section.addr >= SOC_EVE_IBUF_LA_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_LA_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_LA_BASE;
                            section.addr = MPU_EVE2_IBUF_LA_BASE + section.addr;
                        }
                        /* IBUFH */
                        else if ((section.addr >= SOC_EVE_IBUF_HA_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_HA_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_HA_BASE;
                            section.addr = MPU_EVE2_IBUF_HA_BASE + section.addr;
                        }
                        /* IBUFLB */
                        else if ((section.addr >= SOC_EVE_IBUF_LB_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_LB_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_LB_BASE;
                            section.addr = MPU_EVE2_IBUF_LB_BASE + section.addr;
                        }
                        else if ((section.addr >= SOC_EVE_IBUF_HB_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_HB_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_HB_BASE;
                            section.addr = MPU_EVE2_IBUF_HB_BASE + section.addr;
                        }
                        else
                        {
                            UARTPuts("EVE2 - Invalid Memory section", -1);
                        }

                        break;

                    case EVE3_ID:
                        /* DMEM */
                        if ((section.addr >= SOC_EVE_DMEM_BASE) &&
                            (section.addr < (SOC_EVE_DMEM_BASE + 0x8000)))
                        {
                            section.addr = section.addr - SOC_EVE_DMEM_BASE;
                            section.addr = MPU_EVE3_DMEM_BASE + section.addr;
                        }
                        /* WMEM */
                        else if ((section.addr >= SOC_EVE_WBUF_BASE) &&
                                 (section.addr < (SOC_EVE_WBUF_BASE + 0x8000)))
                        {
                            section.addr = section.addr - SOC_EVE_WBUF_BASE;
                            section.addr = MPU_EVE3_WBUF_BASE + section.addr;
                        }
                        /* IBUFLA */
                        else if ((section.addr >= SOC_EVE_IBUF_LA_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_LA_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_LA_BASE;
                            section.addr = MPU_EVE3_IBUF_LA_BASE + section.addr;
                        }
                        /* IBUFH */
                        else if ((section.addr >= SOC_EVE_IBUF_HA_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_HA_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_HA_BASE;
                            section.addr = MPU_EVE3_IBUF_HA_BASE + section.addr;
                        }
                        /* IBUFLB */
                        else if ((section.addr >= SOC_EVE_IBUF_LB_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_LB_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_LB_BASE;
                            section.addr = MPU_EVE3_IBUF_LB_BASE + section.addr;
                        }
                        else if ((section.addr >= SOC_EVE_IBUF_HB_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_HB_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_HB_BASE;
                            section.addr = MPU_EVE3_IBUF_HB_BASE + section.addr;
                        }
                        else
                        {
                            UARTPuts("EVE3 - Invalid Memory section", -1);
                        }

                        break;

                    case EVE4_ID:
                        /* DMEM */
                        if ((section.addr >= SOC_EVE_DMEM_BASE) &&
                            (section.addr < (SOC_EVE_DMEM_BASE + 0x8000)))
                        {
                            section.addr = section.addr - SOC_EVE_DMEM_BASE;
                            section.addr = MPU_EVE4_DMEM_BASE + section.addr;
                        }
                        /* WMEM */
                        else if ((section.addr >= SOC_EVE_WBUF_BASE) &&
                                 (section.addr < (SOC_EVE_WBUF_BASE + 0x8000)))
                        {
                            section.addr = section.addr - SOC_EVE_WBUF_BASE;
                            section.addr = MPU_EVE4_WBUF_BASE + section.addr;
                        }
                        /* IBUFLA */
                        else if ((section.addr >= SOC_EVE_IBUF_LA_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_LA_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_LA_BASE;
                            section.addr = MPU_EVE4_IBUF_LA_BASE + section.addr;
                        }
                        /* IBUFH */
                        else if ((section.addr >= SOC_EVE_IBUF_HA_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_HA_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_HA_BASE;
                            section.addr = MPU_EVE4_IBUF_HA_BASE + section.addr;
                        }
                        /* IBUFLB */
                        else if ((section.addr >= SOC_EVE_IBUF_LB_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_LB_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_LB_BASE;
                            section.addr = MPU_EVE4_IBUF_LB_BASE + section.addr;
                        }
                        else if ((section.addr >= SOC_EVE_IBUF_HB_BASE) &&
                                 (section.addr < (SOC_EVE_IBUF_HB_BASE + 0x4000)))
                        {
                            section.addr = section.addr - SOC_EVE_IBUF_HB_BASE;
                            section.addr = MPU_EVE4_IBUF_HB_BASE + section.addr;
                        }
                        else
                        {
                            UARTPuts("EVE4 - Invalid Memory section", -1);
                        }
                        break;
#endif
                    default:
                        break;
                }
            }
            else
            {
                /* To remove MISRA C error */
            }
            fp_readData((void *) section.addr, currRprcImageAddr, section.size);
            currRprcImageAddr += section.size;
        }
    }
    return retVal;
}

/**
 * \brief           BootCore function stores the CPU entry location into global
 *                  pointer
 *
 * \param[in]    entry - CPU Entry location
 * \param[in] entryPoint - CPU ID
 *
 * \return   none
 */

void BootCore(uint32_t entry, uint32_t CoreID)
{
    switch (CoreID)
    {
        case MPU_CPU0_ID:
            /* MPU CPU0*/
            SBL_PRINTF(TRACE_HIGH, "\n MPU CPU0 image load completed \n");
            entryPoint_MPU_CPU0 = entry;
            break;
#ifdef TDA2XX_BUILD

        case MPU_CPU1_ID:
            /* MPU CPU1 */
            SBL_PRINTF(TRACE_HIGH, "\n MPU CPU1 image load completed \n");
            entryPoint_MPU_CPU1 = entry;
            break;

        case MPU_SMP_ID:
            /* MPU SMP ID */
            SBL_PRINTF(TRACE_HIGH,
                       "\n MPU CPU0 and CPU1 SMP image load completed \n");
            entryPoint_MPU_CPU0 = entry;
            entryPoint_MPU_CPU1 = entry;
            break;
#endif
        case IPU1_CPU0_ID:
            /*IPU1 CPU0*/
            SBL_PRINTF(TRACE_HIGH, "\n IPU1 CPU0 image load completed \n");
            entryPoint_IPU1_CPU0 = entry;
            break;

        case IPU1_CPU1_ID:
            /*IPU1 CPU1*/
            SBL_PRINTF(TRACE_HIGH, "\n IPU1 CPU1 image load completed \n");
            entryPoint_IPU1_CPU1 = entry;
            break;

        case IPU1_CPU_SMP_ID:
            /*IPU1 CPU0 & CPU1*/
            SBL_PRINTF(TRACE_HIGH,
                       "\n IPU1 CPU0 & CPU1 image load completed \n");
            entryPoint_IPU1_CPU0 = entry;
            entryPoint_IPU1_CPU1 = entry;
            break;

#ifdef TDA2XX_BUILD
        case IPU2_CPU0_ID:
            /*IPU2 CPU0*/
            SBL_PRINTF(TRACE_HIGH, "\n IPU2 CPU0 image load completed \n");
            entryPoint_IPU2_CPU0 = entry;
            break;

        case IPU2_CPU1_ID:
            /*IPU2 CPU1*/
            SBL_PRINTF(TRACE_HIGH, "\n IPU2 CPU1 image load completed \n");
            entryPoint_IPU2_CPU1 = entry;
            break;

        case IPU2_CPU_SMP_ID:
            /*IPU2 CPU0 & CPU1*/
            SBL_PRINTF(TRACE_HIGH,
                       "\n IPU2 CPU0 & CPU1  image load completed \n");
            entryPoint_IPU2_CPU0 = entry;
            entryPoint_IPU2_CPU1 = entry;
            break;
#endif
        case DSP1_ID:
            /* DSP1*/
            SBL_PRINTF(TRACE_HIGH, "\n DSP1 image load completed \n");
            entryPoint_DSP1 = entry;
            break;

#ifdef TDA2XX_BUILD
        case DSP2_ID:
            /* DSP2*/
            SBL_PRINTF(TRACE_HIGH, "\n DSP2 image load completed \n");
            entryPoint_DSP2 = entry;
            break;

        case EVE1_ID:
            /* EVE1*/
            SBL_PRINTF(TRACE_HIGH, "\n EVE1 image load completed \n");
            entryPoint_EVE1 = entry;
            break;

        case EVE2_ID:
            /* EVE2*/
            SBL_PRINTF(TRACE_HIGH, "\n EVE2 image load completed \n");
            entryPoint_EVE2 = entry;
            break;

        case EVE3_ID:
            /* EVE3*/
            SBL_PRINTF(TRACE_HIGH, "\n EVE3 image load completed \n");
            entryPoint_EVE3 = entry;
            break;

        case EVE4_ID:
            /* EVE4*/
            SBL_PRINTF(TRACE_HIGH, "\n EVE4 image load completed \n");
            entryPoint_EVE4 = entry;
            break;
#endif
        default:
            /* Wrong CPU ID */
            SBL_PRINTF(TRACE_HIGH, "\n Tried to boot Unknown Core \n");
            break;
    }
}

