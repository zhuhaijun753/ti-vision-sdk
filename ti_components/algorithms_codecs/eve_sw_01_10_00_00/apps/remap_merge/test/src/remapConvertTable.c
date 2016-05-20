/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2015 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <vcop.h>

#include "ti_file_io.h"

#include "evestarterware.h"
#include "alg_osal.h"

#include "xdais_types.h"

#include "iremap_merge_ti.h"

#include "convert_map.h"
#include "remap_common.h"
#include "remapConvertTable_config.h"
#include "remapConvertTable.h"

void remapNatc(uint8_t *srcY, uint8_t *srcUV, uint8_t *dstY, uint8_t *dstUV, RemapParms *params);
void stereovision_getLeftBlockMap(unsigned char **pSrcBlkMapLeft, unsigned int *blockMap_LEN, sConvertMap *mapStruct);
void stereovision_getRightBlockMap(unsigned char **pSrcBlkMapRight, unsigned int *blockMap_LEN, sConvertMap *mapStruct);

#define PRINT_ERRORE_MSG() TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

typedef struct IM_Fxns
{
    IVISION_Fxns * ivision;

} IM_Fxns;

int32_t remapConvertTable(sremapConvertTable_Config * gConfig_remapConvertTable) {
    RemapParms     *params;
    RemapStat       stat;
    uint32_t *coordMap;
    uint32_t lengthOfConvertedMap;
    uint8_t *convertedMap;
    char filepath[256];
    TI_FILE *fid;
    REMAP_MERGE_TI_CreateParams   createParams;

    uint32_t        srcStride, roiWidth, roiHeight, srcHeight;


    uint32_t         blockMap_LEN;
    uint8_t *srcBlkMap;
    int32_t i;
    uint32_t x,y;

    int32_t status= IALG_EOK;

    coordMap= NULL;
    srcBlkMap= NULL;
    convertedMap=  NULL;

    srcStride                           = gConfig_remapConvertTable->remapWidth;
    srcHeight                           = gConfig_remapConvertTable->remapHeight;
    roiWidth                            = gConfig_remapConvertTable->remapWidth;
    roiHeight                           = gConfig_remapConvertTable->remapHeight;

    params                              = &createParams.remapParams;

    params->maps.isSrcMapFloat          = 0;
    params->maps.srcFormat              = gConfig_remapConvertTable->colorFormat;
    params->maps.qShift                 = gConfig_remapConvertTable->qShift;
    params->interpolationLuma           = BILINEAR;
    params->interpolationChroma         = NN;
    params->rightShift                  = 0;
    params->sat_high                    = 255;
    params->sat_high_set                = 255;
    params->sat_low                     = 0;
    params->sat_low_set                 = 0;
    createParams.dstFormat              = gConfig_remapConvertTable->colorFormat;
    createParams.enableMerge            = 0;

    params->maps.srcImageDim.width      = srcStride;
    params->maps.srcImageDim.height     = srcHeight;
    params->maps.mapDim.width           = roiWidth;
    params->maps.mapDim.height          = roiHeight;

    params->maps.outputBlockDim.width   = gConfig_remapConvertTable->blockWidth;
    params->maps.outputBlockDim.height  = gConfig_remapConvertTable->blockHeight;

    blockMap_LEN = convertMap_bbApproach_getMemorysizeBlockMap(&params->maps);

    if ( ((int32_t)blockMap_LEN == -1) || (srcBlkMap = (uint8_t*)malloc(blockMap_LEN)) == NULL){
        status= IALG_EFAIL;
        goto EXIT;
    }

    memset(srcBlkMap, 0, blockMap_LEN);

    /*********  LUT generation for Left ************/
    /* Below is executed in case the TLU passed is in (X,Y) format, which require calling convertMap_bbApproach() */
    coordMap= (uint32_t*)malloc(sizeof(uint32_t)*2*srcStride*srcHeight);
    assert(coordMap!= NULL);

    params->maps.srcMap = (void*)coordMap;

#ifdef _IDENTITY_MAP
    {
        uint32_t r,c;
        for (r=0; r<srcHeight;r++) {
            for(c=0;c<srcStride;c++){
                *((uint32_t*)params->maps.srcMap + 2*c + 2*r*srcStride) = c << params->maps.qShift;
                *((uint32_t*)params->maps.srcMap + 2*c + 1 + 2*r*srcStride) = r << params->maps.qShift;
            }
        }
    }
#else
    sprintf(filepath, "%s", gConfig_remapConvertTable->inputMapFile);

    if (gConfig_remapConvertTable->inputMapFileFormat== 0) {
        if ((fid= FOPEN(filepath,"rb"))== NULL) {
            TEST_PRINTF("Unable to open file %s for reading\n", filepath);
            goto EXIT;
        }
        FREAD((void*)params->maps.srcMap, 4,  2*srcStride*srcHeight, fid); //////CCS FILE LOAD: Comment this line and set breakpoint if file format is binary. Data of size 2*srcStride*srcHeight bytes must be loaded to address params->maps.srcMap
        FCLOSE(fid);
    }
    else if (gConfig_remapConvertTable->inputMapFileFormat== 1){
        if ((fid= FOPEN(filepath,"rt"))== NULL) {
            TEST_PRINTF("Unable to open file %s for reading\n", filepath);
            goto EXIT;
        }
        for(i=0;i<srcStride*srcHeight;i++) {
            FSCANF(fid,"%d %d", &x, &y);
            *((uint32_t*)params->maps.srcMap + 2*i)= x;
            *((uint32_t*)params->maps.srcMap + 2*i + 1)= y;
        }
        FCLOSE(fid);
    }
    else {
        if ((fid= FOPEN(filepath,"rt"))== NULL) {
            TEST_PRINTF("Unable to open file %s for reading\n", filepath);
            goto EXIT;
        }
        for(i=0;i<srcStride*srcHeight;i++) {
            FSCANF(fid,"%d, %d,", &x, &y);
            *((uint32_t*)params->maps.srcMap + 2*i)= x;
            *((uint32_t*)params->maps.srcMap + 2*i + 1)= y;
        }
        FCLOSE(fid);
    }
#endif
    status =  convertMap_bbApproach(&params->maps, &stat, srcBlkMap);
    if (status == -1) {
        PRINT_ERRORE_MSG();
        goto EXIT;
    }

    sprintf(filepath, "%s", gConfig_remapConvertTable->outputMapFile);

    if (gConfig_remapConvertTable->outputMapFileFormat== 0) {

        if ((fid= FOPEN(filepath,"wb"))== NULL) {
            TEST_PRINTF("Unable to open file %s for writing\n", filepath);
            goto EXIT;
        }

        lengthOfConvertedMap= sizeof(params->maps) + sizeof(blockMap_LEN) + blockMap_LEN;
        FWRITE(&lengthOfConvertedMap, 1,  sizeof(lengthOfConvertedMap), fid);
        FWRITE((void*)&params->maps, 1,  sizeof(params->maps), fid);
        FWRITE((void*)&blockMap_LEN, 1,  sizeof(blockMap_LEN), fid);
        FWRITE((void*)srcBlkMap, 1,  blockMap_LEN, fid);    //////CCS FILE LOAD: Comment this line and set breakpoint if output file format is binary. Data of size blockMap_LEN bytes must be downloaded from address srcBlkMap.
        FCLOSE(fid);

    }
    else {
        /* Save the *.c version */
        if ((fid= FOPEN(filepath,"wt"))== NULL) {
            TEST_PRINTF("Unable to open file %s for writing\n", filepath);
            goto EXIT;
        }

        FPRINTF(fid,"#include \"remap_common.h\"\n\n");
        FPRINTF(fid,"far unsigned char %s_srcBlkMap[%d]={\n", gConfig_remapConvertTable->functionName, blockMap_LEN);
        for (i=0; i<blockMap_LEN-1; i++) {
            FPRINTF(fid, "%d,\n", srcBlkMap[i]);
        }
        FPRINTF(fid, "%d };\n\n", srcBlkMap[blockMap_LEN-1]);

        FPRINTF(fid,"void %s(unsigned char **pSrcBlkMap, unsigned int *blockMap_LEN, sConvertMap *mapStruct){\n\n", gConfig_remapConvertTable->functionName);
        FPRINTF(fid,"  *pSrcBlkMap= (unsigned char*)&%s_srcBlkMap[0];\n", gConfig_remapConvertTable->functionName);
        FPRINTF(fid,"  *blockMap_LEN= %d;\n", blockMap_LEN);
        FPRINTF(fid,"  mapStruct->outputBlockDim.width= %d;\n", params->maps.outputBlockDim.width);
        FPRINTF(fid,"  mapStruct->outputBlockDim.height= %d;\n", params->maps.outputBlockDim.height);
        FPRINTF(fid,"  mapStruct->maxInputBlockDim.width= %d;\n", params->maps.maxInputBlockDim.width);
        FPRINTF(fid,"  mapStruct->maxInputBlockDim.height= %d;\n", params->maps.maxInputBlockDim.height);
        FPRINTF(fid,"  mapStruct->maxInputBlockSize= %d;\n", params->maps.maxInputBlockSize);
        FPRINTF(fid,"  mapStruct->maxNumPixelsinTile= %d;\n", params->maps.maxNumPixelsinTile);
        FPRINTF(fid,"  mapStruct->qShift= %d;\n", params->maps.qShift);
        FPRINTF(fid,"  return;\n}\n");

        FCLOSE(fid);
    }

    EXIT:
    /*-----------------------------------------------------------------
                   Call algFree
       -----------------------------------------------------------------*/

    if ( srcBlkMap != NULL )
    {
        free(srcBlkMap);
    }

    if (coordMap != NULL) {
        free(coordMap);
    }

    if (convertedMap != NULL) {
        free(convertedMap);
    }

    return status;
}

void remapConvertTable_getBlockMap(uint8_t **srcBlkMap, uint32_t *blockMap_LEN, sConvertMap *maps, uint8_t *convertedMap) {

    uint32_t i;
    uint8_t *p;
    p= (uint8_t*)maps;

    for (i=0; i< sizeof(sConvertMap);i++)
        *p++= *convertedMap++;

    p= (uint8_t*)blockMap_LEN;
    for (i=0; i< sizeof(*blockMap_LEN);i++)
        *p++= *convertedMap++;

    *srcBlkMap= convertedMap;
}
