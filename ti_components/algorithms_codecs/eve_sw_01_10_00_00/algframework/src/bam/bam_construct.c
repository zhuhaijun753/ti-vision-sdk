/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 *  @file       bam_construct.c
 *
 *  @brief      This file defines functions for BAM Graph Construction
 */

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <string.h>
#include "vcop.h"
#pragma RESET_MISRA ("required")


#include "bam_kernel_interface.h"
#include "bam_construct_int.h"
#include "alg_osal.h"

static uint32_t BAM_logPerf[2];

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because all the GOTOs point to a single exit point */

/* Execute every kernel's init instance functions, which will initialize the internal memory records */
int32_t BAM_initGraphInstance(const BAM_GraphHandle graphHandle);

BAM_Status BAM_initKernelDB(const BAM_KernelDBdef *kernelDBDef)
{
    uint8_t i;
    const BAM_KernelExecFuncDBdef (*kernelExecFuncDbArray)[];
    const BAM_KernelHostDBdef (*kernelHostDbArray)[];
    BAM_Status status = BAM_S_SUCCESS;

    
    kernelExecFuncDbArray= (const BAM_KernelExecFuncDBdef (*)[])(void*)(kernelDBDef->kernelExecFuncDB);
    kernelHostDbArray= (const BAM_KernelHostDBdef (*)[])(void*)(kernelDBDef->kernelHostFuncDB);

    for (i = 0; i < kernelDBDef->numBAMKernels; i++)
    {
        if (((*kernelHostDbArray)[i].kernelId!= i) && ((*kernelExecFuncDbArray)[i].kernelId!= i)) {
            status= BAM_E_DATABASE_KERNELID;
            break;
        }
        (*kernelHostDbArray)[i].kernelInfo->kernelId = (*kernelHostDbArray)[i].kernelId;
    }

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    return status;
}


BAM_Status BAM_createGraph(BAM_CreateGraphParams *createParams, BAM_GraphHandle *pGraphHandle)
{
    BAM_GraphHandle graphHandle= (BAM_GraphHandle)createParams->graphMem;
    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;
    BAM_Status status = BAM_S_SUCCESS;
    uint32_t graphMemSize = 0;
    uint32_t numMemTabs = 0;
    BAM_NodeParamsInt *copyOfNodeList= (BAM_NodeParamsInt*)createParams->onChipScratchMem;
    BAM_MemRec (*memRec)[];

    _tsc_start();
    BAM_logPerf[0]= _tsc_gettime();

    memRec= (BAM_MemRec (*)[])createParams->onChipScratchMem;

    createParams->graphMemConsumed= 0;
    createParams->extMemConsumed= 0;
    createParams->onChipScratchMemConsumed= 0;

    status= BAM_copyNodeList(createParams, copyOfNodeList);
    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }

    status = BAM_fillKernelInfo(createParams->coreType, createParams->kernelDB, copyOfNodeList);
    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }

    /* Get memory required to store graph definition */
    status = BAM_getGraphMemSize(copyOfNodeList, createParams->edgeList, &graphMemSize, &numMemTabs);
    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }

    createParams->graphMemConsumed+= graphMemSize;

    createParams->onChipScratchMemConsumed= (numMemTabs * sizeof(BAM_MemRec)) + ((numMemTabs + BAM_NUM_GUARD_PACKETS)*sizeof(BAM_Packet));
            
    if ((createParams->graphMemConsumed > createParams->graphMemSize) || (createParams->onChipScratchMemConsumed >  createParams->onChipScratchMemSize) || (createParams->extMemConsumed >  createParams->extMemSize))
    {
        status= BAM_E_INVALID_MEM_SIZE;
        goto Exit;
    }

    status = BAM_initGraph(copyOfNodeList, createParams->edgeList, graphHandle, graphMemSize);
    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }

    /* If smartMemAlloc disabled, we copy the memory records that is passed from the application after verifying that the pointer to the memory records array
     * and number of memory records match the precomputed values */
    if (createParams->useSmartMemAlloc== false)  {
        if (createParams->memRec== NULL) {
            status= BAM_E_INVALID_PTR;
            goto Exit;
        }
        else {
            memcpy((*memRec), createParams->memRec,  createParams->numMemRec * sizeof(BAM_MemRec));
        }
    }

    graphDef->memRec= (*memRec);
    graphDef->packetPool= (BAM_Packet*)(void*)(&((*memRec)[numMemTabs]));

    graphDef->thisPtr= graphDef;
    graphDef->kernelDBDef = createParams->kernelDB;
    graphDef->numMemTabs= numMemTabs;

    createParams->memRec= (*memRec);

    graphDef->graphMemSize= graphMemSize;
    graphDef->extMem= createParams->extMem;

    if (createParams->optimizeBlockDim== false) {
        status= createParams->initKernelsArgsFunc(createParams->initKernelsArgsParams, &createParams->blockDimParams);
        if (status != BAM_S_SUCCESS) {
            goto Exit;
        }
        status= BAM_updateNodes(graphHandle, createParams, true);
    }
    else {
        if (createParams->useSmartMemAlloc== true){
            status= BAM_optimizeGraph(graphHandle, createParams);
        }
        else {
            status= BAM_E_UNSUPPORTED;
        }
    }

    if (status != BAM_S_SUCCESS) {
        goto Exit;
    }

    /* Will call each kernel's init instance function. This will intialize the internal memory records that were allocated to store PREG values. */
    BAM_initGraphInstance(graphHandle);

    /* Copy persistent internal memrec into graphDef->extMem using memcpy */
    BAM_copyIntMemRec2ExtMem(graphHandle);

    createParams->numMemRec= graphDef->numMemTabs; /* BAM_updateNodes() has updated graphDef->numMemTabs to the actual number of memory records used */
    *pGraphHandle= graphHandle;

    Exit:
    BAM_logPerf[1]= _tsc_gettime();
    
    return (status);
}

BAM_Status BAM_getStats(BAM_GraphHandle graphHandle, BAM_Statistics *stat) {

    BAM_Status status = BAM_S_SUCCESS;

    stat->createGraph.lastCycles= BAM_getGraphCreateCycles();
    stat->kernelsInit.lastCycles= BAM_getKernelsInitCycles();
    stat->kernelsExec.lastCycles= BAM_getKernelsExecCycles();

    return status;
}


uint32_t BAM_getGraphCreateCycles(void) {
    return (BAM_logPerf[1] - BAM_logPerf[0]);
}

BAM_Status BAM_getVersion(uint16_t *major, uint16_t *minor, uint16_t *patch) {
    BAM_Status status = BAM_S_SUCCESS;

    *major= BAM_MAJOR_VERSION;
    *minor= BAM_MINOR_VERSION;
    *patch= BAM_PATCH_VERSION;

    return status;
}

BAM_Status BAM_printMemRec(BAM_MemRec memRec[], uint32_t numMemRec) {
    uint8_t (*base)[];
    BAM_Status status = BAM_S_SUCCESS;
    char* typeStr[]={"input", "output", "internal"};
    char* attrStr[]={"scratch", "persist", "const"};

    uint16_t i;

    uint8_t oldNodeIndex= memRec[0].attrs.nodeIndex;

    PRINTF("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    PRINTF("#\tnode            \ttype    \tattr   \tiBufAL Start\tiBufAL End\tlength\tiBufAH Start\tiBufAH End\tlength\tWbuf Start\tWbuf End\tlength\tDMEM Start\tDMEM End\tlength\n");
    PRINTF("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (i= 0; i<numMemRec; i++) {

        base= (uint8_t (*)[])memRec[i].base;

        if (memRec[i].attrs.nodeIndex!=  oldNodeIndex) {
            PRINTF("\n");
            oldNodeIndex= memRec[i].attrs.nodeIndex;
        }

        if (memRec[i].space==  BAM_MEMSPACE_IBUFLA) {
            PRINTF("%2d\t%-22.22s\t%-8.8s\t%-7.7s\t0x%8.8x\t0x%8.8x\t%5.5d\n",
                    i, memRec[i].name, typeStr[memRec[i].attrs.memType], attrStr[memRec[i].attrs.memAttrs],
                    memRec[i].base, &((*base)[memRec[i].size]), memRec[i].size);
        }
        else if (memRec[i].space==  BAM_MEMSPACE_IBUFHA) {
            PRINTF("%2d\t%-22.22s\t%-8.8s\t%-7.7s\t          \t          \t     \t0x%8.8x\t0x%8.8x\t%5.5d\n",
                    i, memRec[i].name, typeStr[memRec[i].attrs.memType], attrStr[memRec[i].attrs.memAttrs],
                    memRec[i].base, &((*base)[memRec[i].size]), memRec[i].size);
        }
        else if (memRec[i].space==  BAM_MEMSPACE_WBUF) {
            PRINTF("%2d\t%-22.22s\t%-8.8s\t%-7.7s\t          \t          \t     \t          \t          \t     \t0x%8.8x\t0x%8.8x\t%5.5d\n",
                    i, memRec[i].name, typeStr[memRec[i].attrs.memType], attrStr[memRec[i].attrs.memAttrs],
                    memRec[i].base, &((*base)[memRec[i].size]), memRec[i].size);
        }
        else if (memRec[i].space==  BAM_MEMSPACE_DMEM) {
            PRINTF("%2d\t%-22.22s\t%-8.8s\t%-7.7s\t          \t          \t     \t          \t          \t     \t          \t          \t     \t          \t          \t     \t0x%8.8x\t0x%8.8x\t%5.5d\n",
                    i, memRec[i].name, typeStr[memRec[i].attrs.memType], attrStr[memRec[i].attrs.memAttrs],
                    memRec[i].base, &((*base)[memRec[i].size]), memRec[i].size);
        }
        else {
            PRINTF("%2d\t%-22.22s\t%-8.8s\t%-7.7s\t          \t          \t     \t          \t          \t     \t0x%8.8x\t0x%8.8x\t%5.5d\n",
                    i, "Invalid Record", "Invalid", "Invalid",
                    memRec[i].base, &((*base)[memRec[i].size]), memRec[i].size);
            }

    }

    PRINTF("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

    return status;
}

/* RESET_MISRA("15.1")  -> Reset rule 15.1*/


