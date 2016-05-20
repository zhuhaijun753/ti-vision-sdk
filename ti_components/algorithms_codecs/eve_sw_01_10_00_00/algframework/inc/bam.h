/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @mainpage BAM API Reference
*
* @section Introduction
*
* BAM is a framework that that makes development of an EVE applet
* easier. An applet is a small application developed around a vision algorithm that accepts one or more
* image/data frames at its input and outputs. A frame is composed of more than one data unit. A data unit
* being a pixel in case of image/vision processing.
*
* @subsection xxx Purpose and Scope
* The purpose of this document is to detail the BAM APIs for the EVE applet developement.
*
* @subsection aaa Terms and Abbreviations
*   -# BAM:  Block-based Acceleration Manager
*   -# API:  Application Programmer Interface
*   -# EDMA: Enhanced Direct Memory Access 
*
* @subsection References
*    -# BAM user's guide July, 2014
*
*/

/**
 *  @file       bam.h
 *
 *  @brief      This header defines types & constants shared by all implementations
 *              of the "generic" algorithm interface.
 */

#ifndef _BAM_H_
#define _BAM_H_

#include "bam_construct.h"
#include "bam_execute.h"
#include "eve_edma_bam_interface.h"
#include "eve_qdma_interface.h"

#endif
