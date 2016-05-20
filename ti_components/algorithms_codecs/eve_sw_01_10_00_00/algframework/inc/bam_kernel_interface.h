/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 *  @file       bam_kernel_interface.h
 *
 *  @brief      This header defines interfaces for inserting kernels into BAM
 */

#ifndef BAM_KERNEL_INTERFACE_H
#define BAM_KERNEL_INTERFACE_H

#include "bam_types.h"

/**
 *  @brief      This structure provides to BAM contextual information about a kernel
 */
typedef struct
{

    /**
     *  @brief  System-wide unique identifier of a kernel.
     *  Initially set to 0 when the structure is defined in bam_<kernel_name>_helper_func.c
     *  Later it gets automatically initialized by BAM_initKernelDB() with the ID defined
     *  in the kernel database passed to the function BAM_initKernelDB().
     */
    BAM_KernelId kernelId;

    /**
     *  @brief  Size of the kernel's context structure BAM_<kernel_name>_Context, which is a private structure specific
     *  to the kernel that contains members such as pointers to the input, internal scratch, output data blocks
     *  as well as arguments for the compute kernel. This structure content must follow a specific pattern, described in the BAM user's guide.
     *  By convention, the structure is declared in file bam_<kernel_name>_helper_func.h and defined in file bam_<kernel_name>_helper_func.c
     *  The operator sizeof() should be used to initialize this member kernelContextSize for ease of code maintenance. Ex: sizeof(BAM_<kernel_name>_Context).
     */
    uint32_t kernelContextSize;

    /**
     *  @brief  Size of the kernels' arguments structure BAM_<kernel_name>_Args that is exposed to the application. Such structure becomes the list of parameters
     *  that will be passed to the kernel's compute function. Since it is exposed to the application, it must be declared in the kernel public
     *  header file which is bam_<kernel_name>.h . The way the application will communicate the argument's values is by providing pointers to
     *  initialized BAM_<kernel_name>_Args structures through the nodes' list passed to BAM_createGraph().
     *  The operator sizeof() should be used to initialize this member kernelArgSize for ease of code maintenance. Ex: sizeof(BAM_<kernel_name>_Args).
     */
    uint32_t kernelArgSize;

        /**
         * @brief Type of the processing core on which the kernel is implemented on: BAM_EVE_ARP32, BAM_EVE_VCOP, BAM_EVE_DSP_C64x, etc
         * */
    BAM_CoreType    coreType;

    /**
     *  @brief  Type of node the kernel must be associated to: BAM_NODE_COMPUTE, BAM_NODE_SOURCE, BAM_NODE_SINK.
     *
     *  @sa     BAM_NodeType
     */
    uint8_t nodeType;
    /**
     *  @brief  Number of input data blocks to the kernel.
     */
    uint8_t numInputDataBlocks;

    /**
     *  @brief  Number of output data blocks to the kernel.
     */
    uint8_t numOutputDataBlocks;

    /**
     *  @brief  Number of on-chip memory records required by the kernel during
     *          kernel execution. These memory segments are internal to the
     *          kernel and are used as scratch buffers or to store constant.
     */
    uint8_t numRecInternal;

} BAM_KernelInfo;

/**
 *  @brief      Type definition for BAM kernel GetMemRec function pointer
 */
typedef BAM_Status (*BAM_KernelGetMemRecFunc)(const void *kernelArgs, BAM_MemRec *memRecInternal,
        BAM_MemRec *memRecOutputDataBlock, uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

/**
 *  @brief      Type definition for BAM kernel SetMemRec function pointer
 */
typedef BAM_Status (*BAM_KernelSetMemRecFunc)(const BAM_MemRec *memRecInternal[],
        const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock, void *kernelContext, const void *kernelArgs);

/**
 *  @brief      Helper functions are defined on the core on which the constructor
 *              is executed: Arp32, M3, M4, A15.
 */

typedef struct
{
    /**
     *  @brief  Function to get kernels memory records. BAM will call it when
     *          BAM_createGraph() or BAM_optimizeGraph() is invoked by the applet.
     */
    BAM_KernelGetMemRecFunc getKernelMemRec;

    /**
     *  @brief  Function to set kernels memory records. BAM will call it when
     *          BAM_createGraph() or BAM_optimizeGraph() is invoked by the applet.
     */
    BAM_KernelSetMemRecFunc setKernelMemRec;

#if 0
    /**
     *  @brief  Function used to initialize members pertaining to the
     *          ‘constraints’ of the different datablocks structures that
     *          constitute either the input or output of the compute function.
     *          BAM will call it when BAM_initNodeProcArgs() is invoked by
     *          the applet.
     */
    BAM_KernelInitConstraintsFunc   initDataBlocksConstraints;
    /**
     *  @brief  Function used to check whether the argument values are valid.
     *          BAM will call it when BAM_initNodeProcArgs() is invoked by the
     *          applet.
     */
    BAM_KernelCheckArgsFunc         checkArgs;
#endif
} BAM_KernelHelperFuncDef;

/**
 *  @brief      Helper function database entry
 *
 */
typedef struct
{
    BAM_KernelInfo *kernelInfo;                 /**< @brief Pointer to the kernel's contextual information structure BAM_KernelInfo */
    BAM_KernelHelperFuncDef *kernelHelperFunc;  /**< @brief Pointer to the structure BAM_KernelHelperFuncDef that list the helper functions */
    char *name;                                 /**< @brief Unique name of the kernel */
    BAM_KernelId kernelId;                      /**< @brief Unique ID of the kernel */
} BAM_KernelHostDBdef;

/**
 *  @brief      Type definition for BAM kernel execute function pointer
 *
 */
typedef BAM_Status (*BAM_KernelFunc)(void *kernelContext);

/**
 *  @brief      Type definition for BAM kernel control function pointer
 *
 */
typedef BAM_Status (*BAM_KernelCtlFunc)(void *kernelContext, void *ctlArg);

/**
 *  @brief      Type definition for BAM kernel custom function pointer
 *
 */
typedef void (*BAM_KernelCustom)(uint16_t pBlock[]);


/**
 *  @brief      Specifies Various execute functions of the kernel
 *
 */
typedef struct
{
    /* These 5 functions are only defined on ARP32 (for EVE)
     */
    BAM_KernelFunc kernelInitInstance;  /**< One time initialization function of the kernel. Called the first time the graph is execture or after a context restore */
    BAM_KernelFunc kernelInitFrame;     /**< Initialization function of the kernel which should be called before every frame processing */
    BAM_KernelFunc kernelCompute;       /**< Kernel function which performs the computation on every block of data */
    BAM_KernelFunc kernelWait;          /**< Kernel Function which waits for the completion of computations performed */
    BAM_KernelCtlFunc kernelCtl;        /**< Control function of the kernel*/
    BAM_KernelCustom kernelCustom;      /**< Custom function of the kernel*/
} BAM_KernelExecFuncDef;

/**
 *  @brief      Execute function database entry
 *
 */
typedef struct
{
    BAM_KernelInfo *kernelInfo;             /**< @brief Pointer to the kernel's contextual information structure BAM_KernelInfo */
    BAM_KernelExecFuncDef *kernelExecFunc;  /**< @brief Pointer to the structure BAM_KernelExecFuncDef that list the execution functions  */
    char *name;                             /**< @brief Unique string denoting kernel name*/
    BAM_KernelId kernelId;                  /**< @brief Unique ID of the kernel*/
} BAM_KernelExecFuncDBdef;

/**
 *  @brief  This structure contains reference to the helper functions and execute functions databases.
 *          Reference to this structure can be passed to functions BAM_initKernelDB() and to member kernelDB of BAM_CreateGraphParams
 *          used by BAM_createGraph() and BAM_optimizeGraph().
 */
typedef struct
{
    const int32_t numBAMKernels;                    /**< @brief Number of kernels  recorded in the database */
    const BAM_KernelHostDBdef *kernelHostFuncDB;    /**< @brief Point to the BAM_KernelHostDBdef database */
    const BAM_KernelExecFuncDBdef *kernelExecFuncDB;    /**< @brief Point to the BAM_KernelExecFuncDBdef database */
} BAM_KernelDBdef;

#endif
