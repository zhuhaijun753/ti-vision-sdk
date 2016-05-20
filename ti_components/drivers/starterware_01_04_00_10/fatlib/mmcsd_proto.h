/* =================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and
 *   conditionsstipulated in the agreement under which this program
 *   has been supplied.
 * =================================================================*/
/*
 * \file  mmc_sd.h
 *
 * \brief MMC/SD definitions
 *
 */

#ifndef MMCSD_PROTO_H_
#define MMCSD_PROTO_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#define BIT(x) (1 << x)

/**
 * SD Card information structure
 */
#define MMCSD_CARD_SD     0
#ifndef TDA3XX_FAMILY_BUILD
#define MMCSD_CARD_MMC    1
#endif

struct _mmcsdCtrlInfo;

typedef struct _mmcsdAddrConv {
    uint32_t virtualAddr;
    uint32_t phyAddr;
    uint32_t addrSize;
    int          virtualAddrOffset;
    int          phyAddrOffset;
}mmcsdAddrConv;

typedef struct _mmcsdCardInfo {
    struct _mmcsdCtrlInfo *ctrl;
    uint32_t           cardType;
    uint32_t           rca;
    uint32_t           raw_scr[2];
    uint32_t           raw_csd[4];
    uint32_t           raw_cid[4];
    uint32_t           ocr;
    unsigned char          sd_ver;
    unsigned char          busWidth;
    unsigned char          tranSpeed;
    unsigned char          highCap;
    uint32_t           blkLen;
    uint32_t           nBlks;
    uint32_t           size;
    uint32_t           numConv;
    struct _mmcsdAddrConv *addrConv;
}mmcsdCardInfo;

typedef struct _mmcsdCmd {
    uint32_t idx;
    uint32_t flags;
    uint32_t arg;
    signed char *data;
    uint32_t nblks;
    uint32_t rsp[4];
}mmcsdCmd;

typedef uint32_t (*_mmcsdctrlInit)(struct _mmcsdCtrlInfo *ctrl);
typedef uint32_t (*_mmcsdcmdSend)(struct _mmcsdCtrlInfo *ctrl, mmcsdCmd *c);
typedef void         (*_mmcsdbusWidthConfig)(struct _mmcsdCtrlInfo *ctrl,
                                             uint32_t           busWidth);
typedef int (*_mmcsdbusFreqConfig)(struct _mmcsdCtrlInfo *ctrl,
                                   uint32_t           busFreq);
typedef uint32_t (*_mmcsdcmdStatusGet)(struct _mmcsdCtrlInfo *ctrl);
typedef uint32_t (*_mmcsdxferStatusGet)(struct _mmcsdCtrlInfo *ctrl);
typedef void         (*_mmcsdxferSetup)(struct _mmcsdCtrlInfo *ctrl,
                                        unsigned char rwFlag,
                                        void *ptr, uint32_t blkSize,
                                        uint32_t nBlks);
typedef uint32_t (*_mmcsdcardPresent)(struct _mmcsdCtrlInfo *ctrl);
typedef void         (*_mmcsdintrEnable)(struct _mmcsdCtrlInfo *ctrl);

typedef struct _mmcsdCtrlInfo {
    uint32_t         memBase;
    uint32_t         ipClk;
    uint32_t         opClk;
    _mmcsdctrlInit       ctrlInit;
    _mmcsdcmdSend        cmdSend;
    _mmcsdbusWidthConfig busWidthConfig;
    _mmcsdbusFreqConfig  busFreqConfig;
    _mmcsdcmdStatusGet   cmdStatusGet;
    _mmcsdxferStatusGet  xferStatusGet;
    _mmcsdxferSetup      xferSetup;
    _mmcsdcardPresent    cardPresent;
    _mmcsdintrEnable     intrEnable;
    uint32_t         intrMask;
    uint32_t         dmaEnable;
    uint32_t         edmaTxDreq; /*Event source no*/
    uint32_t         edmaRxDreq;
    uint32_t         edmaChan;   /*edma channel no*/
    uint32_t         busWidth;
    uint32_t         highspeed;
    uint32_t         blocksize;
    uint32_t         ocr;
    uint32_t         cdPinNum;
    uint32_t         wpPinNum;
    mmcsdCardInfo       *card;
}mmcsdCtrlInfo;

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

/* SD voltage enumeration as per VHS field of the interface command */
#define SD_VOLT_2P7_3P6    (0x000100)

/* SD OCR register definitions */
/* High capacity */
#define SD_OCR_HIGH_CAPACITY  BIT(30)
/* Voltage */
#define SD_OCR_VDD_2P7_2P8    BIT(15)
#define SD_OCR_VDD_2P8_2P9    BIT(16)
#define SD_OCR_VDD_2P9_3P0    BIT(17)
#define SD_OCR_VDD_3P0_3P1    BIT(18)
#define SD_OCR_VDD_3P1_3P2    BIT(19)
#define SD_OCR_VDD_3P2_3P3    BIT(20)
#define SD_OCR_VDD_3P3_3P4    BIT(21)
#define SD_OCR_VDD_3P4_3P5    BIT(22)
#define SD_OCR_VDD_3P5_3P6    BIT(23)
/* This is for convenience only. Sets all the VDD fields */
#define SD_OCR_VDD_WILDCARD   (0x1FF << 15)

/* SD CSD register definitions */
#define SD_TRANSPEED_25MBPS   0x32
#define SD_TRANSPEED_50MBPS   0x5A

#define SD_CARD_CSD_VERSION(crd) (((crd)->raw_csd[3] & 0xC0000000) >> 30)

#define SD_CSD0_DEV_SIZE(csd3, csd2, csd1,       \
                         csd0) (((csd2 &         \
                                  0x000003FF) << \
                                 2) | ((csd1 & 0xC0000000) >> 30))
#define SD_CSD0_MULT(csd3, csd2, csd1, csd0) ((csd1 & 0x00038000) >> 15)
#define SD_CSD0_RDBLKLEN(csd3, csd2, csd1, csd0) ((csd2 & 0x000F0000) >> 16)
#define SD_CSD0_TRANSPEED(csd3, csd2, csd1, csd0) ((csd3 & 0x000000FF) >> 0)

#define SD_CARD0_DEV_SIZE(crd) SD_CSD0_DEV_SIZE((crd)->raw_csd[3], \
                                                (crd)->raw_csd[2], \
                                                (crd)->raw_csd[1], \
                                                (crd)->raw_csd[0])
#define SD_CARD0_MULT(crd) SD_CSD0_MULT((crd)->raw_csd[3], (crd)->raw_csd[2], \
                                        (crd)->raw_csd[1], (crd)->raw_csd[0])
#define SD_CARD0_RDBLKLEN(crd) SD_CSD0_RDBLKLEN((crd)->raw_csd[3], \
                                                (crd)->raw_csd[2], \
                                                (crd)->raw_csd[1], \
                                                (crd)->raw_csd[0])
#define SD_CARD0_TRANSPEED(crd) SD_CSD0_TRANSPEED((crd)->raw_csd[3], \
                                                  (crd)->raw_csd[2], \
                                                  (crd)->raw_csd[1], \
                                                  (crd)->raw_csd[0])
#define SD_CARD0_NUMBLK(crd) ((SD_CARD0_DEV_SIZE((crd)) + \
                               1) * (1 << (SD_CARD0_MULT((crd)) + 2)))
#define SD_CARD0_SIZE(crd) ((SD_CARD0_NUMBLK((crd))) * \
                            (1 << (SD_CARD0_RDBLKLEN(crd))))

#define SD_CSD1_DEV_SIZE(csd3, csd2, csd1,       \
                         csd0) (((csd2 &         \
                                  0x0000003F) << \
                                 16) | ((csd1 & 0xFFFF0000) >> 16))
#define SD_CSD1_RDBLKLEN(csd3, csd2, csd1, csd0) ((csd2 & 0x000F0000) >> 16)
#define SD_CSD1_TRANSPEED(csd3, csd2, csd1, csd0) ((csd3 & 0x000000FF) >> 0)

#define SD_CARD1_DEV_SIZE(crd) SD_CSD1_DEV_SIZE((crd)->raw_csd[3], \
                                                (crd)->raw_csd[2], \
                                                (crd)->raw_csd[1], \
                                                (crd)->raw_csd[0])
#define SD_CARD1_RDBLKLEN(crd) SD_CSD1_RDBLKLEN((crd)->raw_csd[3], \
                                                (crd)->raw_csd[2], \
                                                (crd)->raw_csd[1], \
                                                (crd)->raw_csd[0])
#define SD_CARD1_TRANSPEED(crd) SD_CSD1_TRANSPEED((crd)->raw_csd[3], \
                                                  (crd)->raw_csd[2], \
                                                  (crd)->raw_csd[1], \
                                                  (crd)->raw_csd[0])
#define SD_CARD1_SIZE(crd) ((SD_CARD1_DEV_SIZE((crd)) + 1) * (512 * 1024))

/* Check RCA/status */
#define SD_RCA_ADDR(rca)             ((rca & 0xFFFF0000) >> 16)
#define SD_RCA_STAT(rca)             (rca & 0x0xFFFF)

/* Check pattern that can be used for card response validation */
#define SD_CHECK_PATTERN   0xAA

/* SD SCR related macros */
#define SD_VERSION_1P0    0
#define SD_VERSION_1P1    1
#define SD_VERSION_2P0    2
#define SD_BUS_WIDTH_1BIT 1
#define SD_BUS_WIDTH_4BIT 4

/* Helper macros */
/* Note card registers are big endian */
#define SD_CARD_VERSION(sdcard)   ((sdcard)->raw_scr[0] & 0xF)
#define SD_CARD_BUSWIDTH(sdcard)  ((unsigned char) ((sdcard)->raw_scr[0] & \
                                                    0xF00) >> 8)

/*
 * Function prototypes
 */

extern uint32_t MMCSDReadCmdSend(mmcsdCtrlInfo *ctrl, void *ptr,
                                     uint32_t block,
                                     uint32_t blks);
extern uint32_t MMCSDWriteCmdSend(mmcsdCtrlInfo *ctrl, void *ptr,
                                      uint32_t block,
                                      uint32_t blks);
extern uint32_t MMCSDAppCmdSend(mmcsdCtrlInfo *ctrl, mmcsdCmd *c);
extern uint32_t MMCSDCmdSend(mmcsdCtrlInfo *ctrl, mmcsdCmd *c);
extern uint32_t MMCSDTranSpeedSet(mmcsdCtrlInfo *ctrl);
extern uint32_t MMCSDBlockSizeSet(mmcsdCtrlInfo *ctrl);
extern uint32_t MMCSDBusWidthSet(mmcsdCtrlInfo *ctrl);
extern uint32_t MMCSDStopCmdSend(mmcsdCtrlInfo *ctrl);
extern uint32_t MMCSDCardPresent(mmcsdCtrlInfo *ctrl);
extern uint32_t MMCSDCardReset(mmcsdCtrlInfo *ctrl);
extern uint32_t MMCSDCardInit(mmcsdCtrlInfo *ctrl);
extern uint32_t MMCSDCtrlInit(mmcsdCtrlInfo *ctrl);
extern void MMCSDIntEnable(mmcsdCtrlInfo *ctrl);
extern void MMCSDMemCopy (mmcsdCtrlInfo *ctrl, void* dst, const void* src, uint32_t cnt);
#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
