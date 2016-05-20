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
 *  \file vpshal.c
 *
 *  \brief File containing the VPS HAL init, deinit and other common
 *  functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <soc.h>
#include <soc_defines.h>
#include <hal/vpshal_platform.h>
#include <common/vps_common.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if defined (TDA3XX_FAMILY_BUILD)
static VpsHal_PlatformData           gVpsHalPlatDataTda3xx =
{
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    0U,                                                 /* numVpdma */
    {
        /* vpdmaInstPrms:halId,             vpdmaInstPrms:baseAddr */
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
        {
            VPSHAL_VIP1_VPDMA, SOC_VIP1_VIP_VPDMA_REGS_BASE, 0U, 0U, 0U, 0U, 0U
        },
  #endif    /* #if defined (VPS_VIP1_BUILD) */
#endif
    },

    0U,                                                 /* numCsc */
    {
        /* cscInstPrms:halId,    cscInstPrms:baseAddr */
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
        {VPSHAL_VIP1_S0_CSC,   SOC_VIP1_VIP_CSC_SLICE0_REGS_BASE   },
        {VPSHAL_VIP1_S1_CSC,   SOC_VIP1_VIP_CSC_SLICE1_REGS_BASE   },
  #endif    /* #if defined (VPS_VIP1_BUILD) */
#endif
    },

    0U,                                                 /* numSc */
    {
        /*  scInstPrms:halId,               scInstPrms:baseAddr,
         *  scInstPrms:coeffConfigDest,     scInstPrms:isHqScaler */
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
        {
            VPSHAL_VIP1_S0_SC, SOC_VIP1_VIP_SC_SLICE0_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC3, FALSE
        },
        {
            VPSHAL_VIP1_S1_SC, SOC_VIP1_VIP_SC_SLICE1_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC4, FALSE
        },
  #endif    /* #if defined (VPS_VIP1_BUILD) */
#endif
    },
#endif

#ifdef VPS_VIP_BUILD
    0U,                                                 /* numVipTop */
    {
        /* vipTopInstPrms:halId, vipTopInstPrms:baseAddr */
  #if defined (VPS_VIP1_BUILD)
        {VPSHAL_VIP1,          SOC_VIP1_VIP_REGS_BASE              }
  #endif    /* #if defined (VPS_VIP1_BUILD) */
    },

    0U,                                                 /* numVipPort */
    {
        /* vipPortInstPrms:halId,           vipPortInstPrms:baseAddr */
  #if defined (VPS_VIP1_BUILD)
        {VPSHAL_VIP1_S0_PORTA, SOC_VIP1_VIP_PARSER_SLICE0_REGS_BASE},
        {VPSHAL_VIP1_S0_PORTB, SOC_VIP1_VIP_PARSER_SLICE0_REGS_BASE},
        {VPSHAL_VIP1_S1_PORTA, SOC_VIP1_VIP_PARSER_SLICE1_REGS_BASE},
        {VPSHAL_VIP1_S1_PORTB, SOC_VIP1_VIP_PARSER_SLICE1_REGS_BASE}
  #endif    /* #if defined (VPS_VIP1_BUILD) */
    },
#endif

#ifdef VPS_DSS_BUILD
    CSL_VPS_DSS_VID_PIPE_PER_CNT,                   /* numVidPipe */
    {
        /* VidInstParams:halId */
        {VPSHAL_DSS_DISPC_VID1},
        {VPSHAL_DSS_DISPC_VID2},
        {VPSHAL_DSS_DISPC_GFX}
    },

    CSL_VPS_DSS_WB_PIPE_PER_CNT,                           /* numWbPipe */
    {
        {VPSHAL_DSS_DISPC_WB1}
    },

    CSL_VPS_DSS_OVLY_MGR_PER_CNT,                   /* numOvlyMgrs */
    {
        /* DispcOvlInstParams:halId */
        {VPSHAL_DSS_DISPC_LCD1},
        {VPSHAL_DSS_DISPC_LCD2}
    },
#endif
#if !(defined (VPS_VIP_BUILD)) && !(defined (VPS_VPE_BUILD)) && \
    !(defined (VPS_DSS_BUILD))
    0U
#endif
};
#endif  /* #if defined (TDA3XX_FAMILY_BUILD) */

#if defined (TDA2XX_FAMILY_BUILD)
static VpsHal_PlatformData           gVpsHalPlatDataTda2xx =
{
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    0U,                                                 /* numVpdma */
    {
        /* vpdmaInstPrms:halId,             vpdmaInstPrms:baseAddr */
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
        {
            VPSHAL_VIP1_VPDMA, SOC_VIP1_VIP_VPDMA_REGS_BASE, 0U, 0U, 0U, 0U, 0U
        },
  #endif    /* #if defined (VPS_VIP1_BUILD) */
#ifndef TDA2EX_BUILD
  #if defined (VPS_VIP2_BUILD)
        {
            VPSHAL_VIP2_VPDMA, SOC_VIP2_VIP_VPDMA_REGS_BASE, 0U, 0U, 0U, 0U, 0U
        },
  #endif    /* #if defined (VPS_VIP2_BUILD) */
  #if defined (VPS_VIP3_BUILD)
        {
            VPSHAL_VIP3_VPDMA, SOC_VIP3_VIP_VPDMA_REGS_BASE, 0U, 0U, 0U, 0U, 0U
        },
  #endif    /* #if defined (VPS_VIP3_BUILD) */
#endif      /* #ifndef TDA2EX_BUILD */
#endif

#ifdef VPS_VPE_BUILD
        {
            VPSHAL_VPE1_VPDMA, SOC_VPE_VPDMA_REGS_BASE,
            0U, 0U, 0U, 0U, 0U
        }
#endif
    },

    0U,                                                 /* numCsc */
    {
        /* cscInstPrms:halId,    cscInstPrms:baseAddr */
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
        {VPSHAL_VIP1_S0_CSC,     SOC_VIP1_VIP_CSC_SLICE0_REGS_BASE   },
        {VPSHAL_VIP1_S1_CSC,     SOC_VIP1_VIP_CSC_SLICE1_REGS_BASE   },
  #endif    /* #if defined (VPS_VIP1_BUILD) */
#ifndef TDA2EX_BUILD
  #if defined (VPS_VIP2_BUILD)
        {VPSHAL_VIP2_S0_CSC,     SOC_VIP2_VIP_CSC_SLICE0_REGS_BASE   },
        {VPSHAL_VIP2_S1_CSC,     SOC_VIP2_VIP_CSC_SLICE1_REGS_BASE   },
  #endif    /* #if defined (VPS_VIP2_BUILD) */
  #if defined (VPS_VIP3_BUILD)
        {VPSHAL_VIP3_S0_CSC,     SOC_VIP3_VIP_CSC_SLICE0_REGS_BASE   },
        {VPSHAL_VIP3_S1_CSC,     SOC_VIP3_VIP_CSC_SLICE1_REGS_BASE   },
  #endif    /* #if defined (VPS_VIP3_BUILD) */
#endif      /* #ifndef TDA2EX_BUILD */
#endif

#ifdef VPS_VPE_BUILD
        {VPSHAL_VPE1_CSC,        SOC_VPE_CSC_REGS_BASE               }
#endif
    },

    0U,                                                 /* numSc */
    {
        /*  scInstPrms:halId,               scInstPrms:baseAddr,
         *  scInstPrms:coeffConfigDest,     scInstPrms:isHqScaler */
#ifdef VPS_VIP_BUILD
  #if defined (VPS_VIP1_BUILD)
        {
            VPSHAL_VIP1_S0_SC, SOC_VIP1_VIP_SC_SLICE0_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC3, FALSE
        },
        {
            VPSHAL_VIP1_S1_SC, SOC_VIP1_VIP_SC_SLICE1_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC4, FALSE
        },
  #endif    /* #if defined (VPS_VIP1_BUILD) */
#ifndef TDA2EX_BUILD
  #if defined (VPS_VIP2_BUILD)
        {
            VPSHAL_VIP2_S0_SC, SOC_VIP2_VIP_SC_SLICE0_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC3, FALSE
        },
        {
            VPSHAL_VIP2_S1_SC, SOC_VIP2_VIP_SC_SLICE1_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC4, FALSE
        },
  #endif    /* #if defined (VPS_VIP2_BUILD) */
  #if defined (VPS_VIP3_BUILD)
        {
            VPSHAL_VIP3_S0_SC, SOC_VIP3_VIP_SC_SLICE0_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC3, FALSE
        },
        {
            VPSHAL_VIP3_S1_SC, SOC_VIP3_VIP_SC_SLICE1_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC4, FALSE
        },
  #endif    /* #if defined (VPS_VIP3_BUILD) */
#endif      /* #ifndef TDA2EX_BUILD */
#endif

#ifdef VPS_VPE_BUILD
        {
            VPSHAL_VPE1_SC, SOC_VPE_SC_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC1, FALSE
        }
#endif
    },
#endif

#ifdef VPS_VIP_BUILD
    0U,                                                 /* numVipTop */
    {
        /* vipTopInstPrms:halId, vipTopInstPrms:baseAddr */
  #if defined (VPS_VIP1_BUILD)
        {VPSHAL_VIP1,            SOC_VIP1_VIP_REGS_BASE              },
  #endif    /* #if defined (VPS_VIP1_BUILD) */
#ifndef TDA2EX_BUILD
  #if defined (VPS_VIP2_BUILD)
        {VPSHAL_VIP2,            SOC_VIP2_VIP_REGS_BASE              },
  #endif    /* #if defined (VPS_VIP2_BUILD) */
  #if defined (VPS_VIP3_BUILD)
        {VPSHAL_VIP3,            SOC_VIP3_VIP_REGS_BASE              }
  #endif    /* #if defined (VPS_VIP3_BUILD) */
#endif      /* #ifndef TDA2EX_BUILD */
    },

    0U,                                                 /* numVipPort */
    {
        /* vipPortInstPrms:halId,           vipPortInstPrms:baseAddr */
  #if defined (VPS_VIP1_BUILD)
        {VPSHAL_VIP1_S0_PORTA,   SOC_VIP1_VIP_PARSER_SLICE0_REGS_BASE},
        {VPSHAL_VIP1_S0_PORTB,   SOC_VIP1_VIP_PARSER_SLICE0_REGS_BASE},
        {VPSHAL_VIP1_S1_PORTA,   SOC_VIP1_VIP_PARSER_SLICE1_REGS_BASE},
        {VPSHAL_VIP1_S1_PORTB,   SOC_VIP1_VIP_PARSER_SLICE1_REGS_BASE},
  #endif    /* #if defined (VPS_VIP1_BUILD) */
#ifndef TDA2EX_BUILD
  #if defined (VPS_VIP2_BUILD)
        {VPSHAL_VIP2_S0_PORTA,   SOC_VIP2_VIP_PARSER_SLICE0_REGS_BASE},
        {VPSHAL_VIP2_S0_PORTB,   SOC_VIP2_VIP_PARSER_SLICE0_REGS_BASE},
        {VPSHAL_VIP2_S1_PORTA,   SOC_VIP2_VIP_PARSER_SLICE1_REGS_BASE},
        {VPSHAL_VIP2_S1_PORTB,   SOC_VIP2_VIP_PARSER_SLICE1_REGS_BASE},
  #endif    /* #if defined (VPS_VIP2_BUILD) */
  #if defined (VPS_VIP3_BUILD)
        {VPSHAL_VIP3_S0_PORTA,   SOC_VIP3_VIP_PARSER_SLICE0_REGS_BASE},
        {VPSHAL_VIP3_S0_PORTB,   SOC_VIP3_VIP_PARSER_SLICE0_REGS_BASE},
        {VPSHAL_VIP3_S1_PORTA,   SOC_VIP3_VIP_PARSER_SLICE1_REGS_BASE},
        {VPSHAL_VIP3_S1_PORTB,   SOC_VIP3_VIP_PARSER_SLICE1_REGS_BASE}
  #endif    /* #if defined (VPS_VIP3_BUILD) */
#endif      /* #ifndef TDA2EX_BUILD */
    },
#endif

#ifdef VPS_VPE_BUILD
    CSL_VPS_VPE_TOP_PER_CNT,                        /* numVpeTop */
    {
        /* vpeTopInstPrms:halId,            vpeTopInstPrms:baseAddr */
        {VPSHAL_VPE1,            SOC_VPE_REGS_BASE                   },
    },

    CSL_VPS_CHRUS_PER_CNT,                          /* numChrus */
    {
        /* chrusInstPrms:halId,             chrusInstPrms:baseAddr */
        {VPSHAL_VPE1_CHRUS_PRI0, SOC_VPE_CHR_US_INST0_REGS_BASE      },
        {VPSHAL_VPE1_CHRUS_PRI1, SOC_VPE_CHR_US_INST1_REGS_BASE      },
        {VPSHAL_VPE1_CHRUS_PRI2, SOC_VPE_CHR_US_INST2_REGS_BASE      },
        {0U,                     0U                                  },
        {0U,                     0U                                  },
        {0U,                     0U                                  }
    },

    CSL_VPS_DEI_PER_CNT,                            /* numDei */
    {
        /* deiInstPrms:halId,               deiInstPrms:baseAddr */
        {VPSHAL_VPE1_DEI,        SOC_VPE_DEI_REGS_BASE               }
    },
#endif

#ifdef VPS_DSS_BUILD
    CSL_VPS_DSS_VID_PIPE_PER_CNT,                   /* numVidPipe */
    {
        /* VidInstParams:halId */
        {VPSHAL_DSS_DISPC_VID1},
        {VPSHAL_DSS_DISPC_VID2},
        {VPSHAL_DSS_DISPC_VID3},
        {VPSHAL_DSS_DISPC_GFX}
    },

    CSL_VPS_DSS_WB_PIPE_PER_CNT,                           /* numWbPipe */
    {
        {VPSHAL_DSS_DISPC_WB1}
    },

    CSL_VPS_DSS_OVLY_MGR_PER_CNT,                   /* numOvlyMgrs */
    {
        /* DispcOvlInstParams:halId */
        {VPSHAL_DSS_DISPC_LCD1},
        {VPSHAL_DSS_DISPC_LCD2},
        {VPSHAL_DSS_DISPC_LCD3},
        {VPSHAL_DSS_DISPC_HDMI}
    },
#endif
#if !(defined (VPS_VIP_BUILD)) && !(defined (VPS_VPE_BUILD)) && \
    !(defined (VPS_DSS_BUILD))
    0U
#endif
};
#endif  /* #if defined (TDA2XX_FAMILY_BUILD) */

#if defined (OMAP5X_FAMILY_BUILD)
static VpsHal_PlatformData           gVpsHalPlatDataOmap5 =
{
#ifdef VPS_DSS_BUILD
    CSL_VPS_DSS_VID_PIPE_PER_CNT,                   /* numVidPipe */
    {
        /* VidInstParams:halId */
        {VPSHAL_DSS_DISPC_VID1},
        {VPSHAL_DSS_DISPC_VID2},
        {VPSHAL_DSS_DISPC_VID3},
        {VPSHAL_DSS_DISPC_GFX }
    },

    CSL_VPS_DSS_WB_PIPE_PER_CNT,                    /* numWbPipe */
    {
        /* VidInstParams:halId */
        {VPSHAL_DSS_DISPC_WB1 }
    },

    CSL_VPS_DSS_OVLY_MGR_PER_CNT,                   /* numOvlyMgrs */
    {
        /* DispcOvlInstParams:halId */
        {VPSHAL_DSS_DISPC_LCD1},
        {VPSHAL_DSS_DISPC_LCD2},
        {VPSHAL_DSS_DISPC_LCD3},
        {VPSHAL_DSS_DISPC_HDMI}
    },
#endif
#if !(defined (VPS_VIP_BUILD)) && !(defined (VPS_VPE_BUILD)) && \
    !(defined (VPS_DSS_BUILD))
    0U
#endif
};
#endif  /* #if defined (OMAP5X_FAMILY_BUILD) */

#if defined (TI814X_FAMILY_BUILD)
static VpsHal_PlatformData           gVpsHalPlatDataTI814x =
{
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    CSL_VPS_VPDMA_PER_CNT,                       /* numVpdma */
    {
        /*  vpdmaInstPrms:halId,            vpdmaInstPrms:baseAddr */
        {
            VPSHAL_VPDMA_GENERIC, SOC_VPS_VPDMA_0_REGS_BASE,
            0U, 0U, 0U, 0U, 0U
        },
        {0U,                     0U, 0U,
         0U, 0U, 0U,
         0U},
        {0U,                     0U, 0U,                          0U,  0U, 0U,
         0U},
        {0U,                     0U, 0U,                          0U,  0U, 0U,
         0U}
    },

    CSL_VPS_CSC_PER_CNT,                         /* numCsc */
    {
        /* cscInstPrms:halId,    cscInstPrms:baseAddr */
        {VPSHAL_CSC_INST_HD1,    SOC_VPS_CSC_HD1_0_REGS_BASE},
        {VPSHAL_CSC_INST_SD,     SOC_VPS_CSC_SD_0_REGS_BASE},
        {VPSHAL_CSC_INST_WB2,    SOC_VPS_CSC_WB2_0_REGS_BASE},
        {VPSHAL_VIP1_S0_CSC,     SOC_VPS_CSC_VIP0_0_REGS_BASE},
        {VPSHAL_VIP1_S1_CSC,     SOC_VPS_CSC_VIP1_0_REGS_BASE},
        {VPSHAL_CSC_INST_HD0,    SOC_VPS_CSC_HD0_0_REGS_BASE},
        {0U,                     0U}
    },

    CSL_VPS_SC_PER_CNT,                          /* numSc */
    {
        /*  scInstPrms:halId,               scInstPrms:baseAddr,
         *  scInstPrms:coeffConfigDest,     scInstPrms:isHqScaler */
        {
            VPSHAL_VPE1_SC, SOC_VPS_SC_1_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC1, FALSE
        },
        {
            VPSHAL_SC_INST_2, SOC_VPS_SC_2_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC2, FALSE
        },
        {
            VPSHAL_VIP1_S0_SC, SOC_VPS_SC_3_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC3, FALSE
        },
        {
            VPSHAL_VIP1_S1_SC, SOC_VPS_SC_4_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC4, FALSE
        },
        {
            VPSHAL_SC_INST_5, SOC_VPS_SC_5_REGS_BASE,
            VPSHAL_VPDMA_CONFIG_DEST_SC5, FALSE
        },
        {0U,                     0U, VPSHAL_VPDMA_CONFIG_DEST_MMR,FALSE},
        {0U,                     0U, VPSHAL_VPDMA_CONFIG_DEST_MMR,FALSE}
    },
#endif

#ifdef VPS_VIP_BUILD
    CSL_VPS_PER_CNT,                             /* numVipTop */
    {
        /* vipTopInstPrms:halId,            vipTopInstPrms:baseAddr */
        {VPSHAL_VIP1,            SOC_HDVPSS_BASE},
        {0U,                     0U},
        {0U,                     0U}
    },

    CSL_VPS_VIP_PORT_PER_CNT,                           /* numVipPort */
    {
        /* vipPortInstPrms:halId,           vipPortInstPrms:baseAddr */
        {VPSHAL_VIP1_S0_PORTA,   SOC_VPS_VIP0_PARSER_0_REGS_BASE},
        {VPSHAL_VIP1_S0_PORTB,   SOC_VPS_VIP0_PARSER_0_REGS_BASE},
        {VPSHAL_VIP1_S1_PORTA,   SOC_VPS_VIP1_PARSER_0_REGS_BASE},
        {VPSHAL_VIP1_S1_PORTB,   SOC_VPS_VIP1_PARSER_0_REGS_BASE},
        {0U,                     0U},
        {0U,                     0U},
        {0U,                     0U},
        {0U,                     0U},
        {0U,                     0U},
        {0U,                     0U},
        {0U,                     0U},
        {0U,                     0U}
    },
#endif

#ifdef VPS_VPE_BUILD
    /* In case of TI814x, there is only one VPS top, hence use VIP top in case
     * VIP is defined. Else use VPE top. */
#ifdef VPS_VIP_BUILD
    0U,                                          /* numVpeTop */
#else
    CSL_VPS_PER_CNT,                             /* numVpeTop */
#endif
    {
        /* vpeTopInstPrms:halId,            vpeTopInstPrms:baseAddr */
        {VPSHAL_VPE1,            SOC_HDVPSS_BASE},
    },

    CSL_VPS_CHRUS_PER_CNT,                       /* numChrus */
    {
        /* chrusInstPrms:halId,  chrusInstPrms:baseAddr */
        {VPSHAL_VPE1_CHRUS_PRI0, SOC_VPS_CHR_US_PRI_0_REGS_BASE},
        {VPSHAL_CHRUS_AUX,       SOC_VPS_CHR_US_AUX_0_REGS_BASE},
        {VPSHAL_CHRUS_SEC0,      SOC_VPS_CHR_US_SEC0_0_REGS_BASE},
        {VPSHAL_CHRUS_SEC1,      SOC_VPS_CHR_US_SEC1_0_REGS_BASE},
        {VPSHAL_VPE1_CHRUS_PRI1, SOC_VPS_CHR_US_PRI_1_REGS_BASE},
        {VPSHAL_VPE1_CHRUS_PRI2, SOC_VPS_CHR_US_PRI_2_REGS_BASE}
    },

    CSL_VPS_DEI_PER_CNT,                         /* numDei */
    {
        /* deiInstPrms:halId,    deiInstPrms:baseAddr */
        {VPSHAL_VPE1_DEI,        SOC_VPS_DEI_0_REGS_BASE}
    },
#endif

#ifdef VPS_DSS_BUILD
    0U,                                                 /* numVidPipe */
    {
        /* VidInstParams:halId */
        {0U}
    },

    0U,                                                 /* numWbPipe */
    {
        /* VidInstParams:halId */
        {0U}
    },

    0U,                                                 /* numOvlyMgrs */
    {
        /* DispcOvlInstParams:halId */
        {0U}
    },
#endif
#if !(defined (VPS_VIP_BUILD)) && !(defined (VPS_VPE_BUILD)) && \
    !(defined (VPS_DSS_BUILD))
    0U
#endif
};
#endif  /* #if defined (TI814X_FAMILY_BUILD) */

#ifdef VPS_SIMCOP_BUILD
static vpshalissSimcopPlatformData_t gVpsHalSimcopPlatDataTda3xx =
{
    CSL_ISS_SIMCOP_PER_CNT,                /* numSimcop */
    {                                      /* simcopInitPrms[] */
        {
            ISSHAL_SIMCOP_INST_0,          /* instId              */
            ISS_SIMCOP_BASE_REGISTER,      /* simcopBaseAddress   */
            ISS_SIMCOP_DMA_REGISTERS,      /* simcopDmaBaseAddress*/
            CSL_ISS_SIMCOP_NUM_ACT_CTX,    /* numActiveContext*/
            CSL_ISS_SIMCOP_NUM_DMA_CH,     /* numDmaChannels  */
            CSL_ISS_SIMCOP_NUM_IRQ,        /* numIrq          */
            CSL_ISS_SIMCOP_MAX_HWSEQ_STEPS /* maxHwSeqSteps   */
        }
    },
    {                                /* ldcInitPrms[ISSHAL_SIMCOP_MAX_INST] */
        {
            ISSHAL_LDC_INST_0,       /* instId              */
            ISS_SIMCOP_LDC_REGISTERS /* simcopBaseAddress   */
        }
    },
    {                                 /* vtnfInitPrms[ISSHAL_SIMCOP_MAX_INST] */
        {
            ISSHAL_VTNF_INST_0,       /* instId              */
            ISS_SIMCOP_VTNF_REGISTERS /* simcopBaseAddress   */
        }
    }
};
#endif /* DVPS_SIMCOP_BUILD */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief VPS HAL init function.
 */
Int32 VpsHal_init(const VpsHal_InitParams *initPrms)
{
    Int32  retVal = BSP_SOK;
    VpsHal_PlatformData *platData;
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD) || \
    defined (VPS_DSS_BUILD)
    UInt32 cnt;
#endif
#ifdef VPS_DSS_BUILD
    VpsHal_DispcVidInstParams pipeInstPrms[VPSHAL_DSS_DISPC_PIPE_MAX_INST];
#endif

    GT_assert(VpsHalTrace, NULL != initPrms);

    /* Get Platform data */
    platData = VpsHal_getPlatformData();
    GT_assert(VpsHalTrace, NULL != platData);

#ifdef VPS_VIP_BUILD
    if((BSP_SOK == retVal) && (platData->numVipTop > 0))
    {
        /* Init VIP Top HAL */
        GT_assert(VpsHalTrace,
                  platData->numVipTop <= VPSHAL_VIP_TOP_MAX_INST);
        retVal = VpsHal_vipTopInit(
            platData->numVipTop,
            &platData->vipTopInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "VPS HAL: VIP Top init failed\n");
        }
    }
    else
    {
        retVal = BSP_EFAIL;
    }
#endif

#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    if((BSP_SOK == retVal) && (platData->numVpdma > 0))
    {
        for(cnt = 0U; cnt < platData->numVpdma; cnt++)
        {
            platData->vpdmaInstPrms[cnt].isAddrTransReq =
                (Bool) initPrms->isAddrTransReq;
            platData->vpdmaInstPrms[cnt].virtBaseAddr  = initPrms->virtBaseAddr;
            platData->vpdmaInstPrms[cnt].physBaseAddr  = initPrms->physBaseAddr;
            platData->vpdmaInstPrms[cnt].isCacheOpsReq =
                initPrms->isCacheOpsReq;
            platData->vpdmaInstPrms[cnt].isCacheFlushReq =
                initPrms->isCacheFlushReq;
        }

        /* Init VPDMA HAL */
        GT_assert(VpsHalTrace, platData->numVpdma <= VPSHAL_VPDMA_MAX_INST);
        retVal = VpsHal_vpdmaInit(
            platData->numVpdma,
            &platData->vpdmaInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "VPS HAL: VPDMA init failed\n");
        }
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    if((BSP_SOK == retVal) && (platData->numCsc > 0))
    {
        /* Init CSC HAL */
        GT_assert(VpsHalTrace, platData->numCsc <= VPSHAL_CSC_MAX_INST);
        retVal = VpsHal_cscInit(
            platData->numCsc,
            &platData->cscInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "VPS HAL: CSC init failed\n");
        }
    }

    if((BSP_SOK == retVal) && (platData->numSc > 0))
    {
        /* Init SC HAL */
        GT_assert(VpsHalTrace, platData->numSc <= VPSHAL_SC_MAX_INST);
        retVal = VpsHal_scInit(
            platData->numSc,
            &platData->scInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "VPS HAL: SC init failed\n");
        }
    }
#endif

#ifdef VPS_VIP_BUILD
    if((BSP_SOK == retVal) && (platData->numVipPort > 0))
    {
        /* Init VIP Port HAL */
        GT_assert(VpsHalTrace,
                  platData->numVipPort <= VPSHAL_VIP_PORT_MAX_INST);
        retVal = VpsHal_vipPortInit(
            platData->numVipPort,
            &platData->vipPortInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "VPS HAL: VIP PORT init failed\n");
        }
    }
#endif

#ifdef VPS_VPE_BUILD
    if((BSP_SOK == retVal) && (platData->numVpeTop > 0))
    {
        /* Init VPE Top HAL */
        GT_assert(VpsHalTrace,
                  platData->numVpeTop <= VPSHAL_VPE_TOP_MAX_INST);
        retVal = VpsHal_vpeTopInit(
            platData->numVpeTop,
            &platData->vpeTopInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "VPS HAL: VPE Top init failed\n");
        }
    }

    if((BSP_SOK == retVal) && (platData->numChrus > 0))
    {
        /* Init CHRUS HAL */
        GT_assert(VpsHalTrace, platData->numChrus <= VPSHAL_CHRUS_MAX_INST);
        retVal = VpsHal_chrusInit(
            platData->numChrus,
            &platData->chrusInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "VPS HAL: CHRUS init failed\n");
        }
    }

    if((BSP_SOK == retVal) && (platData->numDei > 0))
    {
        /* Init DEI HAL */
        GT_assert(VpsHalTrace, platData->numDei <= VPSHAL_DEI_MAX_INST);
        retVal = VpsHal_deiInit(
            platData->numDei,
            &platData->deiInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "VPS HAL: DEI init failed\n");
        }
    }
#endif

#ifdef VPS_DSS_BUILD
    if((BSP_SOK == retVal) && ((platData->numVidPipe + platData->numWbPipe) > 0))
    {
        /* Init Video Pipeline HAL */
        GT_assert(VpsHalTrace,
                  platData->numVidPipe <= VPSHAL_DSS_DISPC_VID_MAX_INST);

        GT_assert(VpsHalTrace,
                  platData->numWbPipe <= VPSHAL_DSS_DISPC_WB_MAX_INST);

        /* We have same HAL for VID,GFX and WB pipelines, but libdata is
           sepatrate for vid/gfx and WB pipeliens, so combining the initparams
           and calling single init function. */
        for(cnt = 0; cnt < platData->numVidPipe; cnt++)
        {
            pipeInstPrms[cnt] = platData->vidPipeInstPrms[cnt];
        }

        for(cnt = 0; cnt < platData->numWbPipe; cnt++)
        {
            pipeInstPrms[platData->numVidPipe +
                         cnt] = platData->wbPipeInstPrms[cnt];
        }

        retVal = VpsHal_dssVidInit(
            (platData->numVidPipe + platData->numWbPipe),
            &pipeInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(
                VpsHalTrace, GT_ERR,
                "VPS HAL: Video Pipeline HAL init failed\n");
        }
    }

    if((BSP_SOK == retVal) && (platData->numOvlyMgr > 0))
    {
        /* Init Overlay Manager HAL */
        GT_assert(VpsHalTrace,
                  platData->numOvlyMgr <= VPSHAL_DSS_DISPC_OVLY_MAX_INST);
        retVal = VpsHal_dssOvlyInit(
            platData->numOvlyMgr,
            &platData->ovlyMgrInstPrms[0U],
            NULL);
        if(retVal != BSP_SOK)
        {
            GT_0trace(VpsHalTrace, GT_ERR,
                      "VPS HAL: Overlay Manager init failed\n");
        }
    }
#endif

    return (retVal);
}

/**
 *  \brief VPS HAL deinit function.
 */
Int32 VpsHal_deInit(void)
{
    Int32 retVal = BSP_SOK;
    VpsHal_PlatformData *platData;

    /* Get Platform data */
    platData = VpsHal_getPlatformData();
    GT_assert(VpsHalTrace, NULL != platData);

#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    retVal += VpsHal_scDeInit(NULL);
    retVal += VpsHal_cscDeInit(NULL);
    retVal += VpsHal_vpdmaDeInit(NULL);
#endif

#ifdef VPS_VPE_BUILD
    retVal += VpsHal_deiDeInit(NULL);
    retVal += VpsHal_chrusDeInit(NULL);
    if(platData->numVpeTop > 0)
    {
        retVal += VpsHal_vpeTopDeInit(NULL);
    }
#endif

#ifdef VPS_VIP_BUILD
    retVal += VpsHal_vipPortDeInit(NULL);
    retVal += VpsHal_vipTopDeInit(NULL);
#endif

    return (retVal);
}

/**
 *  \brief Returns HAL platform data.
 */
VpsHal_PlatformData *VpsHal_getPlatformData(void)
{
    VpsHal_PlatformData *platData = NULL;
#if defined (TDA2XX_FAMILY_BUILD) || defined (TDA3XX_FAMILY_BUILD)
  #ifdef VPS_VIP_BUILD
    UInt32 numVip;
  #endif
#endif

#if defined (TDA2XX_FAMILY_BUILD)
    {
        platData = &gVpsHalPlatDataTda2xx;
    #if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
        platData->numVpdma = 0U;
        platData->numCsc   = 0U;
        platData->numSc    = 0U;
    #endif
    #ifdef VPS_VIP_BUILD
        numVip = 0U;
      #if defined (VPS_VIP1_BUILD)
        numVip++;
      #endif    /* #if defined (VPS_VIP1_BUILD) */
      #ifndef TDA2EX_BUILD
      #if defined (VPS_VIP2_BUILD)
        numVip++;
      #endif    /* #if defined (VPS_VIP2_BUILD) */
      #if defined (VPS_VIP3_BUILD)
        numVip++;
      #endif    /* #if defined (VPS_VIP3_BUILD) */
      #endif      /* #ifndef TDA2EX_BUILD */

        platData->numVipTop = numVip;
        platData->numVipPort = numVip * 4U;
        platData->numVpdma += numVip;
        /* 2 CSC per VIP */
        platData->numCsc += (numVip * 2U);
        /* 2 SC per VIP */
        platData->numSc += (numVip * 2U);
    #endif
    #ifdef VPS_VPE_BUILD
        platData->numVpdma += CSL_VPS_VPE_PER_CNT;
        /* 1 CSC per VPE */
        platData->numCsc += (CSL_VPS_VPE_PER_CNT * 1U);
        /* 1 SC per VPE */
        platData->numSc += (CSL_VPS_VPE_PER_CNT * 1U);
    #endif
    }
#endif  /* #if defined (TDA2XX_FAMILY_BUILD) */

#if defined (TDA3XX_FAMILY_BUILD)
    {
        platData = &gVpsHalPlatDataTda3xx;
    #if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
        platData->numVpdma = 0U;
        platData->numCsc   = 0U;
        platData->numSc    = 0U;
    #endif
    #ifdef VPS_VIP_BUILD
        numVip = 0U;
      #if defined (VPS_VIP1_BUILD)
        numVip++;
      #endif    /* #if defined (VPS_VIP1_BUILD) */

        platData->numVipTop = numVip;
        platData->numVipPort = numVip * 4U;
        platData->numVpdma += numVip;
        /* 2 CSC per VIP */
        platData->numCsc += (numVip * 2U);
        /* 2 SC per VIP */
        platData->numSc += (numVip * 2U);
    #endif
    }
#endif  /* #if defined (TDA3XX_FAMILY_BUILD)*/

#if defined (TI814X_FAMILY_BUILD)
    {
        platData = &gVpsHalPlatDataTI814x;
    }
#endif  /* #if defined (TI814X_FAMILY_BUILD) */

#if defined (OMAP5X_FAMILY_BUILD)
    {
        platData = &gVpsHalPlatDataOmap5;
    }
#endif  /* #if defined (TI814X_FAMILY_BUILD) */

    return (platData);
}

#ifdef VPS_SIMCOP_BUILD
/**
 *  \brief Returns HAL platform data for SIMCOP instances
 */
vpshalissSimcopPlatformData_t *VpsHal_getSimcopPlatformData(void)
{
    vpshalissSimcopPlatformData_t *halData = NULL;
    if(VpsLib_platformIsTda3xxFamilyBuild())
    {
        halData = &gVpsHalSimcopPlatDataTda3xx;
    }
    return halData;
}

#endif
