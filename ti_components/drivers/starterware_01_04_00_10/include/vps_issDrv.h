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
 *  \defgroup BSP_DRV_ISS_STARTERWARE_API ISS Starterware Driver API
 *
 *  @{
 */

/**
 *  \file VPS_ISSDrv.h
 *
 *  \brief File containing the VPS display driver APIs.
 *
 */
#ifndef VPS_ISSDRV_H_
#define VPS_ISSDRV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Video Pipeline 1 display driver instance number. */

/** \brief ISS Capture driver instance for CAL->DDR */
#define ISSDRV_CAPT_INST_ISS_INST1							(0U)

/** \brief ISS Capture driver instance for RAW capture from CAL,
  		   process and convert it in YUV and store it as YUV format */
#define ISSDRV_CAPT_INST_ISS_INST2							(1U)

/** \brief ISS Capture driver instance for YUV capture from CAL,
		  Resize and store it as YUV */
#define ISSDRV_CAPT_INST_ISS_INST3							(2U)


/* Different Input and Output Stream Id */
/** \brief Id for the current Input */
#define ISSDRV_STREAM_ID_INPUT_0							(0U)

/** \brief Id for the current output */
#define ISSDRV_STREAM_ID_OUTPUT_0							(1U)

/** \brief Id for output from RSZ_A */
#define ISSDRV_STREAM_ID_RSZ_A								(1U)

/** \brief Id for the Previous input */
#define ISSDRV_STREAM_ID_INPUT_N1							(2U)

/** \brief Id for output from RSZ_B */
#define ISSDRV_STREAM_ID_RSZ_B								(3U)

/** \brief Id for output BSC data */
#define ISSDRV_STREAM_ID_BSC								(4U)

/** \brief Id for output Boxcar data */
#define ISSDRV_STREAM_ID_BOXCAR								(5U)

/** \brief Id for output Histogram data */
#define ISSDRV_STREAM_ID_HIST								(6U)

/** \brief Id for output AutoFocus Data */
#define ISSDRV_STREAM_ID_AF									(7U)

/** \brief Id for output AutoWhiteBalance Data */
#define ISSDRV_STREAM_ID_AF									(8U)

/** \brief Id for output AutoExposure Data */
#define ISSDRV_STREAM_ID_AF									(9U)

/** \brief Id for Input LensShadingCorrection Data */
#define ISSDRV_STREAM_ID_LSC								(10U)

/** \brief Id for Input LDC Lut Data */
#define ISSDRV_STREAM_ID_LDC_LUT							(11U)


/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPS_ISSDRV_H_ */

/* @} */
