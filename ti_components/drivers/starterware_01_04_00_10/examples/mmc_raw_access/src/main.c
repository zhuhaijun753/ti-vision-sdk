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
 *   Component:      examples
 *
 *   Filename:       main.c
 *
 *   Description:    Test application for MMC Sector raw read and write
 *
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "uartStdio.h"
#include "soc_defines.h"
#include "soc.h"

#include <common/stw_types.h>
#include <common/stw_config.h>
#include <common/stw_utils.h>

#include "platform.h"
#include "hw_types.h"
#include "hw_l3init_cm_core.h"
#include "hw_ctrl_core_pad.h"
#include "hw_mmc.h"
#include "hs_mmcsd.h"

#ifdef TDA2XX_FAMILY_BUILD
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"
#endif
#include "i2clib/lld_hsi2c.h"
#include <devices/stw_device.h>
#include "boards/stw_board.h"
#include "stwutils_app.h"

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define BUFFER_SIZE    (512)
#define BIT(x) (1 << x)

/* SD Commands enumeration */
#define SD_CMD(x)   (x)

/* Command/Response flags for notifying some information to controller */
#define SD_CMDRSP_NONE      BIT(0)
#define SD_CMDRSP_STOP      BIT(1)
#define SD_CMDRSP_FS        BIT(2)
#define SD_CMDRSP_ABORT     BIT(3)
#define SD_CMDRSP_BUSY      BIT(4)
#define SD_CMDRSP_136BITS   BIT(5)
#define SD_CMDRSP_DATA      BIT(6)
#define SD_CMDRSP_READ      BIT(7)
#define SD_CMDRSP_WRITE     BIT(8)

/* Check RCA/status */
#define SD_RCA_ADDR(rca)             ((rca & 0xFFFF0000) >> 16)
#define SD_RCA_STAT(rca)             (rca & 0x0xFFFF)

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
typedef struct _mmcsdCmd {
    unsigned int idx;
    unsigned int flags;
    unsigned int arg;
    signed char *data;
    unsigned int nblks;
    unsigned int rsp[4];
}mmcsdCmd;

uint32_t          baseAddress       = SOC_MMC2_BASE;
uint32_t          hsmmcsd_dataLen   = 0;
uint32_t          hsmmcsd_blockSize = 0;
volatile uint8_t *hsmmcsd_buffer    = 0;
uint32_t          hsmmcsd_cid[4], hsmmcsd_rca, hsmmcsd_csd[4];
/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
/* MMC module enable functions */
static int32_t mmc2init(void);
void MMCSD_LDO_PWR(void);
void delay(uint32_t delay);

/* MMCSD Host Controller Functions */
static int32_t mmcHostCtrlInit(void);
unsigned int HSMMCSDCmdSend(mmcsdCmd *c);
static int32_t HSMMCSDCmdStatusGet(void);
static void HSMMCSDXferSetup(unsigned char rwFlag,
                             void         *ptr,
                             unsigned int  nBlks);
static unsigned int HSMMCSDXferStatusGet();

/* MMC Card Protocol Functions */
int32_t MMCSDCardReset(void);
int32_t MMCSDCardInit(void);
int32_t mmcBlockReadWrite(void);

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
int main(void)
{
    int32_t            retVal = STW_SOK;
    volatile uint32_t  done   = 1;
    stwAppInitParams_t stwAppInitParams;

    stwAppInitParams.isI2cInitReq  = TRUE;
    stwAppInitParams.isUartInitReq = TRUE;
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        console_print_string("\nSystem Init Failed ");
    }

    /* Clock and pinmux settings */
    retVal = mmc2init();

    /* IO Expander mux config for MMC2*/
    BOARDSelectDevice(DEVICE_ID_MMC, DEVICE_MMC_INST_ID_2);

    retVal += mmcHostCtrlInit();
    if (retVal == STW_SOK)
    {
        UARTPuts("\nmmc Host Ctrl init Done.", -1);

        retVal = MMCSDCardInit();
    }
    if (retVal == STW_SOK)
    {
        retVal = mmcBlockReadWrite();
    }
    if (retVal == STW_SOK)
    {
        UARTprintf("\nData Read Write from eMMC Successful");
    }
    else
    {
        UARTprintf("\nData Read Write from eMMC Failed");
    }
    while (done) ;

    return 0;
}

int32_t mmcBlockReadWrite(void)
{
    int32_t  status = STW_SOK;
    mmcsdCmd cmd;
    uint8_t  flashReadData[BUFFER_SIZE];
    uint8_t  flashWriteData[BUFFER_SIZE];
    uint32_t i, n;
    /* TODO: Get the number of blocks from csd */
    uint32_t numBlocks = 50;
    uint32_t address;

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        flashReadData[i]  = 0;
        flashWriteData[i] = i;
    }

    for (i = 0; i < numBlocks; i++)
    {
        address = hsmmcsd_blockSize * i;
        HSMMCSDXferSetup(0, &flashWriteData[0], 1);
        cmd.flags = SD_CMDRSP_WRITE | SD_CMDRSP_DATA;
        cmd.arg   = address;
        cmd.nblks = 1;
        cmd.idx   = SD_CMD(24);
        status    = HSMMCSDCmdSend(&cmd);
        if (status != STW_SOK)
        {
            return STW_EFAIL;
        }
        HSMMCSDXferStatusGet();

        cmd.idx   = SD_CMD(23);
        cmd.flags = 0;
        cmd.arg   = i;
        status    = HSMMCSDCmdSend(&cmd);
        if (status != STW_SOK)
        {
            return STW_EFAIL;
        }

        /* read from sector*/
        HSMMCSDXferSetup(1, &flashReadData[0], 1);
        cmd.idx   = SD_CMD(17);
        cmd.flags = SD_CMDRSP_READ | SD_CMDRSP_DATA;
        cmd.arg   = address;
        cmd.nblks = 1;
        status    = HSMMCSDCmdSend(&cmd);
        HSMMCSDXferStatusGet();

        for (n = 0; n < hsmmcsd_blockSize; n++)
        {
            if (flashReadData[n] != flashWriteData[n])
            {
                status = STW_EFAIL;
                UARTprintf("\nData Mismatch error for block no %u address %u",
                           i,
                           n);
                break;
            }
        }
        if (status != STW_SOK)
        {
            break;
        }
        /* Reset the read data buffer */
        for (n = 0; n < hsmmcsd_blockSize; n++)
        {
            flashReadData[n] = 0;
        }
    }
    return status;
}

/* MMC module enable functions */
int32_t mmc2init(void)
{
    uint32_t tmpRegVal;
    /*MMC2- CM_L3INIT_MMC2_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC2_CLKCTRL);
    tmpRegVal |= 0x03000000;
    HW_WR_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC2_CLKCTRL, tmpRegVal);

    /*Enable the module - mmc2  */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_MMC2, PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
    MMCSD_LDO_PWR();

    /*MMC1 PAD Configuration*/
    PlatformMMCSD2SetPinMux();

    return STW_SOK;
}

void delay(uint32_t delay)
{
    volatile uint32_t i;
    for (i = 0; i < (1000 * delay); ++i) ;
}

void   MMCSD_LDO_PWR()
{
    /*CTRL_CORE_CONTROL_PBIAS*/

    uint32_t reg_val = 0;

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);

    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    delay(10); /* wait 10 us */
    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    /*Enable SDCARD_BIAS_VMODE*/
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK; /* 3v */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    delay(150); /* wait 10 us */

    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    delay(150); /* wait 10 us */
}

/* MMCSD Host Controller Functions */
static int32_t mmcHostCtrlInit(void)
{
    int32_t  status = STW_SOK;
    uint32_t intrMask;
    /*Refer to the MMC Host and Bus configuration steps in TRM */
    /* controller Reset */
    status = HSMMCSDSoftReset(baseAddress);
    if (status != STW_SOK)
    {
        UARTPuts("\nHS MMC/SD Reset failed\n\r", -1);
    }

    /* Lines Reset */
    status += HSMMCSDLinesReset(baseAddress, MMC_SYSCTL_SRA_MASK);
    /* Set supported voltage list */
    HSMMCSDSupportedVoltSet(baseAddress, MMC_CAPA_VS18_MASK |
                            MMC_CAPA_VS30_MASK);
    HSMMCSDSystemConfig(baseAddress, MMC_SYSCONFIG_AUTOIDLE_MASK);
    /* Set the bus width to 1 bit*/
    HSMMCSDBusWidthSet(baseAddress, 0x1);

    /* Set the bus voltage */
    HSMMCSDBusVoltSet(baseAddress, (MMC_HCTL_SDVS_3V0 << MMC_HCTL_SDVS_SHIFT));
    /* Bus power on */
    status +=
        HSMMCSDBusPower(baseAddress,
                        (MMC_HCTL_SDBP_PWRON << MMC_HCTL_SDBP_SHIFT));
    /* Set the initialization frequency */
    status += HSMMCSDBusFreqSet(baseAddress, MMCSD_IN_FREQ, MMCSD_INIT_FREQ, 0);

    status += HSMMCSDInitStreamSend(baseAddress);

    /* Enable interrupts */
    intrMask = (HS_MMCSD_INTR_CMDCOMP | HS_MMCSD_INTR_CMDTIMEOUT |
                HS_MMCSD_INTR_DATATIMEOUT | HS_MMCSD_INTR_TRNFCOMP);
    HSMMCSDIntrEnable(baseAddress, intrMask);

    if (status != STW_SOK)
    {
        UARTPuts("\nMMC Host Controller init failed\n\r", -1);
    }

    return status;
}

unsigned int HSMMCSDCmdSend(mmcsdCmd *c)
{
    unsigned int cmdType = HS_MMCSD_CMD_TYPE_NORMAL;
    unsigned int dataPresent;
    unsigned int status = STW_SOK;
    unsigned int rspType;
    unsigned int cmdDir;
    unsigned int nblks;
    unsigned int cmd;

    if (c->flags & SD_CMDRSP_STOP)
    {
        cmdType = HS_MMCSD_CMD_TYPE_SUSPEND;
    }
    else if (c->flags & SD_CMDRSP_FS)
    {
        cmdType = HS_MMCSD_CMD_TYPE_FUNCSEL;
    }
    else if (c->flags & SD_CMDRSP_ABORT)
    {
        cmdType = HS_MMCSD_CMD_TYPE_ABORT;
    }

    cmdDir = (c->flags & SD_CMDRSP_READ) ? \
             HS_MMCSD_CMD_DIR_READ : HS_MMCSD_CMD_DIR_WRITE;

    dataPresent = (c->flags & SD_CMDRSP_DATA) ? 1 : 0;
    nblks       = (dataPresent == 1) ? c->nblks : 0;

    if (c->flags & SD_CMDRSP_NONE)
    {
        rspType = HS_MMCSD_NO_RESPONSE;
    }
    else if (c->flags & SD_CMDRSP_136BITS)
    {
        rspType = HS_MMCSD_136BITS_RESPONSE;
    }
    else if (c->flags & SD_CMDRSP_BUSY)
    {
        rspType = HS_MMCSD_48BITS_BUSY_RESPONSE;
    }
    else
    {
        rspType = HS_MMCSD_48BITS_RESPONSE;
    }

    cmd = HS_MMCSD_CMD(c->idx, cmdType, rspType, cmdDir);

    if (dataPresent)
    {
        HSMMCSDIntrStatusClear(baseAddress, HS_MMCSD_STAT_TRNFCOMP);

        HSMMCSDDataTimeoutSet(baseAddress, HS_MMCSD_DATA_TIMEOUT(27));
    }

    HSMMCSDCommandSend(baseAddress, cmd, c->arg, (void *) dataPresent,
                       nblks, FALSE);

    HSMMCSDCmdStatusGet();
    if (status == STW_SOK)
    {
        HSMMCSDResponseGet(baseAddress, (uint32_t *) c->rsp);
    }

    return status;
}

static int32_t HSMMCSDCmdStatusGet(void)
{
    int32_t status = STW_SOK;

    while (1)
    {
        status = HSMMCSDIntrStatusGet(baseAddress, 0xFFFFFFFF);
        if (status & HS_MMCSD_STAT_CMDCOMP)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                   HS_MMCSD_STAT_CMDCOMP);
            break;
        }
        if (status & HS_MMCSD_STAT_ERR)
        {
            if (status & HS_MMCSD_STAT_CMDTIMEOUT)
            {
                HSMMCSDIntrStatusClear(baseAddress,
                                       HS_MMCSD_STAT_CMDTIMEOUT);
                status = STW_ETIMEOUT;
            }
            status = STW_EFAIL;
            break;
        }
    }
    return status;
}

static void HSMMCSDXferSetup(unsigned char rwFlag,
                             void         *ptr,
                             unsigned int  nBlks)
{
    HSMMCSDIntrStatusClear(baseAddress, HS_MMCSD_INTR_TRNFCOMP);

    if (rwFlag == 1)
    {
        HSMMCSDIntrStatusClear(baseAddress, HS_MMCSD_INTR_BUFRDRDY);
        HSMMCSDIntrStatusEnable(baseAddress, HS_MMCSD_INTR_BUFRDRDY);
        HSMMCSDIntrStatusDisable(baseAddress, HS_MMCSD_INTR_BUFWRRDY);
    }
    else
    {
        HSMMCSDIntrStatusClear(baseAddress, HS_MMCSD_INTR_BUFWRRDY);
        HSMMCSDIntrStatusEnable(baseAddress, HS_MMCSD_INTR_BUFWRRDY);
        HSMMCSDIntrStatusDisable(baseAddress, HS_MMCSD_INTR_BUFRDRDY);
    }

    HSMMCSDBlkLenSet(baseAddress, hsmmcsd_blockSize);
    hsmmcsd_dataLen = (nBlks * hsmmcsd_blockSize);
    hsmmcsd_buffer  = (volatile unsigned char *) ptr;
}

static unsigned int HSMMCSDXferStatusGet()
{
    volatile uint32_t status  = 0;
    int32_t           retVal  = 0;
    volatile uint32_t i       = 0, i_max = 0;
    volatile uint8_t *dst_bfr = hsmmcsd_buffer;
    volatile uint32_t temp;

    while (1)
    {
        status = HSMMCSDIntrStatusGet(baseAddress, 0xFFFFFFFF);

        if (status & HS_MMCSD_STAT_BUFRDRDY)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                   HS_MMCSD_STAT_BUFRDRDY);

            if (dst_bfr != NULL)
            {
                if (hsmmcsd_dataLen < hsmmcsd_blockSize)
                {
                    i_max = hsmmcsd_dataLen;
                }
                else
                {
                    i_max = hsmmcsd_blockSize;
                }
                /*Input data bfr will not be 4-byte aligned*/
                for (i = 0; i < i_max; i += 4)
                {
                    temp           = HW_RD_REG32(baseAddress + MMC_DATA);
                    dst_bfr[i]     = *((char *) &temp);
                    dst_bfr[i + 1] = *((char *) &temp + 1);
                    dst_bfr[i + 2] = *((char *) &temp + 2);
                    dst_bfr[i + 3] = *((char *) &temp + 3);
                }
                dst_bfr += i_max;
            }
        }
        if (status & HS_MMCSD_STAT_BUFWRRDY)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                   HS_MMCSD_STAT_BUFRDRDY);

            if (hsmmcsd_buffer != NULL)
            {
                for (i = 0; i < hsmmcsd_dataLen; i += 4)
                {
                    *((char *) &temp)     = hsmmcsd_buffer[i];
                    *((char *) &temp + 1) = hsmmcsd_buffer[i + 1];
                    *((char *) &temp + 2) = hsmmcsd_buffer[i + 2];
                    *((char *) &temp + 3) = hsmmcsd_buffer[i + 3];
                    HW_WR_REG32(baseAddress + MMC_DATA, temp);
                }
            }
        }
        if (status & HS_MMCSD_STAT_DATATIMEOUT)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                   HS_MMCSD_STAT_DATATIMEOUT);
            retVal = STW_ETIMEOUT;
            break;
        }
        if (status & HS_MMCSD_STAT_TRNFCOMP)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                   HS_MMCSD_STAT_TRNFCOMP);
            retVal = STW_SOK;
            break;
        }
    }
    return retVal;
}

/* MMC Card Protocol Functions */
int32_t MMCSDCardReset(void)
{
    int32_t  status = STW_SOK;
    mmcsdCmd cmd;

    cmd.idx   = SD_CMD(0);
    cmd.flags = SD_CMDRSP_NONE;
    cmd.arg   = 0;

    status = HSMMCSDCmdSend(&cmd);

    return status;
}

int32_t MMCSDCardInit(void)
{
    unsigned int status = 0;
    mmcsdCmd     cmd;

    /* CMD0 - reset card */
    status = MMCSDCardReset();

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }
    /* TODO: Detect mmc or sd card and do the init */

    do {
        /* CMD1 - send oper voltage */
        cmd.idx   = SD_CMD(1);
        cmd.flags = 0;
        cmd.arg   = 0xFF8000 | (0x2 << 29);

        status = HSMMCSDCmdSend(&cmd);
    } while (!(*cmd.rsp & (0x1 << 31)));
    /* Send CMD2, to get the card identification register */
    cmd.idx   = SD_CMD(2);
    cmd.flags = SD_CMDRSP_136BITS;
    cmd.arg   = 0;

    status = HSMMCSDCmdSend(&cmd);

    memcpy(&hsmmcsd_cid, cmd.rsp, 16);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }

    /* Send CMD3, to get the card relative address */
    cmd.idx   = SD_CMD(3);
    cmd.flags = 0;
    cmd.arg   = 0;

    status = HSMMCSDCmdSend(&cmd);

    hsmmcsd_rca = SD_RCA_ADDR(cmd.rsp[0]);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }
    /* Send CMD9, to get the card specific data */
    cmd.idx   = SD_CMD(9);
    cmd.flags = SD_CMDRSP_136BITS;
    cmd.arg   = hsmmcsd_rca << 16;

    status = HSMMCSDCmdSend(&cmd);

    memcpy(&hsmmcsd_csd, cmd.rsp, 16);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }

    // SD_CMD(13) to check card state
    HSMMCSDBlkLenSet(baseAddress, 512);
    cmd.idx   = SD_CMD(16);
    cmd.flags = SD_CMDRSP_NONE;
    cmd.arg   = 512;
    status    = HSMMCSDCmdSend(&cmd);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }
    else
    {
        /* TODO: Get the block size from csd */
        hsmmcsd_blockSize = 512;
    }

    /* Select the card */
    cmd.idx   = SD_CMD(7);
    cmd.flags = SD_CMDRSP_BUSY;
    cmd.arg   = hsmmcsd_rca << 16;

    status = HSMMCSDCmdSend(&cmd);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }

    return STW_SOK;
}

/***************************** End Of File ***********************************/

