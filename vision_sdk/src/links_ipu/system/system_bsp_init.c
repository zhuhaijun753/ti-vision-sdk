/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \file system_bsp_init.c
 *
 * \brief  APIs for initializing BIOS Drivers.
 *
 *         BIOS Support Package inits, which includes BIOS video drivers inits
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *                           Include Files                                     *
 ******************************************************************************/

#include "system_bsp_init.h"

/**
 *******************************************************************************
 * \brief Align BSS memory with that of BIOS heap library requirement
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Link Stack
 *
 *        Align descriptor memory with that of VPDMA requirement.
 *        Place the descriptor in non-cached heap section.
 *
 *******************************************************************************
 */

 /*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Initialize the required modules of BIOS video drivers
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 System_bspInit(void)
{
    Int32 nStatus = SYSTEM_LINK_STATUS_SOK;
    Bsp_CommonInitParams commonInitPrms; /* Initialized using BSP APIs */
    Bsp_PlatformInitParams platInitPrms; /* Initialized using BSP APIs */
    Vps_InitParams vpsInitPrms; /* Initialized using BSP APIs */

    BspCommonInitParams_init(&commonInitPrms);

    Vps_printf(" SYSTEM: BSP Common Init in progress !!!\n");
    nStatus = Bsp_commonInit(&commonInitPrms);
    if (SYSTEM_LINK_STATUS_SOK != nStatus)
    {
        Vps_printf(" SYSTEM: BSP Common Init Failed !!!\n");
    }
    else
    {
        Vps_printf(" SYSTEM: BSP Common Init Done !!!\n");
    }

    if (SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        BspPlatformInitParams_init(&platInitPrms);
        Vps_printf(" SYSTEM: BSP Platform Init in progress !!!\n");
#ifdef A15_TARGET_OS_LINUX
        platInitPrms.isPinMuxSettingReq  = FALSE;
        platInitPrms.isAllMcASPInitReq   = FALSE;
        platInitPrms.isAllMcSPIInitReq   = FALSE;
        platInitPrms.isDmaXBarSettingReq = FALSE;
        platInitPrms.isIrqXBarSettingReq = FALSE;
#else
        platInitPrms.isPinMuxSettingReq = TRUE;
#endif

        nStatus = Bsp_platformInit(&platInitPrms);

#ifdef A15_TARGET_OS_LINUX
        if (SYSTEM_LINK_STATUS_SOK == nStatus)
        {
            /* Unlock MMR_LOCK_2  */
            nStatus = Bsp_platformUnLockRegion(BSP_PLATFORM_MMR_REG_2);
            if (SYSTEM_LINK_STATUS_SOK == nStatus)
            {
                    /* XBAR VIP1_IRQ1 to IPU1_27
                        * XBAR VIP2_IRQ1 to IPU1_28 */
                    *((volatile UInt32 *) 0x4A0027E8U) =
                            ((UInt32) 352 << 16) | (UInt32) 351;
                    /* XBAR VIP3_IRQ1 to IPU1_29
                        * XBAR VPE1_IRQ1 to IPU1_30 */
                    *((volatile UInt32 *) 0x4A0027ECU) =
                            ((UInt32) 354 << 16) | (UInt32) 353;
            }
        }
#endif

        if (SYSTEM_LINK_STATUS_SOK != nStatus)
        {
            Vps_printf(" SYSTEM: BSP Platform Init Failed !!!\n");
        }
        else
        {
            Vps_printf(" SYSTEM: BSP Platform Init Done !!!\n");
        }
    }

    if (SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        Vps_printf(" SYSTEM: FVID2 Init in progress !!!\n");
        nStatus = Fvid2_init(NULL);
        if (SYSTEM_LINK_STATUS_SOK != nStatus)
        {
            Vps_printf(" SYSTEM: FVID2 Init Failed !!!\n");
        }
        else
        {
            Vps_printf(" SYSTEM: FVID2 Init Done !!!\n");
        }
    }

    if (SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        Vps_printf(" SYSTEM: VPS Init in progress !!!\n");

        VpsInitParams_init(&vpsInitPrms);
#ifdef TDA2XX_FAMILY_BUILD
        vpsInitPrms.virtBaseAddr = 0x80000000U;
        vpsInitPrms.physBaseAddr = 0x80000000U;
#else
        vpsInitPrms.virtBaseAddr = 0xA0000000U;
        vpsInitPrms.physBaseAddr = 0x80000000U;

        /* if Virtual address != Physical address then enable translation
        * In TDA3xx this is required
        */
        vpsInitPrms.isAddrTransReq = TRUE;
#endif
        Vps_printf(" SYSTEM: VPDMA Descriptor Memory Address translation"
                    " ENABLED [0x%08x -> 0x%08x]\n",
                    vpsInitPrms.virtBaseAddr,
                    vpsInitPrms.physBaseAddr);

    }

    if (SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        nStatus = Vps_init(&vpsInitPrms);
        if (SYSTEM_LINK_STATUS_SOK != nStatus)
        {
            Vps_printf(" SYSTEM: VPS Init Failed !!!\n");
        }
        else
        {
            Vps_printf(" SYSTEM: VPS Init Done !!!\n");
        }
    }

    return nStatus;
}

/**
 *******************************************************************************
 *
 * \brief De-initialize the previously initialized modules
 *  of BIOS video drivers
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 System_bspDeInit(void)
{
    Int32 nStatus = SYSTEM_LINK_STATUS_EFAIL;

    nStatus = Vps_deInit(NULL);
    if (SYSTEM_LINK_STATUS_SOK != nStatus)
    {
        Vps_printf(" SYSTEM: VPS De-Init Failed !!!\n");
    }

    if(SYSTEM_LINK_STATUS_SOK == nStatus)
    {
        nStatus = Fvid2_deInit(NULL);
        if (SYSTEM_LINK_STATUS_SOK != nStatus)
        {
            Vps_printf(" SYSTEM: FVID2 De-Init Failed !!!\n");
        }
    }

    if(SYSTEM_LINK_STATUS_SOK == nStatus)
    {
           nStatus = Bsp_platformDeInit(NULL);
           if (SYSTEM_LINK_STATUS_SOK != nStatus)
           {
               Vps_printf(" SYSTEM: BSP Platform De-Init Failed !!!\n");
           }
    }

    if(SYSTEM_LINK_STATUS_SOK == nStatus)
    {
           nStatus = Bsp_commonDeInit(NULL);
           if (SYSTEM_LINK_STATUS_SOK != nStatus)
           {
               Vps_printf(" SYSTEM: BSP Common De-Init Failed !!!\n");
           }
    }

    return nStatus;
}
