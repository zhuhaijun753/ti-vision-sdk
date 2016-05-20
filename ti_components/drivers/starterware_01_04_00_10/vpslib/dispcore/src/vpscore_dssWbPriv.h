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
 *  \file vpscore_dssWbPriv.h
 *
 *  \brief Header file for DSS Writeback core
 *  This file includes data-structures and function declarations for the
 *  the VPS writeback core interface for DSS.
 *
 */

#ifndef DSSWBLIB_PRIV_H_
#define DSSWBLIB_PRIV_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VPSCORE_DSSWB_DEF_ALIGN  ((uint32_t) 32U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct VpsCore_DssWbObj
 *  \brief DSS WB Core Handle structure. This will be instantiated for each
 *  instance of DSS WB. (Currently there is only one instance of DSS WB)
 */

typedef struct
{
    UInt32               numHandles;
    VpsCore_Handle       pathObjPool[VPSHAL_DSS_DISPC_WB_MAX_INST];
    UInt32               dispcIrqNumber;
    /**< DISPC IRQ number at CPU level INTC. */
    VpscoreDctrl_NodeNum dcNodeNum[VPSHAL_DSS_DISPC_WB_MAX_INST];
    VpsHal_Handle        wbHandle[VPSHAL_DSS_DISPC_WB_MAX_INST];
    BspOsal_IntrHandle   intrHandle;
    /**< Handle to Hardware Interrupt. */
} VpsCore_DssWbObj;

typedef struct
{
    UInt32                      handleId;
    Ptr                         drvData;
    VpsCore_DssWbObj           *parent;
    VpsHal_Handle               pipeHandle;
    /**< HAL handle for WriteBack pipe. */
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
    VpsHal_DssDispcWbPipeCfg    wbPipeCfg;
    /**< Writeback pipeline HAL structure configuration*/
    VpsHal_DssDispcAdvDmaConfig halAdvDmaCfg;
    /**< Advance dma configuration structure*/
    Bool                        isStarted;
    /**< Variable to indicated if streaming is started. */
    UInt32                      outScanFormat;
    /**< Output scan format, for valid values check #Fvid2_ScanFormat */
    UInt32                      isFieldMergeBuff;
    /**< Variable to check if out buffer should be field merged or not
     *       Valid only if outScanFormat is Interlaced. */
    UInt32                      currentFieldVal;
    /**< Variable to store current field is Top or Bottom. Used only in case of
     *   Interlaced display. */
    VpscoreDctrl_NodeNum        dcNode;
    /**< Display Controller Node number. */
    VpscoreDctrlClientHandle    dcHandle;
    /**< Display controller Handle. */
    UInt32                      regionBasedBit;
    /**< Region based bit value. */
} VpsCore_DssWbPathObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*TODO - Add description*/
Int32 VpsCore_dssWbGetProperty(VpsCore_Inst      instObj,
                               VpsCore_Property *property);

VpsCore_Handle VpsCore_dssWbOpen(VpsCore_Inst            pDssWbHandle,
                                 const VpsCore_OpenPrms *openPrms,
                                 const void             *coreOpenPrms,
                                 void                   *coreReturnPrms);

Int32 VpsCore_dssWbPathSetConfig(VpsCore_Handle pathHandle,
                                 const void    *params,
                                 void          *retPrms);

Int32 VpsCore_dssWbPathGetConfig(VpsCore_Handle pathHandle,
                                 void          *params);

Int32 VpsCore_dssWbControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           void          *appArgs,
                           void          *drvArgs);

Int32 VpsCore_dssWbIsr(VpsCore_Handle pathHandle, UInt32 chId);

Int32 VpsCore_dssWbStart(VpsCore_Handle pathHandle);

Int32 VpsCore_dssWbStop(VpsCore_Handle pathHandle);

Int32 VpsCore_dssWbClose(VpsCore_Handle pathHandle);

Int32 VpsCore_dssWbGetErrorStat(VpsCore_Handle pathHandle,
                                void          *params);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* DSSLIB_PRIV_H_ */
