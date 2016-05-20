/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/**
*  @file       edmacc_config.h
*
*  @brief      Contains edma channel controller configuration
*
*
*/
#ifndef EDMACC_CONFIG_H_
#define EDMACC_CONFIG_H_

#ifndef _TMS320C6X
#ifdef VAYU_PLATFORM

/* Number of param set RAM for EDMA sub module for VAYU platform*/
#define EDMA_NUM_PARAMS 128U
/* Number of Queues available for EDMA sub module for VAYU platform*/
#define EDMA_NUM_QUES   2U

/*-----------------------------------------------------------------------*/
/*  This is the number of logical channels that we need for this test    */
/*-----------------------------------------------------------------------*/
/* Maximum number of channels available */
#define NUM_MAX_CHANNELS    16U

/* Number of QDMA channels available */
#define NUM_QDMA_CHANNELS    8U

/* Number of EDMA channels available */
#define NUM_EDMA_CHANNELS    16U

/* Number of EDMA Events available */
#define NUM_EEVTS       16U

/* Number of QDMA Events available */
#define NUM_QEVTS        8U

/* Number of transfer completion codes available */
#define EDMA_NUM_TCCS        16U

#endif /* VAYU_PLATFORM */

#ifdef VME_PLATFORM
/* Number of param set RAM for EDMA sub module for VME platform*/
#define EDMA_NUM_PARAMS 64U
/* Number of Queues available for EDMA sub module for VME platform*/
#define EDMA_NUM_QUES   1U

/*-----------------------------------------------------------------------*/
/*  This is the number of logical channels that we need for this test    */
/*-----------------------------------------------------------------------*/
/* Maximum number of channels available */
#define NUM_MAX_CHANNELS    16U

/* Number of QDMA channels available */
#define NUM_QDMA_CHANNELS    8U

/* Number of EDMA channels available */
#define NUM_EDMA_CHANNELS    16U

/* Number of EDMA Events available */
#define NUM_EEVTS       16U

/* Number of QDMA Events available */
#define NUM_QEVTS        8U

/* Number of transfer completion codes available */
#define EDMA_NUM_TCCS        16U

#endif /* VME_PLATFORM */

#else
/* _TMS320C6X */

/* Number of param set RAM for EDMA sub module for DSP platform*/
#define EDMA_NUM_PARAMS 128U
/* Number of Queues available for EDMA sub module for DSP platform*/
#define EDMA_NUM_QUES   2U

/*-----------------------------------------------------------------------*/
/*  This is the number of logical channels that we need for this test    */
/*-----------------------------------------------------------------------*/
/* Maximum number of channels available */
#define NUM_MAX_CHANNELS    64U

/* Number of QDMA channels available */
#define NUM_QDMA_CHANNELS    8U

/* Number of EDMA channels available */
#define NUM_EDMA_CHANNELS    64U

/* Number of EDMA Events available */
#define NUM_EEVTS       64U

/* Number of QDMA Events available */
#define NUM_QEVTS        8U

/* Number of transfer completion codes available */
#define EDMA_NUM_TCCS        64U

#endif /* _TMS320C6X */



#ifdef HOST_EMULATION
#define EDMA_NUM_PARAMS 128U
/* Number of Queues available for EDMA sub module for VAYU platform*/
#define EDMA_NUM_QUES   1U
/*-----------------------------------------------------------------------*/
/*  This is the number of logical channels that we need for this test    */
/*-----------------------------------------------------------------------*/
/* Maximum number of channels available */
#define NUM_MAX_CHANNELS    16U

/* Number of QDMA channels available */
#define NUM_QDMA_CHANNELS    8U

/* Number of EDMA channels available */
#define NUM_EDMA_CHANNELS    16U

/* Number of EDMA Events available */
#define NUM_EEVTS       16U

/* Number of QDMA Events available */
#define NUM_QEVTS        8U

/* Number of transfer completion codes available */
#define EDMA_NUM_TCCS        16U

#endif /* HOST_EMULATION */

#endif /*EDMACC_CONFIG_H_*/
