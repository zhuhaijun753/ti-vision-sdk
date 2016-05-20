#include "chains_vipSingleCam_SgxDisplay_PASA_priv.h"

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraViewObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_vipSingleCam_SgxDisplay_PASAObj ucObj;

    /**< Link Id's and device IDs to use for this use-case */
    UInt32  appCtrlLinkId;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

    Chains_Ctrl *chainsCfg;

}chains_vipSingleCam_SgxDisplay_PASAAppObj;

Void chains_vipSingleCam_SgxDisplay_PASA_SetSgxDisplayLinkPrms (
                                  SgxDisplayLink_CreateParams *prms,
                                  UInt32 width, UInt32 height);

Void chains_vipSingleCam_SgxDisplay_PASA_SetAppPrms(chains_vipSingleCam_SgxDisplay_PASAObj *pUcObj,Void *appObj);

Void chains_vipSingleCam_SgxDisplay_PASA_StartApp(chains_vipSingleCam_SgxDisplay_PASAAppObj *pObj);

Void chains_vipSingleCam_SgxDisplay_PASA_StopApp(chains_vipSingleCam_SgxDisplay_PASAAppObj *pObj);
