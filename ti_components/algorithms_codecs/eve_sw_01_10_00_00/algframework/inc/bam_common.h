/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 *  @file       bam_common.h
 *
 *  @brief      This header defines common definitions for BAM
 */

#ifndef BAM_COMMON_H
#define BAM_COMMON_H

#include "bam_types.h"
#include "bam_kernel_interface.h"

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

/**
 * These version numbers are returned by BAM_getVersion()
 */
#define BAM_MAJOR_VERSION 2 /**< Major version number */
#define BAM_MINOR_VERSION 5 /**< Minor version number */
#define BAM_PATCH_VERSION 1 /**< Patch version number */

#define MAX_NODES   128U                     /**< Maximum number of possible nodes in a graph */
#define BAM_END_NODE_MARKER 255U             /**< End of the nodes in a graph */
#define BAM_NULL_NODE              254U             /**< To connect unused output port from compute node */
#define BAM_MAX_NODE_INPUT_OUTPUT     10U    /**< Maximun number of possible input output nodes>*/

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/*Function-like macro definition */
/* Deviation allowed since it is a single statement best implemented through a macro function */
#define BAM_ALIGN_WORD(s) (((s) + 3UL) & (uint32_t)(~3UL))  /**< BAM Word alignment */
/* RESET_MISRA("19.7")  -> Reset rule 19.7*/

#define BAM_IMGBUF_GAP 0x20000

/**
 *  @brief      Generic byte pointer type.
 */
typedef uint8_t *BAM_BytePtr;

/**
 *  @brief      Specifies the type of Data Block connection to a kernel.
 */
typedef enum
{
    BAM_INPUT = 1, /**< Input data block */
    BAM_OUTPUT = 2 /**< Output data block */
} BAM_DataBlockDir;

/**
 *  @brief      Specifies the type of node in a graph.
 */
typedef enum
{
    BAM_NODE_SOURCE = 1, /**< Source node */
    BAM_NODE_SINK = 2, /**< Sink node */
    BAM_NODE_COMPUTE = 3 /**< Compute node */
} BAM_NodeType;

/**
 *  @brief      Specifies properties of a kernel graph. This structure is
 *              passed while creating a graph definition.
 */
typedef struct
{
    /**
     *  @brief  Number of source nodes in the graph.
     */
    uint32_t numSourceNodes;

    /**
     *  @brief  Number of sink nodes in the graph.
     */
    uint32_t numSinkNodes;

    /**
     *  @brief  Number of compute nodes in the graph.
     */
    uint32_t numComputeNodes;

    /**
     *  @brief  Number of data blocks in the graph.
     */
    uint32_t numDataBlocks;

} BAM_GraphDefParams;

#define BAM_GRAPH_INITIALIZED       1   /**< Status of the BAM graph showing initialized state*/
#define BAM_GRAPH_VERIFY_SUCCESS    2   /**< Status of the BAM graph verification showing success*/
#define BAM_GRAPH_VERIFY_FAILURE    3   /**< Status of the BAM graph verification showing failure*/

/**
 *  Status of the BAM graph Handle
 */
typedef uint32_t BAM_GraphDefStatus;

/**
 * Graph handle. Actual prototype is defined else where
 */
typedef void *BAM_GraphHandle;

/**
 *  @brief      Specifies the node parameters
 */
typedef struct
{
    uint8_t         nodeIndex;      /**< @brief Index of the node in the graph. Arbitrarily defined by the application. */
    BAM_KernelId    kernelId;       /**< @brief Unique ID of the kernel associated to the node, must correspond to an ID in the kernel database pointed by kernelDB from BAM_CreateGraphParams. */
    void            *kernelArgs;    /**< @brief Pointer to the kernel's arguments structure with initialized values */
} BAM_NodeParams;


/**
 *  @brief      Specifies the edge parameters
 *              which is a data connection between two nodes
 */
typedef struct
{
    struct {
        uint8_t id; /**< @brief Id of the upstream node */
        uint8_t port; /**< @brief Data port of the upstream node, this edge connects to */
    } upStreamNode; /**< @brief Upstream node id and port the edge connects to */
    /**
     *   @brief Downstream node id and port the edge connects to
     */
    struct {
        uint8_t id; /**< @brief Id of the downstream node */
        uint8_t port; /**< @brief Data port of the downstream node, this edge connects to */
    } downStreamNode; /**< @brief Downstream node id and port the edge connects to */
} BAM_EdgeParams;

/**
 *  @brief      Specifies the block dimension structure passed to BAM_createGraph()
 *   This structure contains block dimension variables that BAM_createGraph() will update during the search
 *   for their optimal values as well as step size used for the update process.
 *   These variables are blockWidth and blockHeight, that are updated using blockWidthStep and blockHeightStep.
 */
typedef struct {
    int32_t blockWidth;        /**< @brief Processing block width */
    int32_t blockHeight;       /**< @brief Processing block height */
    int32_t blockWidthStep;    /**< @brief Step size used to increment the processing block width during the optimization process */
    int32_t blockHeightStep;   /**< @brief Step size used to increment the processing block height during the optimization process */
    int32_t blockWidthDivisorOf; /**< @brief Integer the blockWidth must be divisor of, usually a processing ROI's width, 0 means there is no divisor constraint*/
    int32_t blockHeightDivisorOf; /**< @brief Integer the blockHeight must be divisor of, usually a processing ROI's height, , 0 means there is no divisor constraint*/
} BAM_BlockDimParams;

/**
 *  @brief      Type definition for BAM_InitKernelsArgsFunc function pointer
 *   Such function is defined by the application and passed to BAM_createGraph() as callback
 */
typedef BAM_Status (*BAM_InitKernelsArgsFunc)(void *customArg, BAM_BlockDimParams *blockDimParams);

/**
 *  @brief      Specifies the structure passed to BAM_createGraph()
 */
typedef struct
{
    BAM_CoreType           coreType;   /**< @brief Type of the processing core on which the graph will execute. */
    BAM_KernelDBdef      *kernelDB;   /**< @brief Point to the database of processing kernels that the graph nodes will use. The database must have been previously initialized using BAM_initKernelDB(). */
    BAM_NodeParams       *nodeList;             /**< @brief Point to the list of parameters for the nodes that make up the graph */
    BAM_EdgeParams       *edgeList;             /**< @brief Point to the list of parameters for the edges that makes up the graph */
    void            *graphMem;                  /**< @brief Point to on chip memory in which BAM will store the graph object, for EVE, it is recommended to be in DMEM */
    uint32_t        graphMemSize;               /**< @brief Size in bytes of the block of memory pointed by graphMem */
    uint32_t        graphMemConsumed;           /**< @brief Upon returning from BAM_createGraph() the actual number of bytes consumed in graphMem is available here, if BAM_creategraph() returns BAM_E_BLOCK_DIM_TOO_BIG then check if it is because graphMemSizeConsumed > graphMemSize */
    void            *onChipScratchMem;          /**< @brief Point to on chip scratch memory in which BAM will store the graph object, for EVE, it is recommended to be DMEM */
    uint32_t        onChipScratchMemSize;       /**< @brief Size in bytes of the block of memory pointed by onChipScratchMem */
    uint32_t        onChipScratchMemConsumed;   /**< @brief Upon returning from BAM_createGraph() the actual number of bytes consumed in onChipScratchMem is available here, if BAM_creategraph() returns BAM_E_BLOCK_DIM_TOO_BIG then check if it is because onChipScratchMemConsumed > onChipScratchMemSize */
    void            *extMem;                    /**< @brief Point to external memory (DDR usually ) that will be used to store context saving restore data*/
    uint32_t        extMemSize;                 /**< @brief Size in bytes of the block of memory pointed by extMem */
    uint32_t        extMemConsumed;             /**< @brief Upon returning from BAM_createGraph() the actual number of bytes consumed in extMem is available here , if BAM_creategraph() returns BAM_E_OUT_OF_MEM then check if it is because extMemConsumed > extMemSize */
    BOOL            useSmartMemAlloc;          /**< @brief 0: memory allocation is done dynamically and list of memory records is available in memRec after BAM_createGraph() returns. Location of the list will be in onChipScratchMem so application should save it before recycling onChipScratchMem for other purpose \n
                                                         1: memory allocation is done statically by using the list of memory records pointed by memRec. */
    BAM_MemRec      *memRec;                    /**< @brief Point to list of memory records. When useSmartMemAlloc=true, it is produced by BAM_createGraph(), when useSmartMemAlloc=1, caller must initialize it to a list of existing memory records */
    uint32_t        numMemRec;                  /**< @brief When useSmartMemAlloc== true, number of memory records returned by BAM_createGraph(). When useSmartMemAlloc=1, this member is not relevant */
    BOOL            optimizeBlockDim;           /**< @brief If optimizeBlockDim== true, BAM_createGraph() will search for the optimium block dimensions and return them in blockDimParams, note that useSmartMemAlloc must be set to true otherwise BAM_E_UNSUPPORTED is returned */
    BAM_InitKernelsArgsFunc initKernelsArgsFunc; /**<@brief Pointer to user-defined callback function invoked by BAM_createGraph() to initialize all the kernel arguments present in nodeList
                                                            When optimizeBlockDim== false, it is called only one time. When optimizeBlockDim== true, it is called more than one time */
    void            *initKernelsArgsParams;     /**<@brief Point to the custom argument structure passed to the user defined callback function initKernelsArgsFunc()  */
    BAM_BlockDimParams blockDimParams;          /**<@brief Pointer to this sctructure is passed to the callback function initKernelsArgsFunc() and specifies the recommended processing block width and height.
                                                        Note that initKernelsArgsFunc() can modify these values by incremeting or decrementing by blockWidthStep or blockHeightStep in order to meet some constraints.
                                                        The final values picked up initKernelsArgsFunc() are returned into blockDimParams for the caller to use.
                                                        When optimizeBlockDim== true, BAM_createGraph() modifies the values in blockDimParams in search for the optimal ones.
                                                        */
} BAM_CreateGraphParams;

/**
 *  @brief      Structure that will hold timing information of a particular stage after calling BAM_getTimingInfo()
 */
typedef struct {
    uint32_t numExecs; /**< Number of times this stage was executed, CURRENTLY DISABLED */
    uint32_t minCycles; /**< minimum of all the execution times collected so far, CURRENTLY DISABLED  */
    uint32_t maxCycles; /**< minimum of all the execution times collected so far, CURRENTLY DISABLED   */
    uint32_t averCycles; /**< average of all the execution times collected so far, CURRENTLY DISABLED   */
    uint32_t lastCycles; /**< execution time of the last execution */
} BAM_TimingInfo;

/**
 *  @brief  Structure used by BAM_getStats() to communicate benchmark stats to the caller
 */
typedef struct {
    BAM_TimingInfo createGraph; /**< Stats corresponding to BAM_createGraph() */
    BAM_TimingInfo kernelsInit; /**< Stats corresponding to the execution of all kernelCtl(), kernelInitInstance(), kernelInitFrame() functions in the graph */
    BAM_TimingInfo kernelsExec; /**< Stats corresponding to the execution of all kernelCompute() and kernelWait() functions in the graph */
} BAM_Statistics;

#define BAM_INVALID_INDEX   ((uint8_t)0xFF) /**< BAM Invalid Node Index */

/**
 *  @brief      Return benchmark statistics into the structure pointed by stat.
 *  @param[in]  graphHandle      Pointer to the graph handle
 *  @param[in]  stat  Points to the structure of type BAM_Statistics
 *  @retval     BAM_S_SUCCESS   All timing information could be collected.
 *  @retval     BAM_E_UNSUPPORTED The library was built with BAM_LOGPERF undefined so no timing information could be collected.
 */
BAM_Status BAM_getStats(BAM_GraphHandle graphHandle, BAM_Statistics *stat);

/**
 *  @brief      Return BAM library version made of a major, minor and patch numbers
 *  @param[out]  major  Pointer to the placehodler of the major version number
 *  @param[out]  minor  Pointer to the placehodler of the major version number
 *  @param[out]  patch  Pointer to the placehodler of the patch version number
 *  @retval     BAM_S_SUCCESS
 */
BAM_Status BAM_getVersion(uint16_t *major, uint16_t *minor, uint16_t *patch);

/**
 *  @brief      Print to the console all details (node name, type, attribute, base pointer) about each memory record in the table pointed by memRec
 *              This is useful for inspecting the memory allocation produced by the smart memory allocator and decide to do any manual fine-tuning
 *              by manually assigning some kernel's memory records to specific memory space, in the kernel's getMemRec function.
 *  @param[in]  memRec  Pointer to the array of memory records to be printed
 *  @param[in]  numMemRec  Number of memory records in the array
 *  @retval     BAM_S_SUCCESS
 */
BAM_Status BAM_printMemRec(BAM_MemRec memRec[], uint32_t numMemRec);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BAM_COMMON_H */
