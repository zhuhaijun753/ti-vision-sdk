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
 *  \file vpscore_dssPriv.h
 *
 *  \brief Header file for DSS display core
 *  This file includes data-structures and function declarations for the
 *  the VPS display core interface for DSS.
 *
 */

#ifndef DSSLIB_PRIV_H_
#define DSSLIB_PRIV_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#define VPSCORE_DSS_DEF_ALIGN  ((uint32_t) 32U)

/* Enable this macro to user 16ms timer interrupt as DISPC interrupt for
 * debug purpose. */
/* #define VPSCORE_DSS_USE_TIMER_ISR */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct VpsCore_DssObj
 *  \brief DSS Core Handle structure. This will be instantiated for each
 *  instance of DSS. (Currently there is only one instance of DSS)
 */

typedef struct
{
    UInt32               numHandles;
    VpsCore_Handle       pathObjPool[VPSHAL_DSS_DISPC_PIPE_MAX_INST];
    UInt32               dispcIrqNumber;
    VpscoreDctrl_NodeNum dcNodeNum[VPSHAL_DSS_DISPC_PIPE_MAX_INST];
    /**< DISPC IRQ number at CPU level INTC. */
    VpsHal_Handle        vidHandle[VPSHAL_DSS_DISPC_VID_INST_ID_MAX];
    VpsHal_Handle        ovlHandle[VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX];
#ifdef VPSCORE_DSS_USE_TIMER_ISR
    BspOsal_ClockHandle  procClkHandle;
#else
    BspOsal_IntrHandle   intrHandle;
    /**< Handle to Hardware Interrupt. */
#endif
} VpsCore_DssObj;

typedef struct
{
    UInt32                      handleId;
    Ptr                         drvData;
    VpsCore_DssObj             *parent;
    VpsHal_Handle               pipeHandle;
    /**< HAL handle for video/GFX pipe. */
    VpsCore_ReqFrameCb          reqFrmCb;
    /**< Request frame callback function. This cannot be NULL. */
    VpsCore_FrameDoneCb         frmDoneCb;
    /**< Frame complete callback function. This cannot be NULL. */
    VpsCore_Frame              *progFrame;
    /**< Pointer to Programmed Frame buffer structure
     *   this frame will be programmed in the shadowed registers. */
    VpsCore_Frame              *curFrame;
    /**< Pointer to Current Frame buffer structure.
     *   this frame is currently being displayed */
    VpsHal_DssDispcVidPipeCfg   vidPipeCfg;
    /**< Video pipeline HAL structure configuration*/
    VpsHal_DssDispcGfxPipeCfg   gfxPipeCfg;
    /**< Graphics pipeline HAL structure configuration*/
    VpsHal_DssDispcAdvDmaConfig halAdvDmaCfg;
    /**< Advance dma configuration structure*/
    Vps_DssDispcVidVC1Config    vc1Cfg;
    /**< VC1 Range Config structure. */
    UInt32                      memType;
    /**< Memory type. For valid values see #Vps_VpdmaMemoryType.
     *   Note: Tiler Memory is not supported as of now, user should set this
     *   to VPS_VPDMA_MT_NONTILEDMEM. */
    Bool                        isStarted;
    /**< Variable to indicated if streaming is started. */
    UInt32                      inScanFormat;
    /**< Input scan format, for valid values check #Fvid2_ScanFormat */
    UInt32                      isFieldMergeBuff;
    /**< Variable to check if input buffer is field merged or not
     *       Valid only if inScanFormat is Interlaced. */
    VpscoreDctrl_NodeNum        dcNode;
    /**< Display Controller Node number. */
    VpscoreDctrlClientHandle    dcHandle;
    /**< Display controller Handle. */
    UInt32                      dispHeight;
    /**< Venc display height. */
    UInt32                      dispWidth;
    /**< Venc display width. */
    UInt32                      dispStandard;
    /**< standard of display format. */
    UInt32                      dispScanFormat;
    /**< Scan format, for valid values #TODO. */
    Int32                       shiftVidPosX;
    /**<Vid position in overlay to be shifted in Number of pixels. */
} VpsCore_DssPathObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*TODO - Add description*/
Int32 VpsCore_dssGetProperty(VpsCore_Inst      instObj,
                             VpsCore_Property *property);

VpsCore_Handle VpsCore_dssOpen(VpsCore_Inst            pDssHandle,
                               const VpsCore_OpenPrms *openPrms,
                               const void             *coreOpenPrms,
                               void                   *coreReturnPrms);

Int32 VpsCore_dssPathSetConfig(VpsCore_Handle pathHandle,
                               const void    *params,
                               void          *retPrms);

Int32 VpsCore_dssPathGetConfig(VpsCore_Handle pathHandle,
                               void          *params);

Int32 VpsCore_dssControl(VpsCore_Handle handle,
                         UInt32         cmd,
                         void          *appArgs,
                         void          *drvArgs);

Int32 VpsCore_dssIsr(VpsCore_Handle pathHandle, UInt32 chId);

Int32 VpsCore_dssStart(VpsCore_Handle pathHandle);

Int32 VpsCore_dssStop(VpsCore_Handle pathHandle);

Int32 VpsCore_dssClose(VpsCore_Handle pathHandle);

Int32 VpsCore_dssProgBuffer(VpsCore_Handle pathHandle,
                            VpsCore_Frame *frm,
                            UInt32         bypassLowLatencyCheck);

Int32 VpsCore_dssGetErrorStat(VpsCore_Handle pathHandle,
                              void          *params);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* DSSLIB_PRIV_H_ */
