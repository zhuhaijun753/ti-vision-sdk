/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A75
 */

#define __nested__
#define __config__

#include <xdc/std.h>

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     MODULE INCLUDES
 *     
 *     <module-name> INTERNALS
 *     <module-name> INHERITS
 *     <module-name> VTABLE
 *     <module-name> PATCH TABLE
 *     <module-name> DECLARATIONS
 *     <module-name> OBJECT OFFSETS
 *     <module-name> TEMPLATES
 *     <module-name> INITIALIZERS
 *     <module-name> FUNCTION STUBS
 *     <module-name> PROXY BODY
 *     <module-name> OBJECT DESCRIPTOR
 *     <module-name> VIRTUAL FUNCTIONS
 *     <module-name> SYSTEM FUNCTIONS
 *     <module-name> PRAGMAS
 *     
 *     INITIALIZATION ENTRY POINT
 *     PROGRAM GLOBALS
 *     CLINK DIRECTIVES
 */


/*
 * ======== MODULE INCLUDES ========
 */

#include <ti/catalog/arm/cortexm4/tiva/ce/Boot.h>
#include <ti/sdo/utils/NameServerRemoteNull.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Core.h>
#include <xdc/runtime/Defaults.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/GateNull.h>
#include <xdc/runtime/HeapStd.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Main.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Registry.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/SysMin.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Text.h>

/*
 * ======== ti.catalog.arm.cortexm4.tiva.ce.Boot INTERNALS ========
 */


/*
 * ======== ti.sdo.utils.NameServerRemoteNull INTERNALS ========
 */

/* Module__ */
typedef struct ti_sdo_utils_NameServerRemoteNull_Module__ {
    xdc_runtime_Types_Link link;
} ti_sdo_utils_NameServerRemoteNull_Module__;

/* Module__root__V */
extern ti_sdo_utils_NameServerRemoteNull_Module__ ti_sdo_utils_NameServerRemoteNull_Module__root__V;

/* Object__ */
typedef struct ti_sdo_utils_NameServerRemoteNull_Object__ {
    const ti_sdo_utils_NameServerRemoteNull_Fxns__ *__fxns;
} ti_sdo_utils_NameServerRemoteNull_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    ti_sdo_utils_NameServerRemoteNull_Object__ obj;
} ti_sdo_utils_NameServerRemoteNull_Object2__;

/* __ParamsPtr */
#ifdef ti_sdo_utils_NameServerRemoteNull___VERS
    #define ti_sdo_utils_NameServerRemoteNull___ParamsPtr xdc_UChar*
#else
    #define ti_sdo_utils_NameServerRemoteNull___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.Assert INTERNALS ========
 */


/*
 * ======== xdc.runtime.Core INTERNALS ========
 */


/*
 * ======== xdc.runtime.Defaults INTERNALS ========
 */


/*
 * ======== xdc.runtime.Diags INTERNALS ========
 */


/*
 * ======== xdc.runtime.Error INTERNALS ========
 */


/*
 * ======== xdc.runtime.Gate INTERNALS ========
 */


/*
 * ======== xdc.runtime.GateNull INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_GateNull_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_GateNull_Module__;

/* Module__root__V */
extern xdc_runtime_GateNull_Module__ xdc_runtime_GateNull_Module__root__V;

/* Object__ */
typedef struct xdc_runtime_GateNull_Object__ {
    const xdc_runtime_GateNull_Fxns__ *__fxns;
} xdc_runtime_GateNull_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_GateNull_Object__ obj;
} xdc_runtime_GateNull_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_GateNull___VERS
    #define xdc_runtime_GateNull___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_GateNull___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.HeapStd INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_HeapStd_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_HeapStd_Module__;

/* Module__root__V */
extern xdc_runtime_HeapStd_Module__ xdc_runtime_HeapStd_Module__root__V;

/* Object__ */
typedef struct xdc_runtime_HeapStd_Object__ {
    const xdc_runtime_HeapStd_Fxns__ *__fxns;
    xdc_runtime_Memory_Size remainSize;
    xdc_runtime_Memory_Size startSize;
} xdc_runtime_HeapStd_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_HeapStd_Object__ obj;
} xdc_runtime_HeapStd_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_HeapStd___VERS
    #define xdc_runtime_HeapStd___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_HeapStd___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.Log INTERNALS ========
 */


/*
 * ======== xdc.runtime.Main INTERNALS ========
 */


/*
 * ======== xdc.runtime.Main_Module_GateProxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_Main_Module_GateProxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_Main_Module_GateProxy_Module__;

/* Module__root__V */
extern xdc_runtime_Main_Module_GateProxy_Module__ xdc_runtime_Main_Module_GateProxy_Module__root__V;

/* <-- xdc_runtime_GateNull_Object */

/* Object */
typedef xdc_runtime_GateNull_Object__ xdc_runtime_Main_Module_GateProxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_Main_Module_GateProxy_Object__ obj;
} xdc_runtime_Main_Module_GateProxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_Main_Module_GateProxy___VERS
    #define xdc_runtime_Main_Module_GateProxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_Main_Module_GateProxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.Memory INTERNALS ========
 */


/*
 * ======== xdc.runtime.Memory_HeapProxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_Memory_HeapProxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_Memory_HeapProxy_Module__;

/* Module__root__V */
extern xdc_runtime_Memory_HeapProxy_Module__ xdc_runtime_Memory_HeapProxy_Module__root__V;

/* <-- xdc_runtime_HeapStd_Object */

/* Object */
typedef xdc_runtime_HeapStd_Object__ xdc_runtime_Memory_HeapProxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_Memory_HeapProxy_Object__ obj;
} xdc_runtime_Memory_HeapProxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_Memory_HeapProxy___VERS
    #define xdc_runtime_Memory_HeapProxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_Memory_HeapProxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.Registry INTERNALS ========
 */


/*
 * ======== xdc.runtime.Startup INTERNALS ========
 */


/*
 * ======== xdc.runtime.SysMin INTERNALS ========
 */


/*
 * ======== xdc.runtime.System INTERNALS ========
 */


/*
 * ======== xdc.runtime.System_Module_GateProxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_System_Module_GateProxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_System_Module_GateProxy_Module__;

/* Module__root__V */
extern xdc_runtime_System_Module_GateProxy_Module__ xdc_runtime_System_Module_GateProxy_Module__root__V;

/* <-- xdc_runtime_GateNull_Object */

/* Object */
typedef xdc_runtime_GateNull_Object__ xdc_runtime_System_Module_GateProxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_System_Module_GateProxy_Object__ obj;
} xdc_runtime_System_Module_GateProxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_System_Module_GateProxy___VERS
    #define xdc_runtime_System_Module_GateProxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_System_Module_GateProxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.System_SupportProxy INTERNALS ========
 */


/*
 * ======== xdc.runtime.Text INTERNALS ========
 */


/*
 * ======== INHERITS ========
 */

#pragma DATA_SECTION(xdc_runtime_IHeap_Interface__BASE__C, ".const:xdc_runtime_IHeap_Interface__BASE__C");
__FAR__ const xdc_runtime_Types_Base xdc_runtime_IHeap_Interface__BASE__C = {(void*)&xdc_runtime_IModule_Interface__BASE__C};

#pragma DATA_SECTION(xdc_runtime_ISystemSupport_Interface__BASE__C, ".const:xdc_runtime_ISystemSupport_Interface__BASE__C");
__FAR__ const xdc_runtime_Types_Base xdc_runtime_ISystemSupport_Interface__BASE__C = {(void*)&xdc_runtime_IModule_Interface__BASE__C};

#pragma DATA_SECTION(xdc_runtime_IGateProvider_Interface__BASE__C, ".const:xdc_runtime_IGateProvider_Interface__BASE__C");
__FAR__ const xdc_runtime_Types_Base xdc_runtime_IGateProvider_Interface__BASE__C = {(void*)&xdc_runtime_IModule_Interface__BASE__C};

#pragma DATA_SECTION(xdc_runtime_IModule_Interface__BASE__C, ".const:xdc_runtime_IModule_Interface__BASE__C");
__FAR__ const xdc_runtime_Types_Base xdc_runtime_IModule_Interface__BASE__C = {0};


/*
 * ======== xdc.runtime.GateNull VTABLE ========
 */

/* Module__FXNS__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__FXNS__C, ".const:xdc_runtime_GateNull_Module__FXNS__C");
const xdc_runtime_GateNull_Fxns__ xdc_runtime_GateNull_Module__FXNS__C = {
    (void*)&xdc_runtime_IGateProvider_Interface__BASE__C, /* __base */
    &xdc_runtime_GateNull_Module__FXNS__C.__sfxns, /* __sysp */
    xdc_runtime_GateNull_query__E,
    xdc_runtime_GateNull_enter__E,
    xdc_runtime_GateNull_leave__E,
    {
        xdc_runtime_GateNull_Object__create__S,
        xdc_runtime_GateNull_Object__delete__S,
        xdc_runtime_GateNull_Handle__label__S,
        0x8008, /* __mid */
    } /* __sfxns */
};


/*
 * ======== xdc.runtime.HeapStd VTABLE ========
 */

/* Module__FXNS__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__FXNS__C, ".const:xdc_runtime_HeapStd_Module__FXNS__C");
const xdc_runtime_HeapStd_Fxns__ xdc_runtime_HeapStd_Module__FXNS__C = {
    (void*)&xdc_runtime_IHeap_Interface__BASE__C, /* __base */
    &xdc_runtime_HeapStd_Module__FXNS__C.__sfxns, /* __sysp */
    xdc_runtime_HeapStd_alloc__E,
    xdc_runtime_HeapStd_free__E,
    xdc_runtime_HeapStd_isBlocking__E,
    xdc_runtime_HeapStd_getStats__E,
    {
        xdc_runtime_HeapStd_Object__create__S,
        xdc_runtime_HeapStd_Object__delete__S,
        xdc_runtime_HeapStd_Handle__label__S,
        0x800c, /* __mid */
    } /* __sfxns */
};


/*
 * ======== xdc.runtime.SysMin VTABLE ========
 */

/* Module__FXNS__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__FXNS__C, ".const:xdc_runtime_SysMin_Module__FXNS__C");
const xdc_runtime_SysMin_Fxns__ xdc_runtime_SysMin_Module__FXNS__C = {
    (void*)&xdc_runtime_ISystemSupport_Interface__BASE__C, /* __base */
    &xdc_runtime_SysMin_Module__FXNS__C.__sfxns, /* __sysp */
    xdc_runtime_SysMin_abort__E,
    xdc_runtime_SysMin_exit__E,
    xdc_runtime_SysMin_flush__E,
    xdc_runtime_SysMin_putch__E,
    xdc_runtime_SysMin_ready__E,
    {
        NULL, /* __create */
        NULL, /* __delete */
        NULL, /* __label */
        0x8010, /* __mid */
    } /* __sfxns */
};


/*
 * ======== ti.catalog.arm.cortexm4.tiva.ce.Boot DECLARATIONS ========
 */


/*
 * ======== ti.sdo.utils.NameServerRemoteNull DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Assert DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Core DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Defaults DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Diags DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Error DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Error_Module_State__ {
    xdc_UInt16 count;
} xdc_runtime_Error_Module_State__;

/* Module__state__V */
xdc_runtime_Error_Module_State__ xdc_runtime_Error_Module__state__V;


/*
 * ======== xdc.runtime.Gate DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.GateNull DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.HeapStd DECLARATIONS ========
 */

/* Object__table__V */
xdc_runtime_HeapStd_Object__ xdc_runtime_HeapStd_Object__table__V[1];

/* Module_State__ */
typedef struct xdc_runtime_HeapStd_Module_State__ {
    xdc_runtime_Memory_Size remainRTSSize;
} xdc_runtime_HeapStd_Module_State__;

/* Module__state__V */
xdc_runtime_HeapStd_Module_State__ xdc_runtime_HeapStd_Module__state__V;


/*
 * ======== xdc.runtime.Log DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Main DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Main_Module_GateProxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Memory DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Memory_Module_State__ {
    xdc_SizeT maxDefaultTypeAlign;
} xdc_runtime_Memory_Module_State__;

/* Module__state__V */
xdc_runtime_Memory_Module_State__ xdc_runtime_Memory_Module__state__V;


/*
 * ======== xdc.runtime.Memory_HeapProxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Registry DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Registry_Module_State__ {
    xdc_runtime_Registry_Desc *listHead;
    xdc_runtime_Types_ModuleId curId;
} xdc_runtime_Registry_Module_State__;

/* Module__state__V */
xdc_runtime_Registry_Module_State__ xdc_runtime_Registry_Module__state__V;


/*
 * ======== xdc.runtime.Startup DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Startup_Module_State__ {
    xdc_Int *stateTab;
    xdc_Bool execFlag;
    xdc_Bool rtsDoneFlag;
} xdc_runtime_Startup_Module_State__;

/* Module__state__V */
xdc_runtime_Startup_Module_State__ xdc_runtime_Startup_Module__state__V;

/* --> xdc_runtime_Startup_firstFxns__A */
const __T1_xdc_runtime_Startup_firstFxns xdc_runtime_Startup_firstFxns__A[1];

/* --> xdc_runtime_System_Module_startup__E */
extern xdc_Int xdc_runtime_System_Module_startup__E(xdc_Int);

/* --> xdc_runtime_SysMin_Module_startup__E */
extern xdc_Int xdc_runtime_SysMin_Module_startup__E(xdc_Int);

/* --> xdc_runtime_Startup_sfxnTab__A */
const __T1_xdc_runtime_Startup_sfxnTab xdc_runtime_Startup_sfxnTab__A[2];

/* --> xdc_runtime_Startup_sfxnRts__A */
const __T1_xdc_runtime_Startup_sfxnRts xdc_runtime_Startup_sfxnRts__A[2];


/*
 * ======== xdc.runtime.SysMin DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_SysMin_Module_State__ {
    __TA_xdc_runtime_SysMin_Module_State__outbuf outbuf;
    xdc_UInt outidx;
    xdc_Bool wrapped;
} xdc_runtime_SysMin_Module_State__;

/* --> xdc_runtime_SysMin_Module_State_0_outbuf__A */
__T1_xdc_runtime_SysMin_Module_State__outbuf xdc_runtime_SysMin_Module_State_0_outbuf__A[1024];

/* Module__state__V */
xdc_runtime_SysMin_Module_State__ xdc_runtime_SysMin_Module__state__V;

/* --> xdc_runtime_SysMin_output__I */
extern xdc_Void xdc_runtime_SysMin_output__I(xdc_Char*,xdc_UInt);


/*
 * ======== xdc.runtime.System DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_System_Module_State__ {
    __TA_xdc_runtime_System_Module_State__atexitHandlers atexitHandlers;
    xdc_Int numAtexitHandlers;
} xdc_runtime_System_Module_State__;

/* --> xdc_runtime_System_Module_State_0_atexitHandlers__A */
__T1_xdc_runtime_System_Module_State__atexitHandlers xdc_runtime_System_Module_State_0_atexitHandlers__A[8];

/* Module__state__V */
xdc_runtime_System_Module_State__ xdc_runtime_System_Module__state__V;

/* --> xdc_runtime_System_printfExtend__I */
extern xdc_Int xdc_runtime_System_printfExtend__I(xdc_Char**,xdc_CString*,xdc_VaList*,xdc_runtime_System_ParseData*);


/*
 * ======== xdc.runtime.System_Module_GateProxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.System_SupportProxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Text DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Text_Module_State__ {
    xdc_Ptr charBase;
    xdc_Ptr nodeBase;
} xdc_runtime_Text_Module_State__;

/* Module__state__V */
xdc_runtime_Text_Module_State__ xdc_runtime_Text_Module__state__V;

/* --> xdc_runtime_Text_charTab__A */
const __T1_xdc_runtime_Text_charTab xdc_runtime_Text_charTab__A[3762];

/* --> xdc_runtime_Text_nodeTab__A */
const __T1_xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__A[27];


/*
 * ======== xdc.cfg.Program TEMPLATE ========
 */

/*
 *  ======== __ASM__ ========
 *  Define absolute path prefix for this executable's
 *  configuration generated files.
 */
xdc__META(__ASM__, "@(#)__ASM__ = /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/utils/package/cfg/instrumented_pem4");

/*
 *  ======== __ISA__ ========
 *  Define the ISA of this executable.  This symbol is used by platform
 *  specific "exec" commands that support more than one ISA; e.g., gdb
 */
xdc__META(__ISA__, "@(#)__ISA__ = v7M4");

/*
 *  ======== __PLAT__ ========
 *  Define the name of the platform that can run this executable.  This
 *  symbol is used by platform independent "exec" commands
 */
xdc__META(__PLAT__, "@(#)__PLAT__ = ti.platforms.stellaris");

/*
 *  ======== __TARG__ ========
 *  Define the name of the target used to build this executable.
 */
xdc__META(__TARG__, "@(#)__TARG__ = ti.targets.arm.elf.M4");

/*
 *  ======== __TRDR__ ========
 *  Define the name of the class that can read/parse this executable.
 */
xdc__META(__TRDR__, "@(#)__TRDR__ = ti.targets.omf.elf.Elf32");


/*
 * ======== xdc.cfg.SourceDir TEMPLATE ========
 */



/*
 * ======== xdc.runtime.Diags TEMPLATE ========
 */



/*
 * ======== xdc.runtime.Startup TEMPLATE ========
 */

/*
 *  ======== MODULE STARTUP DONE FUNCTIONS ========
 */
xdc_Bool xdc_runtime_System_Module__startupDone__F(void) {
    return (&xdc_runtime_Startup_Module__state__V)->stateTab == 0 || (&xdc_runtime_Startup_Module__state__V)->stateTab[0] < 0;
}
xdc_Bool xdc_runtime_SysMin_Module__startupDone__F(void) {
    return (&xdc_runtime_Startup_Module__state__V)->stateTab == 0 || (&xdc_runtime_Startup_Module__state__V)->stateTab[1] < 0;
}


/* 
 * Startup_exec__I is an internal entry point called by target/platform
 * boot code. Boot code is not brought into a partial-link assembly. So,
 * without this pragma, whole program optimizers would otherwise optimize-out
 * this function.
 */
#ifdef __ti__
#pragma FUNC_EXT_CALLED(xdc_runtime_Startup_exec__I);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
xdc_Void xdc_runtime_Startup_exec__I(void) __attribute__ ((externally_visible));
#endif
#endif

/*
 *  ======== xdc_runtime_Startup_exec__I ========
 *  Initialize all used modules that have startup functions
 */
xdc_Void xdc_runtime_Startup_exec__I(void)
{
    xdc_Int state[2];
    xdc_runtime_Startup_startModsFxn__C(state, 2);
}

/*
 * ======== xdc.runtime.Reset TEMPLATE ========
 */

/* 
 * Startup_reset__I is an internal entry point called by target/platform
 * boot code. Boot code is not brought into a partial-link assembly. So,
 * without this pragma, whole program optimizers would otherwise optimize-out
 * this function.
 */
#ifdef __ti__
#pragma FUNC_EXT_CALLED(xdc_runtime_Startup_reset__I);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
xdc_Void xdc_runtime_Startup_reset__I(void) __attribute__ ((externally_visible));
#endif
#endif


/*
 *  ======== xdc_runtime_Startup_reset__I ========
 *  This function is called by bootstrap initialization code as early as
 *  possible in the startup process.  This function calls all functions in
 *  the Reset.fxns array _as well as_ Startup.resetFxn (if it's non-NULL)
 */
xdc_Void xdc_runtime_Startup_reset__I(void)
{
}

/*
 * ======== xdc.runtime.System TEMPLATE ========
 */


#include <xdc/std.h>
#include <limits.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Text.h>
#include <xdc/runtime/Assert.h>

#include <xdc/runtime/System.h>
#include <xdc/runtime/System__internal.h>

/*
 *  ======== System_printfExtend__I ========
 *  This function processes optional extended formats of printf.
 *  
 *  It returns the number of characters added to the result.
 *
 *  Precision (maximum string length) is not supported for %$S.
 *
 *  Right-justified (which is default) minimum width is not supported
 *  for %$L, %$S, or %$F.
 */
xdc_Int xdc_runtime_System_printfExtend__I(xdc_Char **pbuf, xdc_CString *pfmt, 
    xdc_VaList *pva, xdc_runtime_System_ParseData *parse)
{
    xdc_CString fmt = *pfmt;
    xdc_Int     res;
    xdc_Char    c;
    xdc_Bool    found = FALSE;
    
    /* 
     * Create a local variable 'va' to ensure that the dereference of
     * pva only occurs once.
     */
    va_list va = *pva;
    
    res = 0;

    c = *fmt++;
    *pfmt = *pfmt + 1;

    
    if (c == '$') {
        c = *fmt++;
        *pfmt = *pfmt + 1;
        
        if (c == 'L') {
            xdc_runtime_Types_Label *lab = parse->aFlag ? 
                (xdc_runtime_Types_Label *)xdc_iargToPtr(va_arg(va, xdc_IArg)) :
                (xdc_runtime_Types_Label *)va_arg(va, void *);
            
            /* 
             * Call Text_putLab to write out the label, taking the precision 
             * into account.
             */
            res = xdc_runtime_Text_putLab(lab, pbuf, parse->precis);
            
            /*
             * Set the length to 0 to indicate to 'doPrint' that nothing should
             * be copied from parse.ptr.
             */
            parse->len = 0;
            
            /* Update the minimum width field. */
            parse->width -= res;
            
            found = TRUE;
        }
        
        if (c == 'F') {
            xdc_runtime_Types_Site site;
            
            /* Retrieve the file name string from the argument list */
            site.file = parse->aFlag ? (xdc_Char *) xdc_iargToPtr(va_arg(va, xdc_IArg)) :
                                       (xdc_Char *) va_arg(va, xdc_Char *);
            
            /* Retrieve the line number from the argument list. */
            site.line = parse->aFlag ? (xdc_Int) va_arg(va, xdc_IArg) : 
                                       (xdc_Int) va_arg(va, xdc_Int);
            
            /* 
             * Omit the 'mod' field, set it to 0.
             * '0' is a safe sentinel value - the IDs for named modules are 
             * 0x8000 and higher, and the IDs for unnamed modules go from 0x1
             * to 0x7fff.
             */
            site.mod = 0;
            
            /* 
             * Call putSite to format the file and line number.
             * If a precision was specified, it will be used as the maximum
             * string lengrth.
             */
            res = xdc_runtime_Text_putSite(&site, pbuf, parse->precis);
            
            /*
             * Set the length to 0 to indicate to 'doPrint' that nothing should
             * be copied from parse.ptr.
             */
            parse->len = 0;
       
            /* Update the minimum width field */
            parse->width -= res;
            
            found = TRUE;
        }
        
        if (c == 'S') {
            /* Retrieve the format string from the argument list */
            parse->ptr = parse->aFlag ? 
                (xdc_Char *) xdc_iargToPtr(va_arg(va, xdc_IArg)) :
                (xdc_Char *) va_arg(va, xdc_Char *);
            
            /* Update pva before passing it to doPrint. */
            *pva = va;
            
            /* Perform the recursive format. System_doPrint does not advance
             * the buffer pointer, so it has to be done explicitly.
             */
            res = xdc_runtime_System_doPrint__I(*pbuf, parse->precis, 
                                                parse->ptr, pva, parse->aFlag);

            if (*pbuf) {
                *pbuf += res;
            }
            
            /* Update the temporary variable with any changes to *pva */
            va = *pva;
            
            /*
             * Set the length to 0 to indicate to 'doPrint' that nothing should
             * be copied from parse.ptr
             */
            parse->len = 0;

            /* Update the minimum width field */
            parse->width -= res;
            
            /* Indicate that we were able to interpret the specifier */
            found = TRUE;
        }
        
    }

    if (c == 'f') {
        /* support arguments _after_ optional float support */
        if (parse->aFlag) {
            (void)va_arg(va, xdc_IArg);
        }
        else {
            (void)va_arg(va, double);
        }
    }    

    if (found == FALSE) {
        /* other character (like %) copy to output */
        *(parse->ptr) = c;
        parse->len = 1;
    }

    /*
     * Before returning, we must update the value of pva. We use a label here
     * so that all return points will go through this update.
     * The 'goto end' is here to ensure that there is always a reference to the
     * label (to avoid the compiler complaining). 
     */
    goto end; 
end:
    *pva = va;
    return (res);
}

/*
 * ======== xdc.runtime.SysMin TEMPLATE ========
 */


#if defined(__ti__)
extern int HOSTwrite(int, const char *, unsigned);
#elif (defined(gnu_targets_STD_) && defined(xdc_target__os_undefined))
extern int _write(int, char *, int);
#define HOSTwrite(x,y,z) _write((int)(x),(char *)(y),(int)(z))
#elif defined(__IAR_SYSTEMS_ICC__)
#include <yfuns.h>
#define HOSTwrite(x,y,z) __write((x),(unsigned char *)(y),(z))
#else
#include <stdio.h>
#endif

/*
 *  ======== SysMin_output__I ========
 *  HOSTWrite only writes a max of N chars at a time. The amount it writes
 *  is returned. This function loops until the entire buffer is written.
 *  Being a static function allows it to conditionally compile out.
 */
xdc_Void xdc_runtime_SysMin_output__I(xdc_Char *buf, xdc_UInt size)
{
#if defined(__ti__) || (defined(gnu_targets_STD_) && defined(xdc_target__os_undefined)) || defined (__IAR_SYSTEMS_ICC__)
    xdc_Int printCount;
    
    while (size != 0) {
        printCount = HOSTwrite(1, buf, size);
        if ((printCount <= 0) || (printCount > size)) {
            break;  /* ensure we never get stuck in an infinite loop */
        }
        size -= printCount;
        buf = buf + printCount;
    }    
#else
    fwrite(buf, 1, size, stdout);
#endif
}

/*
 * ======== xdc.runtime.Text TEMPLATE ========
 */


/*
 *  ======== xdc_runtime_Text_visitRope__I ========
 *  This function is indirectly called within Text.c through
 *  the visitRopeFxn configuration parameter of xdc.runtime.Text.
 */
void xdc_runtime_Text_visitRope__I(xdc_runtime_Text_RopeId rope,
    xdc_Fxn visFxn, xdc_Ptr visState)
{
    xdc_String stack[7];
    xdc_runtime_Text_visitRope2__I(rope, visFxn, visState, stack);
}


/*
 * ======== ti.catalog.arm.cortexm4.tiva.ce.Boot TEMPLATE ========
 */

#if defined(__ti__)
#pragma CODE_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_init, ".text:.bootCodeSection")
#endif

/*
 *  ======== ti_catalog_arm_cortexm4_tiva_ce_Boot_init ========
 */
xdc_Void ti_catalog_arm_cortexm4_tiva_ce_Boot_init()
{
    ti_catalog_arm_cortexm4_tiva_ce_Boot_sysCtlClockSet((xdc_ULong)
        (-1056963264));
}


/*
 * ======== ti.sdo.utils.Build TEMPLATE ========
 */


/*
 * ======== ti.catalog.arm.cortexm4.tiva.ce.Boot INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsEnabled__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsEnabled__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsEnabled ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsIncluded__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsIncluded__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsIncluded ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsMask__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsMask__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsMask ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsMask__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gateObj__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gateObj__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gateObj ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gateObj__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gatePrms__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gatePrms__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gatePrms ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gatePrms__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__id__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__id__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__id ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__id__C = (xdc_Bits16)0x8017;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerDefined__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerDefined__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerDefined ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerObj__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerObj__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerObj ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerObj__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn0__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn0__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn0 ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn0__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn1__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn1__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn1 ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn1__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn2__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn2__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn2 ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn2__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn4__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn4__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn4 ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn4__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn8__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn8__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn8 ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn8__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__startupDoneFxn__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__startupDoneFxn__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__startupDoneFxn ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__startupDoneFxn__C = ((CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__count__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__count__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__count ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__heap__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__heap__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__heap ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__sizeof__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__sizeof__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__sizeof ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__table__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__table__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__table ti_catalog_arm_cortexm4_tiva_ce_Boot_Object__table__C = 0;

/* A_mustUseEnhancedClockMode__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_A_mustUseEnhancedClockMode__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_A_mustUseEnhancedClockMode__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_A_mustUseEnhancedClockMode ti_catalog_arm_cortexm4_tiva_ce_Boot_A_mustUseEnhancedClockMode__C = (((xdc_runtime_Assert_Id)400) << 16 | 16);

/* A_mustNotUseEnhancedClockMode__C */
#pragma DATA_SECTION(ti_catalog_arm_cortexm4_tiva_ce_Boot_A_mustNotUseEnhancedClockMode__C, ".const:ti_catalog_arm_cortexm4_tiva_ce_Boot_A_mustNotUseEnhancedClockMode__C");
__FAR__ const CT__ti_catalog_arm_cortexm4_tiva_ce_Boot_A_mustNotUseEnhancedClockMode ti_catalog_arm_cortexm4_tiva_ce_Boot_A_mustNotUseEnhancedClockMode__C = (((xdc_runtime_Assert_Id)474) << 16 | 16);


/*
 * ======== ti.sdo.utils.NameServerRemoteNull INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_utils_NameServerRemoteNull_Object__DESC__C;

/* Object__PARAMS__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Object__PARAMS__C, ".const:ti_sdo_utils_NameServerRemoteNull_Object__PARAMS__C");
__FAR__ const ti_sdo_utils_NameServerRemoteNull_Params ti_sdo_utils_NameServerRemoteNull_Object__PARAMS__C = {
    sizeof (ti_sdo_utils_NameServerRemoteNull_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&ti_sdo_utils_NameServerRemoteNull_Object__PARAMS__C.__iprms, /* instance */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
ti_sdo_utils_NameServerRemoteNull_Module__ ti_sdo_utils_NameServerRemoteNull_Module__root__V = {
    {&ti_sdo_utils_NameServerRemoteNull_Module__root__V.link,  /* link.next */
    &ti_sdo_utils_NameServerRemoteNull_Module__root__V.link},  /* link.prev */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__diagsEnabled__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__diagsEnabled__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsEnabled ti_sdo_utils_NameServerRemoteNull_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__diagsIncluded__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__diagsIncluded__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsIncluded ti_sdo_utils_NameServerRemoteNull_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsMask ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__gateObj__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__gateObj__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__gateObj ti_sdo_utils_NameServerRemoteNull_Module__gateObj__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__gatePrms__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__gatePrms__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__gatePrms ti_sdo_utils_NameServerRemoteNull_Module__gatePrms__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__id__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__id__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__id ti_sdo_utils_NameServerRemoteNull_Module__id__C = (xdc_Bits16)0x801a;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__loggerDefined__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__loggerDefined__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerDefined ti_sdo_utils_NameServerRemoteNull_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__loggerObj__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__loggerObj__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerObj ti_sdo_utils_NameServerRemoteNull_Module__loggerObj__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn0__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn0__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn0 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn0__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn1__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn1__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn1 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn1__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn2__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn2__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn2 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn2__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn4__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn4__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn4 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn4__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn8__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn8__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn8 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn8__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Module__startupDoneFxn__C, ".const:ti_sdo_utils_NameServerRemoteNull_Module__startupDoneFxn__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__startupDoneFxn ti_sdo_utils_NameServerRemoteNull_Module__startupDoneFxn__C = ((CT__ti_sdo_utils_NameServerRemoteNull_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Object__count__C, ".const:ti_sdo_utils_NameServerRemoteNull_Object__count__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Object__count ti_sdo_utils_NameServerRemoteNull_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Object__heap__C, ".const:ti_sdo_utils_NameServerRemoteNull_Object__heap__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Object__heap ti_sdo_utils_NameServerRemoteNull_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Object__sizeof__C, ".const:ti_sdo_utils_NameServerRemoteNull_Object__sizeof__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Object__sizeof ti_sdo_utils_NameServerRemoteNull_Object__sizeof__C = sizeof(ti_sdo_utils_NameServerRemoteNull_Object__);

/* Object__table__C */
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Object__table__C, ".const:ti_sdo_utils_NameServerRemoteNull_Object__table__C");
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Object__table ti_sdo_utils_NameServerRemoteNull_Object__table__C = 0;


/*
 * ======== xdc.runtime.Assert INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__diagsEnabled__C, ".const:xdc_runtime_Assert_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Assert_Module__diagsEnabled xdc_runtime_Assert_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__diagsIncluded__C, ".const:xdc_runtime_Assert_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Assert_Module__diagsIncluded xdc_runtime_Assert_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__diagsMask__C, ".const:xdc_runtime_Assert_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Assert_Module__diagsMask xdc_runtime_Assert_Module__diagsMask__C = ((CT__xdc_runtime_Assert_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__gateObj__C, ".const:xdc_runtime_Assert_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Assert_Module__gateObj xdc_runtime_Assert_Module__gateObj__C = ((CT__xdc_runtime_Assert_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__gatePrms__C, ".const:xdc_runtime_Assert_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Assert_Module__gatePrms xdc_runtime_Assert_Module__gatePrms__C = ((CT__xdc_runtime_Assert_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__id__C, ".const:xdc_runtime_Assert_Module__id__C");
__FAR__ const CT__xdc_runtime_Assert_Module__id xdc_runtime_Assert_Module__id__C = (xdc_Bits16)0x8002;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerDefined__C, ".const:xdc_runtime_Assert_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Assert_Module__loggerDefined xdc_runtime_Assert_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerObj__C, ".const:xdc_runtime_Assert_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Assert_Module__loggerObj xdc_runtime_Assert_Module__loggerObj__C = ((CT__xdc_runtime_Assert_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn0__C, ".const:xdc_runtime_Assert_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn0 xdc_runtime_Assert_Module__loggerFxn0__C = ((CT__xdc_runtime_Assert_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn1__C, ".const:xdc_runtime_Assert_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn1 xdc_runtime_Assert_Module__loggerFxn1__C = ((CT__xdc_runtime_Assert_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn2__C, ".const:xdc_runtime_Assert_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn2 xdc_runtime_Assert_Module__loggerFxn2__C = ((CT__xdc_runtime_Assert_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn4__C, ".const:xdc_runtime_Assert_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn4 xdc_runtime_Assert_Module__loggerFxn4__C = ((CT__xdc_runtime_Assert_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn8__C, ".const:xdc_runtime_Assert_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn8 xdc_runtime_Assert_Module__loggerFxn8__C = ((CT__xdc_runtime_Assert_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Module__startupDoneFxn__C, ".const:xdc_runtime_Assert_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Assert_Module__startupDoneFxn xdc_runtime_Assert_Module__startupDoneFxn__C = ((CT__xdc_runtime_Assert_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Object__count__C, ".const:xdc_runtime_Assert_Object__count__C");
__FAR__ const CT__xdc_runtime_Assert_Object__count xdc_runtime_Assert_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Object__heap__C, ".const:xdc_runtime_Assert_Object__heap__C");
__FAR__ const CT__xdc_runtime_Assert_Object__heap xdc_runtime_Assert_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Object__sizeof__C, ".const:xdc_runtime_Assert_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Assert_Object__sizeof xdc_runtime_Assert_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Assert_Object__table__C, ".const:xdc_runtime_Assert_Object__table__C");
__FAR__ const CT__xdc_runtime_Assert_Object__table xdc_runtime_Assert_Object__table__C = 0;

/* E_assertFailed__C */
#pragma DATA_SECTION(xdc_runtime_Assert_E_assertFailed__C, ".const:xdc_runtime_Assert_E_assertFailed__C");
__FAR__ const CT__xdc_runtime_Assert_E_assertFailed xdc_runtime_Assert_E_assertFailed__C = (((xdc_runtime_Error_Id)2849) << 16 | 0);


/*
 * ======== xdc.runtime.Core INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__diagsEnabled__C, ".const:xdc_runtime_Core_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Core_Module__diagsEnabled xdc_runtime_Core_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__diagsIncluded__C, ".const:xdc_runtime_Core_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Core_Module__diagsIncluded xdc_runtime_Core_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__diagsMask__C, ".const:xdc_runtime_Core_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Core_Module__diagsMask xdc_runtime_Core_Module__diagsMask__C = ((CT__xdc_runtime_Core_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__gateObj__C, ".const:xdc_runtime_Core_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Core_Module__gateObj xdc_runtime_Core_Module__gateObj__C = ((CT__xdc_runtime_Core_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__gatePrms__C, ".const:xdc_runtime_Core_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Core_Module__gatePrms xdc_runtime_Core_Module__gatePrms__C = ((CT__xdc_runtime_Core_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__id__C, ".const:xdc_runtime_Core_Module__id__C");
__FAR__ const CT__xdc_runtime_Core_Module__id xdc_runtime_Core_Module__id__C = (xdc_Bits16)0x8003;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__loggerDefined__C, ".const:xdc_runtime_Core_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Core_Module__loggerDefined xdc_runtime_Core_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__loggerObj__C, ".const:xdc_runtime_Core_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Core_Module__loggerObj xdc_runtime_Core_Module__loggerObj__C = ((CT__xdc_runtime_Core_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn0__C, ".const:xdc_runtime_Core_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn0 xdc_runtime_Core_Module__loggerFxn0__C = ((CT__xdc_runtime_Core_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn1__C, ".const:xdc_runtime_Core_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn1 xdc_runtime_Core_Module__loggerFxn1__C = ((CT__xdc_runtime_Core_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn2__C, ".const:xdc_runtime_Core_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn2 xdc_runtime_Core_Module__loggerFxn2__C = ((CT__xdc_runtime_Core_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn4__C, ".const:xdc_runtime_Core_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn4 xdc_runtime_Core_Module__loggerFxn4__C = ((CT__xdc_runtime_Core_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn8__C, ".const:xdc_runtime_Core_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn8 xdc_runtime_Core_Module__loggerFxn8__C = ((CT__xdc_runtime_Core_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Core_Module__startupDoneFxn__C, ".const:xdc_runtime_Core_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Core_Module__startupDoneFxn xdc_runtime_Core_Module__startupDoneFxn__C = ((CT__xdc_runtime_Core_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Core_Object__count__C, ".const:xdc_runtime_Core_Object__count__C");
__FAR__ const CT__xdc_runtime_Core_Object__count xdc_runtime_Core_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Core_Object__heap__C, ".const:xdc_runtime_Core_Object__heap__C");
__FAR__ const CT__xdc_runtime_Core_Object__heap xdc_runtime_Core_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Core_Object__sizeof__C, ".const:xdc_runtime_Core_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Core_Object__sizeof xdc_runtime_Core_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Core_Object__table__C, ".const:xdc_runtime_Core_Object__table__C");
__FAR__ const CT__xdc_runtime_Core_Object__table xdc_runtime_Core_Object__table__C = 0;

/* A_initializedParams__C */
#pragma DATA_SECTION(xdc_runtime_Core_A_initializedParams__C, ".const:xdc_runtime_Core_A_initializedParams__C");
__FAR__ const CT__xdc_runtime_Core_A_initializedParams xdc_runtime_Core_A_initializedParams__C = (((xdc_runtime_Assert_Id)1) << 16 | 16);


/*
 * ======== xdc.runtime.Defaults INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__diagsEnabled__C, ".const:xdc_runtime_Defaults_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__diagsEnabled xdc_runtime_Defaults_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__diagsIncluded__C, ".const:xdc_runtime_Defaults_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__diagsIncluded xdc_runtime_Defaults_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__diagsMask__C, ".const:xdc_runtime_Defaults_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__diagsMask xdc_runtime_Defaults_Module__diagsMask__C = ((CT__xdc_runtime_Defaults_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__gateObj__C, ".const:xdc_runtime_Defaults_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__gateObj xdc_runtime_Defaults_Module__gateObj__C = ((CT__xdc_runtime_Defaults_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__gatePrms__C, ".const:xdc_runtime_Defaults_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__gatePrms xdc_runtime_Defaults_Module__gatePrms__C = ((CT__xdc_runtime_Defaults_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__id__C, ".const:xdc_runtime_Defaults_Module__id__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__id xdc_runtime_Defaults_Module__id__C = (xdc_Bits16)0x8004;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerDefined__C, ".const:xdc_runtime_Defaults_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerDefined xdc_runtime_Defaults_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerObj__C, ".const:xdc_runtime_Defaults_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerObj xdc_runtime_Defaults_Module__loggerObj__C = ((CT__xdc_runtime_Defaults_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn0__C, ".const:xdc_runtime_Defaults_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn0 xdc_runtime_Defaults_Module__loggerFxn0__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn1__C, ".const:xdc_runtime_Defaults_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn1 xdc_runtime_Defaults_Module__loggerFxn1__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn2__C, ".const:xdc_runtime_Defaults_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn2 xdc_runtime_Defaults_Module__loggerFxn2__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn4__C, ".const:xdc_runtime_Defaults_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn4 xdc_runtime_Defaults_Module__loggerFxn4__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn8__C, ".const:xdc_runtime_Defaults_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn8 xdc_runtime_Defaults_Module__loggerFxn8__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Module__startupDoneFxn__C, ".const:xdc_runtime_Defaults_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Defaults_Module__startupDoneFxn xdc_runtime_Defaults_Module__startupDoneFxn__C = ((CT__xdc_runtime_Defaults_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Object__count__C, ".const:xdc_runtime_Defaults_Object__count__C");
__FAR__ const CT__xdc_runtime_Defaults_Object__count xdc_runtime_Defaults_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Object__heap__C, ".const:xdc_runtime_Defaults_Object__heap__C");
__FAR__ const CT__xdc_runtime_Defaults_Object__heap xdc_runtime_Defaults_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Object__sizeof__C, ".const:xdc_runtime_Defaults_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Defaults_Object__sizeof xdc_runtime_Defaults_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Defaults_Object__table__C, ".const:xdc_runtime_Defaults_Object__table__C");
__FAR__ const CT__xdc_runtime_Defaults_Object__table xdc_runtime_Defaults_Object__table__C = 0;


/*
 * ======== xdc.runtime.Diags INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__diagsEnabled__C, ".const:xdc_runtime_Diags_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Diags_Module__diagsEnabled xdc_runtime_Diags_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__diagsIncluded__C, ".const:xdc_runtime_Diags_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Diags_Module__diagsIncluded xdc_runtime_Diags_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__diagsMask__C, ".const:xdc_runtime_Diags_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Diags_Module__diagsMask xdc_runtime_Diags_Module__diagsMask__C = ((CT__xdc_runtime_Diags_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__gateObj__C, ".const:xdc_runtime_Diags_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Diags_Module__gateObj xdc_runtime_Diags_Module__gateObj__C = ((CT__xdc_runtime_Diags_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__gatePrms__C, ".const:xdc_runtime_Diags_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Diags_Module__gatePrms xdc_runtime_Diags_Module__gatePrms__C = ((CT__xdc_runtime_Diags_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__id__C, ".const:xdc_runtime_Diags_Module__id__C");
__FAR__ const CT__xdc_runtime_Diags_Module__id xdc_runtime_Diags_Module__id__C = (xdc_Bits16)0x8005;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerDefined__C, ".const:xdc_runtime_Diags_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Diags_Module__loggerDefined xdc_runtime_Diags_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerObj__C, ".const:xdc_runtime_Diags_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Diags_Module__loggerObj xdc_runtime_Diags_Module__loggerObj__C = ((CT__xdc_runtime_Diags_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn0__C, ".const:xdc_runtime_Diags_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn0 xdc_runtime_Diags_Module__loggerFxn0__C = ((CT__xdc_runtime_Diags_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn1__C, ".const:xdc_runtime_Diags_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn1 xdc_runtime_Diags_Module__loggerFxn1__C = ((CT__xdc_runtime_Diags_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn2__C, ".const:xdc_runtime_Diags_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn2 xdc_runtime_Diags_Module__loggerFxn2__C = ((CT__xdc_runtime_Diags_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn4__C, ".const:xdc_runtime_Diags_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn4 xdc_runtime_Diags_Module__loggerFxn4__C = ((CT__xdc_runtime_Diags_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn8__C, ".const:xdc_runtime_Diags_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn8 xdc_runtime_Diags_Module__loggerFxn8__C = ((CT__xdc_runtime_Diags_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Module__startupDoneFxn__C, ".const:xdc_runtime_Diags_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Diags_Module__startupDoneFxn xdc_runtime_Diags_Module__startupDoneFxn__C = ((CT__xdc_runtime_Diags_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Object__count__C, ".const:xdc_runtime_Diags_Object__count__C");
__FAR__ const CT__xdc_runtime_Diags_Object__count xdc_runtime_Diags_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Object__heap__C, ".const:xdc_runtime_Diags_Object__heap__C");
__FAR__ const CT__xdc_runtime_Diags_Object__heap xdc_runtime_Diags_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Object__sizeof__C, ".const:xdc_runtime_Diags_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Diags_Object__sizeof xdc_runtime_Diags_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Diags_Object__table__C, ".const:xdc_runtime_Diags_Object__table__C");
__FAR__ const CT__xdc_runtime_Diags_Object__table xdc_runtime_Diags_Object__table__C = 0;

/* setMaskEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Diags_setMaskEnabled__C, ".const:xdc_runtime_Diags_setMaskEnabled__C");
__FAR__ const CT__xdc_runtime_Diags_setMaskEnabled xdc_runtime_Diags_setMaskEnabled__C = 0;

/* dictBase__C */
#pragma DATA_SECTION(xdc_runtime_Diags_dictBase__C, ".const:xdc_runtime_Diags_dictBase__C");
__FAR__ const CT__xdc_runtime_Diags_dictBase xdc_runtime_Diags_dictBase__C = ((CT__xdc_runtime_Diags_dictBase)0);


/*
 * ======== xdc.runtime.Error INITIALIZERS ========
 */

/* Module__state__V */
#if defined (__ICCARM__)
#pragma location = ".data_xdc_runtime_Error_Module__state__V"
#endif
#if defined(__GNUC__) && !(defined(__MACH__) && defined(__APPLE__))
#ifndef __TI_COMPILER_VERSION__
xdc_runtime_Error_Module_State__ xdc_runtime_Error_Module__state__V __attribute__ ((section(".data_xdc_runtime_Error_Module__state__V")));
#endif
#endif
xdc_runtime_Error_Module_State__ xdc_runtime_Error_Module__state__V = {
    (xdc_UInt16)0x0,  /* count */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__diagsEnabled__C, ".const:xdc_runtime_Error_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Error_Module__diagsEnabled xdc_runtime_Error_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__diagsIncluded__C, ".const:xdc_runtime_Error_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Error_Module__diagsIncluded xdc_runtime_Error_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__diagsMask__C, ".const:xdc_runtime_Error_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Error_Module__diagsMask xdc_runtime_Error_Module__diagsMask__C = ((CT__xdc_runtime_Error_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__gateObj__C, ".const:xdc_runtime_Error_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Error_Module__gateObj xdc_runtime_Error_Module__gateObj__C = ((CT__xdc_runtime_Error_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__gatePrms__C, ".const:xdc_runtime_Error_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Error_Module__gatePrms xdc_runtime_Error_Module__gatePrms__C = ((CT__xdc_runtime_Error_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__id__C, ".const:xdc_runtime_Error_Module__id__C");
__FAR__ const CT__xdc_runtime_Error_Module__id xdc_runtime_Error_Module__id__C = (xdc_Bits16)0x8006;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__loggerDefined__C, ".const:xdc_runtime_Error_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Error_Module__loggerDefined xdc_runtime_Error_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__loggerObj__C, ".const:xdc_runtime_Error_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Error_Module__loggerObj xdc_runtime_Error_Module__loggerObj__C = ((CT__xdc_runtime_Error_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn0__C, ".const:xdc_runtime_Error_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn0 xdc_runtime_Error_Module__loggerFxn0__C = ((CT__xdc_runtime_Error_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn1__C, ".const:xdc_runtime_Error_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn1 xdc_runtime_Error_Module__loggerFxn1__C = ((CT__xdc_runtime_Error_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn2__C, ".const:xdc_runtime_Error_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn2 xdc_runtime_Error_Module__loggerFxn2__C = ((CT__xdc_runtime_Error_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn4__C, ".const:xdc_runtime_Error_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn4 xdc_runtime_Error_Module__loggerFxn4__C = ((CT__xdc_runtime_Error_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn8__C, ".const:xdc_runtime_Error_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn8 xdc_runtime_Error_Module__loggerFxn8__C = ((CT__xdc_runtime_Error_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Error_Module__startupDoneFxn__C, ".const:xdc_runtime_Error_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Error_Module__startupDoneFxn xdc_runtime_Error_Module__startupDoneFxn__C = ((CT__xdc_runtime_Error_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Error_Object__count__C, ".const:xdc_runtime_Error_Object__count__C");
__FAR__ const CT__xdc_runtime_Error_Object__count xdc_runtime_Error_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Error_Object__heap__C, ".const:xdc_runtime_Error_Object__heap__C");
__FAR__ const CT__xdc_runtime_Error_Object__heap xdc_runtime_Error_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Error_Object__sizeof__C, ".const:xdc_runtime_Error_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Error_Object__sizeof xdc_runtime_Error_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Error_Object__table__C, ".const:xdc_runtime_Error_Object__table__C");
__FAR__ const CT__xdc_runtime_Error_Object__table xdc_runtime_Error_Object__table__C = 0;

/* policyFxn__C */
#pragma DATA_SECTION(xdc_runtime_Error_policyFxn__C, ".const:xdc_runtime_Error_policyFxn__C");
__FAR__ const CT__xdc_runtime_Error_policyFxn xdc_runtime_Error_policyFxn__C = ((CT__xdc_runtime_Error_policyFxn)((xdc_Fxn)xdc_runtime_Error_policyDefault__E));

/* E_generic__C */
#pragma DATA_SECTION(xdc_runtime_Error_E_generic__C, ".const:xdc_runtime_Error_E_generic__C");
__FAR__ const CT__xdc_runtime_Error_E_generic xdc_runtime_Error_E_generic__C = (((xdc_runtime_Error_Id)2871) << 16 | 0);

/* E_memory__C */
#pragma DATA_SECTION(xdc_runtime_Error_E_memory__C, ".const:xdc_runtime_Error_E_memory__C");
__FAR__ const CT__xdc_runtime_Error_E_memory xdc_runtime_Error_E_memory__C = (((xdc_runtime_Error_Id)2875) << 16 | 0);

/* E_msgCode__C */
#pragma DATA_SECTION(xdc_runtime_Error_E_msgCode__C, ".const:xdc_runtime_Error_E_msgCode__C");
__FAR__ const CT__xdc_runtime_Error_E_msgCode xdc_runtime_Error_E_msgCode__C = (((xdc_runtime_Error_Id)2909) << 16 | 0);

/* policy__C */
#pragma DATA_SECTION(xdc_runtime_Error_policy__C, ".const:xdc_runtime_Error_policy__C");
__FAR__ const CT__xdc_runtime_Error_policy xdc_runtime_Error_policy__C = xdc_runtime_Error_UNWIND;

/* raiseHook__C */
#pragma DATA_SECTION(xdc_runtime_Error_raiseHook__C, ".const:xdc_runtime_Error_raiseHook__C");
__FAR__ const CT__xdc_runtime_Error_raiseHook xdc_runtime_Error_raiseHook__C = ((CT__xdc_runtime_Error_raiseHook)((xdc_Fxn)xdc_runtime_Error_print__E));

/* maxDepth__C */
#pragma DATA_SECTION(xdc_runtime_Error_maxDepth__C, ".const:xdc_runtime_Error_maxDepth__C");
__FAR__ const CT__xdc_runtime_Error_maxDepth xdc_runtime_Error_maxDepth__C = (xdc_UInt16)0x10;


/*
 * ======== xdc.runtime.Gate INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__diagsEnabled__C, ".const:xdc_runtime_Gate_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Gate_Module__diagsEnabled xdc_runtime_Gate_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__diagsIncluded__C, ".const:xdc_runtime_Gate_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Gate_Module__diagsIncluded xdc_runtime_Gate_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__diagsMask__C, ".const:xdc_runtime_Gate_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Gate_Module__diagsMask xdc_runtime_Gate_Module__diagsMask__C = ((CT__xdc_runtime_Gate_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__gateObj__C, ".const:xdc_runtime_Gate_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Gate_Module__gateObj xdc_runtime_Gate_Module__gateObj__C = ((CT__xdc_runtime_Gate_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__gatePrms__C, ".const:xdc_runtime_Gate_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Gate_Module__gatePrms xdc_runtime_Gate_Module__gatePrms__C = ((CT__xdc_runtime_Gate_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__id__C, ".const:xdc_runtime_Gate_Module__id__C");
__FAR__ const CT__xdc_runtime_Gate_Module__id xdc_runtime_Gate_Module__id__C = (xdc_Bits16)0x8007;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerDefined__C, ".const:xdc_runtime_Gate_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Gate_Module__loggerDefined xdc_runtime_Gate_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerObj__C, ".const:xdc_runtime_Gate_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Gate_Module__loggerObj xdc_runtime_Gate_Module__loggerObj__C = ((CT__xdc_runtime_Gate_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn0__C, ".const:xdc_runtime_Gate_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn0 xdc_runtime_Gate_Module__loggerFxn0__C = ((CT__xdc_runtime_Gate_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn1__C, ".const:xdc_runtime_Gate_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn1 xdc_runtime_Gate_Module__loggerFxn1__C = ((CT__xdc_runtime_Gate_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn2__C, ".const:xdc_runtime_Gate_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn2 xdc_runtime_Gate_Module__loggerFxn2__C = ((CT__xdc_runtime_Gate_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn4__C, ".const:xdc_runtime_Gate_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn4 xdc_runtime_Gate_Module__loggerFxn4__C = ((CT__xdc_runtime_Gate_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn8__C, ".const:xdc_runtime_Gate_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn8 xdc_runtime_Gate_Module__loggerFxn8__C = ((CT__xdc_runtime_Gate_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Module__startupDoneFxn__C, ".const:xdc_runtime_Gate_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Gate_Module__startupDoneFxn xdc_runtime_Gate_Module__startupDoneFxn__C = ((CT__xdc_runtime_Gate_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Object__count__C, ".const:xdc_runtime_Gate_Object__count__C");
__FAR__ const CT__xdc_runtime_Gate_Object__count xdc_runtime_Gate_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Object__heap__C, ".const:xdc_runtime_Gate_Object__heap__C");
__FAR__ const CT__xdc_runtime_Gate_Object__heap xdc_runtime_Gate_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Object__sizeof__C, ".const:xdc_runtime_Gate_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Gate_Object__sizeof xdc_runtime_Gate_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Gate_Object__table__C, ".const:xdc_runtime_Gate_Object__table__C");
__FAR__ const CT__xdc_runtime_Gate_Object__table xdc_runtime_Gate_Object__table__C = 0;


/*
 * ======== xdc.runtime.GateNull INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_GateNull_Object__DESC__C;

/* Object__PARAMS__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Object__PARAMS__C, ".const:xdc_runtime_GateNull_Object__PARAMS__C");
__FAR__ const xdc_runtime_GateNull_Params xdc_runtime_GateNull_Object__PARAMS__C = {
    sizeof (xdc_runtime_GateNull_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&xdc_runtime_GateNull_Object__PARAMS__C.__iprms, /* instance */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
xdc_runtime_GateNull_Module__ xdc_runtime_GateNull_Module__root__V = {
    {&xdc_runtime_GateNull_Module__root__V.link,  /* link.next */
    &xdc_runtime_GateNull_Module__root__V.link},  /* link.prev */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__diagsEnabled__C, ".const:xdc_runtime_GateNull_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__diagsEnabled xdc_runtime_GateNull_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__diagsIncluded__C, ".const:xdc_runtime_GateNull_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__diagsIncluded xdc_runtime_GateNull_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__diagsMask__C, ".const:xdc_runtime_GateNull_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__diagsMask xdc_runtime_GateNull_Module__diagsMask__C = ((CT__xdc_runtime_GateNull_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__gateObj__C, ".const:xdc_runtime_GateNull_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__gateObj xdc_runtime_GateNull_Module__gateObj__C = ((CT__xdc_runtime_GateNull_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__gatePrms__C, ".const:xdc_runtime_GateNull_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__gatePrms xdc_runtime_GateNull_Module__gatePrms__C = ((CT__xdc_runtime_GateNull_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__id__C, ".const:xdc_runtime_GateNull_Module__id__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__id xdc_runtime_GateNull_Module__id__C = (xdc_Bits16)0x8008;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__loggerDefined__C, ".const:xdc_runtime_GateNull_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__loggerDefined xdc_runtime_GateNull_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__loggerObj__C, ".const:xdc_runtime_GateNull_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__loggerObj xdc_runtime_GateNull_Module__loggerObj__C = ((CT__xdc_runtime_GateNull_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__loggerFxn0__C, ".const:xdc_runtime_GateNull_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__loggerFxn0 xdc_runtime_GateNull_Module__loggerFxn0__C = ((CT__xdc_runtime_GateNull_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__loggerFxn1__C, ".const:xdc_runtime_GateNull_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__loggerFxn1 xdc_runtime_GateNull_Module__loggerFxn1__C = ((CT__xdc_runtime_GateNull_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__loggerFxn2__C, ".const:xdc_runtime_GateNull_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__loggerFxn2 xdc_runtime_GateNull_Module__loggerFxn2__C = ((CT__xdc_runtime_GateNull_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__loggerFxn4__C, ".const:xdc_runtime_GateNull_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__loggerFxn4 xdc_runtime_GateNull_Module__loggerFxn4__C = ((CT__xdc_runtime_GateNull_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__loggerFxn8__C, ".const:xdc_runtime_GateNull_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__loggerFxn8 xdc_runtime_GateNull_Module__loggerFxn8__C = ((CT__xdc_runtime_GateNull_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Module__startupDoneFxn__C, ".const:xdc_runtime_GateNull_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_GateNull_Module__startupDoneFxn xdc_runtime_GateNull_Module__startupDoneFxn__C = ((CT__xdc_runtime_GateNull_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Object__count__C, ".const:xdc_runtime_GateNull_Object__count__C");
__FAR__ const CT__xdc_runtime_GateNull_Object__count xdc_runtime_GateNull_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Object__heap__C, ".const:xdc_runtime_GateNull_Object__heap__C");
__FAR__ const CT__xdc_runtime_GateNull_Object__heap xdc_runtime_GateNull_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Object__sizeof__C, ".const:xdc_runtime_GateNull_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_GateNull_Object__sizeof xdc_runtime_GateNull_Object__sizeof__C = sizeof(xdc_runtime_GateNull_Object__);

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_GateNull_Object__table__C, ".const:xdc_runtime_GateNull_Object__table__C");
__FAR__ const CT__xdc_runtime_GateNull_Object__table xdc_runtime_GateNull_Object__table__C = 0;


/*
 * ======== xdc.runtime.HeapStd INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_HeapStd_Object__DESC__C;

/* Object__PARAMS__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Object__PARAMS__C, ".const:xdc_runtime_HeapStd_Object__PARAMS__C");
__FAR__ const xdc_runtime_HeapStd_Params xdc_runtime_HeapStd_Object__PARAMS__C = {
    sizeof (xdc_runtime_HeapStd_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&xdc_runtime_HeapStd_Object__PARAMS__C.__iprms, /* instance */
    ((xdc_UArg)(0x0)),  /* size */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
xdc_runtime_HeapStd_Module__ xdc_runtime_HeapStd_Module__root__V = {
    {&xdc_runtime_HeapStd_Module__root__V.link,  /* link.next */
    &xdc_runtime_HeapStd_Module__root__V.link},  /* link.prev */
};

/* Object__table__V */
xdc_runtime_HeapStd_Object__ xdc_runtime_HeapStd_Object__table__V[1] = {
    {/* instance#0 */
        &xdc_runtime_HeapStd_Module__FXNS__C,
        ((xdc_UArg)((-0x0 - 1))),  /* remainSize */
        ((xdc_UArg)((-0x0 - 1))),  /* startSize */
    },
};

/* Module__state__V */
#if defined (__ICCARM__)
#pragma location = ".data_xdc_runtime_HeapStd_Module__state__V"
#endif
#if defined(__GNUC__) && !(defined(__MACH__) && defined(__APPLE__))
#ifndef __TI_COMPILER_VERSION__
xdc_runtime_HeapStd_Module_State__ xdc_runtime_HeapStd_Module__state__V __attribute__ ((section(".data_xdc_runtime_HeapStd_Module__state__V")));
#endif
#endif
xdc_runtime_HeapStd_Module_State__ xdc_runtime_HeapStd_Module__state__V = {
    ((xdc_UArg)(0x1000)),  /* remainRTSSize */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__diagsEnabled__C, ".const:xdc_runtime_HeapStd_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__diagsEnabled xdc_runtime_HeapStd_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__diagsIncluded__C, ".const:xdc_runtime_HeapStd_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__diagsIncluded xdc_runtime_HeapStd_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__diagsMask__C, ".const:xdc_runtime_HeapStd_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__diagsMask xdc_runtime_HeapStd_Module__diagsMask__C = ((CT__xdc_runtime_HeapStd_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__gateObj__C, ".const:xdc_runtime_HeapStd_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__gateObj xdc_runtime_HeapStd_Module__gateObj__C = ((CT__xdc_runtime_HeapStd_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__gatePrms__C, ".const:xdc_runtime_HeapStd_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__gatePrms xdc_runtime_HeapStd_Module__gatePrms__C = ((CT__xdc_runtime_HeapStd_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__id__C, ".const:xdc_runtime_HeapStd_Module__id__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__id xdc_runtime_HeapStd_Module__id__C = (xdc_Bits16)0x800c;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerDefined__C, ".const:xdc_runtime_HeapStd_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerDefined xdc_runtime_HeapStd_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerObj__C, ".const:xdc_runtime_HeapStd_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerObj xdc_runtime_HeapStd_Module__loggerObj__C = ((CT__xdc_runtime_HeapStd_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn0__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn0 xdc_runtime_HeapStd_Module__loggerFxn0__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn1__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn1 xdc_runtime_HeapStd_Module__loggerFxn1__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn2__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn2 xdc_runtime_HeapStd_Module__loggerFxn2__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn4__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn4 xdc_runtime_HeapStd_Module__loggerFxn4__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn8__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn8 xdc_runtime_HeapStd_Module__loggerFxn8__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Module__startupDoneFxn__C, ".const:xdc_runtime_HeapStd_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_HeapStd_Module__startupDoneFxn xdc_runtime_HeapStd_Module__startupDoneFxn__C = ((CT__xdc_runtime_HeapStd_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Object__count__C, ".const:xdc_runtime_HeapStd_Object__count__C");
__FAR__ const CT__xdc_runtime_HeapStd_Object__count xdc_runtime_HeapStd_Object__count__C = 1;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Object__heap__C, ".const:xdc_runtime_HeapStd_Object__heap__C");
__FAR__ const CT__xdc_runtime_HeapStd_Object__heap xdc_runtime_HeapStd_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Object__sizeof__C, ".const:xdc_runtime_HeapStd_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_HeapStd_Object__sizeof xdc_runtime_HeapStd_Object__sizeof__C = sizeof(xdc_runtime_HeapStd_Object__);

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_Object__table__C, ".const:xdc_runtime_HeapStd_Object__table__C");
__FAR__ const CT__xdc_runtime_HeapStd_Object__table xdc_runtime_HeapStd_Object__table__C = xdc_runtime_HeapStd_Object__table__V;

/* E_noRTSMemory__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_E_noRTSMemory__C, ".const:xdc_runtime_HeapStd_E_noRTSMemory__C");
__FAR__ const CT__xdc_runtime_HeapStd_E_noRTSMemory xdc_runtime_HeapStd_E_noRTSMemory__C = (((xdc_runtime_Error_Id)2994) << 16 | 0);

/* A_zeroSize__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_A_zeroSize__C, ".const:xdc_runtime_HeapStd_A_zeroSize__C");
__FAR__ const CT__xdc_runtime_HeapStd_A_zeroSize xdc_runtime_HeapStd_A_zeroSize__C = (((xdc_runtime_Assert_Id)95) << 16 | 16);

/* A_align__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_A_align__C, ".const:xdc_runtime_HeapStd_A_align__C");
__FAR__ const CT__xdc_runtime_HeapStd_A_align xdc_runtime_HeapStd_A_align__C = (((xdc_runtime_Assert_Id)140) << 16 | 16);

/* A_invalidTotalFreeSize__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_A_invalidTotalFreeSize__C, ".const:xdc_runtime_HeapStd_A_invalidTotalFreeSize__C");
__FAR__ const CT__xdc_runtime_HeapStd_A_invalidTotalFreeSize xdc_runtime_HeapStd_A_invalidTotalFreeSize__C = (((xdc_runtime_Assert_Id)185) << 16 | 16);

/* A_invalidAlignment__C */
#pragma DATA_SECTION(xdc_runtime_HeapStd_A_invalidAlignment__C, ".const:xdc_runtime_HeapStd_A_invalidAlignment__C");
__FAR__ const CT__xdc_runtime_HeapStd_A_invalidAlignment xdc_runtime_HeapStd_A_invalidAlignment__C = (((xdc_runtime_Assert_Id)246) << 16 | 16);


/*
 * ======== xdc.runtime.Log INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__diagsEnabled__C, ".const:xdc_runtime_Log_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Log_Module__diagsEnabled xdc_runtime_Log_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__diagsIncluded__C, ".const:xdc_runtime_Log_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Log_Module__diagsIncluded xdc_runtime_Log_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__diagsMask__C, ".const:xdc_runtime_Log_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Log_Module__diagsMask xdc_runtime_Log_Module__diagsMask__C = ((CT__xdc_runtime_Log_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__gateObj__C, ".const:xdc_runtime_Log_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Log_Module__gateObj xdc_runtime_Log_Module__gateObj__C = ((CT__xdc_runtime_Log_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__gatePrms__C, ".const:xdc_runtime_Log_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Log_Module__gatePrms xdc_runtime_Log_Module__gatePrms__C = ((CT__xdc_runtime_Log_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__id__C, ".const:xdc_runtime_Log_Module__id__C");
__FAR__ const CT__xdc_runtime_Log_Module__id xdc_runtime_Log_Module__id__C = (xdc_Bits16)0x8009;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__loggerDefined__C, ".const:xdc_runtime_Log_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Log_Module__loggerDefined xdc_runtime_Log_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__loggerObj__C, ".const:xdc_runtime_Log_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Log_Module__loggerObj xdc_runtime_Log_Module__loggerObj__C = ((CT__xdc_runtime_Log_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn0__C, ".const:xdc_runtime_Log_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn0 xdc_runtime_Log_Module__loggerFxn0__C = ((CT__xdc_runtime_Log_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn1__C, ".const:xdc_runtime_Log_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn1 xdc_runtime_Log_Module__loggerFxn1__C = ((CT__xdc_runtime_Log_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn2__C, ".const:xdc_runtime_Log_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn2 xdc_runtime_Log_Module__loggerFxn2__C = ((CT__xdc_runtime_Log_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn4__C, ".const:xdc_runtime_Log_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn4 xdc_runtime_Log_Module__loggerFxn4__C = ((CT__xdc_runtime_Log_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn8__C, ".const:xdc_runtime_Log_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn8 xdc_runtime_Log_Module__loggerFxn8__C = ((CT__xdc_runtime_Log_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Log_Module__startupDoneFxn__C, ".const:xdc_runtime_Log_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Log_Module__startupDoneFxn xdc_runtime_Log_Module__startupDoneFxn__C = ((CT__xdc_runtime_Log_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Log_Object__count__C, ".const:xdc_runtime_Log_Object__count__C");
__FAR__ const CT__xdc_runtime_Log_Object__count xdc_runtime_Log_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Log_Object__heap__C, ".const:xdc_runtime_Log_Object__heap__C");
__FAR__ const CT__xdc_runtime_Log_Object__heap xdc_runtime_Log_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Log_Object__sizeof__C, ".const:xdc_runtime_Log_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Log_Object__sizeof xdc_runtime_Log_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Log_Object__table__C, ".const:xdc_runtime_Log_Object__table__C");
__FAR__ const CT__xdc_runtime_Log_Object__table xdc_runtime_Log_Object__table__C = 0;

/* L_construct__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_construct__C, ".const:xdc_runtime_Log_L_construct__C");
__FAR__ const CT__xdc_runtime_Log_L_construct xdc_runtime_Log_L_construct__C = (((xdc_runtime_Log_Event)3389) << 16 | 4);

/* L_create__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_create__C, ".const:xdc_runtime_Log_L_create__C");
__FAR__ const CT__xdc_runtime_Log_L_create xdc_runtime_Log_L_create__C = (((xdc_runtime_Log_Event)3413) << 16 | 4);

/* L_destruct__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_destruct__C, ".const:xdc_runtime_Log_L_destruct__C");
__FAR__ const CT__xdc_runtime_Log_L_destruct xdc_runtime_Log_L_destruct__C = (((xdc_runtime_Log_Event)3434) << 16 | 4);

/* L_delete__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_delete__C, ".const:xdc_runtime_Log_L_delete__C");
__FAR__ const CT__xdc_runtime_Log_L_delete xdc_runtime_Log_L_delete__C = (((xdc_runtime_Log_Event)3453) << 16 | 4);

/* L_error__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_error__C, ".const:xdc_runtime_Log_L_error__C");
__FAR__ const CT__xdc_runtime_Log_L_error xdc_runtime_Log_L_error__C = (((xdc_runtime_Log_Event)3470) << 16 | 192);

/* L_warning__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_warning__C, ".const:xdc_runtime_Log_L_warning__C");
__FAR__ const CT__xdc_runtime_Log_L_warning xdc_runtime_Log_L_warning__C = (((xdc_runtime_Log_Event)3484) << 16 | 224);

/* L_info__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_info__C, ".const:xdc_runtime_Log_L_info__C");
__FAR__ const CT__xdc_runtime_Log_L_info xdc_runtime_Log_L_info__C = (((xdc_runtime_Log_Event)3500) << 16 | 16384);

/* L_start__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_start__C, ".const:xdc_runtime_Log_L_start__C");
__FAR__ const CT__xdc_runtime_Log_L_start xdc_runtime_Log_L_start__C = (((xdc_runtime_Log_Event)3507) << 16 | 32768);

/* L_stop__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_stop__C, ".const:xdc_runtime_Log_L_stop__C");
__FAR__ const CT__xdc_runtime_Log_L_stop xdc_runtime_Log_L_stop__C = (((xdc_runtime_Log_Event)3518) << 16 | 32768);

/* L_startInstance__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_startInstance__C, ".const:xdc_runtime_Log_L_startInstance__C");
__FAR__ const CT__xdc_runtime_Log_L_startInstance xdc_runtime_Log_L_startInstance__C = (((xdc_runtime_Log_Event)3528) << 16 | 32768);

/* L_stopInstance__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_stopInstance__C, ".const:xdc_runtime_Log_L_stopInstance__C");
__FAR__ const CT__xdc_runtime_Log_L_stopInstance xdc_runtime_Log_L_stopInstance__C = (((xdc_runtime_Log_Event)3547) << 16 | 32768);


/*
 * ======== xdc.runtime.Main INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__diagsEnabled__C, ".const:xdc_runtime_Main_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Main_Module__diagsEnabled xdc_runtime_Main_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__diagsIncluded__C, ".const:xdc_runtime_Main_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Main_Module__diagsIncluded xdc_runtime_Main_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__diagsMask__C, ".const:xdc_runtime_Main_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Main_Module__diagsMask xdc_runtime_Main_Module__diagsMask__C = ((CT__xdc_runtime_Main_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__gateObj__C, ".const:xdc_runtime_Main_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Main_Module__gateObj xdc_runtime_Main_Module__gateObj__C = ((CT__xdc_runtime_Main_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__gatePrms__C, ".const:xdc_runtime_Main_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Main_Module__gatePrms xdc_runtime_Main_Module__gatePrms__C = ((CT__xdc_runtime_Main_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__id__C, ".const:xdc_runtime_Main_Module__id__C");
__FAR__ const CT__xdc_runtime_Main_Module__id xdc_runtime_Main_Module__id__C = (xdc_Bits16)0x800a;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__loggerDefined__C, ".const:xdc_runtime_Main_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Main_Module__loggerDefined xdc_runtime_Main_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__loggerObj__C, ".const:xdc_runtime_Main_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Main_Module__loggerObj xdc_runtime_Main_Module__loggerObj__C = ((CT__xdc_runtime_Main_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn0__C, ".const:xdc_runtime_Main_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn0 xdc_runtime_Main_Module__loggerFxn0__C = ((CT__xdc_runtime_Main_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn1__C, ".const:xdc_runtime_Main_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn1 xdc_runtime_Main_Module__loggerFxn1__C = ((CT__xdc_runtime_Main_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn2__C, ".const:xdc_runtime_Main_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn2 xdc_runtime_Main_Module__loggerFxn2__C = ((CT__xdc_runtime_Main_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn4__C, ".const:xdc_runtime_Main_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn4 xdc_runtime_Main_Module__loggerFxn4__C = ((CT__xdc_runtime_Main_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn8__C, ".const:xdc_runtime_Main_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn8 xdc_runtime_Main_Module__loggerFxn8__C = ((CT__xdc_runtime_Main_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Main_Module__startupDoneFxn__C, ".const:xdc_runtime_Main_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Main_Module__startupDoneFxn xdc_runtime_Main_Module__startupDoneFxn__C = ((CT__xdc_runtime_Main_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Main_Object__count__C, ".const:xdc_runtime_Main_Object__count__C");
__FAR__ const CT__xdc_runtime_Main_Object__count xdc_runtime_Main_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Main_Object__heap__C, ".const:xdc_runtime_Main_Object__heap__C");
__FAR__ const CT__xdc_runtime_Main_Object__heap xdc_runtime_Main_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Main_Object__sizeof__C, ".const:xdc_runtime_Main_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Main_Object__sizeof xdc_runtime_Main_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Main_Object__table__C, ".const:xdc_runtime_Main_Object__table__C");
__FAR__ const CT__xdc_runtime_Main_Object__table xdc_runtime_Main_Object__table__C = 0;


/*
 * ======== xdc.runtime.Main_Module_GateProxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.Memory INITIALIZERS ========
 */

/* Module__state__V */
#if defined (__ICCARM__)
#pragma location = ".data_xdc_runtime_Memory_Module__state__V"
#endif
#if defined(__GNUC__) && !(defined(__MACH__) && defined(__APPLE__))
#ifndef __TI_COMPILER_VERSION__
xdc_runtime_Memory_Module_State__ xdc_runtime_Memory_Module__state__V __attribute__ ((section(".data_xdc_runtime_Memory_Module__state__V")));
#endif
#endif
xdc_runtime_Memory_Module_State__ xdc_runtime_Memory_Module__state__V = {
    (xdc_SizeT)0x8,  /* maxDefaultTypeAlign */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__diagsEnabled__C, ".const:xdc_runtime_Memory_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Memory_Module__diagsEnabled xdc_runtime_Memory_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__diagsIncluded__C, ".const:xdc_runtime_Memory_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Memory_Module__diagsIncluded xdc_runtime_Memory_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__diagsMask__C, ".const:xdc_runtime_Memory_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Memory_Module__diagsMask xdc_runtime_Memory_Module__diagsMask__C = ((CT__xdc_runtime_Memory_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__gateObj__C, ".const:xdc_runtime_Memory_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Memory_Module__gateObj xdc_runtime_Memory_Module__gateObj__C = ((CT__xdc_runtime_Memory_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__gatePrms__C, ".const:xdc_runtime_Memory_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Memory_Module__gatePrms xdc_runtime_Memory_Module__gatePrms__C = ((CT__xdc_runtime_Memory_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__id__C, ".const:xdc_runtime_Memory_Module__id__C");
__FAR__ const CT__xdc_runtime_Memory_Module__id xdc_runtime_Memory_Module__id__C = (xdc_Bits16)0x800b;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerDefined__C, ".const:xdc_runtime_Memory_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Memory_Module__loggerDefined xdc_runtime_Memory_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerObj__C, ".const:xdc_runtime_Memory_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Memory_Module__loggerObj xdc_runtime_Memory_Module__loggerObj__C = ((CT__xdc_runtime_Memory_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn0__C, ".const:xdc_runtime_Memory_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn0 xdc_runtime_Memory_Module__loggerFxn0__C = ((CT__xdc_runtime_Memory_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn1__C, ".const:xdc_runtime_Memory_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn1 xdc_runtime_Memory_Module__loggerFxn1__C = ((CT__xdc_runtime_Memory_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn2__C, ".const:xdc_runtime_Memory_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn2 xdc_runtime_Memory_Module__loggerFxn2__C = ((CT__xdc_runtime_Memory_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn4__C, ".const:xdc_runtime_Memory_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn4 xdc_runtime_Memory_Module__loggerFxn4__C = ((CT__xdc_runtime_Memory_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn8__C, ".const:xdc_runtime_Memory_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn8 xdc_runtime_Memory_Module__loggerFxn8__C = ((CT__xdc_runtime_Memory_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Module__startupDoneFxn__C, ".const:xdc_runtime_Memory_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Memory_Module__startupDoneFxn xdc_runtime_Memory_Module__startupDoneFxn__C = ((CT__xdc_runtime_Memory_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Object__count__C, ".const:xdc_runtime_Memory_Object__count__C");
__FAR__ const CT__xdc_runtime_Memory_Object__count xdc_runtime_Memory_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Object__heap__C, ".const:xdc_runtime_Memory_Object__heap__C");
__FAR__ const CT__xdc_runtime_Memory_Object__heap xdc_runtime_Memory_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Object__sizeof__C, ".const:xdc_runtime_Memory_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Memory_Object__sizeof xdc_runtime_Memory_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Memory_Object__table__C, ".const:xdc_runtime_Memory_Object__table__C");
__FAR__ const CT__xdc_runtime_Memory_Object__table xdc_runtime_Memory_Object__table__C = 0;

/* defaultHeapInstance__C */
#pragma DATA_SECTION(xdc_runtime_Memory_defaultHeapInstance__C, ".const:xdc_runtime_Memory_defaultHeapInstance__C");
__FAR__ const CT__xdc_runtime_Memory_defaultHeapInstance xdc_runtime_Memory_defaultHeapInstance__C = (xdc_runtime_IHeap_Handle)&xdc_runtime_HeapStd_Object__table__V[0];


/*
 * ======== xdc.runtime.Memory_HeapProxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.Registry INITIALIZERS ========
 */

/* Module__state__V */
#if defined (__ICCARM__)
#pragma location = ".data_xdc_runtime_Registry_Module__state__V"
#endif
#if defined(__GNUC__) && !(defined(__MACH__) && defined(__APPLE__))
#ifndef __TI_COMPILER_VERSION__
xdc_runtime_Registry_Module_State__ xdc_runtime_Registry_Module__state__V __attribute__ ((section(".data_xdc_runtime_Registry_Module__state__V")));
#endif
#endif
xdc_runtime_Registry_Module_State__ xdc_runtime_Registry_Module__state__V = {
    ((xdc_runtime_Types_RegDesc*)0),  /* listHead */
    (xdc_Bits16)0x7fff,  /* curId */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__diagsEnabled__C, ".const:xdc_runtime_Registry_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Registry_Module__diagsEnabled xdc_runtime_Registry_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__diagsIncluded__C, ".const:xdc_runtime_Registry_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Registry_Module__diagsIncluded xdc_runtime_Registry_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__diagsMask__C, ".const:xdc_runtime_Registry_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Registry_Module__diagsMask xdc_runtime_Registry_Module__diagsMask__C = ((CT__xdc_runtime_Registry_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__gateObj__C, ".const:xdc_runtime_Registry_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Registry_Module__gateObj xdc_runtime_Registry_Module__gateObj__C = ((CT__xdc_runtime_Registry_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__gatePrms__C, ".const:xdc_runtime_Registry_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Registry_Module__gatePrms xdc_runtime_Registry_Module__gatePrms__C = ((CT__xdc_runtime_Registry_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__id__C, ".const:xdc_runtime_Registry_Module__id__C");
__FAR__ const CT__xdc_runtime_Registry_Module__id xdc_runtime_Registry_Module__id__C = (xdc_Bits16)0x800d;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerDefined__C, ".const:xdc_runtime_Registry_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Registry_Module__loggerDefined xdc_runtime_Registry_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerObj__C, ".const:xdc_runtime_Registry_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Registry_Module__loggerObj xdc_runtime_Registry_Module__loggerObj__C = ((CT__xdc_runtime_Registry_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn0__C, ".const:xdc_runtime_Registry_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn0 xdc_runtime_Registry_Module__loggerFxn0__C = ((CT__xdc_runtime_Registry_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn1__C, ".const:xdc_runtime_Registry_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn1 xdc_runtime_Registry_Module__loggerFxn1__C = ((CT__xdc_runtime_Registry_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn2__C, ".const:xdc_runtime_Registry_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn2 xdc_runtime_Registry_Module__loggerFxn2__C = ((CT__xdc_runtime_Registry_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn4__C, ".const:xdc_runtime_Registry_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn4 xdc_runtime_Registry_Module__loggerFxn4__C = ((CT__xdc_runtime_Registry_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn8__C, ".const:xdc_runtime_Registry_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn8 xdc_runtime_Registry_Module__loggerFxn8__C = ((CT__xdc_runtime_Registry_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Module__startupDoneFxn__C, ".const:xdc_runtime_Registry_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Registry_Module__startupDoneFxn xdc_runtime_Registry_Module__startupDoneFxn__C = ((CT__xdc_runtime_Registry_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Object__count__C, ".const:xdc_runtime_Registry_Object__count__C");
__FAR__ const CT__xdc_runtime_Registry_Object__count xdc_runtime_Registry_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Object__heap__C, ".const:xdc_runtime_Registry_Object__heap__C");
__FAR__ const CT__xdc_runtime_Registry_Object__heap xdc_runtime_Registry_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Object__sizeof__C, ".const:xdc_runtime_Registry_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Registry_Object__sizeof xdc_runtime_Registry_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Registry_Object__table__C, ".const:xdc_runtime_Registry_Object__table__C");
__FAR__ const CT__xdc_runtime_Registry_Object__table xdc_runtime_Registry_Object__table__C = 0;


/*
 * ======== xdc.runtime.Startup INITIALIZERS ========
 */

/* Module__state__V */
#if defined (__ICCARM__)
#pragma location = ".data_xdc_runtime_Startup_Module__state__V"
#endif
#if defined(__GNUC__) && !(defined(__MACH__) && defined(__APPLE__))
#ifndef __TI_COMPILER_VERSION__
xdc_runtime_Startup_Module_State__ xdc_runtime_Startup_Module__state__V __attribute__ ((section(".data_xdc_runtime_Startup_Module__state__V")));
#endif
#endif
xdc_runtime_Startup_Module_State__ xdc_runtime_Startup_Module__state__V = {
    ((xdc_Int*)0),  /* stateTab */
    0,  /* execFlag */
    0,  /* rtsDoneFlag */
};

/* --> xdc_runtime_Startup_firstFxns__A */
#pragma DATA_SECTION(xdc_runtime_Startup_firstFxns__A, ".const:xdc_runtime_Startup_firstFxns__A");
const __T1_xdc_runtime_Startup_firstFxns xdc_runtime_Startup_firstFxns__A[1] = {
    ((xdc_Void(*)(xdc_Void))((xdc_Fxn)ti_catalog_arm_cortexm4_tiva_ce_Boot_init__I)),  /* [0] */
};

/* --> xdc_runtime_Startup_sfxnTab__A */
#pragma DATA_SECTION(xdc_runtime_Startup_sfxnTab__A, ".const:xdc_runtime_Startup_sfxnTab__A");
const __T1_xdc_runtime_Startup_sfxnTab xdc_runtime_Startup_sfxnTab__A[2] = {
    ((xdc_Int(*)(xdc_Int))((xdc_Fxn)xdc_runtime_System_Module_startup__E)),  /* [0] */
    ((xdc_Int(*)(xdc_Int))((xdc_Fxn)xdc_runtime_SysMin_Module_startup__E)),  /* [1] */
};

/* --> xdc_runtime_Startup_sfxnRts__A */
#pragma DATA_SECTION(xdc_runtime_Startup_sfxnRts__A, ".const:xdc_runtime_Startup_sfxnRts__A");
const __T1_xdc_runtime_Startup_sfxnRts xdc_runtime_Startup_sfxnRts__A[2] = {
    1,  /* [0] */
    1,  /* [1] */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__diagsEnabled__C, ".const:xdc_runtime_Startup_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Startup_Module__diagsEnabled xdc_runtime_Startup_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__diagsIncluded__C, ".const:xdc_runtime_Startup_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Startup_Module__diagsIncluded xdc_runtime_Startup_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__diagsMask__C, ".const:xdc_runtime_Startup_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Startup_Module__diagsMask xdc_runtime_Startup_Module__diagsMask__C = ((CT__xdc_runtime_Startup_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__gateObj__C, ".const:xdc_runtime_Startup_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Startup_Module__gateObj xdc_runtime_Startup_Module__gateObj__C = ((CT__xdc_runtime_Startup_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__gatePrms__C, ".const:xdc_runtime_Startup_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Startup_Module__gatePrms xdc_runtime_Startup_Module__gatePrms__C = ((CT__xdc_runtime_Startup_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__id__C, ".const:xdc_runtime_Startup_Module__id__C");
__FAR__ const CT__xdc_runtime_Startup_Module__id xdc_runtime_Startup_Module__id__C = (xdc_Bits16)0x800e;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerDefined__C, ".const:xdc_runtime_Startup_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Startup_Module__loggerDefined xdc_runtime_Startup_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerObj__C, ".const:xdc_runtime_Startup_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Startup_Module__loggerObj xdc_runtime_Startup_Module__loggerObj__C = ((CT__xdc_runtime_Startup_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn0__C, ".const:xdc_runtime_Startup_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn0 xdc_runtime_Startup_Module__loggerFxn0__C = ((CT__xdc_runtime_Startup_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn1__C, ".const:xdc_runtime_Startup_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn1 xdc_runtime_Startup_Module__loggerFxn1__C = ((CT__xdc_runtime_Startup_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn2__C, ".const:xdc_runtime_Startup_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn2 xdc_runtime_Startup_Module__loggerFxn2__C = ((CT__xdc_runtime_Startup_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn4__C, ".const:xdc_runtime_Startup_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn4 xdc_runtime_Startup_Module__loggerFxn4__C = ((CT__xdc_runtime_Startup_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn8__C, ".const:xdc_runtime_Startup_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn8 xdc_runtime_Startup_Module__loggerFxn8__C = ((CT__xdc_runtime_Startup_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Module__startupDoneFxn__C, ".const:xdc_runtime_Startup_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Startup_Module__startupDoneFxn xdc_runtime_Startup_Module__startupDoneFxn__C = ((CT__xdc_runtime_Startup_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Object__count__C, ".const:xdc_runtime_Startup_Object__count__C");
__FAR__ const CT__xdc_runtime_Startup_Object__count xdc_runtime_Startup_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Object__heap__C, ".const:xdc_runtime_Startup_Object__heap__C");
__FAR__ const CT__xdc_runtime_Startup_Object__heap xdc_runtime_Startup_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Object__sizeof__C, ".const:xdc_runtime_Startup_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Startup_Object__sizeof xdc_runtime_Startup_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Startup_Object__table__C, ".const:xdc_runtime_Startup_Object__table__C");
__FAR__ const CT__xdc_runtime_Startup_Object__table xdc_runtime_Startup_Object__table__C = 0;

/* maxPasses__C */
#pragma DATA_SECTION(xdc_runtime_Startup_maxPasses__C, ".const:xdc_runtime_Startup_maxPasses__C");
__FAR__ const CT__xdc_runtime_Startup_maxPasses xdc_runtime_Startup_maxPasses__C = (xdc_Int)0x20;

/* firstFxns__C */
#pragma DATA_SECTION(xdc_runtime_Startup_firstFxns__C, ".const:xdc_runtime_Startup_firstFxns__C");
__FAR__ const CT__xdc_runtime_Startup_firstFxns xdc_runtime_Startup_firstFxns__C = {1, ((__T1_xdc_runtime_Startup_firstFxns*)xdc_runtime_Startup_firstFxns__A)};

/* lastFxns__C */
#pragma DATA_SECTION(xdc_runtime_Startup_lastFxns__C, ".const:xdc_runtime_Startup_lastFxns__C");
__FAR__ const CT__xdc_runtime_Startup_lastFxns xdc_runtime_Startup_lastFxns__C = {0, 0};

/* startModsFxn__C */
#pragma DATA_SECTION(xdc_runtime_Startup_startModsFxn__C, ".const:xdc_runtime_Startup_startModsFxn__C");
__FAR__ const CT__xdc_runtime_Startup_startModsFxn xdc_runtime_Startup_startModsFxn__C = ((CT__xdc_runtime_Startup_startModsFxn)((xdc_Fxn)xdc_runtime_Startup_startMods__I));

/* execImpl__C */
#pragma DATA_SECTION(xdc_runtime_Startup_execImpl__C, ".const:xdc_runtime_Startup_execImpl__C");
__FAR__ const CT__xdc_runtime_Startup_execImpl xdc_runtime_Startup_execImpl__C = ((CT__xdc_runtime_Startup_execImpl)((xdc_Fxn)xdc_runtime_Startup_exec__I));

/* sfxnTab__C */
#pragma DATA_SECTION(xdc_runtime_Startup_sfxnTab__C, ".const:xdc_runtime_Startup_sfxnTab__C");
__FAR__ const CT__xdc_runtime_Startup_sfxnTab xdc_runtime_Startup_sfxnTab__C = ((CT__xdc_runtime_Startup_sfxnTab)xdc_runtime_Startup_sfxnTab__A);

/* sfxnRts__C */
#pragma DATA_SECTION(xdc_runtime_Startup_sfxnRts__C, ".const:xdc_runtime_Startup_sfxnRts__C");
__FAR__ const CT__xdc_runtime_Startup_sfxnRts xdc_runtime_Startup_sfxnRts__C = ((CT__xdc_runtime_Startup_sfxnRts)xdc_runtime_Startup_sfxnRts__A);


/*
 * ======== xdc.runtime.SysMin INITIALIZERS ========
 */

/* --> xdc_runtime_SysMin_Module_State_0_outbuf__A */
__T1_xdc_runtime_SysMin_Module_State__outbuf xdc_runtime_SysMin_Module_State_0_outbuf__A[1024];

/* Module__state__V */
#if defined (__ICCARM__)
#pragma location = ".data_xdc_runtime_SysMin_Module__state__V"
#endif
#if defined(__GNUC__) && !(defined(__MACH__) && defined(__APPLE__))
#ifndef __TI_COMPILER_VERSION__
xdc_runtime_SysMin_Module_State__ xdc_runtime_SysMin_Module__state__V __attribute__ ((section(".data_xdc_runtime_SysMin_Module__state__V")));
#endif
#endif
xdc_runtime_SysMin_Module_State__ xdc_runtime_SysMin_Module__state__V = {
    ((void*)xdc_runtime_SysMin_Module_State_0_outbuf__A),  /* outbuf */
    (xdc_UInt)0x0,  /* outidx */
    0,  /* wrapped */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__diagsEnabled__C, ".const:xdc_runtime_SysMin_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__diagsEnabled xdc_runtime_SysMin_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__diagsIncluded__C, ".const:xdc_runtime_SysMin_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__diagsIncluded xdc_runtime_SysMin_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__diagsMask__C, ".const:xdc_runtime_SysMin_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__diagsMask xdc_runtime_SysMin_Module__diagsMask__C = ((CT__xdc_runtime_SysMin_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__gateObj__C, ".const:xdc_runtime_SysMin_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__gateObj xdc_runtime_SysMin_Module__gateObj__C = ((CT__xdc_runtime_SysMin_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__gatePrms__C, ".const:xdc_runtime_SysMin_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__gatePrms xdc_runtime_SysMin_Module__gatePrms__C = ((CT__xdc_runtime_SysMin_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__id__C, ".const:xdc_runtime_SysMin_Module__id__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__id xdc_runtime_SysMin_Module__id__C = (xdc_Bits16)0x8010;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__loggerDefined__C, ".const:xdc_runtime_SysMin_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__loggerDefined xdc_runtime_SysMin_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__loggerObj__C, ".const:xdc_runtime_SysMin_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__loggerObj xdc_runtime_SysMin_Module__loggerObj__C = ((CT__xdc_runtime_SysMin_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__loggerFxn0__C, ".const:xdc_runtime_SysMin_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__loggerFxn0 xdc_runtime_SysMin_Module__loggerFxn0__C = ((CT__xdc_runtime_SysMin_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__loggerFxn1__C, ".const:xdc_runtime_SysMin_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__loggerFxn1 xdc_runtime_SysMin_Module__loggerFxn1__C = ((CT__xdc_runtime_SysMin_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__loggerFxn2__C, ".const:xdc_runtime_SysMin_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__loggerFxn2 xdc_runtime_SysMin_Module__loggerFxn2__C = ((CT__xdc_runtime_SysMin_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__loggerFxn4__C, ".const:xdc_runtime_SysMin_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__loggerFxn4 xdc_runtime_SysMin_Module__loggerFxn4__C = ((CT__xdc_runtime_SysMin_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__loggerFxn8__C, ".const:xdc_runtime_SysMin_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__loggerFxn8 xdc_runtime_SysMin_Module__loggerFxn8__C = ((CT__xdc_runtime_SysMin_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Module__startupDoneFxn__C, ".const:xdc_runtime_SysMin_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_SysMin_Module__startupDoneFxn xdc_runtime_SysMin_Module__startupDoneFxn__C = ((CT__xdc_runtime_SysMin_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Object__count__C, ".const:xdc_runtime_SysMin_Object__count__C");
__FAR__ const CT__xdc_runtime_SysMin_Object__count xdc_runtime_SysMin_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Object__heap__C, ".const:xdc_runtime_SysMin_Object__heap__C");
__FAR__ const CT__xdc_runtime_SysMin_Object__heap xdc_runtime_SysMin_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Object__sizeof__C, ".const:xdc_runtime_SysMin_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_SysMin_Object__sizeof xdc_runtime_SysMin_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_Object__table__C, ".const:xdc_runtime_SysMin_Object__table__C");
__FAR__ const CT__xdc_runtime_SysMin_Object__table xdc_runtime_SysMin_Object__table__C = 0;

/* bufSize__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_bufSize__C, ".const:xdc_runtime_SysMin_bufSize__C");
__FAR__ const CT__xdc_runtime_SysMin_bufSize xdc_runtime_SysMin_bufSize__C = (xdc_SizeT)0x400;

/* flushAtExit__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_flushAtExit__C, ".const:xdc_runtime_SysMin_flushAtExit__C");
__FAR__ const CT__xdc_runtime_SysMin_flushAtExit xdc_runtime_SysMin_flushAtExit__C = 1;

/* outputFxn__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_outputFxn__C, ".const:xdc_runtime_SysMin_outputFxn__C");
__FAR__ const CT__xdc_runtime_SysMin_outputFxn xdc_runtime_SysMin_outputFxn__C = ((CT__xdc_runtime_SysMin_outputFxn)0);

/* outputFunc__C */
#pragma DATA_SECTION(xdc_runtime_SysMin_outputFunc__C, ".const:xdc_runtime_SysMin_outputFunc__C");
__FAR__ const CT__xdc_runtime_SysMin_outputFunc xdc_runtime_SysMin_outputFunc__C = ((CT__xdc_runtime_SysMin_outputFunc)((xdc_Fxn)xdc_runtime_SysMin_output__I));


/*
 * ======== xdc.runtime.System INITIALIZERS ========
 */

/* --> xdc_runtime_System_Module_State_0_atexitHandlers__A */
__T1_xdc_runtime_System_Module_State__atexitHandlers xdc_runtime_System_Module_State_0_atexitHandlers__A[8] = {
    ((xdc_Void(*)(xdc_Int))0),  /* [0] */
    ((xdc_Void(*)(xdc_Int))0),  /* [1] */
    ((xdc_Void(*)(xdc_Int))0),  /* [2] */
    ((xdc_Void(*)(xdc_Int))0),  /* [3] */
    ((xdc_Void(*)(xdc_Int))0),  /* [4] */
    ((xdc_Void(*)(xdc_Int))0),  /* [5] */
    ((xdc_Void(*)(xdc_Int))0),  /* [6] */
    ((xdc_Void(*)(xdc_Int))0),  /* [7] */
};

/* Module__state__V */
#if defined (__ICCARM__)
#pragma location = ".data_xdc_runtime_System_Module__state__V"
#endif
#if defined(__GNUC__) && !(defined(__MACH__) && defined(__APPLE__))
#ifndef __TI_COMPILER_VERSION__
xdc_runtime_System_Module_State__ xdc_runtime_System_Module__state__V __attribute__ ((section(".data_xdc_runtime_System_Module__state__V")));
#endif
#endif
xdc_runtime_System_Module_State__ xdc_runtime_System_Module__state__V = {
    ((void*)xdc_runtime_System_Module_State_0_atexitHandlers__A),  /* atexitHandlers */
    (xdc_Int)0x0,  /* numAtexitHandlers */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__diagsEnabled__C, ".const:xdc_runtime_System_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_System_Module__diagsEnabled xdc_runtime_System_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__diagsIncluded__C, ".const:xdc_runtime_System_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_System_Module__diagsIncluded xdc_runtime_System_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__diagsMask__C, ".const:xdc_runtime_System_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_System_Module__diagsMask xdc_runtime_System_Module__diagsMask__C = ((CT__xdc_runtime_System_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__gateObj__C, ".const:xdc_runtime_System_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_System_Module__gateObj xdc_runtime_System_Module__gateObj__C = ((CT__xdc_runtime_System_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__gatePrms__C, ".const:xdc_runtime_System_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_System_Module__gatePrms xdc_runtime_System_Module__gatePrms__C = ((CT__xdc_runtime_System_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__id__C, ".const:xdc_runtime_System_Module__id__C");
__FAR__ const CT__xdc_runtime_System_Module__id xdc_runtime_System_Module__id__C = (xdc_Bits16)0x800f;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__loggerDefined__C, ".const:xdc_runtime_System_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_System_Module__loggerDefined xdc_runtime_System_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__loggerObj__C, ".const:xdc_runtime_System_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_System_Module__loggerObj xdc_runtime_System_Module__loggerObj__C = ((CT__xdc_runtime_System_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn0__C, ".const:xdc_runtime_System_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn0 xdc_runtime_System_Module__loggerFxn0__C = ((CT__xdc_runtime_System_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn1__C, ".const:xdc_runtime_System_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn1 xdc_runtime_System_Module__loggerFxn1__C = ((CT__xdc_runtime_System_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn2__C, ".const:xdc_runtime_System_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn2 xdc_runtime_System_Module__loggerFxn2__C = ((CT__xdc_runtime_System_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn4__C, ".const:xdc_runtime_System_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn4 xdc_runtime_System_Module__loggerFxn4__C = ((CT__xdc_runtime_System_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn8__C, ".const:xdc_runtime_System_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn8 xdc_runtime_System_Module__loggerFxn8__C = ((CT__xdc_runtime_System_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_System_Module__startupDoneFxn__C, ".const:xdc_runtime_System_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_System_Module__startupDoneFxn xdc_runtime_System_Module__startupDoneFxn__C = ((CT__xdc_runtime_System_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_System_Object__count__C, ".const:xdc_runtime_System_Object__count__C");
__FAR__ const CT__xdc_runtime_System_Object__count xdc_runtime_System_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_System_Object__heap__C, ".const:xdc_runtime_System_Object__heap__C");
__FAR__ const CT__xdc_runtime_System_Object__heap xdc_runtime_System_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_System_Object__sizeof__C, ".const:xdc_runtime_System_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_System_Object__sizeof xdc_runtime_System_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_System_Object__table__C, ".const:xdc_runtime_System_Object__table__C");
__FAR__ const CT__xdc_runtime_System_Object__table xdc_runtime_System_Object__table__C = 0;

/* A_cannotFitIntoArg__C */
#pragma DATA_SECTION(xdc_runtime_System_A_cannotFitIntoArg__C, ".const:xdc_runtime_System_A_cannotFitIntoArg__C");
__FAR__ const CT__xdc_runtime_System_A_cannotFitIntoArg xdc_runtime_System_A_cannotFitIntoArg__C = (((xdc_runtime_Assert_Id)352) << 16 | 16);

/* maxAtexitHandlers__C */
#pragma DATA_SECTION(xdc_runtime_System_maxAtexitHandlers__C, ".const:xdc_runtime_System_maxAtexitHandlers__C");
__FAR__ const CT__xdc_runtime_System_maxAtexitHandlers xdc_runtime_System_maxAtexitHandlers__C = (xdc_Int)0x8;

/* abortFxn__C */
#pragma DATA_SECTION(xdc_runtime_System_abortFxn__C, ".const:xdc_runtime_System_abortFxn__C");
__FAR__ const CT__xdc_runtime_System_abortFxn xdc_runtime_System_abortFxn__C = ((CT__xdc_runtime_System_abortFxn)((xdc_Fxn)xdc_runtime_System_abortStd__E));

/* exitFxn__C */
#pragma DATA_SECTION(xdc_runtime_System_exitFxn__C, ".const:xdc_runtime_System_exitFxn__C");
__FAR__ const CT__xdc_runtime_System_exitFxn xdc_runtime_System_exitFxn__C = ((CT__xdc_runtime_System_exitFxn)((xdc_Fxn)xdc_runtime_System_exitStd__E));

/* extendFxn__C */
#pragma DATA_SECTION(xdc_runtime_System_extendFxn__C, ".const:xdc_runtime_System_extendFxn__C");
__FAR__ const CT__xdc_runtime_System_extendFxn xdc_runtime_System_extendFxn__C = ((CT__xdc_runtime_System_extendFxn)((xdc_Fxn)xdc_runtime_System_printfExtend__I));


/*
 * ======== xdc.runtime.System_Module_GateProxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.System_SupportProxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.Text INITIALIZERS ========
 */

/* Module__state__V */
#if defined (__ICCARM__)
#pragma location = ".data_xdc_runtime_Text_Module__state__V"
#endif
#if defined(__GNUC__) && !(defined(__MACH__) && defined(__APPLE__))
#ifndef __TI_COMPILER_VERSION__
xdc_runtime_Text_Module_State__ xdc_runtime_Text_Module__state__V __attribute__ ((section(".data_xdc_runtime_Text_Module__state__V")));
#endif
#endif
xdc_runtime_Text_Module_State__ xdc_runtime_Text_Module__state__V = {
    ((xdc_Ptr)((void*)&xdc_runtime_Text_charTab__A[0])),  /* charBase */
    ((xdc_Ptr)((void*)&xdc_runtime_Text_nodeTab__A[0])),  /* nodeBase */
};

/* --> xdc_runtime_Text_charTab__A */
#pragma DATA_SECTION(xdc_runtime_Text_charTab__A, ".const:xdc_runtime_Text_charTab__A");
const __T1_xdc_runtime_Text_charTab xdc_runtime_Text_charTab__A[3762] = {
    (xdc_Char)0x0,  /* [0] */
    (xdc_Char)0x41,  /* [1] */
    (xdc_Char)0x5f,  /* [2] */
    (xdc_Char)0x69,  /* [3] */
    (xdc_Char)0x6e,  /* [4] */
    (xdc_Char)0x69,  /* [5] */
    (xdc_Char)0x74,  /* [6] */
    (xdc_Char)0x69,  /* [7] */
    (xdc_Char)0x61,  /* [8] */
    (xdc_Char)0x6c,  /* [9] */
    (xdc_Char)0x69,  /* [10] */
    (xdc_Char)0x7a,  /* [11] */
    (xdc_Char)0x65,  /* [12] */
    (xdc_Char)0x64,  /* [13] */
    (xdc_Char)0x50,  /* [14] */
    (xdc_Char)0x61,  /* [15] */
    (xdc_Char)0x72,  /* [16] */
    (xdc_Char)0x61,  /* [17] */
    (xdc_Char)0x6d,  /* [18] */
    (xdc_Char)0x73,  /* [19] */
    (xdc_Char)0x3a,  /* [20] */
    (xdc_Char)0x20,  /* [21] */
    (xdc_Char)0x75,  /* [22] */
    (xdc_Char)0x6e,  /* [23] */
    (xdc_Char)0x69,  /* [24] */
    (xdc_Char)0x6e,  /* [25] */
    (xdc_Char)0x69,  /* [26] */
    (xdc_Char)0x74,  /* [27] */
    (xdc_Char)0x69,  /* [28] */
    (xdc_Char)0x61,  /* [29] */
    (xdc_Char)0x6c,  /* [30] */
    (xdc_Char)0x69,  /* [31] */
    (xdc_Char)0x7a,  /* [32] */
    (xdc_Char)0x65,  /* [33] */
    (xdc_Char)0x64,  /* [34] */
    (xdc_Char)0x20,  /* [35] */
    (xdc_Char)0x50,  /* [36] */
    (xdc_Char)0x61,  /* [37] */
    (xdc_Char)0x72,  /* [38] */
    (xdc_Char)0x61,  /* [39] */
    (xdc_Char)0x6d,  /* [40] */
    (xdc_Char)0x73,  /* [41] */
    (xdc_Char)0x20,  /* [42] */
    (xdc_Char)0x73,  /* [43] */
    (xdc_Char)0x74,  /* [44] */
    (xdc_Char)0x72,  /* [45] */
    (xdc_Char)0x75,  /* [46] */
    (xdc_Char)0x63,  /* [47] */
    (xdc_Char)0x74,  /* [48] */
    (xdc_Char)0x0,  /* [49] */
    (xdc_Char)0x48,  /* [50] */
    (xdc_Char)0x65,  /* [51] */
    (xdc_Char)0x61,  /* [52] */
    (xdc_Char)0x70,  /* [53] */
    (xdc_Char)0x4d,  /* [54] */
    (xdc_Char)0x69,  /* [55] */
    (xdc_Char)0x6e,  /* [56] */
    (xdc_Char)0x5f,  /* [57] */
    (xdc_Char)0x63,  /* [58] */
    (xdc_Char)0x72,  /* [59] */
    (xdc_Char)0x65,  /* [60] */
    (xdc_Char)0x61,  /* [61] */
    (xdc_Char)0x74,  /* [62] */
    (xdc_Char)0x65,  /* [63] */
    (xdc_Char)0x20,  /* [64] */
    (xdc_Char)0x63,  /* [65] */
    (xdc_Char)0x61,  /* [66] */
    (xdc_Char)0x6e,  /* [67] */
    (xdc_Char)0x6e,  /* [68] */
    (xdc_Char)0x6f,  /* [69] */
    (xdc_Char)0x74,  /* [70] */
    (xdc_Char)0x20,  /* [71] */
    (xdc_Char)0x68,  /* [72] */
    (xdc_Char)0x61,  /* [73] */
    (xdc_Char)0x76,  /* [74] */
    (xdc_Char)0x65,  /* [75] */
    (xdc_Char)0x20,  /* [76] */
    (xdc_Char)0x61,  /* [77] */
    (xdc_Char)0x20,  /* [78] */
    (xdc_Char)0x7a,  /* [79] */
    (xdc_Char)0x65,  /* [80] */
    (xdc_Char)0x72,  /* [81] */
    (xdc_Char)0x6f,  /* [82] */
    (xdc_Char)0x20,  /* [83] */
    (xdc_Char)0x73,  /* [84] */
    (xdc_Char)0x69,  /* [85] */
    (xdc_Char)0x7a,  /* [86] */
    (xdc_Char)0x65,  /* [87] */
    (xdc_Char)0x20,  /* [88] */
    (xdc_Char)0x76,  /* [89] */
    (xdc_Char)0x61,  /* [90] */
    (xdc_Char)0x6c,  /* [91] */
    (xdc_Char)0x75,  /* [92] */
    (xdc_Char)0x65,  /* [93] */
    (xdc_Char)0x0,  /* [94] */
    (xdc_Char)0x48,  /* [95] */
    (xdc_Char)0x65,  /* [96] */
    (xdc_Char)0x61,  /* [97] */
    (xdc_Char)0x70,  /* [98] */
    (xdc_Char)0x53,  /* [99] */
    (xdc_Char)0x74,  /* [100] */
    (xdc_Char)0x64,  /* [101] */
    (xdc_Char)0x5f,  /* [102] */
    (xdc_Char)0x63,  /* [103] */
    (xdc_Char)0x72,  /* [104] */
    (xdc_Char)0x65,  /* [105] */
    (xdc_Char)0x61,  /* [106] */
    (xdc_Char)0x74,  /* [107] */
    (xdc_Char)0x65,  /* [108] */
    (xdc_Char)0x20,  /* [109] */
    (xdc_Char)0x63,  /* [110] */
    (xdc_Char)0x61,  /* [111] */
    (xdc_Char)0x6e,  /* [112] */
    (xdc_Char)0x6e,  /* [113] */
    (xdc_Char)0x6f,  /* [114] */
    (xdc_Char)0x74,  /* [115] */
    (xdc_Char)0x20,  /* [116] */
    (xdc_Char)0x68,  /* [117] */
    (xdc_Char)0x61,  /* [118] */
    (xdc_Char)0x76,  /* [119] */
    (xdc_Char)0x65,  /* [120] */
    (xdc_Char)0x20,  /* [121] */
    (xdc_Char)0x61,  /* [122] */
    (xdc_Char)0x20,  /* [123] */
    (xdc_Char)0x7a,  /* [124] */
    (xdc_Char)0x65,  /* [125] */
    (xdc_Char)0x72,  /* [126] */
    (xdc_Char)0x6f,  /* [127] */
    (xdc_Char)0x20,  /* [128] */
    (xdc_Char)0x73,  /* [129] */
    (xdc_Char)0x69,  /* [130] */
    (xdc_Char)0x7a,  /* [131] */
    (xdc_Char)0x65,  /* [132] */
    (xdc_Char)0x20,  /* [133] */
    (xdc_Char)0x76,  /* [134] */
    (xdc_Char)0x61,  /* [135] */
    (xdc_Char)0x6c,  /* [136] */
    (xdc_Char)0x75,  /* [137] */
    (xdc_Char)0x65,  /* [138] */
    (xdc_Char)0x0,  /* [139] */
    (xdc_Char)0x48,  /* [140] */
    (xdc_Char)0x65,  /* [141] */
    (xdc_Char)0x61,  /* [142] */
    (xdc_Char)0x70,  /* [143] */
    (xdc_Char)0x53,  /* [144] */
    (xdc_Char)0x74,  /* [145] */
    (xdc_Char)0x64,  /* [146] */
    (xdc_Char)0x5f,  /* [147] */
    (xdc_Char)0x61,  /* [148] */
    (xdc_Char)0x6c,  /* [149] */
    (xdc_Char)0x6c,  /* [150] */
    (xdc_Char)0x6f,  /* [151] */
    (xdc_Char)0x63,  /* [152] */
    (xdc_Char)0x20,  /* [153] */
    (xdc_Char)0x61,  /* [154] */
    (xdc_Char)0x6c,  /* [155] */
    (xdc_Char)0x69,  /* [156] */
    (xdc_Char)0x67,  /* [157] */
    (xdc_Char)0x6e,  /* [158] */
    (xdc_Char)0x6d,  /* [159] */
    (xdc_Char)0x65,  /* [160] */
    (xdc_Char)0x6e,  /* [161] */
    (xdc_Char)0x74,  /* [162] */
    (xdc_Char)0x20,  /* [163] */
    (xdc_Char)0x6d,  /* [164] */
    (xdc_Char)0x75,  /* [165] */
    (xdc_Char)0x73,  /* [166] */
    (xdc_Char)0x74,  /* [167] */
    (xdc_Char)0x20,  /* [168] */
    (xdc_Char)0x62,  /* [169] */
    (xdc_Char)0x65,  /* [170] */
    (xdc_Char)0x20,  /* [171] */
    (xdc_Char)0x61,  /* [172] */
    (xdc_Char)0x20,  /* [173] */
    (xdc_Char)0x70,  /* [174] */
    (xdc_Char)0x6f,  /* [175] */
    (xdc_Char)0x77,  /* [176] */
    (xdc_Char)0x65,  /* [177] */
    (xdc_Char)0x72,  /* [178] */
    (xdc_Char)0x20,  /* [179] */
    (xdc_Char)0x6f,  /* [180] */
    (xdc_Char)0x66,  /* [181] */
    (xdc_Char)0x20,  /* [182] */
    (xdc_Char)0x32,  /* [183] */
    (xdc_Char)0x0,  /* [184] */
    (xdc_Char)0x48,  /* [185] */
    (xdc_Char)0x65,  /* [186] */
    (xdc_Char)0x61,  /* [187] */
    (xdc_Char)0x70,  /* [188] */
    (xdc_Char)0x53,  /* [189] */
    (xdc_Char)0x74,  /* [190] */
    (xdc_Char)0x64,  /* [191] */
    (xdc_Char)0x20,  /* [192] */
    (xdc_Char)0x69,  /* [193] */
    (xdc_Char)0x6e,  /* [194] */
    (xdc_Char)0x73,  /* [195] */
    (xdc_Char)0x74,  /* [196] */
    (xdc_Char)0x61,  /* [197] */
    (xdc_Char)0x6e,  /* [198] */
    (xdc_Char)0x63,  /* [199] */
    (xdc_Char)0x65,  /* [200] */
    (xdc_Char)0x20,  /* [201] */
    (xdc_Char)0x74,  /* [202] */
    (xdc_Char)0x6f,  /* [203] */
    (xdc_Char)0x74,  /* [204] */
    (xdc_Char)0x61,  /* [205] */
    (xdc_Char)0x6c,  /* [206] */
    (xdc_Char)0x46,  /* [207] */
    (xdc_Char)0x72,  /* [208] */
    (xdc_Char)0x65,  /* [209] */
    (xdc_Char)0x65,  /* [210] */
    (xdc_Char)0x53,  /* [211] */
    (xdc_Char)0x69,  /* [212] */
    (xdc_Char)0x7a,  /* [213] */
    (xdc_Char)0x65,  /* [214] */
    (xdc_Char)0x20,  /* [215] */
    (xdc_Char)0x69,  /* [216] */
    (xdc_Char)0x73,  /* [217] */
    (xdc_Char)0x20,  /* [218] */
    (xdc_Char)0x67,  /* [219] */
    (xdc_Char)0x72,  /* [220] */
    (xdc_Char)0x65,  /* [221] */
    (xdc_Char)0x61,  /* [222] */
    (xdc_Char)0x74,  /* [223] */
    (xdc_Char)0x65,  /* [224] */
    (xdc_Char)0x72,  /* [225] */
    (xdc_Char)0x20,  /* [226] */
    (xdc_Char)0x74,  /* [227] */
    (xdc_Char)0x68,  /* [228] */
    (xdc_Char)0x61,  /* [229] */
    (xdc_Char)0x6e,  /* [230] */
    (xdc_Char)0x20,  /* [231] */
    (xdc_Char)0x73,  /* [232] */
    (xdc_Char)0x74,  /* [233] */
    (xdc_Char)0x61,  /* [234] */
    (xdc_Char)0x72,  /* [235] */
    (xdc_Char)0x74,  /* [236] */
    (xdc_Char)0x69,  /* [237] */
    (xdc_Char)0x6e,  /* [238] */
    (xdc_Char)0x67,  /* [239] */
    (xdc_Char)0x20,  /* [240] */
    (xdc_Char)0x73,  /* [241] */
    (xdc_Char)0x69,  /* [242] */
    (xdc_Char)0x7a,  /* [243] */
    (xdc_Char)0x65,  /* [244] */
    (xdc_Char)0x0,  /* [245] */
    (xdc_Char)0x48,  /* [246] */
    (xdc_Char)0x65,  /* [247] */
    (xdc_Char)0x61,  /* [248] */
    (xdc_Char)0x70,  /* [249] */
    (xdc_Char)0x53,  /* [250] */
    (xdc_Char)0x74,  /* [251] */
    (xdc_Char)0x64,  /* [252] */
    (xdc_Char)0x5f,  /* [253] */
    (xdc_Char)0x61,  /* [254] */
    (xdc_Char)0x6c,  /* [255] */
    (xdc_Char)0x6c,  /* [256] */
    (xdc_Char)0x6f,  /* [257] */
    (xdc_Char)0x63,  /* [258] */
    (xdc_Char)0x20,  /* [259] */
    (xdc_Char)0x2d,  /* [260] */
    (xdc_Char)0x20,  /* [261] */
    (xdc_Char)0x72,  /* [262] */
    (xdc_Char)0x65,  /* [263] */
    (xdc_Char)0x71,  /* [264] */
    (xdc_Char)0x75,  /* [265] */
    (xdc_Char)0x65,  /* [266] */
    (xdc_Char)0x73,  /* [267] */
    (xdc_Char)0x74,  /* [268] */
    (xdc_Char)0x65,  /* [269] */
    (xdc_Char)0x64,  /* [270] */
    (xdc_Char)0x20,  /* [271] */
    (xdc_Char)0x61,  /* [272] */
    (xdc_Char)0x6c,  /* [273] */
    (xdc_Char)0x69,  /* [274] */
    (xdc_Char)0x67,  /* [275] */
    (xdc_Char)0x6e,  /* [276] */
    (xdc_Char)0x6d,  /* [277] */
    (xdc_Char)0x65,  /* [278] */
    (xdc_Char)0x6e,  /* [279] */
    (xdc_Char)0x74,  /* [280] */
    (xdc_Char)0x20,  /* [281] */
    (xdc_Char)0x69,  /* [282] */
    (xdc_Char)0x73,  /* [283] */
    (xdc_Char)0x20,  /* [284] */
    (xdc_Char)0x67,  /* [285] */
    (xdc_Char)0x72,  /* [286] */
    (xdc_Char)0x65,  /* [287] */
    (xdc_Char)0x61,  /* [288] */
    (xdc_Char)0x74,  /* [289] */
    (xdc_Char)0x65,  /* [290] */
    (xdc_Char)0x72,  /* [291] */
    (xdc_Char)0x20,  /* [292] */
    (xdc_Char)0x74,  /* [293] */
    (xdc_Char)0x68,  /* [294] */
    (xdc_Char)0x61,  /* [295] */
    (xdc_Char)0x6e,  /* [296] */
    (xdc_Char)0x20,  /* [297] */
    (xdc_Char)0x61,  /* [298] */
    (xdc_Char)0x6c,  /* [299] */
    (xdc_Char)0x6c,  /* [300] */
    (xdc_Char)0x6f,  /* [301] */
    (xdc_Char)0x77,  /* [302] */
    (xdc_Char)0x65,  /* [303] */
    (xdc_Char)0x64,  /* [304] */
    (xdc_Char)0x0,  /* [305] */
    (xdc_Char)0x41,  /* [306] */
    (xdc_Char)0x5f,  /* [307] */
    (xdc_Char)0x69,  /* [308] */
    (xdc_Char)0x6e,  /* [309] */
    (xdc_Char)0x76,  /* [310] */
    (xdc_Char)0x61,  /* [311] */
    (xdc_Char)0x6c,  /* [312] */
    (xdc_Char)0x69,  /* [313] */
    (xdc_Char)0x64,  /* [314] */
    (xdc_Char)0x4c,  /* [315] */
    (xdc_Char)0x6f,  /* [316] */
    (xdc_Char)0x67,  /* [317] */
    (xdc_Char)0x67,  /* [318] */
    (xdc_Char)0x65,  /* [319] */
    (xdc_Char)0x72,  /* [320] */
    (xdc_Char)0x3a,  /* [321] */
    (xdc_Char)0x20,  /* [322] */
    (xdc_Char)0x54,  /* [323] */
    (xdc_Char)0x68,  /* [324] */
    (xdc_Char)0x65,  /* [325] */
    (xdc_Char)0x20,  /* [326] */
    (xdc_Char)0x6c,  /* [327] */
    (xdc_Char)0x6f,  /* [328] */
    (xdc_Char)0x67,  /* [329] */
    (xdc_Char)0x67,  /* [330] */
    (xdc_Char)0x65,  /* [331] */
    (xdc_Char)0x72,  /* [332] */
    (xdc_Char)0x20,  /* [333] */
    (xdc_Char)0x69,  /* [334] */
    (xdc_Char)0x64,  /* [335] */
    (xdc_Char)0x20,  /* [336] */
    (xdc_Char)0x25,  /* [337] */
    (xdc_Char)0x64,  /* [338] */
    (xdc_Char)0x20,  /* [339] */
    (xdc_Char)0x69,  /* [340] */
    (xdc_Char)0x73,  /* [341] */
    (xdc_Char)0x20,  /* [342] */
    (xdc_Char)0x69,  /* [343] */
    (xdc_Char)0x6e,  /* [344] */
    (xdc_Char)0x76,  /* [345] */
    (xdc_Char)0x61,  /* [346] */
    (xdc_Char)0x6c,  /* [347] */
    (xdc_Char)0x69,  /* [348] */
    (xdc_Char)0x64,  /* [349] */
    (xdc_Char)0x2e,  /* [350] */
    (xdc_Char)0x0,  /* [351] */
    (xdc_Char)0x41,  /* [352] */
    (xdc_Char)0x5f,  /* [353] */
    (xdc_Char)0x63,  /* [354] */
    (xdc_Char)0x61,  /* [355] */
    (xdc_Char)0x6e,  /* [356] */
    (xdc_Char)0x6e,  /* [357] */
    (xdc_Char)0x6f,  /* [358] */
    (xdc_Char)0x74,  /* [359] */
    (xdc_Char)0x46,  /* [360] */
    (xdc_Char)0x69,  /* [361] */
    (xdc_Char)0x74,  /* [362] */
    (xdc_Char)0x49,  /* [363] */
    (xdc_Char)0x6e,  /* [364] */
    (xdc_Char)0x74,  /* [365] */
    (xdc_Char)0x6f,  /* [366] */
    (xdc_Char)0x41,  /* [367] */
    (xdc_Char)0x72,  /* [368] */
    (xdc_Char)0x67,  /* [369] */
    (xdc_Char)0x3a,  /* [370] */
    (xdc_Char)0x20,  /* [371] */
    (xdc_Char)0x73,  /* [372] */
    (xdc_Char)0x69,  /* [373] */
    (xdc_Char)0x7a,  /* [374] */
    (xdc_Char)0x65,  /* [375] */
    (xdc_Char)0x6f,  /* [376] */
    (xdc_Char)0x66,  /* [377] */
    (xdc_Char)0x28,  /* [378] */
    (xdc_Char)0x46,  /* [379] */
    (xdc_Char)0x6c,  /* [380] */
    (xdc_Char)0x6f,  /* [381] */
    (xdc_Char)0x61,  /* [382] */
    (xdc_Char)0x74,  /* [383] */
    (xdc_Char)0x29,  /* [384] */
    (xdc_Char)0x20,  /* [385] */
    (xdc_Char)0x3e,  /* [386] */
    (xdc_Char)0x20,  /* [387] */
    (xdc_Char)0x73,  /* [388] */
    (xdc_Char)0x69,  /* [389] */
    (xdc_Char)0x7a,  /* [390] */
    (xdc_Char)0x65,  /* [391] */
    (xdc_Char)0x6f,  /* [392] */
    (xdc_Char)0x66,  /* [393] */
    (xdc_Char)0x28,  /* [394] */
    (xdc_Char)0x41,  /* [395] */
    (xdc_Char)0x72,  /* [396] */
    (xdc_Char)0x67,  /* [397] */
    (xdc_Char)0x29,  /* [398] */
    (xdc_Char)0x0,  /* [399] */
    (xdc_Char)0x41,  /* [400] */
    (xdc_Char)0x5f,  /* [401] */
    (xdc_Char)0x6d,  /* [402] */
    (xdc_Char)0x75,  /* [403] */
    (xdc_Char)0x73,  /* [404] */
    (xdc_Char)0x74,  /* [405] */
    (xdc_Char)0x55,  /* [406] */
    (xdc_Char)0x73,  /* [407] */
    (xdc_Char)0x65,  /* [408] */
    (xdc_Char)0x45,  /* [409] */
    (xdc_Char)0x6e,  /* [410] */
    (xdc_Char)0x68,  /* [411] */
    (xdc_Char)0x61,  /* [412] */
    (xdc_Char)0x6e,  /* [413] */
    (xdc_Char)0x63,  /* [414] */
    (xdc_Char)0x65,  /* [415] */
    (xdc_Char)0x64,  /* [416] */
    (xdc_Char)0x43,  /* [417] */
    (xdc_Char)0x6c,  /* [418] */
    (xdc_Char)0x6f,  /* [419] */
    (xdc_Char)0x63,  /* [420] */
    (xdc_Char)0x6b,  /* [421] */
    (xdc_Char)0x4d,  /* [422] */
    (xdc_Char)0x6f,  /* [423] */
    (xdc_Char)0x64,  /* [424] */
    (xdc_Char)0x65,  /* [425] */
    (xdc_Char)0x3a,  /* [426] */
    (xdc_Char)0x20,  /* [427] */
    (xdc_Char)0x54,  /* [428] */
    (xdc_Char)0x68,  /* [429] */
    (xdc_Char)0x69,  /* [430] */
    (xdc_Char)0x73,  /* [431] */
    (xdc_Char)0x20,  /* [432] */
    (xdc_Char)0x64,  /* [433] */
    (xdc_Char)0x65,  /* [434] */
    (xdc_Char)0x76,  /* [435] */
    (xdc_Char)0x69,  /* [436] */
    (xdc_Char)0x63,  /* [437] */
    (xdc_Char)0x65,  /* [438] */
    (xdc_Char)0x20,  /* [439] */
    (xdc_Char)0x72,  /* [440] */
    (xdc_Char)0x65,  /* [441] */
    (xdc_Char)0x71,  /* [442] */
    (xdc_Char)0x75,  /* [443] */
    (xdc_Char)0x69,  /* [444] */
    (xdc_Char)0x72,  /* [445] */
    (xdc_Char)0x65,  /* [446] */
    (xdc_Char)0x73,  /* [447] */
    (xdc_Char)0x20,  /* [448] */
    (xdc_Char)0x74,  /* [449] */
    (xdc_Char)0x68,  /* [450] */
    (xdc_Char)0x65,  /* [451] */
    (xdc_Char)0x20,  /* [452] */
    (xdc_Char)0x45,  /* [453] */
    (xdc_Char)0x6e,  /* [454] */
    (xdc_Char)0x68,  /* [455] */
    (xdc_Char)0x61,  /* [456] */
    (xdc_Char)0x6e,  /* [457] */
    (xdc_Char)0x63,  /* [458] */
    (xdc_Char)0x65,  /* [459] */
    (xdc_Char)0x64,  /* [460] */
    (xdc_Char)0x20,  /* [461] */
    (xdc_Char)0x43,  /* [462] */
    (xdc_Char)0x6c,  /* [463] */
    (xdc_Char)0x6f,  /* [464] */
    (xdc_Char)0x63,  /* [465] */
    (xdc_Char)0x6b,  /* [466] */
    (xdc_Char)0x20,  /* [467] */
    (xdc_Char)0x4d,  /* [468] */
    (xdc_Char)0x6f,  /* [469] */
    (xdc_Char)0x64,  /* [470] */
    (xdc_Char)0x65,  /* [471] */
    (xdc_Char)0x2e,  /* [472] */
    (xdc_Char)0x0,  /* [473] */
    (xdc_Char)0x41,  /* [474] */
    (xdc_Char)0x5f,  /* [475] */
    (xdc_Char)0x6d,  /* [476] */
    (xdc_Char)0x75,  /* [477] */
    (xdc_Char)0x73,  /* [478] */
    (xdc_Char)0x74,  /* [479] */
    (xdc_Char)0x4e,  /* [480] */
    (xdc_Char)0x6f,  /* [481] */
    (xdc_Char)0x74,  /* [482] */
    (xdc_Char)0x55,  /* [483] */
    (xdc_Char)0x73,  /* [484] */
    (xdc_Char)0x65,  /* [485] */
    (xdc_Char)0x45,  /* [486] */
    (xdc_Char)0x6e,  /* [487] */
    (xdc_Char)0x68,  /* [488] */
    (xdc_Char)0x61,  /* [489] */
    (xdc_Char)0x6e,  /* [490] */
    (xdc_Char)0x63,  /* [491] */
    (xdc_Char)0x65,  /* [492] */
    (xdc_Char)0x64,  /* [493] */
    (xdc_Char)0x43,  /* [494] */
    (xdc_Char)0x6c,  /* [495] */
    (xdc_Char)0x6f,  /* [496] */
    (xdc_Char)0x63,  /* [497] */
    (xdc_Char)0x6b,  /* [498] */
    (xdc_Char)0x4d,  /* [499] */
    (xdc_Char)0x6f,  /* [500] */
    (xdc_Char)0x64,  /* [501] */
    (xdc_Char)0x65,  /* [502] */
    (xdc_Char)0x3a,  /* [503] */
    (xdc_Char)0x20,  /* [504] */
    (xdc_Char)0x54,  /* [505] */
    (xdc_Char)0x68,  /* [506] */
    (xdc_Char)0x69,  /* [507] */
    (xdc_Char)0x73,  /* [508] */
    (xdc_Char)0x20,  /* [509] */
    (xdc_Char)0x64,  /* [510] */
    (xdc_Char)0x65,  /* [511] */
    (xdc_Char)0x76,  /* [512] */
    (xdc_Char)0x69,  /* [513] */
    (xdc_Char)0x63,  /* [514] */
    (xdc_Char)0x65,  /* [515] */
    (xdc_Char)0x20,  /* [516] */
    (xdc_Char)0x64,  /* [517] */
    (xdc_Char)0x6f,  /* [518] */
    (xdc_Char)0x65,  /* [519] */
    (xdc_Char)0x73,  /* [520] */
    (xdc_Char)0x20,  /* [521] */
    (xdc_Char)0x6e,  /* [522] */
    (xdc_Char)0x6f,  /* [523] */
    (xdc_Char)0x74,  /* [524] */
    (xdc_Char)0x20,  /* [525] */
    (xdc_Char)0x73,  /* [526] */
    (xdc_Char)0x75,  /* [527] */
    (xdc_Char)0x70,  /* [528] */
    (xdc_Char)0x70,  /* [529] */
    (xdc_Char)0x6f,  /* [530] */
    (xdc_Char)0x72,  /* [531] */
    (xdc_Char)0x74,  /* [532] */
    (xdc_Char)0x20,  /* [533] */
    (xdc_Char)0x74,  /* [534] */
    (xdc_Char)0x68,  /* [535] */
    (xdc_Char)0x65,  /* [536] */
    (xdc_Char)0x20,  /* [537] */
    (xdc_Char)0x45,  /* [538] */
    (xdc_Char)0x6e,  /* [539] */
    (xdc_Char)0x68,  /* [540] */
    (xdc_Char)0x61,  /* [541] */
    (xdc_Char)0x6e,  /* [542] */
    (xdc_Char)0x63,  /* [543] */
    (xdc_Char)0x65,  /* [544] */
    (xdc_Char)0x64,  /* [545] */
    (xdc_Char)0x20,  /* [546] */
    (xdc_Char)0x43,  /* [547] */
    (xdc_Char)0x6c,  /* [548] */
    (xdc_Char)0x6f,  /* [549] */
    (xdc_Char)0x63,  /* [550] */
    (xdc_Char)0x6b,  /* [551] */
    (xdc_Char)0x20,  /* [552] */
    (xdc_Char)0x4d,  /* [553] */
    (xdc_Char)0x6f,  /* [554] */
    (xdc_Char)0x64,  /* [555] */
    (xdc_Char)0x65,  /* [556] */
    (xdc_Char)0x2e,  /* [557] */
    (xdc_Char)0x0,  /* [558] */
    (xdc_Char)0x41,  /* [559] */
    (xdc_Char)0x5f,  /* [560] */
    (xdc_Char)0x6e,  /* [561] */
    (xdc_Char)0x75,  /* [562] */
    (xdc_Char)0x6c,  /* [563] */
    (xdc_Char)0x6c,  /* [564] */
    (xdc_Char)0x50,  /* [565] */
    (xdc_Char)0x6f,  /* [566] */
    (xdc_Char)0x69,  /* [567] */
    (xdc_Char)0x6e,  /* [568] */
    (xdc_Char)0x74,  /* [569] */
    (xdc_Char)0x65,  /* [570] */
    (xdc_Char)0x72,  /* [571] */
    (xdc_Char)0x3a,  /* [572] */
    (xdc_Char)0x20,  /* [573] */
    (xdc_Char)0x50,  /* [574] */
    (xdc_Char)0x6f,  /* [575] */
    (xdc_Char)0x69,  /* [576] */
    (xdc_Char)0x6e,  /* [577] */
    (xdc_Char)0x74,  /* [578] */
    (xdc_Char)0x65,  /* [579] */
    (xdc_Char)0x72,  /* [580] */
    (xdc_Char)0x20,  /* [581] */
    (xdc_Char)0x69,  /* [582] */
    (xdc_Char)0x73,  /* [583] */
    (xdc_Char)0x20,  /* [584] */
    (xdc_Char)0x6e,  /* [585] */
    (xdc_Char)0x75,  /* [586] */
    (xdc_Char)0x6c,  /* [587] */
    (xdc_Char)0x6c,  /* [588] */
    (xdc_Char)0x0,  /* [589] */
    (xdc_Char)0x41,  /* [590] */
    (xdc_Char)0x5f,  /* [591] */
    (xdc_Char)0x69,  /* [592] */
    (xdc_Char)0x6e,  /* [593] */
    (xdc_Char)0x76,  /* [594] */
    (xdc_Char)0x61,  /* [595] */
    (xdc_Char)0x6c,  /* [596] */
    (xdc_Char)0x69,  /* [597] */
    (xdc_Char)0x64,  /* [598] */
    (xdc_Char)0x52,  /* [599] */
    (xdc_Char)0x65,  /* [600] */
    (xdc_Char)0x67,  /* [601] */
    (xdc_Char)0x69,  /* [602] */
    (xdc_Char)0x6f,  /* [603] */
    (xdc_Char)0x6e,  /* [604] */
    (xdc_Char)0x49,  /* [605] */
    (xdc_Char)0x64,  /* [606] */
    (xdc_Char)0x3a,  /* [607] */
    (xdc_Char)0x20,  /* [608] */
    (xdc_Char)0x4d,  /* [609] */
    (xdc_Char)0x50,  /* [610] */
    (xdc_Char)0x55,  /* [611] */
    (xdc_Char)0x20,  /* [612] */
    (xdc_Char)0x52,  /* [613] */
    (xdc_Char)0x65,  /* [614] */
    (xdc_Char)0x67,  /* [615] */
    (xdc_Char)0x69,  /* [616] */
    (xdc_Char)0x6f,  /* [617] */
    (xdc_Char)0x6e,  /* [618] */
    (xdc_Char)0x20,  /* [619] */
    (xdc_Char)0x6e,  /* [620] */
    (xdc_Char)0x75,  /* [621] */
    (xdc_Char)0x6d,  /* [622] */
    (xdc_Char)0x62,  /* [623] */
    (xdc_Char)0x65,  /* [624] */
    (xdc_Char)0x72,  /* [625] */
    (xdc_Char)0x20,  /* [626] */
    (xdc_Char)0x70,  /* [627] */
    (xdc_Char)0x61,  /* [628] */
    (xdc_Char)0x73,  /* [629] */
    (xdc_Char)0x73,  /* [630] */
    (xdc_Char)0x65,  /* [631] */
    (xdc_Char)0x64,  /* [632] */
    (xdc_Char)0x20,  /* [633] */
    (xdc_Char)0x69,  /* [634] */
    (xdc_Char)0x73,  /* [635] */
    (xdc_Char)0x20,  /* [636] */
    (xdc_Char)0x69,  /* [637] */
    (xdc_Char)0x6e,  /* [638] */
    (xdc_Char)0x76,  /* [639] */
    (xdc_Char)0x61,  /* [640] */
    (xdc_Char)0x6c,  /* [641] */
    (xdc_Char)0x69,  /* [642] */
    (xdc_Char)0x64,  /* [643] */
    (xdc_Char)0x2e,  /* [644] */
    (xdc_Char)0x0,  /* [645] */
    (xdc_Char)0x41,  /* [646] */
    (xdc_Char)0x5f,  /* [647] */
    (xdc_Char)0x63,  /* [648] */
    (xdc_Char)0x6c,  /* [649] */
    (xdc_Char)0x6f,  /* [650] */
    (xdc_Char)0x63,  /* [651] */
    (xdc_Char)0x6b,  /* [652] */
    (xdc_Char)0x44,  /* [653] */
    (xdc_Char)0x69,  /* [654] */
    (xdc_Char)0x73,  /* [655] */
    (xdc_Char)0x61,  /* [656] */
    (xdc_Char)0x62,  /* [657] */
    (xdc_Char)0x6c,  /* [658] */
    (xdc_Char)0x65,  /* [659] */
    (xdc_Char)0x64,  /* [660] */
    (xdc_Char)0x3a,  /* [661] */
    (xdc_Char)0x20,  /* [662] */
    (xdc_Char)0x43,  /* [663] */
    (xdc_Char)0x61,  /* [664] */
    (xdc_Char)0x6e,  /* [665] */
    (xdc_Char)0x6e,  /* [666] */
    (xdc_Char)0x6f,  /* [667] */
    (xdc_Char)0x74,  /* [668] */
    (xdc_Char)0x20,  /* [669] */
    (xdc_Char)0x63,  /* [670] */
    (xdc_Char)0x72,  /* [671] */
    (xdc_Char)0x65,  /* [672] */
    (xdc_Char)0x61,  /* [673] */
    (xdc_Char)0x74,  /* [674] */
    (xdc_Char)0x65,  /* [675] */
    (xdc_Char)0x20,  /* [676] */
    (xdc_Char)0x61,  /* [677] */
    (xdc_Char)0x20,  /* [678] */
    (xdc_Char)0x63,  /* [679] */
    (xdc_Char)0x6c,  /* [680] */
    (xdc_Char)0x6f,  /* [681] */
    (xdc_Char)0x63,  /* [682] */
    (xdc_Char)0x6b,  /* [683] */
    (xdc_Char)0x20,  /* [684] */
    (xdc_Char)0x69,  /* [685] */
    (xdc_Char)0x6e,  /* [686] */
    (xdc_Char)0x73,  /* [687] */
    (xdc_Char)0x74,  /* [688] */
    (xdc_Char)0x61,  /* [689] */
    (xdc_Char)0x6e,  /* [690] */
    (xdc_Char)0x63,  /* [691] */
    (xdc_Char)0x65,  /* [692] */
    (xdc_Char)0x20,  /* [693] */
    (xdc_Char)0x77,  /* [694] */
    (xdc_Char)0x68,  /* [695] */
    (xdc_Char)0x65,  /* [696] */
    (xdc_Char)0x6e,  /* [697] */
    (xdc_Char)0x20,  /* [698] */
    (xdc_Char)0x42,  /* [699] */
    (xdc_Char)0x49,  /* [700] */
    (xdc_Char)0x4f,  /* [701] */
    (xdc_Char)0x53,  /* [702] */
    (xdc_Char)0x2e,  /* [703] */
    (xdc_Char)0x63,  /* [704] */
    (xdc_Char)0x6c,  /* [705] */
    (xdc_Char)0x6f,  /* [706] */
    (xdc_Char)0x63,  /* [707] */
    (xdc_Char)0x6b,  /* [708] */
    (xdc_Char)0x45,  /* [709] */
    (xdc_Char)0x6e,  /* [710] */
    (xdc_Char)0x61,  /* [711] */
    (xdc_Char)0x62,  /* [712] */
    (xdc_Char)0x6c,  /* [713] */
    (xdc_Char)0x65,  /* [714] */
    (xdc_Char)0x64,  /* [715] */
    (xdc_Char)0x20,  /* [716] */
    (xdc_Char)0x69,  /* [717] */
    (xdc_Char)0x73,  /* [718] */
    (xdc_Char)0x20,  /* [719] */
    (xdc_Char)0x66,  /* [720] */
    (xdc_Char)0x61,  /* [721] */
    (xdc_Char)0x6c,  /* [722] */
    (xdc_Char)0x73,  /* [723] */
    (xdc_Char)0x65,  /* [724] */
    (xdc_Char)0x2e,  /* [725] */
    (xdc_Char)0x0,  /* [726] */
    (xdc_Char)0x41,  /* [727] */
    (xdc_Char)0x5f,  /* [728] */
    (xdc_Char)0x62,  /* [729] */
    (xdc_Char)0x61,  /* [730] */
    (xdc_Char)0x64,  /* [731] */
    (xdc_Char)0x54,  /* [732] */
    (xdc_Char)0x68,  /* [733] */
    (xdc_Char)0x72,  /* [734] */
    (xdc_Char)0x65,  /* [735] */
    (xdc_Char)0x61,  /* [736] */
    (xdc_Char)0x64,  /* [737] */
    (xdc_Char)0x54,  /* [738] */
    (xdc_Char)0x79,  /* [739] */
    (xdc_Char)0x70,  /* [740] */
    (xdc_Char)0x65,  /* [741] */
    (xdc_Char)0x3a,  /* [742] */
    (xdc_Char)0x20,  /* [743] */
    (xdc_Char)0x43,  /* [744] */
    (xdc_Char)0x61,  /* [745] */
    (xdc_Char)0x6e,  /* [746] */
    (xdc_Char)0x6e,  /* [747] */
    (xdc_Char)0x6f,  /* [748] */
    (xdc_Char)0x74,  /* [749] */
    (xdc_Char)0x20,  /* [750] */
    (xdc_Char)0x63,  /* [751] */
    (xdc_Char)0x72,  /* [752] */
    (xdc_Char)0x65,  /* [753] */
    (xdc_Char)0x61,  /* [754] */
    (xdc_Char)0x74,  /* [755] */
    (xdc_Char)0x65,  /* [756] */
    (xdc_Char)0x2f,  /* [757] */
    (xdc_Char)0x64,  /* [758] */
    (xdc_Char)0x65,  /* [759] */
    (xdc_Char)0x6c,  /* [760] */
    (xdc_Char)0x65,  /* [761] */
    (xdc_Char)0x74,  /* [762] */
    (xdc_Char)0x65,  /* [763] */
    (xdc_Char)0x20,  /* [764] */
    (xdc_Char)0x61,  /* [765] */
    (xdc_Char)0x20,  /* [766] */
    (xdc_Char)0x43,  /* [767] */
    (xdc_Char)0x6c,  /* [768] */
    (xdc_Char)0x6f,  /* [769] */
    (xdc_Char)0x63,  /* [770] */
    (xdc_Char)0x6b,  /* [771] */
    (xdc_Char)0x20,  /* [772] */
    (xdc_Char)0x66,  /* [773] */
    (xdc_Char)0x72,  /* [774] */
    (xdc_Char)0x6f,  /* [775] */
    (xdc_Char)0x6d,  /* [776] */
    (xdc_Char)0x20,  /* [777] */
    (xdc_Char)0x48,  /* [778] */
    (xdc_Char)0x77,  /* [779] */
    (xdc_Char)0x69,  /* [780] */
    (xdc_Char)0x20,  /* [781] */
    (xdc_Char)0x6f,  /* [782] */
    (xdc_Char)0x72,  /* [783] */
    (xdc_Char)0x20,  /* [784] */
    (xdc_Char)0x53,  /* [785] */
    (xdc_Char)0x77,  /* [786] */
    (xdc_Char)0x69,  /* [787] */
    (xdc_Char)0x20,  /* [788] */
    (xdc_Char)0x74,  /* [789] */
    (xdc_Char)0x68,  /* [790] */
    (xdc_Char)0x72,  /* [791] */
    (xdc_Char)0x65,  /* [792] */
    (xdc_Char)0x61,  /* [793] */
    (xdc_Char)0x64,  /* [794] */
    (xdc_Char)0x2e,  /* [795] */
    (xdc_Char)0x0,  /* [796] */
    (xdc_Char)0x41,  /* [797] */
    (xdc_Char)0x5f,  /* [798] */
    (xdc_Char)0x6e,  /* [799] */
    (xdc_Char)0x75,  /* [800] */
    (xdc_Char)0x6c,  /* [801] */
    (xdc_Char)0x6c,  /* [802] */
    (xdc_Char)0x45,  /* [803] */
    (xdc_Char)0x76,  /* [804] */
    (xdc_Char)0x65,  /* [805] */
    (xdc_Char)0x6e,  /* [806] */
    (xdc_Char)0x74,  /* [807] */
    (xdc_Char)0x4d,  /* [808] */
    (xdc_Char)0x61,  /* [809] */
    (xdc_Char)0x73,  /* [810] */
    (xdc_Char)0x6b,  /* [811] */
    (xdc_Char)0x73,  /* [812] */
    (xdc_Char)0x3a,  /* [813] */
    (xdc_Char)0x20,  /* [814] */
    (xdc_Char)0x6f,  /* [815] */
    (xdc_Char)0x72,  /* [816] */
    (xdc_Char)0x4d,  /* [817] */
    (xdc_Char)0x61,  /* [818] */
    (xdc_Char)0x73,  /* [819] */
    (xdc_Char)0x6b,  /* [820] */
    (xdc_Char)0x20,  /* [821] */
    (xdc_Char)0x61,  /* [822] */
    (xdc_Char)0x6e,  /* [823] */
    (xdc_Char)0x64,  /* [824] */
    (xdc_Char)0x20,  /* [825] */
    (xdc_Char)0x61,  /* [826] */
    (xdc_Char)0x6e,  /* [827] */
    (xdc_Char)0x64,  /* [828] */
    (xdc_Char)0x4d,  /* [829] */
    (xdc_Char)0x61,  /* [830] */
    (xdc_Char)0x73,  /* [831] */
    (xdc_Char)0x6b,  /* [832] */
    (xdc_Char)0x20,  /* [833] */
    (xdc_Char)0x61,  /* [834] */
    (xdc_Char)0x72,  /* [835] */
    (xdc_Char)0x65,  /* [836] */
    (xdc_Char)0x20,  /* [837] */
    (xdc_Char)0x6e,  /* [838] */
    (xdc_Char)0x75,  /* [839] */
    (xdc_Char)0x6c,  /* [840] */
    (xdc_Char)0x6c,  /* [841] */
    (xdc_Char)0x2e,  /* [842] */
    (xdc_Char)0x0,  /* [843] */
    (xdc_Char)0x41,  /* [844] */
    (xdc_Char)0x5f,  /* [845] */
    (xdc_Char)0x6e,  /* [846] */
    (xdc_Char)0x75,  /* [847] */
    (xdc_Char)0x6c,  /* [848] */
    (xdc_Char)0x6c,  /* [849] */
    (xdc_Char)0x45,  /* [850] */
    (xdc_Char)0x76,  /* [851] */
    (xdc_Char)0x65,  /* [852] */
    (xdc_Char)0x6e,  /* [853] */
    (xdc_Char)0x74,  /* [854] */
    (xdc_Char)0x49,  /* [855] */
    (xdc_Char)0x64,  /* [856] */
    (xdc_Char)0x3a,  /* [857] */
    (xdc_Char)0x20,  /* [858] */
    (xdc_Char)0x70,  /* [859] */
    (xdc_Char)0x6f,  /* [860] */
    (xdc_Char)0x73,  /* [861] */
    (xdc_Char)0x74,  /* [862] */
    (xdc_Char)0x65,  /* [863] */
    (xdc_Char)0x64,  /* [864] */
    (xdc_Char)0x20,  /* [865] */
    (xdc_Char)0x65,  /* [866] */
    (xdc_Char)0x76,  /* [867] */
    (xdc_Char)0x65,  /* [868] */
    (xdc_Char)0x6e,  /* [869] */
    (xdc_Char)0x74,  /* [870] */
    (xdc_Char)0x49,  /* [871] */
    (xdc_Char)0x64,  /* [872] */
    (xdc_Char)0x20,  /* [873] */
    (xdc_Char)0x69,  /* [874] */
    (xdc_Char)0x73,  /* [875] */
    (xdc_Char)0x20,  /* [876] */
    (xdc_Char)0x6e,  /* [877] */
    (xdc_Char)0x75,  /* [878] */
    (xdc_Char)0x6c,  /* [879] */
    (xdc_Char)0x6c,  /* [880] */
    (xdc_Char)0x2e,  /* [881] */
    (xdc_Char)0x0,  /* [882] */
    (xdc_Char)0x41,  /* [883] */
    (xdc_Char)0x5f,  /* [884] */
    (xdc_Char)0x65,  /* [885] */
    (xdc_Char)0x76,  /* [886] */
    (xdc_Char)0x65,  /* [887] */
    (xdc_Char)0x6e,  /* [888] */
    (xdc_Char)0x74,  /* [889] */
    (xdc_Char)0x49,  /* [890] */
    (xdc_Char)0x6e,  /* [891] */
    (xdc_Char)0x55,  /* [892] */
    (xdc_Char)0x73,  /* [893] */
    (xdc_Char)0x65,  /* [894] */
    (xdc_Char)0x3a,  /* [895] */
    (xdc_Char)0x20,  /* [896] */
    (xdc_Char)0x45,  /* [897] */
    (xdc_Char)0x76,  /* [898] */
    (xdc_Char)0x65,  /* [899] */
    (xdc_Char)0x6e,  /* [900] */
    (xdc_Char)0x74,  /* [901] */
    (xdc_Char)0x20,  /* [902] */
    (xdc_Char)0x6f,  /* [903] */
    (xdc_Char)0x62,  /* [904] */
    (xdc_Char)0x6a,  /* [905] */
    (xdc_Char)0x65,  /* [906] */
    (xdc_Char)0x63,  /* [907] */
    (xdc_Char)0x74,  /* [908] */
    (xdc_Char)0x20,  /* [909] */
    (xdc_Char)0x61,  /* [910] */
    (xdc_Char)0x6c,  /* [911] */
    (xdc_Char)0x72,  /* [912] */
    (xdc_Char)0x65,  /* [913] */
    (xdc_Char)0x61,  /* [914] */
    (xdc_Char)0x64,  /* [915] */
    (xdc_Char)0x79,  /* [916] */
    (xdc_Char)0x20,  /* [917] */
    (xdc_Char)0x69,  /* [918] */
    (xdc_Char)0x6e,  /* [919] */
    (xdc_Char)0x20,  /* [920] */
    (xdc_Char)0x75,  /* [921] */
    (xdc_Char)0x73,  /* [922] */
    (xdc_Char)0x65,  /* [923] */
    (xdc_Char)0x2e,  /* [924] */
    (xdc_Char)0x0,  /* [925] */
    (xdc_Char)0x41,  /* [926] */
    (xdc_Char)0x5f,  /* [927] */
    (xdc_Char)0x62,  /* [928] */
    (xdc_Char)0x61,  /* [929] */
    (xdc_Char)0x64,  /* [930] */
    (xdc_Char)0x43,  /* [931] */
    (xdc_Char)0x6f,  /* [932] */
    (xdc_Char)0x6e,  /* [933] */
    (xdc_Char)0x74,  /* [934] */
    (xdc_Char)0x65,  /* [935] */
    (xdc_Char)0x78,  /* [936] */
    (xdc_Char)0x74,  /* [937] */
    (xdc_Char)0x3a,  /* [938] */
    (xdc_Char)0x20,  /* [939] */
    (xdc_Char)0x62,  /* [940] */
    (xdc_Char)0x61,  /* [941] */
    (xdc_Char)0x64,  /* [942] */
    (xdc_Char)0x20,  /* [943] */
    (xdc_Char)0x63,  /* [944] */
    (xdc_Char)0x61,  /* [945] */
    (xdc_Char)0x6c,  /* [946] */
    (xdc_Char)0x6c,  /* [947] */
    (xdc_Char)0x69,  /* [948] */
    (xdc_Char)0x6e,  /* [949] */
    (xdc_Char)0x67,  /* [950] */
    (xdc_Char)0x20,  /* [951] */
    (xdc_Char)0x63,  /* [952] */
    (xdc_Char)0x6f,  /* [953] */
    (xdc_Char)0x6e,  /* [954] */
    (xdc_Char)0x74,  /* [955] */
    (xdc_Char)0x65,  /* [956] */
    (xdc_Char)0x78,  /* [957] */
    (xdc_Char)0x74,  /* [958] */
    (xdc_Char)0x2e,  /* [959] */
    (xdc_Char)0x20,  /* [960] */
    (xdc_Char)0x4d,  /* [961] */
    (xdc_Char)0x75,  /* [962] */
    (xdc_Char)0x73,  /* [963] */
    (xdc_Char)0x74,  /* [964] */
    (xdc_Char)0x20,  /* [965] */
    (xdc_Char)0x62,  /* [966] */
    (xdc_Char)0x65,  /* [967] */
    (xdc_Char)0x20,  /* [968] */
    (xdc_Char)0x63,  /* [969] */
    (xdc_Char)0x61,  /* [970] */
    (xdc_Char)0x6c,  /* [971] */
    (xdc_Char)0x6c,  /* [972] */
    (xdc_Char)0x65,  /* [973] */
    (xdc_Char)0x64,  /* [974] */
    (xdc_Char)0x20,  /* [975] */
    (xdc_Char)0x66,  /* [976] */
    (xdc_Char)0x72,  /* [977] */
    (xdc_Char)0x6f,  /* [978] */
    (xdc_Char)0x6d,  /* [979] */
    (xdc_Char)0x20,  /* [980] */
    (xdc_Char)0x61,  /* [981] */
    (xdc_Char)0x20,  /* [982] */
    (xdc_Char)0x54,  /* [983] */
    (xdc_Char)0x61,  /* [984] */
    (xdc_Char)0x73,  /* [985] */
    (xdc_Char)0x6b,  /* [986] */
    (xdc_Char)0x2e,  /* [987] */
    (xdc_Char)0x0,  /* [988] */
    (xdc_Char)0x41,  /* [989] */
    (xdc_Char)0x5f,  /* [990] */
    (xdc_Char)0x70,  /* [991] */
    (xdc_Char)0x65,  /* [992] */
    (xdc_Char)0x6e,  /* [993] */
    (xdc_Char)0x64,  /* [994] */
    (xdc_Char)0x54,  /* [995] */
    (xdc_Char)0x61,  /* [996] */
    (xdc_Char)0x73,  /* [997] */
    (xdc_Char)0x6b,  /* [998] */
    (xdc_Char)0x44,  /* [999] */
    (xdc_Char)0x69,  /* [1000] */
    (xdc_Char)0x73,  /* [1001] */
    (xdc_Char)0x61,  /* [1002] */
    (xdc_Char)0x62,  /* [1003] */
    (xdc_Char)0x6c,  /* [1004] */
    (xdc_Char)0x65,  /* [1005] */
    (xdc_Char)0x64,  /* [1006] */
    (xdc_Char)0x3a,  /* [1007] */
    (xdc_Char)0x20,  /* [1008] */
    (xdc_Char)0x43,  /* [1009] */
    (xdc_Char)0x61,  /* [1010] */
    (xdc_Char)0x6e,  /* [1011] */
    (xdc_Char)0x6e,  /* [1012] */
    (xdc_Char)0x6f,  /* [1013] */
    (xdc_Char)0x74,  /* [1014] */
    (xdc_Char)0x20,  /* [1015] */
    (xdc_Char)0x63,  /* [1016] */
    (xdc_Char)0x61,  /* [1017] */
    (xdc_Char)0x6c,  /* [1018] */
    (xdc_Char)0x6c,  /* [1019] */
    (xdc_Char)0x20,  /* [1020] */
    (xdc_Char)0x45,  /* [1021] */
    (xdc_Char)0x76,  /* [1022] */
    (xdc_Char)0x65,  /* [1023] */
    (xdc_Char)0x6e,  /* [1024] */
    (xdc_Char)0x74,  /* [1025] */
    (xdc_Char)0x5f,  /* [1026] */
    (xdc_Char)0x70,  /* [1027] */
    (xdc_Char)0x65,  /* [1028] */
    (xdc_Char)0x6e,  /* [1029] */
    (xdc_Char)0x64,  /* [1030] */
    (xdc_Char)0x28,  /* [1031] */
    (xdc_Char)0x29,  /* [1032] */
    (xdc_Char)0x20,  /* [1033] */
    (xdc_Char)0x77,  /* [1034] */
    (xdc_Char)0x68,  /* [1035] */
    (xdc_Char)0x69,  /* [1036] */
    (xdc_Char)0x6c,  /* [1037] */
    (xdc_Char)0x65,  /* [1038] */
    (xdc_Char)0x20,  /* [1039] */
    (xdc_Char)0x74,  /* [1040] */
    (xdc_Char)0x68,  /* [1041] */
    (xdc_Char)0x65,  /* [1042] */
    (xdc_Char)0x20,  /* [1043] */
    (xdc_Char)0x54,  /* [1044] */
    (xdc_Char)0x61,  /* [1045] */
    (xdc_Char)0x73,  /* [1046] */
    (xdc_Char)0x6b,  /* [1047] */
    (xdc_Char)0x20,  /* [1048] */
    (xdc_Char)0x6f,  /* [1049] */
    (xdc_Char)0x72,  /* [1050] */
    (xdc_Char)0x20,  /* [1051] */
    (xdc_Char)0x53,  /* [1052] */
    (xdc_Char)0x77,  /* [1053] */
    (xdc_Char)0x69,  /* [1054] */
    (xdc_Char)0x20,  /* [1055] */
    (xdc_Char)0x73,  /* [1056] */
    (xdc_Char)0x63,  /* [1057] */
    (xdc_Char)0x68,  /* [1058] */
    (xdc_Char)0x65,  /* [1059] */
    (xdc_Char)0x64,  /* [1060] */
    (xdc_Char)0x75,  /* [1061] */
    (xdc_Char)0x6c,  /* [1062] */
    (xdc_Char)0x65,  /* [1063] */
    (xdc_Char)0x72,  /* [1064] */
    (xdc_Char)0x20,  /* [1065] */
    (xdc_Char)0x69,  /* [1066] */
    (xdc_Char)0x73,  /* [1067] */
    (xdc_Char)0x20,  /* [1068] */
    (xdc_Char)0x64,  /* [1069] */
    (xdc_Char)0x69,  /* [1070] */
    (xdc_Char)0x73,  /* [1071] */
    (xdc_Char)0x61,  /* [1072] */
    (xdc_Char)0x62,  /* [1073] */
    (xdc_Char)0x6c,  /* [1074] */
    (xdc_Char)0x65,  /* [1075] */
    (xdc_Char)0x64,  /* [1076] */
    (xdc_Char)0x2e,  /* [1077] */
    (xdc_Char)0x0,  /* [1078] */
    (xdc_Char)0x4d,  /* [1079] */
    (xdc_Char)0x61,  /* [1080] */
    (xdc_Char)0x69,  /* [1081] */
    (xdc_Char)0x6c,  /* [1082] */
    (xdc_Char)0x62,  /* [1083] */
    (xdc_Char)0x6f,  /* [1084] */
    (xdc_Char)0x78,  /* [1085] */
    (xdc_Char)0x5f,  /* [1086] */
    (xdc_Char)0x63,  /* [1087] */
    (xdc_Char)0x72,  /* [1088] */
    (xdc_Char)0x65,  /* [1089] */
    (xdc_Char)0x61,  /* [1090] */
    (xdc_Char)0x74,  /* [1091] */
    (xdc_Char)0x65,  /* [1092] */
    (xdc_Char)0x27,  /* [1093] */
    (xdc_Char)0x73,  /* [1094] */
    (xdc_Char)0x20,  /* [1095] */
    (xdc_Char)0x62,  /* [1096] */
    (xdc_Char)0x75,  /* [1097] */
    (xdc_Char)0x66,  /* [1098] */
    (xdc_Char)0x53,  /* [1099] */
    (xdc_Char)0x69,  /* [1100] */
    (xdc_Char)0x7a,  /* [1101] */
    (xdc_Char)0x65,  /* [1102] */
    (xdc_Char)0x20,  /* [1103] */
    (xdc_Char)0x70,  /* [1104] */
    (xdc_Char)0x61,  /* [1105] */
    (xdc_Char)0x72,  /* [1106] */
    (xdc_Char)0x61,  /* [1107] */
    (xdc_Char)0x6d,  /* [1108] */
    (xdc_Char)0x65,  /* [1109] */
    (xdc_Char)0x74,  /* [1110] */
    (xdc_Char)0x65,  /* [1111] */
    (xdc_Char)0x72,  /* [1112] */
    (xdc_Char)0x20,  /* [1113] */
    (xdc_Char)0x69,  /* [1114] */
    (xdc_Char)0x73,  /* [1115] */
    (xdc_Char)0x20,  /* [1116] */
    (xdc_Char)0x69,  /* [1117] */
    (xdc_Char)0x6e,  /* [1118] */
    (xdc_Char)0x76,  /* [1119] */
    (xdc_Char)0x61,  /* [1120] */
    (xdc_Char)0x6c,  /* [1121] */
    (xdc_Char)0x69,  /* [1122] */
    (xdc_Char)0x64,  /* [1123] */
    (xdc_Char)0x20,  /* [1124] */
    (xdc_Char)0x28,  /* [1125] */
    (xdc_Char)0x74,  /* [1126] */
    (xdc_Char)0x6f,  /* [1127] */
    (xdc_Char)0x6f,  /* [1128] */
    (xdc_Char)0x20,  /* [1129] */
    (xdc_Char)0x73,  /* [1130] */
    (xdc_Char)0x6d,  /* [1131] */
    (xdc_Char)0x61,  /* [1132] */
    (xdc_Char)0x6c,  /* [1133] */
    (xdc_Char)0x6c,  /* [1134] */
    (xdc_Char)0x29,  /* [1135] */
    (xdc_Char)0x0,  /* [1136] */
    (xdc_Char)0x41,  /* [1137] */
    (xdc_Char)0x5f,  /* [1138] */
    (xdc_Char)0x6e,  /* [1139] */
    (xdc_Char)0x6f,  /* [1140] */
    (xdc_Char)0x45,  /* [1141] */
    (xdc_Char)0x76,  /* [1142] */
    (xdc_Char)0x65,  /* [1143] */
    (xdc_Char)0x6e,  /* [1144] */
    (xdc_Char)0x74,  /* [1145] */
    (xdc_Char)0x73,  /* [1146] */
    (xdc_Char)0x3a,  /* [1147] */
    (xdc_Char)0x20,  /* [1148] */
    (xdc_Char)0x54,  /* [1149] */
    (xdc_Char)0x68,  /* [1150] */
    (xdc_Char)0x65,  /* [1151] */
    (xdc_Char)0x20,  /* [1152] */
    (xdc_Char)0x45,  /* [1153] */
    (xdc_Char)0x76,  /* [1154] */
    (xdc_Char)0x65,  /* [1155] */
    (xdc_Char)0x6e,  /* [1156] */
    (xdc_Char)0x74,  /* [1157] */
    (xdc_Char)0x2e,  /* [1158] */
    (xdc_Char)0x73,  /* [1159] */
    (xdc_Char)0x75,  /* [1160] */
    (xdc_Char)0x70,  /* [1161] */
    (xdc_Char)0x70,  /* [1162] */
    (xdc_Char)0x6f,  /* [1163] */
    (xdc_Char)0x72,  /* [1164] */
    (xdc_Char)0x74,  /* [1165] */
    (xdc_Char)0x73,  /* [1166] */
    (xdc_Char)0x45,  /* [1167] */
    (xdc_Char)0x76,  /* [1168] */
    (xdc_Char)0x65,  /* [1169] */
    (xdc_Char)0x6e,  /* [1170] */
    (xdc_Char)0x74,  /* [1171] */
    (xdc_Char)0x73,  /* [1172] */
    (xdc_Char)0x20,  /* [1173] */
    (xdc_Char)0x66,  /* [1174] */
    (xdc_Char)0x6c,  /* [1175] */
    (xdc_Char)0x61,  /* [1176] */
    (xdc_Char)0x67,  /* [1177] */
    (xdc_Char)0x20,  /* [1178] */
    (xdc_Char)0x69,  /* [1179] */
    (xdc_Char)0x73,  /* [1180] */
    (xdc_Char)0x20,  /* [1181] */
    (xdc_Char)0x64,  /* [1182] */
    (xdc_Char)0x69,  /* [1183] */
    (xdc_Char)0x73,  /* [1184] */
    (xdc_Char)0x61,  /* [1185] */
    (xdc_Char)0x62,  /* [1186] */
    (xdc_Char)0x6c,  /* [1187] */
    (xdc_Char)0x65,  /* [1188] */
    (xdc_Char)0x64,  /* [1189] */
    (xdc_Char)0x2e,  /* [1190] */
    (xdc_Char)0x0,  /* [1191] */
    (xdc_Char)0x41,  /* [1192] */
    (xdc_Char)0x5f,  /* [1193] */
    (xdc_Char)0x69,  /* [1194] */
    (xdc_Char)0x6e,  /* [1195] */
    (xdc_Char)0x76,  /* [1196] */
    (xdc_Char)0x54,  /* [1197] */
    (xdc_Char)0x69,  /* [1198] */
    (xdc_Char)0x6d,  /* [1199] */
    (xdc_Char)0x65,  /* [1200] */
    (xdc_Char)0x6f,  /* [1201] */
    (xdc_Char)0x75,  /* [1202] */
    (xdc_Char)0x74,  /* [1203] */
    (xdc_Char)0x3a,  /* [1204] */
    (xdc_Char)0x20,  /* [1205] */
    (xdc_Char)0x43,  /* [1206] */
    (xdc_Char)0x61,  /* [1207] */
    (xdc_Char)0x6e,  /* [1208] */
    (xdc_Char)0x27,  /* [1209] */
    (xdc_Char)0x74,  /* [1210] */
    (xdc_Char)0x20,  /* [1211] */
    (xdc_Char)0x75,  /* [1212] */
    (xdc_Char)0x73,  /* [1213] */
    (xdc_Char)0x65,  /* [1214] */
    (xdc_Char)0x20,  /* [1215] */
    (xdc_Char)0x42,  /* [1216] */
    (xdc_Char)0x49,  /* [1217] */
    (xdc_Char)0x4f,  /* [1218] */
    (xdc_Char)0x53,  /* [1219] */
    (xdc_Char)0x5f,  /* [1220] */
    (xdc_Char)0x45,  /* [1221] */
    (xdc_Char)0x56,  /* [1222] */
    (xdc_Char)0x45,  /* [1223] */
    (xdc_Char)0x4e,  /* [1224] */
    (xdc_Char)0x54,  /* [1225] */
    (xdc_Char)0x5f,  /* [1226] */
    (xdc_Char)0x41,  /* [1227] */
    (xdc_Char)0x43,  /* [1228] */
    (xdc_Char)0x51,  /* [1229] */
    (xdc_Char)0x55,  /* [1230] */
    (xdc_Char)0x49,  /* [1231] */
    (xdc_Char)0x52,  /* [1232] */
    (xdc_Char)0x45,  /* [1233] */
    (xdc_Char)0x44,  /* [1234] */
    (xdc_Char)0x20,  /* [1235] */
    (xdc_Char)0x77,  /* [1236] */
    (xdc_Char)0x69,  /* [1237] */
    (xdc_Char)0x74,  /* [1238] */
    (xdc_Char)0x68,  /* [1239] */
    (xdc_Char)0x20,  /* [1240] */
    (xdc_Char)0x74,  /* [1241] */
    (xdc_Char)0x68,  /* [1242] */
    (xdc_Char)0x69,  /* [1243] */
    (xdc_Char)0x73,  /* [1244] */
    (xdc_Char)0x20,  /* [1245] */
    (xdc_Char)0x53,  /* [1246] */
    (xdc_Char)0x65,  /* [1247] */
    (xdc_Char)0x6d,  /* [1248] */
    (xdc_Char)0x61,  /* [1249] */
    (xdc_Char)0x70,  /* [1250] */
    (xdc_Char)0x68,  /* [1251] */
    (xdc_Char)0x6f,  /* [1252] */
    (xdc_Char)0x72,  /* [1253] */
    (xdc_Char)0x65,  /* [1254] */
    (xdc_Char)0x2e,  /* [1255] */
    (xdc_Char)0x0,  /* [1256] */
    (xdc_Char)0x41,  /* [1257] */
    (xdc_Char)0x5f,  /* [1258] */
    (xdc_Char)0x6f,  /* [1259] */
    (xdc_Char)0x76,  /* [1260] */
    (xdc_Char)0x65,  /* [1261] */
    (xdc_Char)0x72,  /* [1262] */
    (xdc_Char)0x66,  /* [1263] */
    (xdc_Char)0x6c,  /* [1264] */
    (xdc_Char)0x6f,  /* [1265] */
    (xdc_Char)0x77,  /* [1266] */
    (xdc_Char)0x3a,  /* [1267] */
    (xdc_Char)0x20,  /* [1268] */
    (xdc_Char)0x43,  /* [1269] */
    (xdc_Char)0x6f,  /* [1270] */
    (xdc_Char)0x75,  /* [1271] */
    (xdc_Char)0x6e,  /* [1272] */
    (xdc_Char)0x74,  /* [1273] */
    (xdc_Char)0x20,  /* [1274] */
    (xdc_Char)0x68,  /* [1275] */
    (xdc_Char)0x61,  /* [1276] */
    (xdc_Char)0x73,  /* [1277] */
    (xdc_Char)0x20,  /* [1278] */
    (xdc_Char)0x65,  /* [1279] */
    (xdc_Char)0x78,  /* [1280] */
    (xdc_Char)0x63,  /* [1281] */
    (xdc_Char)0x65,  /* [1282] */
    (xdc_Char)0x65,  /* [1283] */
    (xdc_Char)0x64,  /* [1284] */
    (xdc_Char)0x65,  /* [1285] */
    (xdc_Char)0x64,  /* [1286] */
    (xdc_Char)0x20,  /* [1287] */
    (xdc_Char)0x36,  /* [1288] */
    (xdc_Char)0x35,  /* [1289] */
    (xdc_Char)0x35,  /* [1290] */
    (xdc_Char)0x33,  /* [1291] */
    (xdc_Char)0x35,  /* [1292] */
    (xdc_Char)0x20,  /* [1293] */
    (xdc_Char)0x61,  /* [1294] */
    (xdc_Char)0x6e,  /* [1295] */
    (xdc_Char)0x64,  /* [1296] */
    (xdc_Char)0x20,  /* [1297] */
    (xdc_Char)0x72,  /* [1298] */
    (xdc_Char)0x6f,  /* [1299] */
    (xdc_Char)0x6c,  /* [1300] */
    (xdc_Char)0x6c,  /* [1301] */
    (xdc_Char)0x65,  /* [1302] */
    (xdc_Char)0x64,  /* [1303] */
    (xdc_Char)0x20,  /* [1304] */
    (xdc_Char)0x6f,  /* [1305] */
    (xdc_Char)0x76,  /* [1306] */
    (xdc_Char)0x65,  /* [1307] */
    (xdc_Char)0x72,  /* [1308] */
    (xdc_Char)0x2e,  /* [1309] */
    (xdc_Char)0x0,  /* [1310] */
    (xdc_Char)0x41,  /* [1311] */
    (xdc_Char)0x5f,  /* [1312] */
    (xdc_Char)0x70,  /* [1313] */
    (xdc_Char)0x65,  /* [1314] */
    (xdc_Char)0x6e,  /* [1315] */
    (xdc_Char)0x64,  /* [1316] */
    (xdc_Char)0x54,  /* [1317] */
    (xdc_Char)0x61,  /* [1318] */
    (xdc_Char)0x73,  /* [1319] */
    (xdc_Char)0x6b,  /* [1320] */
    (xdc_Char)0x44,  /* [1321] */
    (xdc_Char)0x69,  /* [1322] */
    (xdc_Char)0x73,  /* [1323] */
    (xdc_Char)0x61,  /* [1324] */
    (xdc_Char)0x62,  /* [1325] */
    (xdc_Char)0x6c,  /* [1326] */
    (xdc_Char)0x65,  /* [1327] */
    (xdc_Char)0x64,  /* [1328] */
    (xdc_Char)0x3a,  /* [1329] */
    (xdc_Char)0x20,  /* [1330] */
    (xdc_Char)0x43,  /* [1331] */
    (xdc_Char)0x61,  /* [1332] */
    (xdc_Char)0x6e,  /* [1333] */
    (xdc_Char)0x6e,  /* [1334] */
    (xdc_Char)0x6f,  /* [1335] */
    (xdc_Char)0x74,  /* [1336] */
    (xdc_Char)0x20,  /* [1337] */
    (xdc_Char)0x63,  /* [1338] */
    (xdc_Char)0x61,  /* [1339] */
    (xdc_Char)0x6c,  /* [1340] */
    (xdc_Char)0x6c,  /* [1341] */
    (xdc_Char)0x20,  /* [1342] */
    (xdc_Char)0x53,  /* [1343] */
    (xdc_Char)0x65,  /* [1344] */
    (xdc_Char)0x6d,  /* [1345] */
    (xdc_Char)0x61,  /* [1346] */
    (xdc_Char)0x70,  /* [1347] */
    (xdc_Char)0x68,  /* [1348] */
    (xdc_Char)0x6f,  /* [1349] */
    (xdc_Char)0x72,  /* [1350] */
    (xdc_Char)0x65,  /* [1351] */
    (xdc_Char)0x5f,  /* [1352] */
    (xdc_Char)0x70,  /* [1353] */
    (xdc_Char)0x65,  /* [1354] */
    (xdc_Char)0x6e,  /* [1355] */
    (xdc_Char)0x64,  /* [1356] */
    (xdc_Char)0x28,  /* [1357] */
    (xdc_Char)0x29,  /* [1358] */
    (xdc_Char)0x20,  /* [1359] */
    (xdc_Char)0x77,  /* [1360] */
    (xdc_Char)0x68,  /* [1361] */
    (xdc_Char)0x69,  /* [1362] */
    (xdc_Char)0x6c,  /* [1363] */
    (xdc_Char)0x65,  /* [1364] */
    (xdc_Char)0x20,  /* [1365] */
    (xdc_Char)0x74,  /* [1366] */
    (xdc_Char)0x68,  /* [1367] */
    (xdc_Char)0x65,  /* [1368] */
    (xdc_Char)0x20,  /* [1369] */
    (xdc_Char)0x54,  /* [1370] */
    (xdc_Char)0x61,  /* [1371] */
    (xdc_Char)0x73,  /* [1372] */
    (xdc_Char)0x6b,  /* [1373] */
    (xdc_Char)0x20,  /* [1374] */
    (xdc_Char)0x6f,  /* [1375] */
    (xdc_Char)0x72,  /* [1376] */
    (xdc_Char)0x20,  /* [1377] */
    (xdc_Char)0x53,  /* [1378] */
    (xdc_Char)0x77,  /* [1379] */
    (xdc_Char)0x69,  /* [1380] */
    (xdc_Char)0x20,  /* [1381] */
    (xdc_Char)0x73,  /* [1382] */
    (xdc_Char)0x63,  /* [1383] */
    (xdc_Char)0x68,  /* [1384] */
    (xdc_Char)0x65,  /* [1385] */
    (xdc_Char)0x64,  /* [1386] */
    (xdc_Char)0x75,  /* [1387] */
    (xdc_Char)0x6c,  /* [1388] */
    (xdc_Char)0x65,  /* [1389] */
    (xdc_Char)0x72,  /* [1390] */
    (xdc_Char)0x20,  /* [1391] */
    (xdc_Char)0x69,  /* [1392] */
    (xdc_Char)0x73,  /* [1393] */
    (xdc_Char)0x20,  /* [1394] */
    (xdc_Char)0x64,  /* [1395] */
    (xdc_Char)0x69,  /* [1396] */
    (xdc_Char)0x73,  /* [1397] */
    (xdc_Char)0x61,  /* [1398] */
    (xdc_Char)0x62,  /* [1399] */
    (xdc_Char)0x6c,  /* [1400] */
    (xdc_Char)0x65,  /* [1401] */
    (xdc_Char)0x64,  /* [1402] */
    (xdc_Char)0x2e,  /* [1403] */
    (xdc_Char)0x0,  /* [1404] */
    (xdc_Char)0x41,  /* [1405] */
    (xdc_Char)0x5f,  /* [1406] */
    (xdc_Char)0x73,  /* [1407] */
    (xdc_Char)0x77,  /* [1408] */
    (xdc_Char)0x69,  /* [1409] */
    (xdc_Char)0x44,  /* [1410] */
    (xdc_Char)0x69,  /* [1411] */
    (xdc_Char)0x73,  /* [1412] */
    (xdc_Char)0x61,  /* [1413] */
    (xdc_Char)0x62,  /* [1414] */
    (xdc_Char)0x6c,  /* [1415] */
    (xdc_Char)0x65,  /* [1416] */
    (xdc_Char)0x64,  /* [1417] */
    (xdc_Char)0x3a,  /* [1418] */
    (xdc_Char)0x20,  /* [1419] */
    (xdc_Char)0x43,  /* [1420] */
    (xdc_Char)0x61,  /* [1421] */
    (xdc_Char)0x6e,  /* [1422] */
    (xdc_Char)0x6e,  /* [1423] */
    (xdc_Char)0x6f,  /* [1424] */
    (xdc_Char)0x74,  /* [1425] */
    (xdc_Char)0x20,  /* [1426] */
    (xdc_Char)0x63,  /* [1427] */
    (xdc_Char)0x72,  /* [1428] */
    (xdc_Char)0x65,  /* [1429] */
    (xdc_Char)0x61,  /* [1430] */
    (xdc_Char)0x74,  /* [1431] */
    (xdc_Char)0x65,  /* [1432] */
    (xdc_Char)0x20,  /* [1433] */
    (xdc_Char)0x61,  /* [1434] */
    (xdc_Char)0x20,  /* [1435] */
    (xdc_Char)0x53,  /* [1436] */
    (xdc_Char)0x77,  /* [1437] */
    (xdc_Char)0x69,  /* [1438] */
    (xdc_Char)0x20,  /* [1439] */
    (xdc_Char)0x77,  /* [1440] */
    (xdc_Char)0x68,  /* [1441] */
    (xdc_Char)0x65,  /* [1442] */
    (xdc_Char)0x6e,  /* [1443] */
    (xdc_Char)0x20,  /* [1444] */
    (xdc_Char)0x53,  /* [1445] */
    (xdc_Char)0x77,  /* [1446] */
    (xdc_Char)0x69,  /* [1447] */
    (xdc_Char)0x20,  /* [1448] */
    (xdc_Char)0x69,  /* [1449] */
    (xdc_Char)0x73,  /* [1450] */
    (xdc_Char)0x20,  /* [1451] */
    (xdc_Char)0x64,  /* [1452] */
    (xdc_Char)0x69,  /* [1453] */
    (xdc_Char)0x73,  /* [1454] */
    (xdc_Char)0x61,  /* [1455] */
    (xdc_Char)0x62,  /* [1456] */
    (xdc_Char)0x6c,  /* [1457] */
    (xdc_Char)0x65,  /* [1458] */
    (xdc_Char)0x64,  /* [1459] */
    (xdc_Char)0x2e,  /* [1460] */
    (xdc_Char)0x0,  /* [1461] */
    (xdc_Char)0x41,  /* [1462] */
    (xdc_Char)0x5f,  /* [1463] */
    (xdc_Char)0x62,  /* [1464] */
    (xdc_Char)0x61,  /* [1465] */
    (xdc_Char)0x64,  /* [1466] */
    (xdc_Char)0x50,  /* [1467] */
    (xdc_Char)0x72,  /* [1468] */
    (xdc_Char)0x69,  /* [1469] */
    (xdc_Char)0x6f,  /* [1470] */
    (xdc_Char)0x72,  /* [1471] */
    (xdc_Char)0x69,  /* [1472] */
    (xdc_Char)0x74,  /* [1473] */
    (xdc_Char)0x79,  /* [1474] */
    (xdc_Char)0x3a,  /* [1475] */
    (xdc_Char)0x20,  /* [1476] */
    (xdc_Char)0x41,  /* [1477] */
    (xdc_Char)0x6e,  /* [1478] */
    (xdc_Char)0x20,  /* [1479] */
    (xdc_Char)0x69,  /* [1480] */
    (xdc_Char)0x6e,  /* [1481] */
    (xdc_Char)0x76,  /* [1482] */
    (xdc_Char)0x61,  /* [1483] */
    (xdc_Char)0x6c,  /* [1484] */
    (xdc_Char)0x69,  /* [1485] */
    (xdc_Char)0x64,  /* [1486] */
    (xdc_Char)0x20,  /* [1487] */
    (xdc_Char)0x53,  /* [1488] */
    (xdc_Char)0x77,  /* [1489] */
    (xdc_Char)0x69,  /* [1490] */
    (xdc_Char)0x20,  /* [1491] */
    (xdc_Char)0x70,  /* [1492] */
    (xdc_Char)0x72,  /* [1493] */
    (xdc_Char)0x69,  /* [1494] */
    (xdc_Char)0x6f,  /* [1495] */
    (xdc_Char)0x72,  /* [1496] */
    (xdc_Char)0x69,  /* [1497] */
    (xdc_Char)0x74,  /* [1498] */
    (xdc_Char)0x79,  /* [1499] */
    (xdc_Char)0x20,  /* [1500] */
    (xdc_Char)0x77,  /* [1501] */
    (xdc_Char)0x61,  /* [1502] */
    (xdc_Char)0x73,  /* [1503] */
    (xdc_Char)0x20,  /* [1504] */
    (xdc_Char)0x75,  /* [1505] */
    (xdc_Char)0x73,  /* [1506] */
    (xdc_Char)0x65,  /* [1507] */
    (xdc_Char)0x64,  /* [1508] */
    (xdc_Char)0x2e,  /* [1509] */
    (xdc_Char)0x0,  /* [1510] */
    (xdc_Char)0x41,  /* [1511] */
    (xdc_Char)0x5f,  /* [1512] */
    (xdc_Char)0x62,  /* [1513] */
    (xdc_Char)0x61,  /* [1514] */
    (xdc_Char)0x64,  /* [1515] */
    (xdc_Char)0x54,  /* [1516] */
    (xdc_Char)0x68,  /* [1517] */
    (xdc_Char)0x72,  /* [1518] */
    (xdc_Char)0x65,  /* [1519] */
    (xdc_Char)0x61,  /* [1520] */
    (xdc_Char)0x64,  /* [1521] */
    (xdc_Char)0x54,  /* [1522] */
    (xdc_Char)0x79,  /* [1523] */
    (xdc_Char)0x70,  /* [1524] */
    (xdc_Char)0x65,  /* [1525] */
    (xdc_Char)0x3a,  /* [1526] */
    (xdc_Char)0x20,  /* [1527] */
    (xdc_Char)0x43,  /* [1528] */
    (xdc_Char)0x61,  /* [1529] */
    (xdc_Char)0x6e,  /* [1530] */
    (xdc_Char)0x6e,  /* [1531] */
    (xdc_Char)0x6f,  /* [1532] */
    (xdc_Char)0x74,  /* [1533] */
    (xdc_Char)0x20,  /* [1534] */
    (xdc_Char)0x63,  /* [1535] */
    (xdc_Char)0x72,  /* [1536] */
    (xdc_Char)0x65,  /* [1537] */
    (xdc_Char)0x61,  /* [1538] */
    (xdc_Char)0x74,  /* [1539] */
    (xdc_Char)0x65,  /* [1540] */
    (xdc_Char)0x2f,  /* [1541] */
    (xdc_Char)0x64,  /* [1542] */
    (xdc_Char)0x65,  /* [1543] */
    (xdc_Char)0x6c,  /* [1544] */
    (xdc_Char)0x65,  /* [1545] */
    (xdc_Char)0x74,  /* [1546] */
    (xdc_Char)0x65,  /* [1547] */
    (xdc_Char)0x20,  /* [1548] */
    (xdc_Char)0x61,  /* [1549] */
    (xdc_Char)0x20,  /* [1550] */
    (xdc_Char)0x74,  /* [1551] */
    (xdc_Char)0x61,  /* [1552] */
    (xdc_Char)0x73,  /* [1553] */
    (xdc_Char)0x6b,  /* [1554] */
    (xdc_Char)0x20,  /* [1555] */
    (xdc_Char)0x66,  /* [1556] */
    (xdc_Char)0x72,  /* [1557] */
    (xdc_Char)0x6f,  /* [1558] */
    (xdc_Char)0x6d,  /* [1559] */
    (xdc_Char)0x20,  /* [1560] */
    (xdc_Char)0x48,  /* [1561] */
    (xdc_Char)0x77,  /* [1562] */
    (xdc_Char)0x69,  /* [1563] */
    (xdc_Char)0x20,  /* [1564] */
    (xdc_Char)0x6f,  /* [1565] */
    (xdc_Char)0x72,  /* [1566] */
    (xdc_Char)0x20,  /* [1567] */
    (xdc_Char)0x53,  /* [1568] */
    (xdc_Char)0x77,  /* [1569] */
    (xdc_Char)0x69,  /* [1570] */
    (xdc_Char)0x20,  /* [1571] */
    (xdc_Char)0x74,  /* [1572] */
    (xdc_Char)0x68,  /* [1573] */
    (xdc_Char)0x72,  /* [1574] */
    (xdc_Char)0x65,  /* [1575] */
    (xdc_Char)0x61,  /* [1576] */
    (xdc_Char)0x64,  /* [1577] */
    (xdc_Char)0x2e,  /* [1578] */
    (xdc_Char)0x0,  /* [1579] */
    (xdc_Char)0x41,  /* [1580] */
    (xdc_Char)0x5f,  /* [1581] */
    (xdc_Char)0x62,  /* [1582] */
    (xdc_Char)0x61,  /* [1583] */
    (xdc_Char)0x64,  /* [1584] */
    (xdc_Char)0x54,  /* [1585] */
    (xdc_Char)0x61,  /* [1586] */
    (xdc_Char)0x73,  /* [1587] */
    (xdc_Char)0x6b,  /* [1588] */
    (xdc_Char)0x53,  /* [1589] */
    (xdc_Char)0x74,  /* [1590] */
    (xdc_Char)0x61,  /* [1591] */
    (xdc_Char)0x74,  /* [1592] */
    (xdc_Char)0x65,  /* [1593] */
    (xdc_Char)0x3a,  /* [1594] */
    (xdc_Char)0x20,  /* [1595] */
    (xdc_Char)0x43,  /* [1596] */
    (xdc_Char)0x61,  /* [1597] */
    (xdc_Char)0x6e,  /* [1598] */
    (xdc_Char)0x27,  /* [1599] */
    (xdc_Char)0x74,  /* [1600] */
    (xdc_Char)0x20,  /* [1601] */
    (xdc_Char)0x64,  /* [1602] */
    (xdc_Char)0x65,  /* [1603] */
    (xdc_Char)0x6c,  /* [1604] */
    (xdc_Char)0x65,  /* [1605] */
    (xdc_Char)0x74,  /* [1606] */
    (xdc_Char)0x65,  /* [1607] */
    (xdc_Char)0x20,  /* [1608] */
    (xdc_Char)0x61,  /* [1609] */
    (xdc_Char)0x20,  /* [1610] */
    (xdc_Char)0x74,  /* [1611] */
    (xdc_Char)0x61,  /* [1612] */
    (xdc_Char)0x73,  /* [1613] */
    (xdc_Char)0x6b,  /* [1614] */
    (xdc_Char)0x20,  /* [1615] */
    (xdc_Char)0x69,  /* [1616] */
    (xdc_Char)0x6e,  /* [1617] */
    (xdc_Char)0x20,  /* [1618] */
    (xdc_Char)0x52,  /* [1619] */
    (xdc_Char)0x55,  /* [1620] */
    (xdc_Char)0x4e,  /* [1621] */
    (xdc_Char)0x4e,  /* [1622] */
    (xdc_Char)0x49,  /* [1623] */
    (xdc_Char)0x4e,  /* [1624] */
    (xdc_Char)0x47,  /* [1625] */
    (xdc_Char)0x20,  /* [1626] */
    (xdc_Char)0x73,  /* [1627] */
    (xdc_Char)0x74,  /* [1628] */
    (xdc_Char)0x61,  /* [1629] */
    (xdc_Char)0x74,  /* [1630] */
    (xdc_Char)0x65,  /* [1631] */
    (xdc_Char)0x2e,  /* [1632] */
    (xdc_Char)0x0,  /* [1633] */
    (xdc_Char)0x41,  /* [1634] */
    (xdc_Char)0x5f,  /* [1635] */
    (xdc_Char)0x6e,  /* [1636] */
    (xdc_Char)0x6f,  /* [1637] */
    (xdc_Char)0x50,  /* [1638] */
    (xdc_Char)0x65,  /* [1639] */
    (xdc_Char)0x6e,  /* [1640] */
    (xdc_Char)0x64,  /* [1641] */
    (xdc_Char)0x45,  /* [1642] */
    (xdc_Char)0x6c,  /* [1643] */
    (xdc_Char)0x65,  /* [1644] */
    (xdc_Char)0x6d,  /* [1645] */
    (xdc_Char)0x3a,  /* [1646] */
    (xdc_Char)0x20,  /* [1647] */
    (xdc_Char)0x4e,  /* [1648] */
    (xdc_Char)0x6f,  /* [1649] */
    (xdc_Char)0x74,  /* [1650] */
    (xdc_Char)0x20,  /* [1651] */
    (xdc_Char)0x65,  /* [1652] */
    (xdc_Char)0x6e,  /* [1653] */
    (xdc_Char)0x6f,  /* [1654] */
    (xdc_Char)0x75,  /* [1655] */
    (xdc_Char)0x67,  /* [1656] */
    (xdc_Char)0x68,  /* [1657] */
    (xdc_Char)0x20,  /* [1658] */
    (xdc_Char)0x69,  /* [1659] */
    (xdc_Char)0x6e,  /* [1660] */
    (xdc_Char)0x66,  /* [1661] */
    (xdc_Char)0x6f,  /* [1662] */
    (xdc_Char)0x20,  /* [1663] */
    (xdc_Char)0x74,  /* [1664] */
    (xdc_Char)0x6f,  /* [1665] */
    (xdc_Char)0x20,  /* [1666] */
    (xdc_Char)0x64,  /* [1667] */
    (xdc_Char)0x65,  /* [1668] */
    (xdc_Char)0x6c,  /* [1669] */
    (xdc_Char)0x65,  /* [1670] */
    (xdc_Char)0x74,  /* [1671] */
    (xdc_Char)0x65,  /* [1672] */
    (xdc_Char)0x20,  /* [1673] */
    (xdc_Char)0x42,  /* [1674] */
    (xdc_Char)0x4c,  /* [1675] */
    (xdc_Char)0x4f,  /* [1676] */
    (xdc_Char)0x43,  /* [1677] */
    (xdc_Char)0x4b,  /* [1678] */
    (xdc_Char)0x45,  /* [1679] */
    (xdc_Char)0x44,  /* [1680] */
    (xdc_Char)0x20,  /* [1681] */
    (xdc_Char)0x74,  /* [1682] */
    (xdc_Char)0x61,  /* [1683] */
    (xdc_Char)0x73,  /* [1684] */
    (xdc_Char)0x6b,  /* [1685] */
    (xdc_Char)0x2e,  /* [1686] */
    (xdc_Char)0x0,  /* [1687] */
    (xdc_Char)0x41,  /* [1688] */
    (xdc_Char)0x5f,  /* [1689] */
    (xdc_Char)0x74,  /* [1690] */
    (xdc_Char)0x61,  /* [1691] */
    (xdc_Char)0x73,  /* [1692] */
    (xdc_Char)0x6b,  /* [1693] */
    (xdc_Char)0x44,  /* [1694] */
    (xdc_Char)0x69,  /* [1695] */
    (xdc_Char)0x73,  /* [1696] */
    (xdc_Char)0x61,  /* [1697] */
    (xdc_Char)0x62,  /* [1698] */
    (xdc_Char)0x6c,  /* [1699] */
    (xdc_Char)0x65,  /* [1700] */
    (xdc_Char)0x64,  /* [1701] */
    (xdc_Char)0x3a,  /* [1702] */
    (xdc_Char)0x20,  /* [1703] */
    (xdc_Char)0x43,  /* [1704] */
    (xdc_Char)0x61,  /* [1705] */
    (xdc_Char)0x6e,  /* [1706] */
    (xdc_Char)0x6e,  /* [1707] */
    (xdc_Char)0x6f,  /* [1708] */
    (xdc_Char)0x74,  /* [1709] */
    (xdc_Char)0x20,  /* [1710] */
    (xdc_Char)0x63,  /* [1711] */
    (xdc_Char)0x72,  /* [1712] */
    (xdc_Char)0x65,  /* [1713] */
    (xdc_Char)0x61,  /* [1714] */
    (xdc_Char)0x74,  /* [1715] */
    (xdc_Char)0x65,  /* [1716] */
    (xdc_Char)0x20,  /* [1717] */
    (xdc_Char)0x61,  /* [1718] */
    (xdc_Char)0x20,  /* [1719] */
    (xdc_Char)0x74,  /* [1720] */
    (xdc_Char)0x61,  /* [1721] */
    (xdc_Char)0x73,  /* [1722] */
    (xdc_Char)0x6b,  /* [1723] */
    (xdc_Char)0x20,  /* [1724] */
    (xdc_Char)0x77,  /* [1725] */
    (xdc_Char)0x68,  /* [1726] */
    (xdc_Char)0x65,  /* [1727] */
    (xdc_Char)0x6e,  /* [1728] */
    (xdc_Char)0x20,  /* [1729] */
    (xdc_Char)0x74,  /* [1730] */
    (xdc_Char)0x61,  /* [1731] */
    (xdc_Char)0x73,  /* [1732] */
    (xdc_Char)0x6b,  /* [1733] */
    (xdc_Char)0x69,  /* [1734] */
    (xdc_Char)0x6e,  /* [1735] */
    (xdc_Char)0x67,  /* [1736] */
    (xdc_Char)0x20,  /* [1737] */
    (xdc_Char)0x69,  /* [1738] */
    (xdc_Char)0x73,  /* [1739] */
    (xdc_Char)0x20,  /* [1740] */
    (xdc_Char)0x64,  /* [1741] */
    (xdc_Char)0x69,  /* [1742] */
    (xdc_Char)0x73,  /* [1743] */
    (xdc_Char)0x61,  /* [1744] */
    (xdc_Char)0x62,  /* [1745] */
    (xdc_Char)0x6c,  /* [1746] */
    (xdc_Char)0x65,  /* [1747] */
    (xdc_Char)0x64,  /* [1748] */
    (xdc_Char)0x2e,  /* [1749] */
    (xdc_Char)0x0,  /* [1750] */
    (xdc_Char)0x41,  /* [1751] */
    (xdc_Char)0x5f,  /* [1752] */
    (xdc_Char)0x62,  /* [1753] */
    (xdc_Char)0x61,  /* [1754] */
    (xdc_Char)0x64,  /* [1755] */
    (xdc_Char)0x50,  /* [1756] */
    (xdc_Char)0x72,  /* [1757] */
    (xdc_Char)0x69,  /* [1758] */
    (xdc_Char)0x6f,  /* [1759] */
    (xdc_Char)0x72,  /* [1760] */
    (xdc_Char)0x69,  /* [1761] */
    (xdc_Char)0x74,  /* [1762] */
    (xdc_Char)0x79,  /* [1763] */
    (xdc_Char)0x3a,  /* [1764] */
    (xdc_Char)0x20,  /* [1765] */
    (xdc_Char)0x41,  /* [1766] */
    (xdc_Char)0x6e,  /* [1767] */
    (xdc_Char)0x20,  /* [1768] */
    (xdc_Char)0x69,  /* [1769] */
    (xdc_Char)0x6e,  /* [1770] */
    (xdc_Char)0x76,  /* [1771] */
    (xdc_Char)0x61,  /* [1772] */
    (xdc_Char)0x6c,  /* [1773] */
    (xdc_Char)0x69,  /* [1774] */
    (xdc_Char)0x64,  /* [1775] */
    (xdc_Char)0x20,  /* [1776] */
    (xdc_Char)0x74,  /* [1777] */
    (xdc_Char)0x61,  /* [1778] */
    (xdc_Char)0x73,  /* [1779] */
    (xdc_Char)0x6b,  /* [1780] */
    (xdc_Char)0x20,  /* [1781] */
    (xdc_Char)0x70,  /* [1782] */
    (xdc_Char)0x72,  /* [1783] */
    (xdc_Char)0x69,  /* [1784] */
    (xdc_Char)0x6f,  /* [1785] */
    (xdc_Char)0x72,  /* [1786] */
    (xdc_Char)0x69,  /* [1787] */
    (xdc_Char)0x74,  /* [1788] */
    (xdc_Char)0x79,  /* [1789] */
    (xdc_Char)0x20,  /* [1790] */
    (xdc_Char)0x77,  /* [1791] */
    (xdc_Char)0x61,  /* [1792] */
    (xdc_Char)0x73,  /* [1793] */
    (xdc_Char)0x20,  /* [1794] */
    (xdc_Char)0x75,  /* [1795] */
    (xdc_Char)0x73,  /* [1796] */
    (xdc_Char)0x65,  /* [1797] */
    (xdc_Char)0x64,  /* [1798] */
    (xdc_Char)0x2e,  /* [1799] */
    (xdc_Char)0x0,  /* [1800] */
    (xdc_Char)0x41,  /* [1801] */
    (xdc_Char)0x5f,  /* [1802] */
    (xdc_Char)0x62,  /* [1803] */
    (xdc_Char)0x61,  /* [1804] */
    (xdc_Char)0x64,  /* [1805] */
    (xdc_Char)0x54,  /* [1806] */
    (xdc_Char)0x69,  /* [1807] */
    (xdc_Char)0x6d,  /* [1808] */
    (xdc_Char)0x65,  /* [1809] */
    (xdc_Char)0x6f,  /* [1810] */
    (xdc_Char)0x75,  /* [1811] */
    (xdc_Char)0x74,  /* [1812] */
    (xdc_Char)0x3a,  /* [1813] */
    (xdc_Char)0x20,  /* [1814] */
    (xdc_Char)0x43,  /* [1815] */
    (xdc_Char)0x61,  /* [1816] */
    (xdc_Char)0x6e,  /* [1817] */
    (xdc_Char)0x27,  /* [1818] */
    (xdc_Char)0x74,  /* [1819] */
    (xdc_Char)0x20,  /* [1820] */
    (xdc_Char)0x73,  /* [1821] */
    (xdc_Char)0x6c,  /* [1822] */
    (xdc_Char)0x65,  /* [1823] */
    (xdc_Char)0x65,  /* [1824] */
    (xdc_Char)0x70,  /* [1825] */
    (xdc_Char)0x20,  /* [1826] */
    (xdc_Char)0x46,  /* [1827] */
    (xdc_Char)0x4f,  /* [1828] */
    (xdc_Char)0x52,  /* [1829] */
    (xdc_Char)0x45,  /* [1830] */
    (xdc_Char)0x56,  /* [1831] */
    (xdc_Char)0x45,  /* [1832] */
    (xdc_Char)0x52,  /* [1833] */
    (xdc_Char)0x2e,  /* [1834] */
    (xdc_Char)0x0,  /* [1835] */
    (xdc_Char)0x41,  /* [1836] */
    (xdc_Char)0x5f,  /* [1837] */
    (xdc_Char)0x62,  /* [1838] */
    (xdc_Char)0x61,  /* [1839] */
    (xdc_Char)0x64,  /* [1840] */
    (xdc_Char)0x41,  /* [1841] */
    (xdc_Char)0x66,  /* [1842] */
    (xdc_Char)0x66,  /* [1843] */
    (xdc_Char)0x69,  /* [1844] */
    (xdc_Char)0x6e,  /* [1845] */
    (xdc_Char)0x69,  /* [1846] */
    (xdc_Char)0x74,  /* [1847] */
    (xdc_Char)0x79,  /* [1848] */
    (xdc_Char)0x3a,  /* [1849] */
    (xdc_Char)0x20,  /* [1850] */
    (xdc_Char)0x49,  /* [1851] */
    (xdc_Char)0x6e,  /* [1852] */
    (xdc_Char)0x76,  /* [1853] */
    (xdc_Char)0x61,  /* [1854] */
    (xdc_Char)0x6c,  /* [1855] */
    (xdc_Char)0x69,  /* [1856] */
    (xdc_Char)0x64,  /* [1857] */
    (xdc_Char)0x20,  /* [1858] */
    (xdc_Char)0x61,  /* [1859] */
    (xdc_Char)0x66,  /* [1860] */
    (xdc_Char)0x66,  /* [1861] */
    (xdc_Char)0x69,  /* [1862] */
    (xdc_Char)0x6e,  /* [1863] */
    (xdc_Char)0x69,  /* [1864] */
    (xdc_Char)0x74,  /* [1865] */
    (xdc_Char)0x79,  /* [1866] */
    (xdc_Char)0x2e,  /* [1867] */
    (xdc_Char)0x0,  /* [1868] */
    (xdc_Char)0x41,  /* [1869] */
    (xdc_Char)0x5f,  /* [1870] */
    (xdc_Char)0x73,  /* [1871] */
    (xdc_Char)0x6c,  /* [1872] */
    (xdc_Char)0x65,  /* [1873] */
    (xdc_Char)0x65,  /* [1874] */
    (xdc_Char)0x70,  /* [1875] */
    (xdc_Char)0x54,  /* [1876] */
    (xdc_Char)0x61,  /* [1877] */
    (xdc_Char)0x73,  /* [1878] */
    (xdc_Char)0x6b,  /* [1879] */
    (xdc_Char)0x44,  /* [1880] */
    (xdc_Char)0x69,  /* [1881] */
    (xdc_Char)0x73,  /* [1882] */
    (xdc_Char)0x61,  /* [1883] */
    (xdc_Char)0x62,  /* [1884] */
    (xdc_Char)0x6c,  /* [1885] */
    (xdc_Char)0x65,  /* [1886] */
    (xdc_Char)0x64,  /* [1887] */
    (xdc_Char)0x3a,  /* [1888] */
    (xdc_Char)0x20,  /* [1889] */
    (xdc_Char)0x43,  /* [1890] */
    (xdc_Char)0x61,  /* [1891] */
    (xdc_Char)0x6e,  /* [1892] */
    (xdc_Char)0x6e,  /* [1893] */
    (xdc_Char)0x6f,  /* [1894] */
    (xdc_Char)0x74,  /* [1895] */
    (xdc_Char)0x20,  /* [1896] */
    (xdc_Char)0x63,  /* [1897] */
    (xdc_Char)0x61,  /* [1898] */
    (xdc_Char)0x6c,  /* [1899] */
    (xdc_Char)0x6c,  /* [1900] */
    (xdc_Char)0x20,  /* [1901] */
    (xdc_Char)0x54,  /* [1902] */
    (xdc_Char)0x61,  /* [1903] */
    (xdc_Char)0x73,  /* [1904] */
    (xdc_Char)0x6b,  /* [1905] */
    (xdc_Char)0x5f,  /* [1906] */
    (xdc_Char)0x73,  /* [1907] */
    (xdc_Char)0x6c,  /* [1908] */
    (xdc_Char)0x65,  /* [1909] */
    (xdc_Char)0x65,  /* [1910] */
    (xdc_Char)0x70,  /* [1911] */
    (xdc_Char)0x28,  /* [1912] */
    (xdc_Char)0x29,  /* [1913] */
    (xdc_Char)0x20,  /* [1914] */
    (xdc_Char)0x77,  /* [1915] */
    (xdc_Char)0x68,  /* [1916] */
    (xdc_Char)0x69,  /* [1917] */
    (xdc_Char)0x6c,  /* [1918] */
    (xdc_Char)0x65,  /* [1919] */
    (xdc_Char)0x20,  /* [1920] */
    (xdc_Char)0x74,  /* [1921] */
    (xdc_Char)0x68,  /* [1922] */
    (xdc_Char)0x65,  /* [1923] */
    (xdc_Char)0x20,  /* [1924] */
    (xdc_Char)0x54,  /* [1925] */
    (xdc_Char)0x61,  /* [1926] */
    (xdc_Char)0x73,  /* [1927] */
    (xdc_Char)0x6b,  /* [1928] */
    (xdc_Char)0x20,  /* [1929] */
    (xdc_Char)0x73,  /* [1930] */
    (xdc_Char)0x63,  /* [1931] */
    (xdc_Char)0x68,  /* [1932] */
    (xdc_Char)0x65,  /* [1933] */
    (xdc_Char)0x64,  /* [1934] */
    (xdc_Char)0x75,  /* [1935] */
    (xdc_Char)0x6c,  /* [1936] */
    (xdc_Char)0x65,  /* [1937] */
    (xdc_Char)0x72,  /* [1938] */
    (xdc_Char)0x20,  /* [1939] */
    (xdc_Char)0x69,  /* [1940] */
    (xdc_Char)0x73,  /* [1941] */
    (xdc_Char)0x20,  /* [1942] */
    (xdc_Char)0x64,  /* [1943] */
    (xdc_Char)0x69,  /* [1944] */
    (xdc_Char)0x73,  /* [1945] */
    (xdc_Char)0x61,  /* [1946] */
    (xdc_Char)0x62,  /* [1947] */
    (xdc_Char)0x6c,  /* [1948] */
    (xdc_Char)0x65,  /* [1949] */
    (xdc_Char)0x64,  /* [1950] */
    (xdc_Char)0x2e,  /* [1951] */
    (xdc_Char)0x0,  /* [1952] */
    (xdc_Char)0x41,  /* [1953] */
    (xdc_Char)0x5f,  /* [1954] */
    (xdc_Char)0x69,  /* [1955] */
    (xdc_Char)0x6e,  /* [1956] */
    (xdc_Char)0x76,  /* [1957] */
    (xdc_Char)0x61,  /* [1958] */
    (xdc_Char)0x6c,  /* [1959] */
    (xdc_Char)0x69,  /* [1960] */
    (xdc_Char)0x64,  /* [1961] */
    (xdc_Char)0x43,  /* [1962] */
    (xdc_Char)0x6f,  /* [1963] */
    (xdc_Char)0x72,  /* [1964] */
    (xdc_Char)0x65,  /* [1965] */
    (xdc_Char)0x49,  /* [1966] */
    (xdc_Char)0x64,  /* [1967] */
    (xdc_Char)0x3a,  /* [1968] */
    (xdc_Char)0x20,  /* [1969] */
    (xdc_Char)0x43,  /* [1970] */
    (xdc_Char)0x61,  /* [1971] */
    (xdc_Char)0x6e,  /* [1972] */
    (xdc_Char)0x6e,  /* [1973] */
    (xdc_Char)0x6f,  /* [1974] */
    (xdc_Char)0x74,  /* [1975] */
    (xdc_Char)0x20,  /* [1976] */
    (xdc_Char)0x70,  /* [1977] */
    (xdc_Char)0x61,  /* [1978] */
    (xdc_Char)0x73,  /* [1979] */
    (xdc_Char)0x73,  /* [1980] */
    (xdc_Char)0x20,  /* [1981] */
    (xdc_Char)0x61,  /* [1982] */
    (xdc_Char)0x20,  /* [1983] */
    (xdc_Char)0x6e,  /* [1984] */
    (xdc_Char)0x6f,  /* [1985] */
    (xdc_Char)0x6e,  /* [1986] */
    (xdc_Char)0x2d,  /* [1987] */
    (xdc_Char)0x7a,  /* [1988] */
    (xdc_Char)0x65,  /* [1989] */
    (xdc_Char)0x72,  /* [1990] */
    (xdc_Char)0x6f,  /* [1991] */
    (xdc_Char)0x20,  /* [1992] */
    (xdc_Char)0x43,  /* [1993] */
    (xdc_Char)0x6f,  /* [1994] */
    (xdc_Char)0x72,  /* [1995] */
    (xdc_Char)0x65,  /* [1996] */
    (xdc_Char)0x49,  /* [1997] */
    (xdc_Char)0x64,  /* [1998] */
    (xdc_Char)0x20,  /* [1999] */
    (xdc_Char)0x69,  /* [2000] */
    (xdc_Char)0x6e,  /* [2001] */
    (xdc_Char)0x20,  /* [2002] */
    (xdc_Char)0x61,  /* [2003] */
    (xdc_Char)0x20,  /* [2004] */
    (xdc_Char)0x6e,  /* [2005] */
    (xdc_Char)0x6f,  /* [2006] */
    (xdc_Char)0x6e,  /* [2007] */
    (xdc_Char)0x2d,  /* [2008] */
    (xdc_Char)0x53,  /* [2009] */
    (xdc_Char)0x4d,  /* [2010] */
    (xdc_Char)0x50,  /* [2011] */
    (xdc_Char)0x20,  /* [2012] */
    (xdc_Char)0x61,  /* [2013] */
    (xdc_Char)0x70,  /* [2014] */
    (xdc_Char)0x70,  /* [2015] */
    (xdc_Char)0x6c,  /* [2016] */
    (xdc_Char)0x69,  /* [2017] */
    (xdc_Char)0x63,  /* [2018] */
    (xdc_Char)0x61,  /* [2019] */
    (xdc_Char)0x74,  /* [2020] */
    (xdc_Char)0x69,  /* [2021] */
    (xdc_Char)0x6f,  /* [2022] */
    (xdc_Char)0x6e,  /* [2023] */
    (xdc_Char)0x2e,  /* [2024] */
    (xdc_Char)0x0,  /* [2025] */
    (xdc_Char)0x41,  /* [2026] */
    (xdc_Char)0x5f,  /* [2027] */
    (xdc_Char)0x62,  /* [2028] */
    (xdc_Char)0x61,  /* [2029] */
    (xdc_Char)0x64,  /* [2030] */
    (xdc_Char)0x43,  /* [2031] */
    (xdc_Char)0x6f,  /* [2032] */
    (xdc_Char)0x6e,  /* [2033] */
    (xdc_Char)0x74,  /* [2034] */
    (xdc_Char)0x65,  /* [2035] */
    (xdc_Char)0x78,  /* [2036] */
    (xdc_Char)0x74,  /* [2037] */
    (xdc_Char)0x3a,  /* [2038] */
    (xdc_Char)0x20,  /* [2039] */
    (xdc_Char)0x62,  /* [2040] */
    (xdc_Char)0x61,  /* [2041] */
    (xdc_Char)0x64,  /* [2042] */
    (xdc_Char)0x20,  /* [2043] */
    (xdc_Char)0x63,  /* [2044] */
    (xdc_Char)0x61,  /* [2045] */
    (xdc_Char)0x6c,  /* [2046] */
    (xdc_Char)0x6c,  /* [2047] */
    (xdc_Char)0x69,  /* [2048] */
    (xdc_Char)0x6e,  /* [2049] */
    (xdc_Char)0x67,  /* [2050] */
    (xdc_Char)0x20,  /* [2051] */
    (xdc_Char)0x63,  /* [2052] */
    (xdc_Char)0x6f,  /* [2053] */
    (xdc_Char)0x6e,  /* [2054] */
    (xdc_Char)0x74,  /* [2055] */
    (xdc_Char)0x65,  /* [2056] */
    (xdc_Char)0x78,  /* [2057] */
    (xdc_Char)0x74,  /* [2058] */
    (xdc_Char)0x2e,  /* [2059] */
    (xdc_Char)0x20,  /* [2060] */
    (xdc_Char)0x4d,  /* [2061] */
    (xdc_Char)0x61,  /* [2062] */
    (xdc_Char)0x79,  /* [2063] */
    (xdc_Char)0x20,  /* [2064] */
    (xdc_Char)0x6e,  /* [2065] */
    (xdc_Char)0x6f,  /* [2066] */
    (xdc_Char)0x74,  /* [2067] */
    (xdc_Char)0x20,  /* [2068] */
    (xdc_Char)0x62,  /* [2069] */
    (xdc_Char)0x65,  /* [2070] */
    (xdc_Char)0x20,  /* [2071] */
    (xdc_Char)0x65,  /* [2072] */
    (xdc_Char)0x6e,  /* [2073] */
    (xdc_Char)0x74,  /* [2074] */
    (xdc_Char)0x65,  /* [2075] */
    (xdc_Char)0x72,  /* [2076] */
    (xdc_Char)0x65,  /* [2077] */
    (xdc_Char)0x64,  /* [2078] */
    (xdc_Char)0x20,  /* [2079] */
    (xdc_Char)0x66,  /* [2080] */
    (xdc_Char)0x72,  /* [2081] */
    (xdc_Char)0x6f,  /* [2082] */
    (xdc_Char)0x6d,  /* [2083] */
    (xdc_Char)0x20,  /* [2084] */
    (xdc_Char)0x61,  /* [2085] */
    (xdc_Char)0x20,  /* [2086] */
    (xdc_Char)0x68,  /* [2087] */
    (xdc_Char)0x61,  /* [2088] */
    (xdc_Char)0x72,  /* [2089] */
    (xdc_Char)0x64,  /* [2090] */
    (xdc_Char)0x77,  /* [2091] */
    (xdc_Char)0x61,  /* [2092] */
    (xdc_Char)0x72,  /* [2093] */
    (xdc_Char)0x65,  /* [2094] */
    (xdc_Char)0x20,  /* [2095] */
    (xdc_Char)0x69,  /* [2096] */
    (xdc_Char)0x6e,  /* [2097] */
    (xdc_Char)0x74,  /* [2098] */
    (xdc_Char)0x65,  /* [2099] */
    (xdc_Char)0x72,  /* [2100] */
    (xdc_Char)0x72,  /* [2101] */
    (xdc_Char)0x75,  /* [2102] */
    (xdc_Char)0x70,  /* [2103] */
    (xdc_Char)0x74,  /* [2104] */
    (xdc_Char)0x20,  /* [2105] */
    (xdc_Char)0x74,  /* [2106] */
    (xdc_Char)0x68,  /* [2107] */
    (xdc_Char)0x72,  /* [2108] */
    (xdc_Char)0x65,  /* [2109] */
    (xdc_Char)0x61,  /* [2110] */
    (xdc_Char)0x64,  /* [2111] */
    (xdc_Char)0x2e,  /* [2112] */
    (xdc_Char)0x0,  /* [2113] */
    (xdc_Char)0x41,  /* [2114] */
    (xdc_Char)0x5f,  /* [2115] */
    (xdc_Char)0x62,  /* [2116] */
    (xdc_Char)0x61,  /* [2117] */
    (xdc_Char)0x64,  /* [2118] */
    (xdc_Char)0x43,  /* [2119] */
    (xdc_Char)0x6f,  /* [2120] */
    (xdc_Char)0x6e,  /* [2121] */
    (xdc_Char)0x74,  /* [2122] */
    (xdc_Char)0x65,  /* [2123] */
    (xdc_Char)0x78,  /* [2124] */
    (xdc_Char)0x74,  /* [2125] */
    (xdc_Char)0x3a,  /* [2126] */
    (xdc_Char)0x20,  /* [2127] */
    (xdc_Char)0x62,  /* [2128] */
    (xdc_Char)0x61,  /* [2129] */
    (xdc_Char)0x64,  /* [2130] */
    (xdc_Char)0x20,  /* [2131] */
    (xdc_Char)0x63,  /* [2132] */
    (xdc_Char)0x61,  /* [2133] */
    (xdc_Char)0x6c,  /* [2134] */
    (xdc_Char)0x6c,  /* [2135] */
    (xdc_Char)0x69,  /* [2136] */
    (xdc_Char)0x6e,  /* [2137] */
    (xdc_Char)0x67,  /* [2138] */
    (xdc_Char)0x20,  /* [2139] */
    (xdc_Char)0x63,  /* [2140] */
    (xdc_Char)0x6f,  /* [2141] */
    (xdc_Char)0x6e,  /* [2142] */
    (xdc_Char)0x74,  /* [2143] */
    (xdc_Char)0x65,  /* [2144] */
    (xdc_Char)0x78,  /* [2145] */
    (xdc_Char)0x74,  /* [2146] */
    (xdc_Char)0x2e,  /* [2147] */
    (xdc_Char)0x20,  /* [2148] */
    (xdc_Char)0x4d,  /* [2149] */
    (xdc_Char)0x61,  /* [2150] */
    (xdc_Char)0x79,  /* [2151] */
    (xdc_Char)0x20,  /* [2152] */
    (xdc_Char)0x6e,  /* [2153] */
    (xdc_Char)0x6f,  /* [2154] */
    (xdc_Char)0x74,  /* [2155] */
    (xdc_Char)0x20,  /* [2156] */
    (xdc_Char)0x62,  /* [2157] */
    (xdc_Char)0x65,  /* [2158] */
    (xdc_Char)0x20,  /* [2159] */
    (xdc_Char)0x65,  /* [2160] */
    (xdc_Char)0x6e,  /* [2161] */
    (xdc_Char)0x74,  /* [2162] */
    (xdc_Char)0x65,  /* [2163] */
    (xdc_Char)0x72,  /* [2164] */
    (xdc_Char)0x65,  /* [2165] */
    (xdc_Char)0x64,  /* [2166] */
    (xdc_Char)0x20,  /* [2167] */
    (xdc_Char)0x66,  /* [2168] */
    (xdc_Char)0x72,  /* [2169] */
    (xdc_Char)0x6f,  /* [2170] */
    (xdc_Char)0x6d,  /* [2171] */
    (xdc_Char)0x20,  /* [2172] */
    (xdc_Char)0x61,  /* [2173] */
    (xdc_Char)0x20,  /* [2174] */
    (xdc_Char)0x73,  /* [2175] */
    (xdc_Char)0x6f,  /* [2176] */
    (xdc_Char)0x66,  /* [2177] */
    (xdc_Char)0x74,  /* [2178] */
    (xdc_Char)0x77,  /* [2179] */
    (xdc_Char)0x61,  /* [2180] */
    (xdc_Char)0x72,  /* [2181] */
    (xdc_Char)0x65,  /* [2182] */
    (xdc_Char)0x20,  /* [2183] */
    (xdc_Char)0x6f,  /* [2184] */
    (xdc_Char)0x72,  /* [2185] */
    (xdc_Char)0x20,  /* [2186] */
    (xdc_Char)0x68,  /* [2187] */
    (xdc_Char)0x61,  /* [2188] */
    (xdc_Char)0x72,  /* [2189] */
    (xdc_Char)0x64,  /* [2190] */
    (xdc_Char)0x77,  /* [2191] */
    (xdc_Char)0x61,  /* [2192] */
    (xdc_Char)0x72,  /* [2193] */
    (xdc_Char)0x65,  /* [2194] */
    (xdc_Char)0x20,  /* [2195] */
    (xdc_Char)0x69,  /* [2196] */
    (xdc_Char)0x6e,  /* [2197] */
    (xdc_Char)0x74,  /* [2198] */
    (xdc_Char)0x65,  /* [2199] */
    (xdc_Char)0x72,  /* [2200] */
    (xdc_Char)0x72,  /* [2201] */
    (xdc_Char)0x75,  /* [2202] */
    (xdc_Char)0x70,  /* [2203] */
    (xdc_Char)0x74,  /* [2204] */
    (xdc_Char)0x20,  /* [2205] */
    (xdc_Char)0x74,  /* [2206] */
    (xdc_Char)0x68,  /* [2207] */
    (xdc_Char)0x72,  /* [2208] */
    (xdc_Char)0x65,  /* [2209] */
    (xdc_Char)0x61,  /* [2210] */
    (xdc_Char)0x64,  /* [2211] */
    (xdc_Char)0x2e,  /* [2212] */
    (xdc_Char)0x0,  /* [2213] */
    (xdc_Char)0x41,  /* [2214] */
    (xdc_Char)0x5f,  /* [2215] */
    (xdc_Char)0x62,  /* [2216] */
    (xdc_Char)0x61,  /* [2217] */
    (xdc_Char)0x64,  /* [2218] */
    (xdc_Char)0x43,  /* [2219] */
    (xdc_Char)0x6f,  /* [2220] */
    (xdc_Char)0x6e,  /* [2221] */
    (xdc_Char)0x74,  /* [2222] */
    (xdc_Char)0x65,  /* [2223] */
    (xdc_Char)0x78,  /* [2224] */
    (xdc_Char)0x74,  /* [2225] */
    (xdc_Char)0x3a,  /* [2226] */
    (xdc_Char)0x20,  /* [2227] */
    (xdc_Char)0x62,  /* [2228] */
    (xdc_Char)0x61,  /* [2229] */
    (xdc_Char)0x64,  /* [2230] */
    (xdc_Char)0x20,  /* [2231] */
    (xdc_Char)0x63,  /* [2232] */
    (xdc_Char)0x61,  /* [2233] */
    (xdc_Char)0x6c,  /* [2234] */
    (xdc_Char)0x6c,  /* [2235] */
    (xdc_Char)0x69,  /* [2236] */
    (xdc_Char)0x6e,  /* [2237] */
    (xdc_Char)0x67,  /* [2238] */
    (xdc_Char)0x20,  /* [2239] */
    (xdc_Char)0x63,  /* [2240] */
    (xdc_Char)0x6f,  /* [2241] */
    (xdc_Char)0x6e,  /* [2242] */
    (xdc_Char)0x74,  /* [2243] */
    (xdc_Char)0x65,  /* [2244] */
    (xdc_Char)0x78,  /* [2245] */
    (xdc_Char)0x74,  /* [2246] */
    (xdc_Char)0x2e,  /* [2247] */
    (xdc_Char)0x20,  /* [2248] */
    (xdc_Char)0x53,  /* [2249] */
    (xdc_Char)0x65,  /* [2250] */
    (xdc_Char)0x65,  /* [2251] */
    (xdc_Char)0x20,  /* [2252] */
    (xdc_Char)0x47,  /* [2253] */
    (xdc_Char)0x61,  /* [2254] */
    (xdc_Char)0x74,  /* [2255] */
    (xdc_Char)0x65,  /* [2256] */
    (xdc_Char)0x4d,  /* [2257] */
    (xdc_Char)0x75,  /* [2258] */
    (xdc_Char)0x74,  /* [2259] */
    (xdc_Char)0x65,  /* [2260] */
    (xdc_Char)0x78,  /* [2261] */
    (xdc_Char)0x50,  /* [2262] */
    (xdc_Char)0x72,  /* [2263] */
    (xdc_Char)0x69,  /* [2264] */
    (xdc_Char)0x20,  /* [2265] */
    (xdc_Char)0x41,  /* [2266] */
    (xdc_Char)0x50,  /* [2267] */
    (xdc_Char)0x49,  /* [2268] */
    (xdc_Char)0x20,  /* [2269] */
    (xdc_Char)0x64,  /* [2270] */
    (xdc_Char)0x6f,  /* [2271] */
    (xdc_Char)0x63,  /* [2272] */
    (xdc_Char)0x20,  /* [2273] */
    (xdc_Char)0x66,  /* [2274] */
    (xdc_Char)0x6f,  /* [2275] */
    (xdc_Char)0x72,  /* [2276] */
    (xdc_Char)0x20,  /* [2277] */
    (xdc_Char)0x64,  /* [2278] */
    (xdc_Char)0x65,  /* [2279] */
    (xdc_Char)0x74,  /* [2280] */
    (xdc_Char)0x61,  /* [2281] */
    (xdc_Char)0x69,  /* [2282] */
    (xdc_Char)0x6c,  /* [2283] */
    (xdc_Char)0x73,  /* [2284] */
    (xdc_Char)0x2e,  /* [2285] */
    (xdc_Char)0x0,  /* [2286] */
    (xdc_Char)0x41,  /* [2287] */
    (xdc_Char)0x5f,  /* [2288] */
    (xdc_Char)0x65,  /* [2289] */
    (xdc_Char)0x6e,  /* [2290] */
    (xdc_Char)0x74,  /* [2291] */
    (xdc_Char)0x65,  /* [2292] */
    (xdc_Char)0x72,  /* [2293] */
    (xdc_Char)0x54,  /* [2294] */
    (xdc_Char)0x61,  /* [2295] */
    (xdc_Char)0x73,  /* [2296] */
    (xdc_Char)0x6b,  /* [2297] */
    (xdc_Char)0x44,  /* [2298] */
    (xdc_Char)0x69,  /* [2299] */
    (xdc_Char)0x73,  /* [2300] */
    (xdc_Char)0x61,  /* [2301] */
    (xdc_Char)0x62,  /* [2302] */
    (xdc_Char)0x6c,  /* [2303] */
    (xdc_Char)0x65,  /* [2304] */
    (xdc_Char)0x64,  /* [2305] */
    (xdc_Char)0x3a,  /* [2306] */
    (xdc_Char)0x20,  /* [2307] */
    (xdc_Char)0x43,  /* [2308] */
    (xdc_Char)0x61,  /* [2309] */
    (xdc_Char)0x6e,  /* [2310] */
    (xdc_Char)0x6e,  /* [2311] */
    (xdc_Char)0x6f,  /* [2312] */
    (xdc_Char)0x74,  /* [2313] */
    (xdc_Char)0x20,  /* [2314] */
    (xdc_Char)0x63,  /* [2315] */
    (xdc_Char)0x61,  /* [2316] */
    (xdc_Char)0x6c,  /* [2317] */
    (xdc_Char)0x6c,  /* [2318] */
    (xdc_Char)0x20,  /* [2319] */
    (xdc_Char)0x47,  /* [2320] */
    (xdc_Char)0x61,  /* [2321] */
    (xdc_Char)0x74,  /* [2322] */
    (xdc_Char)0x65,  /* [2323] */
    (xdc_Char)0x4d,  /* [2324] */
    (xdc_Char)0x75,  /* [2325] */
    (xdc_Char)0x74,  /* [2326] */
    (xdc_Char)0x65,  /* [2327] */
    (xdc_Char)0x78,  /* [2328] */
    (xdc_Char)0x50,  /* [2329] */
    (xdc_Char)0x72,  /* [2330] */
    (xdc_Char)0x69,  /* [2331] */
    (xdc_Char)0x5f,  /* [2332] */
    (xdc_Char)0x65,  /* [2333] */
    (xdc_Char)0x6e,  /* [2334] */
    (xdc_Char)0x74,  /* [2335] */
    (xdc_Char)0x65,  /* [2336] */
    (xdc_Char)0x72,  /* [2337] */
    (xdc_Char)0x28,  /* [2338] */
    (xdc_Char)0x29,  /* [2339] */
    (xdc_Char)0x20,  /* [2340] */
    (xdc_Char)0x77,  /* [2341] */
    (xdc_Char)0x68,  /* [2342] */
    (xdc_Char)0x69,  /* [2343] */
    (xdc_Char)0x6c,  /* [2344] */
    (xdc_Char)0x65,  /* [2345] */
    (xdc_Char)0x20,  /* [2346] */
    (xdc_Char)0x74,  /* [2347] */
    (xdc_Char)0x68,  /* [2348] */
    (xdc_Char)0x65,  /* [2349] */
    (xdc_Char)0x20,  /* [2350] */
    (xdc_Char)0x54,  /* [2351] */
    (xdc_Char)0x61,  /* [2352] */
    (xdc_Char)0x73,  /* [2353] */
    (xdc_Char)0x6b,  /* [2354] */
    (xdc_Char)0x20,  /* [2355] */
    (xdc_Char)0x6f,  /* [2356] */
    (xdc_Char)0x72,  /* [2357] */
    (xdc_Char)0x20,  /* [2358] */
    (xdc_Char)0x53,  /* [2359] */
    (xdc_Char)0x77,  /* [2360] */
    (xdc_Char)0x69,  /* [2361] */
    (xdc_Char)0x20,  /* [2362] */
    (xdc_Char)0x73,  /* [2363] */
    (xdc_Char)0x63,  /* [2364] */
    (xdc_Char)0x68,  /* [2365] */
    (xdc_Char)0x65,  /* [2366] */
    (xdc_Char)0x64,  /* [2367] */
    (xdc_Char)0x75,  /* [2368] */
    (xdc_Char)0x6c,  /* [2369] */
    (xdc_Char)0x65,  /* [2370] */
    (xdc_Char)0x72,  /* [2371] */
    (xdc_Char)0x20,  /* [2372] */
    (xdc_Char)0x69,  /* [2373] */
    (xdc_Char)0x73,  /* [2374] */
    (xdc_Char)0x20,  /* [2375] */
    (xdc_Char)0x64,  /* [2376] */
    (xdc_Char)0x69,  /* [2377] */
    (xdc_Char)0x73,  /* [2378] */
    (xdc_Char)0x61,  /* [2379] */
    (xdc_Char)0x62,  /* [2380] */
    (xdc_Char)0x6c,  /* [2381] */
    (xdc_Char)0x65,  /* [2382] */
    (xdc_Char)0x64,  /* [2383] */
    (xdc_Char)0x2e,  /* [2384] */
    (xdc_Char)0x0,  /* [2385] */
    (xdc_Char)0x41,  /* [2386] */
    (xdc_Char)0x5f,  /* [2387] */
    (xdc_Char)0x62,  /* [2388] */
    (xdc_Char)0x61,  /* [2389] */
    (xdc_Char)0x64,  /* [2390] */
    (xdc_Char)0x43,  /* [2391] */
    (xdc_Char)0x6f,  /* [2392] */
    (xdc_Char)0x6e,  /* [2393] */
    (xdc_Char)0x74,  /* [2394] */
    (xdc_Char)0x65,  /* [2395] */
    (xdc_Char)0x78,  /* [2396] */
    (xdc_Char)0x74,  /* [2397] */
    (xdc_Char)0x3a,  /* [2398] */
    (xdc_Char)0x20,  /* [2399] */
    (xdc_Char)0x62,  /* [2400] */
    (xdc_Char)0x61,  /* [2401] */
    (xdc_Char)0x64,  /* [2402] */
    (xdc_Char)0x20,  /* [2403] */
    (xdc_Char)0x63,  /* [2404] */
    (xdc_Char)0x61,  /* [2405] */
    (xdc_Char)0x6c,  /* [2406] */
    (xdc_Char)0x6c,  /* [2407] */
    (xdc_Char)0x69,  /* [2408] */
    (xdc_Char)0x6e,  /* [2409] */
    (xdc_Char)0x67,  /* [2410] */
    (xdc_Char)0x20,  /* [2411] */
    (xdc_Char)0x63,  /* [2412] */
    (xdc_Char)0x6f,  /* [2413] */
    (xdc_Char)0x6e,  /* [2414] */
    (xdc_Char)0x74,  /* [2415] */
    (xdc_Char)0x65,  /* [2416] */
    (xdc_Char)0x78,  /* [2417] */
    (xdc_Char)0x74,  /* [2418] */
    (xdc_Char)0x2e,  /* [2419] */
    (xdc_Char)0x20,  /* [2420] */
    (xdc_Char)0x53,  /* [2421] */
    (xdc_Char)0x65,  /* [2422] */
    (xdc_Char)0x65,  /* [2423] */
    (xdc_Char)0x20,  /* [2424] */
    (xdc_Char)0x47,  /* [2425] */
    (xdc_Char)0x61,  /* [2426] */
    (xdc_Char)0x74,  /* [2427] */
    (xdc_Char)0x65,  /* [2428] */
    (xdc_Char)0x4d,  /* [2429] */
    (xdc_Char)0x75,  /* [2430] */
    (xdc_Char)0x74,  /* [2431] */
    (xdc_Char)0x65,  /* [2432] */
    (xdc_Char)0x78,  /* [2433] */
    (xdc_Char)0x20,  /* [2434] */
    (xdc_Char)0x41,  /* [2435] */
    (xdc_Char)0x50,  /* [2436] */
    (xdc_Char)0x49,  /* [2437] */
    (xdc_Char)0x20,  /* [2438] */
    (xdc_Char)0x64,  /* [2439] */
    (xdc_Char)0x6f,  /* [2440] */
    (xdc_Char)0x63,  /* [2441] */
    (xdc_Char)0x20,  /* [2442] */
    (xdc_Char)0x66,  /* [2443] */
    (xdc_Char)0x6f,  /* [2444] */
    (xdc_Char)0x72,  /* [2445] */
    (xdc_Char)0x20,  /* [2446] */
    (xdc_Char)0x64,  /* [2447] */
    (xdc_Char)0x65,  /* [2448] */
    (xdc_Char)0x74,  /* [2449] */
    (xdc_Char)0x61,  /* [2450] */
    (xdc_Char)0x69,  /* [2451] */
    (xdc_Char)0x6c,  /* [2452] */
    (xdc_Char)0x73,  /* [2453] */
    (xdc_Char)0x2e,  /* [2454] */
    (xdc_Char)0x0,  /* [2455] */
    (xdc_Char)0x41,  /* [2456] */
    (xdc_Char)0x5f,  /* [2457] */
    (xdc_Char)0x62,  /* [2458] */
    (xdc_Char)0x61,  /* [2459] */
    (xdc_Char)0x64,  /* [2460] */
    (xdc_Char)0x43,  /* [2461] */
    (xdc_Char)0x6f,  /* [2462] */
    (xdc_Char)0x6e,  /* [2463] */
    (xdc_Char)0x74,  /* [2464] */
    (xdc_Char)0x65,  /* [2465] */
    (xdc_Char)0x78,  /* [2466] */
    (xdc_Char)0x74,  /* [2467] */
    (xdc_Char)0x3a,  /* [2468] */
    (xdc_Char)0x20,  /* [2469] */
    (xdc_Char)0x62,  /* [2470] */
    (xdc_Char)0x61,  /* [2471] */
    (xdc_Char)0x64,  /* [2472] */
    (xdc_Char)0x20,  /* [2473] */
    (xdc_Char)0x63,  /* [2474] */
    (xdc_Char)0x61,  /* [2475] */
    (xdc_Char)0x6c,  /* [2476] */
    (xdc_Char)0x6c,  /* [2477] */
    (xdc_Char)0x69,  /* [2478] */
    (xdc_Char)0x6e,  /* [2479] */
    (xdc_Char)0x67,  /* [2480] */
    (xdc_Char)0x20,  /* [2481] */
    (xdc_Char)0x63,  /* [2482] */
    (xdc_Char)0x6f,  /* [2483] */
    (xdc_Char)0x6e,  /* [2484] */
    (xdc_Char)0x74,  /* [2485] */
    (xdc_Char)0x65,  /* [2486] */
    (xdc_Char)0x78,  /* [2487] */
    (xdc_Char)0x74,  /* [2488] */
    (xdc_Char)0x2e,  /* [2489] */
    (xdc_Char)0x20,  /* [2490] */
    (xdc_Char)0x53,  /* [2491] */
    (xdc_Char)0x65,  /* [2492] */
    (xdc_Char)0x65,  /* [2493] */
    (xdc_Char)0x20,  /* [2494] */
    (xdc_Char)0x47,  /* [2495] */
    (xdc_Char)0x61,  /* [2496] */
    (xdc_Char)0x74,  /* [2497] */
    (xdc_Char)0x65,  /* [2498] */
    (xdc_Char)0x53,  /* [2499] */
    (xdc_Char)0x70,  /* [2500] */
    (xdc_Char)0x69,  /* [2501] */
    (xdc_Char)0x6e,  /* [2502] */
    (xdc_Char)0x6c,  /* [2503] */
    (xdc_Char)0x6f,  /* [2504] */
    (xdc_Char)0x63,  /* [2505] */
    (xdc_Char)0x6b,  /* [2506] */
    (xdc_Char)0x20,  /* [2507] */
    (xdc_Char)0x41,  /* [2508] */
    (xdc_Char)0x50,  /* [2509] */
    (xdc_Char)0x49,  /* [2510] */
    (xdc_Char)0x20,  /* [2511] */
    (xdc_Char)0x64,  /* [2512] */
    (xdc_Char)0x6f,  /* [2513] */
    (xdc_Char)0x63,  /* [2514] */
    (xdc_Char)0x20,  /* [2515] */
    (xdc_Char)0x66,  /* [2516] */
    (xdc_Char)0x6f,  /* [2517] */
    (xdc_Char)0x72,  /* [2518] */
    (xdc_Char)0x20,  /* [2519] */
    (xdc_Char)0x64,  /* [2520] */
    (xdc_Char)0x65,  /* [2521] */
    (xdc_Char)0x74,  /* [2522] */
    (xdc_Char)0x61,  /* [2523] */
    (xdc_Char)0x69,  /* [2524] */
    (xdc_Char)0x6c,  /* [2525] */
    (xdc_Char)0x73,  /* [2526] */
    (xdc_Char)0x2e,  /* [2527] */
    (xdc_Char)0x0,  /* [2528] */
    (xdc_Char)0x41,  /* [2529] */
    (xdc_Char)0x5f,  /* [2530] */
    (xdc_Char)0x69,  /* [2531] */
    (xdc_Char)0x6e,  /* [2532] */
    (xdc_Char)0x76,  /* [2533] */
    (xdc_Char)0x61,  /* [2534] */
    (xdc_Char)0x6c,  /* [2535] */
    (xdc_Char)0x69,  /* [2536] */
    (xdc_Char)0x64,  /* [2537] */
    (xdc_Char)0x51,  /* [2538] */
    (xdc_Char)0x75,  /* [2539] */
    (xdc_Char)0x61,  /* [2540] */
    (xdc_Char)0x6c,  /* [2541] */
    (xdc_Char)0x69,  /* [2542] */
    (xdc_Char)0x74,  /* [2543] */
    (xdc_Char)0x79,  /* [2544] */
    (xdc_Char)0x3a,  /* [2545] */
    (xdc_Char)0x20,  /* [2546] */
    (xdc_Char)0x53,  /* [2547] */
    (xdc_Char)0x65,  /* [2548] */
    (xdc_Char)0x65,  /* [2549] */
    (xdc_Char)0x20,  /* [2550] */
    (xdc_Char)0x47,  /* [2551] */
    (xdc_Char)0x61,  /* [2552] */
    (xdc_Char)0x74,  /* [2553] */
    (xdc_Char)0x65,  /* [2554] */
    (xdc_Char)0x53,  /* [2555] */
    (xdc_Char)0x70,  /* [2556] */
    (xdc_Char)0x69,  /* [2557] */
    (xdc_Char)0x6e,  /* [2558] */
    (xdc_Char)0x6c,  /* [2559] */
    (xdc_Char)0x6f,  /* [2560] */
    (xdc_Char)0x63,  /* [2561] */
    (xdc_Char)0x6b,  /* [2562] */
    (xdc_Char)0x20,  /* [2563] */
    (xdc_Char)0x41,  /* [2564] */
    (xdc_Char)0x50,  /* [2565] */
    (xdc_Char)0x49,  /* [2566] */
    (xdc_Char)0x20,  /* [2567] */
    (xdc_Char)0x64,  /* [2568] */
    (xdc_Char)0x6f,  /* [2569] */
    (xdc_Char)0x63,  /* [2570] */
    (xdc_Char)0x20,  /* [2571] */
    (xdc_Char)0x66,  /* [2572] */
    (xdc_Char)0x6f,  /* [2573] */
    (xdc_Char)0x72,  /* [2574] */
    (xdc_Char)0x20,  /* [2575] */
    (xdc_Char)0x64,  /* [2576] */
    (xdc_Char)0x65,  /* [2577] */
    (xdc_Char)0x74,  /* [2578] */
    (xdc_Char)0x61,  /* [2579] */
    (xdc_Char)0x69,  /* [2580] */
    (xdc_Char)0x6c,  /* [2581] */
    (xdc_Char)0x73,  /* [2582] */
    (xdc_Char)0x2e,  /* [2583] */
    (xdc_Char)0x0,  /* [2584] */
    (xdc_Char)0x41,  /* [2585] */
    (xdc_Char)0x5f,  /* [2586] */
    (xdc_Char)0x7a,  /* [2587] */
    (xdc_Char)0x65,  /* [2588] */
    (xdc_Char)0x72,  /* [2589] */
    (xdc_Char)0x6f,  /* [2590] */
    (xdc_Char)0x54,  /* [2591] */
    (xdc_Char)0x69,  /* [2592] */
    (xdc_Char)0x6d,  /* [2593] */
    (xdc_Char)0x65,  /* [2594] */
    (xdc_Char)0x6f,  /* [2595] */
    (xdc_Char)0x75,  /* [2596] */
    (xdc_Char)0x74,  /* [2597] */
    (xdc_Char)0x3a,  /* [2598] */
    (xdc_Char)0x20,  /* [2599] */
    (xdc_Char)0x54,  /* [2600] */
    (xdc_Char)0x69,  /* [2601] */
    (xdc_Char)0x6d,  /* [2602] */
    (xdc_Char)0x65,  /* [2603] */
    (xdc_Char)0x6f,  /* [2604] */
    (xdc_Char)0x75,  /* [2605] */
    (xdc_Char)0x74,  /* [2606] */
    (xdc_Char)0x20,  /* [2607] */
    (xdc_Char)0x76,  /* [2608] */
    (xdc_Char)0x61,  /* [2609] */
    (xdc_Char)0x6c,  /* [2610] */
    (xdc_Char)0x75,  /* [2611] */
    (xdc_Char)0x65,  /* [2612] */
    (xdc_Char)0x20,  /* [2613] */
    (xdc_Char)0x61,  /* [2614] */
    (xdc_Char)0x6e,  /* [2615] */
    (xdc_Char)0x6e,  /* [2616] */
    (xdc_Char)0x6f,  /* [2617] */
    (xdc_Char)0x74,  /* [2618] */
    (xdc_Char)0x20,  /* [2619] */
    (xdc_Char)0x62,  /* [2620] */
    (xdc_Char)0x65,  /* [2621] */
    (xdc_Char)0x20,  /* [2622] */
    (xdc_Char)0x7a,  /* [2623] */
    (xdc_Char)0x65,  /* [2624] */
    (xdc_Char)0x72,  /* [2625] */
    (xdc_Char)0x6f,  /* [2626] */
    (xdc_Char)0x0,  /* [2627] */
    (xdc_Char)0x41,  /* [2628] */
    (xdc_Char)0x5f,  /* [2629] */
    (xdc_Char)0x69,  /* [2630] */
    (xdc_Char)0x6e,  /* [2631] */
    (xdc_Char)0x76,  /* [2632] */
    (xdc_Char)0x61,  /* [2633] */
    (xdc_Char)0x6c,  /* [2634] */
    (xdc_Char)0x69,  /* [2635] */
    (xdc_Char)0x64,  /* [2636] */
    (xdc_Char)0x4b,  /* [2637] */
    (xdc_Char)0x65,  /* [2638] */
    (xdc_Char)0x79,  /* [2639] */
    (xdc_Char)0x3a,  /* [2640] */
    (xdc_Char)0x20,  /* [2641] */
    (xdc_Char)0x74,  /* [2642] */
    (xdc_Char)0x68,  /* [2643] */
    (xdc_Char)0x65,  /* [2644] */
    (xdc_Char)0x20,  /* [2645] */
    (xdc_Char)0x6b,  /* [2646] */
    (xdc_Char)0x65,  /* [2647] */
    (xdc_Char)0x79,  /* [2648] */
    (xdc_Char)0x20,  /* [2649] */
    (xdc_Char)0x6d,  /* [2650] */
    (xdc_Char)0x75,  /* [2651] */
    (xdc_Char)0x73,  /* [2652] */
    (xdc_Char)0x74,  /* [2653] */
    (xdc_Char)0x20,  /* [2654] */
    (xdc_Char)0x62,  /* [2655] */
    (xdc_Char)0x65,  /* [2656] */
    (xdc_Char)0x20,  /* [2657] */
    (xdc_Char)0x73,  /* [2658] */
    (xdc_Char)0x65,  /* [2659] */
    (xdc_Char)0x74,  /* [2660] */
    (xdc_Char)0x20,  /* [2661] */
    (xdc_Char)0x74,  /* [2662] */
    (xdc_Char)0x6f,  /* [2663] */
    (xdc_Char)0x20,  /* [2664] */
    (xdc_Char)0x61,  /* [2665] */
    (xdc_Char)0x20,  /* [2666] */
    (xdc_Char)0x6e,  /* [2667] */
    (xdc_Char)0x6f,  /* [2668] */
    (xdc_Char)0x6e,  /* [2669] */
    (xdc_Char)0x2d,  /* [2670] */
    (xdc_Char)0x64,  /* [2671] */
    (xdc_Char)0x65,  /* [2672] */
    (xdc_Char)0x66,  /* [2673] */
    (xdc_Char)0x61,  /* [2674] */
    (xdc_Char)0x75,  /* [2675] */
    (xdc_Char)0x6c,  /* [2676] */
    (xdc_Char)0x74,  /* [2677] */
    (xdc_Char)0x20,  /* [2678] */
    (xdc_Char)0x76,  /* [2679] */
    (xdc_Char)0x61,  /* [2680] */
    (xdc_Char)0x6c,  /* [2681] */
    (xdc_Char)0x75,  /* [2682] */
    (xdc_Char)0x65,  /* [2683] */
    (xdc_Char)0x0,  /* [2684] */
    (xdc_Char)0x41,  /* [2685] */
    (xdc_Char)0x5f,  /* [2686] */
    (xdc_Char)0x69,  /* [2687] */
    (xdc_Char)0x6e,  /* [2688] */
    (xdc_Char)0x76,  /* [2689] */
    (xdc_Char)0x61,  /* [2690] */
    (xdc_Char)0x6c,  /* [2691] */
    (xdc_Char)0x69,  /* [2692] */
    (xdc_Char)0x64,  /* [2693] */
    (xdc_Char)0x4c,  /* [2694] */
    (xdc_Char)0x65,  /* [2695] */
    (xdc_Char)0x6e,  /* [2696] */
    (xdc_Char)0x3a,  /* [2697] */
    (xdc_Char)0x20,  /* [2698] */
    (xdc_Char)0x49,  /* [2699] */
    (xdc_Char)0x6e,  /* [2700] */
    (xdc_Char)0x76,  /* [2701] */
    (xdc_Char)0x61,  /* [2702] */
    (xdc_Char)0x6c,  /* [2703] */
    (xdc_Char)0x69,  /* [2704] */
    (xdc_Char)0x64,  /* [2705] */
    (xdc_Char)0x20,  /* [2706] */
    (xdc_Char)0x6c,  /* [2707] */
    (xdc_Char)0x65,  /* [2708] */
    (xdc_Char)0x6e,  /* [2709] */
    (xdc_Char)0x67,  /* [2710] */
    (xdc_Char)0x74,  /* [2711] */
    (xdc_Char)0x68,  /* [2712] */
    (xdc_Char)0x0,  /* [2713] */
    (xdc_Char)0x41,  /* [2714] */
    (xdc_Char)0x5f,  /* [2715] */
    (xdc_Char)0x69,  /* [2716] */
    (xdc_Char)0x6e,  /* [2717] */
    (xdc_Char)0x76,  /* [2718] */
    (xdc_Char)0x41,  /* [2719] */
    (xdc_Char)0x72,  /* [2720] */
    (xdc_Char)0x67,  /* [2721] */
    (xdc_Char)0x75,  /* [2722] */
    (xdc_Char)0x6d,  /* [2723] */
    (xdc_Char)0x65,  /* [2724] */
    (xdc_Char)0x6e,  /* [2725] */
    (xdc_Char)0x74,  /* [2726] */
    (xdc_Char)0x3a,  /* [2727] */
    (xdc_Char)0x20,  /* [2728] */
    (xdc_Char)0x49,  /* [2729] */
    (xdc_Char)0x6e,  /* [2730] */
    (xdc_Char)0x76,  /* [2731] */
    (xdc_Char)0x61,  /* [2732] */
    (xdc_Char)0x6c,  /* [2733] */
    (xdc_Char)0x69,  /* [2734] */
    (xdc_Char)0x64,  /* [2735] */
    (xdc_Char)0x20,  /* [2736] */
    (xdc_Char)0x61,  /* [2737] */
    (xdc_Char)0x72,  /* [2738] */
    (xdc_Char)0x67,  /* [2739] */
    (xdc_Char)0x75,  /* [2740] */
    (xdc_Char)0x6d,  /* [2741] */
    (xdc_Char)0x65,  /* [2742] */
    (xdc_Char)0x6e,  /* [2743] */
    (xdc_Char)0x74,  /* [2744] */
    (xdc_Char)0x20,  /* [2745] */
    (xdc_Char)0x73,  /* [2746] */
    (xdc_Char)0x75,  /* [2747] */
    (xdc_Char)0x70,  /* [2748] */
    (xdc_Char)0x70,  /* [2749] */
    (xdc_Char)0x6c,  /* [2750] */
    (xdc_Char)0x69,  /* [2751] */
    (xdc_Char)0x65,  /* [2752] */
    (xdc_Char)0x64,  /* [2753] */
    (xdc_Char)0x0,  /* [2754] */
    (xdc_Char)0x41,  /* [2755] */
    (xdc_Char)0x5f,  /* [2756] */
    (xdc_Char)0x69,  /* [2757] */
    (xdc_Char)0x6e,  /* [2758] */
    (xdc_Char)0x76,  /* [2759] */
    (xdc_Char)0x61,  /* [2760] */
    (xdc_Char)0x6c,  /* [2761] */
    (xdc_Char)0x69,  /* [2762] */
    (xdc_Char)0x64,  /* [2763] */
    (xdc_Char)0x4d,  /* [2764] */
    (xdc_Char)0x75,  /* [2765] */
    (xdc_Char)0x6c,  /* [2766] */
    (xdc_Char)0x74,  /* [2767] */
    (xdc_Char)0x69,  /* [2768] */
    (xdc_Char)0x50,  /* [2769] */
    (xdc_Char)0x72,  /* [2770] */
    (xdc_Char)0x6f,  /* [2771] */
    (xdc_Char)0x63,  /* [2772] */
    (xdc_Char)0x49,  /* [2773] */
    (xdc_Char)0x64,  /* [2774] */
    (xdc_Char)0x3a,  /* [2775] */
    (xdc_Char)0x20,  /* [2776] */
    (xdc_Char)0x49,  /* [2777] */
    (xdc_Char)0x6e,  /* [2778] */
    (xdc_Char)0x76,  /* [2779] */
    (xdc_Char)0x61,  /* [2780] */
    (xdc_Char)0x6c,  /* [2781] */
    (xdc_Char)0x69,  /* [2782] */
    (xdc_Char)0x64,  /* [2783] */
    (xdc_Char)0x20,  /* [2784] */
    (xdc_Char)0x4d,  /* [2785] */
    (xdc_Char)0x75,  /* [2786] */
    (xdc_Char)0x6c,  /* [2787] */
    (xdc_Char)0x74,  /* [2788] */
    (xdc_Char)0x69,  /* [2789] */
    (xdc_Char)0x50,  /* [2790] */
    (xdc_Char)0x72,  /* [2791] */
    (xdc_Char)0x6f,  /* [2792] */
    (xdc_Char)0x63,  /* [2793] */
    (xdc_Char)0x20,  /* [2794] */
    (xdc_Char)0x69,  /* [2795] */
    (xdc_Char)0x64,  /* [2796] */
    (xdc_Char)0x0,  /* [2797] */
    (xdc_Char)0x41,  /* [2798] */
    (xdc_Char)0x5f,  /* [2799] */
    (xdc_Char)0x69,  /* [2800] */
    (xdc_Char)0x6e,  /* [2801] */
    (xdc_Char)0x76,  /* [2802] */
    (xdc_Char)0x61,  /* [2803] */
    (xdc_Char)0x6c,  /* [2804] */
    (xdc_Char)0x69,  /* [2805] */
    (xdc_Char)0x64,  /* [2806] */
    (xdc_Char)0x50,  /* [2807] */
    (xdc_Char)0x72,  /* [2808] */
    (xdc_Char)0x6f,  /* [2809] */
    (xdc_Char)0x63,  /* [2810] */
    (xdc_Char)0x4e,  /* [2811] */
    (xdc_Char)0x61,  /* [2812] */
    (xdc_Char)0x6d,  /* [2813] */
    (xdc_Char)0x65,  /* [2814] */
    (xdc_Char)0x3a,  /* [2815] */
    (xdc_Char)0x20,  /* [2816] */
    (xdc_Char)0x4e,  /* [2817] */
    (xdc_Char)0x55,  /* [2818] */
    (xdc_Char)0x4c,  /* [2819] */
    (xdc_Char)0x4c,  /* [2820] */
    (xdc_Char)0x20,  /* [2821] */
    (xdc_Char)0x4d,  /* [2822] */
    (xdc_Char)0x75,  /* [2823] */
    (xdc_Char)0x6c,  /* [2824] */
    (xdc_Char)0x74,  /* [2825] */
    (xdc_Char)0x69,  /* [2826] */
    (xdc_Char)0x50,  /* [2827] */
    (xdc_Char)0x72,  /* [2828] */
    (xdc_Char)0x6f,  /* [2829] */
    (xdc_Char)0x63,  /* [2830] */
    (xdc_Char)0x20,  /* [2831] */
    (xdc_Char)0x6e,  /* [2832] */
    (xdc_Char)0x61,  /* [2833] */
    (xdc_Char)0x6d,  /* [2834] */
    (xdc_Char)0x65,  /* [2835] */
    (xdc_Char)0x20,  /* [2836] */
    (xdc_Char)0x65,  /* [2837] */
    (xdc_Char)0x6e,  /* [2838] */
    (xdc_Char)0x63,  /* [2839] */
    (xdc_Char)0x6f,  /* [2840] */
    (xdc_Char)0x75,  /* [2841] */
    (xdc_Char)0x6e,  /* [2842] */
    (xdc_Char)0x74,  /* [2843] */
    (xdc_Char)0x65,  /* [2844] */
    (xdc_Char)0x72,  /* [2845] */
    (xdc_Char)0x65,  /* [2846] */
    (xdc_Char)0x64,  /* [2847] */
    (xdc_Char)0x0,  /* [2848] */
    (xdc_Char)0x61,  /* [2849] */
    (xdc_Char)0x73,  /* [2850] */
    (xdc_Char)0x73,  /* [2851] */
    (xdc_Char)0x65,  /* [2852] */
    (xdc_Char)0x72,  /* [2853] */
    (xdc_Char)0x74,  /* [2854] */
    (xdc_Char)0x69,  /* [2855] */
    (xdc_Char)0x6f,  /* [2856] */
    (xdc_Char)0x6e,  /* [2857] */
    (xdc_Char)0x20,  /* [2858] */
    (xdc_Char)0x66,  /* [2859] */
    (xdc_Char)0x61,  /* [2860] */
    (xdc_Char)0x69,  /* [2861] */
    (xdc_Char)0x6c,  /* [2862] */
    (xdc_Char)0x75,  /* [2863] */
    (xdc_Char)0x72,  /* [2864] */
    (xdc_Char)0x65,  /* [2865] */
    (xdc_Char)0x25,  /* [2866] */
    (xdc_Char)0x73,  /* [2867] */
    (xdc_Char)0x25,  /* [2868] */
    (xdc_Char)0x73,  /* [2869] */
    (xdc_Char)0x0,  /* [2870] */
    (xdc_Char)0x25,  /* [2871] */
    (xdc_Char)0x24,  /* [2872] */
    (xdc_Char)0x53,  /* [2873] */
    (xdc_Char)0x0,  /* [2874] */
    (xdc_Char)0x6f,  /* [2875] */
    (xdc_Char)0x75,  /* [2876] */
    (xdc_Char)0x74,  /* [2877] */
    (xdc_Char)0x20,  /* [2878] */
    (xdc_Char)0x6f,  /* [2879] */
    (xdc_Char)0x66,  /* [2880] */
    (xdc_Char)0x20,  /* [2881] */
    (xdc_Char)0x6d,  /* [2882] */
    (xdc_Char)0x65,  /* [2883] */
    (xdc_Char)0x6d,  /* [2884] */
    (xdc_Char)0x6f,  /* [2885] */
    (xdc_Char)0x72,  /* [2886] */
    (xdc_Char)0x79,  /* [2887] */
    (xdc_Char)0x3a,  /* [2888] */
    (xdc_Char)0x20,  /* [2889] */
    (xdc_Char)0x68,  /* [2890] */
    (xdc_Char)0x65,  /* [2891] */
    (xdc_Char)0x61,  /* [2892] */
    (xdc_Char)0x70,  /* [2893] */
    (xdc_Char)0x3d,  /* [2894] */
    (xdc_Char)0x30,  /* [2895] */
    (xdc_Char)0x78,  /* [2896] */
    (xdc_Char)0x25,  /* [2897] */
    (xdc_Char)0x78,  /* [2898] */
    (xdc_Char)0x2c,  /* [2899] */
    (xdc_Char)0x20,  /* [2900] */
    (xdc_Char)0x73,  /* [2901] */
    (xdc_Char)0x69,  /* [2902] */
    (xdc_Char)0x7a,  /* [2903] */
    (xdc_Char)0x65,  /* [2904] */
    (xdc_Char)0x3d,  /* [2905] */
    (xdc_Char)0x25,  /* [2906] */
    (xdc_Char)0x75,  /* [2907] */
    (xdc_Char)0x0,  /* [2908] */
    (xdc_Char)0x25,  /* [2909] */
    (xdc_Char)0x73,  /* [2910] */
    (xdc_Char)0x20,  /* [2911] */
    (xdc_Char)0x30,  /* [2912] */
    (xdc_Char)0x78,  /* [2913] */
    (xdc_Char)0x25,  /* [2914] */
    (xdc_Char)0x78,  /* [2915] */
    (xdc_Char)0x0,  /* [2916] */
    (xdc_Char)0x45,  /* [2917] */
    (xdc_Char)0x5f,  /* [2918] */
    (xdc_Char)0x62,  /* [2919] */
    (xdc_Char)0x61,  /* [2920] */
    (xdc_Char)0x64,  /* [2921] */
    (xdc_Char)0x4c,  /* [2922] */
    (xdc_Char)0x65,  /* [2923] */
    (xdc_Char)0x76,  /* [2924] */
    (xdc_Char)0x65,  /* [2925] */
    (xdc_Char)0x6c,  /* [2926] */
    (xdc_Char)0x3a,  /* [2927] */
    (xdc_Char)0x20,  /* [2928] */
    (xdc_Char)0x42,  /* [2929] */
    (xdc_Char)0x61,  /* [2930] */
    (xdc_Char)0x64,  /* [2931] */
    (xdc_Char)0x20,  /* [2932] */
    (xdc_Char)0x66,  /* [2933] */
    (xdc_Char)0x69,  /* [2934] */
    (xdc_Char)0x6c,  /* [2935] */
    (xdc_Char)0x74,  /* [2936] */
    (xdc_Char)0x65,  /* [2937] */
    (xdc_Char)0x72,  /* [2938] */
    (xdc_Char)0x20,  /* [2939] */
    (xdc_Char)0x6c,  /* [2940] */
    (xdc_Char)0x65,  /* [2941] */
    (xdc_Char)0x76,  /* [2942] */
    (xdc_Char)0x65,  /* [2943] */
    (xdc_Char)0x6c,  /* [2944] */
    (xdc_Char)0x20,  /* [2945] */
    (xdc_Char)0x76,  /* [2946] */
    (xdc_Char)0x61,  /* [2947] */
    (xdc_Char)0x6c,  /* [2948] */
    (xdc_Char)0x75,  /* [2949] */
    (xdc_Char)0x65,  /* [2950] */
    (xdc_Char)0x3a,  /* [2951] */
    (xdc_Char)0x20,  /* [2952] */
    (xdc_Char)0x25,  /* [2953] */
    (xdc_Char)0x64,  /* [2954] */
    (xdc_Char)0x0,  /* [2955] */
    (xdc_Char)0x66,  /* [2956] */
    (xdc_Char)0x72,  /* [2957] */
    (xdc_Char)0x65,  /* [2958] */
    (xdc_Char)0x65,  /* [2959] */
    (xdc_Char)0x28,  /* [2960] */
    (xdc_Char)0x29,  /* [2961] */
    (xdc_Char)0x20,  /* [2962] */
    (xdc_Char)0x69,  /* [2963] */
    (xdc_Char)0x6e,  /* [2964] */
    (xdc_Char)0x76,  /* [2965] */
    (xdc_Char)0x61,  /* [2966] */
    (xdc_Char)0x6c,  /* [2967] */
    (xdc_Char)0x69,  /* [2968] */
    (xdc_Char)0x64,  /* [2969] */
    (xdc_Char)0x20,  /* [2970] */
    (xdc_Char)0x69,  /* [2971] */
    (xdc_Char)0x6e,  /* [2972] */
    (xdc_Char)0x20,  /* [2973] */
    (xdc_Char)0x67,  /* [2974] */
    (xdc_Char)0x72,  /* [2975] */
    (xdc_Char)0x6f,  /* [2976] */
    (xdc_Char)0x77,  /* [2977] */
    (xdc_Char)0x74,  /* [2978] */
    (xdc_Char)0x68,  /* [2979] */
    (xdc_Char)0x2d,  /* [2980] */
    (xdc_Char)0x6f,  /* [2981] */
    (xdc_Char)0x6e,  /* [2982] */
    (xdc_Char)0x6c,  /* [2983] */
    (xdc_Char)0x79,  /* [2984] */
    (xdc_Char)0x20,  /* [2985] */
    (xdc_Char)0x48,  /* [2986] */
    (xdc_Char)0x65,  /* [2987] */
    (xdc_Char)0x61,  /* [2988] */
    (xdc_Char)0x70,  /* [2989] */
    (xdc_Char)0x4d,  /* [2990] */
    (xdc_Char)0x69,  /* [2991] */
    (xdc_Char)0x6e,  /* [2992] */
    (xdc_Char)0x0,  /* [2993] */
    (xdc_Char)0x54,  /* [2994] */
    (xdc_Char)0x68,  /* [2995] */
    (xdc_Char)0x65,  /* [2996] */
    (xdc_Char)0x20,  /* [2997] */
    (xdc_Char)0x52,  /* [2998] */
    (xdc_Char)0x54,  /* [2999] */
    (xdc_Char)0x53,  /* [3000] */
    (xdc_Char)0x20,  /* [3001] */
    (xdc_Char)0x68,  /* [3002] */
    (xdc_Char)0x65,  /* [3003] */
    (xdc_Char)0x61,  /* [3004] */
    (xdc_Char)0x70,  /* [3005] */
    (xdc_Char)0x20,  /* [3006] */
    (xdc_Char)0x69,  /* [3007] */
    (xdc_Char)0x73,  /* [3008] */
    (xdc_Char)0x20,  /* [3009] */
    (xdc_Char)0x75,  /* [3010] */
    (xdc_Char)0x73,  /* [3011] */
    (xdc_Char)0x65,  /* [3012] */
    (xdc_Char)0x64,  /* [3013] */
    (xdc_Char)0x20,  /* [3014] */
    (xdc_Char)0x75,  /* [3015] */
    (xdc_Char)0x70,  /* [3016] */
    (xdc_Char)0x2e,  /* [3017] */
    (xdc_Char)0x20,  /* [3018] */
    (xdc_Char)0x45,  /* [3019] */
    (xdc_Char)0x78,  /* [3020] */
    (xdc_Char)0x61,  /* [3021] */
    (xdc_Char)0x6d,  /* [3022] */
    (xdc_Char)0x69,  /* [3023] */
    (xdc_Char)0x6e,  /* [3024] */
    (xdc_Char)0x65,  /* [3025] */
    (xdc_Char)0x20,  /* [3026] */
    (xdc_Char)0x50,  /* [3027] */
    (xdc_Char)0x72,  /* [3028] */
    (xdc_Char)0x6f,  /* [3029] */
    (xdc_Char)0x67,  /* [3030] */
    (xdc_Char)0x72,  /* [3031] */
    (xdc_Char)0x61,  /* [3032] */
    (xdc_Char)0x6d,  /* [3033] */
    (xdc_Char)0x2e,  /* [3034] */
    (xdc_Char)0x68,  /* [3035] */
    (xdc_Char)0x65,  /* [3036] */
    (xdc_Char)0x61,  /* [3037] */
    (xdc_Char)0x70,  /* [3038] */
    (xdc_Char)0x2e,  /* [3039] */
    (xdc_Char)0x0,  /* [3040] */
    (xdc_Char)0x45,  /* [3041] */
    (xdc_Char)0x5f,  /* [3042] */
    (xdc_Char)0x62,  /* [3043] */
    (xdc_Char)0x61,  /* [3044] */
    (xdc_Char)0x64,  /* [3045] */
    (xdc_Char)0x43,  /* [3046] */
    (xdc_Char)0x6f,  /* [3047] */
    (xdc_Char)0x6d,  /* [3048] */
    (xdc_Char)0x6d,  /* [3049] */
    (xdc_Char)0x61,  /* [3050] */
    (xdc_Char)0x6e,  /* [3051] */
    (xdc_Char)0x64,  /* [3052] */
    (xdc_Char)0x3a,  /* [3053] */
    (xdc_Char)0x20,  /* [3054] */
    (xdc_Char)0x52,  /* [3055] */
    (xdc_Char)0x65,  /* [3056] */
    (xdc_Char)0x63,  /* [3057] */
    (xdc_Char)0x65,  /* [3058] */
    (xdc_Char)0x69,  /* [3059] */
    (xdc_Char)0x76,  /* [3060] */
    (xdc_Char)0x65,  /* [3061] */
    (xdc_Char)0x64,  /* [3062] */
    (xdc_Char)0x20,  /* [3063] */
    (xdc_Char)0x69,  /* [3064] */
    (xdc_Char)0x6e,  /* [3065] */
    (xdc_Char)0x76,  /* [3066] */
    (xdc_Char)0x61,  /* [3067] */
    (xdc_Char)0x6c,  /* [3068] */
    (xdc_Char)0x69,  /* [3069] */
    (xdc_Char)0x64,  /* [3070] */
    (xdc_Char)0x20,  /* [3071] */
    (xdc_Char)0x63,  /* [3072] */
    (xdc_Char)0x6f,  /* [3073] */
    (xdc_Char)0x6d,  /* [3074] */
    (xdc_Char)0x6d,  /* [3075] */
    (xdc_Char)0x61,  /* [3076] */
    (xdc_Char)0x6e,  /* [3077] */
    (xdc_Char)0x64,  /* [3078] */
    (xdc_Char)0x2c,  /* [3079] */
    (xdc_Char)0x20,  /* [3080] */
    (xdc_Char)0x69,  /* [3081] */
    (xdc_Char)0x64,  /* [3082] */
    (xdc_Char)0x3a,  /* [3083] */
    (xdc_Char)0x20,  /* [3084] */
    (xdc_Char)0x25,  /* [3085] */
    (xdc_Char)0x64,  /* [3086] */
    (xdc_Char)0x2e,  /* [3087] */
    (xdc_Char)0x0,  /* [3088] */
    (xdc_Char)0x45,  /* [3089] */
    (xdc_Char)0x5f,  /* [3090] */
    (xdc_Char)0x73,  /* [3091] */
    (xdc_Char)0x74,  /* [3092] */
    (xdc_Char)0x61,  /* [3093] */
    (xdc_Char)0x63,  /* [3094] */
    (xdc_Char)0x6b,  /* [3095] */
    (xdc_Char)0x4f,  /* [3096] */
    (xdc_Char)0x76,  /* [3097] */
    (xdc_Char)0x65,  /* [3098] */
    (xdc_Char)0x72,  /* [3099] */
    (xdc_Char)0x66,  /* [3100] */
    (xdc_Char)0x6c,  /* [3101] */
    (xdc_Char)0x6f,  /* [3102] */
    (xdc_Char)0x77,  /* [3103] */
    (xdc_Char)0x3a,  /* [3104] */
    (xdc_Char)0x20,  /* [3105] */
    (xdc_Char)0x54,  /* [3106] */
    (xdc_Char)0x61,  /* [3107] */
    (xdc_Char)0x73,  /* [3108] */
    (xdc_Char)0x6b,  /* [3109] */
    (xdc_Char)0x20,  /* [3110] */
    (xdc_Char)0x30,  /* [3111] */
    (xdc_Char)0x78,  /* [3112] */
    (xdc_Char)0x25,  /* [3113] */
    (xdc_Char)0x78,  /* [3114] */
    (xdc_Char)0x20,  /* [3115] */
    (xdc_Char)0x73,  /* [3116] */
    (xdc_Char)0x74,  /* [3117] */
    (xdc_Char)0x61,  /* [3118] */
    (xdc_Char)0x63,  /* [3119] */
    (xdc_Char)0x6b,  /* [3120] */
    (xdc_Char)0x20,  /* [3121] */
    (xdc_Char)0x6f,  /* [3122] */
    (xdc_Char)0x76,  /* [3123] */
    (xdc_Char)0x65,  /* [3124] */
    (xdc_Char)0x72,  /* [3125] */
    (xdc_Char)0x66,  /* [3126] */
    (xdc_Char)0x6c,  /* [3127] */
    (xdc_Char)0x6f,  /* [3128] */
    (xdc_Char)0x77,  /* [3129] */
    (xdc_Char)0x2e,  /* [3130] */
    (xdc_Char)0x0,  /* [3131] */
    (xdc_Char)0x45,  /* [3132] */
    (xdc_Char)0x5f,  /* [3133] */
    (xdc_Char)0x73,  /* [3134] */
    (xdc_Char)0x70,  /* [3135] */
    (xdc_Char)0x4f,  /* [3136] */
    (xdc_Char)0x75,  /* [3137] */
    (xdc_Char)0x74,  /* [3138] */
    (xdc_Char)0x4f,  /* [3139] */
    (xdc_Char)0x66,  /* [3140] */
    (xdc_Char)0x42,  /* [3141] */
    (xdc_Char)0x6f,  /* [3142] */
    (xdc_Char)0x75,  /* [3143] */
    (xdc_Char)0x6e,  /* [3144] */
    (xdc_Char)0x64,  /* [3145] */
    (xdc_Char)0x73,  /* [3146] */
    (xdc_Char)0x3a,  /* [3147] */
    (xdc_Char)0x20,  /* [3148] */
    (xdc_Char)0x54,  /* [3149] */
    (xdc_Char)0x61,  /* [3150] */
    (xdc_Char)0x73,  /* [3151] */
    (xdc_Char)0x6b,  /* [3152] */
    (xdc_Char)0x20,  /* [3153] */
    (xdc_Char)0x30,  /* [3154] */
    (xdc_Char)0x78,  /* [3155] */
    (xdc_Char)0x25,  /* [3156] */
    (xdc_Char)0x78,  /* [3157] */
    (xdc_Char)0x20,  /* [3158] */
    (xdc_Char)0x73,  /* [3159] */
    (xdc_Char)0x74,  /* [3160] */
    (xdc_Char)0x61,  /* [3161] */
    (xdc_Char)0x63,  /* [3162] */
    (xdc_Char)0x6b,  /* [3163] */
    (xdc_Char)0x20,  /* [3164] */
    (xdc_Char)0x65,  /* [3165] */
    (xdc_Char)0x72,  /* [3166] */
    (xdc_Char)0x72,  /* [3167] */
    (xdc_Char)0x6f,  /* [3168] */
    (xdc_Char)0x72,  /* [3169] */
    (xdc_Char)0x2c,  /* [3170] */
    (xdc_Char)0x20,  /* [3171] */
    (xdc_Char)0x53,  /* [3172] */
    (xdc_Char)0x50,  /* [3173] */
    (xdc_Char)0x20,  /* [3174] */
    (xdc_Char)0x3d,  /* [3175] */
    (xdc_Char)0x20,  /* [3176] */
    (xdc_Char)0x30,  /* [3177] */
    (xdc_Char)0x78,  /* [3178] */
    (xdc_Char)0x25,  /* [3179] */
    (xdc_Char)0x78,  /* [3180] */
    (xdc_Char)0x2e,  /* [3181] */
    (xdc_Char)0x0,  /* [3182] */
    (xdc_Char)0x45,  /* [3183] */
    (xdc_Char)0x5f,  /* [3184] */
    (xdc_Char)0x64,  /* [3185] */
    (xdc_Char)0x65,  /* [3186] */
    (xdc_Char)0x6c,  /* [3187] */
    (xdc_Char)0x65,  /* [3188] */
    (xdc_Char)0x74,  /* [3189] */
    (xdc_Char)0x65,  /* [3190] */
    (xdc_Char)0x4e,  /* [3191] */
    (xdc_Char)0x6f,  /* [3192] */
    (xdc_Char)0x74,  /* [3193] */
    (xdc_Char)0x41,  /* [3194] */
    (xdc_Char)0x6c,  /* [3195] */
    (xdc_Char)0x6c,  /* [3196] */
    (xdc_Char)0x6f,  /* [3197] */
    (xdc_Char)0x77,  /* [3198] */
    (xdc_Char)0x65,  /* [3199] */
    (xdc_Char)0x64,  /* [3200] */
    (xdc_Char)0x3a,  /* [3201] */
    (xdc_Char)0x20,  /* [3202] */
    (xdc_Char)0x54,  /* [3203] */
    (xdc_Char)0x61,  /* [3204] */
    (xdc_Char)0x73,  /* [3205] */
    (xdc_Char)0x6b,  /* [3206] */
    (xdc_Char)0x20,  /* [3207] */
    (xdc_Char)0x30,  /* [3208] */
    (xdc_Char)0x78,  /* [3209] */
    (xdc_Char)0x25,  /* [3210] */
    (xdc_Char)0x78,  /* [3211] */
    (xdc_Char)0x2e,  /* [3212] */
    (xdc_Char)0x0,  /* [3213] */
    (xdc_Char)0x45,  /* [3214] */
    (xdc_Char)0x5f,  /* [3215] */
    (xdc_Char)0x6d,  /* [3216] */
    (xdc_Char)0x61,  /* [3217] */
    (xdc_Char)0x78,  /* [3218] */
    (xdc_Char)0x52,  /* [3219] */
    (xdc_Char)0x65,  /* [3220] */
    (xdc_Char)0x61,  /* [3221] */
    (xdc_Char)0x63,  /* [3222] */
    (xdc_Char)0x68,  /* [3223] */
    (xdc_Char)0x65,  /* [3224] */
    (xdc_Char)0x64,  /* [3225] */
    (xdc_Char)0x3a,  /* [3226] */
    (xdc_Char)0x20,  /* [3227] */
    (xdc_Char)0x41,  /* [3228] */
    (xdc_Char)0x6c,  /* [3229] */
    (xdc_Char)0x6c,  /* [3230] */
    (xdc_Char)0x20,  /* [3231] */
    (xdc_Char)0x65,  /* [3232] */
    (xdc_Char)0x6e,  /* [3233] */
    (xdc_Char)0x74,  /* [3234] */
    (xdc_Char)0x72,  /* [3235] */
    (xdc_Char)0x69,  /* [3236] */
    (xdc_Char)0x65,  /* [3237] */
    (xdc_Char)0x73,  /* [3238] */
    (xdc_Char)0x20,  /* [3239] */
    (xdc_Char)0x69,  /* [3240] */
    (xdc_Char)0x6e,  /* [3241] */
    (xdc_Char)0x20,  /* [3242] */
    (xdc_Char)0x75,  /* [3243] */
    (xdc_Char)0x73,  /* [3244] */
    (xdc_Char)0x65,  /* [3245] */
    (xdc_Char)0x2e,  /* [3246] */
    (xdc_Char)0x20,  /* [3247] */
    (xdc_Char)0x4e,  /* [3248] */
    (xdc_Char)0x61,  /* [3249] */
    (xdc_Char)0x6d,  /* [3250] */
    (xdc_Char)0x65,  /* [3251] */
    (xdc_Char)0x53,  /* [3252] */
    (xdc_Char)0x65,  /* [3253] */
    (xdc_Char)0x72,  /* [3254] */
    (xdc_Char)0x76,  /* [3255] */
    (xdc_Char)0x65,  /* [3256] */
    (xdc_Char)0x72,  /* [3257] */
    (xdc_Char)0x2e,  /* [3258] */
    (xdc_Char)0x6d,  /* [3259] */
    (xdc_Char)0x61,  /* [3260] */
    (xdc_Char)0x78,  /* [3261] */
    (xdc_Char)0x52,  /* [3262] */
    (xdc_Char)0x75,  /* [3263] */
    (xdc_Char)0x6e,  /* [3264] */
    (xdc_Char)0x74,  /* [3265] */
    (xdc_Char)0x69,  /* [3266] */
    (xdc_Char)0x6d,  /* [3267] */
    (xdc_Char)0x65,  /* [3268] */
    (xdc_Char)0x45,  /* [3269] */
    (xdc_Char)0x6e,  /* [3270] */
    (xdc_Char)0x74,  /* [3271] */
    (xdc_Char)0x72,  /* [3272] */
    (xdc_Char)0x69,  /* [3273] */
    (xdc_Char)0x65,  /* [3274] */
    (xdc_Char)0x73,  /* [3275] */
    (xdc_Char)0x20,  /* [3276] */
    (xdc_Char)0x69,  /* [3277] */
    (xdc_Char)0x73,  /* [3278] */
    (xdc_Char)0x20,  /* [3279] */
    (xdc_Char)0x25,  /* [3280] */
    (xdc_Char)0x64,  /* [3281] */
    (xdc_Char)0x0,  /* [3282] */
    (xdc_Char)0x45,  /* [3283] */
    (xdc_Char)0x5f,  /* [3284] */
    (xdc_Char)0x65,  /* [3285] */
    (xdc_Char)0x6e,  /* [3286] */
    (xdc_Char)0x74,  /* [3287] */
    (xdc_Char)0x72,  /* [3288] */
    (xdc_Char)0x79,  /* [3289] */
    (xdc_Char)0x45,  /* [3290] */
    (xdc_Char)0x78,  /* [3291] */
    (xdc_Char)0x69,  /* [3292] */
    (xdc_Char)0x73,  /* [3293] */
    (xdc_Char)0x74,  /* [3294] */
    (xdc_Char)0x73,  /* [3295] */
    (xdc_Char)0x3a,  /* [3296] */
    (xdc_Char)0x20,  /* [3297] */
    (xdc_Char)0x25,  /* [3298] */
    (xdc_Char)0x73,  /* [3299] */
    (xdc_Char)0x20,  /* [3300] */
    (xdc_Char)0x6e,  /* [3301] */
    (xdc_Char)0x61,  /* [3302] */
    (xdc_Char)0x6d,  /* [3303] */
    (xdc_Char)0x65,  /* [3304] */
    (xdc_Char)0x20,  /* [3305] */
    (xdc_Char)0x61,  /* [3306] */
    (xdc_Char)0x6c,  /* [3307] */
    (xdc_Char)0x72,  /* [3308] */
    (xdc_Char)0x65,  /* [3309] */
    (xdc_Char)0x61,  /* [3310] */
    (xdc_Char)0x64,  /* [3311] */
    (xdc_Char)0x79,  /* [3312] */
    (xdc_Char)0x20,  /* [3313] */
    (xdc_Char)0x69,  /* [3314] */
    (xdc_Char)0x6e,  /* [3315] */
    (xdc_Char)0x20,  /* [3316] */
    (xdc_Char)0x74,  /* [3317] */
    (xdc_Char)0x61,  /* [3318] */
    (xdc_Char)0x62,  /* [3319] */
    (xdc_Char)0x6c,  /* [3320] */
    (xdc_Char)0x65,  /* [3321] */
    (xdc_Char)0x20,  /* [3322] */
    (xdc_Char)0x0,  /* [3323] */
    (xdc_Char)0x45,  /* [3324] */
    (xdc_Char)0x5f,  /* [3325] */
    (xdc_Char)0x70,  /* [3326] */
    (xdc_Char)0x61,  /* [3327] */
    (xdc_Char)0x72,  /* [3328] */
    (xdc_Char)0x61,  /* [3329] */
    (xdc_Char)0x6d,  /* [3330] */
    (xdc_Char)0x4d,  /* [3331] */
    (xdc_Char)0x69,  /* [3332] */
    (xdc_Char)0x73,  /* [3333] */
    (xdc_Char)0x6d,  /* [3334] */
    (xdc_Char)0x61,  /* [3335] */
    (xdc_Char)0x74,  /* [3336] */
    (xdc_Char)0x63,  /* [3337] */
    (xdc_Char)0x68,  /* [3338] */
    (xdc_Char)0x3a,  /* [3339] */
    (xdc_Char)0x20,  /* [3340] */
    (xdc_Char)0x70,  /* [3341] */
    (xdc_Char)0x61,  /* [3342] */
    (xdc_Char)0x72,  /* [3343] */
    (xdc_Char)0x61,  /* [3344] */
    (xdc_Char)0x6d,  /* [3345] */
    (xdc_Char)0x65,  /* [3346] */
    (xdc_Char)0x74,  /* [3347] */
    (xdc_Char)0x65,  /* [3348] */
    (xdc_Char)0x72,  /* [3349] */
    (xdc_Char)0x73,  /* [3350] */
    (xdc_Char)0x20,  /* [3351] */
    (xdc_Char)0x64,  /* [3352] */
    (xdc_Char)0x6f,  /* [3353] */
    (xdc_Char)0x20,  /* [3354] */
    (xdc_Char)0x6e,  /* [3355] */
    (xdc_Char)0x6f,  /* [3356] */
    (xdc_Char)0x74,  /* [3357] */
    (xdc_Char)0x20,  /* [3358] */
    (xdc_Char)0x6d,  /* [3359] */
    (xdc_Char)0x61,  /* [3360] */
    (xdc_Char)0x74,  /* [3361] */
    (xdc_Char)0x63,  /* [3362] */
    (xdc_Char)0x68,  /* [3363] */
    (xdc_Char)0x20,  /* [3364] */
    (xdc_Char)0x65,  /* [3365] */
    (xdc_Char)0x78,  /* [3366] */
    (xdc_Char)0x69,  /* [3367] */
    (xdc_Char)0x73,  /* [3368] */
    (xdc_Char)0x74,  /* [3369] */
    (xdc_Char)0x69,  /* [3370] */
    (xdc_Char)0x6e,  /* [3371] */
    (xdc_Char)0x67,  /* [3372] */
    (xdc_Char)0x20,  /* [3373] */
    (xdc_Char)0x4e,  /* [3374] */
    (xdc_Char)0x61,  /* [3375] */
    (xdc_Char)0x6d,  /* [3376] */
    (xdc_Char)0x65,  /* [3377] */
    (xdc_Char)0x53,  /* [3378] */
    (xdc_Char)0x65,  /* [3379] */
    (xdc_Char)0x72,  /* [3380] */
    (xdc_Char)0x76,  /* [3381] */
    (xdc_Char)0x65,  /* [3382] */
    (xdc_Char)0x72,  /* [3383] */
    (xdc_Char)0x20,  /* [3384] */
    (xdc_Char)0x25,  /* [3385] */
    (xdc_Char)0x73,  /* [3386] */
    (xdc_Char)0x20,  /* [3387] */
    (xdc_Char)0x0,  /* [3388] */
    (xdc_Char)0x3c,  /* [3389] */
    (xdc_Char)0x2d,  /* [3390] */
    (xdc_Char)0x2d,  /* [3391] */
    (xdc_Char)0x20,  /* [3392] */
    (xdc_Char)0x63,  /* [3393] */
    (xdc_Char)0x6f,  /* [3394] */
    (xdc_Char)0x6e,  /* [3395] */
    (xdc_Char)0x73,  /* [3396] */
    (xdc_Char)0x74,  /* [3397] */
    (xdc_Char)0x72,  /* [3398] */
    (xdc_Char)0x75,  /* [3399] */
    (xdc_Char)0x63,  /* [3400] */
    (xdc_Char)0x74,  /* [3401] */
    (xdc_Char)0x3a,  /* [3402] */
    (xdc_Char)0x20,  /* [3403] */
    (xdc_Char)0x25,  /* [3404] */
    (xdc_Char)0x70,  /* [3405] */
    (xdc_Char)0x28,  /* [3406] */
    (xdc_Char)0x27,  /* [3407] */
    (xdc_Char)0x25,  /* [3408] */
    (xdc_Char)0x73,  /* [3409] */
    (xdc_Char)0x27,  /* [3410] */
    (xdc_Char)0x29,  /* [3411] */
    (xdc_Char)0x0,  /* [3412] */
    (xdc_Char)0x3c,  /* [3413] */
    (xdc_Char)0x2d,  /* [3414] */
    (xdc_Char)0x2d,  /* [3415] */
    (xdc_Char)0x20,  /* [3416] */
    (xdc_Char)0x63,  /* [3417] */
    (xdc_Char)0x72,  /* [3418] */
    (xdc_Char)0x65,  /* [3419] */
    (xdc_Char)0x61,  /* [3420] */
    (xdc_Char)0x74,  /* [3421] */
    (xdc_Char)0x65,  /* [3422] */
    (xdc_Char)0x3a,  /* [3423] */
    (xdc_Char)0x20,  /* [3424] */
    (xdc_Char)0x25,  /* [3425] */
    (xdc_Char)0x70,  /* [3426] */
    (xdc_Char)0x28,  /* [3427] */
    (xdc_Char)0x27,  /* [3428] */
    (xdc_Char)0x25,  /* [3429] */
    (xdc_Char)0x73,  /* [3430] */
    (xdc_Char)0x27,  /* [3431] */
    (xdc_Char)0x29,  /* [3432] */
    (xdc_Char)0x0,  /* [3433] */
    (xdc_Char)0x2d,  /* [3434] */
    (xdc_Char)0x2d,  /* [3435] */
    (xdc_Char)0x3e,  /* [3436] */
    (xdc_Char)0x20,  /* [3437] */
    (xdc_Char)0x64,  /* [3438] */
    (xdc_Char)0x65,  /* [3439] */
    (xdc_Char)0x73,  /* [3440] */
    (xdc_Char)0x74,  /* [3441] */
    (xdc_Char)0x72,  /* [3442] */
    (xdc_Char)0x75,  /* [3443] */
    (xdc_Char)0x63,  /* [3444] */
    (xdc_Char)0x74,  /* [3445] */
    (xdc_Char)0x3a,  /* [3446] */
    (xdc_Char)0x20,  /* [3447] */
    (xdc_Char)0x28,  /* [3448] */
    (xdc_Char)0x25,  /* [3449] */
    (xdc_Char)0x70,  /* [3450] */
    (xdc_Char)0x29,  /* [3451] */
    (xdc_Char)0x0,  /* [3452] */
    (xdc_Char)0x2d,  /* [3453] */
    (xdc_Char)0x2d,  /* [3454] */
    (xdc_Char)0x3e,  /* [3455] */
    (xdc_Char)0x20,  /* [3456] */
    (xdc_Char)0x64,  /* [3457] */
    (xdc_Char)0x65,  /* [3458] */
    (xdc_Char)0x6c,  /* [3459] */
    (xdc_Char)0x65,  /* [3460] */
    (xdc_Char)0x74,  /* [3461] */
    (xdc_Char)0x65,  /* [3462] */
    (xdc_Char)0x3a,  /* [3463] */
    (xdc_Char)0x20,  /* [3464] */
    (xdc_Char)0x28,  /* [3465] */
    (xdc_Char)0x25,  /* [3466] */
    (xdc_Char)0x70,  /* [3467] */
    (xdc_Char)0x29,  /* [3468] */
    (xdc_Char)0x0,  /* [3469] */
    (xdc_Char)0x45,  /* [3470] */
    (xdc_Char)0x52,  /* [3471] */
    (xdc_Char)0x52,  /* [3472] */
    (xdc_Char)0x4f,  /* [3473] */
    (xdc_Char)0x52,  /* [3474] */
    (xdc_Char)0x3a,  /* [3475] */
    (xdc_Char)0x20,  /* [3476] */
    (xdc_Char)0x25,  /* [3477] */
    (xdc_Char)0x24,  /* [3478] */
    (xdc_Char)0x46,  /* [3479] */
    (xdc_Char)0x25,  /* [3480] */
    (xdc_Char)0x24,  /* [3481] */
    (xdc_Char)0x53,  /* [3482] */
    (xdc_Char)0x0,  /* [3483] */
    (xdc_Char)0x57,  /* [3484] */
    (xdc_Char)0x41,  /* [3485] */
    (xdc_Char)0x52,  /* [3486] */
    (xdc_Char)0x4e,  /* [3487] */
    (xdc_Char)0x49,  /* [3488] */
    (xdc_Char)0x4e,  /* [3489] */
    (xdc_Char)0x47,  /* [3490] */
    (xdc_Char)0x3a,  /* [3491] */
    (xdc_Char)0x20,  /* [3492] */
    (xdc_Char)0x25,  /* [3493] */
    (xdc_Char)0x24,  /* [3494] */
    (xdc_Char)0x46,  /* [3495] */
    (xdc_Char)0x25,  /* [3496] */
    (xdc_Char)0x24,  /* [3497] */
    (xdc_Char)0x53,  /* [3498] */
    (xdc_Char)0x0,  /* [3499] */
    (xdc_Char)0x25,  /* [3500] */
    (xdc_Char)0x24,  /* [3501] */
    (xdc_Char)0x46,  /* [3502] */
    (xdc_Char)0x25,  /* [3503] */
    (xdc_Char)0x24,  /* [3504] */
    (xdc_Char)0x53,  /* [3505] */
    (xdc_Char)0x0,  /* [3506] */
    (xdc_Char)0x53,  /* [3507] */
    (xdc_Char)0x74,  /* [3508] */
    (xdc_Char)0x61,  /* [3509] */
    (xdc_Char)0x72,  /* [3510] */
    (xdc_Char)0x74,  /* [3511] */
    (xdc_Char)0x3a,  /* [3512] */
    (xdc_Char)0x20,  /* [3513] */
    (xdc_Char)0x25,  /* [3514] */
    (xdc_Char)0x24,  /* [3515] */
    (xdc_Char)0x53,  /* [3516] */
    (xdc_Char)0x0,  /* [3517] */
    (xdc_Char)0x53,  /* [3518] */
    (xdc_Char)0x74,  /* [3519] */
    (xdc_Char)0x6f,  /* [3520] */
    (xdc_Char)0x70,  /* [3521] */
    (xdc_Char)0x3a,  /* [3522] */
    (xdc_Char)0x20,  /* [3523] */
    (xdc_Char)0x25,  /* [3524] */
    (xdc_Char)0x24,  /* [3525] */
    (xdc_Char)0x53,  /* [3526] */
    (xdc_Char)0x0,  /* [3527] */
    (xdc_Char)0x53,  /* [3528] */
    (xdc_Char)0x74,  /* [3529] */
    (xdc_Char)0x61,  /* [3530] */
    (xdc_Char)0x72,  /* [3531] */
    (xdc_Char)0x74,  /* [3532] */
    (xdc_Char)0x49,  /* [3533] */
    (xdc_Char)0x6e,  /* [3534] */
    (xdc_Char)0x73,  /* [3535] */
    (xdc_Char)0x74,  /* [3536] */
    (xdc_Char)0x61,  /* [3537] */
    (xdc_Char)0x6e,  /* [3538] */
    (xdc_Char)0x63,  /* [3539] */
    (xdc_Char)0x65,  /* [3540] */
    (xdc_Char)0x3a,  /* [3541] */
    (xdc_Char)0x20,  /* [3542] */
    (xdc_Char)0x25,  /* [3543] */
    (xdc_Char)0x24,  /* [3544] */
    (xdc_Char)0x53,  /* [3545] */
    (xdc_Char)0x0,  /* [3546] */
    (xdc_Char)0x53,  /* [3547] */
    (xdc_Char)0x74,  /* [3548] */
    (xdc_Char)0x6f,  /* [3549] */
    (xdc_Char)0x70,  /* [3550] */
    (xdc_Char)0x49,  /* [3551] */
    (xdc_Char)0x6e,  /* [3552] */
    (xdc_Char)0x73,  /* [3553] */
    (xdc_Char)0x74,  /* [3554] */
    (xdc_Char)0x61,  /* [3555] */
    (xdc_Char)0x6e,  /* [3556] */
    (xdc_Char)0x63,  /* [3557] */
    (xdc_Char)0x65,  /* [3558] */
    (xdc_Char)0x3a,  /* [3559] */
    (xdc_Char)0x20,  /* [3560] */
    (xdc_Char)0x25,  /* [3561] */
    (xdc_Char)0x24,  /* [3562] */
    (xdc_Char)0x53,  /* [3563] */
    (xdc_Char)0x0,  /* [3564] */
    (xdc_Char)0x78,  /* [3565] */
    (xdc_Char)0x64,  /* [3566] */
    (xdc_Char)0x63,  /* [3567] */
    (xdc_Char)0x2e,  /* [3568] */
    (xdc_Char)0x0,  /* [3569] */
    (xdc_Char)0x72,  /* [3570] */
    (xdc_Char)0x75,  /* [3571] */
    (xdc_Char)0x6e,  /* [3572] */
    (xdc_Char)0x74,  /* [3573] */
    (xdc_Char)0x69,  /* [3574] */
    (xdc_Char)0x6d,  /* [3575] */
    (xdc_Char)0x65,  /* [3576] */
    (xdc_Char)0x2e,  /* [3577] */
    (xdc_Char)0x0,  /* [3578] */
    (xdc_Char)0x41,  /* [3579] */
    (xdc_Char)0x73,  /* [3580] */
    (xdc_Char)0x73,  /* [3581] */
    (xdc_Char)0x65,  /* [3582] */
    (xdc_Char)0x72,  /* [3583] */
    (xdc_Char)0x74,  /* [3584] */
    (xdc_Char)0x0,  /* [3585] */
    (xdc_Char)0x43,  /* [3586] */
    (xdc_Char)0x6f,  /* [3587] */
    (xdc_Char)0x72,  /* [3588] */
    (xdc_Char)0x65,  /* [3589] */
    (xdc_Char)0x0,  /* [3590] */
    (xdc_Char)0x44,  /* [3591] */
    (xdc_Char)0x65,  /* [3592] */
    (xdc_Char)0x66,  /* [3593] */
    (xdc_Char)0x61,  /* [3594] */
    (xdc_Char)0x75,  /* [3595] */
    (xdc_Char)0x6c,  /* [3596] */
    (xdc_Char)0x74,  /* [3597] */
    (xdc_Char)0x73,  /* [3598] */
    (xdc_Char)0x0,  /* [3599] */
    (xdc_Char)0x44,  /* [3600] */
    (xdc_Char)0x69,  /* [3601] */
    (xdc_Char)0x61,  /* [3602] */
    (xdc_Char)0x67,  /* [3603] */
    (xdc_Char)0x73,  /* [3604] */
    (xdc_Char)0x0,  /* [3605] */
    (xdc_Char)0x45,  /* [3606] */
    (xdc_Char)0x72,  /* [3607] */
    (xdc_Char)0x72,  /* [3608] */
    (xdc_Char)0x6f,  /* [3609] */
    (xdc_Char)0x72,  /* [3610] */
    (xdc_Char)0x0,  /* [3611] */
    (xdc_Char)0x47,  /* [3612] */
    (xdc_Char)0x61,  /* [3613] */
    (xdc_Char)0x74,  /* [3614] */
    (xdc_Char)0x65,  /* [3615] */
    (xdc_Char)0x0,  /* [3616] */
    (xdc_Char)0x47,  /* [3617] */
    (xdc_Char)0x61,  /* [3618] */
    (xdc_Char)0x74,  /* [3619] */
    (xdc_Char)0x65,  /* [3620] */
    (xdc_Char)0x4e,  /* [3621] */
    (xdc_Char)0x75,  /* [3622] */
    (xdc_Char)0x6c,  /* [3623] */
    (xdc_Char)0x6c,  /* [3624] */
    (xdc_Char)0x0,  /* [3625] */
    (xdc_Char)0x4c,  /* [3626] */
    (xdc_Char)0x6f,  /* [3627] */
    (xdc_Char)0x67,  /* [3628] */
    (xdc_Char)0x0,  /* [3629] */
    (xdc_Char)0x4d,  /* [3630] */
    (xdc_Char)0x61,  /* [3631] */
    (xdc_Char)0x69,  /* [3632] */
    (xdc_Char)0x6e,  /* [3633] */
    (xdc_Char)0x0,  /* [3634] */
    (xdc_Char)0x4d,  /* [3635] */
    (xdc_Char)0x65,  /* [3636] */
    (xdc_Char)0x6d,  /* [3637] */
    (xdc_Char)0x6f,  /* [3638] */
    (xdc_Char)0x72,  /* [3639] */
    (xdc_Char)0x79,  /* [3640] */
    (xdc_Char)0x0,  /* [3641] */
    (xdc_Char)0x48,  /* [3642] */
    (xdc_Char)0x65,  /* [3643] */
    (xdc_Char)0x61,  /* [3644] */
    (xdc_Char)0x70,  /* [3645] */
    (xdc_Char)0x53,  /* [3646] */
    (xdc_Char)0x74,  /* [3647] */
    (xdc_Char)0x64,  /* [3648] */
    (xdc_Char)0x0,  /* [3649] */
    (xdc_Char)0x52,  /* [3650] */
    (xdc_Char)0x65,  /* [3651] */
    (xdc_Char)0x67,  /* [3652] */
    (xdc_Char)0x69,  /* [3653] */
    (xdc_Char)0x73,  /* [3654] */
    (xdc_Char)0x74,  /* [3655] */
    (xdc_Char)0x72,  /* [3656] */
    (xdc_Char)0x79,  /* [3657] */
    (xdc_Char)0x0,  /* [3658] */
    (xdc_Char)0x53,  /* [3659] */
    (xdc_Char)0x74,  /* [3660] */
    (xdc_Char)0x61,  /* [3661] */
    (xdc_Char)0x72,  /* [3662] */
    (xdc_Char)0x74,  /* [3663] */
    (xdc_Char)0x75,  /* [3664] */
    (xdc_Char)0x70,  /* [3665] */
    (xdc_Char)0x0,  /* [3666] */
    (xdc_Char)0x53,  /* [3667] */
    (xdc_Char)0x79,  /* [3668] */
    (xdc_Char)0x73,  /* [3669] */
    (xdc_Char)0x74,  /* [3670] */
    (xdc_Char)0x65,  /* [3671] */
    (xdc_Char)0x6d,  /* [3672] */
    (xdc_Char)0x0,  /* [3673] */
    (xdc_Char)0x53,  /* [3674] */
    (xdc_Char)0x79,  /* [3675] */
    (xdc_Char)0x73,  /* [3676] */
    (xdc_Char)0x4d,  /* [3677] */
    (xdc_Char)0x69,  /* [3678] */
    (xdc_Char)0x6e,  /* [3679] */
    (xdc_Char)0x0,  /* [3680] */
    (xdc_Char)0x54,  /* [3681] */
    (xdc_Char)0x65,  /* [3682] */
    (xdc_Char)0x78,  /* [3683] */
    (xdc_Char)0x74,  /* [3684] */
    (xdc_Char)0x0,  /* [3685] */
    (xdc_Char)0x74,  /* [3686] */
    (xdc_Char)0x69,  /* [3687] */
    (xdc_Char)0x2e,  /* [3688] */
    (xdc_Char)0x0,  /* [3689] */
    (xdc_Char)0x63,  /* [3690] */
    (xdc_Char)0x61,  /* [3691] */
    (xdc_Char)0x74,  /* [3692] */
    (xdc_Char)0x61,  /* [3693] */
    (xdc_Char)0x6c,  /* [3694] */
    (xdc_Char)0x6f,  /* [3695] */
    (xdc_Char)0x67,  /* [3696] */
    (xdc_Char)0x2e,  /* [3697] */
    (xdc_Char)0x0,  /* [3698] */
    (xdc_Char)0x61,  /* [3699] */
    (xdc_Char)0x72,  /* [3700] */
    (xdc_Char)0x6d,  /* [3701] */
    (xdc_Char)0x2e,  /* [3702] */
    (xdc_Char)0x0,  /* [3703] */
    (xdc_Char)0x63,  /* [3704] */
    (xdc_Char)0x6f,  /* [3705] */
    (xdc_Char)0x72,  /* [3706] */
    (xdc_Char)0x74,  /* [3707] */
    (xdc_Char)0x65,  /* [3708] */
    (xdc_Char)0x78,  /* [3709] */
    (xdc_Char)0x6d,  /* [3710] */
    (xdc_Char)0x34,  /* [3711] */
    (xdc_Char)0x2e,  /* [3712] */
    (xdc_Char)0x0,  /* [3713] */
    (xdc_Char)0x74,  /* [3714] */
    (xdc_Char)0x69,  /* [3715] */
    (xdc_Char)0x76,  /* [3716] */
    (xdc_Char)0x61,  /* [3717] */
    (xdc_Char)0x2e,  /* [3718] */
    (xdc_Char)0x0,  /* [3719] */
    (xdc_Char)0x63,  /* [3720] */
    (xdc_Char)0x65,  /* [3721] */
    (xdc_Char)0x2e,  /* [3722] */
    (xdc_Char)0x0,  /* [3723] */
    (xdc_Char)0x42,  /* [3724] */
    (xdc_Char)0x6f,  /* [3725] */
    (xdc_Char)0x6f,  /* [3726] */
    (xdc_Char)0x74,  /* [3727] */
    (xdc_Char)0x0,  /* [3728] */
    (xdc_Char)0x73,  /* [3729] */
    (xdc_Char)0x64,  /* [3730] */
    (xdc_Char)0x6f,  /* [3731] */
    (xdc_Char)0x2e,  /* [3732] */
    (xdc_Char)0x0,  /* [3733] */
    (xdc_Char)0x75,  /* [3734] */
    (xdc_Char)0x74,  /* [3735] */
    (xdc_Char)0x69,  /* [3736] */
    (xdc_Char)0x6c,  /* [3737] */
    (xdc_Char)0x73,  /* [3738] */
    (xdc_Char)0x2e,  /* [3739] */
    (xdc_Char)0x0,  /* [3740] */
    (xdc_Char)0x4e,  /* [3741] */
    (xdc_Char)0x61,  /* [3742] */
    (xdc_Char)0x6d,  /* [3743] */
    (xdc_Char)0x65,  /* [3744] */
    (xdc_Char)0x53,  /* [3745] */
    (xdc_Char)0x65,  /* [3746] */
    (xdc_Char)0x72,  /* [3747] */
    (xdc_Char)0x76,  /* [3748] */
    (xdc_Char)0x65,  /* [3749] */
    (xdc_Char)0x72,  /* [3750] */
    (xdc_Char)0x52,  /* [3751] */
    (xdc_Char)0x65,  /* [3752] */
    (xdc_Char)0x6d,  /* [3753] */
    (xdc_Char)0x6f,  /* [3754] */
    (xdc_Char)0x74,  /* [3755] */
    (xdc_Char)0x65,  /* [3756] */
    (xdc_Char)0x4e,  /* [3757] */
    (xdc_Char)0x75,  /* [3758] */
    (xdc_Char)0x6c,  /* [3759] */
    (xdc_Char)0x6c,  /* [3760] */
    (xdc_Char)0x0,  /* [3761] */
};

/* --> xdc_runtime_Text_nodeTab__A */
#pragma DATA_SECTION(xdc_runtime_Text_nodeTab__A, ".const:xdc_runtime_Text_nodeTab__A");
const __T1_xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__A[27] = {
    {
        (xdc_Bits16)0x0,  /* left */
        (xdc_Bits16)0x0,  /* right */
    },  /* [0] */
    {
        (xdc_Bits16)0xded,  /* left */
        (xdc_Bits16)0xdf2,  /* right */
    },  /* [1] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xdfb,  /* right */
    },  /* [2] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe02,  /* right */
    },  /* [3] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe07,  /* right */
    },  /* [4] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe10,  /* right */
    },  /* [5] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe16,  /* right */
    },  /* [6] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe1c,  /* right */
    },  /* [7] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe21,  /* right */
    },  /* [8] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe2a,  /* right */
    },  /* [9] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe2e,  /* right */
    },  /* [10] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe33,  /* right */
    },  /* [11] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe3a,  /* right */
    },  /* [12] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe42,  /* right */
    },  /* [13] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe4b,  /* right */
    },  /* [14] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe53,  /* right */
    },  /* [15] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe5a,  /* right */
    },  /* [16] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xe61,  /* right */
    },  /* [17] */
    {
        (xdc_Bits16)0xe66,  /* left */
        (xdc_Bits16)0xe6a,  /* right */
    },  /* [18] */
    {
        (xdc_Bits16)0x8012,  /* left */
        (xdc_Bits16)0xe73,  /* right */
    },  /* [19] */
    {
        (xdc_Bits16)0x8013,  /* left */
        (xdc_Bits16)0xe78,  /* right */
    },  /* [20] */
    {
        (xdc_Bits16)0x8014,  /* left */
        (xdc_Bits16)0xe82,  /* right */
    },  /* [21] */
    {
        (xdc_Bits16)0x8015,  /* left */
        (xdc_Bits16)0xe88,  /* right */
    },  /* [22] */
    {
        (xdc_Bits16)0x8016,  /* left */
        (xdc_Bits16)0xe8c,  /* right */
    },  /* [23] */
    {
        (xdc_Bits16)0xe66,  /* left */
        (xdc_Bits16)0xe91,  /* right */
    },  /* [24] */
    {
        (xdc_Bits16)0x8018,  /* left */
        (xdc_Bits16)0xe96,  /* right */
    },  /* [25] */
    {
        (xdc_Bits16)0x8019,  /* left */
        (xdc_Bits16)0xe9d,  /* right */
    },  /* [26] */
};

/* Module__diagsEnabled__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__diagsEnabled__C, ".const:xdc_runtime_Text_Module__diagsEnabled__C");
__FAR__ const CT__xdc_runtime_Text_Module__diagsEnabled xdc_runtime_Text_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__diagsIncluded__C, ".const:xdc_runtime_Text_Module__diagsIncluded__C");
__FAR__ const CT__xdc_runtime_Text_Module__diagsIncluded xdc_runtime_Text_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__diagsMask__C, ".const:xdc_runtime_Text_Module__diagsMask__C");
__FAR__ const CT__xdc_runtime_Text_Module__diagsMask xdc_runtime_Text_Module__diagsMask__C = ((CT__xdc_runtime_Text_Module__diagsMask)0);

/* Module__gateObj__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__gateObj__C, ".const:xdc_runtime_Text_Module__gateObj__C");
__FAR__ const CT__xdc_runtime_Text_Module__gateObj xdc_runtime_Text_Module__gateObj__C = ((CT__xdc_runtime_Text_Module__gateObj)0);

/* Module__gatePrms__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__gatePrms__C, ".const:xdc_runtime_Text_Module__gatePrms__C");
__FAR__ const CT__xdc_runtime_Text_Module__gatePrms xdc_runtime_Text_Module__gatePrms__C = ((CT__xdc_runtime_Text_Module__gatePrms)0);

/* Module__id__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__id__C, ".const:xdc_runtime_Text_Module__id__C");
__FAR__ const CT__xdc_runtime_Text_Module__id xdc_runtime_Text_Module__id__C = (xdc_Bits16)0x8011;

/* Module__loggerDefined__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__loggerDefined__C, ".const:xdc_runtime_Text_Module__loggerDefined__C");
__FAR__ const CT__xdc_runtime_Text_Module__loggerDefined xdc_runtime_Text_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__loggerObj__C, ".const:xdc_runtime_Text_Module__loggerObj__C");
__FAR__ const CT__xdc_runtime_Text_Module__loggerObj xdc_runtime_Text_Module__loggerObj__C = ((CT__xdc_runtime_Text_Module__loggerObj)0);

/* Module__loggerFxn0__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn0__C, ".const:xdc_runtime_Text_Module__loggerFxn0__C");
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn0 xdc_runtime_Text_Module__loggerFxn0__C = ((CT__xdc_runtime_Text_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn1__C, ".const:xdc_runtime_Text_Module__loggerFxn1__C");
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn1 xdc_runtime_Text_Module__loggerFxn1__C = ((CT__xdc_runtime_Text_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn2__C, ".const:xdc_runtime_Text_Module__loggerFxn2__C");
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn2 xdc_runtime_Text_Module__loggerFxn2__C = ((CT__xdc_runtime_Text_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn4__C, ".const:xdc_runtime_Text_Module__loggerFxn4__C");
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn4 xdc_runtime_Text_Module__loggerFxn4__C = ((CT__xdc_runtime_Text_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn8__C, ".const:xdc_runtime_Text_Module__loggerFxn8__C");
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn8 xdc_runtime_Text_Module__loggerFxn8__C = ((CT__xdc_runtime_Text_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
#pragma DATA_SECTION(xdc_runtime_Text_Module__startupDoneFxn__C, ".const:xdc_runtime_Text_Module__startupDoneFxn__C");
__FAR__ const CT__xdc_runtime_Text_Module__startupDoneFxn xdc_runtime_Text_Module__startupDoneFxn__C = ((CT__xdc_runtime_Text_Module__startupDoneFxn)0);

/* Object__count__C */
#pragma DATA_SECTION(xdc_runtime_Text_Object__count__C, ".const:xdc_runtime_Text_Object__count__C");
__FAR__ const CT__xdc_runtime_Text_Object__count xdc_runtime_Text_Object__count__C = 0;

/* Object__heap__C */
#pragma DATA_SECTION(xdc_runtime_Text_Object__heap__C, ".const:xdc_runtime_Text_Object__heap__C");
__FAR__ const CT__xdc_runtime_Text_Object__heap xdc_runtime_Text_Object__heap__C = 0;

/* Object__sizeof__C */
#pragma DATA_SECTION(xdc_runtime_Text_Object__sizeof__C, ".const:xdc_runtime_Text_Object__sizeof__C");
__FAR__ const CT__xdc_runtime_Text_Object__sizeof xdc_runtime_Text_Object__sizeof__C = 0;

/* Object__table__C */
#pragma DATA_SECTION(xdc_runtime_Text_Object__table__C, ".const:xdc_runtime_Text_Object__table__C");
__FAR__ const CT__xdc_runtime_Text_Object__table xdc_runtime_Text_Object__table__C = 0;

/* nameUnknown__C */
#pragma DATA_SECTION(xdc_runtime_Text_nameUnknown__C, ".const:xdc_runtime_Text_nameUnknown__C");
__FAR__ const CT__xdc_runtime_Text_nameUnknown xdc_runtime_Text_nameUnknown__C = "{unknown-instance-name}";

/* nameEmpty__C */
#pragma DATA_SECTION(xdc_runtime_Text_nameEmpty__C, ".const:xdc_runtime_Text_nameEmpty__C");
__FAR__ const CT__xdc_runtime_Text_nameEmpty xdc_runtime_Text_nameEmpty__C = "{empty-instance-name}";

/* nameStatic__C */
#pragma DATA_SECTION(xdc_runtime_Text_nameStatic__C, ".const:xdc_runtime_Text_nameStatic__C");
__FAR__ const CT__xdc_runtime_Text_nameStatic xdc_runtime_Text_nameStatic__C = "{static-instance-name}";

/* isLoaded__C */
#pragma DATA_SECTION(xdc_runtime_Text_isLoaded__C, ".const:xdc_runtime_Text_isLoaded__C");
__FAR__ const CT__xdc_runtime_Text_isLoaded xdc_runtime_Text_isLoaded__C = 1;

/* charTab__C */
#pragma DATA_SECTION(xdc_runtime_Text_charTab__C, ".const:xdc_runtime_Text_charTab__C");
__FAR__ const CT__xdc_runtime_Text_charTab xdc_runtime_Text_charTab__C = ((CT__xdc_runtime_Text_charTab)xdc_runtime_Text_charTab__A);

/* nodeTab__C */
#pragma DATA_SECTION(xdc_runtime_Text_nodeTab__C, ".const:xdc_runtime_Text_nodeTab__C");
__FAR__ const CT__xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__C = ((CT__xdc_runtime_Text_nodeTab)xdc_runtime_Text_nodeTab__A);

/* charCnt__C */
#pragma DATA_SECTION(xdc_runtime_Text_charCnt__C, ".const:xdc_runtime_Text_charCnt__C");
__FAR__ const CT__xdc_runtime_Text_charCnt xdc_runtime_Text_charCnt__C = (xdc_Int16)0xeb2;

/* nodeCnt__C */
#pragma DATA_SECTION(xdc_runtime_Text_nodeCnt__C, ".const:xdc_runtime_Text_nodeCnt__C");
__FAR__ const CT__xdc_runtime_Text_nodeCnt xdc_runtime_Text_nodeCnt__C = (xdc_Int16)0x1b;

/* unnamedModsLastId__C */
#pragma DATA_SECTION(xdc_runtime_Text_unnamedModsLastId__C, ".const:xdc_runtime_Text_unnamedModsLastId__C");
__FAR__ const CT__xdc_runtime_Text_unnamedModsLastId xdc_runtime_Text_unnamedModsLastId__C = (xdc_UInt16)0x4000;

/* registryModsLastId__C */
#pragma DATA_SECTION(xdc_runtime_Text_registryModsLastId__C, ".const:xdc_runtime_Text_registryModsLastId__C");
__FAR__ const CT__xdc_runtime_Text_registryModsLastId xdc_runtime_Text_registryModsLastId__C = (xdc_UInt16)0x7fff;

/* visitRopeFxn__C */
#pragma DATA_SECTION(xdc_runtime_Text_visitRopeFxn__C, ".const:xdc_runtime_Text_visitRopeFxn__C");
__FAR__ const CT__xdc_runtime_Text_visitRopeFxn xdc_runtime_Text_visitRopeFxn__C = ((CT__xdc_runtime_Text_visitRopeFxn)((xdc_Fxn)xdc_runtime_Text_visitRope__I));

/* visitRopeFxn2__C */
#pragma DATA_SECTION(xdc_runtime_Text_visitRopeFxn2__C, ".const:xdc_runtime_Text_visitRopeFxn2__C");
__FAR__ const CT__xdc_runtime_Text_visitRopeFxn2 xdc_runtime_Text_visitRopeFxn2__C = ((CT__xdc_runtime_Text_visitRopeFxn2)((xdc_Fxn)xdc_runtime_Text_visitRope2__I));


/*
 * ======== ti.sdo.utils.NameServerRemoteNull FUNCTION STUBS ========
 */

/* get__E */
xdc_Int ti_sdo_utils_NameServerRemoteNull_get__E( ti_sdo_utils_NameServerRemoteNull_Handle __inst, xdc_String instanceName, xdc_String name, xdc_Ptr value, xdc_UInt32 *valueLen, xdc_runtime_knl_ISync_Handle syncHandle, xdc_runtime_Error_Block *eb ) 
{
    return ti_sdo_utils_NameServerRemoteNull_get__F((void*)__inst, instanceName, name, value, valueLen, syncHandle, eb);
}


/*
 * ======== xdc.runtime.System FUNCTION STUBS ========
 */

/* printf_va__E */
xdc_Int xdc_runtime_System_printf_va__E( xdc_CString fmt, va_list __va ) 
{
    return xdc_runtime_System_printf_va__F(fmt, __va);
}

/* printf__E */
xdc_Int xdc_runtime_System_printf__E( xdc_CString fmt, ... ) 
{
    xdc_Int __ret;

    va_list __va; va_start(__va, fmt);
    __ret = xdc_runtime_System_printf_va__F(fmt, __va);

    va_end(__va);
    return __ret;
}

/* aprintf_va__E */
xdc_Int xdc_runtime_System_aprintf_va__E( xdc_CString fmt, va_list __va ) 
{
    return xdc_runtime_System_aprintf_va__F(fmt, __va);
}

/* aprintf__E */
xdc_Int xdc_runtime_System_aprintf__E( xdc_CString fmt, ... ) 
{
    xdc_Int __ret;

    va_list __va; va_start(__va, fmt);
    __ret = xdc_runtime_System_aprintf_va__F(fmt, __va);

    va_end(__va);
    return __ret;
}

/* sprintf_va__E */
xdc_Int xdc_runtime_System_sprintf_va__E( xdc_Char buf[], xdc_CString fmt, va_list __va ) 
{
    return xdc_runtime_System_sprintf_va__F(buf, fmt, __va);
}

/* sprintf__E */
xdc_Int xdc_runtime_System_sprintf__E( xdc_Char buf[], xdc_CString fmt, ... ) 
{
    xdc_Int __ret;

    va_list __va; va_start(__va, fmt);
    __ret = xdc_runtime_System_sprintf_va__F(buf, fmt, __va);

    va_end(__va);
    return __ret;
}

/* asprintf_va__E */
xdc_Int xdc_runtime_System_asprintf_va__E( xdc_Char buf[], xdc_CString fmt, va_list __va ) 
{
    return xdc_runtime_System_asprintf_va__F(buf, fmt, __va);
}

/* asprintf__E */
xdc_Int xdc_runtime_System_asprintf__E( xdc_Char buf[], xdc_CString fmt, ... ) 
{
    xdc_Int __ret;

    va_list __va; va_start(__va, fmt);
    __ret = xdc_runtime_System_asprintf_va__F(buf, fmt, __va);

    va_end(__va);
    return __ret;
}

/* snprintf_va__E */
xdc_Int xdc_runtime_System_snprintf_va__E( xdc_Char buf[], xdc_SizeT n, xdc_CString fmt, va_list __va ) 
{
    return xdc_runtime_System_snprintf_va__F(buf, n, fmt, __va);
}

/* snprintf__E */
xdc_Int xdc_runtime_System_snprintf__E( xdc_Char buf[], xdc_SizeT n, xdc_CString fmt, ... ) 
{
    xdc_Int __ret;

    va_list __va; va_start(__va, fmt);
    __ret = xdc_runtime_System_snprintf_va__F(buf, n, fmt, __va);

    va_end(__va);
    return __ret;
}


/*
 * ======== xdc.runtime.Main_Module_GateProxy PROXY BODY ========
 */

/* DELEGATES TO xdc.runtime.GateNull */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Main_Module_GateProxy_Module__startupDone__S( void ) 
{
    return xdc_runtime_GateNull_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_Main_Module_GateProxy_Object__create__S (
    xdc_Ptr __obj, 
    xdc_SizeT __osz,
    const xdc_Ptr __aa,
    const xdc_runtime_Main_Module_GateProxy___ParamsPtr __paramsPtr,
    xdc_SizeT __psz,
    xdc_runtime_Error_Block *__eb)
{
    return xdc_runtime_GateNull_Object__create__S(__obj, __osz, __aa, (xdc_runtime_GateNull___ParamsPtr)__paramsPtr, sizeof(xdc_runtime_IGateProvider_Params), __eb);
}

/* create */
xdc_runtime_Main_Module_GateProxy_Handle xdc_runtime_Main_Module_GateProxy_create( const xdc_runtime_Main_Module_GateProxy_Params *__prms, xdc_runtime_Error_Block *__eb )
{
    return (xdc_runtime_Main_Module_GateProxy_Handle)xdc_runtime_Main_Module_GateProxy_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(xdc_runtime_Main_Module_GateProxy_Params), __eb);
}

/* Object__delete__S */
void xdc_runtime_Main_Module_GateProxy_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_GateNull_Object__delete__S(instp);
}

/* delete */
void xdc_runtime_Main_Module_GateProxy_delete(xdc_runtime_Main_Module_GateProxy_Handle *instp)
{
    xdc_runtime_Main_Module_GateProxy_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_Main_Module_GateProxy_Params__init__S( xdc_Ptr dst, const void *src, xdc_SizeT psz, xdc_SizeT isz )
{
    xdc_runtime_GateNull_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label *xdc_runtime_Main_Module_GateProxy_Handle__label__S(xdc_Ptr obj, xdc_runtime_Types_Label *lab)
{
    return xdc_runtime_GateNull_Handle__label__S(obj, lab);
}

/* query__E */
xdc_Bool xdc_runtime_Main_Module_GateProxy_query__E( xdc_Int qual )
{
    return xdc_runtime_GateNull_query(qual);
}

/* enter__E */
xdc_IArg xdc_runtime_Main_Module_GateProxy_enter__E( xdc_runtime_Main_Module_GateProxy_Handle __inst )
{
    return xdc_runtime_GateNull_enter((xdc_runtime_GateNull_Handle)__inst);
}

/* leave__E */
xdc_Void xdc_runtime_Main_Module_GateProxy_leave__E( xdc_runtime_Main_Module_GateProxy_Handle __inst, xdc_IArg key )
{
    xdc_runtime_GateNull_leave((xdc_runtime_GateNull_Handle)__inst, key);
}


/*
 * ======== xdc.runtime.Memory_HeapProxy PROXY BODY ========
 */

/* DELEGATES TO xdc.runtime.HeapStd */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Memory_HeapProxy_Module__startupDone__S( void ) 
{
    return xdc_runtime_HeapStd_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_Memory_HeapProxy_Object__create__S (
    xdc_Ptr __obj, 
    xdc_SizeT __osz,
    const xdc_Ptr __aa,
    const xdc_runtime_Memory_HeapProxy___ParamsPtr __paramsPtr,
    xdc_SizeT __psz,
    xdc_runtime_Error_Block *__eb)
{
    return xdc_runtime_HeapStd_Object__create__S(__obj, __osz, __aa, (xdc_runtime_HeapStd___ParamsPtr)__paramsPtr, sizeof(xdc_runtime_IHeap_Params), __eb);
}

/* create */
xdc_runtime_Memory_HeapProxy_Handle xdc_runtime_Memory_HeapProxy_create( const xdc_runtime_Memory_HeapProxy_Params *__prms, xdc_runtime_Error_Block *__eb )
{
    return (xdc_runtime_Memory_HeapProxy_Handle)xdc_runtime_Memory_HeapProxy_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(xdc_runtime_Memory_HeapProxy_Params), __eb);
}

/* Object__delete__S */
void xdc_runtime_Memory_HeapProxy_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_HeapStd_Object__delete__S(instp);
}

/* delete */
void xdc_runtime_Memory_HeapProxy_delete(xdc_runtime_Memory_HeapProxy_Handle *instp)
{
    xdc_runtime_Memory_HeapProxy_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_Memory_HeapProxy_Params__init__S( xdc_Ptr dst, const void *src, xdc_SizeT psz, xdc_SizeT isz )
{
    xdc_runtime_HeapStd_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label *xdc_runtime_Memory_HeapProxy_Handle__label__S(xdc_Ptr obj, xdc_runtime_Types_Label *lab)
{
    return xdc_runtime_HeapStd_Handle__label__S(obj, lab);
}

/* alloc__E */
xdc_Ptr xdc_runtime_Memory_HeapProxy_alloc__E( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block *eb )
{
    return xdc_runtime_IHeap_alloc((xdc_runtime_IHeap_Handle)__inst, size, align, eb);
}

/* free__E */
xdc_Void xdc_runtime_Memory_HeapProxy_free__E( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_Ptr block, xdc_SizeT size )
{
    xdc_runtime_IHeap_free((xdc_runtime_IHeap_Handle)__inst, block, size);
}

/* isBlocking__E */
xdc_Bool xdc_runtime_Memory_HeapProxy_isBlocking__E( xdc_runtime_Memory_HeapProxy_Handle __inst )
{
    return xdc_runtime_IHeap_isBlocking((xdc_runtime_IHeap_Handle)__inst);
}

/* getStats__E */
xdc_Void xdc_runtime_Memory_HeapProxy_getStats__E( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_runtime_Memory_Stats *stats )
{
    xdc_runtime_IHeap_getStats((xdc_runtime_IHeap_Handle)__inst, stats);
}


/*
 * ======== xdc.runtime.System_Module_GateProxy PROXY BODY ========
 */

/* DELEGATES TO xdc.runtime.GateNull */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_System_Module_GateProxy_Module__startupDone__S( void ) 
{
    return xdc_runtime_GateNull_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_System_Module_GateProxy_Object__create__S (
    xdc_Ptr __obj, 
    xdc_SizeT __osz,
    const xdc_Ptr __aa,
    const xdc_runtime_System_Module_GateProxy___ParamsPtr __paramsPtr,
    xdc_SizeT __psz,
    xdc_runtime_Error_Block *__eb)
{
    return xdc_runtime_GateNull_Object__create__S(__obj, __osz, __aa, (xdc_runtime_GateNull___ParamsPtr)__paramsPtr, sizeof(xdc_runtime_IGateProvider_Params), __eb);
}

/* create */
xdc_runtime_System_Module_GateProxy_Handle xdc_runtime_System_Module_GateProxy_create( const xdc_runtime_System_Module_GateProxy_Params *__prms, xdc_runtime_Error_Block *__eb )
{
    return (xdc_runtime_System_Module_GateProxy_Handle)xdc_runtime_System_Module_GateProxy_Object__create__S(0, 0, 0, (const xdc_UChar*)__prms, sizeof(xdc_runtime_System_Module_GateProxy_Params), __eb);
}

/* Object__delete__S */
void xdc_runtime_System_Module_GateProxy_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_GateNull_Object__delete__S(instp);
}

/* delete */
void xdc_runtime_System_Module_GateProxy_delete(xdc_runtime_System_Module_GateProxy_Handle *instp)
{
    xdc_runtime_System_Module_GateProxy_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_System_Module_GateProxy_Params__init__S( xdc_Ptr dst, const void *src, xdc_SizeT psz, xdc_SizeT isz )
{
    xdc_runtime_GateNull_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label *xdc_runtime_System_Module_GateProxy_Handle__label__S(xdc_Ptr obj, xdc_runtime_Types_Label *lab)
{
    return xdc_runtime_GateNull_Handle__label__S(obj, lab);
}

/* query__E */
xdc_Bool xdc_runtime_System_Module_GateProxy_query__E( xdc_Int qual )
{
    return xdc_runtime_GateNull_query(qual);
}

/* enter__E */
xdc_IArg xdc_runtime_System_Module_GateProxy_enter__E( xdc_runtime_System_Module_GateProxy_Handle __inst )
{
    return xdc_runtime_GateNull_enter((xdc_runtime_GateNull_Handle)__inst);
}

/* leave__E */
xdc_Void xdc_runtime_System_Module_GateProxy_leave__E( xdc_runtime_System_Module_GateProxy_Handle __inst, xdc_IArg key )
{
    xdc_runtime_GateNull_leave((xdc_runtime_GateNull_Handle)__inst, key);
}


/*
 * ======== xdc.runtime.System_SupportProxy PROXY BODY ========
 */

/* DELEGATES TO xdc.runtime.SysMin */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_System_SupportProxy_Module__startupDone__S( void ) 
{
    return xdc_runtime_SysMin_Module__startupDone__S();
}

/* abort__E */
xdc_Void xdc_runtime_System_SupportProxy_abort__E( xdc_CString str )
{
    xdc_runtime_SysMin_abort(str);
}

/* exit__E */
xdc_Void xdc_runtime_System_SupportProxy_exit__E( xdc_Int stat )
{
    xdc_runtime_SysMin_exit(stat);
}

/* flush__E */
xdc_Void xdc_runtime_System_SupportProxy_flush__E( void )
{
    xdc_runtime_SysMin_flush();
}

/* putch__E */
xdc_Void xdc_runtime_System_SupportProxy_putch__E( xdc_Char ch )
{
    xdc_runtime_SysMin_putch(ch);
}

/* ready__E */
xdc_Bool xdc_runtime_System_SupportProxy_ready__E( void )
{
    return xdc_runtime_SysMin_ready();
}


/*
 * ======== ti.sdo.utils.NameServerRemoteNull OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { ti_sdo_utils_NameServerRemoteNull_Object2__ s0; char c; } ti_sdo_utils_NameServerRemoteNull___S1;
#pragma DATA_SECTION(ti_sdo_utils_NameServerRemoteNull_Object__DESC__C, ".const:ti_sdo_utils_NameServerRemoteNull_Object__DESC__C");
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_utils_NameServerRemoteNull_Object__DESC__C = {
    (xdc_Ptr)0, /* fxnTab */
    &ti_sdo_utils_NameServerRemoteNull_Module__root__V.link, /* modLink */
    sizeof(ti_sdo_utils_NameServerRemoteNull___S1) - sizeof(ti_sdo_utils_NameServerRemoteNull_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(ti_sdo_utils_NameServerRemoteNull_Object2__), /* objSize */
    (xdc_Ptr)&ti_sdo_utils_NameServerRemoteNull_Object__PARAMS__C, /* prmsInit */
    sizeof(ti_sdo_utils_NameServerRemoteNull_Params), /* prmsSize */
};


/*
 * ======== xdc.runtime.GateNull OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { xdc_runtime_GateNull_Object2__ s0; char c; } xdc_runtime_GateNull___S1;
#pragma DATA_SECTION(xdc_runtime_GateNull_Object__DESC__C, ".const:xdc_runtime_GateNull_Object__DESC__C");
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_GateNull_Object__DESC__C = {
    (xdc_Ptr)&xdc_runtime_GateNull_Module__FXNS__C, /* fxnTab */
    &xdc_runtime_GateNull_Module__root__V.link, /* modLink */
    sizeof(xdc_runtime_GateNull___S1) - sizeof(xdc_runtime_GateNull_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(xdc_runtime_GateNull_Object2__), /* objSize */
    (xdc_Ptr)&xdc_runtime_GateNull_Object__PARAMS__C, /* prmsInit */
    sizeof(xdc_runtime_GateNull_Params), /* prmsSize */
};


/*
 * ======== xdc.runtime.HeapStd OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { xdc_runtime_HeapStd_Object2__ s0; char c; } xdc_runtime_HeapStd___S1;
#pragma DATA_SECTION(xdc_runtime_HeapStd_Object__DESC__C, ".const:xdc_runtime_HeapStd_Object__DESC__C");
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_HeapStd_Object__DESC__C = {
    (xdc_Ptr)&xdc_runtime_HeapStd_Module__FXNS__C, /* fxnTab */
    &xdc_runtime_HeapStd_Module__root__V.link, /* modLink */
    sizeof(xdc_runtime_HeapStd___S1) - sizeof(xdc_runtime_HeapStd_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(xdc_runtime_HeapStd_Object2__), /* objSize */
    (xdc_Ptr)&xdc_runtime_HeapStd_Object__PARAMS__C, /* prmsInit */
    sizeof(xdc_runtime_HeapStd_Params), /* prmsSize */
};


/*
 * ======== xdc.runtime.IHeap VIRTUAL FUNCTIONS ========
 */

/* create */
xdc_runtime_IHeap_Handle xdc_runtime_IHeap_create( xdc_runtime_IHeap_Module __mod, const xdc_runtime_IHeap_Params *__prms, xdc_runtime_Error_Block *__eb )
{
    return (xdc_runtime_IHeap_Handle) __mod->__sysp->__create(0, 0, 0, (const xdc_UChar*)__prms, sizeof (xdc_runtime_IHeap_Params), __eb);
}

/* delete */
void xdc_runtime_IHeap_delete( xdc_runtime_IHeap_Handle *instp )
{
    (*instp)->__fxns->__sysp->__delete(instp);
}


/*
 * ======== xdc.runtime.IGateProvider VIRTUAL FUNCTIONS ========
 */

/* create */
xdc_runtime_IGateProvider_Handle xdc_runtime_IGateProvider_create( xdc_runtime_IGateProvider_Module __mod, const xdc_runtime_IGateProvider_Params *__prms, xdc_runtime_Error_Block *__eb )
{
    return (xdc_runtime_IGateProvider_Handle) __mod->__sysp->__create(0, 0, 0, (const xdc_UChar*)__prms, sizeof (xdc_runtime_IGateProvider_Params), __eb);
}

/* delete */
void xdc_runtime_IGateProvider_delete( xdc_runtime_IGateProvider_Handle *instp )
{
    (*instp)->__fxns->__sysp->__delete(instp);
}


/*
 * ======== ti.catalog.arm.cortexm4.tiva.ce.Boot SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool ti_catalog_arm_cortexm4_tiva_ce_Boot_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== ti.sdo.utils.NameServerRemoteNull SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_utils_NameServerRemoteNull_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_utils_NameServerRemoteNull_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_utils_NameServerRemoteNull_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_utils_NameServerRemoteNull_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_utils_NameServerRemoteNull_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_utils_NameServerRemoteNull_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_utils_NameServerRemoteNull_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_utils_NameServerRemoteNull_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_utils_NameServerRemoteNull_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_utils_NameServerRemoteNull_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_utils_NameServerRemoteNull_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_utils_NameServerRemoteNull_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_utils_NameServerRemoteNull_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_utils_NameServerRemoteNull_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool ti_sdo_utils_NameServerRemoteNull_Module__startupDone__S( void )
{
    return 1;
}

/* Handle__label__S */
xdc_runtime_Types_Label *ti_sdo_utils_NameServerRemoteNull_Handle__label__S(xdc_Ptr obj, xdc_runtime_Types_Label *lab) 
{
    lab->handle = obj;
    lab->modId = 32794;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void ti_sdo_utils_NameServerRemoteNull_Params__init__S( xdc_Ptr prms, const void *src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &ti_sdo_utils_NameServerRemoteNull_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr ti_sdo_utils_NameServerRemoteNull_Object__get__S(xdc_Ptr oa, xdc_Int i)
{
    if (oa) {
        return ((ti_sdo_utils_NameServerRemoteNull_Object__ *)oa) + i;
    }

    if (ti_sdo_utils_NameServerRemoteNull_Object__count__C == 0) {
        return NULL;
    }

    return ((ti_sdo_utils_NameServerRemoteNull_Object__ *)ti_sdo_utils_NameServerRemoteNull_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr ti_sdo_utils_NameServerRemoteNull_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)ti_sdo_utils_NameServerRemoteNull_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&ti_sdo_utils_NameServerRemoteNull_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr ti_sdo_utils_NameServerRemoteNull_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&ti_sdo_utils_NameServerRemoteNull_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr ti_sdo_utils_NameServerRemoteNull_Object__create__S (
    xdc_Ptr __obj, 
    xdc_SizeT __osz,
    const xdc_Ptr __aa,
    const ti_sdo_utils_NameServerRemoteNull___ParamsPtr __paramsPtr,
    xdc_SizeT __psz,
    xdc_runtime_Error_Block *__eb)
{
    ti_sdo_utils_NameServerRemoteNull_Args__create *__args = __aa;
    ti_sdo_utils_NameServerRemoteNull_Params __prms;
    ti_sdo_utils_NameServerRemoteNull_Object *__newobj;

    /* common instance initialization */
    __newobj = xdc_runtime_Core_createObject__I(&ti_sdo_utils_NameServerRemoteNull_Object__DESC__C, __obj, &__prms, (xdc_Ptr)__paramsPtr, sizeof(ti_sdo_utils_NameServerRemoteNull_Params), __eb);
    if (__newobj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    ti_sdo_utils_NameServerRemoteNull_Instance_init__E(__newobj, __args->procId, &__prms);
    return __newobj;
}

/* create */
ti_sdo_utils_NameServerRemoteNull_Handle ti_sdo_utils_NameServerRemoteNull_create( xdc_UInt16 procId, const ti_sdo_utils_NameServerRemoteNull_Params *__paramsPtr, xdc_runtime_Error_Block *__eb )
{
    ti_sdo_utils_NameServerRemoteNull_Params __prms;
    ti_sdo_utils_NameServerRemoteNull_Object *__newobj;

    /* common instance initialization */
    __newobj = xdc_runtime_Core_createObject__I(&ti_sdo_utils_NameServerRemoteNull_Object__DESC__C, 0, &__prms, (xdc_Ptr)__paramsPtr, sizeof(ti_sdo_utils_NameServerRemoteNull_Params), __eb);
    if (__newobj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    ti_sdo_utils_NameServerRemoteNull_Instance_init__E(__newobj, procId, &__prms);
    return __newobj;
}

/* construct */
void ti_sdo_utils_NameServerRemoteNull_construct(ti_sdo_utils_NameServerRemoteNull_Struct *__obj, xdc_UInt16 procId, const ti_sdo_utils_NameServerRemoteNull_Params *__paramsPtr )
{
    ti_sdo_utils_NameServerRemoteNull_Params __prms;

    /* common instance initialization */
    xdc_runtime_Core_constructObject__I(&ti_sdo_utils_NameServerRemoteNull_Object__DESC__C, __obj, &__prms, (xdc_Ptr)__paramsPtr, sizeof(ti_sdo_utils_NameServerRemoteNull_Params), NULL);
    /* module-specific initialization */
    ti_sdo_utils_NameServerRemoteNull_Instance_init__E((xdc_Ptr)__obj, procId, &__prms);
}

/* Object__destruct__S */
xdc_Void ti_sdo_utils_NameServerRemoteNull_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_utils_NameServerRemoteNull_Object__DESC__C, obj, NULL, -1, TRUE);
}

/* destruct */
void ti_sdo_utils_NameServerRemoteNull_destruct(ti_sdo_utils_NameServerRemoteNull_Struct *obj)
{
    ti_sdo_utils_NameServerRemoteNull_Object__destruct__S(obj);
}

/* Object__delete__S */
xdc_Void ti_sdo_utils_NameServerRemoteNull_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_utils_NameServerRemoteNull_Object__DESC__C, *((ti_sdo_utils_NameServerRemoteNull_Object**)instp), NULL, -1, FALSE);
    *((ti_sdo_utils_NameServerRemoteNull_Handle*)instp) = NULL;
}

/* delete */
void ti_sdo_utils_NameServerRemoteNull_delete(ti_sdo_utils_NameServerRemoteNull_Handle *instp)
{
    ti_sdo_utils_NameServerRemoteNull_Object__delete__S(instp);
}


/*
 * ======== xdc.runtime.Assert SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Assert_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.Core SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Core_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.Defaults SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Defaults_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.Diags SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Diags_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.Error SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Error_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.Gate SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Gate_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.GateNull SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_GateNull_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_GateNull_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_GateNull_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_GateNull_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_GateNull_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_GateNull_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_GateNull_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_GateNull_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_GateNull_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_GateNull_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_GateNull_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_GateNull_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_GateNull_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_GateNull_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_GateNull_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_GateNull_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_GateNull_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_GateNull_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool xdc_runtime_GateNull_Module__startupDone__S( void )
{
    return 1;
}

/* Handle__label__S */
xdc_runtime_Types_Label *xdc_runtime_GateNull_Handle__label__S(xdc_Ptr obj, xdc_runtime_Types_Label *lab) 
{
    lab->handle = obj;
    lab->modId = 32776;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void xdc_runtime_GateNull_Params__init__S( xdc_Ptr prms, const void *src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &xdc_runtime_GateNull_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr xdc_runtime_GateNull_Object__get__S(xdc_Ptr oa, xdc_Int i)
{
    if (oa) {
        return ((xdc_runtime_GateNull_Object__ *)oa) + i;
    }

    if (xdc_runtime_GateNull_Object__count__C == 0) {
        return NULL;
    }

    return ((xdc_runtime_GateNull_Object__ *)xdc_runtime_GateNull_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr xdc_runtime_GateNull_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)xdc_runtime_GateNull_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&xdc_runtime_GateNull_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr xdc_runtime_GateNull_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&xdc_runtime_GateNull_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr xdc_runtime_GateNull_Object__create__S (
    xdc_Ptr __obj, 
    xdc_SizeT __osz,
    const xdc_Ptr __aa,
    const xdc_runtime_GateNull___ParamsPtr __paramsPtr,
    xdc_SizeT __psz,
    xdc_runtime_Error_Block *__eb)
{
    xdc_runtime_GateNull_Params __prms;
    xdc_runtime_GateNull_Object *__newobj;

    /* common instance initialization */
    __newobj = xdc_runtime_Core_createObject__I(&xdc_runtime_GateNull_Object__DESC__C, __obj, &__prms, (xdc_Ptr)__paramsPtr, sizeof(xdc_runtime_GateNull_Params), __eb);
    if (__newobj == NULL) {
        return NULL;
    }

    return __newobj;
}

/* create */
xdc_runtime_GateNull_Handle xdc_runtime_GateNull_create( const xdc_runtime_GateNull_Params *__paramsPtr, xdc_runtime_Error_Block *__eb )
{
    xdc_runtime_GateNull_Params __prms;
    xdc_runtime_GateNull_Object *__newobj;

    /* common instance initialization */
    __newobj = xdc_runtime_Core_createObject__I(&xdc_runtime_GateNull_Object__DESC__C, 0, &__prms, (xdc_Ptr)__paramsPtr, sizeof(xdc_runtime_GateNull_Params), __eb);
    if (__newobj == NULL) {
        return NULL;
    }

    return __newobj;
}

/* construct */
void xdc_runtime_GateNull_construct(xdc_runtime_GateNull_Struct *__obj, const xdc_runtime_GateNull_Params *__paramsPtr )
{
    xdc_runtime_GateNull_Params __prms;

    /* common instance initialization */
    xdc_runtime_Core_constructObject__I(&xdc_runtime_GateNull_Object__DESC__C, __obj, &__prms, (xdc_Ptr)__paramsPtr, sizeof(xdc_runtime_GateNull_Params), NULL);
}

/* Object__destruct__S */
xdc_Void xdc_runtime_GateNull_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_GateNull_Object__DESC__C, obj, NULL, -1, TRUE);
}

/* destruct */
void xdc_runtime_GateNull_destruct(xdc_runtime_GateNull_Struct *obj)
{
    xdc_runtime_GateNull_Object__destruct__S(obj);
}

/* Object__delete__S */
xdc_Void xdc_runtime_GateNull_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_GateNull_Object__DESC__C, *((xdc_runtime_GateNull_Object**)instp), NULL, -1, FALSE);
    *((xdc_runtime_GateNull_Handle*)instp) = NULL;
}

/* delete */
void xdc_runtime_GateNull_delete(xdc_runtime_GateNull_Handle *instp)
{
    xdc_runtime_GateNull_Object__delete__S(instp);
}


/*
 * ======== xdc.runtime.HeapStd SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_HeapStd_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_HeapStd_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_HeapStd_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_HeapStd_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_HeapStd_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_HeapStd_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_HeapStd_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_HeapStd_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_HeapStd_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_HeapStd_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_HeapStd_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_HeapStd_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_HeapStd_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_HeapStd_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_HeapStd_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_HeapStd_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_HeapStd_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_HeapStd_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool xdc_runtime_HeapStd_Module__startupDone__S( void )
{
    return 1;
}

/* Handle__label__S */
xdc_runtime_Types_Label *xdc_runtime_HeapStd_Handle__label__S(xdc_Ptr obj, xdc_runtime_Types_Label *lab) 
{
    lab->handle = obj;
    lab->modId = 32780;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void xdc_runtime_HeapStd_Params__init__S( xdc_Ptr prms, const void *src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &xdc_runtime_HeapStd_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr xdc_runtime_HeapStd_Object__get__S(xdc_Ptr oa, xdc_Int i)
{
    if (oa) {
        return ((xdc_runtime_HeapStd_Object__ *)oa) + i;
    }

    if (xdc_runtime_HeapStd_Object__count__C == 0) {
        return NULL;
    }

    return ((xdc_runtime_HeapStd_Object__ *)xdc_runtime_HeapStd_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr xdc_runtime_HeapStd_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)xdc_runtime_HeapStd_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&xdc_runtime_HeapStd_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr xdc_runtime_HeapStd_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&xdc_runtime_HeapStd_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr xdc_runtime_HeapStd_Object__create__S (
    xdc_Ptr __obj, 
    xdc_SizeT __osz,
    const xdc_Ptr __aa,
    const xdc_runtime_HeapStd___ParamsPtr __paramsPtr,
    xdc_SizeT __psz,
    xdc_runtime_Error_Block *__eb)
{
    xdc_runtime_HeapStd_Params __prms;
    xdc_runtime_HeapStd_Object *__newobj;
    int iStat;

    /* common instance initialization */
    __newobj = xdc_runtime_Core_createObject__I(&xdc_runtime_HeapStd_Object__DESC__C, __obj, &__prms, (xdc_Ptr)__paramsPtr, sizeof(xdc_runtime_HeapStd_Params), __eb);
    if (__newobj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = xdc_runtime_HeapStd_Instance_init__E(__newobj, &__prms, __eb);
    if (xdc_runtime_Error_check(__eb)) {
        xdc_runtime_Core_deleteObject__I(&xdc_runtime_HeapStd_Object__DESC__C, __newobj, NULL, iStat, (xdc_Bool)(__obj != NULL));
        return NULL;
    }

    return __newobj;
}

/* create */
xdc_runtime_HeapStd_Handle xdc_runtime_HeapStd_create( const xdc_runtime_HeapStd_Params *__paramsPtr, xdc_runtime_Error_Block *__eb )
{
    xdc_runtime_HeapStd_Params __prms;
    xdc_runtime_HeapStd_Object *__newobj;
    int iStat;

    /* common instance initialization */
    __newobj = xdc_runtime_Core_createObject__I(&xdc_runtime_HeapStd_Object__DESC__C, 0, &__prms, (xdc_Ptr)__paramsPtr, sizeof(xdc_runtime_HeapStd_Params), __eb);
    if (__newobj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = xdc_runtime_HeapStd_Instance_init__E(__newobj, &__prms, __eb);
    if (xdc_runtime_Error_check(__eb)) {
        xdc_runtime_Core_deleteObject__I(&xdc_runtime_HeapStd_Object__DESC__C, __newobj, NULL, iStat, 0);
        return NULL;
    }

    return __newobj;
}

/* construct */
void xdc_runtime_HeapStd_construct(xdc_runtime_HeapStd_Struct *__obj, const xdc_runtime_HeapStd_Params *__paramsPtr, xdc_runtime_Error_Block *__eb )
{
    xdc_runtime_HeapStd_Params __prms;
    int iStat;

    /* common instance initialization */
    xdc_runtime_Core_constructObject__I(&xdc_runtime_HeapStd_Object__DESC__C, __obj, &__prms, (xdc_Ptr)__paramsPtr, sizeof(xdc_runtime_HeapStd_Params), __eb);
    /* module-specific initialization */
    iStat = xdc_runtime_HeapStd_Instance_init__E((xdc_Ptr)__obj, &__prms, __eb);
    if (xdc_runtime_Error_check(__eb)) {
        xdc_runtime_Core_deleteObject__I(&xdc_runtime_HeapStd_Object__DESC__C, (xdc_Ptr)__obj, NULL, iStat, 1);
    }

}

/* Object__destruct__S */
xdc_Void xdc_runtime_HeapStd_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_HeapStd_Object__DESC__C, obj, NULL, 0, TRUE);
}

/* destruct */
void xdc_runtime_HeapStd_destruct(xdc_runtime_HeapStd_Struct *obj)
{
    xdc_runtime_HeapStd_Object__destruct__S(obj);
}

/* Object__delete__S */
xdc_Void xdc_runtime_HeapStd_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_HeapStd_Object__DESC__C, *((xdc_runtime_HeapStd_Object**)instp), NULL, 0, FALSE);
    *((xdc_runtime_HeapStd_Handle*)instp) = NULL;
}

/* delete */
void xdc_runtime_HeapStd_delete(xdc_runtime_HeapStd_Handle *instp)
{
    xdc_runtime_HeapStd_Object__delete__S(instp);
}


/*
 * ======== xdc.runtime.Log SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Log_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.Main SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Main_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.Main_Module_GateProxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_Main_Module_GateProxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_Main_Module_GateProxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_Main_Module_GateProxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_Main_Module_GateProxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_Main_Module_GateProxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_Main_Module_GateProxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_Main_Module_GateProxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_Main_Module_GateProxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_Main_Module_GateProxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_Main_Module_GateProxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_Main_Module_GateProxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_Main_Module_GateProxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_Main_Module_GateProxy_Module_GateProxy_query

xdc_Bool xdc_runtime_Main_Module_GateProxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_Main_Module_GateProxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&xdc_runtime_GateNull_Module__FXNS__C;
}



/*
 * ======== xdc.runtime.Memory SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Memory_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.Memory_HeapProxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_Memory_HeapProxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_Memory_HeapProxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_Memory_HeapProxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_Memory_HeapProxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_Memory_HeapProxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_Memory_HeapProxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_Memory_HeapProxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_Memory_HeapProxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_Memory_HeapProxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_Memory_HeapProxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_Memory_HeapProxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_Memory_HeapProxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_Memory_HeapProxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_Memory_HeapProxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_Memory_HeapProxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_Memory_HeapProxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_Memory_HeapProxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_Memory_HeapProxy_Module_GateProxy_query

xdc_Bool xdc_runtime_Memory_HeapProxy_Proxy__abstract__S( void )
{
    return 1;
}
xdc_Ptr xdc_runtime_Memory_HeapProxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&xdc_runtime_HeapStd_Module__FXNS__C;
}



/*
 * ======== xdc.runtime.Registry SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Registry_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.Startup SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Startup_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== xdc.runtime.SysMin SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_SysMin_Module__startupDone__S( void )
{
    return xdc_runtime_SysMin_Module__startupDone__F();
}



/*
 * ======== xdc.runtime.System SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_System_Module__startupDone__S( void )
{
    return xdc_runtime_System_Module__startupDone__F();
}



/*
 * ======== xdc.runtime.System_Module_GateProxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_System_Module_GateProxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_System_Module_GateProxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_System_Module_GateProxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_System_Module_GateProxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_System_Module_GateProxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_System_Module_GateProxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_System_Module_GateProxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_System_Module_GateProxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_System_Module_GateProxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_System_Module_GateProxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_System_Module_GateProxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_System_Module_GateProxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_System_Module_GateProxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_System_Module_GateProxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_System_Module_GateProxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_System_Module_GateProxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_System_Module_GateProxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_System_Module_GateProxy_Module_GateProxy_query

xdc_Bool xdc_runtime_System_Module_GateProxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_System_Module_GateProxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&xdc_runtime_GateNull_Module__FXNS__C;
}



/*
 * ======== xdc.runtime.System_SupportProxy SYSTEM FUNCTIONS ========
 */


xdc_Bool xdc_runtime_System_SupportProxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_System_SupportProxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&xdc_runtime_SysMin_Module__FXNS__C;
}


/*
 * ======== xdc.runtime.Text SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Text_Module__startupDone__S( void )
{
    return 1;
}



/*
 * ======== INITIALIZATION ENTRY POINT ========
 */

extern int __xdc__init(void);
#ifdef __GNUC__
#ifndef __TI_COMPILER_VERSION__
    __attribute__ ((externally_visible))
#endif
#endif
__FAR__ int (* volatile __xdc__init__addr)(void) = &__xdc__init;


/*
 * ======== PROGRAM GLOBALS ========
 */

