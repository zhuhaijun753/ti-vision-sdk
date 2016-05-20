/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 *  @file       bam_types.h
 *
 *  @brief      This header defines common defenitions for BAM
 */

#ifndef BAM_TYPES_H
#define BAM_TYPES_H

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#pragma RESET_MISRA ("required")

/* for zebu_uart defenition of PRINTF */
#pragma CHECK_MISRA ("none")
#include "evestarterware.h"
#pragma RESET_MISRA ("required")

#include "alg_osal.h"


/**
 *  @brief      Status returned from BAM APIs.
 */
typedef int32_t BAM_Status;

/**
 *  @brief      Unique identifier for a kernel.
 */
typedef uint32_t BAM_KernelId;

/**
 *  @brief      Type of core. It takes one of the values defined by macros
 *               in bam_construct.h.
 *
 */
typedef uint8_t BAM_CoreType;

/**
 * @brief Memory space in which the data block should be allocated in.
 */
typedef int32_t BAM_MemSpace;

#define VCOP_MEMSPACE_NONE       (-1)                   /**< BAM memory space NONE*/
#define BAM_MEMSPACE_STARTIDX    0                      /**< BAM memory space start index*/
#define BAM_MEMSPACE_IBUFLA      (BAM_MEMSPACE_STARTIDX)/**< BAM memory space IBUFLA*/
#define BAM_MEMSPACE_IBUFHA      1                      /**< BAM memory space IBUFHA*/
#define BAM_MEMSPACE_IBUFLB      2                      /**< BAM memory space IBUFLB*/
#define BAM_MEMSPACE_IBUFHB      3                      /**< BAM memory space IBUFHB*/
#define BAM_MEMSPACE_WBUF        4                      /**< BAM memory space WBUF*/
#define BAM_MEMSPACE_ANY_VCOPBUF 5                      /**< BAM memory space in any VCOP buffers */
#define BAM_MEMSPACE_DMEM        6                      /**< BAM memory space DMEM*/
#define BAM_MEMSPACE_EXTMEM      7                      /**< BAM memory space External memory*/
#define BAM_MEMSPACE_NUM         (BAM_MEMSPACE_EXTMEM+1)/**< Number of supported BAM memory spaces*/

/**
 *  @brief      Enumerated type of BAM Indices for different memory spaces.
 */
enum BAM_MemSpaceIdx_Enum
{
    BAM_MEMSPACE_EVEMEM_STARTIDX = BAM_MEMSPACE_STARTIDX,   /**< Starting index of the EVE memories */
    BAM_MEMSPACE_VCOPMEM_STARTIDX = BAM_MEMSPACE_STARTIDX,  /**< Starting index of the VCOP memories */
    BAM_MEMSPACE_VCOPMEM_ENDIDX = BAM_MEMSPACE_WBUF,        /**< Ending index of the VCOP memories */
    BAM_MEMSPACE_EVEMEM_ENDIDX = BAM_MEMSPACE_DMEM,         /**< Ending index of the EVE memories*/

    BAM_MEMSPACE_EXTMEM_STARTIDX = BAM_MEMSPACE_EXTMEM,     /**< Starting index of the External memory */
    BAM_MEMSPACE_EXTMEM_ENDIDX = BAM_MEMSPACE_EXTMEM        /**< Ending index of the External memory */
};

/**
 *  @brief      Enumerated type of BAM memory attributes.
 */
typedef enum
{
    BAM_MEMATTRS_SCRATCH,   /**< Memory space with this attribute CAN be re-used by other nodes to allow overlay and ARE NOT saved & restored during context switching*/
    BAM_MEMATTRS_PERSIST,   /**< Memory space with this attribute CANNOT be re-used by other nodes and ARE saved & restored  during context switching */
    BAM_MEMATTRS_CONST      /**< Memory space with this attribute CANNOT be re-used by other nodes and ARE NOT saved & restored  during context switching */
} BAM_MemAttrs_Enum;

/**
 *  @brief      BAM memory types.
 */
typedef enum
{
    BAM_MEMTYPE_NODEMEM_INPUT,      /**< Type of Memory space to be used for input data */
    BAM_MEMTYPE_NODEMEM_OUTPUT,     /**< Type of Memory space to be used for output data */
    BAM_MEMTYPE_NODEMEM_INTERNAL    /**< Type of Memory space to be used for internal data*/
} BAM_MemType_Enum;

/**
 *  @brief      Specifies BAM memory properties.
 */
typedef struct
{
    uint8_t nodeIndex;  /**< @brief For internal BAM usage, Index of the node in the graph */
    uint8_t memType;    /**< @brief For internal BAM usage, Type of the memory: BAM_MEMTYPE_NODEMEM_INPUT,  BAM_MEMTYPE_NODEMEM_OUTPUT, BAM_MEMTYPE_NODEMEM_INTERNAL */
    uint8_t dataBlockIndex;    /**< @brief For internal BAM usage, Corresponding data block index for backward reference  */
    uint8_t memAttrs;   /**< @brief Attribute of the memory:\n 
   		BAM_MEMATTRS_SCRATCH: Memory space with this attribute CAN be re-used by other nodes to allow overlay and ARE NOT saved & restored during context switching.\n
   		BAM_MEMATTRS_PERSIST: Memory space with this attribute CANNOT be re-used by other nodes and ARE saved & restored  during context switching.\n
   		BAM_MEMATTRS_CONST: Memory space with this attribute CANNOT be re-used by other nodes and ARE NOT saved & restored  during context switching.
   */
} BAM_MemAttrs;

/**
 *  @brief      Specifies BAM memory requirements.
 */
typedef struct
{
    uint32_t size;      /**< @brief size in bytes of the memory block decribed by this record */
    int32_t alignment;  /**< @brief Alignment of the block's start address in memory */
    BAM_MemSpace space; /**< @brief Automatically filled by BAM, location where the block must be allocated: VCOP image buffer, working memories, ARP32 data memory or external memory */
    BAM_MemAttrs attrs; /**< @brief Specifies BAM memory attributes */
    void *base;         /**< @brief Can be automatically filled by BAM if static memory allocation disabled , point to the allocated block. */
    void *ext;          /**< @brief For internal usage: extra pointer used for context save/restore of persistent internal memory */
    char *name;         /**< @brief Automatically filled by BAM, pointer to the string of the node to which this memory record belongs, for easy tracing during debugging */
} BAM_MemRec;

/**
 *  @brief      Specifies a BAM 2-dimensional point.
 */
typedef struct
{
    int32_t x;  /**< @brief Offset (in bytes) in x-direction */
    int32_t y;  /**< @brief Offset (in lines) in y-direction */
} BAM_Point;

/**
 *  @brief      Specifies a BAM rectangle.
 */
typedef struct
{
    BAM_Point topLeft;      /**< @brief Top left corner of the retctangle */
    BAM_Point bottomRight;  /**< @brief Bottom right corner of the retctangle */
} BAM_Rect;

/**
 *  @brief      Struct describing a buffer size
 *
 *  @remarks    More advanced memory types (e.g. tiled memory) cannot
 *              indicate buffer size using a simple integer, but rather
 *              must indicate memory size using a width and height.
 */
typedef struct
{
    uint32_t bytes;         /**< @brief Number of bytes in the buffer */
    uint32_t width;         /**< @brief Width of the ROI processed (in bytes). */
    uint32_t height;        /**< @brief Height of the ROI processed (in lines).  */
    int32_t pitch;          /**< @brief Pitch of the buffer */
    uint32_t reserved[2];   /**< @brief Reserved for later use */
} BAM_BufSize;

/**
 *  @brief      A generic buffer descriptor
 *
 *  @remarks    None
 */

typedef struct
{
    void *buf;                  /**< @brief Pointer to the buffer          */
    BAM_BufSize bufSize;        /**< @brief Descriptor for Size of the buffer             */
    BAM_Point sliceOffset;       /**< @brief Current Slice offset for algorithm processing, expressed in terms of offset x and offset y.*/
    BAM_Rect reservedOffset;    /**< @brief Current active region of input beyond which data may be junk */
                                /** @brief Used internally by the algorithm for padding */
    int32_t formatType;         /**< @brief Format of the buffer data - for example NV12 */
    int32_t contentType;        /**< @brief Content of the buffer - for example Y component of NV12 */
    uint32_t reserved[2];       /**< @brief Reserved for later use */
} BAM_BufDesc;


/**
 *  @brief      A generic buffer descriptor
 *
 *  @remarks    None
 */
typedef struct
{
    uint32_t size;          /**< @brief Size of this structure */
    uint32_t numBufs;       /**< @brief Number of elements of type BAM_BufDesc in the list */
    uint32_t reserved[2];   /**< @brief Reserved for later use */
    BAM_BufDesc *bufDesc;   /**< @brief Pointer to array of BAM_BufDesc */
} BAM_BufDescList;

/**
 *  @brief      BAM input buffer description list
 *
 *  @remarks    None
 */
typedef BAM_BufDescList BAM_InBufs;

/**
 *  @brief      BAM output buffer description list
 *
 *  @remarks    None
 */
typedef BAM_BufDescList BAM_OutBufs;

/**
 *  @brief      BAM input arguments to be passed in the algorithm process
 *
 *  @remarks    None
 */
typedef struct
{
    uint32_t size;      /**< @brief Size of this structure */
    int32_t sliceIndex; /**< @brief Index of the slice in the frame to be processed */
} BAM_InArgs;

/**
 *  @brief      BAM output arguments to be passed in the algorithm process
 *
 *  @remarks    None
 */
typedef struct
{
    uint32_t size;  /**< @brief Size of this structure */
} BAM_OutArgs;

/**
 * Do not change these values. There are aligned with ievealg interface defenitions
 */
#define BAM_E_BASE                       0                  /**< BAM error base*/
#define BAM_S_SUCCESS                   (BAM_E_BASE)        /**< BAM error code showing success*/
#define BAM_E_FAIL                      (BAM_E_BASE - 1)    /**< BAM error code showing failure*/
#define BAM_E_FAIL_RUNTIME              (BAM_E_BASE - 2)    /**< BAM error code showing runtime failure*/
#define BAM_E_UNSUPPORTED               (BAM_E_BASE - 3)    /**< BAM error code showing unsupported feature*/

/**
 * Add additional error codes if required.
 */
#define BAM_E_CUSTOMFAILEND             (-256)                      /**< BAM custom error code end */
#define BAM_E_INVALID_MEM_SIZE          (BAM_E_CUSTOMFAILEND - 0)   /**< BAM error code returned by BAM_createGraph() in case one of the member graphMemSize, onChipScratchMemSize or extMemSize of the structure BAM_CreateGraphParams is too small  */
#define BAM_E_INVALID_PTR               (BAM_E_CUSTOMFAILEND - 1)   /**< BAM error code showing invalid pointer*/
#define BAM_E_INVALID_NODE_INDEX        (BAM_E_CUSTOMFAILEND - 2)   /**< BAM error code showing invalid node index*/
#define BAM_E_INVALID_NODE_COUNT        (BAM_E_CUSTOMFAILEND - 3)   /**< BAM error code showing invalid node count*/
#define BAM_E_INVALID_STATUS            (BAM_E_CUSTOMFAILEND - 4)   /**< BAM error code showing invalid status*/
#define BAM_E_INVALID_NODE_TYPE         (BAM_E_CUSTOMFAILEND - 5)   /**< BAM error code showing invalid node type*/
#define BAM_E_INVALID_DATA_BLOCK_INDEX  (BAM_E_CUSTOMFAILEND - 6)   /**< BAM error code showing invalid data block index*/
#define BAM_E_INVALID_DATA_BLOCK_DIR    (BAM_E_CUSTOMFAILEND - 7)   /**< BAM error code showing invalid datablock direction*/
#define BAM_E_OUT_OF_MEM                (BAM_E_CUSTOMFAILEND - 8)   /**< BAM error code showing insufficient memory */
#define BAM_E_BLOCK_DIM_TOO_BIG         (BAM_E_CUSTOMFAILEND - 9)   /**< BAM error code showing processing block dimension too big */
#define BAM_E_BLOCK_DIM_NOT_FOUND         (BAM_E_CUSTOMFAILEND - 10)   /**< BAM error code showing that optimum processing block dimension was not found */
#define BAM_E_CORETYPE_INVALID         (BAM_E_CUSTOMFAILEND - 11)   /**< BAM error code showing that kernel's core type does not match graph's core type */
#define BAM_E_PORT_NOT_CONNECTED      (BAM_E_CUSTOMFAILEND - 12)   /**< at least one compute node's port is missign a connection. If the graph does not need a particular output port to be consumed  then connect to  BAM_NULL_NODE= 254 */
#define BAM_E_SMART_MEM_ALLOCATOR   (BAM_E_CUSTOMFAILEND - 13)   /**< Some unexpected error with the smart memory allocator */
#define BAM_E_SIZE_GRAPH_OBJ (BAM_E_CUSTOMFAILEND - 14)   /**< BAM error code thrown by the smart memory allocator showing the graph object code size is too small */
#define BAM_E_OUT_OF_MEMPACKETS (BAM_E_CUSTOMFAILEND - 15)   /**< BAM error code thrown by the smart memory allocator when number of packets is reached, it should not happen. In case the error occurs, try to increase BAM_NUM_GUARD_PACKETS in file bam_mempkt.h and recompile */
#define BAM_E_DATABASE_KERNELID (BAM_E_CUSTOMFAILEND - 16)   /**< BAM error code returned by BAM_initKernelDB() when a kernelID value doesn't follow a sequential increasing order*/
#define BAM_E_NUM_MEM_RECORDS   (BAM_E_CUSTOMFAILEND - 17)   /**< The number of internal / output memory records for the kernel exceeds BAM_MAX_NODE_INTERNAL/BAM_MAX_NODE_INPUT_OUTPUT */

#ifndef BAM_NULL
#define BAM_NULL (0)            /**< NULL Pointer */
#endif

#ifndef BAM_TRUE
#define BAM_TRUE (1)            /**< Boolean TRUE */
#endif

#ifndef BAM_FALSE
#define BAM_FALSE (0)           /**< Boolean FALSE */
#endif

#endif /* BAM_TYPES_H */
