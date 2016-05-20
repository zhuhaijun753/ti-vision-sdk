#ifndef WHITE_BALANCE_H_
#define WHITE_BALANCE_H_

/************************************************************************************//**
* TI ISP Library Reference Code
* This library is a software module developed for simulation of vision and ISP
* algorithms ported on TI's embedded platforms
* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
* @file name    white_balance.h
* @brief        This header file provides necessary functions for vspAWB algorithm
* @author       Hrushikesh Garud (A0393878)
* @version      1.0
*
****************************************************************************************/

#include <stdbool.h>
# include "inc/Image_Data_Handling.h"
# include "inc/spatial_domain.h"

#define BLUE_GAIN_LIMIT (5000)
#define TRANSITION_WIDTH (1500)

typedef struct {
    float temperature;     //Illuminant CCT
    int   RGB[3];          //Illuminant color composition
}Illuminant;

typedef struct
{
    float gainFactors[3]; //WB gain factors for rgb channels
    float offsets[3];     //WB offsets for rgb channels
}WB_GainOffset;           //Slightly different structure over the platform code

typedef struct
{
    Illuminant    illum;
    WB_GainOffset gainOffset;
}WBParams; //Additional structure over the platform code can be considered as the suuset of structure wbHistory in the platform code

/************************************************************************************//**
* FUNCTION: void WB_estimateWbParams (Image * imgPtr, float percPix, WBParams * cP);
*
* This function is used to compute the correction parameters that should be used to  achieve the automatic
* white balance of the image by method as described in  Garud, H., Ray, A. K., Mahadevappa, M.,
* Chatterjee, J., Mandal, S., "A fast auto white balance scheme for digital pathology," Biomedical and
* Health Informatics (BHI), 2014 IEEE-EMBS International Conference on , vol., no., pp.153,156, 1-4 June 2014.
*
* Later the function can be updated to provide the AWB functionality as described in Garud, H.,
* Pudipeddi, U. K., Desappan K., Nagori, S. N., "A Fast Color Constancy Scheme for Automobile Video
* Cameras", International Conference on Signal Processing and Communications - 2014, (SPCOM 2014).
*
* Parameters:
*     [IN] imgPtr       pointer to the RGB image based on which  the AWB params need to be estimated
*     [IN]  percPix     tunable parameter to be used in estimation of illuminant
*     [OUT] cP          white balance parameters which can be used for image correction or retained
*                       as part of the history for temporal filtering part
*     [RET] 1/0         1 = successful completion of task
****************************************************************************************/
int WB_estimateWbParams(Image *imgPtr, float percPix, WBParams *cP);

/************************************************************************************//**
* FUNCTION: void WB_clipCorrectionParams (WBParams * cP);
*
* This function is used to perform post processing of the correction params details of which can be found in
* Garud, H., Pudipeddi, U. K., Desappan K., Nagori, S. N., "A Fast Color Constancy Scheme for Automobile Video
* Cameras", International Conference on Signal Processing and Communications - 2014, (SPCOM 2014).
*
* This function requires to set
* Parameters:
*     [IN/OUT]    cP          white balance parameters which can be used for image correction or retained
*                             as part of the history for temporal filtering part
*
****************************************************************************************/
void WB_clipCorrectionParams(WBParams *cP);

/************************************************************************************//**
* FUNCTION: void WB_computeGainOffsetValues (WBParams * cP);
*
* This function is used to compute the correction params details of which can be found in
* Garud, H., Pudipeddi, U. K., Desappan K., Nagori, S. N., "A Fast Color Constancy Scheme for Automobile Video
* Cameras", International Conference on Signal Processing and Communications - 2014, (SPCOM 2014).
*
* This function requires to set
* Parameters:
*     [IN/OUT]    cP          white balance parameters which can be used for image correction or retained
*                             as part of the history for temporal filtering part
*
****************************************************************************************/
void WB_computeGainOffsetValues(WBParams *cP);

/*****************************************************************************//**
* FUNCTION: int WB_estimateIlluminant (Image *imgPtr, float percPix, Illuminant *Illum);
* This function is used to estimate illuminant from image statistic using method described in
* Garud, H., Pudipeddi, U. K., Desappan K., Nagori, S. N., "A Fast Color Constancy Scheme for Automobile Video
* Cameras", International Conference on Signal Processing and Communications - 2014, (SPCOM 2014).
* Parameters:
*     [IN] imgPtr       pointer to the RGB image based on which the illuminant is to be estimated
*     [IN]  percPix     tunable parameter to be used in estimation of illuminant
*     [OUT] Illum       estimated illiminant, color composition and corrsponding CCT
****************************************************************************************/
int WB_estimateIlluminant(Image *imgPtr, float percPix, Illuminant *Illum);

/*****************************************************************************//**
* FUNCTION: int WB_computeLUT (WB_GainOffset *gainOffset, lookUpTable *LUT);
* This function is used to create the lookup tables used in WB correction process.
*     [IN] gainOffset   Gain and offset values to be used in WB correction process
*     [OUT] LUT         lookup tables 3 in number one for each channel
****************************************************************************************/
void WB_computeLUT(WB_GainOffset *gainOffset, lookUpTable *LUT);

/*****************************************************************************//**
* FUNCTION: int WB_computeLUT (WB_GainOffset *gainOffset, lookUpTable *LUT);
* This function performs the WB correction useng LUTs provided
*     [IN/OUT] imgPtr   Image which is to be white balance corrected
*     [IN] LUT          lookup tables, 3 in number one for each channel
****************************************************************************************/
int WB_wbAdjustment(Image *imgPtr, lookUpTable *LUT);

# endif
