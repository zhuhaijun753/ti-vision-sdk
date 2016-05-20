/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/**
 *  \file vpshal_vpdma.h
 *
 *  \brief HAL Header file for VPDMA
 *  This file exposes the HAL APIs for VPS VPDMA module
 *
 */

#ifndef VPSHAL_VPDMA_H_
#define VPSHAL_VPDMA_H_

/* TODO: Interrupt related API pending */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <hal/vpshal.h>
#ifdef TDA3XX_FAMILY_BUILD
#include <hal/vpshalVpdmaTda3xx.h>
#endif
#ifdef TDA2XX_FAMILY_BUILD
#include <hal/vpshalVpdmaTda2xx.h>
#endif
#ifdef TI814X_FAMILY_BUILD
#include <hal/vpshalVpdmaTI814x.h>
#endif
#include <fvid2/fvid2_dataTypes.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* VPDMA Macros */
#define VPSHAL_VPDMA_MAX_LIST                  (8U)
#define VPSHAL_VPDMA_MAX_CLIENTS               (63U)
#define VPSHAL_VPDMA_MAX_SI_SOURCE             (16U)
#define VPSHAL_VPDMA_MAX_LM_FID                (3U)

/**
 *  enum VpsHal_VpdmaInst
 *  \brief Enum for selecting different modules within VPDMA
 *  Used in enabling/disabling/reset/unreset APIs
 */
typedef enum
{
    VPSHAL_VIP1_VPDMA,
    /**< VPDMA instance in VIP 1. */
    VPSHAL_VIP2_VPDMA,
    /**< VPDMA instance in VIP 2. */
    VPSHAL_VIP3_VPDMA,
    /**< VPDMA instance in VIP 3. */
    VPSHAL_VPE1_VPDMA,
    /**< VPDMA instance in VPE */

    /*
     * Below instances are applicable only to TI81xx platforms.
     */
    VPSHAL_VPDMA_GENERIC,
    /**< VPDMA instance common to all. */

    VPSHAL_VPDMA_INST_ID_MAX
    /**< Max - used for error check. */
} VpsHal_VpdmaInst;

/**
 *  \brief VPDMA maximum number of instances for any given platform - used for
 *  memory allocation.
 */
#define VPSHAL_VPDMA_MAX_INST           (4U)

/**
 *  enum VpsHal_VpdmaFirmwareVersion
 *  \brief Enumeration for VPDMA firmware versions
 */
typedef enum
{
    VPSHAL_VPDMA_NO_FIRMWARE_LOADED = 0,
    VPSHAL_VPDMA_VER_DEFAULT,
    VPSHAL_VPDMA_VER_288,
    VPSHAL_VPDMA_VER_1B8,
    VPSHAL_VPDMA_VER_MAX
} VpsHal_VpdmaFirmwareVersion;

/**
 *  enum VpsHal_VpdmaChanDT
 *  \brief Enums for data types that VPDMA channel can
 *  accept. This enum can be used directly to set the data type in data
 *  descriptor
 */
typedef enum
{
    VPSHAL_VPDMA_CHANDT_RGB565 = 0,
    /**< RGB  565 */
    VPSHAL_VPDMA_CHANDT_ARGB1555 = 1,
    /**< ARGB 1555 */
    VPSHAL_VPDMA_CHANDT_ARGB4444 = 2,
    /**< ARGB 4444 */
    VPSHAL_VPDMA_CHANDT_RGBA5551 = 3,
    /**< RGBA 5551 */
    VPSHAL_VPDMA_CHANDT_RGBA4444 = 4,
    /**< RGBA 4444 */
    VPSHAL_VPDMA_CHANDT_ARGB6666 = 5,
    /**< ARGB 6666 */
    VPSHAL_VPDMA_CHANDT_RGB888 = 6,
    /**< RGB  888 */
    VPSHAL_VPDMA_CHANDT_ARGB8888 = 7,
    /**< ARGB 8888 */
    VPSHAL_VPDMA_CHANDT_RGBA6666 = 8,
    /**< RGBA 6666 */
    VPSHAL_VPDMA_CHANDT_RGBA8888 = 9,
    /**< RGBA 8888 */
    /*new for PG2.0*/
    VPSHAL_VPDMA_CHANDT_BGR565 = 0x10,
    /**< BGR 565 */
    VPSHAL_VPDMA_CHANDT_ABGR1555 = 0x11,
    /**< ABGR 1555 */
    VPSHAL_VPDMA_CHANDT_ABGR4444 = 0x12,
    /**< ABGR 4444 */
    VPSHAL_VPDMA_CHANDT_BGRA5551 = 0x13,
    /**< BGRA 1555 */
    VPSHAL_VPDMA_CHANDT_BGRA4444 = 0x14,
    /**< BGRA 4444 */
    VPSHAL_VPDMA_CHANDT_ABGR6666 = 0x15,
    /**< ABGR 6666 */
    VPSHAL_VPDMA_CHANDT_BGR888 = 0x16,
    /**< BGR 888 */
    VPSHAL_VPDMA_CHANDT_ABGR8888 = 0x17,
    /**< ABGR 8888 */
    VPSHAL_VPDMA_CHANDT_BGRA6666 = 0x18,
    /**< BGRA 6666 */
    VPSHAL_VPDMA_CHANDT_BGRA8888 = 0x19,
    /**< BGRA 8888 */
    VPSHAL_VPDMA_CHANDT_BITMAP8 = 0x20,
    /**< 8 bit clut */
    VPSHAL_VPDMA_CHANDT_BITMAP4_LOWER = 0x22,
    /**< 4 bit clut with lower address */
    VPSHAL_VPDMA_CHANDT_BITMAP4_UPPER = 0x23,
    /**< 4 bit clut with upper address */
    VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET0 = 0x24,
    /**< 2 bit clut with offset0 */
    VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET1 = 0x25,
    /**< 2 bit clut with offset1 */
    VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET2 = 0x26,
    /**< 2 bit clut with offset2 */
    VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET3 = 0x27,
    /**< 2 bit clut with offset3 */
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET0 = 0x28,
    /**< 1 bit clut with offset0 */
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET1 = 0x29,
    /**< 1 bit clut with offset1 */
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET2 = 0x2A,
    /**< 1 bit clut with offset2 */
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET3 = 0x2B,
    /**< 1 bit clut with offset3 */
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET4 = 0x2C,
    /**< 1 bit clut with offset4 */
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET5 = 0x2D,
    /**< 1 bit clut with offset5 */
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET6 = 0x2E,
    /**< 1 bit clut with offset6 */
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET7 = 0x2F,
    /**< 1 bit clut with offset7 */
    /*new for PG2.0*/
    VPSHAL_VPDMA_CHANDT_BITMAP8_BGRA32 = 0x30,
    /**< 8 bit clut with BGRA32 format */
    VPSHAL_VPDMA_CHANDT_BITMAP4_LOWER_BGRA32 = 0x32,
    /**< 4 bit clut lower address with BGRA32 format */
    VPSHAL_VPDMA_CHANDT_BITMAP4_UPPER_BGRA32 = 0x33,
    /**< 4 bit clut UPPER address with BGRA32 format */
    VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET0_BGRA32 = 0x34,
    /**< 2 bit clut with offset0 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET1_BGRA32 = 0x35,
    /**< 2 bit clut with offset1 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET2_BGRA32 = 0x36,
    /**< 2 bit clut with offset2 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP2_OFFSET3_BGRA32 = 0x37,
    /**< 2 bit clut with offset3 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET0_BGRA32 = 0x38,
    /**< 1 bit clut with offset0 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET1_BGRA32 = 0x39,
    /**< 1 bit clut with offset1 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET2_BGRA32 = 0x3A,
    /**< 1 bit clut with offset2 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET3_BGRA32 = 0x3B,
    /**< 1 bit clut with offset3 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET4_BGRA32 = 0x3C,
    /**< 1 bit clut with offset4 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET5_BGRA32 = 0x3D,
    /**< 1 bit clut with offset5 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET6_BGRA32 = 0x3E,
    /**< 1 bit clut with offset6 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_BITMAP1_OFFSET7_BGRA32 = 0x3F,
    /**< 1 bit clut with offset7 BGRA32 format*/
    VPSHAL_VPDMA_CHANDT_Y444 = 0,
    /**< Y 4:4:4 */
    VPSHAL_VPDMA_CHANDT_Y422 = 1,
    /**< Y 4:2:2 */
    VPSHAL_VPDMA_CHANDT_Y420 = 2,
    /**< Y 4:2:0 */
    VPSHAL_VPDMA_CHANDT_C444 = 4,
    /**< U 4:4:4 */
    VPSHAL_VPDMA_CHANDT_C422 = 5,
    /**< Chroma plane in (4:2:2 U:V) */
    VPSHAL_VPDMA_CHANDT_C420 = 6,
    /**< Chroma plane in NV12 (4:2:0 U:V) */
    VPSHAL_VPDMA_CHANDT_YC422 = 7,
    /**< YC 4:2:2 Y on LSB, C on MSB i.e. YUYV */
    VPSHAL_VPDMA_CHANDT_YC444 = 8,
    /**< YC 4:4:4 Y on LSB, C on MSB */
    VPSHAL_VPDMA_CHANDT_MV = 3,
    /**< Motion Vector and MVSTM are 4-bit data */
    VPSHAL_VPDMA_CHANDT_STENCIL = 0,
    /**< Stencil Data is 1-bit. */
    VPSHAL_VPDMA_CHANDT_CLUT = 7,
    /**< CLUT Table is 8-bit. */
    VPSHAL_VPDMA_CHANDT_ANC = 8,
    /**< Ancillary Data is 8-bit. */
    VPSHAL_VPDMA_CHANDT_Cb444 = 0x14,
    /**< V 4:4:4 */
    VPSHAL_VPDMA_CHANDT_Cb422 = 0x15,
    /**< Chroma plane in (4:2:2 V:U) */
    VPSHAL_VPDMA_CHANDT_Cb420 = 0x16,
    /**< Chroma plane in NV21 (4:2:0 V:U) */
    VPSHAL_VPDMA_CHANDT_YCb422 = 0x17,
    /**< YC 4:2:2 Y on LSB, C on MSB i.e. YVYU */
    VPSHAL_VPDMA_CHANDT_CY422 = 0x27,
    /**< CY 4:2:2 C on LSB, Y on MSB i.e. UYVY */
    VPSHAL_VPDMA_CHANDT_CbY422 = 0x37,
    /**< CY 4:2:2 C on LSB, Y on MSB i.e. VYUY */
    VPSHAL_VPDMA_CHANDT_INVALID = 0xFF
                                  /**< Invalid Data Type */
} VpsHal_VpdmaChanDT;

/**
 *  enum VpsHal_VpdmaLineSkip
 *  \brief Enum for number of line skip supported by VPDMA
 */
typedef enum
{
    VPSHAL_VPDMA_LS_1 = 0,
    /**< Skip 1 line */
    VPSHAL_VPDMA_LS_2
    /**< Skip 2 lines */
} VpsHal_VpdmaLineSkip;

typedef enum
{
    VPSHAL_VPDMA_LM_0 = 0,
    /**< repeat lines twice each output data line gets 2 times the number
     *   of frame lines */
    VPSHAL_VPDMA_LM_1,
    /**< each line once with Line Buffer Disabled, so no mirroring. Each
     *   line gets frame lines with identical data */
    VPSHAL_VPDMA_LM_2,
    /**< Each line seen once Mirroring is enabled so the top lines get
     *   the top lines repeated at the top of the frame and the bottom
     *   lines have the bottom lines repeated. Each line of data gets
     *   frame lines + number of buffered lines */
    VPSHAL_VPDMA_LM_3
    /**< Each line once only on one line. Each data line gets number of
     *   frame lines divided by number of buffered lines */
} VpsHal_VpdmaLineMode;

/**
 *  enum VpsHal_VpdmaDataDescPrio
 *  \brief Enum for setting OCP bus priority for a data descriptor in VPDMA
 */
typedef enum
{
    VPSHAL_VPDMA_DATADESCPRIO_0 = 0,
    /**< Highest Priority */
    VPSHAL_VPDMA_DATADESCPRIO_1,
    VPSHAL_VPDMA_DATADESCPRIO_2,
    VPSHAL_VPDMA_DATADESCPRIO_3,
    VPSHAL_VPDMA_DATADESCPRIO_4,
    VPSHAL_VPDMA_DATADESCPRIO_5,
    VPSHAL_VPDMA_DATADESCPRIO_6,
    VPSHAL_VPDMA_DATADESCPRIO_7
    /**< Lowest Priority */
} VpsHal_VpdmaDataDescPrio;

/**
 *  enum VpsHal_VpdmaMemoryType
 *  \brief Enum for type of memory where data is (read from)/(written to)
 */
typedef enum
{
    VPSHAL_VPDMA_MT_NONTILEDMEM = 0,
    /**< Non-Tiled Memory. */
    VPSHAL_VPDMA_MT_TILEDMEM
    /**< Tiled Memory. */
} VpsHal_VpdmaMemoryType;

/**
 *  \brief Enum for frame start event. This tells VPDMA
 *  which NF signal to use for a client. This has to be configured on the
 *  channel associated with client.
 */
typedef enum
{
    VPSHAL_VPDMA_FSEVENT_HDMI_FID = 0,
    /**< Change in value of hdmi_field_id */
    VPSHAL_VPDMA_FSEVENT_DVO2_FID,
    /**< Change in value of dvo2_field_id */
    VPSHAL_VPDMA_FSEVENT_HDCOMP_FID,
    /**< Change in value of hdcomp_field_id */
    VPSHAL_VPDMA_FSEVENT_SD_FID,
    /**< Change in value of sd_field_id */
    VPSHAL_VPDMA_FSEVENT_LM_FID0,
    /**< Use List Manager Internal Field - 0 */
    VPSHAL_VPDMA_FSEVENT_LM_FID1,
    /**< Use List Manager Internal Field - 1 */
    VPSHAL_VPDMA_FSEVENT_LM_FID2,
    /**< Use List Manager Internal Field - 2*/
    VPSHAL_VPDMA_FSEVENT_CHANNEL_ACTIVE
    /**< Start on channel active */
} VpsHal_VpdmaFSEvent;

/**
 *  enum VpsHal_VpdmaSocEvent
 *  \brief This defines the different sync events supported by the
 *  Sync On Client control descriptor
 */
typedef enum
{
    VPSHAL_VPDMA_SOC_EOF = 0,
    /**< End of Frame */
    VPSHAL_VPDMA_SOC_SOF,
    /**< Start of Frame */
    VPSHAL_VPDMA_SOC_EOL,
    /**< End of Line X */
    VPSHAL_VPDMA_SOC_SOL,
    /**< Start of Line X */
    VPSHAL_VPDMA_SOC_PIXEL,
    /**< Matching exact pixel */
    VPSHAL_VPDMA_SOC_ACTIVE,
    /**< Client is Active */
    VPSHAL_VPDMA_SOC_NOTACTIVE,
    /**< Client is not active */
    VPSHAL_VPDMA_SOC_FID_CHANGE01,
    /**< Field Change from 0 to 1 */
    VPSHAL_VPDMA_SOC_FID_CHANGE10,
    /**< Field Change from 1 to 0 */
    VPSHAL_VPDMA_SOC_EOEL
    /**< End of Every Line X */
} VpsHal_VpdmaSocEvent;

/**
 *  enum VpsHal_VpdmaDescSize
 *  \brief Enum for size in bytes of different types of lists
 */
typedef enum
{
    VPSHAL_VPDMA_DATA_DESC_SIZE = 32U,
    /**< VPDMA Data descriptor size */
    VPSHAL_VPDMA_CTRL_DESC_SIZE = 16U,
    /**< VPDMA Control descriptor size */
    VPSHAL_VPDMA_CONFIG_DESC_SIZE = 16U
                                    /**< VPDMA Config descriptor size */
} VpsHal_VpdmaDescSize;

/**
 *  enum VpsHal_VpdmaListType
 *  \brief Enum for type of the list supported by VPDMA
 */
typedef enum
{
    VPSHAL_VPDMA_LT_NORMAL = 0,
    /**< Normal List */
    VPSHAL_VPDMA_LT_SELFMODIFYING = 1,
    /**< Self Modifying List */
    VPSHAL_VPDMA_LT_DEBUG = 7
                            /**< List type for VPDMA debugging */
} VpsHal_VpdmaListType;

/** Masks for addresses for input and output buffers */
#define VPSHAL_VPDMA_DATADESC_INBUFFERMASK     (0xFFFFFFFCU)
#define VPSHAL_VPDMA_DATADESC_INBUFFEROFFSET   (2U)
#define VPSHAL_VPDMA_DATADESC_OUTBUFFERMASK    (0xFFFFFFE0U)
#define VPSHAL_VPDMA_DATADESC_OUTBUFFEROFFSET  (5U)

/**
 *  enum VpsHal_VpdmaConfigDest
 *  \brief This defines the configuration destinations.
 *  This enum can be used directly to set the destination field of
 *  configuration descriptor
 */
typedef enum
{
    VPSHAL_VPDMA_CONFIG_DEST_MMR = 0,
    /**< Destination is MMR client */
    VPSHAL_VPDMA_CONFIG_DEST_SC_GRPX0,
    /**< Graphics 0 scaler */
    VPSHAL_VPDMA_CONFIG_DEST_SC_GRPX1,
    /**< Graphics 1 scaler */
    VPSHAL_VPDMA_CONFIG_DEST_SC_GRPX2,
    /**< Graphics 2 scaler */
    VPSHAL_VPDMA_CONFIG_DEST_SC1,
    /**< Primary path scaler */
    VPSHAL_VPDMA_CONFIG_DEST_SC2,
    /**< Aux path scaler */
    VPSHAL_VPDMA_CONFIG_DEST_SC5,
    /**< Write back 2 scaler */
    VPSHAL_VPDMA_CONFIG_DEST_SC3,
    /**< Video Input Port 0 scaler */
    VPSHAL_VPDMA_CONFIG_DEST_SC4
    /**< Video Input Port 1 scaler */
} VpsHal_VpdmaConfigDest;

/**
 *  \brief Enum for specifying configuration descriptor payload type
 *  i.e. Address set or Block set
 */
typedef enum
{
    VPSHAL_VPDMA_CPT_ADDR_DATA_SET = 0,
    /**< Payload consists of Blocks of addresses */
    VPSHAL_VPDMA_CPT_BLOCK_SET
    /**< Payload consists of simple a block of data */
} VpsHal_VpdmaConfigPayloadType;

/**
 *  Enum for specifying configuration command type i.e. Direct or
 *  indirect
 */
typedef enum
{
    VPSHAL_VPDMA_CCT_INDIRECT = 0,
    /**< Payload is stored somewhere in memory */
    VPSHAL_VPDMA_CCT_DIRECT
    /**< Payload is contiguous with config desc */
} VpsHal_VpdmaConfigCmdType;

/**
 * \brief VpsHal_VpdmaPath
 *  Enum defining VPDMA path
 */
typedef enum
{
    VPSHAL_VPDMA_PATH_VIP0_LO_UV = 0,
    VPSHAL_VPDMA_PATH_VIP0_LO_Y,
    VPSHAL_VPDMA_PATH_VIP0_UP_UV,
    VPSHAL_VPDMA_PATH_VIP0_UP_Y,
    VPSHAL_VPDMA_PATH_VIP1_LO_UV,
    VPSHAL_VPDMA_PATH_VIP1_LO_Y,
    VPSHAL_VPDMA_PATH_VIP1_UP_UV,
    VPSHAL_VPDMA_PATH_VIP1_UP_Y,
    VPSHAL_VPDMA_PATH_VIP0_ANCA,
    VPSHAL_VPDMA_PATH_VIP0_ANCB,
    VPSHAL_VPDMA_PATH_VIP1_ANCA,
    VPSHAL_VPDMA_PATH_VIP1_ANCB,
    VPSHAL_VPDMA_PATH_SEC0,
    VPSHAL_VPDMA_PATH_SEC1,
    VPSHAL_VPDMA_PATH_PRI,
    VPSHAL_VPDMA_PATH_WB0,
    VPSHAL_VPDMA_PATH_AUX,
    VPSHAL_VPDMA_PATH_WB1,
    VPSHAL_VPDMA_PATH_BP0,
    VPSHAL_VPDMA_PATH_BP1,
    VPSHAL_VPDMA_PATH_WB2,
    VPSHAL_VPDMA_PATH_GRPX0,
    VPSHAL_VPDMA_PATH_GRPX0_STENC,
    VPSHAL_VPDMA_PATH_GRPX1,
    VPSHAL_VPDMA_PATH_GRPX1_STENC,
    VPSHAL_VPDMA_PATH_GRPX2,
    VPSHAL_VPDMA_PATH_GRPX2_STENC,
    VPSHAL_VPDMA_PATH_VBI_HD,
    VPSHAL_VPDMA_PATH_VBI_SD,
    VPSHAL_VPDMA_PATH_NF,
    VPSHAL_VPDMA_MAX_PATH
} VpsHal_VpdmaPath;

/**
 *  Different alignment constraints for lists and descriptors
 *  List size is always in terms of 128 bit words so it is aligned on 16
 *  bytes boundary
 */
#define VPSHAL_VPDMA_DESC_BYTE_ALIGN           (UInt32) (16U)
#define VPSHAL_VPDMA_CONFIG_PAYLOAD_BYTE_ALIGN (UInt32) (16U)
#define VPSHAL_VPDMA_LIST_SIZE_SHIFT           (UInt32) (4U)
#define VPSHAL_VPDMA_LIST_SIZE_ALIGN           (UInt32) (16U)
#define VPSHAL_VPDMA_LIST_ADDR_ALIGN           (UInt32) (16U)
#define VPSHAL_VPDMA_LINE_STRIDE_ALIGN         (UInt32) (16U)
#define VPSHAL_VPDMA_BUF_ADDR_ALIGN            (UInt32) (16U)
#define VPSHAL_VPDMA_WR_DESC_BUF_ADDR_ALIGN    ((UInt32) 32U)
/* Config descriptors related */
#define VPSHAL_VPDMA_CONFIG_PAYLOAD_ADDR_ALIGN (UInt32) (16U)
#define VPSHAL_VPDMA_CONFIG_PAYLOAD_SIZE_ALIGN (UInt32) (16U)
#define VPSHAL_VPDMA_CONFIG_PAYLOAD_SIZE_SHIFT (UInt32) (4U)
#define VPSHAL_VPDMA_CONFIG_DATA_SIZE_MASK     (UInt32) (0x0000FFFFU)

/* Max frame size in data descriptor */
#define VPSHAL_VPDMA_MAX_FRAME_WIDTH            (UInt32) (4096U)
#define VPSHAL_VPDMA_MAX_FRAME_HEIGHT           (UInt32) (2048U)

/* Minumum width is suggested by hardware team. This
 * is not the actual hardware restriction, but combination
 * of hardware paths like SC_H, DEI_H etc
 */
#define VPSHAL_VPDMA_MIN_FRAME_WIDTH            (UInt32) (24U)
#define VPSHAL_VPDMA_MIN_FRAME_HEIGHT           (UInt32) (8U)

/**
 *  VpsHal_VpdmaIntLine
 *  Enum for specifying interrupt lines inside VPDMA
 */
typedef enum
{
    VPSHAL_VPDMA_INT0 = 0,
#ifdef TDA3XX_FAMILY_BUILD
    VPSHAL_VPDMA_INT1
#elif defined TDA2XX_FAMILY_BUILD
    VPSHAL_VPDMA_INT1
#elif defined TI814X_FAMILY_BUILD
    VPSHAL_VPDMA_INT1,
    VPSHAL_VPDMA_INT2,
    VPSHAL_VPDMA_INT3
#endif
} VpsHal_VpdmaIntLine;

/* ========================================================================= */
/*                         Structure Declarations                            */
/* ========================================================================= */
/**
 *  struct VpsHal_VpdmaOpenParams
 *  \brief Structure to identify a VPDMA HAL instance
 */

typedef struct
{
    UInt32                      halId;
    /**< VPDMA Instance ID: #VpsHal_VpdmaInst */

    VpsHal_VpdmaFirmwareVersion ver;
    /**< VPDMA Firware version to use #VpsHal_VpdmaFirmwareVersion */
} VpsHal_VpdmaOpenParams;

/**
 *  struct VpsHal_VpdmaInstParams
 *  \brief Structure containg parameters to initialize VPDMA HAL instance
 *         Primarily baseAddress.
 */

typedef struct
{
    UInt32 halId;
    /**< VPDMA Instance ID: #VpsHal_VpdmaInst */
    UInt32 baseAddr;
    /**< Base address for the current instance */
    Bool   isAddrTransReq;
    /**< Set this flag to TRUE if the driver has to perform address translation
     *   of the descriptor memory before submitting the descriptor to the
     *   hardware. This is used when the physical memory of the descriptor
     *   is mapped to a different virtual memory.
     *
     *   When address translation is enabled, the dirver performs the following
     *   operations to convert the virtual address to physical address and
     *   vice versa.
     *
     *   physAddr = (virtAddr - virtBaseAddr) + physBaseAddr;
     *   virtAddr = (physAddr - physBaseAddr) + virtBaseAddr;
     *
     *   Important: The descriptor memory should in a physically continuous
     *   memory.
     *
     *   Note: The buffer address will not be translated using the above
     *   translation and hence the application should provide the physical
     *   address to be programmed to the hardware. */
    UInt32 virtBaseAddr;
    /**< Virtual memory base address. */
    UInt32 physBaseAddr;
    /**< Physical memory base address. */
    UInt32 isCacheOpsReq;
    /**< This will enable cache flush and invalidate operations on the
     *   descriptor memory in case the descriptor memory is cache region.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
    UInt32 isCacheFlushReq;
    /**< This will enable cache flush operations on the
     *   descriptor memory in case the descriptor memory is cache region.
     *   In case of write-through cache mode, this flag could be set to FALSE
     *   to save cycles as flush operation is not required in write-through
     *   mode.
     *   This parameter is valid/used only if isCacheOpsReq is TRUE.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
} VpsHal_VpdmaInstParams;

/**
 *  struct VpsHal_VpdmaOutDescParams
 *  \brief This structure is for creating
 *  outbound data descriptor. Upper layer passes pointer of this structure to
 *  the createOutBoundDataDesc function to create the data data descriptor in
 *  the given memory.
 */

typedef struct
{
    VpsHal_VpdmaChannel      channel;
    /**< VPDMA Channel number for which data descriptor is to be created */
    VpsHal_VpdmaChanDT       dataType;
    /**< Channel Data Type */
    UInt16                   lineStride;
    /**< Line stride in bytes between two lines in transfer window */
    VpsHal_VpdmaLineSkip     lineSkip;
    /**< Number of lines to skip after each line in transfer window.This along
     *   with the lineStride is used to calculate next line address */
    UInt32                   notify;
    /**< Fires notify interrupt for this list at end of data transfer */
    VpsHal_VpdmaDataDescPrio priority;
    /**< Data descriptor priority */
    VpsHal_VpdmaMemoryType   memType;
    /**< Type of memory i.e. Tiled or Non-Tiled. */
    VpsHal_VpdmaChannel      nextChannel;
    /**< Next channel to be programmed in the outbound descriptor */
    Vps_VpdmaMaxOutWidth     maxWidth;
    /**< The maximum number of pixes per line */
    Vps_VpdmaMaxOutHeight    maxHeight;
    /**< The maximum number of lines per frame */
    UInt32                   is1DData;
    /**< Is this 1D data */
} VpsHal_VpdmaOutDescParams;

/**
 *  struct VpsHal_VpdmaInDescParams
 *  \brief This structure is for creating
 *  inbound data descriptor. Upper layer passes pointer of this structure to
 *  the createInBoundDataDesc function to create the data data descriptor in
 *  the given memory.
 */
typedef struct
{
    VpsHal_VpdmaChannel      channel;
    /**< VPDMA Channel number for which data descriptor is to be created */
    VpsHal_VpdmaChanDT       dataType;
    /**< Channel Data Type */
    UInt16                   transWidth;
    /**< Width of the buffer. VPDMA provides feature using which it can read
     *   small buffer and provide larger frame to the downstream module by
     *   filing up the remaining buffer with the background color. Transfer size
     *   refers to the input buffer size and frame size refers to the target
     *   buffer provided to the downstream module.*/
    UInt16                   transHeight;
    /**< Height of the buffer */
    UInt16                   frameWidth;
    /**< Width of frame */
    UInt16                   frameHeight;
    /**< Height of the frame */
    UInt16                   startX;
    /**< Horizontal start position of the transfer window in frame window */
    UInt16                   startY;
    /**< Vertical start position of the transfer window in frame window */
    UInt16                   lineStride;
    /**< Line stride in bytes between two lines in transfer window */
    VpsHal_VpdmaLineSkip     lineSkip;
    /**< Number of lines to skip after each line in transfer window. This along
     *   with the lineStride is used to calculate next line address */
    VpsHal_VpdmaChannel      nextChannel;
    /**< For virtual video buffer or region base graphics, this parameter is
     *   used to the specify channel number of the next free channel */
    UInt32                   notify;
    /**< Fires notify interrupt for this list at end of data transfer */
    VpsHal_VpdmaDataDescPrio priority;
    /**< Data descriptor priority */
    VpsHal_VpdmaMemoryType   memType;
    /**< Type of memory i.e. Tiled or Non-Tiled. */
    UInt32                   is1DData;
    /**< Is this 1D data */
} VpsHal_VpdmaInDescParams;

typedef struct
{
    VpsHal_VpdmaChannel      channel;
    /**< VPDMA Channel number for which data descriptor is to be created */
    VpsHal_VpdmaChanDT       dataType;
    /**< Channel Data Type */
    UInt16                   transWidth;
    /**< Width of the buffer. VPDMA provides feature using which it can read
     *   small buffer and provide larger frame to the downstream module by
     *   filing up the remaining buffer with the background color. Transfer size
     *   refers to the input buffer size and frame size refers to the target
     *   buffer provided to the downstream module.*/
    UInt16                   transHeight;
    /**< Height of the buffer */
    UInt16                   frameWidth;
    /**< Width of frame */
    UInt16                   frameHeight;
    /**< Height of the frame */
    UInt16                   startX;
    /**< Horizontal start position of the transfer window in frame window */
    UInt16                   startY;
    /**< Vertical start position of the transfer window in frame window */
    UInt16                   lineStride;
    /**< Line stride in bytes between two lines in transfer window */
    VpsHal_VpdmaLineSkip     lineSkip;
    /**< Number of lines to skip after each line in transfer window. This along
     *   with the lineStride is used to calculate next line address */
    VpsHal_VpdmaChannel      nextChannel;
    /**< For virtual video buffer or region base graphics, this parameter is
     *   used to the specify channel number of the next free channel */
    UInt32                   notify;
    /**< Fires notify interrupt for this list at end of data transfer */
    VpsHal_VpdmaDataDescPrio priority;
    /**< Data descriptor priority */
    VpsHal_VpdmaMemoryType   memType;
    /**< Type of memory i.e. Tiled or Non-Tiled. */
    Bool                     is1DData;
    /**< Is this 1D data */
    UInt32                   fid;
    /**< Captured FID as seen in the write descriptor */
    Ptr                      bufferAddr;
    /**< Captured buffer address as seen in the write descriptor */
    Bool                     isValid;
    /**< Is the write descriptor valid */
} VpsHal_VpdmaWriteDescParams;

/* ========================================================================== */
/*                        Public Function Declarations                        */
/* ========================================================================== */
/**
 *  VpsHal_vpdmaInit
 *  \brief VPDMA HAL init function.
 *  This function should be called before calling any of VPDMA HAL API's.
 *
 *  \param numInst          Number of instances to initialize.
 *  \param instPrms         Pointer to #VpsHal_VpdmaInstParams.
 *  \param arg              Not used currently. Meant for future purpose.
 *
 *  \return                 TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_vpdmaInit(UInt32                        numInst,
                       const VpsHal_VpdmaInstParams *instPrms,
                       Ptr                           arg);

/**
 *  VpsHal_vpdmaDeInit
 *  \brief VPDMA HAL exit function.
 *  Resets internal variables.
 *
 *  \param arg      Not used currently. Meant for future purpose
 *
 *  \return         TODO: Error check. Always returns BSP_SOK for now.
 *
 */
Int32 VpsHal_vpdmaDeInit(Ptr arg);

/**
 *  VpsHal_vpdmaOpen
 *  \brief Returns the handle to the requested VPDMA instance.
 *  Multiple handles are supported. TODO: Check on multiple handle support
 *
 *  This function should be called prior to calling any of the VPDMA HAL
 *  configuration APIs.
 *
 *  VpsHal_vpdmaInit should be called prior to this
 *  Caller shall ensure simulataneous calls do not happen.
 *
 *  \param openPrms     VpsHal_VpdmaOpenParams
 *
 *  \return              success     VPDMA instance's HAL handle
 *                       failure     NULL
 */
VpsHal_Handle VpsHal_vpdmaOpen(const VpsHal_VpdmaOpenParams *openPrms);

/**
 *  VpsHal_vpdmaClose
 *  \brief Closes specified instance of VPDMA HAL
 *  VpsHal_vpdmaInit and VpsHal_vpdmaOpen should be called prior to this.
 *  Reset internal variables of the HAL handle
 *
 *  \param handle       Valid handle returned by VpsHal_vpdmaOpen function.
 *
 *  \return             success    0
 *                      failure    error value
 */
Int32 VpsHal_vpdmaClose(VpsHal_Handle handle);

/**
 *  VpsHal_vpdmaPostList
 *  \brief Function for posting the list to the VPDMA. Once posted, VPDMA will
 *  start reading and processing the list. It is interrupt protected so
 *  can be called from the interrupt context also.
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param configOvlyPtr      Register Overlay address. Ignored if 0.
 *  \param listNum          List Number
 *  \param listType         List Type i.e. Normal or Self Modifying
 *  \param listAddr         Physical address of the contiguous memory
 *                          containing list
 *  \param listSize         List size in bytes
 *  \param enableCheck      Flag to indicate whether parameter check needs to
 *                          be done or not. TODO: Not used currently.
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_vpdmaPostList(VpsHal_Handle        handle,
                           UInt8                listNum,
                           VpsHal_VpdmaListType listType,
                           Ptr                  listAddr,
                           UInt32               listSize,
                           UInt32               enableCheck);
/**
 *  VpsHal_vpdmaStopList
 *  \brief Function to stop the self modiyfing list. Self modifying list is a
 *  free running list. It is like a circular list which runs on its own.
 *  This function is used to stop self modifying list. When stop bit is set,
 *  it completes the current transfer and stops the list.
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param listNum          List to be stopped
 *  \param listType         NONE
 */
void VpsHal_vpdmaStopList(VpsHal_Handle        handle,
                          UInt8                listNum,
                          VpsHal_VpdmaListType listType);

/**
 *  VpsHal_vpdmaListWaitComplete
 *  \brief Function for posting the list to the VPDMA. Once posted, VPDMA will
 *  start reading and processing the list. It is interrupt protected so
 *  can be called from the interrupt context also.
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param listNum          List Number to wait for
 *  \param timeout          Control loop-count while waiting for list to
 *                          complete. ~multiple of 1ms
 *
 *  \return                 BSP_SOK if list complete is detected,
 *                          BSP_EFAIL otherwise.
 */
Int32 VpsHal_vpdmaListWaitComplete(VpsHal_Handle handle,
                                   UInt8         listNum,
                                   UInt32        timeout);

/**
 *  VpsHal_vpdmaSetFrameStartEvent
 *  \brief Function is used to set the frame start event for the channel/client.
 *  This function tells VPDMA to use a given source of NF to transfer data
 *  to the down stream module. VPDMA starts transfer of data at the NF
 *  signal only. If there is no NF signal, it will transfer data to the
 *  internal FIFO. When FIFO becomes full, that channel will be blocked.
 *  Upper layer should pass the channel number to set the frame
 *  start event and VPDMA HAL sets it in the client register. This VPDMA
 *  client is the one associated with the channel number. If event is to
 *  be set for multiplexed client, upper layer can pass any channel
 *  associated with that client to set frame start event
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param chanNum          Channel Number for which frame start event is
 *                          to be set
 *  \param fsEvent          Source of NF signal
 *  \param lineMode         NONE
 *  \param reqDelay         NONE
 *  \param ovlyPtr          NONE
 *  \param index            NONE
 *  \return                 None
 */
Void VpsHal_vpdmaSetFrameStartEvent(VpsHal_Handle        handle,
                                    VpsHal_VpdmaChannel  chanNum,
                                    VpsHal_VpdmaFSEvent  fsEvent,
                                    VpsHal_VpdmaLineMode lineMode,
                                    UInt32               reqDelay,
                                    Ptr                  ovlyPtr,
                                    UInt32               index);

/**
 *  VpsHal_vpdmaCreateOutBoundDataDesc
 *  \brief Function to create Out Bound Data descriptor from the given
 *  parameters and in the given contiguous memory. Memory pointer given must
 *  contain physically contiguous memory because VPDMA works with that only.
 *
 *  \param memPtr           Pointer to physically contiguous memory into
 *                          which descriptor will be created
 *  \param descInfo         Pointer to structure containing out bound data
 *                          descriptor parameters
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_vpdmaCreateOutBoundDataDesc(
    Ptr memPtr,
    const VpsHal_VpdmaOutDescParams *
    descInfo);

/**
 *  VpsHal_vpdmaCreateInBoundDataDesc
 *  \brief Function to create In Bound Data descriptor from the given parameters
 *  and in the given contiguous memory. Memory pointer given must contain
 *  physically contiguous memory because VPDMA works with that only.
 *
 *  \param memPtr           Pointer to physically contiguous memory into
 *                          which descriptor will be created
 *  \param descInfo         Pointer to structure containing in bound data
 *                          descriptor parameters
 *  \return                 Returns 0 on success else returns error value
 */
Int32 VpsHal_vpdmaCreateInBoundDataDesc(
    Ptr memPtr,
    const VpsHal_VpdmaInDescParams *
    descInfo);

Int32 VpsHal_vpdmaParseWriteDesc(const void                  *memPtr,
                                 VpsHal_VpdmaWriteDescParams *descInfo);

/**
 *  VpsHal_vpdmaSetSyncList
 *  \brief Function to register bit for the Sync on Register event.
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param listNum          List Number
 *  \return                 None
 */
Void VpsHal_vpdmaSetSyncList(VpsHal_Handle handle, UInt8 listNum);

/**
 *  VpsHal_vpdmaCreateSICtrlDesc
 *  \brief Function to create a Send Interrupt Control Descriptor
 *  in the given memory
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param source           Send Interrupt source possible values are 0-15
 *  \return                 None
 */
Void VpsHal_vpdmaCreateSICtrlDesc(Ptr memPtr, UInt16 source);

/**
 *  VpsHal_vpdmaCreateRLCtrlDesc
 *  \brief Function to create Reload Control Descriptor in the given memory
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param rlListAddr       Address of the memory from where list is to be
 *                          reloaded
 *  \param size             Size of the reloaded list in bytes
 *  \return                 None
 */
Void VpsHal_vpdmaCreateRLCtrlDesc(Ptr    memPtr,
                                  Ptr    rlListAddr,
                                  UInt32 size);

/**
 *  VpsHal_vpdmaCreateAbortCtrlDesc
 *  \brief Function to create a control descriptor to Invert List Manager
 *  FID
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param channelNum       Channel whose data transfer is to be aborted
 *  \return                 None
 */
Void VpsHal_vpdmaCreateAbortCtrlDesc(Ptr                 memPtr,
                                     VpsHal_VpdmaChannel channelNum);

/**
 *  VpsHal_vpdmaCreateSORCtrlDesc
 *  \brief Function to create Sync On Register Control Descriptor in the
 *  given memory
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param listNum          List Number for which SOR is to be created
 *  \return                 None
 */
Void VpsHal_vpdmaCreateSORCtrlDesc(Ptr memPtr, UInt8 listNum);

/**
 *  VpsHal_vpdmaCreateSOCHCtrlDesc
 *  \brief Function to create Sync On Channel Control Descriptor in the
 *  given memory
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param chNum            Channel Number to sync on
 *  \return                 None
 */
Void VpsHal_vpdmaCreateSOCHCtrlDesc(Ptr                 memPtr,
                                    VpsHal_VpdmaChannel chNum);

/**
 *  VpsHal_vpdmaCreateCCISCtrlDesc
 *  Function to create a Change client interrupt source control descriptor
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param channelNum       Channel whose interrupt is to be changed
 *  \param event            event to which interrupt is to be changed
 *  \param lineCount        Line Count
 *  \param pixCount         Pixel Count
 *  \return                 None
 */
Void VpsHal_vpdmaCreateCCISCtrlDesc(Ptr                  memPtr,
                                    VpsHal_VpdmaChannel  channelNum,
                                    VpsHal_VpdmaSocEvent event,
                                    UInt16               lineCount,
                                    UInt16               pixCount);

/**
 *  VpsHal_vpdmaCreateSOCCtrlDesc
 *  \brief Function to create a Sync on Client control Descriptor
 *
 *  \param memPtr           Pointer to the memory in which control
 *                          descriptor is to be created
 *  \param chNum            Channel whose interrupt is to be changed
 *  \param event            event to which interrupt is to be changed
 *  \param lineCount        Line Count
 *  \param pixCount         Pixel Count
 *  \return                 None
 */
Void VpsHal_vpdmaCreateSOCCtrlDesc(Ptr                  memPtr,
                                   VpsHal_VpdmaChannel  chNum,
                                   VpsHal_VpdmaSocEvent event,
                                   UInt16               lineCount,
                                   UInt16               pixCount);

/**
 *  VpsHal_vpdmaCreateDummyDesc
 *  \brief Function to create Dummy descriptor of 4 words in the given memory
 *
 *  \param memPtr           Pointer to the memory in which dummy
 *                          descriptor is to be created
 *  \return                 None
 */
Void VpsHal_vpdmaCreateDummyDesc(Ptr memPtr);

/**
 *  VpsHal_vpdmaIsValidSize
 *  \brief Function to check whether the size is valid or not for
 *         the given input path and for the given format
 *
 *  \param vpdmaPath        VPDMA Path
 *  \param isYuv422iFormat  Is the format YUV 422 interleaved?
 *                          descriptor is to be created
 *  \return                 None
 */
Int32 VpsHal_vpdmaIsValidSize(VpsHal_VpdmaPath       vpdmaPath,
                              Bool                   isYuv422iFormat,
                              VpsHal_VpdmaMemoryType memType,
                              UInt32                 width,
                              UInt32                 height);

/**
 *  VpsHal_vpdmaCreateConfigDesc
 *  \brief Function to create the configuration descriptor in the given memory.
 *
 *  \param memPtr           Pointer memory in which config descriptor is
 *                          to be created
 *  \param dest             Config descriptor destination
 *  \param clss             This indicates whether payload is blocks of
 *                          data or single contiguous block.
 *  \param direct           This indicates whether payload is stored in
 *                          contiguous with the descriptor or stored in some
 *                          other memory location
 *  \param payloadSize      Payload size in bytes
 *  \param payloadAddr      Pointer to payload memory for indirect
 *                          configuration
 *  \param destAddr         Destination address offset used for block type
 *                          configuration class. Not used for address set.
 *  \param dataSize         NONE
 *
 *  \return                 None
 */
Void VpsHal_vpdmaCreateConfigDesc(Ptr                           memPtr,
                                  VpsHal_VpdmaConfigDest        dest,
                                  VpsHal_VpdmaConfigPayloadType classVal,
                                  VpsHal_VpdmaConfigCmdType     direct,
                                  UInt32                        payloadSize,
                                  Ptr                           payloadAddr,
                                  Ptr                           destAddr,
                                  UInt16                        dataSize);
/**
 *  VpsHal_vpdmaGetClientRegAdd
 *  \brief This function is used to get the base address for the client
 * registers. This address needs to pass to VPDMA to create the register
 * overlay for that client register
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param chanNum          Channel number for which the base address of client
 *                          reg is address.
 *  \return                 Returns the base address of the client register.
 */
Ptr VpsHal_vpdmaGetClientRegAdd(VpsHal_Handle       handle,
                                VpsHal_VpdmaChannel chanNum);

/**
 *  VpsHal_vpdmaSetAddress
 *  \brief Function to set the buffer address and fid in the data descriptor.
 *  This function can be called from the ISR to update the buffer
 *  address and fid
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param fid              Value of FID. It must be either 0 or 1.
 *  \param bufferAddr       Buffer Address to be set in the data desc.
 *  \return                 None
 */
Void VpsHal_vpdmaSetAddress(Ptr memPtr, UInt8 fid, Ptr bufferAddr);

/**
 *  VpsHal_vpdmaGetAddress
 *  \brief Function to get address from a VPDMA descriptor in memory
 */
Ptr VpsHal_vpdmaGetAddress(Ptr memPtr);

/**
 *  VpsHal_vpdmaSetDescWriteAddr
 *  \brief Function to set the descriptor write address into
 *  data descriptor. This is the address where VPDMA prepares the
 *  data descriptor. This function is used only for the outbound
 *  data descriptor.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param wrDescAddr       Address of the memory where descriptors will
 *                          be written by VPDMA
 *  \return                 None
 */
Void VpsHal_vpdmaSetDescWriteAddr(Ptr memPtr, Ptr wrDescAddr);

/**
 *  VpsHal_vpdmaSetWriteDesc
 *  Function to set the write descriptor flag in out bound data
 *  descriptor. Setting this flag tells VPDMA to write data descriptor
 *  in the memory
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param enable           Flag to indicate whether to enable/disable
 *                          Write Descriptor
 *                          be written by VPDMA
 *  \return                 None
 */
Void VpsHal_vpdmaSetWriteDesc(Ptr memPtr, UInt8 enable);

/**
 *  VpsHal_vpdmaEnableDescSkip
 *  \brief Function to enable/disable skip desc bit.
 *
 *  \param memPtr           Pointer to memory containing in bound
 *                          descriptor
 *  \param enableSkip       Flag to indicate whether to enable/disable
 *
 *  \return                 None
 */
Void VpsHal_vpdmaEnableDescSkip(Ptr memPtr, UInt32 enableSkip);

/**
 *  VpsHal_vpdmaEnableListCompleteInterrupt
 *  \brief Enable/Disable interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *  Not implemented. HAL update reqd..
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpdmaEnableListCompleteInterrupt(VpsHal_Handle handle,
                                              UInt32        intrLine,
                                              UInt32        listNum,
                                              UInt32        enable);

/**
 *  VpsHal_vpdmaClearListCompleteInterrupt
 *  \brief Clear interrupt for list loading completion
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *  Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpdmaClearListCompleteInterrupt(VpsHal_Handle handle,
                                             UInt32        intrLine,
                                             UInt32        listNum);

/**
 *  VpsHal_vpdmaEnableListNotifyInterrupt
 *  \brief Enable/Disable interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *  Not implemented. HAL update reqd.
 *  \param listNum          List to set interrupt for.
 *  \param enable           1: Enable, 0: Disable interrupt
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpdmaEnableListNotifyInterrupt(VpsHal_Handle handle,
                                            UInt32        intrLine,
                                            UInt32        listNum,
                                            UInt32        enable);

/**
 *  VpsHal_vpdmaClearListNotifyInterrupt
 *  \brief Clear interrupt for channel completion corresponding to list
 *  specified (notify bit must be set in descriptor)
 *
 *  \param handle           Valid handle returned by VpsHal_vpdmaOpen function.
 *  \param intrLine         Interrupt line to use. #VpsHal_VpdmaIntLine TODO:
 *  Not implemented. HAL update reqd.
 *  \param listNum          List to clear interrupt for.
 *
 *  \return                   success    0
 *                            failure    error value
 */
Int32 VpsHal_vpdmaClearListNotifyInterrupt(VpsHal_Handle handle,
                                           UInt32        intrLine,
                                           UInt32        listNum);

/**
 *  VpsHal_vpdmaCalcRegOvlyMemSize
 *  \brief Function to calculate the size of memory required for creating
 *  VPDMA configuration address set for the given register offsets. It
 *  also returns the offsets of the virtual register in the register
 *  overlay from the starting location of the overlay in terms of
 *  words. This function will be used for the other HALs to calculate
 *  the size required to store configured through VPDMA and to get
 *  the virtual register offset so that they can modify virtual
 *  registers.
 *
 *  \param regOffset        List of Register Offsets
 *  \param numReg           Number of register offsets in first parameter
 *  \param virtRegOffset    Pointer to array in which virtual register
 *                          offsets will be returned. This offsets are
 *                          in terms of words.
 *  \return                 Size of memory in terms of bytes
 */
UInt32 VpsHal_vpdmaCalcRegOvlyMemSize(UInt32 *const *regOffset,
                                      UInt32         numReg,
                                      UInt32        *virtRegOffset);

/**
 *  VpsHal_vpdmaCreateRegOverlay
 *  Function is used to create complete configuration descriptor
 *  with the address set for the given registers offsets. It takes
 *  list of register offsets and pointer to memory, creates
 *  configuration descriptor and address set for the register set and
 *  returns the virtual addresses of the registers.
 *
 *  \param configRegList    List of Register Offsets
 *  \param numConfigReg     List of Register Offsets
 *  \param regOverlay       Pointer to array in which virtual register
 *                          offsets will be returned. This offsets are
 *                          in terms of words.
 *  \return                 Size of memory in terms of bytes
 */
Int32 VpsHal_vpdmaCreateRegOverlay(UInt32 *const *configRegList,
                                   UInt32         numConfigReg,
                                   Void          *regOverlay);

/**
 *  VpsHal_vpdmaSetLineStride
 *  Function to set the line stride for both in/out bound data descriptor.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param lineStride       Line stride in bytes between two lines
 *
 *  \return                 None
 */
Void VpsHal_vpdmaSetLineStride(Ptr memPtr, UInt16 lineStride);

/**
 *  VpsHal_vpdmaSetMemType
 *  Function to set the memory type for both in/out bound data descriptor.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param memType          Type of memory i.e. Tiled or Non-Tiled
 *
 *  \return                 None
 */
Void VpsHal_vpdmaSetMemType(Ptr memPtr, VpsHal_VpdmaMemoryType memType);

/**
 *  VpsHal_vpdmaSetDropData
 *  Function to set the drop data flag in out bound data descriptor.
 *  When this flag is set, VPDMA will drop the captured data without
 *  storing it the memory.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param enable           Flag to indicate whether to enable/disable
 *                          drop data be written by VPDMA
 *  \return                 None
 */
Void VpsHal_vpdmaSetDropData(Ptr memPtr, UInt8 enable);

/**
 *  VpsHal_vpdmaSetDescHeight
 *  Function to set the height in out bound data
 *  descriptor. This API is used to set the height in
 *  case of slice based operations.
 *
 *  \param memPtr           Pointer to memory containing out bound
 *                          descriptor
 *  \param enable
 *                          Pointer to Data descriptor whose height
 *                          field needs to be modified
 *
 *  \return                 None
 */
Void VpsHal_vpdmaSetDescHeight(Ptr                             memPtr,
                               const VpsHal_VpdmaInDescParams *descInfo);

/**
 *  VpsHal_vpdmaGetClient
 *  \brief Function to map the channel number to client number.
 *
 *  \param channel          #VpsHal_VpdmaChannel
 *
 *  \return                 #VpsHal_VpdmaClient
 */
VpsHal_VpdmaClient VpsHal_vpdmaGetClient(VpsHal_VpdmaChannel channel);

/**
 *  VpsHal_vpdmaSetFrameSizeReg
 *  \brief Function to set the MAX_SIZE1, MAX_SIZE2, and MAX_SIZE3 registers.
 *
 *  \param handle           Vpdma handle.
 *
 *  \param args             Pointer to instance of #Vps_VpdmaMaxSizeParams
 *                          structure.
 *
 *  \return                 None.
 */
Void VpsHal_vpdmaSetFrameSizeReg(VpsHal_Handle handle,
                                 Ptr           args);

/**
 *  VpsHal_vpdmaFvid2ToVpdma
 *  \brief Returns VPDMA data-types corresponding to input FVID2 datatypes
 *
 *  \param fvid2DT         Input FVID2 data-type
 *
 *  \return                Corresponding VPDMA data-type.
 *                         Returns VPSHAL_VPDMA_CHANDT_INVALID for invalid
 *                         input.
 *
 */
VpsHal_VpdmaChanDT VpsHal_vpdmaFvid2ToVpdma(Fvid2_DataFormat fvid2DT);

/**
 *  VpsHal_vpdmaSetRgbBackgroundColor
 *  \brief Function used to set the background color for RGB.
 *                  Bits  7:0  -  Configures Blend
 *                  Bits 15:8  -  Configures Blue
 *                  Bits 23:16 -  Configures Green
 *                  Bits 31:24 -  Configures Red
 *
 *  \param handle       VpsHal_Handle handle returned by VpsHal_vpdmaOpen function.
 *  \param value        Value used to set the background color register.
 *
 *  \return                None
 *
 */
void VpsHal_vpdmaSetRgbBackgroundColor(VpsHal_Handle handle,UInt32 value);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPSHAL_VPDMA_H_ */
