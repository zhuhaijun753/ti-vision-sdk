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
 *  \file vpshal_isscal.c
 *
 *  \brief This file defines all abstractions for CAL module of ISS.
 *  This abstraction will support multiple instances of PPI, CSI. Operates 2
 *  modes primarily. memory to memory mode and capture mode.
 *
 *  TODO / TBD
 *  3. Pad Control Register base address - should be received as we do for CAL
 *      and PHY. SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE
 *  4. Pad PULL UP / DOWN Control reg same as above
 *      CTRL_CORE_PAD_IO_SMA_SW_10
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>

#include <soc.h>
#include <hw/hw_iss_regs.h>
#include <hw/hw_types.h>
#include <hw/hw_iss_cal.h>
#include <hw/hw_ctrl_core_pad.h>

#include <fvid2/fvid2_dataTypes.h>
#include <vps/iss/vps_cfgcal.h>

#include <hal/vpshal.h>
#include <hal/vpshal_iss.h>
#include <hal/vpshal_isscal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CTRL_CORE_PAD_IO_SMA_SW_10         (0x00001C68U)

#define SMA_SW_CSI2_X0_UP_MASK             (0x00000001U)
#define SMA_SW_CSI2_Y0_UP_MASK             (0x00000002U)

#define SMA_SW_CSI2_X1_UP_MASK             (0x00000004U)
#define SMA_SW_CSI2_Y1_UP_MASK             (0x00000008U)

#define SMA_SW_CSI2_X2_UP_MASK             (0x00000010U)
#define SMA_SW_CSI2_Y2_UP_MASK             (0x00000020U)

#define SMA_SW_CSI2_X3_UP_MASK             (0x00000040U)
#define SMA_SW_CSI2_Y3_UP_MASK             (0x00000080U)

#define SMA_SW_CSI2_X4_UP_MASK             (0x00000100U)
#define SMA_SW_CSI2_Y4_UP_MASK             (0x00000200U)

#define SMA_SW_CSI2_X0_DW_MASK             (0x00000400U)
#define SMA_SW_CSI2_Y0_DW_MASK             (0x00000800U)

#define SMA_SW_CSI2_X1_DW_MASK             (0x00001000U)
#define SMA_SW_CSI2_Y1_DW_MASK             (0x00002000U)

#define SMA_SW_CSI2_X2_DW_MASK             (0x00004000U)
#define SMA_SW_CSI2_Y2_DW_MASK             (0x00008000U)

#define SMA_SW_CSI2_X3_DW_MASK             (0x00010000U)
#define SMA_SW_CSI2_Y3_DW_MASK             (0x00020000U)

#define SMA_SW_CSI2_X4_DW_MASK             (0x00040000U)
#define SMA_SW_CSI2_Y4_DW_MASK             (0x00080000U)

/**< Bit 2 set, used to compute register values for lanes enabled. */
#define CAL_BIT_2_SET       ((uint32_t)0x4U)

/**< If PPI is enabled before DMA writes are, there is possibility that 1st
        frame received will be written to address 0x0.
        As Write DMA address is latched with a frame start event.
        If PPI is enabled, before any buffer are primed, the write address is
        not yet updated. 0x0 being reset value of write DMA address, 1st
        frame would be written there. */
#define ENABLE_PPI_WHEN_STARTING
/* #define J6_ECO_METHOD_PHY_INIT  (TRUE) */

/**< Functional PHY clock is expected to be 96 MHz
        Period of PHY clock in nS is 10.41666
        ((1/<PHY Clock) / 1e-9) */
#define DPHY_FUNCTIONAL_CLK_PERIOD  (10.41666)

/**< There are multiple ways of initializing DPHY for reception. This macro
        enables a proven sequence. */
#define SECOND_PROVEN_INIT_SEQUENCE

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct isshalCalInstObj
 *  \brief Describes a instance of Cal configuration.
 */
typedef struct isshalCalInstObj
{
    uint32_t           instId;
    /**< Instance ID */
    uint32_t           baseAddr;
    /**< Base address of the CAL module */
    uint32_t           phyBaseAddress;
    /**< If this CAL instance has an associated PHY, this will hold a non-null
     *      value */
    uint32_t           isInited;
    /**< Flag to indicate successful initialization */
    uint32_t           openCnt;
    /**< Number of times the hal is opened. */
    isshalCalInstCfg_t instCfg;
    /**< Instance configuration */
} isshalCalInstObj_t;

/**
 *  struct isshalCalObj
 *  \brief Describes a cal object.
 */
typedef struct isshalCalObj
{
    isshalCalMode_t     mode;
    /**< Mode */
    isshalCalInstObj_t *pInstObj;
    /**< Pointer to instance specific config */
} isshalCalObj_t;

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#ifdef J6_ECO_METHOD_PHY_INIT
/**
 * \brief   Resets the instance of CAL
 *
 * \param   pInst   Valid pointer to instance object
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalResetInstance(isshalCalInstObj_t *pInst,
                                isshalCalInstCfg_t *cfg,
                                isshalCalMode_t     mode);

/**
 * \brief   Configures instance specific configurations.
 *
 * \param   pInst   Valid pointer to instance object
 * \param   cfg     Valid instance config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetInstCfg(isshalCalInstObj_t *pInst,
                             isshalCalInstCfg_t *cfg,
                             isshalCalMode_t     mode);
#else /* J6_ECO_METHOD_PHY_INIT */
/**
 * \brief   Resets the CAL instance
 *
 * \param   baseAddr Base address of the CAL instance to be reset.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalReset(uint32_t baseAddr);

/**
 * \brief   Configure instance LANE config and frame mode of operation. Note
 *              that the low level port is enabled for reception.
 *
 * \param   baseAddr Base address of the CAL.
 * \param   pCfg     Valid lane and frame mode configurations
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalCfgInstLanePpiCfg(uint32_t            baseAddr,
                                    isshalCalInstCfg_t *pCfg);

/**
 * \brief   Configure various aspects of the PHY.
 *
 * \param   baseAddr            Base address of the CAL.
 * \param   camRxCoreBaseAddr   Base address of the PHY.
 * \param   pCfg                Current DDR MHz and stop state timeouts
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalPhyEnClockAndReset(uint32_t            baseAddr,
                                     uint32_t            camRxCoreBaseAddr,
                                     isshalCalInstCfg_t *pCfg);
/**
 * \brief   Resets CAL / PHY and applies instance specific config for capture
 *              Updated DMA read specifics for other modes.
 *
 * \param   hndl    Handle returned when opened.
 * \param   cfg     Valid configuration for mode specified in open.
 * \param   mode    Mode as specified during open.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalResetApplyInstConfig(const isshalCalObj_t *pHndl,
                                       isshalCalInstCfg_t   *pCfg,
                                       isshalCalMode_t       mode);
#endif /* J6_ECO_METHOD_PHY_INIT */

/**
 * \brief   Applies supplied configurations, for all mode & all blocks.
 *
 * \param   hndl    Handle returned when opened.
 * \param   cfg     Valid configuration for mode specified in open.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetCfg(const isshalCalObj_t *hndl, const isshalCalCfg_t *cfg);

/**
 * \brief   Applies configurations required for m2m mode.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for m2m.
 * \param   mode    Indicates if in capture / m2m mode.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetCfgForMode(const isshalCalInstObj_t *pInst,
                                const isshalCalCfg_t     *cfg,
                                isshalCalMode_t           mode);

/**
 * \brief   Applies CSI2 Virtual processing configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for Virtual Channels of CSI2.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalCsi2VcCfg(const isshalCalInstObj_t   *pInst,
                            const isshalCalCsi2VcCfg_t *cfg,
                            uint32_t                    cportId);

/**
 * \brief   Applies pixel processing configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for pixel processing.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetPixProcCfg(const isshalCalInstObj_t *pInst,
                                const vpsissCalPixProc_t *cfg,
                                uint32_t                  cportId);

/**
 * \brief   Applies BYS Out port configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for BYS Out port.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetBysOutCfg(const isshalCalInstObj_t *pInst,
                               const vpsissCalBysOut_t  *cfg,
                               uint32_t                  cportId);

/**
 * \brief   Applies VPORT out configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for VPORT Out.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetVportCfg(const isshalCalInstObj_t *pInst,
                              const vpsissCalVPort_t   *cfg,
                              uint32_t                  cportId);

/**
 * \brief   Applies DMA Read configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for DMA Read.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetRdDmaCfg(const isshalCalInstObj_t  *pInst,
                              const isshalCalRdDmaCfg_t *cfg,
                              uint32_t                   cportId);

/**
 * \brief   Applies DMA Read frame size
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for frame config.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetRdDmaFrameCfg(const isshalCalInstObj_t *pInst,
                                   const Fvid2_Format       *cfg);

/**
 * \brief   Applies DMA Write configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for DMA Write.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetWrDmaCfg(const isshalCalInstObj_t  *pInst,
                              const isshalCalWrDmaCfg_t *cfg,
                              uint32_t                   cportId);

/**
 * \brief   Sets the DMA mode, expected to be used to enable/disable DMA writes
 *              For all the DMA write contexts that have been configured, the
 *              supplied mode is applied
 *
 * \param   pInstObj   Pointer to instance object.
 * \param   pDmaCfg    Pointer to DMA config
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t calSetWrDmaMode(const isshalCalInstObj_t  *pInstObj,
                               const isshalCalDmaVcCfg_t *pDmaCfg);

static int32_t CalCfgInstWrDma(
    uint32_t baseAddr, const isshalCalInstCfg_t *pCfg);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static isshalCalInstObj_t gCalInstObj[VPS_ISS_CAL_MAX_INST] =
{
    {
        0x0,
        0x0,
        (uint32_t)FALSE,
        0x0,
        0x0
    },
    {
        0x0,
        0x0,
        (uint32_t)FALSE,
        0x0,
        0x0
    }
};
/**< Instance specific config */

static isshalCalObj_t     gCalObj \
    [VPS_ISS_CAL_MAX_INST][VPS_HAL_ISS_CAL_OPEN_NUM];
/**< Handle / open specific config */

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gCalInstDefaults' visibility is too wide.
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used in many functions, but not accessed by any
 * other file.
 */
static isshalCalInstCfg_t gCalInstDefaults;

/**< Default instance config */
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t VpsHal_isscalInit(uint32_t numInst,
                          const isshalCalInstParams_t *initPrms, Ptr arg)
{
    uint32_t i, j;
    uint32_t isInited = (uint32_t)FALSE;

    GT_assert(VpsHalTrace, (VPS_ISS_CAL_MAX_INST >= numInst));
    GT_assert(VpsHalTrace, (NULL != initPrms));
    GT_assert(VpsHalTrace, (0x0 != initPrms->baseAddress));

    for(i = 0; i < VPS_ISS_CAL_MAX_INST; i++)
    {
        if((uint32_t)FALSE != gCalInstObj[i].isInited)
        {
            /* Has been initialized earlier. Exit now */
            isInited = (uint32_t)TRUE;
            /* This is MISRA C violation, for having multiple returns.
             *  This should not cause any issues. Please ignore */
        }
    }

    if((uint32_t)FALSE == isInited)
    {
        /* Do not require to initialize gCalObj, we rely primarily
         * on gCalInstObj
         *  The association between gCalInstObj & gCalObj is done
         * further down */
        /* . Set defaults */
        /* Indicates the urgency of real time traffic using the
         * number of contexts
         *  currently in use by the write DMA.
         *  00: SAFE (n<MFLAGL)
         *  01: VULNERABLE (MFLAGL<=n<MFLAGH)
         *  11: ENDANGERED (MFLAGH<=n)
         *  Assuming 4 write DMA contexts, n = 4 */

        gCalInstDefaults.mFlagH = 10U;
        gCalInstDefaults.mFlagL = 6U;
        /* Assuming CAL receives via a sensor */
        gCalInstDefaults.rdDmaStall   = (uint32_t)TRUE;
        gCalInstDefaults.pwrScpClk    = (uint32_t)FALSE;
        gCalInstDefaults.dmaBurstSize = CAL_CTRL_BURSTSIZE_BURST128;
        gCalInstDefaults.tagCnt       = 15U;
        gCalInstDefaults.postedWrites = (uint32_t)FALSE;
        gCalInstDefaults.csi2PhyClock = 400U;

        for(i = 0; i < VPS_ISS_CAL_MAX_CMPLXIO_INST; i++)
        {
            /* TBD TODO Sujith
             *  On silicon this would require an update.
             *  Clock on 1, data1 on 2, data2 on 3, data3 on 4 & data4 on 5. */
            gCalInstDefaults.numCmplxIoInst =
                VPS_ISS_CAL_MAX_CMPLXIO_INST;
            gCalInstDefaults.cmplxIoCfg[i].enable = (uint32_t)TRUE;
            gCalInstDefaults.cmplxIoCfg[i].clockLane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].clockLane.position = 5U;
            gCalInstDefaults.cmplxIoCfg[i].data1Lane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].data1Lane.position = 1U;
            gCalInstDefaults.cmplxIoCfg[i].data2Lane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].data2Lane.position = 2U;
            gCalInstDefaults.cmplxIoCfg[i].data3Lane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].data3Lane.position = 3U;
            gCalInstDefaults.cmplxIoCfg[i].data4Lane.pol      = (uint32_t)FALSE;
            gCalInstDefaults.cmplxIoCfg[i].data4Lane.position = 4U;
            gCalInstDefaults.cmplxIoCfg[i].pwrAuto            = (uint32_t)FALSE;
            /* Always
             * powered
             * up
             */
        }
        for(i = 0; i < VPS_ISS_CAL_MAX_PPI_INST; i++)
        {
            gCalInstDefaults.numPpiInst         = VPS_ISS_CAL_MAX_PPI_INST;
            gCalInstDefaults.ppiCfg[i].enable   = (uint32_t)FALSE;
            gCalInstDefaults.ppiCfg[i].instance = 0x0U;
            gCalInstDefaults.ppiCfg[i].frame    = (uint32_t)TRUE;
            gCalInstDefaults.ppiCfg[i].ecc      = (uint32_t)FALSE;

            /* Careful while updating these, are used to determine
                the stop state
                detection.
                Please ignore force_rx_mode_0I01 - will be removed */
            gCalInstDefaults.ppiCfg[i].csi2Cfg.force_rx_mode_0I01     = 1U;
            gCalInstDefaults.ppiCfg[i].csi2Cfg.stop_state_x16_I01     = 1U;
            gCalInstDefaults.ppiCfg[i].csi2Cfg.stop_state_x4_I01      = 0U;
            gCalInstDefaults.ppiCfg[i].csi2Cfg.stop_state_counter_I01 = 0x197U;
        }

        for(i = 0; ((i < numInst) && (i < VPS_ISS_CAL_MAX_INST)); i++)
        {
            gCalInstObj[i].instId = i;
            GT_assert(VpsHalTrace, (0x0 != initPrms->baseAddress));
            gCalInstObj[i].baseAddr       = initPrms->baseAddress;
            gCalInstObj[i].phyBaseAddress = initPrms->phyBaseAddress;
            gCalInstObj[i].openCnt        = 0U;
            gCalInstObj[i].isInited       = (uint32_t)TRUE;
            BspUtils_memcpy((Ptr) & gCalInstObj[i].instCfg,
                            (const void *) &gCalInstDefaults,
                            sizeof(isshalCalInstCfg_t));
            for(j = 0; j < VPS_HAL_ISS_CAL_OPEN_NUM; j++)
            {
                gCalObj[i][j].pInstObj = &gCalInstObj[i];
            }

            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * Pointer Arithmatic
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER: Pointer is incremented to get the next
             * object's location.
             * This function is called by init function, which passes
             * cal number of instances. The size of this number of instances
             * is never more than VPS_ISS_CAL_MAX_INST.
             */
            initPrms++;
        }
    }

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

int32_t VpsHal_isscalDeInit(Ptr arg)
{
    uint32_t i;

    for(i = 0; i < VPS_ISS_CAL_MAX_INST; i++)
    {
        GT_assert(VpsHalTrace, (0x0 == gCalInstObj[i].openCnt));
        BspUtils_memset(&gCalInstObj[i], 0U, sizeof(isshalCalInstObj_t));
    }
    /* Do not require any updates to gCalObj, the close will take care */
    return FVID2_SOK;
}

/**************************Function Separator**********************************/

VpsHal_Handle VpsHal_isscalOpen(const isshalCalOpenParams_t *openPrms,
                                Ptr                          arg)
{
    isshalCalObj_t *hndl = NULL;
    int32_t         rtnVal;
    uint32_t        openCnt;

    rtnVal = FVID2_SOK;
    if(NULL == openPrms)
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (VPS_ISS_CAL_MAX_INST <= openPrms->instId))
    {
        rtnVal = FVID2_EBADARGS;
    }
    if((FVID2_SOK == rtnVal) &&
       ((VPS_HAL_ISS_CAL_MODE_MIN >= openPrms->mode) ||
        (VPS_HAL_ISS_CAL_MODE_MAX <= openPrms->mode)))
    {
        rtnVal = FVID2_EBADARGS;
    }
    if(FVID2_SOK == rtnVal)
    {
        openCnt = gCalObj[openPrms->instId][0].pInstObj->openCnt;
        if(VPS_HAL_ISS_CAL_OPEN_NUM <= openCnt)
        {
            rtnVal = FVID2_EALLOC;
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        hndl = &gCalObj[openPrms->instId][openCnt];
        if(NULL == hndl->pInstObj)
        {
            /* Not initialized/ */
            rtnVal = FVID2_EBADARGS;
        }
    }
    if(FVID2_SOK == rtnVal)
    {
        hndl->pInstObj->openCnt++;
#ifdef J6_ECO_METHOD_PHY_INIT
        /* Do assume anything, let the upper layer perform reset and apply
         *  required instance config */

        /* For the very first open,
         *  . reset the IP
         *  . program the instance defaults (all, capture, m2m, complex io
         */
        if(0x0 == openCnt)
        {
            rtnVal = CalResetInstance(hndl->pInstObj, &hndl->pInstObj->instCfg,
                                      openPrms->mode);
        }
        if(FVID2_SOK == rtnVal)
        {
            /* TODO - Do this only once when opening,
             * However, the DMA read operations should be done multiple time? */
            /* Program the instance defaults */
            rtnVal = CalSetInstCfg(hndl->pInstObj, &hndl->pInstObj->instCfg,
                                   openPrms->mode);
        }
#else
        rtnVal = CalResetApplyInstConfig(hndl, &hndl->pInstObj->instCfg,
                                         openPrms->mode);

#endif  /* J6_ECO_METHOD_PHY_INIT */
        if(FVID2_SOK == rtnVal)
        {
            hndl->mode = openPrms->mode;
        }
    }

    return ((VpsHal_Handle) hndl);
}

/**************************Function Separator**********************************/

int32_t VpsHal_isscalClose(VpsHal_Handle handle, Ptr arg)
{
    uint32_t          instance, i;
    int32_t           rtnVal = FVID2_SOK;
    volatile uint32_t reg, timeOut;
    isshalCalObj_t   *hndl = (isshalCalObj_t *) handle;

    if(NULL == hndl)
    {
        rtnVal = FVID2_EBADARGS;
    }
    else
    {
        GT_assert(VpsHalTrace, (NULL != hndl->pInstObj));
    }

    if(FVID2_SOK == rtnVal)
    {
        if(0x0 == hndl->pInstObj->openCnt)
        {
            rtnVal = FVID2_EBADARGS;
        }
    }

    if(FVID2_SOK == rtnVal)
    {
        if(VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode)
        {
            rtnVal = FVID2_SOK;
            for(i = 0; ((FVID2_SOK == rtnVal) &&
                        (i < hndl->pInstObj->instCfg.numPpiInst)); i++)
            {
                if((uint32_t)FALSE != hndl->pInstObj->instCfg.ppiCfg[i].enable)
                {
                    instance = hndl->pInstObj->instCfg.ppiCfg[i].instance;
                    if(VPS_ISS_CAL_MAX_PPI_INST < instance)
                    {
                        rtnVal = FVID2_EBADARGS;
                        break;
                    }
#ifndef ENABLE_PPI_WHEN_STARTING
                    if(1U == hndl->pInstObj->openCnt)
                    {
                        /* Last instance of open, disable PPI */
                        reg = HW_RD_REG32(hndl->pInstObj->baseAddr +
                                          CAL_CSI2_PPI_CTRL(instance));
                        reg &= ~CAL_CSI2_PPI_CTRL_IF_EN_MASK;
                        HW_WR_REG32(hndl->pInstObj->baseAddr +
                                    CAL_CSI2_PPI_CTRL(instance), reg);
                        rtnVal = FVID2_SOK;
                    }
#endif              /* ENABLE_PPI_WHEN_STARTING */
                }
            }
            for(i = 0; i < VPS_ISS_CAL_MAX_CMPLXIO_INST; i++)
            {
                if(1U == hndl->pInstObj->openCnt)
                {
                    reg = HW_RD_REG32(hndl->pInstObj->baseAddr +
                                      CAL_CSI2_COMPLEXIO_CFG(i));
                    reg &= ~(CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK);
                    HW_WR_REG32(hndl->pInstObj->baseAddr +
                                CAL_CSI2_COMPLEXIO_CFG(i), reg);

                    /* Wait for power down completion */
                    timeOut = 0xFFFFU;
#ifdef PLATFORM_EVM_SI
                    while(timeOut)
                    {
                        reg = HW_RD_REG32(hndl->pInstObj->baseAddr +
                                          CAL_CSI2_COMPLEXIO_CFG(i));
                        if(0U == (reg & CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK))
                        {
                            break;
                        }
                        timeOut--;
                    }
#endif              /* PLATFORM_EVM_SI */
                    if(0U == timeOut)
                    {
                        /* Could not power down the PHY... */
                        rtnVal = FVID2_ETIMEOUT;
                        GT_assert(VpsHalTrace, ((uint32_t)FALSE));
                        break;
                    }
                }
            }
        }
        else if(VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode)
        {
            rtnVal = FVID2_SOK;
            if(1U == hndl->pInstObj->openCnt)
            {
                /* For the very last clos ensure that there are no pending
                    DMA reads */
                reg = HW_RD_REG32(hndl->pInstObj->baseAddr + CAL_RD_DMA_CTRL);
                if(CAL_RD_DMA_CTRL_GO_MASK == (reg & CAL_RD_DMA_CTRL_GO_MASK))
                {
                    rtnVal = FVID2_EDEVICE_INUSE;
                }
            }
        }
        else
        {
            GT_assert(VpsHalTrace,
                      (VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL != hndl->mode));
            rtnVal = FVID2_SOK;
        }
        hndl->pInstObj->openCnt--;

        hndl->mode = VPS_HAL_ISS_CAL_MODE_MIN;
    }

    return rtnVal;
}

/**************************Function Separator**********************************/

int32_t VpsHal_isscalControl(VpsHal_Handle handle,
                             UInt32        cmd,
                             Ptr           cmdArgs,
                             Ptr           arg)
{
    volatile uint32_t      reg;
    uint32_t               idx, baseAddr, offset;
    isshalCalInstObj_t    *pInstObj;
    isshalCalBufferAddr_t *bufPtrs;
    isshalCalObj_t        *hndl = (isshalCalObj_t *) handle;

    int32_t rtnVal = FVID2_SOK;

    if(NULL == hndl)
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (NULL != hndl->pInstObj))
    {
        pInstObj = hndl->pInstObj;
    }
    else
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (NULL == pInstObj->baseAddr))
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (0x0 == pInstObj->openCnt))
    {
        rtnVal = FVID2_EFAIL;
    }

    if(FVID2_SOK == rtnVal)
    {
        switch(cmd)
        {
            case VPS_HAL_ISS_IOCTL_CAL_UPDATE_BUFFERS:
                if(NULL != cmdArgs)
                {
                    bufPtrs = (isshalCalBufferAddr_t *) cmdArgs;

                    rtnVal = FVID2_SOK;
                    for(idx = 0U; idx < bufPtrs->numBuff; idx++)
                    {
                        if(NULL == bufPtrs->buffAddr[idx])
                        {
                            rtnVal = FVID2_EBADARGS;
                        }
                        if((VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode) ||
                           (VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode))
                        {
                            if(VPS_ISS_CAL_MAX_STREAMS <=
                               bufPtrs->wrDmaCtx[idx])
                            {
                                rtnVal = FVID2_EBADARGS;
                            }
                        }

                        if(FVID2_SOK != rtnVal)
                        {
                            break;
                        }

                        baseAddr = pInstObj->baseAddr;
                        if((0x0 == bufPtrs->cPortId[idx]) &&
                           (VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode))
                        {
                            reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_PIX_ADDR);
                            reg &= ~CAL_RD_DMA_PIX_ADDR_MASK;
                            reg |= CAL_RD_DMA_PIX_ADDR_MASK &
                                   bufPtrs->buffAddr[idx];
                            HW_WR_REG32(baseAddr + CAL_RD_DMA_PIX_ADDR, reg);

                            reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_PIX_OFST);
                            reg &= ~CAL_RD_DMA_PIX_OFST_MASK;
                            reg |= CAL_RD_DMA_PIX_OFST_MASK &
                                   bufPtrs->pitch[idx];
                            HW_WR_REG32(baseAddr + CAL_RD_DMA_PIX_OFST, reg);
                        }

                        if((VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode) ||
                           (VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode))
                        {
                            reg = HW_RD_REG32(baseAddr +
                                              CAL_WR_DMA_ADRR(bufPtrs->wrDmaCtx
                                                              [idx]));
                            reg &= ~CAL_WR_DMA_ADRR_ADDR_MASK;
                            reg |= CAL_WR_DMA_ADRR_ADDR_MASK &
                                   bufPtrs->buffAddr[idx];
                            HW_WR_REG32(baseAddr +
                                        CAL_WR_DMA_ADRR(
                                            bufPtrs->wrDmaCtx[idx]), reg);
                        }
                    }
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            case VPS_HAL_ISS_IOCTL_CAL_RD_FMT_UPDATE:
                rtnVal = CalSetRdDmaFrameCfg(pInstObj, (Fvid2_Format *)cmdArgs);
                break;

            case VPS_HAL_ISS_IOCTL_START:
                if((VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode) &&
                   (NULL != cmdArgs))
                {
                    rtnVal = calSetWrDmaMode(pInstObj,
                                             (isshalCalDmaVcCfg_t *) cmdArgs);

#ifdef ENABLE_PPI_WHEN_STARTING
                    for(idx = 0; idx < pInstObj->instCfg.numPpiInst; idx++)
                    {
                        if((uint32_t)FALSE !=
                           pInstObj->instCfg.ppiCfg[idx].enable)
                        {
                            baseAddr = pInstObj->baseAddr;
                            offset   = pInstObj->instCfg.ppiCfg[idx].instance;
                            reg      =
                                HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset));
                            reg |= CAL_CSI2_PPI_CTRL_IF_EN_MASK;
                            HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset),
                                        reg);
                        }
                    }
#endif          /* ENABLE_PPI_WHEN_STARTING */
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            case VPS_HAL_ISS_IOCTL_STOP:
                if((VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode) &&
                   (NULL != cmdArgs))
                {
                    rtnVal = calSetWrDmaMode(pInstObj,
                                             (isshalCalDmaVcCfg_t *) cmdArgs);
#ifdef ENABLE_PPI_WHEN_STARTING
                    /* TODO - Check if all write DMAs have been stopped.
                                Otherwise multiple handle will not work.
                                Right way would be
                                . Do it in the core
                                . If NOT the last wr context
                                . Setup to receive into 10 X 10 buffer
                                . Updated size, offset
                                . On disable of last context
                                . Setup to receive into 10 x 10 buffer,
                                . Disable PPI
                                . */

                    for(idx = 0; idx < pInstObj->instCfg.numPpiInst; idx++)
                    {
                        if((uint32_t)FALSE !=
                           pInstObj->instCfg.ppiCfg[idx].enable)
                        {
                            baseAddr = pInstObj->baseAddr;
                            offset   = pInstObj->instCfg.ppiCfg[idx].instance;
                            reg      =
                                HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset));
                            reg &= ~CAL_CSI2_PPI_CTRL_IF_EN_MASK;
                            HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset),
                                        reg);
                        }
                    }
#endif          /* ENABLE_PPI_WHEN_STARTING */
                }
                else if(VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode)
                {
                    /* Nothing to stop as of now - check TODO */
                    rtnVal = FVID2_SOK;
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            case VPS_HAL_ISS_IOCTL_CAL_SETCFG:
                if(NULL != cmdArgs)
                {
                    rtnVal = CalSetCfg(hndl, (isshalCalCfg_t *) cmdArgs);
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            case VPS_HAL_ISS_IOCTL_CAL_GET_INSTANCECFG:
                if(NULL != cmdArgs)
                {
                    BspUtils_memcpy((Ptr) cmdArgs,
                                    (const void *) &hndl->pInstObj->instCfg,
                                    sizeof(isshalCalInstCfg_t));
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            case VPS_HAL_ISS_IOCTL_CAL_SET_INSTANCECFG:
                if(NULL != cmdArgs)
                {
#ifdef J6_ECO_METHOD_PHY_INIT
                    rtnVal = CalSetInstCfg(hndl->pInstObj,
                                           (isshalCalInstCfg_t *) cmdArgs,
                                           hndl->mode);
#else           /* J6_ECO_METHOD_PHY_INIT */
                    rtnVal = CalResetApplyInstConfig(
                        hndl,
                        (isshalCalInstCfg_t *)
                        cmdArgs,
                        hndl->mode);
#endif          /* J6_ECO_METHOD_PHY_INIT */

                    if(FVID2_SOK == rtnVal)
                    {
                        BspUtils_memcpy((Ptr) & hndl->pInstObj->instCfg,
                                        (const void *) cmdArgs,
                                        sizeof(isshalCalInstCfg_t));
                    }
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;
            case VPS_HAL_ISS_IOCTL_CAL_SET_VPORT_CFG:
                if(NULL != cmdArgs)
                {
                    rtnVal = CalSetVportCfg(
                        hndl->pInstObj,
                        (vpsissCalVPort_t *) cmdArgs,
                        *(uint32_t *) arg);
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;
            case VPS_HAL_ISS_IOCTL_CAL_SET_BYSOUT_CFG:
                if(NULL != cmdArgs)
                {
                    rtnVal = CalSetBysOutCfg(
                        hndl->pInstObj,
                        (vpsissCalBysOut_t *) cmdArgs,
                        *(uint32_t *) arg);
                }
                else
                {
                    rtnVal = FVID2_EBADARGS;
                }
                break;

            default:
                rtnVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (rtnVal);
}

/**************************Function Separator**********************************/
#ifdef J6_ECO_METHOD_PHY_INIT
static int32_t CalResetInstance(isshalCalInstObj_t *pInst,
                                isshalCalInstCfg_t *cfg,
                                isshalCalMode_t     mode)
{
    int32_t           idx, rtnVal = FVID2_SOK;
    volatile uint32_t reg, baseAddr, timeOut;
#ifdef PLATFORM_EVM_SI
    uint32_t          thsTerm, thsSettle, camRxCoreBaseAddr; /* essentially PHY
                                                             **/
#endif /* PLATFORM_EVM */

    GT_assert(VpsHalTrace, (NULL != pInst));
    baseAddr = pInst->baseAddr;

    timeOut = 0xFFFF;
    reg     = HW_RD_REG32(baseAddr + CAL_HL_SYSCONFIG);

    reg &= ~CAL_HL_SYSCONFIG_IDLEMODE_MASK;
    reg |= CAL_HL_SYSCONFIG_IDLEMODE_MASK & (CAL_HL_SYSCONFIG_IDLEMODE_NO <<
                                             CAL_HL_SYSCONFIG_IDLEMODE_SHIFT);

    reg |= CAL_HL_SYSCONFIG_SOFTRESET_MASK;
    HW_WR_REG32(baseAddr + CAL_HL_SYSCONFIG, reg);

    while((timeOut) && (CAL_HL_SYSCONFIG_SOFTRESET_MASK ==
                        (reg & CAL_HL_SYSCONFIG_SOFTRESET_MASK)))
    {
        timeOut--;
        reg = HW_RD_REG32(baseAddr + CAL_HL_SYSCONFIG);
    }
    if((0x0 == timeOut) || (CAL_HL_SYSCONFIG_SOFTRESET_MASK ==
                            (reg & CAL_HL_SYSCONFIG_SOFTRESET_MASK)))
    {
        /* Reset did not complete. We would require an  PRCM reset now! */
        rtnVal = FVID2_ETIMEOUT;
    }

    /* PHY is not required when operating in M2M mode (CAL memory read) */
    if((VPS_HAL_ISS_CAL_MODE_CAPTURE == mode) ||
       (VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL == mode))
    {
        /* Reset PHY
         *  On Silicon, remember that writes will take 8 cycles or, ensure to
         *  insert delays and check the status after power up! */
        for(idx = 0; idx < VPS_ISS_CAL_MAX_CMPLXIO_INST;
            idx++)
        {
            reg = 0;

            /* Enable clock lane */
            reg |= CTRL_CORE_PAD_CONTROL_CAMERA_RX_CSIPORTA_MODE_MASK;

            /* Enable all data lane */
            reg |= CTRL_CORE_PAD_CONTROL_CAMERA_RX_CSIPORTA_LANEENABLE_MASK;
            reg |= CTRL_CORE_PAD_CONTROL_CAMERA_RX_CSIPORTA_LANEENABLE_MASK;

            /* Enable DPHY Mode */
            reg &= ~CTRL_CORE_PAD_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_MASK;
            reg |= (CTRL_CORE_PAD_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_DPHY <<
                    CTRL_CORE_PAD_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_SHIFT);

            /* Enable CTRL CLK */
            reg &= ~CTRL_CORE_PAD_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_MASK;
            reg |= (CTRL_CORE_PAD_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_ENABLE
                    <<
                    CTRL_CORE_PAD_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_SHIFT);

            HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                        CTRL_CORE_PAD_CONTROL_CAMERA_RX, reg);

            /* CAL_CSI2_TIMING */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_TIMING(idx));
            reg &= ~(CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK |
                     CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK |
                     CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK |
                     CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK);
            reg |= CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK &
                   (cfg->ppiCfg[idx].csi2Cfg.force_rx_mode_0I01 <<
                    CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_SHIFT);
            reg |= CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK &
                   (cfg->ppiCfg[idx].csi2Cfg.stop_state_x16_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_X16_IO1_SHIFT);
            reg |= CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK &
                   (cfg->ppiCfg[idx].csi2Cfg.stop_state_x4_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_X4_IO1_SHIFT);
            reg |= CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK &
                   (cfg->ppiCfg[idx].csi2Cfg.stop_state_counter_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_TIMING(idx), reg);

            /* CAL_CSI2_COMPLEXIO_CFG - release PHY_RESET */
            reg  = 0U;
            reg |= CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_MASK;
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);
            /* Dummy read to allow SCP to complete */
            reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));

            timeOut = 0xFFFF;
#ifdef PLATFORM_EVM_SI
            /* Wait for the reset to complete */
            while(timeOut)
            {
                reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
                if(reg == (reg & CAL_CSI2_COMPLEXIO_CFG_RESET_DONE_MASK))
                {
                    break;
                }
                timeOut--;
            }
            if(0U == timeOut)
            {
                rtnVal = FVID2_ETIMEOUT;
                break;
            }
            camRxCoreBaseAddr = pInst->phyBaseAddress;
            if(NULL != camRxCoreBaseAddr)
            {
                reg  = HW_RD_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG0);
                reg &= ~(CAL_CSI2_PHY_REG0_THS_TERM_MASK |
                         CAL_CSI2_PHY_REG0_THS_SETTLE_MASK);

                /* Setup REG0, REG1 and REG2 */
                thsTerm = (((((12500U * cfg->csi2PhyClock) +
                              (1000000U / 2U)) / 1000000U) - 1U) & 0xFF);
                thsSettle = (((((90000 * cfg->csi2PhyClock) +
                                (1000000 / 2)) / 1000000) + 3) & 0xFF);
                reg |= thsTerm << CAL_CSI2_PHY_REG0_THS_TERM_SHIFT;

                reg |= thsSettle << CAL_CSI2_PHY_REG0_THS_SETTLE_SHIFT;

                HW_WR_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG0, reg);
            }
#endif      /* PLATFORM_EVM_SI*/

            /* CAL_CSI2_COMPLEXIO_CFG - send PWR_ON CMD */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            reg |= CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK &
                   (CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_STATE_ON <<
                    CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);

            /* CAL_CSI2_COMPLEXIO_CFG - wait for PWR_ON STATUS */
            timeOut = 0xFFFF;
#ifdef PLATFORM_EVM_SI
            while(timeOut)
            {
                reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
                reg = (reg & CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_MASK);
                reg = (reg >> CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_SHIFT);
                if(CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_STATE_ON == reg)
                {
                    break;
                }
                timeOut--;
            }
#endif      /* PLATFORM_EVM_SI*/
            if(0U == timeOut)
            {
                rtnVal = FVID2_ETIMEOUT;
                break;
            }
        }
    }
    return (rtnVal);
}

/**************************Function Separator**********************************/

static int32_t CalSetInstCfg(isshalCalInstObj_t *pInst,
                             isshalCalInstCfg_t *cfg,
                             isshalCalMode_t     mode)
{
    uint32_t               baseAddr, offset, idx;
    volatile uint32_t      reg;
    vpsissCalCmplxIoCfg_t *cmplxIoCfg;
    int32_t rtnVal = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));
    baseAddr = pInst->baseAddr;

    /* Set up
     *  . complex IO TBD TODO
     *  . PPI config
     *  . Other M2M configs
     */
    if((VPS_HAL_ISS_CAL_MODE_CAPTURE == mode) ||
       (VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL == mode))
    {
        GT_assert(VpsHalTrace, (VPS_ISS_CAL_MAX_PPI_INST >= cfg->numPpiInst));
        GT_assert(VpsHalTrace,
                  (VPS_ISS_CAL_MAX_CMPLXIO_INST >= cfg->numCmplxIoInst));

        /* Complex IO config */
        offset = 0x0;
        for(idx = 0; idx < cfg->numCmplxIoInst; idx++)
        {
            cmplxIoCfg = &cfg->cmplxIoCfg[idx];

            /* Setup the polarity of lanes */
            if((uint32_t)TRUE == cmplxIoCfg->enable)
            {
                reg  = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
                reg &= ~(CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK |
                         CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_MASK |
                         CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_MASK |
                         CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_MASK |
                         CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_MASK);
                reg &= ~(CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK |
                         CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_MASK |
                         CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_MASK |
                         CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_MASK |
                         CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_MASK);
                reg |= CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK &
                       cmplxIoCfg->clockLane.position;
                reg |= CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_MASK &
                       (cmplxIoCfg->data1Lane.position <<
                        CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_SHIFT);
                reg |= CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_MASK &
                       (cmplxIoCfg->data2Lane.position <<
                        CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_SHIFT);
                reg |= CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_MASK &
                       (cmplxIoCfg->data3Lane.position <<
                        CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_SHIFT);
                reg |= CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_MASK &
                       (cmplxIoCfg->data4Lane.position <<
                        CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_SHIFT);

                reg |= CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK &
                       (cmplxIoCfg->clockLane.pol <<
                        CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_SHIFT);
                reg |= CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_MASK &
                       (cmplxIoCfg->data1Lane.pol <<
                        CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_SHIFT);
                reg |= CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_MASK &
                       (cmplxIoCfg->data2Lane.pol <<
                        CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_SHIFT);
                reg |= CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_MASK &
                       (cmplxIoCfg->data3Lane.pol <<
                        CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_SHIFT);
                reg |= CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_MASK &
                       (cmplxIoCfg->data4Lane.pol <<
                        CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_SHIFT);

                HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);

                /* Dummy read to wait for SCP write to complete */
                reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            }
        }
        /* . PPI Config */
        offset = 0x0;
        for(idx = 0; idx < cfg->numPpiInst; idx++)
        {
            if((uint32_t)FALSE !=
               cfg->ppiCfg[idx].enable)
            {
                offset = cfg->ppiCfg[idx].instance;
                if(VPS_ISS_CAL_MAX_PPI_INST < offset)
                {
                    rtnVal = FVID2_EBADARGS;
                    break;
                }

                reg  = HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset));
                reg &= ~(CAL_CSI2_PPI_CTRL_IF_EN_MASK |
                         CAL_CSI2_PPI_CTRL_FRAME_MASK |
                         CAL_CSI2_PPI_CTRL_ECC_EN_MASK);

                if((uint32_t)TRUE == cfg->ppiCfg[idx].ecc)
                {
                    reg |= CAL_CSI2_PPI_CTRL_ECC_EN_MASK;
                }
                if((uint32_t)TRUE == cfg->ppiCfg[idx].frame)
                {
                    reg |= CAL_CSI2_PPI_CTRL_FRAME_MASK;
                }
                HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset), reg);

#ifndef ENABLE_PPI_WHEN_STARTING
                reg  = HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(idx));
                reg |= CAL_CSI2_PPI_CTRL_IF_EN_MASK;
                HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(idx), reg);
#endif          /* ENABLE_PPI_WHEN_STARTING */
            }
        }
    }

    /* .Other M2M configs */
    reg  = HW_RD_REG32(baseAddr + CAL_CTRL);
    reg &= ~(CAL_CTRL_POSTED_WRITES_MASK | CAL_CTRL_TAGCNT_MASK |
             CAL_CTRL_BURSTSIZE_MASK | CAL_CTRL_MFLAGL_MASK |
             CAL_CTRL_PWRSCPCLK_MASK | CAL_CTRL_RD_DMA_STALL_MASK |
             CAL_CTRL_MFLAGH_MASK);

    reg |= CAL_CTRL_MFLAGH_MASK & (cfg->mFlagH << CAL_CTRL_MFLAGH_SHIFT);

    if((uint32_t)TRUE == cfg->rdDmaStall)
    {
        reg |= CAL_CTRL_RD_DMA_STALL_MASK;
    }

    if((uint32_t)TRUE == cfg->pwrScpClk)
    {
        reg |= CAL_CTRL_PWRSCPCLK_MASK;
    }

    reg |= CAL_CTRL_MFLAGL_MASK & (cfg->mFlagL << CAL_CTRL_MFLAGL_SHIFT);

    reg |= CAL_CTRL_BURSTSIZE_MASK &
           (cfg->dmaBurstSize << CAL_CTRL_BURSTSIZE_SHIFT);

    reg |= CAL_CTRL_TAGCNT_MASK & (cfg->tagCnt << CAL_CTRL_TAGCNT_SHIFT);

    if((uint32_t)TRUE == cfg->postedWrites)
    {
        reg |= CAL_CTRL_POSTED_WRITES_MASK;
    }

    HW_WR_REG32(baseAddr + CAL_CTRL, reg);

    return rtnVal;
}

#else /* J6_ECO_METHOD_PHY_INIT */

/**************************Function Separator**********************************/

static int32_t CalReset(uint32_t baseAddr)
{
    int32_t           rtnVal = FVID2_SOK;
    volatile uint32_t reg, timeOut;

    GT_assert(VpsHalTrace, (0U != baseAddr));
    timeOut = 0xFFFFU;
    reg     = HW_RD_REG32(baseAddr + CAL_HL_SYSCONFIG);

    reg &= ~CAL_HL_SYSCONFIG_IDLEMODE_MASK;
    reg |= CAL_HL_SYSCONFIG_IDLEMODE_MASK & (CAL_HL_SYSCONFIG_IDLEMODE_NO <<
                                             CAL_HL_SYSCONFIG_IDLEMODE_SHIFT);

    reg |= CAL_HL_SYSCONFIG_SOFTRESET_MASK;
    HW_WR_REG32(baseAddr + CAL_HL_SYSCONFIG, reg);

    while(timeOut)
    {
        reg = HW_RD_REG32(baseAddr + CAL_HL_SYSCONFIG);
        if(CAL_HL_SYSCONFIG_SOFTRESET_MASK !=
           (reg & CAL_HL_SYSCONFIG_SOFTRESET_MASK))
        {
            break;
        }

        timeOut--;
    }

    /* If reset is not done, timeOut will be zero, so only one
       condition check required here
       If reset is done, this condition is anyway false. */
    if((reg & CAL_HL_SYSCONFIG_SOFTRESET_MASK) ==
       CAL_HL_SYSCONFIG_SOFTRESET_MASK)
    {
        /* Reset did not complete. We would require an  PRCM reset now! */
        rtnVal = FVID2_ETIMEOUT;
    }
    return rtnVal;
}

/**************************Function Separator**********************************/

static int32_t CalCfgInstWrDma(
    uint32_t baseAddr, const isshalCalInstCfg_t *pCfg)
{
    volatile uint32_t reg;
    reg  = HW_RD_REG32(baseAddr + CAL_CTRL);
    reg &= ~(CAL_CTRL_POSTED_WRITES_MASK | CAL_CTRL_TAGCNT_MASK |
             CAL_CTRL_BURSTSIZE_MASK | CAL_CTRL_MFLAGL_MASK |
             CAL_CTRL_PWRSCPCLK_MASK | CAL_CTRL_RD_DMA_STALL_MASK |
             CAL_CTRL_MFLAGH_MASK);

    reg |= CAL_CTRL_MFLAGH_MASK & (pCfg->mFlagH << CAL_CTRL_MFLAGH_SHIFT);

    if((uint32_t)TRUE == pCfg->rdDmaStall)
    {
        reg |= CAL_CTRL_RD_DMA_STALL_MASK;
    }

    if((uint32_t)TRUE == pCfg->pwrScpClk)
    {
        reg |= CAL_CTRL_PWRSCPCLK_MASK;
    }

    reg |= CAL_CTRL_MFLAGL_MASK & (pCfg->mFlagL << CAL_CTRL_MFLAGL_SHIFT);

    reg |= CAL_CTRL_BURSTSIZE_MASK &
           (pCfg->dmaBurstSize << CAL_CTRL_BURSTSIZE_SHIFT);

    reg |= CAL_CTRL_TAGCNT_MASK & (pCfg->tagCnt << CAL_CTRL_TAGCNT_SHIFT);

    if((uint32_t)TRUE == pCfg->postedWrites)
    {
        reg |= CAL_CTRL_POSTED_WRITES_MASK;
    }

    HW_WR_REG32(baseAddr + CAL_CTRL, reg);

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalCfgInstLanePpiCfg(uint32_t baseAddr, isshalCalInstCfg_t *pCfg)
{
    uint32_t               offset, idx;
    volatile uint32_t      reg;
    vpsissCalCmplxIoCfg_t *pCmplxIoCfg;
    int32_t rtnVal = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != pCfg));
    GT_assert(VpsHalTrace, (VPS_ISS_CAL_MAX_PPI_INST >= pCfg->numPpiInst));
    GT_assert(VpsHalTrace,
              (VPS_ISS_CAL_MAX_CMPLXIO_INST >= pCfg->numCmplxIoInst));

    /* Lane Config */
    offset = 0x0;
    for(idx = 0; idx < pCfg->numCmplxIoInst; idx++)
    {
        pCmplxIoCfg = &pCfg->cmplxIoCfg[idx];

        /* Setup the polarity of lanes */
        if((uint32_t)TRUE == pCmplxIoCfg->enable)
        {
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            reg &= ~(CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_MASK);
            reg &= ~(CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_MASK |
                     CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_MASK);
            reg |= CAL_CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK &
                   pCmplxIoCfg->clockLane.position;
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_MASK &
                   (pCmplxIoCfg->data1Lane.position <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA1_POSITION_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_MASK &
                   (pCmplxIoCfg->data2Lane.position <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA2_POSITION_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_MASK &
                   (pCmplxIoCfg->data3Lane.position <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA3_POSITION_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_MASK &
                   (pCmplxIoCfg->data4Lane.position <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA4_POSITION_SHIFT);

            reg |= CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_MASK &
                   (pCmplxIoCfg->clockLane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_CLOCK_POL_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_MASK &
                   (pCmplxIoCfg->data1Lane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA1_POL_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_MASK &
                   (pCmplxIoCfg->data2Lane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA2_POL_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_MASK &
                   (pCmplxIoCfg->data3Lane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA3_POL_SHIFT);
            reg |= CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_MASK &
                   (pCmplxIoCfg->data4Lane.pol <<
                    CAL_CSI2_COMPLEXIO_CFG_DATA4_POL_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);

            /* Dummy read to wait for SCP write to complete */
            reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
        }
    }
    /* PPI Config */
    offset = 0x0;
    for(idx = 0; idx < pCfg->numPpiInst; idx++)
    {
        if((uint32_t)FALSE != pCfg->ppiCfg[idx].enable)
        {
            offset = pCfg->ppiCfg[idx].instance;
            if(VPS_ISS_CAL_MAX_PPI_INST < offset)
            {
                rtnVal = FVID2_EBADARGS;
                break;
            }

            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset));
            reg &= ~(CAL_CSI2_PPI_CTRL_IF_EN_MASK |
                     CAL_CSI2_PPI_CTRL_FRAME_MASK |
                     CAL_CSI2_PPI_CTRL_ECC_EN_MASK);

            if((uint32_t)TRUE == pCfg->ppiCfg[idx].ecc)
            {
                reg |= CAL_CSI2_PPI_CTRL_ECC_EN_MASK;
            }
            if((uint32_t)TRUE == pCfg->ppiCfg[idx].frame)
            {
                reg |= CAL_CSI2_PPI_CTRL_FRAME_MASK;
            }
            HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset), reg);

#ifndef ENABLE_PPI_WHEN_STARTING
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset));
            reg |= CAL_CSI2_PPI_CTRL_IF_EN_MASK;
            HW_WR_REG32(baseAddr + CAL_CSI2_PPI_CTRL(offset), reg);
#endif      /* ENABLE_PPI_WHEN_STARTING */
        }
    }
    return (rtnVal);
}

/**************************Function Separator**********************************/
static int32_t CalPhyEnClockAndReset(uint32_t            baseAddr,
                                     uint32_t            camRxCoreBaseAddr,
                                     isshalCalInstCfg_t *pCfg)
{
    int32_t                rtnVal;
    uint32_t               idx;
    volatile uint32_t      reg, timeOut, enaLanes;
    vpsissCalCmplxIoCfg_t *pCmplxIoCfg;

    GT_assert(VpsHalTrace, (0U != baseAddr));
    GT_assert(VpsHalTrace, (0U != camRxCoreBaseAddr));
    GT_assert(VpsHalTrace, (NULL != pCfg));

    rtnVal = FVID2_SOK;
    /* Steps
     *  1. Configure D-PHY mode -?
     *  2. Reset complex IO - Wait for completion of reset
     *          Note if the external sensor is not sending byte clock, the
     *          reset will timeout
     *  3 Reset PHY
     *      A. Program THS_TERM, THS_SETTLE, etc... Timings parameters in terms
     *              of DDR clock periods
     *      B. Set up the stop state transition timeouts
     *      C. Force FORCERXMODE
     *      D. Enable pull down using pad control
     *      E. Power up PHY
     *      F. Wait for power up completion
     *      G. Wait for all enabled lane to reach stop state
     *      H. Disable pull down using pad control
     */
    for(idx = 0U; idx < pCfg->numCmplxIoInst; idx++)
    {
        reg = 0;

        reg = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                          CTRL_CORE_CONTROL_CAMERA_RX);
        reg &= ~(CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_MODE_MASK |
                 CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_LANEENABLE_MASK |
                 CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_MASK |
                 CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_MASK);

        /* 1. Configure D PHY mode */
        /* Enable clock lane */
        reg |= CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_MODE_MASK;

        /* Enable all data lane
        reg |= CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_LANEENABLE_MASK; */

        enaLanes    = 0x0;
        pCmplxIoCfg = &pCfg->cmplxIoCfg[idx];
        if((uint32_t)TRUE == pCmplxIoCfg->enable)
        {
            if(0x0U != pCmplxIoCfg->clockLane.position)
            {
                enaLanes |= CAL_BIT_2_SET << pCmplxIoCfg->clockLane.position;
            }
            if(0x0U != pCmplxIoCfg->data1Lane.position)
            {
                enaLanes |= CAL_BIT_2_SET << pCmplxIoCfg->data1Lane.position;
            }
            if(0x0U != pCmplxIoCfg->data2Lane.position)
            {
                enaLanes |= CAL_BIT_2_SET << pCmplxIoCfg->data2Lane.position;
            }
            if(0x0U != pCmplxIoCfg->data3Lane.position)
            {
                enaLanes |= CAL_BIT_2_SET << pCmplxIoCfg->data3Lane.position;
            }
            if(0x0U != pCmplxIoCfg->data4Lane.position)
            {
                enaLanes |= CAL_BIT_2_SET << pCmplxIoCfg->data4Lane.position;
            }
            reg |= enaLanes;
        }

        /* Enable DPHY Mode */
        reg |= CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_MASK &
               (CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_DPHY <<
                CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_SHIFT);

        /* Enable CTRL CLK */
        reg |= CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_MASK &
               (CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_ENABLE <<
                CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_SHIFT);

        HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                    CTRL_CORE_CONTROL_CAMERA_RX, reg);

#ifdef SECOND_PROVEN_INIT_SEQUENCE
        /*
            . Reset complex IO - Do not wait for the reset completion.
            . Configure stop states
            . Force RX mode
            . Pull Down all lanes
            . Power up PHY
            . Check for power up status
            . Configure Reg 0 - CSI2 lane clocks
            . Wait for stop stop state - not required - commented out.
            . Pull up all lanes
            */
        if((FVID2_SOK == rtnVal) && (0U != camRxCoreBaseAddr))
        {
            uint32_t thsTerm, thsSettle, tclkTerm, tclkSettle;
            Float32  ddrClkPeriod, temp;

            /* 2. Reset complex IO - Do not wait for reset completion */
            reg  = reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            reg |= CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_MASK;
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);
            /* Dummy read to allow SCP to complete */
            reg     = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            timeOut = 0xFFFFFU;

            /* A. Setup the timings parameters in terms of DDR &
                    PHY functional clock */
            reg  = HW_RD_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG0);
            reg &= ~(CAL_CSI2_PHY_REG0_THS_TERM_MASK |
                     CAL_CSI2_PHY_REG0_THS_SETTLE_MASK);

            /* Effective time for enabling of termination = synchronizer delay
                + timer delay + LPRX delay + combinational routing delay
                THS_TERM = Floor (20/DDR Clock)- 2 */

            /* Get DDR clock period in nS */
            ddrClkPeriod = (Float32)(pCfg->csi2PhyClock * (Float32)1000000U);
            ddrClkPeriod = (Float32)((Float32)1U / ddrClkPeriod);
            ddrClkPeriod = (Float32)(ddrClkPeriod * (Float32)1000000000U);
            GT_assert(VpsHalTrace, ((uint32_t)ddrClkPeriod > 0U));
            temp    = ((Float32)20U / ddrClkPeriod);
            thsTerm = (uint32_t)temp;
            if(thsTerm >= 2U)
            {
                thsTerm -= 2U;
            }
            if(800U == pCfg->csi2PhyClock)
            {
                thsTerm = 0x9U;
            }
            /* Effective Ths-settle seen on line
                (starting to look for sync pattern) THS_SETTLE =
                synchronizer delay + timer delay + LPRX delay + combinational
                routing delay - pipeline delay in HS data path.
                THS_SETTLE = floor(176.3 nS/9.26 nS)-1
                Effective delay = (2 clk)+(THS_SETTLE clks)+(15 nS)-1clk
                Effective delay = (THS_SETTLE+1)clks+15nS (max)
                Maximum delay is 191.3
                191.3 = (THS_SETTLE+1)clks+15nS (max)
                THS_SETTLE = floor(176.3 nS/<Functional PHY Clock in nS>) - 1
                */
            temp = ((Float32)176.3 /
                    (Float32)DPHY_FUNCTIONAL_CLK_PERIOD);
            thsSettle = (uint32_t)temp;
            if(thsSettle >= 1U)
            {
                thsSettle -= 1U;
            }
            if(800U == pCfg->csi2PhyClock)
            {
                thsSettle = 75U;
            }
            reg |= thsTerm << CAL_CSI2_PHY_REG0_THS_TERM_SHIFT;

            reg |= thsSettle << CAL_CSI2_PHY_REG0_THS_SETTLE_SHIFT;

            HW_WR_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG0, reg);

            if(800U != pCfg->csi2PhyClock)
            {
                reg  = HW_RD_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG1);
                reg &= ~(CAL_CSI2_PHY_REG1_TCLK_TERM_MASK |
                         CAL_CSI2_PHY_REG1_TCLK_SETTLE_MASK);
                /* Requirement from D-PHY spec= (Dn Voltage < 450 mV) - 38 ns
                    Effective time for enabling of termination (TCLK_TERM) =
                        synchronizer delay + timer delay + LPRX delay +
                            combinational routing delay
                    TCLK_TERM =
                        floor((38 nS-15)/<Functional PHY Clock in nS>))- 2 nS
                        Functional PHY clock = 96 MHz
                        Period of PHY clock in nS is 10.41666
                            ((1/<PHY Clock) / 1e-9)
                */
                temp = ((Float32)23U /
                        (Float32)DPHY_FUNCTIONAL_CLK_PERIOD);
                tclkTerm = (uint32_t)temp;
                if(tclkTerm >= 2U)
                {
                    tclkTerm -= 2U;
                }

                /* Derived requirement from D-PHY spec = 100 ns to 300ns.
                    Effective Ths-settle = synchronizer delay + timer delay +
                        LPRX delay + combinational routing delay
                    Considering little less than maximum (285nS)
                    Should be X >> minimum & X < maximum. any value should be ok.

                    TCLK_SETTLE = floor(285/<Functional PHY Clock in nS>) - 2
                */
                temp = ((Float32)285U /
                        (Float32)DPHY_FUNCTIONAL_CLK_PERIOD);
                tclkSettle = (uint32_t)temp;
                if(tclkSettle >= 2U)
                {
                    tclkSettle -= 2U;
                }
                reg |= CAL_CSI2_PHY_REG1_TCLK_TERM_MASK &
                       (tclkTerm << CAL_CSI2_PHY_REG1_TCLK_TERM_SHIFT);

                reg |= CAL_CSI2_PHY_REG1_TCLK_SETTLE_MASK &
                       (tclkSettle << CAL_CSI2_PHY_REG1_TCLK_SETTLE_SHIFT);

                HW_WR_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG1, reg);
            }

            /* B. Set up the stop state transition timeouts */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_TIMING(idx));
            reg &= ~(CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK |
                     CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK |
                     CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK |
                     CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK);
            reg |= CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK &
                   (pCfg->ppiCfg[idx].csi2Cfg.stop_state_x16_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_X16_IO1_SHIFT);
            reg |= CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK &
                   (pCfg->ppiCfg[idx].csi2Cfg.stop_state_x4_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_X4_IO1_SHIFT);
            reg |= CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK &
                   (pCfg->ppiCfg[idx].csi2Cfg.stop_state_counter_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_TIMING(idx), reg);

            /* C. Force FORCERXMODE */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_TIMING(idx));
            reg |= CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK;
            HW_WR_REG32(baseAddr + CAL_CSI2_TIMING(idx), reg);

            /* D. Enable pull down on all lanes used */
            reg = HW_RD_REG32(
                SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10);
            /* These are active low */
            /* Assert PULL DOWN */
            reg &= ~(SMA_SW_CSI2_X0_DW_MASK | SMA_SW_CSI2_Y0_DW_MASK |
                     SMA_SW_CSI2_X1_DW_MASK | SMA_SW_CSI2_Y1_DW_MASK |
                     SMA_SW_CSI2_X2_DW_MASK | SMA_SW_CSI2_Y2_DW_MASK |
                     SMA_SW_CSI2_X3_DW_MASK | SMA_SW_CSI2_Y3_DW_MASK |
                     SMA_SW_CSI2_X4_DW_MASK | SMA_SW_CSI2_Y4_DW_MASK);

            /* De Assert PULL UP */
            reg |= (SMA_SW_CSI2_X0_UP_MASK | SMA_SW_CSI2_Y0_UP_MASK |
                    SMA_SW_CSI2_X1_UP_MASK | SMA_SW_CSI2_Y1_UP_MASK |
                    SMA_SW_CSI2_X2_UP_MASK | SMA_SW_CSI2_Y2_UP_MASK |
                    SMA_SW_CSI2_X3_UP_MASK | SMA_SW_CSI2_Y3_UP_MASK |
                    SMA_SW_CSI2_X4_UP_MASK | SMA_SW_CSI2_Y4_UP_MASK);
            HW_WR_REG32(SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10,
                        reg);

            /* E. Power up the PHY using the complex IO */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            reg |= CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK &
                   (CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_STATE_ON <<
                    CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);

            /* F. Wait for power up completion */
            timeOut = 0xFFFFFFU;
            while(timeOut)
            {
                reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
                reg = (reg & CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_MASK);
                reg = (reg >> CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_SHIFT);
                if(CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_STATE_ON == reg)
                {
                    break;
                }
                timeOut--;
            }
            if(0U == timeOut)
            {
                /* Could not power up the PHY... */
                rtnVal = FVID2_ETIMEOUT;
                GT_assert(VpsHalTrace, ((uint32_t)FALSE));
                break;
            }

            /* These are active low */
            /* De Assert PULL DOWN */
            reg = HW_RD_REG32(
                SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10);
            reg |= (SMA_SW_CSI2_X0_DW_MASK | SMA_SW_CSI2_Y0_DW_MASK |
                    SMA_SW_CSI2_X1_DW_MASK | SMA_SW_CSI2_Y1_DW_MASK |
                    SMA_SW_CSI2_X2_DW_MASK | SMA_SW_CSI2_Y2_DW_MASK |
                    SMA_SW_CSI2_X3_DW_MASK | SMA_SW_CSI2_Y3_DW_MASK |
                    SMA_SW_CSI2_X4_DW_MASK | SMA_SW_CSI2_Y4_DW_MASK);

            /* Assert PULL UP */
            reg &= ~(SMA_SW_CSI2_X0_UP_MASK | SMA_SW_CSI2_Y0_UP_MASK |
                     SMA_SW_CSI2_X1_UP_MASK | SMA_SW_CSI2_Y1_UP_MASK |
                     SMA_SW_CSI2_X2_UP_MASK | SMA_SW_CSI2_Y2_UP_MASK |
                     SMA_SW_CSI2_X3_UP_MASK | SMA_SW_CSI2_Y3_UP_MASK |
                     SMA_SW_CSI2_X4_UP_MASK | SMA_SW_CSI2_Y4_UP_MASK);
            HW_WR_REG32(SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10,
                        reg);
        }

#else

        /* 3. Reset PHY */
        if((FVID2_SOK == rtnVal) && (NULL != camRxCoreBaseAddr))
        {
#if NOT_YET /* This seems to broken - a value 0, works, others do not */
            uint32_t thsTerm, thsSettle;

            /* A. Setup the timings parameters in terms of DDR clock */
            reg  = HW_RD_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG0);
            reg &= ~(CAL_CSI2_PHY_REG0_THS_TERM_MASK |
                     CAL_CSI2_PHY_REG0_THS_SETTLE_MASK);

            thsTerm = (((((12500U * pCfg->csi2PhyClock) +
                          (1000000U / 2U)) / 1000000U) - 1U) & 0xFF);
            thsSettle = (((((90000 * pCfg->csi2PhyClock) +
                            (1000000 / 2)) / 1000000) + 3) & 0xFF);
            reg |= thsTerm << CAL_CSI2_PHY_REG0_THS_TERM_SHIFT;

            reg |= thsSettle << CAL_CSI2_PHY_REG0_THS_SETTLE_SHIFT;

            HW_WR_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG0, reg);
#endif      /* NOT_YET */

            /* B. Set up the stop state transition timeouts */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_TIMING(idx));
            reg &= ~(CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK |
                     CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK |
                     CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK |
                     CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK);
            reg |= CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK &
                   (pCfg->ppiCfg[idx].csi2Cfg.stop_state_x16_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_X16_IO1_SHIFT);
            reg |= CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK &
                   (pCfg->ppiCfg[idx].csi2Cfg.stop_state_x4_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_X4_IO1_SHIFT);
            reg |= CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK &
                   (pCfg->ppiCfg[idx].csi2Cfg.stop_state_counter_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_TIMING(idx), reg);

            /* C. Force FORCERXMODE */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_TIMING(idx));
            reg |= CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK;
            HW_WR_REG32(baseAddr + CAL_CSI2_TIMING(idx), reg);

            /* 2. Reset complex IO - Do not wait for reset completion */
            reg  = reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            reg |= CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_MASK;
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);
            /* Dummy read to allow SCP to complete */
            reg     = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            timeOut = 0xFFFFF;

            /* D. Enable pull down on all lanes used */
            reg = HW_RD_REG32(
                SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10);
            /* These are active low */
            /* Assert PULL DOWN */
            reg &= ~(SMA_SW_CSI2_X0_DW_MASK | SMA_SW_CSI2_Y0_DW_MASK |
                     SMA_SW_CSI2_X1_DW_MASK | SMA_SW_CSI2_Y1_DW_MASK |
                     SMA_SW_CSI2_X2_DW_MASK | SMA_SW_CSI2_Y2_DW_MASK |
                     SMA_SW_CSI2_X3_DW_MASK | SMA_SW_CSI2_Y3_DW_MASK);

            /* De Assert PULL UP */
            reg |= (SMA_SW_CSI2_X0_UP_MASK | SMA_SW_CSI2_Y0_UP_MASK |
                    SMA_SW_CSI2_X1_UP_MASK | SMA_SW_CSI2_Y1_UP_MASK |
                    SMA_SW_CSI2_X2_UP_MASK | SMA_SW_CSI2_Y2_UP_MASK |
                    SMA_SW_CSI2_X3_UP_MASK | SMA_SW_CSI2_Y3_UP_MASK);
            HW_WR_REG32(SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10,
                        reg);

            /* E. Power up the PHY using the complex IO */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            reg |= CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK &
                   (CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_STATE_ON <<
                    CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);

            /* F. Wait for power up completion */
            timeOut = 0xFFFFFF;
#ifdef PLATFORM_EVM_SI
            while(timeOut)
            {
                reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
                reg = (reg & CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_MASK);
                reg = (reg >> CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_SHIFT);
                if(CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_STATE_ON == reg)
                {
                    break;
                }
                timeOut--;
            }
#endif      /* PLATFORM_EVM_SI */
            if(0 == timeOut)
            {
                /* Could not power up the PHY... */
                rtnVal = FVID2_ETIMEOUT;
                GT_assert(VpsHalTrace, ((uint32_t)FALSE));
                break;
            }

            /* H. Enable pull up on all lanes used */
            /* These are active low */
            /* De Assert PULL DOWN */
            reg = HW_RD_REG32(
                SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10);
            reg |= (SMA_SW_CSI2_X0_DW_MASK | SMA_SW_CSI2_Y0_DW_MASK |
                    SMA_SW_CSI2_X1_DW_MASK | SMA_SW_CSI2_Y1_DW_MASK |
                    SMA_SW_CSI2_X2_DW_MASK | SMA_SW_CSI2_Y2_DW_MASK |
                    SMA_SW_CSI2_X3_DW_MASK | SMA_SW_CSI2_Y3_DW_MASK);

            /* Assert PULL UP */
            reg &= ~(SMA_SW_CSI2_X0_UP_MASK | SMA_SW_CSI2_Y0_UP_MASK |
                     SMA_SW_CSI2_X1_UP_MASK | SMA_SW_CSI2_Y1_UP_MASK |
                     SMA_SW_CSI2_X2_UP_MASK | SMA_SW_CSI2_Y2_UP_MASK |
                     SMA_SW_CSI2_X3_UP_MASK | SMA_SW_CSI2_Y3_UP_MASK);
            HW_WR_REG32(SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10,
                        reg);
        }
#endif
    }

    return rtnVal;
}

/**************************Function Separator**********************************/

static int32_t CalResetApplyInstConfig(const isshalCalObj_t *pHndl,
                                       isshalCalInstCfg_t   *pCfg,
                                       isshalCalMode_t       mode)
{
    int32_t             rtnVal = FVID2_SOK;
    isshalCalInstObj_t *pInst  = NULL;
    volatile uint32_t   reg, baseAddr, timeOut;

    GT_assert(VpsHalTrace, (NULL != pHndl));
    GT_assert(VpsHalTrace, (NULL != pCfg));
    GT_assert(VpsHalTrace, (NULL != pHndl->pInstObj));

    pInst = pHndl->pInstObj;
    GT_assert(VpsHalTrace, (NULL != pInst->baseAddr));
    baseAddr = pInst->baseAddr;

    /* In Case of M2M mode,
     *      . Reset CAL
     *      . Apply M2M specifics
     * In Case of capture via CSI2 / LVDS (CPI)
     *      . Reset CAL
     *      . Configure generic CAL / DMA write config
     *      . Configure lane and PPI
     *      . Enable Clock to PHY and Reset the same
     */
    /* . Reset CAL */
    rtnVal = CalReset(baseAddr);
    /* . Apply M2M config */
    if((FVID2_SOK == rtnVal) && (VPS_HAL_ISS_CAL_MODE_M2M == mode))
    {
        reg  = HW_RD_REG32(baseAddr + CAL_CTRL);
        reg &= ~(CAL_CTRL_RD_DMA_STALL_MASK | CAL_CTRL_PWRSCPCLK_MASK |
                 CAL_CTRL_TAGCNT_MASK);

        if((uint32_t)TRUE == pCfg->rdDmaStall)
        {
            reg |= CAL_CTRL_RD_DMA_STALL_MASK;
        }
        if((uint32_t)TRUE == pCfg->pwrScpClk)
        {
            reg |= CAL_CTRL_PWRSCPCLK_MASK;
        }

        reg |= CAL_CTRL_TAGCNT_MASK & (pCfg->tagCnt << CAL_CTRL_TAGCNT_SHIFT);

        HW_WR_REG32(baseAddr + CAL_CTRL, reg);
    }
    else if(VPS_HAL_ISS_CAL_MODE_CAPTURE == mode)
    {
        GT_assert(VpsHalTrace, (NULL != pInst->phyBaseAddress));
        /* Important to configure RD DMA stall config, as m2m mode will not be
         *  worried about this, but write will definitely be */
        rtnVal = CalCfgInstWrDma(baseAddr, pCfg);

        if(FVID2_SOK == rtnVal)
        {
            rtnVal = CalCfgInstLanePpiCfg(baseAddr, pCfg);
        }

        if(FVID2_SOK == rtnVal)
        {
            rtnVal = CalPhyEnClockAndReset(baseAddr, pInst->phyBaseAddress,
                                           pCfg);
        }
    }
    else if(VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL == mode)
    {
        /* TBD */
        rtnVal = FVID2_EBADARGS;
    }
    else
    {
        rtnVal = FVID2_EBADARGS;
    }

    return (rtnVal);
}

#endif /* J6_ECO_METHOD_PHY_INIT */

/**************************Function Separator**********************************/

static int32_t CalSetCfg(const isshalCalObj_t *hndl, const isshalCalCfg_t *cfg)
{
    /*
     *  .Configure Capture
     *  .Configure M2M
     *  .Configure Complex IO TODO TBD
     */
    int32_t rtnVal = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != hndl));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (NULL != hndl->pInstObj));

    if(0x0 == hndl->pInstObj->openCnt)
    {
        rtnVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == rtnVal)
    {
        if(VPS_HAL_ISS_CAL_MODE_CAPTURE == hndl->mode)
        {
            rtnVal = CalSetCfgForMode(hndl->pInstObj, cfg, hndl->mode);
        }
        else if(VPS_HAL_ISS_CAL_MODE_M2M == hndl->mode)
        {
            rtnVal = CalSetCfgForMode(hndl->pInstObj, cfg, hndl->mode);
        }
        else if(VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL == hndl->mode)
        {
            GT_assert(VpsHalTrace, ((uint32_t)FALSE));
            /* TODO TBD implement complex IO config apply */
        }
        else
        {
            /* Wrong mode, but why? */
            rtnVal = FVID2_EBADARGS;
        }
    }

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalSetCfgForMode(const isshalCalInstObj_t *pInst,
                                const isshalCalCfg_t     *cfg,
                                isshalCalMode_t           mode)
{
    int32_t              rtnVal = FVID2_SOK;
    uint32_t             baseAddr, cId, idx;
    volatile uint32_t    reg;
    isshalCalDmaVcCfg_t *pDmaCfg = (isshalCalDmaVcCfg_t *) cfg->pDmaVcCfg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));
    GT_assert(VpsHalTrace, (NULL != pDmaCfg));

    baseAddr = pInst->baseAddr;

    /* Ensure there are no pending reads */
    reg = HW_RD_REG32(baseAddr + CAL_RD_DMA_CTRL);
    if(((reg & CAL_RD_DMA_CTRL_GO_MASK) == CAL_RD_DMA_CTRL_GO_MASK) &&
       (VPS_HAL_ISS_CAL_MODE_M2M == mode))
    {
        rtnVal = FVID2_EAGAIN;
    }

    for(idx = 0; ((FVID2_SOK == rtnVal) && (idx < cfg->numCPortId)); idx++)
    {
        cId = cfg->cportId[idx];
        GT_assert(VpsHalTrace, (VPS_ISS_CAL_MAX_STREAMS > cId));

        if(((uint32_t)TRUE == pDmaCfg->isCsi2VcCfgValid[idx]) &&
           (VPS_HAL_ISS_CAL_MODE_CAPTURE == mode))
        {
            rtnVal = CalCsi2VcCfg(pInst, &pDmaCfg->csi2VcCfg[idx], cId);
        }
        if((uint32_t)TRUE == cfg->isPixProcCfgValid[idx])
        {
            rtnVal = CalSetPixProcCfg(pInst, &cfg->pixProcCfg[idx], cId);
        }
        if((uint32_t)TRUE == pDmaCfg->isWrDmaCfgValid[idx])
        {
            /* CFG WR DMA */
            rtnVal = CalSetWrDmaCfg(pInst, &pDmaCfg->wrDmaCfg[idx], cId);
        }
        if((uint32_t)TRUE == cfg->isBysOutCfgValid[idx])
        {
            /* CFG BYS Out */
            rtnVal = CalSetBysOutCfg(pInst, &cfg->bysOutCfg[idx], cId);
        }
        if((uint32_t)TRUE == cfg->isBysInCfgValid[idx])
        {
            /* CFG BYS In */
            if((uint32_t)TRUE == cfg->bysInEnable[idx])
            {
                reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL2);
                reg &= ~CAL_BYS_CTRL2_CPORTIN_MASK;
                reg |= CAL_BYS_CTRL2_CPORTIN_MASK & cId;
                HW_WR_REG32(baseAddr + CAL_BYS_CTRL2, reg);

                reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL1);
                reg |= CAL_BYS_CTRL1_BYSINEN_MASK;
                HW_WR_REG32(baseAddr + CAL_BYS_CTRL1, reg);
            }
            else
            {
                reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL1);
                reg &= ~CAL_BYS_CTRL1_BYSINEN_MASK;
                HW_WR_REG32(baseAddr + CAL_BYS_CTRL1, reg);
            }
        }
        if((uint32_t)TRUE == cfg->isVportCfgValid[idx])
        {
            /* CFG VP in */
            rtnVal = CalSetVportCfg(pInst, &cfg->vportCfg[idx], cId);
        }
        if((uint32_t)TRUE == pDmaCfg->isRdDmaCfgValid[idx])
        {
            /* CFG Read DMA */
            rtnVal = CalSetRdDmaCfg(pInst, &pDmaCfg->rdDmaCfg[idx], cId);
        }
    }

    return rtnVal;
}

/**************************Function Separator**********************************/

static int32_t CalCsi2VcCfg(const isshalCalInstObj_t   *pInst,
                            const isshalCalCsi2VcCfg_t *cfg,
                            uint32_t                    cportId)
{
    int32_t           rtnVal = FVID2_SOK;
    uint32_t          baseAddr, instance, context;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    instance = cfg->instance;
    context  = cfg->contextToBeUsed;
    GT_assert(VpsHalTrace, (VPS_ISS_CAL_MAX_STREAMS > context));
    GT_assert(VpsHalTrace, ((0x0U == instance) || (0x1U == instance)));

    reg = HW_RD_REG32(baseAddr + CAL_CSI2_CTX0(instance) + context * 4U);

    reg &= ~(CAL_CSI2_CTX0_DT_MASK | CAL_CSI2_CTX0_VC_MASK |
             CAL_CSI2_CTX0_CPORT_MASK | CAL_CSI2_CTX0_ATT_MASK |
             CAL_CSI2_CTX0_PACK_MODE_MASK | CAL_CSI2_CTX0_LINES_MASK);

    reg |= CAL_CSI2_CTX0_LINES_MASK & (cfg->lines << CAL_CSI2_CTX0_LINES_SHIFT);

    /* TODO Remove the hard-coding, get appropriate macros */
    if((cfg->dt < 0x17) && (cfg->dt != 0x1))
    {
        /* When receiving non-pixel data would be packed between FS and FE.
         *  no notion of LS & LE.
         * else
         *  Pixel typically line boundaries is specified. Data is packed between
         *      LS & LE.
         */
        reg |= CAL_CSI2_CTX0_PACK_MODE_MASK;
    }

    reg |= CAL_CSI2_CTX0_ATT_MASK & (cfg->att << CAL_CSI2_CTX0_ATT_SHIFT);
    reg |= CAL_CSI2_CTX0_CPORT_MASK & (cportId << CAL_CSI2_CTX0_CPORT_SHIFT);
    reg |= CAL_CSI2_CTX0_VC_MASK & (cfg->virtualChanNum <<
                                    CAL_CSI2_CTX0_VC_SHIFT);
    reg |= CAL_CSI2_CTX0_DT_MASK & (cfg->dt << CAL_CSI2_CTX0_DT_SHIFT);

    HW_WR_REG32(baseAddr + CAL_CSI2_CTX0(instance) + context * 4U, reg);
    return (rtnVal);
}

/**************************Function Separator**********************************/

static int32_t CalSetPixProcCfg(const isshalCalInstObj_t *pInst,
                                const vpsissCalPixProc_t *cfg, uint32_t cportId)
{
    int32_t           rtnVal = FVID2_SOK;
    uint32_t          baseAddr, context;
    uint32_t          extract;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    context  = cfg->contextToBeUsed;
    extract  = cfg->extract;
    extract--;

    if(context >= VPS_ISS_CAL_MAX_PIX_PROC_CTX)
    {
        rtnVal = FVID2_EINVALID_PARAMS;
    }
    else
    {
        reg  = HW_RD_REG32(baseAddr + CAL_PIX_PROC(context));
        reg &= ~CAL_PIX_PROC_EN_MASK;
        HW_WR_REG32(baseAddr + CAL_PIX_PROC(context), reg);

        reg  = HW_RD_REG32(baseAddr + CAL_PIX_PROC(context));
        reg &= ~(CAL_PIX_PROC_EXTRACT_MASK | CAL_PIX_PROC_DPCMD_MASK |
                 CAL_PIX_PROC_DPCME_MASK | CAL_PIX_PROC_PACK_MASK |
                 CAL_PIX_PROC_CPORT_MASK);

        GT_assert(VpsHalTrace, (VPS_ISS_CAL_PIX_EXRCT_MIN != cfg->extract));
        GT_assert(VpsHalTrace, (VPS_ISS_CAL_PIX_EXRCT_MAX >= cfg->extract));
        reg |= CAL_PIX_PROC_EXTRACT_MASK &
               ((extract) << CAL_PIX_PROC_EXTRACT_SHIFT);

        reg |= CAL_PIX_PROC_DPCMD_MASK &
               (cfg->decCodec << CAL_PIX_PROC_DPCMD_SHIFT);

        reg |= CAL_PIX_PROC_DPCME_MASK &
               (cfg->encCodec << CAL_PIX_PROC_DPCME_SHIFT);

        reg |= CAL_PIX_PROC_PACK_MASK & (cfg->pack << CAL_PIX_PROC_PACK_SHIFT);
        reg |= CAL_PIX_PROC_CPORT_MASK & (cportId << CAL_PIX_PROC_CPORT_SHIFT);

        HW_WR_REG32(baseAddr + CAL_PIX_PROC(context), reg);

        reg = HW_RD_REG32(baseAddr + CAL_RD_DMA_CTRL);
        if((uint32_t)TRUE == cfg->enableDpcmInitContext)
        {
            reg |= CAL_RD_DMA_CTRL_INIT_MASK;
            GT_assert(VpsHalTrace, (NULL != cfg->addr));
        }
        else
        {
            reg &= ~CAL_RD_DMA_CTRL_INIT_MASK;
        }
        HW_WR_REG32(baseAddr + CAL_RD_DMA_CTRL, reg);

        if((uint32_t)TRUE == cfg->enableDpcmInitContext)
        {
            reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_INIT_ADDR);
            reg &= ~CAL_RD_DMA_INIT_ADDR_MASK;
            reg |= CAL_RD_DMA_INIT_ADDR_MASK & cfg->addr;
            HW_WR_REG32(baseAddr + CAL_RD_DMA_INIT_ADDR, reg);

            reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_INIT_OFST);
            reg &= ~CAL_RD_DMA_INIT_OFST_MASK;
            reg |= CAL_RD_DMA_INIT_OFST_MASK & cfg->offSet;
            HW_WR_REG32(baseAddr + CAL_RD_DMA_INIT_OFST, reg);
        }

        /* Enable Pixel Processing, as a last step */
        reg  = HW_RD_REG32(baseAddr + CAL_PIX_PROC(context));
        reg |= CAL_PIX_PROC_EN_MASK;
        HW_WR_REG32(baseAddr + CAL_PIX_PROC(context), reg);
    }

    return rtnVal;
}

/**************************Function Separator**********************************/

static int32_t CalSetBysOutCfg(const isshalCalInstObj_t *pInst,
                               const vpsissCalBysOut_t *cfg, uint32_t cportId)
{
    uint32_t          baseAddr;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    GT_assert(VpsHalTrace, (0U != baseAddr));

    reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL1);
    reg &= ~CAL_BYS_CTRL1_PCLK_MASK;
    if((uint32_t)TRUE == cfg->enable)
    {
        reg &= ~(CAL_BYS_CTRL1_XBLK_MASK | CAL_BYS_CTRL1_YBLK_MASK);

        reg |= CAL_BYS_CTRL1_PCLK_MASK &
               (cfg->pixClock << CAL_BYS_CTRL1_PCLK_SHIFT);

        reg |= CAL_BYS_CTRL1_XBLK_MASK &
               (cfg->xBlk << CAL_BYS_CTRL1_XBLK_SHIFT);

        reg |= CAL_BYS_CTRL1_YBLK_MASK &
               (cfg->yBlk << CAL_BYS_CTRL1_YBLK_SHIFT);
        HW_WR_REG32(baseAddr + CAL_BYS_CTRL1, reg);

        reg  = HW_RD_REG32(baseAddr + CAL_BYS_CTRL2);
        reg &= ~(CAL_BYS_CTRL2_CPORTOUT_MASK |
                 CAL_BYS_CTRL2_DUPLICATEDDATA_MASK |
                 CAL_BYS_CTRL2_FREERUNNING_MASK);
        if((uint32_t)TRUE == cfg->freeRun)
        {
            reg |= CAL_BYS_CTRL2_FREERUNNING_MASK;
        }

        if((uint32_t)TRUE == cfg->copyStreamToEncode)
        {
            reg |= CAL_BYS_CTRL2_DUPLICATEDDATA_MASK;
        }

        reg |= CAL_BYS_CTRL2_CPORTOUT_MASK &
               (cportId << CAL_BYS_CTRL2_CPORTOUT_SHIFT);

        HW_WR_REG32(baseAddr + CAL_BYS_CTRL2, reg);
    }
    else
    {
        HW_WR_REG32(baseAddr + CAL_BYS_CTRL1, reg);
    }

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalSetVportCfg(const isshalCalInstObj_t *pInst,
                              const vpsissCalVPort_t   *cfg,
                              uint32_t                  cportId)
{
    uint32_t          baseAddr;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    GT_assert(VpsHalTrace, (0U != baseAddr));

    reg  = HW_RD_REG32(baseAddr + CAL_VPORT_CTRL1);
    reg &= ~CAL_VPORT_CTRL1_PCLK_MASK;
    if((uint32_t)TRUE == cfg->enable)
    {
        reg &= ~(CAL_VPORT_CTRL1_XBLK_MASK | CAL_VPORT_CTRL1_YBLK_MASK |
                 CAL_VPORT_CTRL1_WIDTH_MASK);

        reg |= CAL_VPORT_CTRL1_PCLK_MASK & cfg->pixClock;

        reg |= CAL_VPORT_CTRL1_XBLK_MASK &
               (cfg->xBlk << CAL_VPORT_CTRL1_XBLK_SHIFT);

        reg |= CAL_VPORT_CTRL1_YBLK_MASK &
               (cfg->yBlk << CAL_VPORT_CTRL1_YBLK_SHIFT);

        if(0x0U != cfg->width)
        {
            reg |= CAL_VPORT_CTRL1_WIDTH_MASK;
        }
        HW_WR_REG32(baseAddr + CAL_VPORT_CTRL1, reg);

        reg  = HW_RD_REG32(baseAddr + CAL_VPORT_CTRL2);
        reg &=
            ~(CAL_VPORT_CTRL2_RDY_THR_MASK | CAL_VPORT_CTRL2_FSM_RESET_MASK |
              CAL_VPORT_CTRL2_FS_RESETS_MASK |
              CAL_VPORT_CTRL2_FREERUNNING_MASK |
              CAL_VPORT_CTRL2_CPORT_MASK);

        reg |= CAL_VPORT_CTRL2_CPORT_MASK & cportId;

        if((uint32_t)TRUE == cfg->freeRun)
        {
            reg |= CAL_VPORT_CTRL2_FREERUNNING_MASK;
        }

        if((uint32_t)TRUE == cfg->fsReset)
        {
            reg |= CAL_VPORT_CTRL2_FS_RESETS_MASK;
        }

        reg |= CAL_VPORT_CTRL2_RDY_THR_MASK &
               (cfg->rdyThr << CAL_VPORT_CTRL2_RDY_THR_SHIFT);

        HW_WR_REG32(baseAddr + CAL_VPORT_CTRL2, reg);
    }
    else
    {
        HW_WR_REG32(baseAddr + CAL_VPORT_CTRL1, reg);
    }

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalSetRdDmaCfg(const isshalCalInstObj_t  *pInst,
                              const isshalCalRdDmaCfg_t *cfg,
                              uint32_t                   cportId)
{
    uint32_t          baseAddr;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    GT_assert(VpsHalTrace, (0U != baseAddr));

    reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_CTRL);
    reg &= ~CAL_RD_DMA_CTRL_PCLK_MASK;

    if((uint32_t)TRUE == cfg->enable)
    {
        reg &= ~(CAL_RD_DMA_CTRL_GO_MASK | CAL_RD_DMA_CTRL_BW_LIMITER_MASK |
                 CAL_RD_DMA_CTRL_OCP_TAG_CNT_MASK);

        reg |= CAL_RD_DMA_CTRL_BW_LIMITER_MASK &
               (cfg->bwLimit << CAL_RD_DMA_CTRL_BW_LIMITER_SHIFT);

        reg |= CAL_RD_DMA_CTRL_OCP_TAG_CNT_MASK &
               (cfg->ocpTagCnt << CAL_RD_DMA_CTRL_OCP_TAG_CNT_SHIFT);

        reg |= CAL_RD_DMA_CTRL_PCLK_MASK &
               (cfg->pixClock << CAL_RD_DMA_CTRL_PCLK_SHIFT);

        HW_WR_REG32(baseAddr + CAL_RD_DMA_CTRL, reg);

        reg = HW_RD_REG32(baseAddr + CAL_RD_DMA_CTRL2);

        reg &= ~(CAL_RD_DMA_CTRL2_CIRC_MODE_MASK |
                 CAL_RD_DMA_CTRL2_CIRC_SIZE_MASK |
                 CAL_RD_DMA_CTRL2_ICM_CSTART_MASK |
                 CAL_RD_DMA_CTRL2_PATTERN_MASK |
                 CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_MASK);
        reg |= CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_MASK &
               (cfg->bysOutLeWait << CAL_RD_DMA_CTRL2_BYSOUT_LE_WAIT_SHIFT);

        reg |= CAL_RD_DMA_CTRL2_PATTERN_MASK &
               (cfg->ySkipMode << CAL_RD_DMA_CTRL2_PATTERN_SHIFT);

        HW_WR_REG32(baseAddr + CAL_RD_DMA_CTRL2, reg);

        CalSetRdDmaFrameCfg(pInst, &cfg->format);
    }
    else
    {
        HW_WR_REG32(baseAddr + CAL_RD_DMA_CTRL, reg);
    }
    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t CalSetRdDmaFrameCfg(const isshalCalInstObj_t *pInst,
                                   const Fvid2_Format       *cfg)
{
    uint32_t          baseAddr;
    uint32_t          hSize;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    GT_assert(VpsHalTrace, (0U != baseAddr));

    if((FVID2_BPP_BITS10 == cfg->bpp) ||
       (FVID2_BPP_BITS11 == cfg->bpp) ||
       (FVID2_BPP_BITS12 == cfg->bpp) ||
       (FVID2_BPP_BITS13 == cfg->bpp) ||
       (FVID2_BPP_BITS14 == cfg->bpp) ||
       (FVID2_BPP_BITS15 == cfg->bpp) ||
       (FVID2_BPP_BITS16 == cfg->bpp))
    {
        hSize = ((cfg->width * 2U) / 8U);
    }
    else
    {
        hSize = (cfg->width / 8U);
    }

    reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_XSIZE);
    reg &= ~CAL_RD_DMA_XSIZE_MASK;
    /* Require to specify the number of 64 bits read, essentially
     *  total bits / 64 or byte count / 8 */
    reg |= CAL_RD_DMA_XSIZE_MASK & ((hSize) << CAL_RD_DMA_XSIZE_SHIFT);
    HW_WR_REG32(baseAddr + CAL_RD_DMA_XSIZE, reg);

    reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_YSIZE);
    reg &= ~CAL_RD_DMA_YSIZE_MASK;
    reg |= CAL_RD_DMA_YSIZE_MASK & (cfg->height << CAL_RD_DMA_YSIZE_SHIFT);
    HW_WR_REG32(baseAddr + CAL_RD_DMA_YSIZE, reg);

    reg  = HW_RD_REG32(baseAddr + CAL_RD_DMA_PIX_OFST);
    reg &= ~CAL_RD_DMA_PIX_OFST_MASK;
    reg |= (CAL_RD_DMA_PIX_OFST_MASK & cfg->pitch[0U]);

    HW_WR_REG32(baseAddr + CAL_RD_DMA_PIX_OFST, reg);

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

int32_t VpsHal_isscalRdDmaStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg)
{
    int32_t             rtnVal = FVID2_SOK;
    volatile uint32_t   reg;
    isshalCalInstObj_t *pInstObj;
    isshalCalObj_t     *hndl = (isshalCalObj_t *) handle;

    if(NULL == hndl)
    {
        rtnVal = FVID2_EBADARGS;
    }

    if((FVID2_SOK == rtnVal) && (NULL == hndl->pInstObj))
    {
        rtnVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == rtnVal)
    {
        pInstObj = hndl->pInstObj;

        rtnVal = FVID2_EAGAIN;

        reg = HW_RD_REG32(pInstObj->baseAddr + CAL_RD_DMA_CTRL);
        if(CAL_RD_DMA_CTRL_GO_MASK != (reg & CAL_RD_DMA_CTRL_GO_MASK))
        {
            reg   |= CAL_RD_DMA_CTRL_GO_MASK;
            rtnVal = FVID2_SOK;
            HW_WR_REG32(pInstObj->baseAddr + CAL_RD_DMA_CTRL, reg);
        }
    }

    return rtnVal;
}

/**************************Function Separator**********************************/

/**
 * \brief   Applies DMA Write configurations.
 *
 * \param   pInst   Pointer to instance object.
 * \param   cfg     Valid configuration for DMA Write.
 *
 * \return  FVID2_SOK on success else error code.
 *
 **/
static int32_t CalSetWrDmaCfg(const isshalCalInstObj_t  *pInst,
                              const isshalCalWrDmaCfg_t *cfg,
                              uint32_t                   cportId)
{
    uint32_t          baseAddr, context;
    volatile uint32_t reg;

    GT_assert(VpsHalTrace, (NULL != pInst));
    GT_assert(VpsHalTrace, (NULL != cfg));

    baseAddr = pInst->baseAddr;
    context  = cfg->contextToBeUsed;
    GT_assert(VpsHalTrace, (0U != baseAddr));
    GT_assert(VpsHalTrace, (VPS_ISS_CAL_MAX_STREAMS > context));

    reg  = HW_RD_REG32(baseAddr + CAL_WR_DMA_CTRL(context));
    reg &= ~(CAL_WR_DMA_CTRL_YSIZE_MASK | CAL_WR_DMA_CTRL_STALL_RD_DMA_MASK |
             CAL_WR_DMA_CTRL_CPORT_MASK | CAL_WR_DMA_CTRL_DTAG_MASK |
             CAL_WR_DMA_CTRL_WR_PATTERN_MASK | CAL_WR_DMA_CTRL_MODE_MASK);

    reg |= CAL_WR_DMA_CTRL_MODE_MASK & cfg->mode;

    reg |= CAL_WR_DMA_CTRL_WR_PATTERN_MASK &
           (cfg->ySkipMode << CAL_WR_DMA_CTRL_WR_PATTERN_SHIFT);

    reg |= CAL_WR_DMA_CTRL_DTAG_MASK &
           (cfg->stream << CAL_WR_DMA_CTRL_DTAG_SHIFT);

    reg |= CAL_WR_DMA_CTRL_CPORT_MASK &
           (cportId << CAL_WR_DMA_CTRL_CPORT_SHIFT);

    reg |= CAL_WR_DMA_CTRL_STALL_RD_DMA_MASK &
           (cfg->stallM2MRd << CAL_WR_DMA_CTRL_STALL_RD_DMA_SHIFT);

    reg |= CAL_WR_DMA_CTRL_YSIZE_MASK &
           (cfg->format.height << CAL_WR_DMA_CTRL_YSIZE_SHIFT);
    HW_WR_REG32(baseAddr + CAL_WR_DMA_CTRL(context), reg);

    reg  = HW_RD_REG32(baseAddr + CAL_WR_DMA_OFST(context));
    reg &= ~CAL_WR_DMA_OFST_OFFST_MASK;
    /* No support for circular mode as of now */
    reg &= ~(CAL_WR_DMA_OFST_CIRC_MODE_MASK | CAL_WR_DMA_OFST_CIRC_SIZE_MASK);
    /* Shifting is not required */
    reg |= CAL_WR_DMA_OFST_OFFST_MASK & cfg->format.pitch[0];
    HW_WR_REG32(baseAddr + CAL_WR_DMA_OFST(context), reg);

    reg  = HW_RD_REG32(baseAddr + CAL_WR_DMA_XSIZE(context));
    reg &= ~(CAL_WR_DMA_XSIZE_XSIZE_MASK | CAL_WR_DMA_XSIZE_XSKIP_MASK);
    reg |= CAL_WR_DMA_XSIZE_XSKIP_MASK &
           (cfg->xPixelSkip << CAL_WR_DMA_XSIZE_XSKIP_SHIFT);

    reg |= CAL_WR_DMA_XSIZE_XSIZE_MASK &
           (cfg->format.width << CAL_WR_DMA_XSIZE_XSIZE_SHIFT);
    HW_WR_REG32(baseAddr + CAL_WR_DMA_XSIZE(context), reg);

    return FVID2_SOK;
}

/**************************Function Separator**********************************/

static int32_t calSetWrDmaMode(const isshalCalInstObj_t  *pInstObj,
                               const isshalCalDmaVcCfg_t *pDmaCfg)
{
    volatile uint32_t reg;
    uint32_t          baseAddr, instance, i;

    baseAddr = pInstObj->baseAddr;
    for(i = 0; i < pDmaCfg->numCPortId; i++)
    {
        if((uint32_t)TRUE == pDmaCfg->isWrDmaCfgValid[i])
        {
            instance = pDmaCfg->wrDmaCfg[i].contextToBeUsed;
            reg      = HW_RD_REG32(baseAddr + CAL_WR_DMA_CTRL(instance));
            reg     &= ~CAL_WR_DMA_CTRL_MODE_MASK;

            reg |= CAL_WR_DMA_CTRL_MODE_MASK &
                   pDmaCfg->wrDmaCfg[i].mode;

            HW_WR_REG32(baseAddr + CAL_WR_DMA_CTRL(instance), reg);
        }
    }

    return (FVID2_SOK);
}

/**************************Function Separator**********************************/
