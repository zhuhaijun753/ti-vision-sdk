/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 *  @file       IBAMALG.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the "generic" algorithm interface.
 */

#ifndef _IBAMALG_H_
#define _IBAMALG_H_

#include "ibamalgtypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * Forward declaration of Fxns
     */
    typedef struct _IBAMALG_Fxns IBAMALG_Fxns;

    /**
     *  @brief      This must be the first field of all IBAMALG
     *              instance objects.
     */
    typedef struct _ibamalg_obj
    {
        uint32_t size;          /**< Size of the object */
        uint32_t numMemRecs;    /**< Number of all algorithm Memory requirements which are allocated from outside */
        IBAMALG_Fxns *fxns;     /**< Pointer to IBAMALG_Fxns structure of the algorithm */
    } IBAMALG_Obj;


    /**
     *  @brief      Opaque handle to an IBAMALG objects.
     */
    typedef struct _ibamalg_obj *IBAMALG_Handle;


    /**
     *  @brief      Defines the control commands for the IBAMALG module.
     *
     *  @sa         IBAMALG_Fxns::control()
     */
    typedef uint32_t IBAMALG_Cmd;




    /**
    *  @brief      Number of memory allocation requests required.
    *
    *  @remarks    algNumAlloc() returns the maximum number of memory allocation
    *              requests that the algAlloc() method requires.  This operation
    *              allows clients to allocate sufficient space to call the
    *              algAlloc() method or fail because insufficient space exists
    *              to support the creation of the algorithm's instance object.
    *              algNumAlloc() may be called at any time, and it must be
    *              idempotent; i.e., it can be called repeatedly without any
    *              side effects, and always returns the same result.
    *
    *  @remarks    algNumAlloc() is optional; if it is not implemented, the
    *              maximum number of memory records for algAlloc() is assumed
    *              to be IBAMALG_DEFMEMRECS.  This is equivalent to the following
    *              implementation:
    *
    *  @remarks    If a module does not implement this method, the algNumAlloc()
    *              field in the module's static function table (of type IALG_Fxns)
    *              must be set to @c NULL.
    *
    *  @post       The return value from algNumAlloc() is always greater than
    *              or equal to one and always equals or exceeds the value
    *              returned by algAlloc().
    *
    *  @sa algAlloc()
    */
    typedef int32_t (*IBAMALG_algNumAlloc)(const IBAMALG_Params *params);

    /**
    *  @brief      Apps call this to query the algorithm about
    *              its basic memory requirements.  Must be non-NULL.
    *
    *  @param[in]  params          Algorithm specific attributes.
    *  @param[in]  maxMemAvailable Platform specific memroy availability. Pointer to integer array of size
    *                              numMemHeaps. Consult ALG OSAL header file for the maximum value for numMemHeaps
    *                              and also for the order in which memory sizes are to be populated.
    *  @param[in]   numMemHeaps     number of memory heaps as defined in ALG OSAL file
    *  @param[out] memTab          array of memory records.
    *
    *  @remarks    algAlloc() returns a table of memory records that
    *              describe the size, alignment, type and memory space of
    *              all buffers required by an algorithm (including the
    *              algorithm's instance object itself).  If successful,
    *              this function returns a positive non-zero value
    *              indicating the number of records initialized.  This
    *              function can never initialize more memory records than
    *              the number returned by algNumAlloc().
    *
    *  @remarks    If algNumAlloc() is not implemented, the maximum number
    *              of initialized memory records is IBAMALG_DEFMEMRECS.
    *
    *  @remarks    The first argument to algAlloc() is a pointer to the creation
    *              parameters for the instance of the algorithm object to be
    *              created.  This pointer is algorithm-specific; i.e., it points
    *              to a structure that is defined by each particular algorithm.
    *              This pointer may be @c NULL; however, in this case, algAlloc()
    *              must assume default creation parameters and must not fail.
    *
    *  @remarks    algAlloc() may be called at any time and it must be idempotent;
    *              i.e., it can be called repeatedly without any side effects,
    *              and always returns the same result.
    *
    *  @remarks    Algorithms are encouraged to return (and document!) clear,
    *              algorithm-specific error codes from algAlloc().  Create-time
    *              failures are a common integration issue, and the clearer a
    *              return value, the sooner the algorithm integrator can identify
    *              and resolve the issue.
    *
    *  @pre        The number of memory records in the array @c memTab[] is no
    *              less than the number returned by algNumAlloc().
    *
    *  @post       For each memory descriptor in memTab with an BAM_MEMATTRS_CONST
    *              attribute, the algorithm has either set the base field to a
    *              non-NULL value, which is the address of a statically
    *              allocated and initialized memory buffer of the indicated
    *              'size', or has set the base field to @c NULL, thereby
    *              requiring the memory for the buffer to be provided by the
    *              client.
    *
    *  @post       Exactly @c n elements of the @c memTab[] array are initialized,
    *              where @c n is the return value from this operation.
    *
    *  @post       For each memory descriptor in @c memTab with an BAM_MEMATTRS_PERSIST or
    *              BAM_MEMATTRS_SCRATCH attribute, the algorithm does not set its base
    *              field.
    *
    *  @post       @c memTab[0] defines the memory required for the instance's
    *              object and this object's first field is an IBAMALG_Obj structure.
    *
    *  @post       @c memTab[0] is requested as persistent memory.
    *
    *  @sa         algFree()
    */
    typedef int32_t (*IBAMALG_algAlloc)(const IBAMALG_Params *params, int32_t maxMemAvailable[], int32_t numMemHeaps,
                    IBAMALG_MemRec *memRec, uint32_t numMemRecs);

    /**
    *  @brief      Apps call this to query the algorithm about
    *              its additinal memory requirements.
    *
    *  @param[in]  params          Algorithm specific attributes.
    *  @param[out] memTab          array of memory records.
    *
    *  @remarks    algAlloc() returns a table of memory records that
    *              describe the size, alignment, type and memory space of
    *              all buffers required by an algorithm (including the
    *              algorithm's instance object itself).  If successful,
    *              this function returns a positive non-zero value
    *              indicating the number of records initialized.  This
    *              function can never initialize more memory records than
    *              the number returned by algNumAlloc().
    *
    *  @remarks    If algNumAlloc() is not implemented, the maximum number
    *              of initialized memory records is IBAMALG_DEFMEMRECS.
    *
    *  @remarks    The first argument to algAlloc() is a pointer to the creation
    *              parameters for the instance of the algorithm object to be
    *              created.  This pointer is algorithm-specific; i.e., it points
    *              to a structure that is defined by each particular algorithm.
    *              This pointer may be @c NULL; however, in this case, algAlloc()
    *              must assume default creation parameters and must not fail.
    *
    *  @remarks    The second argument to algAlloc() is an optional parameter.
    *              algAlloc() may return a pointer to its parent's IALG functions.
    *              If this output value is assigned a non-NULL value, the client
    *              must create the parent instance object using the designated
    *              IALG functions pointer.  The parent instance object must then
    *              be passed to algInit().
    *
    *  @remarks    algAlloc() may be called at any time and it must be idempotent;
    *              i.e., it can be called repeatedly without any side effects,
    *              and always returns the same result.
    *
    *  @remarks    Algorithms are encouraged to return (and document!) clear,
    *              algorithm-specific error codes from algAlloc().  Create-time
    *              failures are a common integration issue, and the clearer a
    *              return value, the sooner the algorithm integrator can identify
    *              and resolve the issue.
    *
    *  @pre        The number of memory records in the array @c memTab[] is no
    *              less than the number returned by algNumAlloc().
    *
    *  @pre        @c *parentFxns is a valid pointer to an IALG_Fxns pointer
    *              variable.
    *
    *  @post       If the algorithm needs a parent object to be created, the
    *              pointer @c *parentFxns is set to a non-NULL value that points
    *              to a valid IALG_Fxns structure, the parent's IALG
    *              implementation.  Otherwise, this pointer is not set.  algAlloc()
    *              may elect to ignore the @c parentFxns pointer altogether.
    *
    *  @post       For each memory descriptor in memTab with an BAM_MEMATTRS_CONST
    *              attribute, the algorithm has either set the base field to a
    *              non-NULL value, which is the address of a statically
    *              allocated and initialized memory buffer of the indicated
    *              'size', or has set the base field to @c NULL, thereby
    *              requiring the memory for the buffer to be provided by the
    *              client.
    *
    *  @post       Exactly @c n elements of the @c memTab[] array are initialized,
    *              where @c n is the return value from this operation.
    *
    *  @post       For each memory descriptor in @c memTab with an BAM_MEMATTRS_PERSIST or
    *              BAM_MEMATTRS_SCRATCH attribute, the algorithm does not set its base
    *              field.
    *
    *  @post       @c memTab[0] defines the memory required for the instance's
    *              object and this object's first field is an IALG_Obj structure.
    *
    *  @post       @c memTab[0] is requested as persistent memory.
    *
    *  @sa         algFree()
    */
    typedef int32_t (*IBAMALG_algAllocMem)(IBAMALG_Handle *handle, const IBAMALG_Params *params, 
            IBAMALG_MemRec *memRec, uint32_t numMemRecs);

    /**
    *  @brief      Initialize an algorithm's instance object.  Must be non-NULL.
    *
    *  @param[in]  handle          Algorithm instance handle.  This is a pointer
    *                              to an initialized IALG_Obj structure.  Its
    *                              value is identical to the
    *                              <tt>memTab[0].base</tt>.
    *  @param[in]  memTab          Array of allocated buffers.
    *  @param[in]  params          Pointer to algorithm's instance parameters.
    *
    *  @remarks    algInit() performs all initialization necessary to complete the
    *              run-time creation of an algorithm's instance object.  After a
    *              successful return from algInit(), the algorithm's instance
    *              object is ready to be used to process data.
    *
    *  @remarks    @c handle is a pointer to an initialized IALG_Obj structure.
    *              Its value is identical to the <tt>memTab[0].base</tt>.
    *
    *  @remarks    @c memTab is a table of memory records that describe the
    *              base address, size, alignment, type, and memory space
    *              of all buffers allocated for an algorithm instance
    *              (including the algorithm's instance object itself).  The
    *              number of initialized records is identical to the
    *              number returned by a prior call to algAlloc().
    *
    *  @remarks    @c parent is a handle to another algorithm instance object.
    *              This parameter is often NULL; indicating that no
    *              parent object exists.  This parameter allows clients
    *              to create a shared algorithm instance object and pass
    *              it to other algorithm instances.  For example, a
    *              parent instance object might contain global read-only
    *              tables that are used by several instances of a
    *              vocoder.
    *
    *  @remarks    @c params is a pointer to algorithm-specific parameters that
    *              are necessary for the creation and initialization of
    *              the instance object.  This pointer points to the same
    *              parameters passed to the algAlloc() operation.
    *              However, this pointer may be NULL.  In this case,
    *              algInit(), must assume default creation parameters.
    *
    *  @remarks    Algorithms are encouraged to return (and document!) clear,
    *              algorithm-specific error codes from algInit().  Create-time
    *              failures are a common integration issue, and the clearer a
    *              return value, the sooner the algorithm integrator can identify
    *              and resolve the issue.
    *
    *  @remarks    The algorithm <b>must not</b> access any scratch resources,
    *              memory or otherwise, until it has been activated (see
    *              algActivate()).  A common error is to initialize
    *              scratch resources during algInit().  This is an error
    *              as <i>another</i> algorithm, or instance of the same
    *              algorithm, may be active when this instance's
    *              algInit() is called.  This algorithm must not access
    *              scratch resources until it is active.
    *
    *  @remarks    The client is not required to satisfy the IALG_MemSpace
    *              attribute of the requested memory.  Note however that
    *              C6000 algorithms that use DMA may strictly require the
    *              client to satisfy its on-chip memory requirements and
    *              may not function correctly otherwise.
    *
    *  @remarks    The client may allocate the requested BAM_MEMATTRS_CONST
    *              buffers once (or never, if the algorithm has assigned
    *              a base address in the prior call to algAlloc) and use
    *              the same buffers to initialize multiple instances of
    *              the same algorithm that are created with identical
    *              parameters.
    *
    *  @pre        @c memTab contains pointers to non-overlapping buffers with
    *              the size and alignment requested via a prior call to
    *              algAlloc().  In addition, the algorithm parameters,
    *              params, passed to algAlloc() are identical to those
    *              passed to this operation.
    *
    *  @pre        @c handle must be a valid handle for the algorithm's
    *              instance object; i.e., <tt>handle == memTab[0].base</tt> and
    *              @c handle->fxns is initialized to point to the
    *              appropriate IALG_Fxns structure.
    *
    *  @pre        The prior call to algAlloc() using same creation params must
    *              have returned value > 1.  This pre-condition ensures that any
    *              create-time parameter validation can be done once (in
    *              algAlloc()), and is not required to be done in algInit().
    *              Note that algInit() can, and should, validate any algorithm-
    *              specific requirements on resources received (e.g. internal
    *              memory, etc).
    *
    *  @pre        If the prior call to algAlloc() has not assigned a non-NULL
    *              base address to an BAM_MEMATTRS_CONST @c memTab entry,
    *              the client must provide the memory resource with the
    *              requested size and alignment.
    *
    *  @pre        If the prior call to algAlloc() returned a non-NULL parent
    *              functions pointer, then the parent handle, @c parent,
    *              must be a valid handle to an instance object created
    *              via that function pointer.
    *
    *  @pre        No other algorithm method is currently being run on this
    *              instance.  This method never preempts any other method
    *              on the same instance.
    *
    *  @pre        If @c parent is non-NULL, no other method is currently being
    *              run on the parent instance; i.e., this method never
    *              preempts any other method on the parent instance.
    *
    *  @pre        If the prior call to algAlloc() assigned a non-NULL base
    *              address to an BAM_MEMATTRS_CONST @c memTab[] entry, the
    *              client may pass back the same address in the base
    *              field without allocating additional memory for that
    *              persistent write-once buffer. Alternatively, the
    *              client may treat BAM_MEMATTRS_CONST buffers in the same
    *              way as BAM_MEMATTRS_PERSIST buffers; by allocating new memory
    *              and granting it to the algorithm using the base field.
    *
    *  @pre        The buffer pointed to in @c memTab[0] is initialized
    *              with a pointer to the appropriate IALG_Fxns structure
    *              followed by all 0s.
    *
    *  @post       With the exception of any initialization performed
    *              by algActivate() and any optional auxilary interface
    *              initialization functions (such as IRES and IDMA3),
    *              all of the instance's persistent and write-once memory is
    *              initialized and the object is ready to be used.
    *
    *  @post       All subsequent memory accesses to the BAM_MEMATTRS_CONST
    *              buffers by this algorithm instance will be read-only.
    *
    *  @post       If the algorithm has implemented the IDMA2 interface,
    *              the dmaGetChannels() operation can be called.
    *
    *  @retval     IBAMALG_EOK       
    *  @retval     IBAMALG_EFAIL     
    *  @retval     "Custom error"  Algorithm-specific error - see
    *                              algorithm's documentation.
    *
    *  @sa         algAlloc()
    *  @sa         algMoved()
    */
    typedef int32_t (*IBAMALG_algInit)(IBAMALG_Handle *handle, const IBAMALG_Params *params, const IBAMALG_MemRec *memRec, uint32_t numMemRecs);

    /**
    *  @brief      Notify algorithm instance that instance memory has been
    *              relocated.
    *
    *  @param[in]  handle          Algorithm instance handle.
    *  @param[in]  memTab          Array of allocated buffers.
    *  @param[in]  parent          Handle of algorithm's parent instance.
    *  @param[in]  params          Pointer to algorithm's instance parameters.
    *
    *  @remarks    algMoved() performs any reinitialization necessary to insure
    *              that, if an algorithm's instance object has been moved by the
    *              client, all internal data references are recomputed.
    *
    *  @remarks    The implementation of algMoved() is optional.  However, it is
    *              highly recommended that this method be implemented.  If a
    *              module does not implement this method, the algMoved() field
    *              in the module's static function table (of type IALG_Fxns) must
    *              be set to @c NULL.  This is equivalent to asserting that the
    *              algorithm's instance objects cannot be moved.
    */
    typedef void (*IBAMALG_algMoved)(IBAMALG_Handle handle, const IBAMALG_MemRec *memRec, uint32_t numMemRecs, const IBAMALG_Params *params);

    /**
    *  @brief      Notification to the algorithm that its memory
    *              is "active" and algorithm processing methods
    *              may be called.
    *
    *  @param[in]  handle          Handle to an algorithm instance.
    *
    *  @remarks    algActivate() initializes any of the instance's scratch
    *              buffers using the persistent memory that is part of the
    *              algorithm's instance object.
    *
    *  @remarks    The implementation of algActivate() (and algDeactivate())
    *              is <b>required</b> if the algorithm requests memory of
    *              type BAM_MEMATTRS_SCRATCH.
    *
    *  @remarks    The algActivate() method should only be implemented if
    *              a module wants to factor out initialization code that
    *              can be executed once prior to processing multiple
    *              consecutive frames of data.
    *
    *  @remarks    If a module does not implement this method, the algActivate()
    *              field in the module's static function table (of type
    *              IALG_Fxns) must be set to @c NULL.  This is equivalent to
    *              the following implementation:
    *
    *  @pre        algActivate() can only be called after a successful return
    *              from algInit().
    *
    *  @pre        @c handle must be a valid handle for the algorithm's
    *              instance object.
    *
    *  @pre        No other algorithm method is currently being run on this
    *              instance. This method never preempts any other method on
    *              the same instance.
    *
    *  @post       All methods related to the algorithm may now be executed
    *              by client (subject to algorithm specific restrictions).
    *
    *  @sa         algDeactivate().
    */
    typedef void (*IBAMALG_algActivate)(IBAMALG_Handle handle);

    /**
    *  @brief      Control behaviour of an algorithm.
    *
    *  @param[in]  handle          Handle to an algorithm instance.
    *  @param[in]  id              Command id.  See XDM_CmdId.
    *  @param[in]  params          Dynamic parameters.  This is a required
    *                              parameter.
    *  @param[out] status          Output results.  This is a required parameter.
    *
    *  @pre        @c handle must be a valid algorithm instance handle.
    *
    *  @pre        @c params must not be NULL, and must point to a valid
    *              IBAMALG_DynamicParams structure.
    *
    *  @pre        @c status must not be NULL, and must point to a valid
    *              IBAMALG_Status structure.
    *
    *  @pre        If a buffer is provided in the @c status->data field,
    *              it must be physically contiguous and owned by the calling
    *              application.
    *
    *  @post       The algorithm <b>must not</b> modify the contents of @c params.
    *              That is, the data pointed to by this parameter must be
    *              treated as read-only.
    *
    *  @post       If a buffer was provided in the @c status->data field,
    *              it is owned by the calling application.
    *
    *  @retval     IBAMALG_EOK          
    *  @retval     IBAMALG_EFAIL        
    *                                      See IBAMALG_Status#extendedError
    *                                      for more detailed further error
    *                                      conditions.
    *  @retval     IBAMALG_EUNSUPPORTED 
    */
    typedef int32_t (*IBAMALG_algControl)(IBAMALG_Handle handle, IBAMALG_Cmd id, IBAMALG_ControlParams *params,
                                          IBAMALG_Status *status);

    /**
    *  @brief      Basic video encoding call.
    *
    *  @param[in]  handle          Handle to an algorithm instance.
    *  @param[in]  inArgs          Input arguments.  This is a required
    *                              parameter.
    *  @param[out] outArgs         Ouput results.  This is a required parameter.
    *
    *  @remarks    process() is a blocking call.  When process() returns, the
    *              algorithm's processing is complete.
    *
    *  @pre        @c inArgs must not be NULL, and must point to a valid
    *              IVIDENC_InArgs structure.
    *
    *  @pre        @c outArgs must not be NULL, and must point to a valid
    *              IVIDENC_OutArgs structure.
    *
    *  @pre        The buffers in @c inBufs and @c outBufs are physically
    *              contiguous and owned by the calling application.
    *
    *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
    *
    *  @post       The buffers in @c inBufs are
    *              owned by the calling application.
    *
    *  @retval     IALG_EOK        Success.
    *  @retval     IALG_EFAIL      Failure.  See IVIDENC_OutArgs#extendedError
    *                              for more detailed further error conditions.
    */
    typedef int32_t (*IBAMALG_algProcess)(IBAMALG_Handle handle, IBAMALG_InBufs *inBufs, IBAMALG_OutBufs *outBufs, IBAMALG_InArgs *inArgs, IBAMALG_OutArgs *outArgs);


    /**
    *  @brief      Save all persistent data to non-scratch memory.
    *
    *  @param[in]  handle          Algorithm instance handle.
    *
    *  @remarks    algDeactivate() saves any persistent information to non-scratch
    *              buffers using the persistent memory that is part of the
    *              algorithm's instance object.
    *
    *  @remarks    @c handle is used by the algorithm to identify the various
    *              buffers that must be saved prior to the next cycle of
    *              algActivate() and processing.
    *
    *  @remarks    The implementation of algDeactivate() (and algActivate())
    *              is <b>required</b> if the algorithm requests memory of
    *              type BAM_MEMATTRS_SCRATCH.
    *
    *  @remarks    The algDeactivate() method is only implemented if a
    *              module wants to factor out initialization code that
    *              can be executed once prior to processing multiple
    *              consecutive frames of data.
    *
    *  @remarks    If a module does not implement this method, the
    *              algDeactivate() field in the module's static function table
    *              (of type IALG_Fxns) must be set to @c NULL.
    *
    *  @pre        algDeactivate() can only be called after a successful return
    *              from algInit().
    *
    *  @pre        The instance object is currently "active"; i.e., all instance
    *              memory is active and if an algActivate() method is defined,
    *              it has been called.
    *
    *  @pre        @c handle must be a valid handle for the algorithm's instance
    *              object.
    *
    *  @pre        No other algorithm method is currently being run on this
    *              instance.  This method never preempts any other method on the
    *              same instance.
    *
    *  @post       No methods related to the algorithm may now be executed by
    *              the client; only algActivate() or algFree() may be called.
    *
    *  @post       All instance scratch memory may be safely overwritten.
    *
    *  @sa         algActivate()
    */
    typedef void (*IBAMALG_algDeactivate)(IBAMALG_Handle handle);

    /**
    *  @brief      Apps call this to allow the algorithm to initialize memory
    *              requested via algAlloc().  Must be non-NULL.
    *
    *  @param[in]  handle          Algorithm instance handle.
    *  @param[out] memTab          Output array of memory records.
    *
    *  @remarks    algFree() returns a table of memory records that describe
    *              the base address, size, alignment, type and memory space
    *              of all buffers previously allocated for the algorithm's
    *              instance (including the algorithm's instance object itself)
    *              specified by @c handle.  This function always returns a
    *              positive non-zero value indicating the number of records
    *              initialized.  This function can never initialize more memory
    *              records than the value returned by algNumAlloc().
    *
    *  @pre        The @c memTab[] array contains at least algNumAlloc() records.
    *
    *  @pre        @c handle must be a valid handle for the algorithm's instance
    *              object.
    *
    *  @pre        If the prior call to algAlloc() returned a non-NULL parent
    *              functions pointer, then the parent instance must be an active
    *              instance object created via that function pointer.
    *
    *  @pre        No other agorithm method is currently being run on this
    *              instance.  This method never preempts any other method on the
    *              same instance.
    *
    *  @post       @c memTab[] contains pointers to all of the memory passed to
    *              the algorithm via algInit().
    *
    *  @post       The size and alignment fields contain the same values passed
    *              to the client via algAlloc(); i.e., if the client makes changes
    *              to the values returned via algAlloc() and passes these new
    *              values to algInit(), the algorithm is not responsible for
    *              retaining any such changes.
    *
    *  @sa         algAlloc()
    */
    typedef int32_t (*IBAMALG_algFree)(IBAMALG_Handle handle, IBAMALG_MemRec *memRec, uint32_t numMemRecs);

    /**
    *              Example create function. Apps can call this to create the handles.
    *              If this implementation of create doesnot serve the purpose, apps can choose to
    *             write their own create function.
    */
    typedef int32_t (*IBAMALG_algCreate)(const IBAMALG_Fxns *fxns,  IBAMALG_Handle *handle, const IBAMALG_Params *params,
                                         ALGOSAL_MemAllocator *memAllocator);


    /**
    *              Example delete function. Apps can call this to delete the handles.
    *              If this implementation of create doesnot serve the purpose, apps can choose to
    *             write their own delete function.
    */
    typedef int32_t (*IBAMALG_algDelete)(const IBAMALG_Handle handle, ALGOSAL_MemAllocator *memAllocator);

    /**
     *  @brief      Defines the fields and methods that must be supplied by all
     *              IBAMALG algorithms.
     */
    /*
     *      algNumAlloc()     - query algorithm for number of memory requests.
     *                          May be NULL; NULL => number of mem recs is less
     *                          then IBAMALG_DEFMEMRECS.
     *      algAlloc()        - apps call this to query the algorithm about
     *                          its basic memory requirements. Must be non-NULL.
     *      alloc()           - apps call this to query the algorithm about
     *                          its extended memory requirements.
     *      algInit()         - apps call this to allow the algorithm to
     *                          initialize memory requested via algAlloc().  Must
     *                          be non-NULL.
     *      algMoved()        - apps call this whenever an algorithms object or
     *                          any pointer parameters are moved in real-time.
     *                          May be NULL; NULL => object can not be moved.
     *      algActivate()     - notification that current instance is about to
     *                          be "activiated".  May be NULL; NULL => do nothing.
     *      control()         - control function to get or set parameters
     *      process()         - actual execution function
     *      algDeactivate()   - notification that current instance is about to
     *                          be "deactivated".  May be NULL; NULL => do nothing.
     *      algFree()         - query algorithm for memory to free when removing
     *                          an instance.  Must be non-NULL.
     *      algCreate()         Sample (meaning, a typical) create function
     *      algDelete()         Sample (meaning, a typical) delete function
     */
    struct _IBAMALG_Fxns
    {
        /**
         *  @brief      Unique pointer that identifies the module
         *              implementing this interface.
         */
        void *implementationId;

        /**
        *  @brief      Number of memory allocation requests required.
        */
        IBAMALG_algNumAlloc algNumAlloc;

        /**
        *  @brief      Apps call this to query the algorithm about
        *              memory requirements of its handles.  Must be non-NULL.
        */
        IBAMALG_algAlloc algAlloc;

        /**
        *  @brief      Apps call this to query the algorithm about
        *              its additinal memory requirements.
        *
        */
        IBAMALG_algAllocMem algAllocMem;

        /**
        *  @brief      Initialize an algorithm's instance object.  Must be non-NULL.
        */
        IBAMALG_algInit algInit;

        /**
        *  @brief      Notify algorithm instance that instance memory has been
        *              relocated.
        */
        IBAMALG_algMoved algMoved;

        /**
        *  @brief      Notification to the algorithm that its memory
        *              is "active" and algorithm processing methods
        *              may be called.
        */
        IBAMALG_algActivate algActivate;

        /**
        *  @brief      Control behaviour of an algorithm.
        */
        IBAMALG_algControl algControl;

        /**
        *  @brief      Basic video encoding call.
        */
        IBAMALG_algProcess algProcess;


        /**
        *  @brief      Save all persistent data to non-scratch memory.
        */
        IBAMALG_algDeactivate algDeactivate;

        /**
        *  @brief      Apps call this to allow the algorithm to initialize memory
        *              requested via algAlloc().  Must be non-NULL.
        */
        IBAMALG_algFree algFree;
        /**
        *              Example create function. Apps can call this to create the handles.
        *              If this implementation of create doesnot serve the purpose, apps can choose to
        *             write their own create function.
        */
        IBAMALG_algCreate algCreate;


        /**
        *              Example delete function. Apps can call this to delete the handles.
        *              If this implementation of create doesnot serve the purpose, apps can choose to
        *             write their own delete function.
        */
        IBAMALG_algDelete algDelete;

    };



#ifdef __cplusplus
}
#endif

#endif


