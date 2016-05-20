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
 *   Component:        SBL
 *
 *   Filename:         sbl_tda2xx_platform.h
 *
 *   Description:      This file contain sbl specific tda2xx platform's macro
 *                     definition
 */
#ifndef SBL_TDA2xx_PLATFORM_H_
#define SBL_TDA2xx_PLATFORM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include "hw_types.h"
#include "soc.h"
#include "pm/pm_types.h"
#include "pm/pmhal/pmhal_vm.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Core Id Enum Definition */
#define CORE_A8 0
#define CORE_DSP 1
#define CORE_M3VIDEO 2
#define CORE_M3VPSS 3
#define CORE_ARP32 4

#define DEVICE_CENTEVE 8
#define DEVICE_CENTAURUS 3

#define QSPI_OFFSET_SI      ((uint32_t) 0x80000)

#define NOR_BASE_ADDRESS    ((uint32_t) 0x8000000)
#define NOR_OFFSET_SI       ((uint32_t) 0x80000)

#define SBL_DEBUG_LOGGER_BFR  0x40511000

#define MPU_DSP1_L2_RAM         0x40800000
#define MPU_DSP1_L1P_CACHE      0x40E00000
#define MPU_DSP1_L1D_CACHE      0x40F00000
#define MPU_DSP2_L2_RAM         0x41000000
#define MPU_DSP2_L1P_CACHE      0x41600000
#define MPU_DSP2_L1D_CACHE      0x41700000

#define MPU_IPU1_ROM                                (SOC_IPU1_TARGET_BASE)
#define MPU_IPU1_RAM                                (SOC_IPU1_TARGET_BASE + \
                                                     (uint32_t) 0x20000)
#define MPU_IPU1_UNICACHE_MMU_CONFIG_REGS       (SOC_IPU1_TARGET_BASE + 0x80000)
#define MPU_IPU1_WUGEN                              (SOC_IPU1_TARGET_BASE + \
                                                     (uint32_t) 0x81000)
#define MPU_IPU1_MMU                                (SOC_IPU1_TARGET_BASE + \
                                                     (uint32_t) 0x82000)

#define MPU_IPU2_ROM                                (SOC_IPU2_TARGET_BASE)
#define MPU_IPU2_RAM                                (SOC_IPU2_TARGET_BASE + \
                                                     (uint32_t) 0x20000)
#define MPU_IPU2_UNICACHE_MMU_CONFIG_REGS       (SOC_IPU2_TARGET_BASE + 0x80000)
#define MPU_IPU2_WUGEN                              (SOC_IPU2_TARGET_BASE + \
                                                     (uint32_t) 0x81000)
#define MPU_IPU2_MMU                                (SOC_IPU2_TARGET_BASE + \
                                                     (uint32_t) 0x82000)

#define MPU_EVE1_DMEM_BASE      (SOC_EVE1_DMEM_BASE)
#define MPU_EVE1_WBUF_BASE      (SOC_EVE1_WBUF_BASE)
#define MPU_EVE1_IBUF_LA_BASE  (SOC_EVE1_IBUFLA_BASE)
#define MPU_EVE1_IBUF_HA_BASE  (SOC_EVE1_IBUFHA_BASE)
#define MPU_EVE1_IBUF_LB_BASE  (SOC_EVE1_IBUFLB_BASE)
#define MPU_EVE1_IBUF_HB_BASE  (SOC_EVE1_IBUFHB_BASE)

#define MPU_EVE2_DMEM_BASE      (SOC_EVE2_DMEM_BASE)
#define MPU_EVE2_WBUF_BASE      (SOC_EVE2_WBUF_BASE)
#define MPU_EVE2_IBUF_LA_BASE  (SOC_EVE2_IBUFLA_BASE)
#define MPU_EVE2_IBUF_HA_BASE  (SOC_EVE2_IBUFHA_BASE)
#define MPU_EVE2_IBUF_LB_BASE  (SOC_EVE2_IBUFLB_BASE)
#define MPU_EVE2_IBUF_HB_BASE  (SOC_EVE2_IBUFHB_BASE)

#define MPU_EVE3_DMEM_BASE      (SOC_EVE3_DMEM_BASE)
#define MPU_EVE3_WBUF_BASE      (SOC_EVE3_WBUF_BASE)
#define MPU_EVE3_IBUF_LA_BASE  (SOC_EVE3_IBUFLA_BASE)
#define MPU_EVE3_IBUF_HA_BASE  (SOC_EVE3_IBUFHA_BASE)
#define MPU_EVE3_IBUF_LB_BASE  (SOC_EVE3_IBUFLB_BASE)
#define MPU_EVE3_IBUF_HB_BASE  (SOC_EVE3_IBUFHB_BASE)

#define MPU_EVE4_DMEM_BASE      (SOC_EVE4_DMEM_BASE)
#define MPU_EVE4_WBUF_BASE      (SOC_EVE4_WBUF_BASE)
#define MPU_EVE4_IBUF_LA_BASE  (SOC_EVE4_IBUFLA_BASE)
#define MPU_EVE4_IBUF_HA_BASE  (SOC_EVE4_IBUFHA_BASE)
#define MPU_EVE4_IBUF_LB_BASE  (SOC_EVE4_IBUFLB_BASE)
#define MPU_EVE4_IBUF_HB_BASE  (SOC_EVE4_IBUFHB_BASE)

#define SOC_DSP_L2_BASE                            0x800000
#define SOC_DSP_L1P_BASE                         0xe00000
#define SOC_DSP_L1D_BASE                         0xf00000

#define SOC_IPU1_BOOT_SPACE_BASE    ((uint32_t) 0x0)
#define SOC_IPU1_ROM_BASE \
    0x55000000
#define SOC_IPU1_RAM_BASE \
    0x55020000

#define SOC_EVE_DMEM_BASE \
    0x40020000
#define SOC_EVE_WBUF_BASE \
    0x40040000
#define SOC_EVE_IBUF_LA_BASE \
    0x40050000
#define SOC_EVE_IBUF_HA_BASE \
    0x40054000
#define SOC_EVE_IBUF_LB_BASE \
    0x40070000
#define SOC_EVE_IBUF_HB_BASE \
    0x40074000

#define SOC_OCMC_RAM1_SIZE          ((uint32_t) 0x80000)     /*OCMC1 512KB*/
#define SOC_OCMC_RAM2_SIZE          ((uint32_t) 0x100000)    /*OCMC2 1MB   */
#define SOC_OCMC_RAM3_SIZE          ((uint32_t) 0x100000)    /*OCMC3  1MB   */

/* PRM_VC_VAL_BYPASS */
#define PRM_VC_I2C_CHANNEL_FREQ_KHZ 400

/*DSS PLL Registers*/
#define PLL_CONTROL             0x00000000U
#define PLL_STATUS              0x00000004U
#define PLL_GO                  0x00000008U
#define PLL_CONFIGURATION1      0x0000000CU
#define PLL_CONFIGURATION2      0x00000010U
#define PLL_CONFIGURATION3      0x00000014U

/*DSI1 Registers */
#define DSI_CLK_CTRL                    0x58004054
#define DSI_PLL_STATUS              0x58004304

/*DSI1 Registers */
#define DSI2_CLK_CTRL                   0x58009054
#define DSI2_PLL_STATUS             0x58009304

/*Memory Subsystem*/
#define DMM_LISA_MAP                        0x40

/* Memory Adapter */
#define DMM_LISA_MA_BASE                0x482AF040

#define DUAL_EMIF_2X512MB       (0)
#define DUAL_EMIF_1GB_512MB     (1)
#define SINGLE_EMIF_256MB           (2)

/* OPP Configuration*/
#define OPP_LOW                  (0)
#define OPP_NOM                  (1)
#define OPP_OD                   (2)
#define OPP_HIGH                 (3)

#define CFG_MODE_DDR3           0x1000U
#define CFG_MODE_DDR2           0x1001U
#define CFG_MODE_LPDDR2         0x1002U /* Not supported in DRA75x_74x,
                                         * DRA72x, TDA2x, TDA2Ex */

/* DMM */
#define SOC_MA_MPU_CONF_REGS_BASE                               (0x482af000U)
#define LISA_MAP_0                                              (0x40U)
#define LISA_MAP_1                                              (0x44U)
#define LISA_MAP_2                                              (0x48U)
#define LISA_MAP_3                                              (0x4CU)

#define EMIF_PHY_STATUS_7                                       (0x15CU)
#define EMIF_PHY_STATUS_8                                       (0x160U)
#define EMIF_PHY_STATUS_9                                       (0x164U)
#define EMIF_PHY_STATUS_10                                      (0x168U)
#define EMIF_PHY_STATUS_11                                      (0x16CU)
#define EMIF_PHY_STATUS_12                                      (0x170U)
#define EMIF_PHY_STATUS_13                                      (0x174U)
#define EMIF_PHY_STATUS_14                                      (0x178U)
#define EMIF_PHY_STATUS_15                                      (0x17CU)
#define EMIF_PHY_STATUS_16                                      (0x180U)
#define EMIF_PHY_STATUS_17                                      (0x184U)
#define EMIF_PHY_STATUS_18                                      (0x188U)
#define EMIF_PHY_STATUS_19                                      (0x18CU)
#define EMIF_PHY_STATUS_20                                      (0x190U)
#define EMIF_PHY_STATUS_21                                      (0x194U)
#define EMIF_PHY_STATUS_22                                      (0x198U)
#define EMIF_PHY_STATUS_23                                      (0x19CU)
#define EMIF_PHY_STATUS_24                                      (0x1A0U)
#define EMIF_PHY_STATUS_25                                      (0x1A4U)
#define EMIF_PHY_STATUS_26                                      (0x1A8U)

#define EMIF_LPDDR2_MODE_REG_DATA                               (0x40U)
#define EMIF_LPDDR2_MODE_REG_CONFIG                             (0x50U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef enum cpu_core_id
{
    MPU_CPU0_ID = 0,
    MPU_CPU1_ID,
    IPU1_CPU0_ID,
    IPU1_CPU1_ID,
    IPU1_CPU_SMP_ID,
    IPU2_CPU0_ID,
    IPU2_CPU1_ID,
    IPU2_CPU_SMP_ID,
    DSP1_ID,
    DSP2_ID,
    EVE1_ID,
    EVE2_ID,
    EVE3_ID,
    EVE4_ID,
    MPU_SMP_ID
}cpu_core_id_t;

typedef enum {
    TRACE_REG    = 0, /*Regression Mode*/
    TRACE_HIGH   = 1,
    TRACE_MEDIUM = 2,
    TRACE_LOW    = 3
}traceLevel_t;

/**
 *  \brief This structure defines the delay configuration for IO Delay Config
 *         Registers: CFG_X_IN, CFG_X_OUT and CFG_X_OEN.
 */
typedef struct delayConfig
{
    uint16_t offset;
    /**< Offset for Delay Configuration Register */
    uint16_t aDelay;
    /**< Value of Process Agnostic(Unaware) Delay */
    uint16_t gDelay;
    /**< Value of Process Gnostic(Aware) Delay */
}delayConfig_t;

/**
 *  \brief This structure defines the delay configuration associated with a
 *         particular pad as given by PCT (Pad Configuration Tool).
 */
typedef struct padDelayConfig
{
    uint16_t      offset;
    /**< Offset for Pad Configuration Register */
    uint32_t      regVal;
    /**< Value of Pad configuration Register as given by PCT */
    delayConfig_t delayConfigIn;
    /**< Delay Configuration of CFG_X_IN register */
    delayConfig_t delayConfigOen;
    /**< Delay Configuration of CFG_X_OEN register */
    delayConfig_t delayConfigOut;
    /**< Delay Configuration of CFG_X_OUT register */
}padDelayConfig_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void  SBL_PRINTF(traceLevel_t level, const char *ptr);
void  BootAbort(void);
int32_t SBLConfigAllVotageRails(void);
void scale_iodelay(void);
void sbl_ddr3_config(void);
int32_t GetDeviceId(void);

/**
 * \brief   This function configures the SoC PAD Mux as given by PCT along
 *          with Virtual and Manual mode delays.
 *
 * \param   None
 *
 * \return  None
 */
void SBLPlatformConfigPadMux(void);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /*SBL_TDA2xx_PLATFORM_H_*/
