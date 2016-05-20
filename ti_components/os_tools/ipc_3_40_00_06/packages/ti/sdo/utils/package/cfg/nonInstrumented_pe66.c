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
const __T1_xdc_runtime_Text_charTab xdc_runtime_Text_charTab__A[3988];

/* --> xdc_runtime_Text_nodeTab__A */
const __T1_xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__A[21];


/*
 * ======== xdc.cfg.Program TEMPLATE ========
 */

/*
 *  ======== __ASM__ ========
 *  Define absolute path prefix for this executable's
 *  configuration generated files.
 */
xdc__META(__ASM__, "@(#)__ASM__ = /datalocal1/ti_components/os_tools/ipc_3_40_00_06/packages/ti/sdo/utils/package/cfg/nonInstrumented_pe66");

/*
 *  ======== __ISA__ ========
 *  Define the ISA of this executable.  This symbol is used by platform
 *  specific "exec" commands that support more than one ISA; e.g., gdb
 */
xdc__META(__ISA__, "@(#)__ISA__ = 66");

/*
 *  ======== __PLAT__ ========
 *  Define the name of the platform that can run this executable.  This
 *  symbol is used by platform independent "exec" commands
 */
xdc__META(__PLAT__, "@(#)__PLAT__ = ti.platforms.simTCI6616");

/*
 *  ======== __TARG__ ========
 *  Define the name of the target used to build this executable.
 */
xdc__META(__TARG__, "@(#)__TARG__ = ti.targets.elf.C66");

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
    xdc_String stack[4];
    xdc_runtime_Text_visitRope2__I(rope, visFxn, visState, stack);
}


/*
 * ======== ti.sdo.utils.Build TEMPLATE ========
 */


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
__FAR__ const CT__ti_sdo_utils_NameServerRemoteNull_Module__id ti_sdo_utils_NameServerRemoteNull_Module__id__C = (xdc_Bits16)0x8014;

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
__FAR__ const CT__xdc_runtime_Assert_E_assertFailed xdc_runtime_Assert_E_assertFailed__C = (((xdc_runtime_Error_Id)2648) << 16 | 0);


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
__FAR__ const CT__xdc_runtime_Error_E_generic xdc_runtime_Error_E_generic__C = (((xdc_runtime_Error_Id)2670) << 16 | 0);

/* E_memory__C */
#pragma DATA_SECTION(xdc_runtime_Error_E_memory__C, ".const:xdc_runtime_Error_E_memory__C");
__FAR__ const CT__xdc_runtime_Error_E_memory xdc_runtime_Error_E_memory__C = (((xdc_runtime_Error_Id)2674) << 16 | 0);

/* E_msgCode__C */
#pragma DATA_SECTION(xdc_runtime_Error_E_msgCode__C, ".const:xdc_runtime_Error_E_msgCode__C");
__FAR__ const CT__xdc_runtime_Error_E_msgCode xdc_runtime_Error_E_msgCode__C = (((xdc_runtime_Error_Id)2708) << 16 | 0);

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
__FAR__ const CT__xdc_runtime_HeapStd_E_noRTSMemory xdc_runtime_HeapStd_E_noRTSMemory__C = (((xdc_runtime_Error_Id)2793) << 16 | 0);

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
__FAR__ const CT__xdc_runtime_Log_L_construct xdc_runtime_Log_L_construct__C = (((xdc_runtime_Log_Event)3654) << 16 | 4);

/* L_create__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_create__C, ".const:xdc_runtime_Log_L_create__C");
__FAR__ const CT__xdc_runtime_Log_L_create xdc_runtime_Log_L_create__C = (((xdc_runtime_Log_Event)3678) << 16 | 4);

/* L_destruct__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_destruct__C, ".const:xdc_runtime_Log_L_destruct__C");
__FAR__ const CT__xdc_runtime_Log_L_destruct xdc_runtime_Log_L_destruct__C = (((xdc_runtime_Log_Event)3699) << 16 | 4);

/* L_delete__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_delete__C, ".const:xdc_runtime_Log_L_delete__C");
__FAR__ const CT__xdc_runtime_Log_L_delete xdc_runtime_Log_L_delete__C = (((xdc_runtime_Log_Event)3718) << 16 | 4);

/* L_error__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_error__C, ".const:xdc_runtime_Log_L_error__C");
__FAR__ const CT__xdc_runtime_Log_L_error xdc_runtime_Log_L_error__C = (((xdc_runtime_Log_Event)3735) << 16 | 192);

/* L_warning__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_warning__C, ".const:xdc_runtime_Log_L_warning__C");
__FAR__ const CT__xdc_runtime_Log_L_warning xdc_runtime_Log_L_warning__C = (((xdc_runtime_Log_Event)3749) << 16 | 224);

/* L_info__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_info__C, ".const:xdc_runtime_Log_L_info__C");
__FAR__ const CT__xdc_runtime_Log_L_info xdc_runtime_Log_L_info__C = (((xdc_runtime_Log_Event)3765) << 16 | 16384);

/* L_start__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_start__C, ".const:xdc_runtime_Log_L_start__C");
__FAR__ const CT__xdc_runtime_Log_L_start xdc_runtime_Log_L_start__C = (((xdc_runtime_Log_Event)3772) << 16 | 32768);

/* L_stop__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_stop__C, ".const:xdc_runtime_Log_L_stop__C");
__FAR__ const CT__xdc_runtime_Log_L_stop xdc_runtime_Log_L_stop__C = (((xdc_runtime_Log_Event)3783) << 16 | 32768);

/* L_startInstance__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_startInstance__C, ".const:xdc_runtime_Log_L_startInstance__C");
__FAR__ const CT__xdc_runtime_Log_L_startInstance xdc_runtime_Log_L_startInstance__C = (((xdc_runtime_Log_Event)3793) << 16 | 32768);

/* L_stopInstance__C */
#pragma DATA_SECTION(xdc_runtime_Log_L_stopInstance__C, ".const:xdc_runtime_Log_L_stopInstance__C");
__FAR__ const CT__xdc_runtime_Log_L_stopInstance xdc_runtime_Log_L_stopInstance__C = (((xdc_runtime_Log_Event)3812) << 16 | 32768);


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
__FAR__ const CT__xdc_runtime_Startup_firstFxns xdc_runtime_Startup_firstFxns__C = {0, 0};

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
const __T1_xdc_runtime_Text_charTab xdc_runtime_Text_charTab__A[3988] = {
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
    (xdc_Char)0x69,  /* [402] */
    (xdc_Char)0x6e,  /* [403] */
    (xdc_Char)0x76,  /* [404] */
    (xdc_Char)0x61,  /* [405] */
    (xdc_Char)0x6c,  /* [406] */
    (xdc_Char)0x69,  /* [407] */
    (xdc_Char)0x64,  /* [408] */
    (xdc_Char)0x45,  /* [409] */
    (xdc_Char)0x76,  /* [410] */
    (xdc_Char)0x65,  /* [411] */
    (xdc_Char)0x6e,  /* [412] */
    (xdc_Char)0x74,  /* [413] */
    (xdc_Char)0x49,  /* [414] */
    (xdc_Char)0x64,  /* [415] */
    (xdc_Char)0x3a,  /* [416] */
    (xdc_Char)0x20,  /* [417] */
    (xdc_Char)0x49,  /* [418] */
    (xdc_Char)0x6e,  /* [419] */
    (xdc_Char)0x76,  /* [420] */
    (xdc_Char)0x61,  /* [421] */
    (xdc_Char)0x6c,  /* [422] */
    (xdc_Char)0x69,  /* [423] */
    (xdc_Char)0x64,  /* [424] */
    (xdc_Char)0x20,  /* [425] */
    (xdc_Char)0x65,  /* [426] */
    (xdc_Char)0x76,  /* [427] */
    (xdc_Char)0x65,  /* [428] */
    (xdc_Char)0x6e,  /* [429] */
    (xdc_Char)0x74,  /* [430] */
    (xdc_Char)0x20,  /* [431] */
    (xdc_Char)0x49,  /* [432] */
    (xdc_Char)0x64,  /* [433] */
    (xdc_Char)0x20,  /* [434] */
    (xdc_Char)0x73,  /* [435] */
    (xdc_Char)0x70,  /* [436] */
    (xdc_Char)0x65,  /* [437] */
    (xdc_Char)0x63,  /* [438] */
    (xdc_Char)0x69,  /* [439] */
    (xdc_Char)0x66,  /* [440] */
    (xdc_Char)0x69,  /* [441] */
    (xdc_Char)0x65,  /* [442] */
    (xdc_Char)0x64,  /* [443] */
    (xdc_Char)0x0,  /* [444] */
    (xdc_Char)0x41,  /* [445] */
    (xdc_Char)0x5f,  /* [446] */
    (xdc_Char)0x63,  /* [447] */
    (xdc_Char)0x6c,  /* [448] */
    (xdc_Char)0x6f,  /* [449] */
    (xdc_Char)0x63,  /* [450] */
    (xdc_Char)0x6b,  /* [451] */
    (xdc_Char)0x44,  /* [452] */
    (xdc_Char)0x69,  /* [453] */
    (xdc_Char)0x73,  /* [454] */
    (xdc_Char)0x61,  /* [455] */
    (xdc_Char)0x62,  /* [456] */
    (xdc_Char)0x6c,  /* [457] */
    (xdc_Char)0x65,  /* [458] */
    (xdc_Char)0x64,  /* [459] */
    (xdc_Char)0x3a,  /* [460] */
    (xdc_Char)0x20,  /* [461] */
    (xdc_Char)0x43,  /* [462] */
    (xdc_Char)0x61,  /* [463] */
    (xdc_Char)0x6e,  /* [464] */
    (xdc_Char)0x6e,  /* [465] */
    (xdc_Char)0x6f,  /* [466] */
    (xdc_Char)0x74,  /* [467] */
    (xdc_Char)0x20,  /* [468] */
    (xdc_Char)0x63,  /* [469] */
    (xdc_Char)0x72,  /* [470] */
    (xdc_Char)0x65,  /* [471] */
    (xdc_Char)0x61,  /* [472] */
    (xdc_Char)0x74,  /* [473] */
    (xdc_Char)0x65,  /* [474] */
    (xdc_Char)0x20,  /* [475] */
    (xdc_Char)0x61,  /* [476] */
    (xdc_Char)0x20,  /* [477] */
    (xdc_Char)0x63,  /* [478] */
    (xdc_Char)0x6c,  /* [479] */
    (xdc_Char)0x6f,  /* [480] */
    (xdc_Char)0x63,  /* [481] */
    (xdc_Char)0x6b,  /* [482] */
    (xdc_Char)0x20,  /* [483] */
    (xdc_Char)0x69,  /* [484] */
    (xdc_Char)0x6e,  /* [485] */
    (xdc_Char)0x73,  /* [486] */
    (xdc_Char)0x74,  /* [487] */
    (xdc_Char)0x61,  /* [488] */
    (xdc_Char)0x6e,  /* [489] */
    (xdc_Char)0x63,  /* [490] */
    (xdc_Char)0x65,  /* [491] */
    (xdc_Char)0x20,  /* [492] */
    (xdc_Char)0x77,  /* [493] */
    (xdc_Char)0x68,  /* [494] */
    (xdc_Char)0x65,  /* [495] */
    (xdc_Char)0x6e,  /* [496] */
    (xdc_Char)0x20,  /* [497] */
    (xdc_Char)0x42,  /* [498] */
    (xdc_Char)0x49,  /* [499] */
    (xdc_Char)0x4f,  /* [500] */
    (xdc_Char)0x53,  /* [501] */
    (xdc_Char)0x2e,  /* [502] */
    (xdc_Char)0x63,  /* [503] */
    (xdc_Char)0x6c,  /* [504] */
    (xdc_Char)0x6f,  /* [505] */
    (xdc_Char)0x63,  /* [506] */
    (xdc_Char)0x6b,  /* [507] */
    (xdc_Char)0x45,  /* [508] */
    (xdc_Char)0x6e,  /* [509] */
    (xdc_Char)0x61,  /* [510] */
    (xdc_Char)0x62,  /* [511] */
    (xdc_Char)0x6c,  /* [512] */
    (xdc_Char)0x65,  /* [513] */
    (xdc_Char)0x64,  /* [514] */
    (xdc_Char)0x20,  /* [515] */
    (xdc_Char)0x69,  /* [516] */
    (xdc_Char)0x73,  /* [517] */
    (xdc_Char)0x20,  /* [518] */
    (xdc_Char)0x66,  /* [519] */
    (xdc_Char)0x61,  /* [520] */
    (xdc_Char)0x6c,  /* [521] */
    (xdc_Char)0x73,  /* [522] */
    (xdc_Char)0x65,  /* [523] */
    (xdc_Char)0x2e,  /* [524] */
    (xdc_Char)0x0,  /* [525] */
    (xdc_Char)0x41,  /* [526] */
    (xdc_Char)0x5f,  /* [527] */
    (xdc_Char)0x62,  /* [528] */
    (xdc_Char)0x61,  /* [529] */
    (xdc_Char)0x64,  /* [530] */
    (xdc_Char)0x54,  /* [531] */
    (xdc_Char)0x68,  /* [532] */
    (xdc_Char)0x72,  /* [533] */
    (xdc_Char)0x65,  /* [534] */
    (xdc_Char)0x61,  /* [535] */
    (xdc_Char)0x64,  /* [536] */
    (xdc_Char)0x54,  /* [537] */
    (xdc_Char)0x79,  /* [538] */
    (xdc_Char)0x70,  /* [539] */
    (xdc_Char)0x65,  /* [540] */
    (xdc_Char)0x3a,  /* [541] */
    (xdc_Char)0x20,  /* [542] */
    (xdc_Char)0x43,  /* [543] */
    (xdc_Char)0x61,  /* [544] */
    (xdc_Char)0x6e,  /* [545] */
    (xdc_Char)0x6e,  /* [546] */
    (xdc_Char)0x6f,  /* [547] */
    (xdc_Char)0x74,  /* [548] */
    (xdc_Char)0x20,  /* [549] */
    (xdc_Char)0x63,  /* [550] */
    (xdc_Char)0x72,  /* [551] */
    (xdc_Char)0x65,  /* [552] */
    (xdc_Char)0x61,  /* [553] */
    (xdc_Char)0x74,  /* [554] */
    (xdc_Char)0x65,  /* [555] */
    (xdc_Char)0x2f,  /* [556] */
    (xdc_Char)0x64,  /* [557] */
    (xdc_Char)0x65,  /* [558] */
    (xdc_Char)0x6c,  /* [559] */
    (xdc_Char)0x65,  /* [560] */
    (xdc_Char)0x74,  /* [561] */
    (xdc_Char)0x65,  /* [562] */
    (xdc_Char)0x20,  /* [563] */
    (xdc_Char)0x61,  /* [564] */
    (xdc_Char)0x20,  /* [565] */
    (xdc_Char)0x43,  /* [566] */
    (xdc_Char)0x6c,  /* [567] */
    (xdc_Char)0x6f,  /* [568] */
    (xdc_Char)0x63,  /* [569] */
    (xdc_Char)0x6b,  /* [570] */
    (xdc_Char)0x20,  /* [571] */
    (xdc_Char)0x66,  /* [572] */
    (xdc_Char)0x72,  /* [573] */
    (xdc_Char)0x6f,  /* [574] */
    (xdc_Char)0x6d,  /* [575] */
    (xdc_Char)0x20,  /* [576] */
    (xdc_Char)0x48,  /* [577] */
    (xdc_Char)0x77,  /* [578] */
    (xdc_Char)0x69,  /* [579] */
    (xdc_Char)0x20,  /* [580] */
    (xdc_Char)0x6f,  /* [581] */
    (xdc_Char)0x72,  /* [582] */
    (xdc_Char)0x20,  /* [583] */
    (xdc_Char)0x53,  /* [584] */
    (xdc_Char)0x77,  /* [585] */
    (xdc_Char)0x69,  /* [586] */
    (xdc_Char)0x20,  /* [587] */
    (xdc_Char)0x74,  /* [588] */
    (xdc_Char)0x68,  /* [589] */
    (xdc_Char)0x72,  /* [590] */
    (xdc_Char)0x65,  /* [591] */
    (xdc_Char)0x61,  /* [592] */
    (xdc_Char)0x64,  /* [593] */
    (xdc_Char)0x2e,  /* [594] */
    (xdc_Char)0x0,  /* [595] */
    (xdc_Char)0x41,  /* [596] */
    (xdc_Char)0x5f,  /* [597] */
    (xdc_Char)0x6e,  /* [598] */
    (xdc_Char)0x75,  /* [599] */
    (xdc_Char)0x6c,  /* [600] */
    (xdc_Char)0x6c,  /* [601] */
    (xdc_Char)0x45,  /* [602] */
    (xdc_Char)0x76,  /* [603] */
    (xdc_Char)0x65,  /* [604] */
    (xdc_Char)0x6e,  /* [605] */
    (xdc_Char)0x74,  /* [606] */
    (xdc_Char)0x4d,  /* [607] */
    (xdc_Char)0x61,  /* [608] */
    (xdc_Char)0x73,  /* [609] */
    (xdc_Char)0x6b,  /* [610] */
    (xdc_Char)0x73,  /* [611] */
    (xdc_Char)0x3a,  /* [612] */
    (xdc_Char)0x20,  /* [613] */
    (xdc_Char)0x6f,  /* [614] */
    (xdc_Char)0x72,  /* [615] */
    (xdc_Char)0x4d,  /* [616] */
    (xdc_Char)0x61,  /* [617] */
    (xdc_Char)0x73,  /* [618] */
    (xdc_Char)0x6b,  /* [619] */
    (xdc_Char)0x20,  /* [620] */
    (xdc_Char)0x61,  /* [621] */
    (xdc_Char)0x6e,  /* [622] */
    (xdc_Char)0x64,  /* [623] */
    (xdc_Char)0x20,  /* [624] */
    (xdc_Char)0x61,  /* [625] */
    (xdc_Char)0x6e,  /* [626] */
    (xdc_Char)0x64,  /* [627] */
    (xdc_Char)0x4d,  /* [628] */
    (xdc_Char)0x61,  /* [629] */
    (xdc_Char)0x73,  /* [630] */
    (xdc_Char)0x6b,  /* [631] */
    (xdc_Char)0x20,  /* [632] */
    (xdc_Char)0x61,  /* [633] */
    (xdc_Char)0x72,  /* [634] */
    (xdc_Char)0x65,  /* [635] */
    (xdc_Char)0x20,  /* [636] */
    (xdc_Char)0x6e,  /* [637] */
    (xdc_Char)0x75,  /* [638] */
    (xdc_Char)0x6c,  /* [639] */
    (xdc_Char)0x6c,  /* [640] */
    (xdc_Char)0x2e,  /* [641] */
    (xdc_Char)0x0,  /* [642] */
    (xdc_Char)0x41,  /* [643] */
    (xdc_Char)0x5f,  /* [644] */
    (xdc_Char)0x6e,  /* [645] */
    (xdc_Char)0x75,  /* [646] */
    (xdc_Char)0x6c,  /* [647] */
    (xdc_Char)0x6c,  /* [648] */
    (xdc_Char)0x45,  /* [649] */
    (xdc_Char)0x76,  /* [650] */
    (xdc_Char)0x65,  /* [651] */
    (xdc_Char)0x6e,  /* [652] */
    (xdc_Char)0x74,  /* [653] */
    (xdc_Char)0x49,  /* [654] */
    (xdc_Char)0x64,  /* [655] */
    (xdc_Char)0x3a,  /* [656] */
    (xdc_Char)0x20,  /* [657] */
    (xdc_Char)0x70,  /* [658] */
    (xdc_Char)0x6f,  /* [659] */
    (xdc_Char)0x73,  /* [660] */
    (xdc_Char)0x74,  /* [661] */
    (xdc_Char)0x65,  /* [662] */
    (xdc_Char)0x64,  /* [663] */
    (xdc_Char)0x20,  /* [664] */
    (xdc_Char)0x65,  /* [665] */
    (xdc_Char)0x76,  /* [666] */
    (xdc_Char)0x65,  /* [667] */
    (xdc_Char)0x6e,  /* [668] */
    (xdc_Char)0x74,  /* [669] */
    (xdc_Char)0x49,  /* [670] */
    (xdc_Char)0x64,  /* [671] */
    (xdc_Char)0x20,  /* [672] */
    (xdc_Char)0x69,  /* [673] */
    (xdc_Char)0x73,  /* [674] */
    (xdc_Char)0x20,  /* [675] */
    (xdc_Char)0x6e,  /* [676] */
    (xdc_Char)0x75,  /* [677] */
    (xdc_Char)0x6c,  /* [678] */
    (xdc_Char)0x6c,  /* [679] */
    (xdc_Char)0x2e,  /* [680] */
    (xdc_Char)0x0,  /* [681] */
    (xdc_Char)0x41,  /* [682] */
    (xdc_Char)0x5f,  /* [683] */
    (xdc_Char)0x65,  /* [684] */
    (xdc_Char)0x76,  /* [685] */
    (xdc_Char)0x65,  /* [686] */
    (xdc_Char)0x6e,  /* [687] */
    (xdc_Char)0x74,  /* [688] */
    (xdc_Char)0x49,  /* [689] */
    (xdc_Char)0x6e,  /* [690] */
    (xdc_Char)0x55,  /* [691] */
    (xdc_Char)0x73,  /* [692] */
    (xdc_Char)0x65,  /* [693] */
    (xdc_Char)0x3a,  /* [694] */
    (xdc_Char)0x20,  /* [695] */
    (xdc_Char)0x45,  /* [696] */
    (xdc_Char)0x76,  /* [697] */
    (xdc_Char)0x65,  /* [698] */
    (xdc_Char)0x6e,  /* [699] */
    (xdc_Char)0x74,  /* [700] */
    (xdc_Char)0x20,  /* [701] */
    (xdc_Char)0x6f,  /* [702] */
    (xdc_Char)0x62,  /* [703] */
    (xdc_Char)0x6a,  /* [704] */
    (xdc_Char)0x65,  /* [705] */
    (xdc_Char)0x63,  /* [706] */
    (xdc_Char)0x74,  /* [707] */
    (xdc_Char)0x20,  /* [708] */
    (xdc_Char)0x61,  /* [709] */
    (xdc_Char)0x6c,  /* [710] */
    (xdc_Char)0x72,  /* [711] */
    (xdc_Char)0x65,  /* [712] */
    (xdc_Char)0x61,  /* [713] */
    (xdc_Char)0x64,  /* [714] */
    (xdc_Char)0x79,  /* [715] */
    (xdc_Char)0x20,  /* [716] */
    (xdc_Char)0x69,  /* [717] */
    (xdc_Char)0x6e,  /* [718] */
    (xdc_Char)0x20,  /* [719] */
    (xdc_Char)0x75,  /* [720] */
    (xdc_Char)0x73,  /* [721] */
    (xdc_Char)0x65,  /* [722] */
    (xdc_Char)0x2e,  /* [723] */
    (xdc_Char)0x0,  /* [724] */
    (xdc_Char)0x41,  /* [725] */
    (xdc_Char)0x5f,  /* [726] */
    (xdc_Char)0x62,  /* [727] */
    (xdc_Char)0x61,  /* [728] */
    (xdc_Char)0x64,  /* [729] */
    (xdc_Char)0x43,  /* [730] */
    (xdc_Char)0x6f,  /* [731] */
    (xdc_Char)0x6e,  /* [732] */
    (xdc_Char)0x74,  /* [733] */
    (xdc_Char)0x65,  /* [734] */
    (xdc_Char)0x78,  /* [735] */
    (xdc_Char)0x74,  /* [736] */
    (xdc_Char)0x3a,  /* [737] */
    (xdc_Char)0x20,  /* [738] */
    (xdc_Char)0x62,  /* [739] */
    (xdc_Char)0x61,  /* [740] */
    (xdc_Char)0x64,  /* [741] */
    (xdc_Char)0x20,  /* [742] */
    (xdc_Char)0x63,  /* [743] */
    (xdc_Char)0x61,  /* [744] */
    (xdc_Char)0x6c,  /* [745] */
    (xdc_Char)0x6c,  /* [746] */
    (xdc_Char)0x69,  /* [747] */
    (xdc_Char)0x6e,  /* [748] */
    (xdc_Char)0x67,  /* [749] */
    (xdc_Char)0x20,  /* [750] */
    (xdc_Char)0x63,  /* [751] */
    (xdc_Char)0x6f,  /* [752] */
    (xdc_Char)0x6e,  /* [753] */
    (xdc_Char)0x74,  /* [754] */
    (xdc_Char)0x65,  /* [755] */
    (xdc_Char)0x78,  /* [756] */
    (xdc_Char)0x74,  /* [757] */
    (xdc_Char)0x2e,  /* [758] */
    (xdc_Char)0x20,  /* [759] */
    (xdc_Char)0x4d,  /* [760] */
    (xdc_Char)0x75,  /* [761] */
    (xdc_Char)0x73,  /* [762] */
    (xdc_Char)0x74,  /* [763] */
    (xdc_Char)0x20,  /* [764] */
    (xdc_Char)0x62,  /* [765] */
    (xdc_Char)0x65,  /* [766] */
    (xdc_Char)0x20,  /* [767] */
    (xdc_Char)0x63,  /* [768] */
    (xdc_Char)0x61,  /* [769] */
    (xdc_Char)0x6c,  /* [770] */
    (xdc_Char)0x6c,  /* [771] */
    (xdc_Char)0x65,  /* [772] */
    (xdc_Char)0x64,  /* [773] */
    (xdc_Char)0x20,  /* [774] */
    (xdc_Char)0x66,  /* [775] */
    (xdc_Char)0x72,  /* [776] */
    (xdc_Char)0x6f,  /* [777] */
    (xdc_Char)0x6d,  /* [778] */
    (xdc_Char)0x20,  /* [779] */
    (xdc_Char)0x61,  /* [780] */
    (xdc_Char)0x20,  /* [781] */
    (xdc_Char)0x54,  /* [782] */
    (xdc_Char)0x61,  /* [783] */
    (xdc_Char)0x73,  /* [784] */
    (xdc_Char)0x6b,  /* [785] */
    (xdc_Char)0x2e,  /* [786] */
    (xdc_Char)0x0,  /* [787] */
    (xdc_Char)0x41,  /* [788] */
    (xdc_Char)0x5f,  /* [789] */
    (xdc_Char)0x70,  /* [790] */
    (xdc_Char)0x65,  /* [791] */
    (xdc_Char)0x6e,  /* [792] */
    (xdc_Char)0x64,  /* [793] */
    (xdc_Char)0x54,  /* [794] */
    (xdc_Char)0x61,  /* [795] */
    (xdc_Char)0x73,  /* [796] */
    (xdc_Char)0x6b,  /* [797] */
    (xdc_Char)0x44,  /* [798] */
    (xdc_Char)0x69,  /* [799] */
    (xdc_Char)0x73,  /* [800] */
    (xdc_Char)0x61,  /* [801] */
    (xdc_Char)0x62,  /* [802] */
    (xdc_Char)0x6c,  /* [803] */
    (xdc_Char)0x65,  /* [804] */
    (xdc_Char)0x64,  /* [805] */
    (xdc_Char)0x3a,  /* [806] */
    (xdc_Char)0x20,  /* [807] */
    (xdc_Char)0x43,  /* [808] */
    (xdc_Char)0x61,  /* [809] */
    (xdc_Char)0x6e,  /* [810] */
    (xdc_Char)0x6e,  /* [811] */
    (xdc_Char)0x6f,  /* [812] */
    (xdc_Char)0x74,  /* [813] */
    (xdc_Char)0x20,  /* [814] */
    (xdc_Char)0x63,  /* [815] */
    (xdc_Char)0x61,  /* [816] */
    (xdc_Char)0x6c,  /* [817] */
    (xdc_Char)0x6c,  /* [818] */
    (xdc_Char)0x20,  /* [819] */
    (xdc_Char)0x45,  /* [820] */
    (xdc_Char)0x76,  /* [821] */
    (xdc_Char)0x65,  /* [822] */
    (xdc_Char)0x6e,  /* [823] */
    (xdc_Char)0x74,  /* [824] */
    (xdc_Char)0x5f,  /* [825] */
    (xdc_Char)0x70,  /* [826] */
    (xdc_Char)0x65,  /* [827] */
    (xdc_Char)0x6e,  /* [828] */
    (xdc_Char)0x64,  /* [829] */
    (xdc_Char)0x28,  /* [830] */
    (xdc_Char)0x29,  /* [831] */
    (xdc_Char)0x20,  /* [832] */
    (xdc_Char)0x77,  /* [833] */
    (xdc_Char)0x68,  /* [834] */
    (xdc_Char)0x69,  /* [835] */
    (xdc_Char)0x6c,  /* [836] */
    (xdc_Char)0x65,  /* [837] */
    (xdc_Char)0x20,  /* [838] */
    (xdc_Char)0x74,  /* [839] */
    (xdc_Char)0x68,  /* [840] */
    (xdc_Char)0x65,  /* [841] */
    (xdc_Char)0x20,  /* [842] */
    (xdc_Char)0x54,  /* [843] */
    (xdc_Char)0x61,  /* [844] */
    (xdc_Char)0x73,  /* [845] */
    (xdc_Char)0x6b,  /* [846] */
    (xdc_Char)0x20,  /* [847] */
    (xdc_Char)0x6f,  /* [848] */
    (xdc_Char)0x72,  /* [849] */
    (xdc_Char)0x20,  /* [850] */
    (xdc_Char)0x53,  /* [851] */
    (xdc_Char)0x77,  /* [852] */
    (xdc_Char)0x69,  /* [853] */
    (xdc_Char)0x20,  /* [854] */
    (xdc_Char)0x73,  /* [855] */
    (xdc_Char)0x63,  /* [856] */
    (xdc_Char)0x68,  /* [857] */
    (xdc_Char)0x65,  /* [858] */
    (xdc_Char)0x64,  /* [859] */
    (xdc_Char)0x75,  /* [860] */
    (xdc_Char)0x6c,  /* [861] */
    (xdc_Char)0x65,  /* [862] */
    (xdc_Char)0x72,  /* [863] */
    (xdc_Char)0x20,  /* [864] */
    (xdc_Char)0x69,  /* [865] */
    (xdc_Char)0x73,  /* [866] */
    (xdc_Char)0x20,  /* [867] */
    (xdc_Char)0x64,  /* [868] */
    (xdc_Char)0x69,  /* [869] */
    (xdc_Char)0x73,  /* [870] */
    (xdc_Char)0x61,  /* [871] */
    (xdc_Char)0x62,  /* [872] */
    (xdc_Char)0x6c,  /* [873] */
    (xdc_Char)0x65,  /* [874] */
    (xdc_Char)0x64,  /* [875] */
    (xdc_Char)0x2e,  /* [876] */
    (xdc_Char)0x0,  /* [877] */
    (xdc_Char)0x4d,  /* [878] */
    (xdc_Char)0x61,  /* [879] */
    (xdc_Char)0x69,  /* [880] */
    (xdc_Char)0x6c,  /* [881] */
    (xdc_Char)0x62,  /* [882] */
    (xdc_Char)0x6f,  /* [883] */
    (xdc_Char)0x78,  /* [884] */
    (xdc_Char)0x5f,  /* [885] */
    (xdc_Char)0x63,  /* [886] */
    (xdc_Char)0x72,  /* [887] */
    (xdc_Char)0x65,  /* [888] */
    (xdc_Char)0x61,  /* [889] */
    (xdc_Char)0x74,  /* [890] */
    (xdc_Char)0x65,  /* [891] */
    (xdc_Char)0x27,  /* [892] */
    (xdc_Char)0x73,  /* [893] */
    (xdc_Char)0x20,  /* [894] */
    (xdc_Char)0x62,  /* [895] */
    (xdc_Char)0x75,  /* [896] */
    (xdc_Char)0x66,  /* [897] */
    (xdc_Char)0x53,  /* [898] */
    (xdc_Char)0x69,  /* [899] */
    (xdc_Char)0x7a,  /* [900] */
    (xdc_Char)0x65,  /* [901] */
    (xdc_Char)0x20,  /* [902] */
    (xdc_Char)0x70,  /* [903] */
    (xdc_Char)0x61,  /* [904] */
    (xdc_Char)0x72,  /* [905] */
    (xdc_Char)0x61,  /* [906] */
    (xdc_Char)0x6d,  /* [907] */
    (xdc_Char)0x65,  /* [908] */
    (xdc_Char)0x74,  /* [909] */
    (xdc_Char)0x65,  /* [910] */
    (xdc_Char)0x72,  /* [911] */
    (xdc_Char)0x20,  /* [912] */
    (xdc_Char)0x69,  /* [913] */
    (xdc_Char)0x73,  /* [914] */
    (xdc_Char)0x20,  /* [915] */
    (xdc_Char)0x69,  /* [916] */
    (xdc_Char)0x6e,  /* [917] */
    (xdc_Char)0x76,  /* [918] */
    (xdc_Char)0x61,  /* [919] */
    (xdc_Char)0x6c,  /* [920] */
    (xdc_Char)0x69,  /* [921] */
    (xdc_Char)0x64,  /* [922] */
    (xdc_Char)0x20,  /* [923] */
    (xdc_Char)0x28,  /* [924] */
    (xdc_Char)0x74,  /* [925] */
    (xdc_Char)0x6f,  /* [926] */
    (xdc_Char)0x6f,  /* [927] */
    (xdc_Char)0x20,  /* [928] */
    (xdc_Char)0x73,  /* [929] */
    (xdc_Char)0x6d,  /* [930] */
    (xdc_Char)0x61,  /* [931] */
    (xdc_Char)0x6c,  /* [932] */
    (xdc_Char)0x6c,  /* [933] */
    (xdc_Char)0x29,  /* [934] */
    (xdc_Char)0x0,  /* [935] */
    (xdc_Char)0x41,  /* [936] */
    (xdc_Char)0x5f,  /* [937] */
    (xdc_Char)0x6e,  /* [938] */
    (xdc_Char)0x6f,  /* [939] */
    (xdc_Char)0x45,  /* [940] */
    (xdc_Char)0x76,  /* [941] */
    (xdc_Char)0x65,  /* [942] */
    (xdc_Char)0x6e,  /* [943] */
    (xdc_Char)0x74,  /* [944] */
    (xdc_Char)0x73,  /* [945] */
    (xdc_Char)0x3a,  /* [946] */
    (xdc_Char)0x20,  /* [947] */
    (xdc_Char)0x54,  /* [948] */
    (xdc_Char)0x68,  /* [949] */
    (xdc_Char)0x65,  /* [950] */
    (xdc_Char)0x20,  /* [951] */
    (xdc_Char)0x45,  /* [952] */
    (xdc_Char)0x76,  /* [953] */
    (xdc_Char)0x65,  /* [954] */
    (xdc_Char)0x6e,  /* [955] */
    (xdc_Char)0x74,  /* [956] */
    (xdc_Char)0x2e,  /* [957] */
    (xdc_Char)0x73,  /* [958] */
    (xdc_Char)0x75,  /* [959] */
    (xdc_Char)0x70,  /* [960] */
    (xdc_Char)0x70,  /* [961] */
    (xdc_Char)0x6f,  /* [962] */
    (xdc_Char)0x72,  /* [963] */
    (xdc_Char)0x74,  /* [964] */
    (xdc_Char)0x73,  /* [965] */
    (xdc_Char)0x45,  /* [966] */
    (xdc_Char)0x76,  /* [967] */
    (xdc_Char)0x65,  /* [968] */
    (xdc_Char)0x6e,  /* [969] */
    (xdc_Char)0x74,  /* [970] */
    (xdc_Char)0x73,  /* [971] */
    (xdc_Char)0x20,  /* [972] */
    (xdc_Char)0x66,  /* [973] */
    (xdc_Char)0x6c,  /* [974] */
    (xdc_Char)0x61,  /* [975] */
    (xdc_Char)0x67,  /* [976] */
    (xdc_Char)0x20,  /* [977] */
    (xdc_Char)0x69,  /* [978] */
    (xdc_Char)0x73,  /* [979] */
    (xdc_Char)0x20,  /* [980] */
    (xdc_Char)0x64,  /* [981] */
    (xdc_Char)0x69,  /* [982] */
    (xdc_Char)0x73,  /* [983] */
    (xdc_Char)0x61,  /* [984] */
    (xdc_Char)0x62,  /* [985] */
    (xdc_Char)0x6c,  /* [986] */
    (xdc_Char)0x65,  /* [987] */
    (xdc_Char)0x64,  /* [988] */
    (xdc_Char)0x2e,  /* [989] */
    (xdc_Char)0x0,  /* [990] */
    (xdc_Char)0x41,  /* [991] */
    (xdc_Char)0x5f,  /* [992] */
    (xdc_Char)0x69,  /* [993] */
    (xdc_Char)0x6e,  /* [994] */
    (xdc_Char)0x76,  /* [995] */
    (xdc_Char)0x54,  /* [996] */
    (xdc_Char)0x69,  /* [997] */
    (xdc_Char)0x6d,  /* [998] */
    (xdc_Char)0x65,  /* [999] */
    (xdc_Char)0x6f,  /* [1000] */
    (xdc_Char)0x75,  /* [1001] */
    (xdc_Char)0x74,  /* [1002] */
    (xdc_Char)0x3a,  /* [1003] */
    (xdc_Char)0x20,  /* [1004] */
    (xdc_Char)0x43,  /* [1005] */
    (xdc_Char)0x61,  /* [1006] */
    (xdc_Char)0x6e,  /* [1007] */
    (xdc_Char)0x27,  /* [1008] */
    (xdc_Char)0x74,  /* [1009] */
    (xdc_Char)0x20,  /* [1010] */
    (xdc_Char)0x75,  /* [1011] */
    (xdc_Char)0x73,  /* [1012] */
    (xdc_Char)0x65,  /* [1013] */
    (xdc_Char)0x20,  /* [1014] */
    (xdc_Char)0x42,  /* [1015] */
    (xdc_Char)0x49,  /* [1016] */
    (xdc_Char)0x4f,  /* [1017] */
    (xdc_Char)0x53,  /* [1018] */
    (xdc_Char)0x5f,  /* [1019] */
    (xdc_Char)0x45,  /* [1020] */
    (xdc_Char)0x56,  /* [1021] */
    (xdc_Char)0x45,  /* [1022] */
    (xdc_Char)0x4e,  /* [1023] */
    (xdc_Char)0x54,  /* [1024] */
    (xdc_Char)0x5f,  /* [1025] */
    (xdc_Char)0x41,  /* [1026] */
    (xdc_Char)0x43,  /* [1027] */
    (xdc_Char)0x51,  /* [1028] */
    (xdc_Char)0x55,  /* [1029] */
    (xdc_Char)0x49,  /* [1030] */
    (xdc_Char)0x52,  /* [1031] */
    (xdc_Char)0x45,  /* [1032] */
    (xdc_Char)0x44,  /* [1033] */
    (xdc_Char)0x20,  /* [1034] */
    (xdc_Char)0x77,  /* [1035] */
    (xdc_Char)0x69,  /* [1036] */
    (xdc_Char)0x74,  /* [1037] */
    (xdc_Char)0x68,  /* [1038] */
    (xdc_Char)0x20,  /* [1039] */
    (xdc_Char)0x74,  /* [1040] */
    (xdc_Char)0x68,  /* [1041] */
    (xdc_Char)0x69,  /* [1042] */
    (xdc_Char)0x73,  /* [1043] */
    (xdc_Char)0x20,  /* [1044] */
    (xdc_Char)0x53,  /* [1045] */
    (xdc_Char)0x65,  /* [1046] */
    (xdc_Char)0x6d,  /* [1047] */
    (xdc_Char)0x61,  /* [1048] */
    (xdc_Char)0x70,  /* [1049] */
    (xdc_Char)0x68,  /* [1050] */
    (xdc_Char)0x6f,  /* [1051] */
    (xdc_Char)0x72,  /* [1052] */
    (xdc_Char)0x65,  /* [1053] */
    (xdc_Char)0x2e,  /* [1054] */
    (xdc_Char)0x0,  /* [1055] */
    (xdc_Char)0x41,  /* [1056] */
    (xdc_Char)0x5f,  /* [1057] */
    (xdc_Char)0x6f,  /* [1058] */
    (xdc_Char)0x76,  /* [1059] */
    (xdc_Char)0x65,  /* [1060] */
    (xdc_Char)0x72,  /* [1061] */
    (xdc_Char)0x66,  /* [1062] */
    (xdc_Char)0x6c,  /* [1063] */
    (xdc_Char)0x6f,  /* [1064] */
    (xdc_Char)0x77,  /* [1065] */
    (xdc_Char)0x3a,  /* [1066] */
    (xdc_Char)0x20,  /* [1067] */
    (xdc_Char)0x43,  /* [1068] */
    (xdc_Char)0x6f,  /* [1069] */
    (xdc_Char)0x75,  /* [1070] */
    (xdc_Char)0x6e,  /* [1071] */
    (xdc_Char)0x74,  /* [1072] */
    (xdc_Char)0x20,  /* [1073] */
    (xdc_Char)0x68,  /* [1074] */
    (xdc_Char)0x61,  /* [1075] */
    (xdc_Char)0x73,  /* [1076] */
    (xdc_Char)0x20,  /* [1077] */
    (xdc_Char)0x65,  /* [1078] */
    (xdc_Char)0x78,  /* [1079] */
    (xdc_Char)0x63,  /* [1080] */
    (xdc_Char)0x65,  /* [1081] */
    (xdc_Char)0x65,  /* [1082] */
    (xdc_Char)0x64,  /* [1083] */
    (xdc_Char)0x65,  /* [1084] */
    (xdc_Char)0x64,  /* [1085] */
    (xdc_Char)0x20,  /* [1086] */
    (xdc_Char)0x36,  /* [1087] */
    (xdc_Char)0x35,  /* [1088] */
    (xdc_Char)0x35,  /* [1089] */
    (xdc_Char)0x33,  /* [1090] */
    (xdc_Char)0x35,  /* [1091] */
    (xdc_Char)0x20,  /* [1092] */
    (xdc_Char)0x61,  /* [1093] */
    (xdc_Char)0x6e,  /* [1094] */
    (xdc_Char)0x64,  /* [1095] */
    (xdc_Char)0x20,  /* [1096] */
    (xdc_Char)0x72,  /* [1097] */
    (xdc_Char)0x6f,  /* [1098] */
    (xdc_Char)0x6c,  /* [1099] */
    (xdc_Char)0x6c,  /* [1100] */
    (xdc_Char)0x65,  /* [1101] */
    (xdc_Char)0x64,  /* [1102] */
    (xdc_Char)0x20,  /* [1103] */
    (xdc_Char)0x6f,  /* [1104] */
    (xdc_Char)0x76,  /* [1105] */
    (xdc_Char)0x65,  /* [1106] */
    (xdc_Char)0x72,  /* [1107] */
    (xdc_Char)0x2e,  /* [1108] */
    (xdc_Char)0x0,  /* [1109] */
    (xdc_Char)0x41,  /* [1110] */
    (xdc_Char)0x5f,  /* [1111] */
    (xdc_Char)0x70,  /* [1112] */
    (xdc_Char)0x65,  /* [1113] */
    (xdc_Char)0x6e,  /* [1114] */
    (xdc_Char)0x64,  /* [1115] */
    (xdc_Char)0x54,  /* [1116] */
    (xdc_Char)0x61,  /* [1117] */
    (xdc_Char)0x73,  /* [1118] */
    (xdc_Char)0x6b,  /* [1119] */
    (xdc_Char)0x44,  /* [1120] */
    (xdc_Char)0x69,  /* [1121] */
    (xdc_Char)0x73,  /* [1122] */
    (xdc_Char)0x61,  /* [1123] */
    (xdc_Char)0x62,  /* [1124] */
    (xdc_Char)0x6c,  /* [1125] */
    (xdc_Char)0x65,  /* [1126] */
    (xdc_Char)0x64,  /* [1127] */
    (xdc_Char)0x3a,  /* [1128] */
    (xdc_Char)0x20,  /* [1129] */
    (xdc_Char)0x43,  /* [1130] */
    (xdc_Char)0x61,  /* [1131] */
    (xdc_Char)0x6e,  /* [1132] */
    (xdc_Char)0x6e,  /* [1133] */
    (xdc_Char)0x6f,  /* [1134] */
    (xdc_Char)0x74,  /* [1135] */
    (xdc_Char)0x20,  /* [1136] */
    (xdc_Char)0x63,  /* [1137] */
    (xdc_Char)0x61,  /* [1138] */
    (xdc_Char)0x6c,  /* [1139] */
    (xdc_Char)0x6c,  /* [1140] */
    (xdc_Char)0x20,  /* [1141] */
    (xdc_Char)0x53,  /* [1142] */
    (xdc_Char)0x65,  /* [1143] */
    (xdc_Char)0x6d,  /* [1144] */
    (xdc_Char)0x61,  /* [1145] */
    (xdc_Char)0x70,  /* [1146] */
    (xdc_Char)0x68,  /* [1147] */
    (xdc_Char)0x6f,  /* [1148] */
    (xdc_Char)0x72,  /* [1149] */
    (xdc_Char)0x65,  /* [1150] */
    (xdc_Char)0x5f,  /* [1151] */
    (xdc_Char)0x70,  /* [1152] */
    (xdc_Char)0x65,  /* [1153] */
    (xdc_Char)0x6e,  /* [1154] */
    (xdc_Char)0x64,  /* [1155] */
    (xdc_Char)0x28,  /* [1156] */
    (xdc_Char)0x29,  /* [1157] */
    (xdc_Char)0x20,  /* [1158] */
    (xdc_Char)0x77,  /* [1159] */
    (xdc_Char)0x68,  /* [1160] */
    (xdc_Char)0x69,  /* [1161] */
    (xdc_Char)0x6c,  /* [1162] */
    (xdc_Char)0x65,  /* [1163] */
    (xdc_Char)0x20,  /* [1164] */
    (xdc_Char)0x74,  /* [1165] */
    (xdc_Char)0x68,  /* [1166] */
    (xdc_Char)0x65,  /* [1167] */
    (xdc_Char)0x20,  /* [1168] */
    (xdc_Char)0x54,  /* [1169] */
    (xdc_Char)0x61,  /* [1170] */
    (xdc_Char)0x73,  /* [1171] */
    (xdc_Char)0x6b,  /* [1172] */
    (xdc_Char)0x20,  /* [1173] */
    (xdc_Char)0x6f,  /* [1174] */
    (xdc_Char)0x72,  /* [1175] */
    (xdc_Char)0x20,  /* [1176] */
    (xdc_Char)0x53,  /* [1177] */
    (xdc_Char)0x77,  /* [1178] */
    (xdc_Char)0x69,  /* [1179] */
    (xdc_Char)0x20,  /* [1180] */
    (xdc_Char)0x73,  /* [1181] */
    (xdc_Char)0x63,  /* [1182] */
    (xdc_Char)0x68,  /* [1183] */
    (xdc_Char)0x65,  /* [1184] */
    (xdc_Char)0x64,  /* [1185] */
    (xdc_Char)0x75,  /* [1186] */
    (xdc_Char)0x6c,  /* [1187] */
    (xdc_Char)0x65,  /* [1188] */
    (xdc_Char)0x72,  /* [1189] */
    (xdc_Char)0x20,  /* [1190] */
    (xdc_Char)0x69,  /* [1191] */
    (xdc_Char)0x73,  /* [1192] */
    (xdc_Char)0x20,  /* [1193] */
    (xdc_Char)0x64,  /* [1194] */
    (xdc_Char)0x69,  /* [1195] */
    (xdc_Char)0x73,  /* [1196] */
    (xdc_Char)0x61,  /* [1197] */
    (xdc_Char)0x62,  /* [1198] */
    (xdc_Char)0x6c,  /* [1199] */
    (xdc_Char)0x65,  /* [1200] */
    (xdc_Char)0x64,  /* [1201] */
    (xdc_Char)0x2e,  /* [1202] */
    (xdc_Char)0x0,  /* [1203] */
    (xdc_Char)0x41,  /* [1204] */
    (xdc_Char)0x5f,  /* [1205] */
    (xdc_Char)0x73,  /* [1206] */
    (xdc_Char)0x77,  /* [1207] */
    (xdc_Char)0x69,  /* [1208] */
    (xdc_Char)0x44,  /* [1209] */
    (xdc_Char)0x69,  /* [1210] */
    (xdc_Char)0x73,  /* [1211] */
    (xdc_Char)0x61,  /* [1212] */
    (xdc_Char)0x62,  /* [1213] */
    (xdc_Char)0x6c,  /* [1214] */
    (xdc_Char)0x65,  /* [1215] */
    (xdc_Char)0x64,  /* [1216] */
    (xdc_Char)0x3a,  /* [1217] */
    (xdc_Char)0x20,  /* [1218] */
    (xdc_Char)0x43,  /* [1219] */
    (xdc_Char)0x61,  /* [1220] */
    (xdc_Char)0x6e,  /* [1221] */
    (xdc_Char)0x6e,  /* [1222] */
    (xdc_Char)0x6f,  /* [1223] */
    (xdc_Char)0x74,  /* [1224] */
    (xdc_Char)0x20,  /* [1225] */
    (xdc_Char)0x63,  /* [1226] */
    (xdc_Char)0x72,  /* [1227] */
    (xdc_Char)0x65,  /* [1228] */
    (xdc_Char)0x61,  /* [1229] */
    (xdc_Char)0x74,  /* [1230] */
    (xdc_Char)0x65,  /* [1231] */
    (xdc_Char)0x20,  /* [1232] */
    (xdc_Char)0x61,  /* [1233] */
    (xdc_Char)0x20,  /* [1234] */
    (xdc_Char)0x53,  /* [1235] */
    (xdc_Char)0x77,  /* [1236] */
    (xdc_Char)0x69,  /* [1237] */
    (xdc_Char)0x20,  /* [1238] */
    (xdc_Char)0x77,  /* [1239] */
    (xdc_Char)0x68,  /* [1240] */
    (xdc_Char)0x65,  /* [1241] */
    (xdc_Char)0x6e,  /* [1242] */
    (xdc_Char)0x20,  /* [1243] */
    (xdc_Char)0x53,  /* [1244] */
    (xdc_Char)0x77,  /* [1245] */
    (xdc_Char)0x69,  /* [1246] */
    (xdc_Char)0x20,  /* [1247] */
    (xdc_Char)0x69,  /* [1248] */
    (xdc_Char)0x73,  /* [1249] */
    (xdc_Char)0x20,  /* [1250] */
    (xdc_Char)0x64,  /* [1251] */
    (xdc_Char)0x69,  /* [1252] */
    (xdc_Char)0x73,  /* [1253] */
    (xdc_Char)0x61,  /* [1254] */
    (xdc_Char)0x62,  /* [1255] */
    (xdc_Char)0x6c,  /* [1256] */
    (xdc_Char)0x65,  /* [1257] */
    (xdc_Char)0x64,  /* [1258] */
    (xdc_Char)0x2e,  /* [1259] */
    (xdc_Char)0x0,  /* [1260] */
    (xdc_Char)0x41,  /* [1261] */
    (xdc_Char)0x5f,  /* [1262] */
    (xdc_Char)0x62,  /* [1263] */
    (xdc_Char)0x61,  /* [1264] */
    (xdc_Char)0x64,  /* [1265] */
    (xdc_Char)0x50,  /* [1266] */
    (xdc_Char)0x72,  /* [1267] */
    (xdc_Char)0x69,  /* [1268] */
    (xdc_Char)0x6f,  /* [1269] */
    (xdc_Char)0x72,  /* [1270] */
    (xdc_Char)0x69,  /* [1271] */
    (xdc_Char)0x74,  /* [1272] */
    (xdc_Char)0x79,  /* [1273] */
    (xdc_Char)0x3a,  /* [1274] */
    (xdc_Char)0x20,  /* [1275] */
    (xdc_Char)0x41,  /* [1276] */
    (xdc_Char)0x6e,  /* [1277] */
    (xdc_Char)0x20,  /* [1278] */
    (xdc_Char)0x69,  /* [1279] */
    (xdc_Char)0x6e,  /* [1280] */
    (xdc_Char)0x76,  /* [1281] */
    (xdc_Char)0x61,  /* [1282] */
    (xdc_Char)0x6c,  /* [1283] */
    (xdc_Char)0x69,  /* [1284] */
    (xdc_Char)0x64,  /* [1285] */
    (xdc_Char)0x20,  /* [1286] */
    (xdc_Char)0x53,  /* [1287] */
    (xdc_Char)0x77,  /* [1288] */
    (xdc_Char)0x69,  /* [1289] */
    (xdc_Char)0x20,  /* [1290] */
    (xdc_Char)0x70,  /* [1291] */
    (xdc_Char)0x72,  /* [1292] */
    (xdc_Char)0x69,  /* [1293] */
    (xdc_Char)0x6f,  /* [1294] */
    (xdc_Char)0x72,  /* [1295] */
    (xdc_Char)0x69,  /* [1296] */
    (xdc_Char)0x74,  /* [1297] */
    (xdc_Char)0x79,  /* [1298] */
    (xdc_Char)0x20,  /* [1299] */
    (xdc_Char)0x77,  /* [1300] */
    (xdc_Char)0x61,  /* [1301] */
    (xdc_Char)0x73,  /* [1302] */
    (xdc_Char)0x20,  /* [1303] */
    (xdc_Char)0x75,  /* [1304] */
    (xdc_Char)0x73,  /* [1305] */
    (xdc_Char)0x65,  /* [1306] */
    (xdc_Char)0x64,  /* [1307] */
    (xdc_Char)0x2e,  /* [1308] */
    (xdc_Char)0x0,  /* [1309] */
    (xdc_Char)0x41,  /* [1310] */
    (xdc_Char)0x5f,  /* [1311] */
    (xdc_Char)0x62,  /* [1312] */
    (xdc_Char)0x61,  /* [1313] */
    (xdc_Char)0x64,  /* [1314] */
    (xdc_Char)0x54,  /* [1315] */
    (xdc_Char)0x68,  /* [1316] */
    (xdc_Char)0x72,  /* [1317] */
    (xdc_Char)0x65,  /* [1318] */
    (xdc_Char)0x61,  /* [1319] */
    (xdc_Char)0x64,  /* [1320] */
    (xdc_Char)0x54,  /* [1321] */
    (xdc_Char)0x79,  /* [1322] */
    (xdc_Char)0x70,  /* [1323] */
    (xdc_Char)0x65,  /* [1324] */
    (xdc_Char)0x3a,  /* [1325] */
    (xdc_Char)0x20,  /* [1326] */
    (xdc_Char)0x43,  /* [1327] */
    (xdc_Char)0x61,  /* [1328] */
    (xdc_Char)0x6e,  /* [1329] */
    (xdc_Char)0x6e,  /* [1330] */
    (xdc_Char)0x6f,  /* [1331] */
    (xdc_Char)0x74,  /* [1332] */
    (xdc_Char)0x20,  /* [1333] */
    (xdc_Char)0x63,  /* [1334] */
    (xdc_Char)0x72,  /* [1335] */
    (xdc_Char)0x65,  /* [1336] */
    (xdc_Char)0x61,  /* [1337] */
    (xdc_Char)0x74,  /* [1338] */
    (xdc_Char)0x65,  /* [1339] */
    (xdc_Char)0x2f,  /* [1340] */
    (xdc_Char)0x64,  /* [1341] */
    (xdc_Char)0x65,  /* [1342] */
    (xdc_Char)0x6c,  /* [1343] */
    (xdc_Char)0x65,  /* [1344] */
    (xdc_Char)0x74,  /* [1345] */
    (xdc_Char)0x65,  /* [1346] */
    (xdc_Char)0x20,  /* [1347] */
    (xdc_Char)0x61,  /* [1348] */
    (xdc_Char)0x20,  /* [1349] */
    (xdc_Char)0x74,  /* [1350] */
    (xdc_Char)0x61,  /* [1351] */
    (xdc_Char)0x73,  /* [1352] */
    (xdc_Char)0x6b,  /* [1353] */
    (xdc_Char)0x20,  /* [1354] */
    (xdc_Char)0x66,  /* [1355] */
    (xdc_Char)0x72,  /* [1356] */
    (xdc_Char)0x6f,  /* [1357] */
    (xdc_Char)0x6d,  /* [1358] */
    (xdc_Char)0x20,  /* [1359] */
    (xdc_Char)0x48,  /* [1360] */
    (xdc_Char)0x77,  /* [1361] */
    (xdc_Char)0x69,  /* [1362] */
    (xdc_Char)0x20,  /* [1363] */
    (xdc_Char)0x6f,  /* [1364] */
    (xdc_Char)0x72,  /* [1365] */
    (xdc_Char)0x20,  /* [1366] */
    (xdc_Char)0x53,  /* [1367] */
    (xdc_Char)0x77,  /* [1368] */
    (xdc_Char)0x69,  /* [1369] */
    (xdc_Char)0x20,  /* [1370] */
    (xdc_Char)0x74,  /* [1371] */
    (xdc_Char)0x68,  /* [1372] */
    (xdc_Char)0x72,  /* [1373] */
    (xdc_Char)0x65,  /* [1374] */
    (xdc_Char)0x61,  /* [1375] */
    (xdc_Char)0x64,  /* [1376] */
    (xdc_Char)0x2e,  /* [1377] */
    (xdc_Char)0x0,  /* [1378] */
    (xdc_Char)0x41,  /* [1379] */
    (xdc_Char)0x5f,  /* [1380] */
    (xdc_Char)0x62,  /* [1381] */
    (xdc_Char)0x61,  /* [1382] */
    (xdc_Char)0x64,  /* [1383] */
    (xdc_Char)0x54,  /* [1384] */
    (xdc_Char)0x61,  /* [1385] */
    (xdc_Char)0x73,  /* [1386] */
    (xdc_Char)0x6b,  /* [1387] */
    (xdc_Char)0x53,  /* [1388] */
    (xdc_Char)0x74,  /* [1389] */
    (xdc_Char)0x61,  /* [1390] */
    (xdc_Char)0x74,  /* [1391] */
    (xdc_Char)0x65,  /* [1392] */
    (xdc_Char)0x3a,  /* [1393] */
    (xdc_Char)0x20,  /* [1394] */
    (xdc_Char)0x43,  /* [1395] */
    (xdc_Char)0x61,  /* [1396] */
    (xdc_Char)0x6e,  /* [1397] */
    (xdc_Char)0x27,  /* [1398] */
    (xdc_Char)0x74,  /* [1399] */
    (xdc_Char)0x20,  /* [1400] */
    (xdc_Char)0x64,  /* [1401] */
    (xdc_Char)0x65,  /* [1402] */
    (xdc_Char)0x6c,  /* [1403] */
    (xdc_Char)0x65,  /* [1404] */
    (xdc_Char)0x74,  /* [1405] */
    (xdc_Char)0x65,  /* [1406] */
    (xdc_Char)0x20,  /* [1407] */
    (xdc_Char)0x61,  /* [1408] */
    (xdc_Char)0x20,  /* [1409] */
    (xdc_Char)0x74,  /* [1410] */
    (xdc_Char)0x61,  /* [1411] */
    (xdc_Char)0x73,  /* [1412] */
    (xdc_Char)0x6b,  /* [1413] */
    (xdc_Char)0x20,  /* [1414] */
    (xdc_Char)0x69,  /* [1415] */
    (xdc_Char)0x6e,  /* [1416] */
    (xdc_Char)0x20,  /* [1417] */
    (xdc_Char)0x52,  /* [1418] */
    (xdc_Char)0x55,  /* [1419] */
    (xdc_Char)0x4e,  /* [1420] */
    (xdc_Char)0x4e,  /* [1421] */
    (xdc_Char)0x49,  /* [1422] */
    (xdc_Char)0x4e,  /* [1423] */
    (xdc_Char)0x47,  /* [1424] */
    (xdc_Char)0x20,  /* [1425] */
    (xdc_Char)0x73,  /* [1426] */
    (xdc_Char)0x74,  /* [1427] */
    (xdc_Char)0x61,  /* [1428] */
    (xdc_Char)0x74,  /* [1429] */
    (xdc_Char)0x65,  /* [1430] */
    (xdc_Char)0x2e,  /* [1431] */
    (xdc_Char)0x0,  /* [1432] */
    (xdc_Char)0x41,  /* [1433] */
    (xdc_Char)0x5f,  /* [1434] */
    (xdc_Char)0x6e,  /* [1435] */
    (xdc_Char)0x6f,  /* [1436] */
    (xdc_Char)0x50,  /* [1437] */
    (xdc_Char)0x65,  /* [1438] */
    (xdc_Char)0x6e,  /* [1439] */
    (xdc_Char)0x64,  /* [1440] */
    (xdc_Char)0x45,  /* [1441] */
    (xdc_Char)0x6c,  /* [1442] */
    (xdc_Char)0x65,  /* [1443] */
    (xdc_Char)0x6d,  /* [1444] */
    (xdc_Char)0x3a,  /* [1445] */
    (xdc_Char)0x20,  /* [1446] */
    (xdc_Char)0x4e,  /* [1447] */
    (xdc_Char)0x6f,  /* [1448] */
    (xdc_Char)0x74,  /* [1449] */
    (xdc_Char)0x20,  /* [1450] */
    (xdc_Char)0x65,  /* [1451] */
    (xdc_Char)0x6e,  /* [1452] */
    (xdc_Char)0x6f,  /* [1453] */
    (xdc_Char)0x75,  /* [1454] */
    (xdc_Char)0x67,  /* [1455] */
    (xdc_Char)0x68,  /* [1456] */
    (xdc_Char)0x20,  /* [1457] */
    (xdc_Char)0x69,  /* [1458] */
    (xdc_Char)0x6e,  /* [1459] */
    (xdc_Char)0x66,  /* [1460] */
    (xdc_Char)0x6f,  /* [1461] */
    (xdc_Char)0x20,  /* [1462] */
    (xdc_Char)0x74,  /* [1463] */
    (xdc_Char)0x6f,  /* [1464] */
    (xdc_Char)0x20,  /* [1465] */
    (xdc_Char)0x64,  /* [1466] */
    (xdc_Char)0x65,  /* [1467] */
    (xdc_Char)0x6c,  /* [1468] */
    (xdc_Char)0x65,  /* [1469] */
    (xdc_Char)0x74,  /* [1470] */
    (xdc_Char)0x65,  /* [1471] */
    (xdc_Char)0x20,  /* [1472] */
    (xdc_Char)0x42,  /* [1473] */
    (xdc_Char)0x4c,  /* [1474] */
    (xdc_Char)0x4f,  /* [1475] */
    (xdc_Char)0x43,  /* [1476] */
    (xdc_Char)0x4b,  /* [1477] */
    (xdc_Char)0x45,  /* [1478] */
    (xdc_Char)0x44,  /* [1479] */
    (xdc_Char)0x20,  /* [1480] */
    (xdc_Char)0x74,  /* [1481] */
    (xdc_Char)0x61,  /* [1482] */
    (xdc_Char)0x73,  /* [1483] */
    (xdc_Char)0x6b,  /* [1484] */
    (xdc_Char)0x2e,  /* [1485] */
    (xdc_Char)0x0,  /* [1486] */
    (xdc_Char)0x41,  /* [1487] */
    (xdc_Char)0x5f,  /* [1488] */
    (xdc_Char)0x74,  /* [1489] */
    (xdc_Char)0x61,  /* [1490] */
    (xdc_Char)0x73,  /* [1491] */
    (xdc_Char)0x6b,  /* [1492] */
    (xdc_Char)0x44,  /* [1493] */
    (xdc_Char)0x69,  /* [1494] */
    (xdc_Char)0x73,  /* [1495] */
    (xdc_Char)0x61,  /* [1496] */
    (xdc_Char)0x62,  /* [1497] */
    (xdc_Char)0x6c,  /* [1498] */
    (xdc_Char)0x65,  /* [1499] */
    (xdc_Char)0x64,  /* [1500] */
    (xdc_Char)0x3a,  /* [1501] */
    (xdc_Char)0x20,  /* [1502] */
    (xdc_Char)0x43,  /* [1503] */
    (xdc_Char)0x61,  /* [1504] */
    (xdc_Char)0x6e,  /* [1505] */
    (xdc_Char)0x6e,  /* [1506] */
    (xdc_Char)0x6f,  /* [1507] */
    (xdc_Char)0x74,  /* [1508] */
    (xdc_Char)0x20,  /* [1509] */
    (xdc_Char)0x63,  /* [1510] */
    (xdc_Char)0x72,  /* [1511] */
    (xdc_Char)0x65,  /* [1512] */
    (xdc_Char)0x61,  /* [1513] */
    (xdc_Char)0x74,  /* [1514] */
    (xdc_Char)0x65,  /* [1515] */
    (xdc_Char)0x20,  /* [1516] */
    (xdc_Char)0x61,  /* [1517] */
    (xdc_Char)0x20,  /* [1518] */
    (xdc_Char)0x74,  /* [1519] */
    (xdc_Char)0x61,  /* [1520] */
    (xdc_Char)0x73,  /* [1521] */
    (xdc_Char)0x6b,  /* [1522] */
    (xdc_Char)0x20,  /* [1523] */
    (xdc_Char)0x77,  /* [1524] */
    (xdc_Char)0x68,  /* [1525] */
    (xdc_Char)0x65,  /* [1526] */
    (xdc_Char)0x6e,  /* [1527] */
    (xdc_Char)0x20,  /* [1528] */
    (xdc_Char)0x74,  /* [1529] */
    (xdc_Char)0x61,  /* [1530] */
    (xdc_Char)0x73,  /* [1531] */
    (xdc_Char)0x6b,  /* [1532] */
    (xdc_Char)0x69,  /* [1533] */
    (xdc_Char)0x6e,  /* [1534] */
    (xdc_Char)0x67,  /* [1535] */
    (xdc_Char)0x20,  /* [1536] */
    (xdc_Char)0x69,  /* [1537] */
    (xdc_Char)0x73,  /* [1538] */
    (xdc_Char)0x20,  /* [1539] */
    (xdc_Char)0x64,  /* [1540] */
    (xdc_Char)0x69,  /* [1541] */
    (xdc_Char)0x73,  /* [1542] */
    (xdc_Char)0x61,  /* [1543] */
    (xdc_Char)0x62,  /* [1544] */
    (xdc_Char)0x6c,  /* [1545] */
    (xdc_Char)0x65,  /* [1546] */
    (xdc_Char)0x64,  /* [1547] */
    (xdc_Char)0x2e,  /* [1548] */
    (xdc_Char)0x0,  /* [1549] */
    (xdc_Char)0x41,  /* [1550] */
    (xdc_Char)0x5f,  /* [1551] */
    (xdc_Char)0x62,  /* [1552] */
    (xdc_Char)0x61,  /* [1553] */
    (xdc_Char)0x64,  /* [1554] */
    (xdc_Char)0x50,  /* [1555] */
    (xdc_Char)0x72,  /* [1556] */
    (xdc_Char)0x69,  /* [1557] */
    (xdc_Char)0x6f,  /* [1558] */
    (xdc_Char)0x72,  /* [1559] */
    (xdc_Char)0x69,  /* [1560] */
    (xdc_Char)0x74,  /* [1561] */
    (xdc_Char)0x79,  /* [1562] */
    (xdc_Char)0x3a,  /* [1563] */
    (xdc_Char)0x20,  /* [1564] */
    (xdc_Char)0x41,  /* [1565] */
    (xdc_Char)0x6e,  /* [1566] */
    (xdc_Char)0x20,  /* [1567] */
    (xdc_Char)0x69,  /* [1568] */
    (xdc_Char)0x6e,  /* [1569] */
    (xdc_Char)0x76,  /* [1570] */
    (xdc_Char)0x61,  /* [1571] */
    (xdc_Char)0x6c,  /* [1572] */
    (xdc_Char)0x69,  /* [1573] */
    (xdc_Char)0x64,  /* [1574] */
    (xdc_Char)0x20,  /* [1575] */
    (xdc_Char)0x74,  /* [1576] */
    (xdc_Char)0x61,  /* [1577] */
    (xdc_Char)0x73,  /* [1578] */
    (xdc_Char)0x6b,  /* [1579] */
    (xdc_Char)0x20,  /* [1580] */
    (xdc_Char)0x70,  /* [1581] */
    (xdc_Char)0x72,  /* [1582] */
    (xdc_Char)0x69,  /* [1583] */
    (xdc_Char)0x6f,  /* [1584] */
    (xdc_Char)0x72,  /* [1585] */
    (xdc_Char)0x69,  /* [1586] */
    (xdc_Char)0x74,  /* [1587] */
    (xdc_Char)0x79,  /* [1588] */
    (xdc_Char)0x20,  /* [1589] */
    (xdc_Char)0x77,  /* [1590] */
    (xdc_Char)0x61,  /* [1591] */
    (xdc_Char)0x73,  /* [1592] */
    (xdc_Char)0x20,  /* [1593] */
    (xdc_Char)0x75,  /* [1594] */
    (xdc_Char)0x73,  /* [1595] */
    (xdc_Char)0x65,  /* [1596] */
    (xdc_Char)0x64,  /* [1597] */
    (xdc_Char)0x2e,  /* [1598] */
    (xdc_Char)0x0,  /* [1599] */
    (xdc_Char)0x41,  /* [1600] */
    (xdc_Char)0x5f,  /* [1601] */
    (xdc_Char)0x62,  /* [1602] */
    (xdc_Char)0x61,  /* [1603] */
    (xdc_Char)0x64,  /* [1604] */
    (xdc_Char)0x54,  /* [1605] */
    (xdc_Char)0x69,  /* [1606] */
    (xdc_Char)0x6d,  /* [1607] */
    (xdc_Char)0x65,  /* [1608] */
    (xdc_Char)0x6f,  /* [1609] */
    (xdc_Char)0x75,  /* [1610] */
    (xdc_Char)0x74,  /* [1611] */
    (xdc_Char)0x3a,  /* [1612] */
    (xdc_Char)0x20,  /* [1613] */
    (xdc_Char)0x43,  /* [1614] */
    (xdc_Char)0x61,  /* [1615] */
    (xdc_Char)0x6e,  /* [1616] */
    (xdc_Char)0x27,  /* [1617] */
    (xdc_Char)0x74,  /* [1618] */
    (xdc_Char)0x20,  /* [1619] */
    (xdc_Char)0x73,  /* [1620] */
    (xdc_Char)0x6c,  /* [1621] */
    (xdc_Char)0x65,  /* [1622] */
    (xdc_Char)0x65,  /* [1623] */
    (xdc_Char)0x70,  /* [1624] */
    (xdc_Char)0x20,  /* [1625] */
    (xdc_Char)0x46,  /* [1626] */
    (xdc_Char)0x4f,  /* [1627] */
    (xdc_Char)0x52,  /* [1628] */
    (xdc_Char)0x45,  /* [1629] */
    (xdc_Char)0x56,  /* [1630] */
    (xdc_Char)0x45,  /* [1631] */
    (xdc_Char)0x52,  /* [1632] */
    (xdc_Char)0x2e,  /* [1633] */
    (xdc_Char)0x0,  /* [1634] */
    (xdc_Char)0x41,  /* [1635] */
    (xdc_Char)0x5f,  /* [1636] */
    (xdc_Char)0x62,  /* [1637] */
    (xdc_Char)0x61,  /* [1638] */
    (xdc_Char)0x64,  /* [1639] */
    (xdc_Char)0x41,  /* [1640] */
    (xdc_Char)0x66,  /* [1641] */
    (xdc_Char)0x66,  /* [1642] */
    (xdc_Char)0x69,  /* [1643] */
    (xdc_Char)0x6e,  /* [1644] */
    (xdc_Char)0x69,  /* [1645] */
    (xdc_Char)0x74,  /* [1646] */
    (xdc_Char)0x79,  /* [1647] */
    (xdc_Char)0x3a,  /* [1648] */
    (xdc_Char)0x20,  /* [1649] */
    (xdc_Char)0x49,  /* [1650] */
    (xdc_Char)0x6e,  /* [1651] */
    (xdc_Char)0x76,  /* [1652] */
    (xdc_Char)0x61,  /* [1653] */
    (xdc_Char)0x6c,  /* [1654] */
    (xdc_Char)0x69,  /* [1655] */
    (xdc_Char)0x64,  /* [1656] */
    (xdc_Char)0x20,  /* [1657] */
    (xdc_Char)0x61,  /* [1658] */
    (xdc_Char)0x66,  /* [1659] */
    (xdc_Char)0x66,  /* [1660] */
    (xdc_Char)0x69,  /* [1661] */
    (xdc_Char)0x6e,  /* [1662] */
    (xdc_Char)0x69,  /* [1663] */
    (xdc_Char)0x74,  /* [1664] */
    (xdc_Char)0x79,  /* [1665] */
    (xdc_Char)0x2e,  /* [1666] */
    (xdc_Char)0x0,  /* [1667] */
    (xdc_Char)0x41,  /* [1668] */
    (xdc_Char)0x5f,  /* [1669] */
    (xdc_Char)0x73,  /* [1670] */
    (xdc_Char)0x6c,  /* [1671] */
    (xdc_Char)0x65,  /* [1672] */
    (xdc_Char)0x65,  /* [1673] */
    (xdc_Char)0x70,  /* [1674] */
    (xdc_Char)0x54,  /* [1675] */
    (xdc_Char)0x61,  /* [1676] */
    (xdc_Char)0x73,  /* [1677] */
    (xdc_Char)0x6b,  /* [1678] */
    (xdc_Char)0x44,  /* [1679] */
    (xdc_Char)0x69,  /* [1680] */
    (xdc_Char)0x73,  /* [1681] */
    (xdc_Char)0x61,  /* [1682] */
    (xdc_Char)0x62,  /* [1683] */
    (xdc_Char)0x6c,  /* [1684] */
    (xdc_Char)0x65,  /* [1685] */
    (xdc_Char)0x64,  /* [1686] */
    (xdc_Char)0x3a,  /* [1687] */
    (xdc_Char)0x20,  /* [1688] */
    (xdc_Char)0x43,  /* [1689] */
    (xdc_Char)0x61,  /* [1690] */
    (xdc_Char)0x6e,  /* [1691] */
    (xdc_Char)0x6e,  /* [1692] */
    (xdc_Char)0x6f,  /* [1693] */
    (xdc_Char)0x74,  /* [1694] */
    (xdc_Char)0x20,  /* [1695] */
    (xdc_Char)0x63,  /* [1696] */
    (xdc_Char)0x61,  /* [1697] */
    (xdc_Char)0x6c,  /* [1698] */
    (xdc_Char)0x6c,  /* [1699] */
    (xdc_Char)0x20,  /* [1700] */
    (xdc_Char)0x54,  /* [1701] */
    (xdc_Char)0x61,  /* [1702] */
    (xdc_Char)0x73,  /* [1703] */
    (xdc_Char)0x6b,  /* [1704] */
    (xdc_Char)0x5f,  /* [1705] */
    (xdc_Char)0x73,  /* [1706] */
    (xdc_Char)0x6c,  /* [1707] */
    (xdc_Char)0x65,  /* [1708] */
    (xdc_Char)0x65,  /* [1709] */
    (xdc_Char)0x70,  /* [1710] */
    (xdc_Char)0x28,  /* [1711] */
    (xdc_Char)0x29,  /* [1712] */
    (xdc_Char)0x20,  /* [1713] */
    (xdc_Char)0x77,  /* [1714] */
    (xdc_Char)0x68,  /* [1715] */
    (xdc_Char)0x69,  /* [1716] */
    (xdc_Char)0x6c,  /* [1717] */
    (xdc_Char)0x65,  /* [1718] */
    (xdc_Char)0x20,  /* [1719] */
    (xdc_Char)0x74,  /* [1720] */
    (xdc_Char)0x68,  /* [1721] */
    (xdc_Char)0x65,  /* [1722] */
    (xdc_Char)0x20,  /* [1723] */
    (xdc_Char)0x54,  /* [1724] */
    (xdc_Char)0x61,  /* [1725] */
    (xdc_Char)0x73,  /* [1726] */
    (xdc_Char)0x6b,  /* [1727] */
    (xdc_Char)0x20,  /* [1728] */
    (xdc_Char)0x73,  /* [1729] */
    (xdc_Char)0x63,  /* [1730] */
    (xdc_Char)0x68,  /* [1731] */
    (xdc_Char)0x65,  /* [1732] */
    (xdc_Char)0x64,  /* [1733] */
    (xdc_Char)0x75,  /* [1734] */
    (xdc_Char)0x6c,  /* [1735] */
    (xdc_Char)0x65,  /* [1736] */
    (xdc_Char)0x72,  /* [1737] */
    (xdc_Char)0x20,  /* [1738] */
    (xdc_Char)0x69,  /* [1739] */
    (xdc_Char)0x73,  /* [1740] */
    (xdc_Char)0x20,  /* [1741] */
    (xdc_Char)0x64,  /* [1742] */
    (xdc_Char)0x69,  /* [1743] */
    (xdc_Char)0x73,  /* [1744] */
    (xdc_Char)0x61,  /* [1745] */
    (xdc_Char)0x62,  /* [1746] */
    (xdc_Char)0x6c,  /* [1747] */
    (xdc_Char)0x65,  /* [1748] */
    (xdc_Char)0x64,  /* [1749] */
    (xdc_Char)0x2e,  /* [1750] */
    (xdc_Char)0x0,  /* [1751] */
    (xdc_Char)0x41,  /* [1752] */
    (xdc_Char)0x5f,  /* [1753] */
    (xdc_Char)0x69,  /* [1754] */
    (xdc_Char)0x6e,  /* [1755] */
    (xdc_Char)0x76,  /* [1756] */
    (xdc_Char)0x61,  /* [1757] */
    (xdc_Char)0x6c,  /* [1758] */
    (xdc_Char)0x69,  /* [1759] */
    (xdc_Char)0x64,  /* [1760] */
    (xdc_Char)0x43,  /* [1761] */
    (xdc_Char)0x6f,  /* [1762] */
    (xdc_Char)0x72,  /* [1763] */
    (xdc_Char)0x65,  /* [1764] */
    (xdc_Char)0x49,  /* [1765] */
    (xdc_Char)0x64,  /* [1766] */
    (xdc_Char)0x3a,  /* [1767] */
    (xdc_Char)0x20,  /* [1768] */
    (xdc_Char)0x43,  /* [1769] */
    (xdc_Char)0x61,  /* [1770] */
    (xdc_Char)0x6e,  /* [1771] */
    (xdc_Char)0x6e,  /* [1772] */
    (xdc_Char)0x6f,  /* [1773] */
    (xdc_Char)0x74,  /* [1774] */
    (xdc_Char)0x20,  /* [1775] */
    (xdc_Char)0x70,  /* [1776] */
    (xdc_Char)0x61,  /* [1777] */
    (xdc_Char)0x73,  /* [1778] */
    (xdc_Char)0x73,  /* [1779] */
    (xdc_Char)0x20,  /* [1780] */
    (xdc_Char)0x61,  /* [1781] */
    (xdc_Char)0x20,  /* [1782] */
    (xdc_Char)0x6e,  /* [1783] */
    (xdc_Char)0x6f,  /* [1784] */
    (xdc_Char)0x6e,  /* [1785] */
    (xdc_Char)0x2d,  /* [1786] */
    (xdc_Char)0x7a,  /* [1787] */
    (xdc_Char)0x65,  /* [1788] */
    (xdc_Char)0x72,  /* [1789] */
    (xdc_Char)0x6f,  /* [1790] */
    (xdc_Char)0x20,  /* [1791] */
    (xdc_Char)0x43,  /* [1792] */
    (xdc_Char)0x6f,  /* [1793] */
    (xdc_Char)0x72,  /* [1794] */
    (xdc_Char)0x65,  /* [1795] */
    (xdc_Char)0x49,  /* [1796] */
    (xdc_Char)0x64,  /* [1797] */
    (xdc_Char)0x20,  /* [1798] */
    (xdc_Char)0x69,  /* [1799] */
    (xdc_Char)0x6e,  /* [1800] */
    (xdc_Char)0x20,  /* [1801] */
    (xdc_Char)0x61,  /* [1802] */
    (xdc_Char)0x20,  /* [1803] */
    (xdc_Char)0x6e,  /* [1804] */
    (xdc_Char)0x6f,  /* [1805] */
    (xdc_Char)0x6e,  /* [1806] */
    (xdc_Char)0x2d,  /* [1807] */
    (xdc_Char)0x53,  /* [1808] */
    (xdc_Char)0x4d,  /* [1809] */
    (xdc_Char)0x50,  /* [1810] */
    (xdc_Char)0x20,  /* [1811] */
    (xdc_Char)0x61,  /* [1812] */
    (xdc_Char)0x70,  /* [1813] */
    (xdc_Char)0x70,  /* [1814] */
    (xdc_Char)0x6c,  /* [1815] */
    (xdc_Char)0x69,  /* [1816] */
    (xdc_Char)0x63,  /* [1817] */
    (xdc_Char)0x61,  /* [1818] */
    (xdc_Char)0x74,  /* [1819] */
    (xdc_Char)0x69,  /* [1820] */
    (xdc_Char)0x6f,  /* [1821] */
    (xdc_Char)0x6e,  /* [1822] */
    (xdc_Char)0x2e,  /* [1823] */
    (xdc_Char)0x0,  /* [1824] */
    (xdc_Char)0x41,  /* [1825] */
    (xdc_Char)0x5f,  /* [1826] */
    (xdc_Char)0x62,  /* [1827] */
    (xdc_Char)0x61,  /* [1828] */
    (xdc_Char)0x64,  /* [1829] */
    (xdc_Char)0x43,  /* [1830] */
    (xdc_Char)0x6f,  /* [1831] */
    (xdc_Char)0x6e,  /* [1832] */
    (xdc_Char)0x74,  /* [1833] */
    (xdc_Char)0x65,  /* [1834] */
    (xdc_Char)0x78,  /* [1835] */
    (xdc_Char)0x74,  /* [1836] */
    (xdc_Char)0x3a,  /* [1837] */
    (xdc_Char)0x20,  /* [1838] */
    (xdc_Char)0x62,  /* [1839] */
    (xdc_Char)0x61,  /* [1840] */
    (xdc_Char)0x64,  /* [1841] */
    (xdc_Char)0x20,  /* [1842] */
    (xdc_Char)0x63,  /* [1843] */
    (xdc_Char)0x61,  /* [1844] */
    (xdc_Char)0x6c,  /* [1845] */
    (xdc_Char)0x6c,  /* [1846] */
    (xdc_Char)0x69,  /* [1847] */
    (xdc_Char)0x6e,  /* [1848] */
    (xdc_Char)0x67,  /* [1849] */
    (xdc_Char)0x20,  /* [1850] */
    (xdc_Char)0x63,  /* [1851] */
    (xdc_Char)0x6f,  /* [1852] */
    (xdc_Char)0x6e,  /* [1853] */
    (xdc_Char)0x74,  /* [1854] */
    (xdc_Char)0x65,  /* [1855] */
    (xdc_Char)0x78,  /* [1856] */
    (xdc_Char)0x74,  /* [1857] */
    (xdc_Char)0x2e,  /* [1858] */
    (xdc_Char)0x20,  /* [1859] */
    (xdc_Char)0x4d,  /* [1860] */
    (xdc_Char)0x61,  /* [1861] */
    (xdc_Char)0x79,  /* [1862] */
    (xdc_Char)0x20,  /* [1863] */
    (xdc_Char)0x6e,  /* [1864] */
    (xdc_Char)0x6f,  /* [1865] */
    (xdc_Char)0x74,  /* [1866] */
    (xdc_Char)0x20,  /* [1867] */
    (xdc_Char)0x62,  /* [1868] */
    (xdc_Char)0x65,  /* [1869] */
    (xdc_Char)0x20,  /* [1870] */
    (xdc_Char)0x65,  /* [1871] */
    (xdc_Char)0x6e,  /* [1872] */
    (xdc_Char)0x74,  /* [1873] */
    (xdc_Char)0x65,  /* [1874] */
    (xdc_Char)0x72,  /* [1875] */
    (xdc_Char)0x65,  /* [1876] */
    (xdc_Char)0x64,  /* [1877] */
    (xdc_Char)0x20,  /* [1878] */
    (xdc_Char)0x66,  /* [1879] */
    (xdc_Char)0x72,  /* [1880] */
    (xdc_Char)0x6f,  /* [1881] */
    (xdc_Char)0x6d,  /* [1882] */
    (xdc_Char)0x20,  /* [1883] */
    (xdc_Char)0x61,  /* [1884] */
    (xdc_Char)0x20,  /* [1885] */
    (xdc_Char)0x68,  /* [1886] */
    (xdc_Char)0x61,  /* [1887] */
    (xdc_Char)0x72,  /* [1888] */
    (xdc_Char)0x64,  /* [1889] */
    (xdc_Char)0x77,  /* [1890] */
    (xdc_Char)0x61,  /* [1891] */
    (xdc_Char)0x72,  /* [1892] */
    (xdc_Char)0x65,  /* [1893] */
    (xdc_Char)0x20,  /* [1894] */
    (xdc_Char)0x69,  /* [1895] */
    (xdc_Char)0x6e,  /* [1896] */
    (xdc_Char)0x74,  /* [1897] */
    (xdc_Char)0x65,  /* [1898] */
    (xdc_Char)0x72,  /* [1899] */
    (xdc_Char)0x72,  /* [1900] */
    (xdc_Char)0x75,  /* [1901] */
    (xdc_Char)0x70,  /* [1902] */
    (xdc_Char)0x74,  /* [1903] */
    (xdc_Char)0x20,  /* [1904] */
    (xdc_Char)0x74,  /* [1905] */
    (xdc_Char)0x68,  /* [1906] */
    (xdc_Char)0x72,  /* [1907] */
    (xdc_Char)0x65,  /* [1908] */
    (xdc_Char)0x61,  /* [1909] */
    (xdc_Char)0x64,  /* [1910] */
    (xdc_Char)0x2e,  /* [1911] */
    (xdc_Char)0x0,  /* [1912] */
    (xdc_Char)0x41,  /* [1913] */
    (xdc_Char)0x5f,  /* [1914] */
    (xdc_Char)0x62,  /* [1915] */
    (xdc_Char)0x61,  /* [1916] */
    (xdc_Char)0x64,  /* [1917] */
    (xdc_Char)0x43,  /* [1918] */
    (xdc_Char)0x6f,  /* [1919] */
    (xdc_Char)0x6e,  /* [1920] */
    (xdc_Char)0x74,  /* [1921] */
    (xdc_Char)0x65,  /* [1922] */
    (xdc_Char)0x78,  /* [1923] */
    (xdc_Char)0x74,  /* [1924] */
    (xdc_Char)0x3a,  /* [1925] */
    (xdc_Char)0x20,  /* [1926] */
    (xdc_Char)0x62,  /* [1927] */
    (xdc_Char)0x61,  /* [1928] */
    (xdc_Char)0x64,  /* [1929] */
    (xdc_Char)0x20,  /* [1930] */
    (xdc_Char)0x63,  /* [1931] */
    (xdc_Char)0x61,  /* [1932] */
    (xdc_Char)0x6c,  /* [1933] */
    (xdc_Char)0x6c,  /* [1934] */
    (xdc_Char)0x69,  /* [1935] */
    (xdc_Char)0x6e,  /* [1936] */
    (xdc_Char)0x67,  /* [1937] */
    (xdc_Char)0x20,  /* [1938] */
    (xdc_Char)0x63,  /* [1939] */
    (xdc_Char)0x6f,  /* [1940] */
    (xdc_Char)0x6e,  /* [1941] */
    (xdc_Char)0x74,  /* [1942] */
    (xdc_Char)0x65,  /* [1943] */
    (xdc_Char)0x78,  /* [1944] */
    (xdc_Char)0x74,  /* [1945] */
    (xdc_Char)0x2e,  /* [1946] */
    (xdc_Char)0x20,  /* [1947] */
    (xdc_Char)0x4d,  /* [1948] */
    (xdc_Char)0x61,  /* [1949] */
    (xdc_Char)0x79,  /* [1950] */
    (xdc_Char)0x20,  /* [1951] */
    (xdc_Char)0x6e,  /* [1952] */
    (xdc_Char)0x6f,  /* [1953] */
    (xdc_Char)0x74,  /* [1954] */
    (xdc_Char)0x20,  /* [1955] */
    (xdc_Char)0x62,  /* [1956] */
    (xdc_Char)0x65,  /* [1957] */
    (xdc_Char)0x20,  /* [1958] */
    (xdc_Char)0x65,  /* [1959] */
    (xdc_Char)0x6e,  /* [1960] */
    (xdc_Char)0x74,  /* [1961] */
    (xdc_Char)0x65,  /* [1962] */
    (xdc_Char)0x72,  /* [1963] */
    (xdc_Char)0x65,  /* [1964] */
    (xdc_Char)0x64,  /* [1965] */
    (xdc_Char)0x20,  /* [1966] */
    (xdc_Char)0x66,  /* [1967] */
    (xdc_Char)0x72,  /* [1968] */
    (xdc_Char)0x6f,  /* [1969] */
    (xdc_Char)0x6d,  /* [1970] */
    (xdc_Char)0x20,  /* [1971] */
    (xdc_Char)0x61,  /* [1972] */
    (xdc_Char)0x20,  /* [1973] */
    (xdc_Char)0x73,  /* [1974] */
    (xdc_Char)0x6f,  /* [1975] */
    (xdc_Char)0x66,  /* [1976] */
    (xdc_Char)0x74,  /* [1977] */
    (xdc_Char)0x77,  /* [1978] */
    (xdc_Char)0x61,  /* [1979] */
    (xdc_Char)0x72,  /* [1980] */
    (xdc_Char)0x65,  /* [1981] */
    (xdc_Char)0x20,  /* [1982] */
    (xdc_Char)0x6f,  /* [1983] */
    (xdc_Char)0x72,  /* [1984] */
    (xdc_Char)0x20,  /* [1985] */
    (xdc_Char)0x68,  /* [1986] */
    (xdc_Char)0x61,  /* [1987] */
    (xdc_Char)0x72,  /* [1988] */
    (xdc_Char)0x64,  /* [1989] */
    (xdc_Char)0x77,  /* [1990] */
    (xdc_Char)0x61,  /* [1991] */
    (xdc_Char)0x72,  /* [1992] */
    (xdc_Char)0x65,  /* [1993] */
    (xdc_Char)0x20,  /* [1994] */
    (xdc_Char)0x69,  /* [1995] */
    (xdc_Char)0x6e,  /* [1996] */
    (xdc_Char)0x74,  /* [1997] */
    (xdc_Char)0x65,  /* [1998] */
    (xdc_Char)0x72,  /* [1999] */
    (xdc_Char)0x72,  /* [2000] */
    (xdc_Char)0x75,  /* [2001] */
    (xdc_Char)0x70,  /* [2002] */
    (xdc_Char)0x74,  /* [2003] */
    (xdc_Char)0x20,  /* [2004] */
    (xdc_Char)0x74,  /* [2005] */
    (xdc_Char)0x68,  /* [2006] */
    (xdc_Char)0x72,  /* [2007] */
    (xdc_Char)0x65,  /* [2008] */
    (xdc_Char)0x61,  /* [2009] */
    (xdc_Char)0x64,  /* [2010] */
    (xdc_Char)0x2e,  /* [2011] */
    (xdc_Char)0x0,  /* [2012] */
    (xdc_Char)0x41,  /* [2013] */
    (xdc_Char)0x5f,  /* [2014] */
    (xdc_Char)0x62,  /* [2015] */
    (xdc_Char)0x61,  /* [2016] */
    (xdc_Char)0x64,  /* [2017] */
    (xdc_Char)0x43,  /* [2018] */
    (xdc_Char)0x6f,  /* [2019] */
    (xdc_Char)0x6e,  /* [2020] */
    (xdc_Char)0x74,  /* [2021] */
    (xdc_Char)0x65,  /* [2022] */
    (xdc_Char)0x78,  /* [2023] */
    (xdc_Char)0x74,  /* [2024] */
    (xdc_Char)0x3a,  /* [2025] */
    (xdc_Char)0x20,  /* [2026] */
    (xdc_Char)0x62,  /* [2027] */
    (xdc_Char)0x61,  /* [2028] */
    (xdc_Char)0x64,  /* [2029] */
    (xdc_Char)0x20,  /* [2030] */
    (xdc_Char)0x63,  /* [2031] */
    (xdc_Char)0x61,  /* [2032] */
    (xdc_Char)0x6c,  /* [2033] */
    (xdc_Char)0x6c,  /* [2034] */
    (xdc_Char)0x69,  /* [2035] */
    (xdc_Char)0x6e,  /* [2036] */
    (xdc_Char)0x67,  /* [2037] */
    (xdc_Char)0x20,  /* [2038] */
    (xdc_Char)0x63,  /* [2039] */
    (xdc_Char)0x6f,  /* [2040] */
    (xdc_Char)0x6e,  /* [2041] */
    (xdc_Char)0x74,  /* [2042] */
    (xdc_Char)0x65,  /* [2043] */
    (xdc_Char)0x78,  /* [2044] */
    (xdc_Char)0x74,  /* [2045] */
    (xdc_Char)0x2e,  /* [2046] */
    (xdc_Char)0x20,  /* [2047] */
    (xdc_Char)0x53,  /* [2048] */
    (xdc_Char)0x65,  /* [2049] */
    (xdc_Char)0x65,  /* [2050] */
    (xdc_Char)0x20,  /* [2051] */
    (xdc_Char)0x47,  /* [2052] */
    (xdc_Char)0x61,  /* [2053] */
    (xdc_Char)0x74,  /* [2054] */
    (xdc_Char)0x65,  /* [2055] */
    (xdc_Char)0x4d,  /* [2056] */
    (xdc_Char)0x75,  /* [2057] */
    (xdc_Char)0x74,  /* [2058] */
    (xdc_Char)0x65,  /* [2059] */
    (xdc_Char)0x78,  /* [2060] */
    (xdc_Char)0x50,  /* [2061] */
    (xdc_Char)0x72,  /* [2062] */
    (xdc_Char)0x69,  /* [2063] */
    (xdc_Char)0x20,  /* [2064] */
    (xdc_Char)0x41,  /* [2065] */
    (xdc_Char)0x50,  /* [2066] */
    (xdc_Char)0x49,  /* [2067] */
    (xdc_Char)0x20,  /* [2068] */
    (xdc_Char)0x64,  /* [2069] */
    (xdc_Char)0x6f,  /* [2070] */
    (xdc_Char)0x63,  /* [2071] */
    (xdc_Char)0x20,  /* [2072] */
    (xdc_Char)0x66,  /* [2073] */
    (xdc_Char)0x6f,  /* [2074] */
    (xdc_Char)0x72,  /* [2075] */
    (xdc_Char)0x20,  /* [2076] */
    (xdc_Char)0x64,  /* [2077] */
    (xdc_Char)0x65,  /* [2078] */
    (xdc_Char)0x74,  /* [2079] */
    (xdc_Char)0x61,  /* [2080] */
    (xdc_Char)0x69,  /* [2081] */
    (xdc_Char)0x6c,  /* [2082] */
    (xdc_Char)0x73,  /* [2083] */
    (xdc_Char)0x2e,  /* [2084] */
    (xdc_Char)0x0,  /* [2085] */
    (xdc_Char)0x41,  /* [2086] */
    (xdc_Char)0x5f,  /* [2087] */
    (xdc_Char)0x65,  /* [2088] */
    (xdc_Char)0x6e,  /* [2089] */
    (xdc_Char)0x74,  /* [2090] */
    (xdc_Char)0x65,  /* [2091] */
    (xdc_Char)0x72,  /* [2092] */
    (xdc_Char)0x54,  /* [2093] */
    (xdc_Char)0x61,  /* [2094] */
    (xdc_Char)0x73,  /* [2095] */
    (xdc_Char)0x6b,  /* [2096] */
    (xdc_Char)0x44,  /* [2097] */
    (xdc_Char)0x69,  /* [2098] */
    (xdc_Char)0x73,  /* [2099] */
    (xdc_Char)0x61,  /* [2100] */
    (xdc_Char)0x62,  /* [2101] */
    (xdc_Char)0x6c,  /* [2102] */
    (xdc_Char)0x65,  /* [2103] */
    (xdc_Char)0x64,  /* [2104] */
    (xdc_Char)0x3a,  /* [2105] */
    (xdc_Char)0x20,  /* [2106] */
    (xdc_Char)0x43,  /* [2107] */
    (xdc_Char)0x61,  /* [2108] */
    (xdc_Char)0x6e,  /* [2109] */
    (xdc_Char)0x6e,  /* [2110] */
    (xdc_Char)0x6f,  /* [2111] */
    (xdc_Char)0x74,  /* [2112] */
    (xdc_Char)0x20,  /* [2113] */
    (xdc_Char)0x63,  /* [2114] */
    (xdc_Char)0x61,  /* [2115] */
    (xdc_Char)0x6c,  /* [2116] */
    (xdc_Char)0x6c,  /* [2117] */
    (xdc_Char)0x20,  /* [2118] */
    (xdc_Char)0x47,  /* [2119] */
    (xdc_Char)0x61,  /* [2120] */
    (xdc_Char)0x74,  /* [2121] */
    (xdc_Char)0x65,  /* [2122] */
    (xdc_Char)0x4d,  /* [2123] */
    (xdc_Char)0x75,  /* [2124] */
    (xdc_Char)0x74,  /* [2125] */
    (xdc_Char)0x65,  /* [2126] */
    (xdc_Char)0x78,  /* [2127] */
    (xdc_Char)0x50,  /* [2128] */
    (xdc_Char)0x72,  /* [2129] */
    (xdc_Char)0x69,  /* [2130] */
    (xdc_Char)0x5f,  /* [2131] */
    (xdc_Char)0x65,  /* [2132] */
    (xdc_Char)0x6e,  /* [2133] */
    (xdc_Char)0x74,  /* [2134] */
    (xdc_Char)0x65,  /* [2135] */
    (xdc_Char)0x72,  /* [2136] */
    (xdc_Char)0x28,  /* [2137] */
    (xdc_Char)0x29,  /* [2138] */
    (xdc_Char)0x20,  /* [2139] */
    (xdc_Char)0x77,  /* [2140] */
    (xdc_Char)0x68,  /* [2141] */
    (xdc_Char)0x69,  /* [2142] */
    (xdc_Char)0x6c,  /* [2143] */
    (xdc_Char)0x65,  /* [2144] */
    (xdc_Char)0x20,  /* [2145] */
    (xdc_Char)0x74,  /* [2146] */
    (xdc_Char)0x68,  /* [2147] */
    (xdc_Char)0x65,  /* [2148] */
    (xdc_Char)0x20,  /* [2149] */
    (xdc_Char)0x54,  /* [2150] */
    (xdc_Char)0x61,  /* [2151] */
    (xdc_Char)0x73,  /* [2152] */
    (xdc_Char)0x6b,  /* [2153] */
    (xdc_Char)0x20,  /* [2154] */
    (xdc_Char)0x6f,  /* [2155] */
    (xdc_Char)0x72,  /* [2156] */
    (xdc_Char)0x20,  /* [2157] */
    (xdc_Char)0x53,  /* [2158] */
    (xdc_Char)0x77,  /* [2159] */
    (xdc_Char)0x69,  /* [2160] */
    (xdc_Char)0x20,  /* [2161] */
    (xdc_Char)0x73,  /* [2162] */
    (xdc_Char)0x63,  /* [2163] */
    (xdc_Char)0x68,  /* [2164] */
    (xdc_Char)0x65,  /* [2165] */
    (xdc_Char)0x64,  /* [2166] */
    (xdc_Char)0x75,  /* [2167] */
    (xdc_Char)0x6c,  /* [2168] */
    (xdc_Char)0x65,  /* [2169] */
    (xdc_Char)0x72,  /* [2170] */
    (xdc_Char)0x20,  /* [2171] */
    (xdc_Char)0x69,  /* [2172] */
    (xdc_Char)0x73,  /* [2173] */
    (xdc_Char)0x20,  /* [2174] */
    (xdc_Char)0x64,  /* [2175] */
    (xdc_Char)0x69,  /* [2176] */
    (xdc_Char)0x73,  /* [2177] */
    (xdc_Char)0x61,  /* [2178] */
    (xdc_Char)0x62,  /* [2179] */
    (xdc_Char)0x6c,  /* [2180] */
    (xdc_Char)0x65,  /* [2181] */
    (xdc_Char)0x64,  /* [2182] */
    (xdc_Char)0x2e,  /* [2183] */
    (xdc_Char)0x0,  /* [2184] */
    (xdc_Char)0x41,  /* [2185] */
    (xdc_Char)0x5f,  /* [2186] */
    (xdc_Char)0x62,  /* [2187] */
    (xdc_Char)0x61,  /* [2188] */
    (xdc_Char)0x64,  /* [2189] */
    (xdc_Char)0x43,  /* [2190] */
    (xdc_Char)0x6f,  /* [2191] */
    (xdc_Char)0x6e,  /* [2192] */
    (xdc_Char)0x74,  /* [2193] */
    (xdc_Char)0x65,  /* [2194] */
    (xdc_Char)0x78,  /* [2195] */
    (xdc_Char)0x74,  /* [2196] */
    (xdc_Char)0x3a,  /* [2197] */
    (xdc_Char)0x20,  /* [2198] */
    (xdc_Char)0x62,  /* [2199] */
    (xdc_Char)0x61,  /* [2200] */
    (xdc_Char)0x64,  /* [2201] */
    (xdc_Char)0x20,  /* [2202] */
    (xdc_Char)0x63,  /* [2203] */
    (xdc_Char)0x61,  /* [2204] */
    (xdc_Char)0x6c,  /* [2205] */
    (xdc_Char)0x6c,  /* [2206] */
    (xdc_Char)0x69,  /* [2207] */
    (xdc_Char)0x6e,  /* [2208] */
    (xdc_Char)0x67,  /* [2209] */
    (xdc_Char)0x20,  /* [2210] */
    (xdc_Char)0x63,  /* [2211] */
    (xdc_Char)0x6f,  /* [2212] */
    (xdc_Char)0x6e,  /* [2213] */
    (xdc_Char)0x74,  /* [2214] */
    (xdc_Char)0x65,  /* [2215] */
    (xdc_Char)0x78,  /* [2216] */
    (xdc_Char)0x74,  /* [2217] */
    (xdc_Char)0x2e,  /* [2218] */
    (xdc_Char)0x20,  /* [2219] */
    (xdc_Char)0x53,  /* [2220] */
    (xdc_Char)0x65,  /* [2221] */
    (xdc_Char)0x65,  /* [2222] */
    (xdc_Char)0x20,  /* [2223] */
    (xdc_Char)0x47,  /* [2224] */
    (xdc_Char)0x61,  /* [2225] */
    (xdc_Char)0x74,  /* [2226] */
    (xdc_Char)0x65,  /* [2227] */
    (xdc_Char)0x4d,  /* [2228] */
    (xdc_Char)0x75,  /* [2229] */
    (xdc_Char)0x74,  /* [2230] */
    (xdc_Char)0x65,  /* [2231] */
    (xdc_Char)0x78,  /* [2232] */
    (xdc_Char)0x20,  /* [2233] */
    (xdc_Char)0x41,  /* [2234] */
    (xdc_Char)0x50,  /* [2235] */
    (xdc_Char)0x49,  /* [2236] */
    (xdc_Char)0x20,  /* [2237] */
    (xdc_Char)0x64,  /* [2238] */
    (xdc_Char)0x6f,  /* [2239] */
    (xdc_Char)0x63,  /* [2240] */
    (xdc_Char)0x20,  /* [2241] */
    (xdc_Char)0x66,  /* [2242] */
    (xdc_Char)0x6f,  /* [2243] */
    (xdc_Char)0x72,  /* [2244] */
    (xdc_Char)0x20,  /* [2245] */
    (xdc_Char)0x64,  /* [2246] */
    (xdc_Char)0x65,  /* [2247] */
    (xdc_Char)0x74,  /* [2248] */
    (xdc_Char)0x61,  /* [2249] */
    (xdc_Char)0x69,  /* [2250] */
    (xdc_Char)0x6c,  /* [2251] */
    (xdc_Char)0x73,  /* [2252] */
    (xdc_Char)0x2e,  /* [2253] */
    (xdc_Char)0x0,  /* [2254] */
    (xdc_Char)0x41,  /* [2255] */
    (xdc_Char)0x5f,  /* [2256] */
    (xdc_Char)0x62,  /* [2257] */
    (xdc_Char)0x61,  /* [2258] */
    (xdc_Char)0x64,  /* [2259] */
    (xdc_Char)0x43,  /* [2260] */
    (xdc_Char)0x6f,  /* [2261] */
    (xdc_Char)0x6e,  /* [2262] */
    (xdc_Char)0x74,  /* [2263] */
    (xdc_Char)0x65,  /* [2264] */
    (xdc_Char)0x78,  /* [2265] */
    (xdc_Char)0x74,  /* [2266] */
    (xdc_Char)0x3a,  /* [2267] */
    (xdc_Char)0x20,  /* [2268] */
    (xdc_Char)0x62,  /* [2269] */
    (xdc_Char)0x61,  /* [2270] */
    (xdc_Char)0x64,  /* [2271] */
    (xdc_Char)0x20,  /* [2272] */
    (xdc_Char)0x63,  /* [2273] */
    (xdc_Char)0x61,  /* [2274] */
    (xdc_Char)0x6c,  /* [2275] */
    (xdc_Char)0x6c,  /* [2276] */
    (xdc_Char)0x69,  /* [2277] */
    (xdc_Char)0x6e,  /* [2278] */
    (xdc_Char)0x67,  /* [2279] */
    (xdc_Char)0x20,  /* [2280] */
    (xdc_Char)0x63,  /* [2281] */
    (xdc_Char)0x6f,  /* [2282] */
    (xdc_Char)0x6e,  /* [2283] */
    (xdc_Char)0x74,  /* [2284] */
    (xdc_Char)0x65,  /* [2285] */
    (xdc_Char)0x78,  /* [2286] */
    (xdc_Char)0x74,  /* [2287] */
    (xdc_Char)0x2e,  /* [2288] */
    (xdc_Char)0x20,  /* [2289] */
    (xdc_Char)0x53,  /* [2290] */
    (xdc_Char)0x65,  /* [2291] */
    (xdc_Char)0x65,  /* [2292] */
    (xdc_Char)0x20,  /* [2293] */
    (xdc_Char)0x47,  /* [2294] */
    (xdc_Char)0x61,  /* [2295] */
    (xdc_Char)0x74,  /* [2296] */
    (xdc_Char)0x65,  /* [2297] */
    (xdc_Char)0x53,  /* [2298] */
    (xdc_Char)0x70,  /* [2299] */
    (xdc_Char)0x69,  /* [2300] */
    (xdc_Char)0x6e,  /* [2301] */
    (xdc_Char)0x6c,  /* [2302] */
    (xdc_Char)0x6f,  /* [2303] */
    (xdc_Char)0x63,  /* [2304] */
    (xdc_Char)0x6b,  /* [2305] */
    (xdc_Char)0x20,  /* [2306] */
    (xdc_Char)0x41,  /* [2307] */
    (xdc_Char)0x50,  /* [2308] */
    (xdc_Char)0x49,  /* [2309] */
    (xdc_Char)0x20,  /* [2310] */
    (xdc_Char)0x64,  /* [2311] */
    (xdc_Char)0x6f,  /* [2312] */
    (xdc_Char)0x63,  /* [2313] */
    (xdc_Char)0x20,  /* [2314] */
    (xdc_Char)0x66,  /* [2315] */
    (xdc_Char)0x6f,  /* [2316] */
    (xdc_Char)0x72,  /* [2317] */
    (xdc_Char)0x20,  /* [2318] */
    (xdc_Char)0x64,  /* [2319] */
    (xdc_Char)0x65,  /* [2320] */
    (xdc_Char)0x74,  /* [2321] */
    (xdc_Char)0x61,  /* [2322] */
    (xdc_Char)0x69,  /* [2323] */
    (xdc_Char)0x6c,  /* [2324] */
    (xdc_Char)0x73,  /* [2325] */
    (xdc_Char)0x2e,  /* [2326] */
    (xdc_Char)0x0,  /* [2327] */
    (xdc_Char)0x41,  /* [2328] */
    (xdc_Char)0x5f,  /* [2329] */
    (xdc_Char)0x69,  /* [2330] */
    (xdc_Char)0x6e,  /* [2331] */
    (xdc_Char)0x76,  /* [2332] */
    (xdc_Char)0x61,  /* [2333] */
    (xdc_Char)0x6c,  /* [2334] */
    (xdc_Char)0x69,  /* [2335] */
    (xdc_Char)0x64,  /* [2336] */
    (xdc_Char)0x51,  /* [2337] */
    (xdc_Char)0x75,  /* [2338] */
    (xdc_Char)0x61,  /* [2339] */
    (xdc_Char)0x6c,  /* [2340] */
    (xdc_Char)0x69,  /* [2341] */
    (xdc_Char)0x74,  /* [2342] */
    (xdc_Char)0x79,  /* [2343] */
    (xdc_Char)0x3a,  /* [2344] */
    (xdc_Char)0x20,  /* [2345] */
    (xdc_Char)0x53,  /* [2346] */
    (xdc_Char)0x65,  /* [2347] */
    (xdc_Char)0x65,  /* [2348] */
    (xdc_Char)0x20,  /* [2349] */
    (xdc_Char)0x47,  /* [2350] */
    (xdc_Char)0x61,  /* [2351] */
    (xdc_Char)0x74,  /* [2352] */
    (xdc_Char)0x65,  /* [2353] */
    (xdc_Char)0x53,  /* [2354] */
    (xdc_Char)0x70,  /* [2355] */
    (xdc_Char)0x69,  /* [2356] */
    (xdc_Char)0x6e,  /* [2357] */
    (xdc_Char)0x6c,  /* [2358] */
    (xdc_Char)0x6f,  /* [2359] */
    (xdc_Char)0x63,  /* [2360] */
    (xdc_Char)0x6b,  /* [2361] */
    (xdc_Char)0x20,  /* [2362] */
    (xdc_Char)0x41,  /* [2363] */
    (xdc_Char)0x50,  /* [2364] */
    (xdc_Char)0x49,  /* [2365] */
    (xdc_Char)0x20,  /* [2366] */
    (xdc_Char)0x64,  /* [2367] */
    (xdc_Char)0x6f,  /* [2368] */
    (xdc_Char)0x63,  /* [2369] */
    (xdc_Char)0x20,  /* [2370] */
    (xdc_Char)0x66,  /* [2371] */
    (xdc_Char)0x6f,  /* [2372] */
    (xdc_Char)0x72,  /* [2373] */
    (xdc_Char)0x20,  /* [2374] */
    (xdc_Char)0x64,  /* [2375] */
    (xdc_Char)0x65,  /* [2376] */
    (xdc_Char)0x74,  /* [2377] */
    (xdc_Char)0x61,  /* [2378] */
    (xdc_Char)0x69,  /* [2379] */
    (xdc_Char)0x6c,  /* [2380] */
    (xdc_Char)0x73,  /* [2381] */
    (xdc_Char)0x2e,  /* [2382] */
    (xdc_Char)0x0,  /* [2383] */
    (xdc_Char)0x41,  /* [2384] */
    (xdc_Char)0x5f,  /* [2385] */
    (xdc_Char)0x7a,  /* [2386] */
    (xdc_Char)0x65,  /* [2387] */
    (xdc_Char)0x72,  /* [2388] */
    (xdc_Char)0x6f,  /* [2389] */
    (xdc_Char)0x54,  /* [2390] */
    (xdc_Char)0x69,  /* [2391] */
    (xdc_Char)0x6d,  /* [2392] */
    (xdc_Char)0x65,  /* [2393] */
    (xdc_Char)0x6f,  /* [2394] */
    (xdc_Char)0x75,  /* [2395] */
    (xdc_Char)0x74,  /* [2396] */
    (xdc_Char)0x3a,  /* [2397] */
    (xdc_Char)0x20,  /* [2398] */
    (xdc_Char)0x54,  /* [2399] */
    (xdc_Char)0x69,  /* [2400] */
    (xdc_Char)0x6d,  /* [2401] */
    (xdc_Char)0x65,  /* [2402] */
    (xdc_Char)0x6f,  /* [2403] */
    (xdc_Char)0x75,  /* [2404] */
    (xdc_Char)0x74,  /* [2405] */
    (xdc_Char)0x20,  /* [2406] */
    (xdc_Char)0x76,  /* [2407] */
    (xdc_Char)0x61,  /* [2408] */
    (xdc_Char)0x6c,  /* [2409] */
    (xdc_Char)0x75,  /* [2410] */
    (xdc_Char)0x65,  /* [2411] */
    (xdc_Char)0x20,  /* [2412] */
    (xdc_Char)0x61,  /* [2413] */
    (xdc_Char)0x6e,  /* [2414] */
    (xdc_Char)0x6e,  /* [2415] */
    (xdc_Char)0x6f,  /* [2416] */
    (xdc_Char)0x74,  /* [2417] */
    (xdc_Char)0x20,  /* [2418] */
    (xdc_Char)0x62,  /* [2419] */
    (xdc_Char)0x65,  /* [2420] */
    (xdc_Char)0x20,  /* [2421] */
    (xdc_Char)0x7a,  /* [2422] */
    (xdc_Char)0x65,  /* [2423] */
    (xdc_Char)0x72,  /* [2424] */
    (xdc_Char)0x6f,  /* [2425] */
    (xdc_Char)0x0,  /* [2426] */
    (xdc_Char)0x41,  /* [2427] */
    (xdc_Char)0x5f,  /* [2428] */
    (xdc_Char)0x69,  /* [2429] */
    (xdc_Char)0x6e,  /* [2430] */
    (xdc_Char)0x76,  /* [2431] */
    (xdc_Char)0x61,  /* [2432] */
    (xdc_Char)0x6c,  /* [2433] */
    (xdc_Char)0x69,  /* [2434] */
    (xdc_Char)0x64,  /* [2435] */
    (xdc_Char)0x4b,  /* [2436] */
    (xdc_Char)0x65,  /* [2437] */
    (xdc_Char)0x79,  /* [2438] */
    (xdc_Char)0x3a,  /* [2439] */
    (xdc_Char)0x20,  /* [2440] */
    (xdc_Char)0x74,  /* [2441] */
    (xdc_Char)0x68,  /* [2442] */
    (xdc_Char)0x65,  /* [2443] */
    (xdc_Char)0x20,  /* [2444] */
    (xdc_Char)0x6b,  /* [2445] */
    (xdc_Char)0x65,  /* [2446] */
    (xdc_Char)0x79,  /* [2447] */
    (xdc_Char)0x20,  /* [2448] */
    (xdc_Char)0x6d,  /* [2449] */
    (xdc_Char)0x75,  /* [2450] */
    (xdc_Char)0x73,  /* [2451] */
    (xdc_Char)0x74,  /* [2452] */
    (xdc_Char)0x20,  /* [2453] */
    (xdc_Char)0x62,  /* [2454] */
    (xdc_Char)0x65,  /* [2455] */
    (xdc_Char)0x20,  /* [2456] */
    (xdc_Char)0x73,  /* [2457] */
    (xdc_Char)0x65,  /* [2458] */
    (xdc_Char)0x74,  /* [2459] */
    (xdc_Char)0x20,  /* [2460] */
    (xdc_Char)0x74,  /* [2461] */
    (xdc_Char)0x6f,  /* [2462] */
    (xdc_Char)0x20,  /* [2463] */
    (xdc_Char)0x61,  /* [2464] */
    (xdc_Char)0x20,  /* [2465] */
    (xdc_Char)0x6e,  /* [2466] */
    (xdc_Char)0x6f,  /* [2467] */
    (xdc_Char)0x6e,  /* [2468] */
    (xdc_Char)0x2d,  /* [2469] */
    (xdc_Char)0x64,  /* [2470] */
    (xdc_Char)0x65,  /* [2471] */
    (xdc_Char)0x66,  /* [2472] */
    (xdc_Char)0x61,  /* [2473] */
    (xdc_Char)0x75,  /* [2474] */
    (xdc_Char)0x6c,  /* [2475] */
    (xdc_Char)0x74,  /* [2476] */
    (xdc_Char)0x20,  /* [2477] */
    (xdc_Char)0x76,  /* [2478] */
    (xdc_Char)0x61,  /* [2479] */
    (xdc_Char)0x6c,  /* [2480] */
    (xdc_Char)0x75,  /* [2481] */
    (xdc_Char)0x65,  /* [2482] */
    (xdc_Char)0x0,  /* [2483] */
    (xdc_Char)0x41,  /* [2484] */
    (xdc_Char)0x5f,  /* [2485] */
    (xdc_Char)0x69,  /* [2486] */
    (xdc_Char)0x6e,  /* [2487] */
    (xdc_Char)0x76,  /* [2488] */
    (xdc_Char)0x61,  /* [2489] */
    (xdc_Char)0x6c,  /* [2490] */
    (xdc_Char)0x69,  /* [2491] */
    (xdc_Char)0x64,  /* [2492] */
    (xdc_Char)0x4c,  /* [2493] */
    (xdc_Char)0x65,  /* [2494] */
    (xdc_Char)0x6e,  /* [2495] */
    (xdc_Char)0x3a,  /* [2496] */
    (xdc_Char)0x20,  /* [2497] */
    (xdc_Char)0x49,  /* [2498] */
    (xdc_Char)0x6e,  /* [2499] */
    (xdc_Char)0x76,  /* [2500] */
    (xdc_Char)0x61,  /* [2501] */
    (xdc_Char)0x6c,  /* [2502] */
    (xdc_Char)0x69,  /* [2503] */
    (xdc_Char)0x64,  /* [2504] */
    (xdc_Char)0x20,  /* [2505] */
    (xdc_Char)0x6c,  /* [2506] */
    (xdc_Char)0x65,  /* [2507] */
    (xdc_Char)0x6e,  /* [2508] */
    (xdc_Char)0x67,  /* [2509] */
    (xdc_Char)0x74,  /* [2510] */
    (xdc_Char)0x68,  /* [2511] */
    (xdc_Char)0x0,  /* [2512] */
    (xdc_Char)0x41,  /* [2513] */
    (xdc_Char)0x5f,  /* [2514] */
    (xdc_Char)0x69,  /* [2515] */
    (xdc_Char)0x6e,  /* [2516] */
    (xdc_Char)0x76,  /* [2517] */
    (xdc_Char)0x41,  /* [2518] */
    (xdc_Char)0x72,  /* [2519] */
    (xdc_Char)0x67,  /* [2520] */
    (xdc_Char)0x75,  /* [2521] */
    (xdc_Char)0x6d,  /* [2522] */
    (xdc_Char)0x65,  /* [2523] */
    (xdc_Char)0x6e,  /* [2524] */
    (xdc_Char)0x74,  /* [2525] */
    (xdc_Char)0x3a,  /* [2526] */
    (xdc_Char)0x20,  /* [2527] */
    (xdc_Char)0x49,  /* [2528] */
    (xdc_Char)0x6e,  /* [2529] */
    (xdc_Char)0x76,  /* [2530] */
    (xdc_Char)0x61,  /* [2531] */
    (xdc_Char)0x6c,  /* [2532] */
    (xdc_Char)0x69,  /* [2533] */
    (xdc_Char)0x64,  /* [2534] */
    (xdc_Char)0x20,  /* [2535] */
    (xdc_Char)0x61,  /* [2536] */
    (xdc_Char)0x72,  /* [2537] */
    (xdc_Char)0x67,  /* [2538] */
    (xdc_Char)0x75,  /* [2539] */
    (xdc_Char)0x6d,  /* [2540] */
    (xdc_Char)0x65,  /* [2541] */
    (xdc_Char)0x6e,  /* [2542] */
    (xdc_Char)0x74,  /* [2543] */
    (xdc_Char)0x20,  /* [2544] */
    (xdc_Char)0x73,  /* [2545] */
    (xdc_Char)0x75,  /* [2546] */
    (xdc_Char)0x70,  /* [2547] */
    (xdc_Char)0x70,  /* [2548] */
    (xdc_Char)0x6c,  /* [2549] */
    (xdc_Char)0x69,  /* [2550] */
    (xdc_Char)0x65,  /* [2551] */
    (xdc_Char)0x64,  /* [2552] */
    (xdc_Char)0x0,  /* [2553] */
    (xdc_Char)0x41,  /* [2554] */
    (xdc_Char)0x5f,  /* [2555] */
    (xdc_Char)0x69,  /* [2556] */
    (xdc_Char)0x6e,  /* [2557] */
    (xdc_Char)0x76,  /* [2558] */
    (xdc_Char)0x61,  /* [2559] */
    (xdc_Char)0x6c,  /* [2560] */
    (xdc_Char)0x69,  /* [2561] */
    (xdc_Char)0x64,  /* [2562] */
    (xdc_Char)0x4d,  /* [2563] */
    (xdc_Char)0x75,  /* [2564] */
    (xdc_Char)0x6c,  /* [2565] */
    (xdc_Char)0x74,  /* [2566] */
    (xdc_Char)0x69,  /* [2567] */
    (xdc_Char)0x50,  /* [2568] */
    (xdc_Char)0x72,  /* [2569] */
    (xdc_Char)0x6f,  /* [2570] */
    (xdc_Char)0x63,  /* [2571] */
    (xdc_Char)0x49,  /* [2572] */
    (xdc_Char)0x64,  /* [2573] */
    (xdc_Char)0x3a,  /* [2574] */
    (xdc_Char)0x20,  /* [2575] */
    (xdc_Char)0x49,  /* [2576] */
    (xdc_Char)0x6e,  /* [2577] */
    (xdc_Char)0x76,  /* [2578] */
    (xdc_Char)0x61,  /* [2579] */
    (xdc_Char)0x6c,  /* [2580] */
    (xdc_Char)0x69,  /* [2581] */
    (xdc_Char)0x64,  /* [2582] */
    (xdc_Char)0x20,  /* [2583] */
    (xdc_Char)0x4d,  /* [2584] */
    (xdc_Char)0x75,  /* [2585] */
    (xdc_Char)0x6c,  /* [2586] */
    (xdc_Char)0x74,  /* [2587] */
    (xdc_Char)0x69,  /* [2588] */
    (xdc_Char)0x50,  /* [2589] */
    (xdc_Char)0x72,  /* [2590] */
    (xdc_Char)0x6f,  /* [2591] */
    (xdc_Char)0x63,  /* [2592] */
    (xdc_Char)0x20,  /* [2593] */
    (xdc_Char)0x69,  /* [2594] */
    (xdc_Char)0x64,  /* [2595] */
    (xdc_Char)0x0,  /* [2596] */
    (xdc_Char)0x41,  /* [2597] */
    (xdc_Char)0x5f,  /* [2598] */
    (xdc_Char)0x69,  /* [2599] */
    (xdc_Char)0x6e,  /* [2600] */
    (xdc_Char)0x76,  /* [2601] */
    (xdc_Char)0x61,  /* [2602] */
    (xdc_Char)0x6c,  /* [2603] */
    (xdc_Char)0x69,  /* [2604] */
    (xdc_Char)0x64,  /* [2605] */
    (xdc_Char)0x50,  /* [2606] */
    (xdc_Char)0x72,  /* [2607] */
    (xdc_Char)0x6f,  /* [2608] */
    (xdc_Char)0x63,  /* [2609] */
    (xdc_Char)0x4e,  /* [2610] */
    (xdc_Char)0x61,  /* [2611] */
    (xdc_Char)0x6d,  /* [2612] */
    (xdc_Char)0x65,  /* [2613] */
    (xdc_Char)0x3a,  /* [2614] */
    (xdc_Char)0x20,  /* [2615] */
    (xdc_Char)0x4e,  /* [2616] */
    (xdc_Char)0x55,  /* [2617] */
    (xdc_Char)0x4c,  /* [2618] */
    (xdc_Char)0x4c,  /* [2619] */
    (xdc_Char)0x20,  /* [2620] */
    (xdc_Char)0x4d,  /* [2621] */
    (xdc_Char)0x75,  /* [2622] */
    (xdc_Char)0x6c,  /* [2623] */
    (xdc_Char)0x74,  /* [2624] */
    (xdc_Char)0x69,  /* [2625] */
    (xdc_Char)0x50,  /* [2626] */
    (xdc_Char)0x72,  /* [2627] */
    (xdc_Char)0x6f,  /* [2628] */
    (xdc_Char)0x63,  /* [2629] */
    (xdc_Char)0x20,  /* [2630] */
    (xdc_Char)0x6e,  /* [2631] */
    (xdc_Char)0x61,  /* [2632] */
    (xdc_Char)0x6d,  /* [2633] */
    (xdc_Char)0x65,  /* [2634] */
    (xdc_Char)0x20,  /* [2635] */
    (xdc_Char)0x65,  /* [2636] */
    (xdc_Char)0x6e,  /* [2637] */
    (xdc_Char)0x63,  /* [2638] */
    (xdc_Char)0x6f,  /* [2639] */
    (xdc_Char)0x75,  /* [2640] */
    (xdc_Char)0x6e,  /* [2641] */
    (xdc_Char)0x74,  /* [2642] */
    (xdc_Char)0x65,  /* [2643] */
    (xdc_Char)0x72,  /* [2644] */
    (xdc_Char)0x65,  /* [2645] */
    (xdc_Char)0x64,  /* [2646] */
    (xdc_Char)0x0,  /* [2647] */
    (xdc_Char)0x61,  /* [2648] */
    (xdc_Char)0x73,  /* [2649] */
    (xdc_Char)0x73,  /* [2650] */
    (xdc_Char)0x65,  /* [2651] */
    (xdc_Char)0x72,  /* [2652] */
    (xdc_Char)0x74,  /* [2653] */
    (xdc_Char)0x69,  /* [2654] */
    (xdc_Char)0x6f,  /* [2655] */
    (xdc_Char)0x6e,  /* [2656] */
    (xdc_Char)0x20,  /* [2657] */
    (xdc_Char)0x66,  /* [2658] */
    (xdc_Char)0x61,  /* [2659] */
    (xdc_Char)0x69,  /* [2660] */
    (xdc_Char)0x6c,  /* [2661] */
    (xdc_Char)0x75,  /* [2662] */
    (xdc_Char)0x72,  /* [2663] */
    (xdc_Char)0x65,  /* [2664] */
    (xdc_Char)0x25,  /* [2665] */
    (xdc_Char)0x73,  /* [2666] */
    (xdc_Char)0x25,  /* [2667] */
    (xdc_Char)0x73,  /* [2668] */
    (xdc_Char)0x0,  /* [2669] */
    (xdc_Char)0x25,  /* [2670] */
    (xdc_Char)0x24,  /* [2671] */
    (xdc_Char)0x53,  /* [2672] */
    (xdc_Char)0x0,  /* [2673] */
    (xdc_Char)0x6f,  /* [2674] */
    (xdc_Char)0x75,  /* [2675] */
    (xdc_Char)0x74,  /* [2676] */
    (xdc_Char)0x20,  /* [2677] */
    (xdc_Char)0x6f,  /* [2678] */
    (xdc_Char)0x66,  /* [2679] */
    (xdc_Char)0x20,  /* [2680] */
    (xdc_Char)0x6d,  /* [2681] */
    (xdc_Char)0x65,  /* [2682] */
    (xdc_Char)0x6d,  /* [2683] */
    (xdc_Char)0x6f,  /* [2684] */
    (xdc_Char)0x72,  /* [2685] */
    (xdc_Char)0x79,  /* [2686] */
    (xdc_Char)0x3a,  /* [2687] */
    (xdc_Char)0x20,  /* [2688] */
    (xdc_Char)0x68,  /* [2689] */
    (xdc_Char)0x65,  /* [2690] */
    (xdc_Char)0x61,  /* [2691] */
    (xdc_Char)0x70,  /* [2692] */
    (xdc_Char)0x3d,  /* [2693] */
    (xdc_Char)0x30,  /* [2694] */
    (xdc_Char)0x78,  /* [2695] */
    (xdc_Char)0x25,  /* [2696] */
    (xdc_Char)0x78,  /* [2697] */
    (xdc_Char)0x2c,  /* [2698] */
    (xdc_Char)0x20,  /* [2699] */
    (xdc_Char)0x73,  /* [2700] */
    (xdc_Char)0x69,  /* [2701] */
    (xdc_Char)0x7a,  /* [2702] */
    (xdc_Char)0x65,  /* [2703] */
    (xdc_Char)0x3d,  /* [2704] */
    (xdc_Char)0x25,  /* [2705] */
    (xdc_Char)0x75,  /* [2706] */
    (xdc_Char)0x0,  /* [2707] */
    (xdc_Char)0x25,  /* [2708] */
    (xdc_Char)0x73,  /* [2709] */
    (xdc_Char)0x20,  /* [2710] */
    (xdc_Char)0x30,  /* [2711] */
    (xdc_Char)0x78,  /* [2712] */
    (xdc_Char)0x25,  /* [2713] */
    (xdc_Char)0x78,  /* [2714] */
    (xdc_Char)0x0,  /* [2715] */
    (xdc_Char)0x45,  /* [2716] */
    (xdc_Char)0x5f,  /* [2717] */
    (xdc_Char)0x62,  /* [2718] */
    (xdc_Char)0x61,  /* [2719] */
    (xdc_Char)0x64,  /* [2720] */
    (xdc_Char)0x4c,  /* [2721] */
    (xdc_Char)0x65,  /* [2722] */
    (xdc_Char)0x76,  /* [2723] */
    (xdc_Char)0x65,  /* [2724] */
    (xdc_Char)0x6c,  /* [2725] */
    (xdc_Char)0x3a,  /* [2726] */
    (xdc_Char)0x20,  /* [2727] */
    (xdc_Char)0x42,  /* [2728] */
    (xdc_Char)0x61,  /* [2729] */
    (xdc_Char)0x64,  /* [2730] */
    (xdc_Char)0x20,  /* [2731] */
    (xdc_Char)0x66,  /* [2732] */
    (xdc_Char)0x69,  /* [2733] */
    (xdc_Char)0x6c,  /* [2734] */
    (xdc_Char)0x74,  /* [2735] */
    (xdc_Char)0x65,  /* [2736] */
    (xdc_Char)0x72,  /* [2737] */
    (xdc_Char)0x20,  /* [2738] */
    (xdc_Char)0x6c,  /* [2739] */
    (xdc_Char)0x65,  /* [2740] */
    (xdc_Char)0x76,  /* [2741] */
    (xdc_Char)0x65,  /* [2742] */
    (xdc_Char)0x6c,  /* [2743] */
    (xdc_Char)0x20,  /* [2744] */
    (xdc_Char)0x76,  /* [2745] */
    (xdc_Char)0x61,  /* [2746] */
    (xdc_Char)0x6c,  /* [2747] */
    (xdc_Char)0x75,  /* [2748] */
    (xdc_Char)0x65,  /* [2749] */
    (xdc_Char)0x3a,  /* [2750] */
    (xdc_Char)0x20,  /* [2751] */
    (xdc_Char)0x25,  /* [2752] */
    (xdc_Char)0x64,  /* [2753] */
    (xdc_Char)0x0,  /* [2754] */
    (xdc_Char)0x66,  /* [2755] */
    (xdc_Char)0x72,  /* [2756] */
    (xdc_Char)0x65,  /* [2757] */
    (xdc_Char)0x65,  /* [2758] */
    (xdc_Char)0x28,  /* [2759] */
    (xdc_Char)0x29,  /* [2760] */
    (xdc_Char)0x20,  /* [2761] */
    (xdc_Char)0x69,  /* [2762] */
    (xdc_Char)0x6e,  /* [2763] */
    (xdc_Char)0x76,  /* [2764] */
    (xdc_Char)0x61,  /* [2765] */
    (xdc_Char)0x6c,  /* [2766] */
    (xdc_Char)0x69,  /* [2767] */
    (xdc_Char)0x64,  /* [2768] */
    (xdc_Char)0x20,  /* [2769] */
    (xdc_Char)0x69,  /* [2770] */
    (xdc_Char)0x6e,  /* [2771] */
    (xdc_Char)0x20,  /* [2772] */
    (xdc_Char)0x67,  /* [2773] */
    (xdc_Char)0x72,  /* [2774] */
    (xdc_Char)0x6f,  /* [2775] */
    (xdc_Char)0x77,  /* [2776] */
    (xdc_Char)0x74,  /* [2777] */
    (xdc_Char)0x68,  /* [2778] */
    (xdc_Char)0x2d,  /* [2779] */
    (xdc_Char)0x6f,  /* [2780] */
    (xdc_Char)0x6e,  /* [2781] */
    (xdc_Char)0x6c,  /* [2782] */
    (xdc_Char)0x79,  /* [2783] */
    (xdc_Char)0x20,  /* [2784] */
    (xdc_Char)0x48,  /* [2785] */
    (xdc_Char)0x65,  /* [2786] */
    (xdc_Char)0x61,  /* [2787] */
    (xdc_Char)0x70,  /* [2788] */
    (xdc_Char)0x4d,  /* [2789] */
    (xdc_Char)0x69,  /* [2790] */
    (xdc_Char)0x6e,  /* [2791] */
    (xdc_Char)0x0,  /* [2792] */
    (xdc_Char)0x54,  /* [2793] */
    (xdc_Char)0x68,  /* [2794] */
    (xdc_Char)0x65,  /* [2795] */
    (xdc_Char)0x20,  /* [2796] */
    (xdc_Char)0x52,  /* [2797] */
    (xdc_Char)0x54,  /* [2798] */
    (xdc_Char)0x53,  /* [2799] */
    (xdc_Char)0x20,  /* [2800] */
    (xdc_Char)0x68,  /* [2801] */
    (xdc_Char)0x65,  /* [2802] */
    (xdc_Char)0x61,  /* [2803] */
    (xdc_Char)0x70,  /* [2804] */
    (xdc_Char)0x20,  /* [2805] */
    (xdc_Char)0x69,  /* [2806] */
    (xdc_Char)0x73,  /* [2807] */
    (xdc_Char)0x20,  /* [2808] */
    (xdc_Char)0x75,  /* [2809] */
    (xdc_Char)0x73,  /* [2810] */
    (xdc_Char)0x65,  /* [2811] */
    (xdc_Char)0x64,  /* [2812] */
    (xdc_Char)0x20,  /* [2813] */
    (xdc_Char)0x75,  /* [2814] */
    (xdc_Char)0x70,  /* [2815] */
    (xdc_Char)0x2e,  /* [2816] */
    (xdc_Char)0x20,  /* [2817] */
    (xdc_Char)0x45,  /* [2818] */
    (xdc_Char)0x78,  /* [2819] */
    (xdc_Char)0x61,  /* [2820] */
    (xdc_Char)0x6d,  /* [2821] */
    (xdc_Char)0x69,  /* [2822] */
    (xdc_Char)0x6e,  /* [2823] */
    (xdc_Char)0x65,  /* [2824] */
    (xdc_Char)0x20,  /* [2825] */
    (xdc_Char)0x50,  /* [2826] */
    (xdc_Char)0x72,  /* [2827] */
    (xdc_Char)0x6f,  /* [2828] */
    (xdc_Char)0x67,  /* [2829] */
    (xdc_Char)0x72,  /* [2830] */
    (xdc_Char)0x61,  /* [2831] */
    (xdc_Char)0x6d,  /* [2832] */
    (xdc_Char)0x2e,  /* [2833] */
    (xdc_Char)0x68,  /* [2834] */
    (xdc_Char)0x65,  /* [2835] */
    (xdc_Char)0x61,  /* [2836] */
    (xdc_Char)0x70,  /* [2837] */
    (xdc_Char)0x2e,  /* [2838] */
    (xdc_Char)0x0,  /* [2839] */
    (xdc_Char)0x45,  /* [2840] */
    (xdc_Char)0x5f,  /* [2841] */
    (xdc_Char)0x62,  /* [2842] */
    (xdc_Char)0x61,  /* [2843] */
    (xdc_Char)0x64,  /* [2844] */
    (xdc_Char)0x43,  /* [2845] */
    (xdc_Char)0x6f,  /* [2846] */
    (xdc_Char)0x6d,  /* [2847] */
    (xdc_Char)0x6d,  /* [2848] */
    (xdc_Char)0x61,  /* [2849] */
    (xdc_Char)0x6e,  /* [2850] */
    (xdc_Char)0x64,  /* [2851] */
    (xdc_Char)0x3a,  /* [2852] */
    (xdc_Char)0x20,  /* [2853] */
    (xdc_Char)0x52,  /* [2854] */
    (xdc_Char)0x65,  /* [2855] */
    (xdc_Char)0x63,  /* [2856] */
    (xdc_Char)0x65,  /* [2857] */
    (xdc_Char)0x69,  /* [2858] */
    (xdc_Char)0x76,  /* [2859] */
    (xdc_Char)0x65,  /* [2860] */
    (xdc_Char)0x64,  /* [2861] */
    (xdc_Char)0x20,  /* [2862] */
    (xdc_Char)0x69,  /* [2863] */
    (xdc_Char)0x6e,  /* [2864] */
    (xdc_Char)0x76,  /* [2865] */
    (xdc_Char)0x61,  /* [2866] */
    (xdc_Char)0x6c,  /* [2867] */
    (xdc_Char)0x69,  /* [2868] */
    (xdc_Char)0x64,  /* [2869] */
    (xdc_Char)0x20,  /* [2870] */
    (xdc_Char)0x63,  /* [2871] */
    (xdc_Char)0x6f,  /* [2872] */
    (xdc_Char)0x6d,  /* [2873] */
    (xdc_Char)0x6d,  /* [2874] */
    (xdc_Char)0x61,  /* [2875] */
    (xdc_Char)0x6e,  /* [2876] */
    (xdc_Char)0x64,  /* [2877] */
    (xdc_Char)0x2c,  /* [2878] */
    (xdc_Char)0x20,  /* [2879] */
    (xdc_Char)0x69,  /* [2880] */
    (xdc_Char)0x64,  /* [2881] */
    (xdc_Char)0x3a,  /* [2882] */
    (xdc_Char)0x20,  /* [2883] */
    (xdc_Char)0x25,  /* [2884] */
    (xdc_Char)0x64,  /* [2885] */
    (xdc_Char)0x2e,  /* [2886] */
    (xdc_Char)0x0,  /* [2887] */
    (xdc_Char)0x45,  /* [2888] */
    (xdc_Char)0x5f,  /* [2889] */
    (xdc_Char)0x75,  /* [2890] */
    (xdc_Char)0x6e,  /* [2891] */
    (xdc_Char)0x70,  /* [2892] */
    (xdc_Char)0x6c,  /* [2893] */
    (xdc_Char)0x75,  /* [2894] */
    (xdc_Char)0x67,  /* [2895] */
    (xdc_Char)0x67,  /* [2896] */
    (xdc_Char)0x65,  /* [2897] */
    (xdc_Char)0x64,  /* [2898] */
    (xdc_Char)0x45,  /* [2899] */
    (xdc_Char)0x76,  /* [2900] */
    (xdc_Char)0x65,  /* [2901] */
    (xdc_Char)0x6e,  /* [2902] */
    (xdc_Char)0x74,  /* [2903] */
    (xdc_Char)0x3a,  /* [2904] */
    (xdc_Char)0x20,  /* [2905] */
    (xdc_Char)0x45,  /* [2906] */
    (xdc_Char)0x76,  /* [2907] */
    (xdc_Char)0x65,  /* [2908] */
    (xdc_Char)0x6e,  /* [2909] */
    (xdc_Char)0x74,  /* [2910] */
    (xdc_Char)0x23,  /* [2911] */
    (xdc_Char)0x20,  /* [2912] */
    (xdc_Char)0x25,  /* [2913] */
    (xdc_Char)0x64,  /* [2914] */
    (xdc_Char)0x20,  /* [2915] */
    (xdc_Char)0x69,  /* [2916] */
    (xdc_Char)0x73,  /* [2917] */
    (xdc_Char)0x20,  /* [2918] */
    (xdc_Char)0x75,  /* [2919] */
    (xdc_Char)0x6e,  /* [2920] */
    (xdc_Char)0x70,  /* [2921] */
    (xdc_Char)0x6c,  /* [2922] */
    (xdc_Char)0x75,  /* [2923] */
    (xdc_Char)0x67,  /* [2924] */
    (xdc_Char)0x67,  /* [2925] */
    (xdc_Char)0x65,  /* [2926] */
    (xdc_Char)0x64,  /* [2927] */
    (xdc_Char)0x0,  /* [2928] */
    (xdc_Char)0x45,  /* [2929] */
    (xdc_Char)0x5f,  /* [2930] */
    (xdc_Char)0x65,  /* [2931] */
    (xdc_Char)0x78,  /* [2932] */
    (xdc_Char)0x63,  /* [2933] */
    (xdc_Char)0x65,  /* [2934] */
    (xdc_Char)0x70,  /* [2935] */
    (xdc_Char)0x74,  /* [2936] */
    (xdc_Char)0x69,  /* [2937] */
    (xdc_Char)0x6f,  /* [2938] */
    (xdc_Char)0x6e,  /* [2939] */
    (xdc_Char)0x4d,  /* [2940] */
    (xdc_Char)0x69,  /* [2941] */
    (xdc_Char)0x6e,  /* [2942] */
    (xdc_Char)0x3a,  /* [2943] */
    (xdc_Char)0x20,  /* [2944] */
    (xdc_Char)0x70,  /* [2945] */
    (xdc_Char)0x63,  /* [2946] */
    (xdc_Char)0x20,  /* [2947] */
    (xdc_Char)0x3d,  /* [2948] */
    (xdc_Char)0x20,  /* [2949] */
    (xdc_Char)0x30,  /* [2950] */
    (xdc_Char)0x78,  /* [2951] */
    (xdc_Char)0x25,  /* [2952] */
    (xdc_Char)0x30,  /* [2953] */
    (xdc_Char)0x38,  /* [2954] */
    (xdc_Char)0x78,  /* [2955] */
    (xdc_Char)0x2c,  /* [2956] */
    (xdc_Char)0x20,  /* [2957] */
    (xdc_Char)0x73,  /* [2958] */
    (xdc_Char)0x70,  /* [2959] */
    (xdc_Char)0x20,  /* [2960] */
    (xdc_Char)0x3d,  /* [2961] */
    (xdc_Char)0x20,  /* [2962] */
    (xdc_Char)0x30,  /* [2963] */
    (xdc_Char)0x78,  /* [2964] */
    (xdc_Char)0x25,  /* [2965] */
    (xdc_Char)0x30,  /* [2966] */
    (xdc_Char)0x38,  /* [2967] */
    (xdc_Char)0x78,  /* [2968] */
    (xdc_Char)0x2e,  /* [2969] */
    (xdc_Char)0xa,  /* [2970] */
    (xdc_Char)0x54,  /* [2971] */
    (xdc_Char)0x6f,  /* [2972] */
    (xdc_Char)0x20,  /* [2973] */
    (xdc_Char)0x73,  /* [2974] */
    (xdc_Char)0x65,  /* [2975] */
    (xdc_Char)0x65,  /* [2976] */
    (xdc_Char)0x20,  /* [2977] */
    (xdc_Char)0x6d,  /* [2978] */
    (xdc_Char)0x6f,  /* [2979] */
    (xdc_Char)0x72,  /* [2980] */
    (xdc_Char)0x65,  /* [2981] */
    (xdc_Char)0x20,  /* [2982] */
    (xdc_Char)0x65,  /* [2983] */
    (xdc_Char)0x78,  /* [2984] */
    (xdc_Char)0x63,  /* [2985] */
    (xdc_Char)0x65,  /* [2986] */
    (xdc_Char)0x70,  /* [2987] */
    (xdc_Char)0x74,  /* [2988] */
    (xdc_Char)0x69,  /* [2989] */
    (xdc_Char)0x6f,  /* [2990] */
    (xdc_Char)0x6e,  /* [2991] */
    (xdc_Char)0x20,  /* [2992] */
    (xdc_Char)0x64,  /* [2993] */
    (xdc_Char)0x65,  /* [2994] */
    (xdc_Char)0x74,  /* [2995] */
    (xdc_Char)0x61,  /* [2996] */
    (xdc_Char)0x69,  /* [2997] */
    (xdc_Char)0x6c,  /* [2998] */
    (xdc_Char)0x2c,  /* [2999] */
    (xdc_Char)0x20,  /* [3000] */
    (xdc_Char)0x75,  /* [3001] */
    (xdc_Char)0x73,  /* [3002] */
    (xdc_Char)0x65,  /* [3003] */
    (xdc_Char)0x20,  /* [3004] */
    (xdc_Char)0x52,  /* [3005] */
    (xdc_Char)0x4f,  /* [3006] */
    (xdc_Char)0x56,  /* [3007] */
    (xdc_Char)0x20,  /* [3008] */
    (xdc_Char)0x6f,  /* [3009] */
    (xdc_Char)0x72,  /* [3010] */
    (xdc_Char)0x20,  /* [3011] */
    (xdc_Char)0x73,  /* [3012] */
    (xdc_Char)0x65,  /* [3013] */
    (xdc_Char)0x74,  /* [3014] */
    (xdc_Char)0x20,  /* [3015] */
    (xdc_Char)0x27,  /* [3016] */
    (xdc_Char)0x74,  /* [3017] */
    (xdc_Char)0x69,  /* [3018] */
    (xdc_Char)0x2e,  /* [3019] */
    (xdc_Char)0x73,  /* [3020] */
    (xdc_Char)0x79,  /* [3021] */
    (xdc_Char)0x73,  /* [3022] */
    (xdc_Char)0x62,  /* [3023] */
    (xdc_Char)0x69,  /* [3024] */
    (xdc_Char)0x6f,  /* [3025] */
    (xdc_Char)0x73,  /* [3026] */
    (xdc_Char)0x2e,  /* [3027] */
    (xdc_Char)0x66,  /* [3028] */
    (xdc_Char)0x61,  /* [3029] */
    (xdc_Char)0x6d,  /* [3030] */
    (xdc_Char)0x69,  /* [3031] */
    (xdc_Char)0x6c,  /* [3032] */
    (xdc_Char)0x79,  /* [3033] */
    (xdc_Char)0x2e,  /* [3034] */
    (xdc_Char)0x63,  /* [3035] */
    (xdc_Char)0x36,  /* [3036] */
    (xdc_Char)0x34,  /* [3037] */
    (xdc_Char)0x70,  /* [3038] */
    (xdc_Char)0x2e,  /* [3039] */
    (xdc_Char)0x45,  /* [3040] */
    (xdc_Char)0x78,  /* [3041] */
    (xdc_Char)0x63,  /* [3042] */
    (xdc_Char)0x65,  /* [3043] */
    (xdc_Char)0x70,  /* [3044] */
    (xdc_Char)0x74,  /* [3045] */
    (xdc_Char)0x69,  /* [3046] */
    (xdc_Char)0x6f,  /* [3047] */
    (xdc_Char)0x6e,  /* [3048] */
    (xdc_Char)0x2e,  /* [3049] */
    (xdc_Char)0x65,  /* [3050] */
    (xdc_Char)0x6e,  /* [3051] */
    (xdc_Char)0x61,  /* [3052] */
    (xdc_Char)0x62,  /* [3053] */
    (xdc_Char)0x6c,  /* [3054] */
    (xdc_Char)0x65,  /* [3055] */
    (xdc_Char)0x50,  /* [3056] */
    (xdc_Char)0x72,  /* [3057] */
    (xdc_Char)0x69,  /* [3058] */
    (xdc_Char)0x6e,  /* [3059] */
    (xdc_Char)0x74,  /* [3060] */
    (xdc_Char)0x20,  /* [3061] */
    (xdc_Char)0x3d,  /* [3062] */
    (xdc_Char)0x20,  /* [3063] */
    (xdc_Char)0x74,  /* [3064] */
    (xdc_Char)0x72,  /* [3065] */
    (xdc_Char)0x75,  /* [3066] */
    (xdc_Char)0x65,  /* [3067] */
    (xdc_Char)0x3b,  /* [3068] */
    (xdc_Char)0x27,  /* [3069] */
    (xdc_Char)0x0,  /* [3070] */
    (xdc_Char)0x45,  /* [3071] */
    (xdc_Char)0x5f,  /* [3072] */
    (xdc_Char)0x65,  /* [3073] */
    (xdc_Char)0x78,  /* [3074] */
    (xdc_Char)0x63,  /* [3075] */
    (xdc_Char)0x65,  /* [3076] */
    (xdc_Char)0x70,  /* [3077] */
    (xdc_Char)0x74,  /* [3078] */
    (xdc_Char)0x69,  /* [3079] */
    (xdc_Char)0x6f,  /* [3080] */
    (xdc_Char)0x6e,  /* [3081] */
    (xdc_Char)0x4d,  /* [3082] */
    (xdc_Char)0x61,  /* [3083] */
    (xdc_Char)0x78,  /* [3084] */
    (xdc_Char)0x3a,  /* [3085] */
    (xdc_Char)0x20,  /* [3086] */
    (xdc_Char)0x70,  /* [3087] */
    (xdc_Char)0x63,  /* [3088] */
    (xdc_Char)0x20,  /* [3089] */
    (xdc_Char)0x3d,  /* [3090] */
    (xdc_Char)0x20,  /* [3091] */
    (xdc_Char)0x30,  /* [3092] */
    (xdc_Char)0x78,  /* [3093] */
    (xdc_Char)0x25,  /* [3094] */
    (xdc_Char)0x30,  /* [3095] */
    (xdc_Char)0x38,  /* [3096] */
    (xdc_Char)0x78,  /* [3097] */
    (xdc_Char)0x2c,  /* [3098] */
    (xdc_Char)0x20,  /* [3099] */
    (xdc_Char)0x73,  /* [3100] */
    (xdc_Char)0x70,  /* [3101] */
    (xdc_Char)0x20,  /* [3102] */
    (xdc_Char)0x3d,  /* [3103] */
    (xdc_Char)0x20,  /* [3104] */
    (xdc_Char)0x30,  /* [3105] */
    (xdc_Char)0x78,  /* [3106] */
    (xdc_Char)0x25,  /* [3107] */
    (xdc_Char)0x30,  /* [3108] */
    (xdc_Char)0x38,  /* [3109] */
    (xdc_Char)0x78,  /* [3110] */
    (xdc_Char)0x2e,  /* [3111] */
    (xdc_Char)0x0,  /* [3112] */
    (xdc_Char)0x45,  /* [3113] */
    (xdc_Char)0x5f,  /* [3114] */
    (xdc_Char)0x61,  /* [3115] */
    (xdc_Char)0x6c,  /* [3116] */
    (xdc_Char)0x72,  /* [3117] */
    (xdc_Char)0x65,  /* [3118] */
    (xdc_Char)0x61,  /* [3119] */
    (xdc_Char)0x64,  /* [3120] */
    (xdc_Char)0x79,  /* [3121] */
    (xdc_Char)0x44,  /* [3122] */
    (xdc_Char)0x65,  /* [3123] */
    (xdc_Char)0x66,  /* [3124] */
    (xdc_Char)0x69,  /* [3125] */
    (xdc_Char)0x6e,  /* [3126] */
    (xdc_Char)0x65,  /* [3127] */
    (xdc_Char)0x64,  /* [3128] */
    (xdc_Char)0x3a,  /* [3129] */
    (xdc_Char)0x20,  /* [3130] */
    (xdc_Char)0x48,  /* [3131] */
    (xdc_Char)0x77,  /* [3132] */
    (xdc_Char)0x69,  /* [3133] */
    (xdc_Char)0x20,  /* [3134] */
    (xdc_Char)0x61,  /* [3135] */
    (xdc_Char)0x6c,  /* [3136] */
    (xdc_Char)0x72,  /* [3137] */
    (xdc_Char)0x65,  /* [3138] */
    (xdc_Char)0x61,  /* [3139] */
    (xdc_Char)0x64,  /* [3140] */
    (xdc_Char)0x79,  /* [3141] */
    (xdc_Char)0x20,  /* [3142] */
    (xdc_Char)0x64,  /* [3143] */
    (xdc_Char)0x65,  /* [3144] */
    (xdc_Char)0x66,  /* [3145] */
    (xdc_Char)0x69,  /* [3146] */
    (xdc_Char)0x6e,  /* [3147] */
    (xdc_Char)0x65,  /* [3148] */
    (xdc_Char)0x64,  /* [3149] */
    (xdc_Char)0x3a,  /* [3150] */
    (xdc_Char)0x20,  /* [3151] */
    (xdc_Char)0x69,  /* [3152] */
    (xdc_Char)0x6e,  /* [3153] */
    (xdc_Char)0x74,  /* [3154] */
    (xdc_Char)0x72,  /* [3155] */
    (xdc_Char)0x23,  /* [3156] */
    (xdc_Char)0x20,  /* [3157] */
    (xdc_Char)0x25,  /* [3158] */
    (xdc_Char)0x64,  /* [3159] */
    (xdc_Char)0x0,  /* [3160] */
    (xdc_Char)0x45,  /* [3161] */
    (xdc_Char)0x5f,  /* [3162] */
    (xdc_Char)0x68,  /* [3163] */
    (xdc_Char)0x61,  /* [3164] */
    (xdc_Char)0x6e,  /* [3165] */
    (xdc_Char)0x64,  /* [3166] */
    (xdc_Char)0x6c,  /* [3167] */
    (xdc_Char)0x65,  /* [3168] */
    (xdc_Char)0x4e,  /* [3169] */
    (xdc_Char)0x6f,  /* [3170] */
    (xdc_Char)0x74,  /* [3171] */
    (xdc_Char)0x46,  /* [3172] */
    (xdc_Char)0x6f,  /* [3173] */
    (xdc_Char)0x75,  /* [3174] */
    (xdc_Char)0x6e,  /* [3175] */
    (xdc_Char)0x64,  /* [3176] */
    (xdc_Char)0x3a,  /* [3177] */
    (xdc_Char)0x20,  /* [3178] */
    (xdc_Char)0x48,  /* [3179] */
    (xdc_Char)0x77,  /* [3180] */
    (xdc_Char)0x69,  /* [3181] */
    (xdc_Char)0x20,  /* [3182] */
    (xdc_Char)0x68,  /* [3183] */
    (xdc_Char)0x61,  /* [3184] */
    (xdc_Char)0x6e,  /* [3185] */
    (xdc_Char)0x64,  /* [3186] */
    (xdc_Char)0x6c,  /* [3187] */
    (xdc_Char)0x65,  /* [3188] */
    (xdc_Char)0x20,  /* [3189] */
    (xdc_Char)0x6e,  /* [3190] */
    (xdc_Char)0x6f,  /* [3191] */
    (xdc_Char)0x74,  /* [3192] */
    (xdc_Char)0x20,  /* [3193] */
    (xdc_Char)0x66,  /* [3194] */
    (xdc_Char)0x6f,  /* [3195] */
    (xdc_Char)0x75,  /* [3196] */
    (xdc_Char)0x6e,  /* [3197] */
    (xdc_Char)0x64,  /* [3198] */
    (xdc_Char)0x3a,  /* [3199] */
    (xdc_Char)0x20,  /* [3200] */
    (xdc_Char)0x30,  /* [3201] */
    (xdc_Char)0x78,  /* [3202] */
    (xdc_Char)0x25,  /* [3203] */
    (xdc_Char)0x78,  /* [3204] */
    (xdc_Char)0x0,  /* [3205] */
    (xdc_Char)0x45,  /* [3206] */
    (xdc_Char)0x5f,  /* [3207] */
    (xdc_Char)0x61,  /* [3208] */
    (xdc_Char)0x6c,  /* [3209] */
    (xdc_Char)0x6c,  /* [3210] */
    (xdc_Char)0x6f,  /* [3211] */
    (xdc_Char)0x63,  /* [3212] */
    (xdc_Char)0x53,  /* [3213] */
    (xdc_Char)0x43,  /* [3214] */
    (xdc_Char)0x46,  /* [3215] */
    (xdc_Char)0x61,  /* [3216] */
    (xdc_Char)0x69,  /* [3217] */
    (xdc_Char)0x6c,  /* [3218] */
    (xdc_Char)0x65,  /* [3219] */
    (xdc_Char)0x64,  /* [3220] */
    (xdc_Char)0x3a,  /* [3221] */
    (xdc_Char)0x20,  /* [3222] */
    (xdc_Char)0x41,  /* [3223] */
    (xdc_Char)0x6c,  /* [3224] */
    (xdc_Char)0x6c,  /* [3225] */
    (xdc_Char)0x6f,  /* [3226] */
    (xdc_Char)0x63,  /* [3227] */
    (xdc_Char)0x20,  /* [3228] */
    (xdc_Char)0x73,  /* [3229] */
    (xdc_Char)0x65,  /* [3230] */
    (xdc_Char)0x63,  /* [3231] */
    (xdc_Char)0x75,  /* [3232] */
    (xdc_Char)0x72,  /* [3233] */
    (xdc_Char)0x65,  /* [3234] */
    (xdc_Char)0x20,  /* [3235] */
    (xdc_Char)0x63,  /* [3236] */
    (xdc_Char)0x6f,  /* [3237] */
    (xdc_Char)0x6e,  /* [3238] */
    (xdc_Char)0x74,  /* [3239] */
    (xdc_Char)0x65,  /* [3240] */
    (xdc_Char)0x78,  /* [3241] */
    (xdc_Char)0x74,  /* [3242] */
    (xdc_Char)0x20,  /* [3243] */
    (xdc_Char)0x66,  /* [3244] */
    (xdc_Char)0x61,  /* [3245] */
    (xdc_Char)0x69,  /* [3246] */
    (xdc_Char)0x6c,  /* [3247] */
    (xdc_Char)0x65,  /* [3248] */
    (xdc_Char)0x64,  /* [3249] */
    (xdc_Char)0x0,  /* [3250] */
    (xdc_Char)0x45,  /* [3251] */
    (xdc_Char)0x5f,  /* [3252] */
    (xdc_Char)0x72,  /* [3253] */
    (xdc_Char)0x65,  /* [3254] */
    (xdc_Char)0x67,  /* [3255] */
    (xdc_Char)0x69,  /* [3256] */
    (xdc_Char)0x73,  /* [3257] */
    (xdc_Char)0x74,  /* [3258] */
    (xdc_Char)0x65,  /* [3259] */
    (xdc_Char)0x72,  /* [3260] */
    (xdc_Char)0x53,  /* [3261] */
    (xdc_Char)0x43,  /* [3262] */
    (xdc_Char)0x46,  /* [3263] */
    (xdc_Char)0x61,  /* [3264] */
    (xdc_Char)0x69,  /* [3265] */
    (xdc_Char)0x6c,  /* [3266] */
    (xdc_Char)0x65,  /* [3267] */
    (xdc_Char)0x64,  /* [3268] */
    (xdc_Char)0x3a,  /* [3269] */
    (xdc_Char)0x20,  /* [3270] */
    (xdc_Char)0x52,  /* [3271] */
    (xdc_Char)0x65,  /* [3272] */
    (xdc_Char)0x67,  /* [3273] */
    (xdc_Char)0x69,  /* [3274] */
    (xdc_Char)0x73,  /* [3275] */
    (xdc_Char)0x74,  /* [3276] */
    (xdc_Char)0x65,  /* [3277] */
    (xdc_Char)0x72,  /* [3278] */
    (xdc_Char)0x20,  /* [3279] */
    (xdc_Char)0x73,  /* [3280] */
    (xdc_Char)0x65,  /* [3281] */
    (xdc_Char)0x63,  /* [3282] */
    (xdc_Char)0x75,  /* [3283] */
    (xdc_Char)0x72,  /* [3284] */
    (xdc_Char)0x65,  /* [3285] */
    (xdc_Char)0x20,  /* [3286] */
    (xdc_Char)0x63,  /* [3287] */
    (xdc_Char)0x6f,  /* [3288] */
    (xdc_Char)0x6e,  /* [3289] */
    (xdc_Char)0x74,  /* [3290] */
    (xdc_Char)0x65,  /* [3291] */
    (xdc_Char)0x78,  /* [3292] */
    (xdc_Char)0x74,  /* [3293] */
    (xdc_Char)0x20,  /* [3294] */
    (xdc_Char)0x66,  /* [3295] */
    (xdc_Char)0x61,  /* [3296] */
    (xdc_Char)0x69,  /* [3297] */
    (xdc_Char)0x6c,  /* [3298] */
    (xdc_Char)0x65,  /* [3299] */
    (xdc_Char)0x64,  /* [3300] */
    (xdc_Char)0x0,  /* [3301] */
    (xdc_Char)0x45,  /* [3302] */
    (xdc_Char)0x5f,  /* [3303] */
    (xdc_Char)0x69,  /* [3304] */
    (xdc_Char)0x6e,  /* [3305] */
    (xdc_Char)0x76,  /* [3306] */
    (xdc_Char)0x61,  /* [3307] */
    (xdc_Char)0x6c,  /* [3308] */
    (xdc_Char)0x69,  /* [3309] */
    (xdc_Char)0x64,  /* [3310] */
    (xdc_Char)0x49,  /* [3311] */
    (xdc_Char)0x6e,  /* [3312] */
    (xdc_Char)0x74,  /* [3313] */
    (xdc_Char)0x4e,  /* [3314] */
    (xdc_Char)0x75,  /* [3315] */
    (xdc_Char)0x6d,  /* [3316] */
    (xdc_Char)0x3a,  /* [3317] */
    (xdc_Char)0x20,  /* [3318] */
    (xdc_Char)0x49,  /* [3319] */
    (xdc_Char)0x6e,  /* [3320] */
    (xdc_Char)0x76,  /* [3321] */
    (xdc_Char)0x61,  /* [3322] */
    (xdc_Char)0x6c,  /* [3323] */
    (xdc_Char)0x69,  /* [3324] */
    (xdc_Char)0x64,  /* [3325] */
    (xdc_Char)0x20,  /* [3326] */
    (xdc_Char)0x69,  /* [3327] */
    (xdc_Char)0x6e,  /* [3328] */
    (xdc_Char)0x74,  /* [3329] */
    (xdc_Char)0x65,  /* [3330] */
    (xdc_Char)0x72,  /* [3331] */
    (xdc_Char)0x72,  /* [3332] */
    (xdc_Char)0x75,  /* [3333] */
    (xdc_Char)0x70,  /* [3334] */
    (xdc_Char)0x74,  /* [3335] */
    (xdc_Char)0x20,  /* [3336] */
    (xdc_Char)0x6e,  /* [3337] */
    (xdc_Char)0x75,  /* [3338] */
    (xdc_Char)0x6d,  /* [3339] */
    (xdc_Char)0x62,  /* [3340] */
    (xdc_Char)0x65,  /* [3341] */
    (xdc_Char)0x72,  /* [3342] */
    (xdc_Char)0x3a,  /* [3343] */
    (xdc_Char)0x20,  /* [3344] */
    (xdc_Char)0x69,  /* [3345] */
    (xdc_Char)0x6e,  /* [3346] */
    (xdc_Char)0x74,  /* [3347] */
    (xdc_Char)0x72,  /* [3348] */
    (xdc_Char)0x23,  /* [3349] */
    (xdc_Char)0x20,  /* [3350] */
    (xdc_Char)0x25,  /* [3351] */
    (xdc_Char)0x64,  /* [3352] */
    (xdc_Char)0x0,  /* [3353] */
    (xdc_Char)0x45,  /* [3354] */
    (xdc_Char)0x5f,  /* [3355] */
    (xdc_Char)0x73,  /* [3356] */
    (xdc_Char)0x74,  /* [3357] */
    (xdc_Char)0x61,  /* [3358] */
    (xdc_Char)0x63,  /* [3359] */
    (xdc_Char)0x6b,  /* [3360] */
    (xdc_Char)0x4f,  /* [3361] */
    (xdc_Char)0x76,  /* [3362] */
    (xdc_Char)0x65,  /* [3363] */
    (xdc_Char)0x72,  /* [3364] */
    (xdc_Char)0x66,  /* [3365] */
    (xdc_Char)0x6c,  /* [3366] */
    (xdc_Char)0x6f,  /* [3367] */
    (xdc_Char)0x77,  /* [3368] */
    (xdc_Char)0x3a,  /* [3369] */
    (xdc_Char)0x20,  /* [3370] */
    (xdc_Char)0x54,  /* [3371] */
    (xdc_Char)0x61,  /* [3372] */
    (xdc_Char)0x73,  /* [3373] */
    (xdc_Char)0x6b,  /* [3374] */
    (xdc_Char)0x20,  /* [3375] */
    (xdc_Char)0x30,  /* [3376] */
    (xdc_Char)0x78,  /* [3377] */
    (xdc_Char)0x25,  /* [3378] */
    (xdc_Char)0x78,  /* [3379] */
    (xdc_Char)0x20,  /* [3380] */
    (xdc_Char)0x73,  /* [3381] */
    (xdc_Char)0x74,  /* [3382] */
    (xdc_Char)0x61,  /* [3383] */
    (xdc_Char)0x63,  /* [3384] */
    (xdc_Char)0x6b,  /* [3385] */
    (xdc_Char)0x20,  /* [3386] */
    (xdc_Char)0x6f,  /* [3387] */
    (xdc_Char)0x76,  /* [3388] */
    (xdc_Char)0x65,  /* [3389] */
    (xdc_Char)0x72,  /* [3390] */
    (xdc_Char)0x66,  /* [3391] */
    (xdc_Char)0x6c,  /* [3392] */
    (xdc_Char)0x6f,  /* [3393] */
    (xdc_Char)0x77,  /* [3394] */
    (xdc_Char)0x2e,  /* [3395] */
    (xdc_Char)0x0,  /* [3396] */
    (xdc_Char)0x45,  /* [3397] */
    (xdc_Char)0x5f,  /* [3398] */
    (xdc_Char)0x73,  /* [3399] */
    (xdc_Char)0x70,  /* [3400] */
    (xdc_Char)0x4f,  /* [3401] */
    (xdc_Char)0x75,  /* [3402] */
    (xdc_Char)0x74,  /* [3403] */
    (xdc_Char)0x4f,  /* [3404] */
    (xdc_Char)0x66,  /* [3405] */
    (xdc_Char)0x42,  /* [3406] */
    (xdc_Char)0x6f,  /* [3407] */
    (xdc_Char)0x75,  /* [3408] */
    (xdc_Char)0x6e,  /* [3409] */
    (xdc_Char)0x64,  /* [3410] */
    (xdc_Char)0x73,  /* [3411] */
    (xdc_Char)0x3a,  /* [3412] */
    (xdc_Char)0x20,  /* [3413] */
    (xdc_Char)0x54,  /* [3414] */
    (xdc_Char)0x61,  /* [3415] */
    (xdc_Char)0x73,  /* [3416] */
    (xdc_Char)0x6b,  /* [3417] */
    (xdc_Char)0x20,  /* [3418] */
    (xdc_Char)0x30,  /* [3419] */
    (xdc_Char)0x78,  /* [3420] */
    (xdc_Char)0x25,  /* [3421] */
    (xdc_Char)0x78,  /* [3422] */
    (xdc_Char)0x20,  /* [3423] */
    (xdc_Char)0x73,  /* [3424] */
    (xdc_Char)0x74,  /* [3425] */
    (xdc_Char)0x61,  /* [3426] */
    (xdc_Char)0x63,  /* [3427] */
    (xdc_Char)0x6b,  /* [3428] */
    (xdc_Char)0x20,  /* [3429] */
    (xdc_Char)0x65,  /* [3430] */
    (xdc_Char)0x72,  /* [3431] */
    (xdc_Char)0x72,  /* [3432] */
    (xdc_Char)0x6f,  /* [3433] */
    (xdc_Char)0x72,  /* [3434] */
    (xdc_Char)0x2c,  /* [3435] */
    (xdc_Char)0x20,  /* [3436] */
    (xdc_Char)0x53,  /* [3437] */
    (xdc_Char)0x50,  /* [3438] */
    (xdc_Char)0x20,  /* [3439] */
    (xdc_Char)0x3d,  /* [3440] */
    (xdc_Char)0x20,  /* [3441] */
    (xdc_Char)0x30,  /* [3442] */
    (xdc_Char)0x78,  /* [3443] */
    (xdc_Char)0x25,  /* [3444] */
    (xdc_Char)0x78,  /* [3445] */
    (xdc_Char)0x2e,  /* [3446] */
    (xdc_Char)0x0,  /* [3447] */
    (xdc_Char)0x45,  /* [3448] */
    (xdc_Char)0x5f,  /* [3449] */
    (xdc_Char)0x64,  /* [3450] */
    (xdc_Char)0x65,  /* [3451] */
    (xdc_Char)0x6c,  /* [3452] */
    (xdc_Char)0x65,  /* [3453] */
    (xdc_Char)0x74,  /* [3454] */
    (xdc_Char)0x65,  /* [3455] */
    (xdc_Char)0x4e,  /* [3456] */
    (xdc_Char)0x6f,  /* [3457] */
    (xdc_Char)0x74,  /* [3458] */
    (xdc_Char)0x41,  /* [3459] */
    (xdc_Char)0x6c,  /* [3460] */
    (xdc_Char)0x6c,  /* [3461] */
    (xdc_Char)0x6f,  /* [3462] */
    (xdc_Char)0x77,  /* [3463] */
    (xdc_Char)0x65,  /* [3464] */
    (xdc_Char)0x64,  /* [3465] */
    (xdc_Char)0x3a,  /* [3466] */
    (xdc_Char)0x20,  /* [3467] */
    (xdc_Char)0x54,  /* [3468] */
    (xdc_Char)0x61,  /* [3469] */
    (xdc_Char)0x73,  /* [3470] */
    (xdc_Char)0x6b,  /* [3471] */
    (xdc_Char)0x20,  /* [3472] */
    (xdc_Char)0x30,  /* [3473] */
    (xdc_Char)0x78,  /* [3474] */
    (xdc_Char)0x25,  /* [3475] */
    (xdc_Char)0x78,  /* [3476] */
    (xdc_Char)0x2e,  /* [3477] */
    (xdc_Char)0x0,  /* [3478] */
    (xdc_Char)0x45,  /* [3479] */
    (xdc_Char)0x5f,  /* [3480] */
    (xdc_Char)0x6d,  /* [3481] */
    (xdc_Char)0x61,  /* [3482] */
    (xdc_Char)0x78,  /* [3483] */
    (xdc_Char)0x52,  /* [3484] */
    (xdc_Char)0x65,  /* [3485] */
    (xdc_Char)0x61,  /* [3486] */
    (xdc_Char)0x63,  /* [3487] */
    (xdc_Char)0x68,  /* [3488] */
    (xdc_Char)0x65,  /* [3489] */
    (xdc_Char)0x64,  /* [3490] */
    (xdc_Char)0x3a,  /* [3491] */
    (xdc_Char)0x20,  /* [3492] */
    (xdc_Char)0x41,  /* [3493] */
    (xdc_Char)0x6c,  /* [3494] */
    (xdc_Char)0x6c,  /* [3495] */
    (xdc_Char)0x20,  /* [3496] */
    (xdc_Char)0x65,  /* [3497] */
    (xdc_Char)0x6e,  /* [3498] */
    (xdc_Char)0x74,  /* [3499] */
    (xdc_Char)0x72,  /* [3500] */
    (xdc_Char)0x69,  /* [3501] */
    (xdc_Char)0x65,  /* [3502] */
    (xdc_Char)0x73,  /* [3503] */
    (xdc_Char)0x20,  /* [3504] */
    (xdc_Char)0x69,  /* [3505] */
    (xdc_Char)0x6e,  /* [3506] */
    (xdc_Char)0x20,  /* [3507] */
    (xdc_Char)0x75,  /* [3508] */
    (xdc_Char)0x73,  /* [3509] */
    (xdc_Char)0x65,  /* [3510] */
    (xdc_Char)0x2e,  /* [3511] */
    (xdc_Char)0x20,  /* [3512] */
    (xdc_Char)0x4e,  /* [3513] */
    (xdc_Char)0x61,  /* [3514] */
    (xdc_Char)0x6d,  /* [3515] */
    (xdc_Char)0x65,  /* [3516] */
    (xdc_Char)0x53,  /* [3517] */
    (xdc_Char)0x65,  /* [3518] */
    (xdc_Char)0x72,  /* [3519] */
    (xdc_Char)0x76,  /* [3520] */
    (xdc_Char)0x65,  /* [3521] */
    (xdc_Char)0x72,  /* [3522] */
    (xdc_Char)0x2e,  /* [3523] */
    (xdc_Char)0x6d,  /* [3524] */
    (xdc_Char)0x61,  /* [3525] */
    (xdc_Char)0x78,  /* [3526] */
    (xdc_Char)0x52,  /* [3527] */
    (xdc_Char)0x75,  /* [3528] */
    (xdc_Char)0x6e,  /* [3529] */
    (xdc_Char)0x74,  /* [3530] */
    (xdc_Char)0x69,  /* [3531] */
    (xdc_Char)0x6d,  /* [3532] */
    (xdc_Char)0x65,  /* [3533] */
    (xdc_Char)0x45,  /* [3534] */
    (xdc_Char)0x6e,  /* [3535] */
    (xdc_Char)0x74,  /* [3536] */
    (xdc_Char)0x72,  /* [3537] */
    (xdc_Char)0x69,  /* [3538] */
    (xdc_Char)0x65,  /* [3539] */
    (xdc_Char)0x73,  /* [3540] */
    (xdc_Char)0x20,  /* [3541] */
    (xdc_Char)0x69,  /* [3542] */
    (xdc_Char)0x73,  /* [3543] */
    (xdc_Char)0x20,  /* [3544] */
    (xdc_Char)0x25,  /* [3545] */
    (xdc_Char)0x64,  /* [3546] */
    (xdc_Char)0x0,  /* [3547] */
    (xdc_Char)0x45,  /* [3548] */
    (xdc_Char)0x5f,  /* [3549] */
    (xdc_Char)0x65,  /* [3550] */
    (xdc_Char)0x6e,  /* [3551] */
    (xdc_Char)0x74,  /* [3552] */
    (xdc_Char)0x72,  /* [3553] */
    (xdc_Char)0x79,  /* [3554] */
    (xdc_Char)0x45,  /* [3555] */
    (xdc_Char)0x78,  /* [3556] */
    (xdc_Char)0x69,  /* [3557] */
    (xdc_Char)0x73,  /* [3558] */
    (xdc_Char)0x74,  /* [3559] */
    (xdc_Char)0x73,  /* [3560] */
    (xdc_Char)0x3a,  /* [3561] */
    (xdc_Char)0x20,  /* [3562] */
    (xdc_Char)0x25,  /* [3563] */
    (xdc_Char)0x73,  /* [3564] */
    (xdc_Char)0x20,  /* [3565] */
    (xdc_Char)0x6e,  /* [3566] */
    (xdc_Char)0x61,  /* [3567] */
    (xdc_Char)0x6d,  /* [3568] */
    (xdc_Char)0x65,  /* [3569] */
    (xdc_Char)0x20,  /* [3570] */
    (xdc_Char)0x61,  /* [3571] */
    (xdc_Char)0x6c,  /* [3572] */
    (xdc_Char)0x72,  /* [3573] */
    (xdc_Char)0x65,  /* [3574] */
    (xdc_Char)0x61,  /* [3575] */
    (xdc_Char)0x64,  /* [3576] */
    (xdc_Char)0x79,  /* [3577] */
    (xdc_Char)0x20,  /* [3578] */
    (xdc_Char)0x69,  /* [3579] */
    (xdc_Char)0x6e,  /* [3580] */
    (xdc_Char)0x20,  /* [3581] */
    (xdc_Char)0x74,  /* [3582] */
    (xdc_Char)0x61,  /* [3583] */
    (xdc_Char)0x62,  /* [3584] */
    (xdc_Char)0x6c,  /* [3585] */
    (xdc_Char)0x65,  /* [3586] */
    (xdc_Char)0x20,  /* [3587] */
    (xdc_Char)0x0,  /* [3588] */
    (xdc_Char)0x45,  /* [3589] */
    (xdc_Char)0x5f,  /* [3590] */
    (xdc_Char)0x70,  /* [3591] */
    (xdc_Char)0x61,  /* [3592] */
    (xdc_Char)0x72,  /* [3593] */
    (xdc_Char)0x61,  /* [3594] */
    (xdc_Char)0x6d,  /* [3595] */
    (xdc_Char)0x4d,  /* [3596] */
    (xdc_Char)0x69,  /* [3597] */
    (xdc_Char)0x73,  /* [3598] */
    (xdc_Char)0x6d,  /* [3599] */
    (xdc_Char)0x61,  /* [3600] */
    (xdc_Char)0x74,  /* [3601] */
    (xdc_Char)0x63,  /* [3602] */
    (xdc_Char)0x68,  /* [3603] */
    (xdc_Char)0x3a,  /* [3604] */
    (xdc_Char)0x20,  /* [3605] */
    (xdc_Char)0x70,  /* [3606] */
    (xdc_Char)0x61,  /* [3607] */
    (xdc_Char)0x72,  /* [3608] */
    (xdc_Char)0x61,  /* [3609] */
    (xdc_Char)0x6d,  /* [3610] */
    (xdc_Char)0x65,  /* [3611] */
    (xdc_Char)0x74,  /* [3612] */
    (xdc_Char)0x65,  /* [3613] */
    (xdc_Char)0x72,  /* [3614] */
    (xdc_Char)0x73,  /* [3615] */
    (xdc_Char)0x20,  /* [3616] */
    (xdc_Char)0x64,  /* [3617] */
    (xdc_Char)0x6f,  /* [3618] */
    (xdc_Char)0x20,  /* [3619] */
    (xdc_Char)0x6e,  /* [3620] */
    (xdc_Char)0x6f,  /* [3621] */
    (xdc_Char)0x74,  /* [3622] */
    (xdc_Char)0x20,  /* [3623] */
    (xdc_Char)0x6d,  /* [3624] */
    (xdc_Char)0x61,  /* [3625] */
    (xdc_Char)0x74,  /* [3626] */
    (xdc_Char)0x63,  /* [3627] */
    (xdc_Char)0x68,  /* [3628] */
    (xdc_Char)0x20,  /* [3629] */
    (xdc_Char)0x65,  /* [3630] */
    (xdc_Char)0x78,  /* [3631] */
    (xdc_Char)0x69,  /* [3632] */
    (xdc_Char)0x73,  /* [3633] */
    (xdc_Char)0x74,  /* [3634] */
    (xdc_Char)0x69,  /* [3635] */
    (xdc_Char)0x6e,  /* [3636] */
    (xdc_Char)0x67,  /* [3637] */
    (xdc_Char)0x20,  /* [3638] */
    (xdc_Char)0x4e,  /* [3639] */
    (xdc_Char)0x61,  /* [3640] */
    (xdc_Char)0x6d,  /* [3641] */
    (xdc_Char)0x65,  /* [3642] */
    (xdc_Char)0x53,  /* [3643] */
    (xdc_Char)0x65,  /* [3644] */
    (xdc_Char)0x72,  /* [3645] */
    (xdc_Char)0x76,  /* [3646] */
    (xdc_Char)0x65,  /* [3647] */
    (xdc_Char)0x72,  /* [3648] */
    (xdc_Char)0x20,  /* [3649] */
    (xdc_Char)0x25,  /* [3650] */
    (xdc_Char)0x73,  /* [3651] */
    (xdc_Char)0x20,  /* [3652] */
    (xdc_Char)0x0,  /* [3653] */
    (xdc_Char)0x3c,  /* [3654] */
    (xdc_Char)0x2d,  /* [3655] */
    (xdc_Char)0x2d,  /* [3656] */
    (xdc_Char)0x20,  /* [3657] */
    (xdc_Char)0x63,  /* [3658] */
    (xdc_Char)0x6f,  /* [3659] */
    (xdc_Char)0x6e,  /* [3660] */
    (xdc_Char)0x73,  /* [3661] */
    (xdc_Char)0x74,  /* [3662] */
    (xdc_Char)0x72,  /* [3663] */
    (xdc_Char)0x75,  /* [3664] */
    (xdc_Char)0x63,  /* [3665] */
    (xdc_Char)0x74,  /* [3666] */
    (xdc_Char)0x3a,  /* [3667] */
    (xdc_Char)0x20,  /* [3668] */
    (xdc_Char)0x25,  /* [3669] */
    (xdc_Char)0x70,  /* [3670] */
    (xdc_Char)0x28,  /* [3671] */
    (xdc_Char)0x27,  /* [3672] */
    (xdc_Char)0x25,  /* [3673] */
    (xdc_Char)0x73,  /* [3674] */
    (xdc_Char)0x27,  /* [3675] */
    (xdc_Char)0x29,  /* [3676] */
    (xdc_Char)0x0,  /* [3677] */
    (xdc_Char)0x3c,  /* [3678] */
    (xdc_Char)0x2d,  /* [3679] */
    (xdc_Char)0x2d,  /* [3680] */
    (xdc_Char)0x20,  /* [3681] */
    (xdc_Char)0x63,  /* [3682] */
    (xdc_Char)0x72,  /* [3683] */
    (xdc_Char)0x65,  /* [3684] */
    (xdc_Char)0x61,  /* [3685] */
    (xdc_Char)0x74,  /* [3686] */
    (xdc_Char)0x65,  /* [3687] */
    (xdc_Char)0x3a,  /* [3688] */
    (xdc_Char)0x20,  /* [3689] */
    (xdc_Char)0x25,  /* [3690] */
    (xdc_Char)0x70,  /* [3691] */
    (xdc_Char)0x28,  /* [3692] */
    (xdc_Char)0x27,  /* [3693] */
    (xdc_Char)0x25,  /* [3694] */
    (xdc_Char)0x73,  /* [3695] */
    (xdc_Char)0x27,  /* [3696] */
    (xdc_Char)0x29,  /* [3697] */
    (xdc_Char)0x0,  /* [3698] */
    (xdc_Char)0x2d,  /* [3699] */
    (xdc_Char)0x2d,  /* [3700] */
    (xdc_Char)0x3e,  /* [3701] */
    (xdc_Char)0x20,  /* [3702] */
    (xdc_Char)0x64,  /* [3703] */
    (xdc_Char)0x65,  /* [3704] */
    (xdc_Char)0x73,  /* [3705] */
    (xdc_Char)0x74,  /* [3706] */
    (xdc_Char)0x72,  /* [3707] */
    (xdc_Char)0x75,  /* [3708] */
    (xdc_Char)0x63,  /* [3709] */
    (xdc_Char)0x74,  /* [3710] */
    (xdc_Char)0x3a,  /* [3711] */
    (xdc_Char)0x20,  /* [3712] */
    (xdc_Char)0x28,  /* [3713] */
    (xdc_Char)0x25,  /* [3714] */
    (xdc_Char)0x70,  /* [3715] */
    (xdc_Char)0x29,  /* [3716] */
    (xdc_Char)0x0,  /* [3717] */
    (xdc_Char)0x2d,  /* [3718] */
    (xdc_Char)0x2d,  /* [3719] */
    (xdc_Char)0x3e,  /* [3720] */
    (xdc_Char)0x20,  /* [3721] */
    (xdc_Char)0x64,  /* [3722] */
    (xdc_Char)0x65,  /* [3723] */
    (xdc_Char)0x6c,  /* [3724] */
    (xdc_Char)0x65,  /* [3725] */
    (xdc_Char)0x74,  /* [3726] */
    (xdc_Char)0x65,  /* [3727] */
    (xdc_Char)0x3a,  /* [3728] */
    (xdc_Char)0x20,  /* [3729] */
    (xdc_Char)0x28,  /* [3730] */
    (xdc_Char)0x25,  /* [3731] */
    (xdc_Char)0x70,  /* [3732] */
    (xdc_Char)0x29,  /* [3733] */
    (xdc_Char)0x0,  /* [3734] */
    (xdc_Char)0x45,  /* [3735] */
    (xdc_Char)0x52,  /* [3736] */
    (xdc_Char)0x52,  /* [3737] */
    (xdc_Char)0x4f,  /* [3738] */
    (xdc_Char)0x52,  /* [3739] */
    (xdc_Char)0x3a,  /* [3740] */
    (xdc_Char)0x20,  /* [3741] */
    (xdc_Char)0x25,  /* [3742] */
    (xdc_Char)0x24,  /* [3743] */
    (xdc_Char)0x46,  /* [3744] */
    (xdc_Char)0x25,  /* [3745] */
    (xdc_Char)0x24,  /* [3746] */
    (xdc_Char)0x53,  /* [3747] */
    (xdc_Char)0x0,  /* [3748] */
    (xdc_Char)0x57,  /* [3749] */
    (xdc_Char)0x41,  /* [3750] */
    (xdc_Char)0x52,  /* [3751] */
    (xdc_Char)0x4e,  /* [3752] */
    (xdc_Char)0x49,  /* [3753] */
    (xdc_Char)0x4e,  /* [3754] */
    (xdc_Char)0x47,  /* [3755] */
    (xdc_Char)0x3a,  /* [3756] */
    (xdc_Char)0x20,  /* [3757] */
    (xdc_Char)0x25,  /* [3758] */
    (xdc_Char)0x24,  /* [3759] */
    (xdc_Char)0x46,  /* [3760] */
    (xdc_Char)0x25,  /* [3761] */
    (xdc_Char)0x24,  /* [3762] */
    (xdc_Char)0x53,  /* [3763] */
    (xdc_Char)0x0,  /* [3764] */
    (xdc_Char)0x25,  /* [3765] */
    (xdc_Char)0x24,  /* [3766] */
    (xdc_Char)0x46,  /* [3767] */
    (xdc_Char)0x25,  /* [3768] */
    (xdc_Char)0x24,  /* [3769] */
    (xdc_Char)0x53,  /* [3770] */
    (xdc_Char)0x0,  /* [3771] */
    (xdc_Char)0x53,  /* [3772] */
    (xdc_Char)0x74,  /* [3773] */
    (xdc_Char)0x61,  /* [3774] */
    (xdc_Char)0x72,  /* [3775] */
    (xdc_Char)0x74,  /* [3776] */
    (xdc_Char)0x3a,  /* [3777] */
    (xdc_Char)0x20,  /* [3778] */
    (xdc_Char)0x25,  /* [3779] */
    (xdc_Char)0x24,  /* [3780] */
    (xdc_Char)0x53,  /* [3781] */
    (xdc_Char)0x0,  /* [3782] */
    (xdc_Char)0x53,  /* [3783] */
    (xdc_Char)0x74,  /* [3784] */
    (xdc_Char)0x6f,  /* [3785] */
    (xdc_Char)0x70,  /* [3786] */
    (xdc_Char)0x3a,  /* [3787] */
    (xdc_Char)0x20,  /* [3788] */
    (xdc_Char)0x25,  /* [3789] */
    (xdc_Char)0x24,  /* [3790] */
    (xdc_Char)0x53,  /* [3791] */
    (xdc_Char)0x0,  /* [3792] */
    (xdc_Char)0x53,  /* [3793] */
    (xdc_Char)0x74,  /* [3794] */
    (xdc_Char)0x61,  /* [3795] */
    (xdc_Char)0x72,  /* [3796] */
    (xdc_Char)0x74,  /* [3797] */
    (xdc_Char)0x49,  /* [3798] */
    (xdc_Char)0x6e,  /* [3799] */
    (xdc_Char)0x73,  /* [3800] */
    (xdc_Char)0x74,  /* [3801] */
    (xdc_Char)0x61,  /* [3802] */
    (xdc_Char)0x6e,  /* [3803] */
    (xdc_Char)0x63,  /* [3804] */
    (xdc_Char)0x65,  /* [3805] */
    (xdc_Char)0x3a,  /* [3806] */
    (xdc_Char)0x20,  /* [3807] */
    (xdc_Char)0x25,  /* [3808] */
    (xdc_Char)0x24,  /* [3809] */
    (xdc_Char)0x53,  /* [3810] */
    (xdc_Char)0x0,  /* [3811] */
    (xdc_Char)0x53,  /* [3812] */
    (xdc_Char)0x74,  /* [3813] */
    (xdc_Char)0x6f,  /* [3814] */
    (xdc_Char)0x70,  /* [3815] */
    (xdc_Char)0x49,  /* [3816] */
    (xdc_Char)0x6e,  /* [3817] */
    (xdc_Char)0x73,  /* [3818] */
    (xdc_Char)0x74,  /* [3819] */
    (xdc_Char)0x61,  /* [3820] */
    (xdc_Char)0x6e,  /* [3821] */
    (xdc_Char)0x63,  /* [3822] */
    (xdc_Char)0x65,  /* [3823] */
    (xdc_Char)0x3a,  /* [3824] */
    (xdc_Char)0x20,  /* [3825] */
    (xdc_Char)0x25,  /* [3826] */
    (xdc_Char)0x24,  /* [3827] */
    (xdc_Char)0x53,  /* [3828] */
    (xdc_Char)0x0,  /* [3829] */
    (xdc_Char)0x78,  /* [3830] */
    (xdc_Char)0x64,  /* [3831] */
    (xdc_Char)0x63,  /* [3832] */
    (xdc_Char)0x2e,  /* [3833] */
    (xdc_Char)0x0,  /* [3834] */
    (xdc_Char)0x72,  /* [3835] */
    (xdc_Char)0x75,  /* [3836] */
    (xdc_Char)0x6e,  /* [3837] */
    (xdc_Char)0x74,  /* [3838] */
    (xdc_Char)0x69,  /* [3839] */
    (xdc_Char)0x6d,  /* [3840] */
    (xdc_Char)0x65,  /* [3841] */
    (xdc_Char)0x2e,  /* [3842] */
    (xdc_Char)0x0,  /* [3843] */
    (xdc_Char)0x41,  /* [3844] */
    (xdc_Char)0x73,  /* [3845] */
    (xdc_Char)0x73,  /* [3846] */
    (xdc_Char)0x65,  /* [3847] */
    (xdc_Char)0x72,  /* [3848] */
    (xdc_Char)0x74,  /* [3849] */
    (xdc_Char)0x0,  /* [3850] */
    (xdc_Char)0x43,  /* [3851] */
    (xdc_Char)0x6f,  /* [3852] */
    (xdc_Char)0x72,  /* [3853] */
    (xdc_Char)0x65,  /* [3854] */
    (xdc_Char)0x0,  /* [3855] */
    (xdc_Char)0x44,  /* [3856] */
    (xdc_Char)0x65,  /* [3857] */
    (xdc_Char)0x66,  /* [3858] */
    (xdc_Char)0x61,  /* [3859] */
    (xdc_Char)0x75,  /* [3860] */
    (xdc_Char)0x6c,  /* [3861] */
    (xdc_Char)0x74,  /* [3862] */
    (xdc_Char)0x73,  /* [3863] */
    (xdc_Char)0x0,  /* [3864] */
    (xdc_Char)0x44,  /* [3865] */
    (xdc_Char)0x69,  /* [3866] */
    (xdc_Char)0x61,  /* [3867] */
    (xdc_Char)0x67,  /* [3868] */
    (xdc_Char)0x73,  /* [3869] */
    (xdc_Char)0x0,  /* [3870] */
    (xdc_Char)0x45,  /* [3871] */
    (xdc_Char)0x72,  /* [3872] */
    (xdc_Char)0x72,  /* [3873] */
    (xdc_Char)0x6f,  /* [3874] */
    (xdc_Char)0x72,  /* [3875] */
    (xdc_Char)0x0,  /* [3876] */
    (xdc_Char)0x47,  /* [3877] */
    (xdc_Char)0x61,  /* [3878] */
    (xdc_Char)0x74,  /* [3879] */
    (xdc_Char)0x65,  /* [3880] */
    (xdc_Char)0x0,  /* [3881] */
    (xdc_Char)0x47,  /* [3882] */
    (xdc_Char)0x61,  /* [3883] */
    (xdc_Char)0x74,  /* [3884] */
    (xdc_Char)0x65,  /* [3885] */
    (xdc_Char)0x4e,  /* [3886] */
    (xdc_Char)0x75,  /* [3887] */
    (xdc_Char)0x6c,  /* [3888] */
    (xdc_Char)0x6c,  /* [3889] */
    (xdc_Char)0x0,  /* [3890] */
    (xdc_Char)0x4c,  /* [3891] */
    (xdc_Char)0x6f,  /* [3892] */
    (xdc_Char)0x67,  /* [3893] */
    (xdc_Char)0x0,  /* [3894] */
    (xdc_Char)0x4d,  /* [3895] */
    (xdc_Char)0x61,  /* [3896] */
    (xdc_Char)0x69,  /* [3897] */
    (xdc_Char)0x6e,  /* [3898] */
    (xdc_Char)0x0,  /* [3899] */
    (xdc_Char)0x4d,  /* [3900] */
    (xdc_Char)0x65,  /* [3901] */
    (xdc_Char)0x6d,  /* [3902] */
    (xdc_Char)0x6f,  /* [3903] */
    (xdc_Char)0x72,  /* [3904] */
    (xdc_Char)0x79,  /* [3905] */
    (xdc_Char)0x0,  /* [3906] */
    (xdc_Char)0x48,  /* [3907] */
    (xdc_Char)0x65,  /* [3908] */
    (xdc_Char)0x61,  /* [3909] */
    (xdc_Char)0x70,  /* [3910] */
    (xdc_Char)0x53,  /* [3911] */
    (xdc_Char)0x74,  /* [3912] */
    (xdc_Char)0x64,  /* [3913] */
    (xdc_Char)0x0,  /* [3914] */
    (xdc_Char)0x52,  /* [3915] */
    (xdc_Char)0x65,  /* [3916] */
    (xdc_Char)0x67,  /* [3917] */
    (xdc_Char)0x69,  /* [3918] */
    (xdc_Char)0x73,  /* [3919] */
    (xdc_Char)0x74,  /* [3920] */
    (xdc_Char)0x72,  /* [3921] */
    (xdc_Char)0x79,  /* [3922] */
    (xdc_Char)0x0,  /* [3923] */
    (xdc_Char)0x53,  /* [3924] */
    (xdc_Char)0x74,  /* [3925] */
    (xdc_Char)0x61,  /* [3926] */
    (xdc_Char)0x72,  /* [3927] */
    (xdc_Char)0x74,  /* [3928] */
    (xdc_Char)0x75,  /* [3929] */
    (xdc_Char)0x70,  /* [3930] */
    (xdc_Char)0x0,  /* [3931] */
    (xdc_Char)0x53,  /* [3932] */
    (xdc_Char)0x79,  /* [3933] */
    (xdc_Char)0x73,  /* [3934] */
    (xdc_Char)0x74,  /* [3935] */
    (xdc_Char)0x65,  /* [3936] */
    (xdc_Char)0x6d,  /* [3937] */
    (xdc_Char)0x0,  /* [3938] */
    (xdc_Char)0x53,  /* [3939] */
    (xdc_Char)0x79,  /* [3940] */
    (xdc_Char)0x73,  /* [3941] */
    (xdc_Char)0x4d,  /* [3942] */
    (xdc_Char)0x69,  /* [3943] */
    (xdc_Char)0x6e,  /* [3944] */
    (xdc_Char)0x0,  /* [3945] */
    (xdc_Char)0x54,  /* [3946] */
    (xdc_Char)0x65,  /* [3947] */
    (xdc_Char)0x78,  /* [3948] */
    (xdc_Char)0x74,  /* [3949] */
    (xdc_Char)0x0,  /* [3950] */
    (xdc_Char)0x74,  /* [3951] */
    (xdc_Char)0x69,  /* [3952] */
    (xdc_Char)0x2e,  /* [3953] */
    (xdc_Char)0x0,  /* [3954] */
    (xdc_Char)0x73,  /* [3955] */
    (xdc_Char)0x64,  /* [3956] */
    (xdc_Char)0x6f,  /* [3957] */
    (xdc_Char)0x2e,  /* [3958] */
    (xdc_Char)0x0,  /* [3959] */
    (xdc_Char)0x75,  /* [3960] */
    (xdc_Char)0x74,  /* [3961] */
    (xdc_Char)0x69,  /* [3962] */
    (xdc_Char)0x6c,  /* [3963] */
    (xdc_Char)0x73,  /* [3964] */
    (xdc_Char)0x2e,  /* [3965] */
    (xdc_Char)0x0,  /* [3966] */
    (xdc_Char)0x4e,  /* [3967] */
    (xdc_Char)0x61,  /* [3968] */
    (xdc_Char)0x6d,  /* [3969] */
    (xdc_Char)0x65,  /* [3970] */
    (xdc_Char)0x53,  /* [3971] */
    (xdc_Char)0x65,  /* [3972] */
    (xdc_Char)0x72,  /* [3973] */
    (xdc_Char)0x76,  /* [3974] */
    (xdc_Char)0x65,  /* [3975] */
    (xdc_Char)0x72,  /* [3976] */
    (xdc_Char)0x52,  /* [3977] */
    (xdc_Char)0x65,  /* [3978] */
    (xdc_Char)0x6d,  /* [3979] */
    (xdc_Char)0x6f,  /* [3980] */
    (xdc_Char)0x74,  /* [3981] */
    (xdc_Char)0x65,  /* [3982] */
    (xdc_Char)0x4e,  /* [3983] */
    (xdc_Char)0x75,  /* [3984] */
    (xdc_Char)0x6c,  /* [3985] */
    (xdc_Char)0x6c,  /* [3986] */
    (xdc_Char)0x0,  /* [3987] */
};

/* --> xdc_runtime_Text_nodeTab__A */
#pragma DATA_SECTION(xdc_runtime_Text_nodeTab__A, ".const:xdc_runtime_Text_nodeTab__A");
const __T1_xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__A[21] = {
    {
        (xdc_Bits16)0x0,  /* left */
        (xdc_Bits16)0x0,  /* right */
    },  /* [0] */
    {
        (xdc_Bits16)0xef6,  /* left */
        (xdc_Bits16)0xefb,  /* right */
    },  /* [1] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf04,  /* right */
    },  /* [2] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf0b,  /* right */
    },  /* [3] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf10,  /* right */
    },  /* [4] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf19,  /* right */
    },  /* [5] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf1f,  /* right */
    },  /* [6] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf25,  /* right */
    },  /* [7] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf2a,  /* right */
    },  /* [8] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf33,  /* right */
    },  /* [9] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf37,  /* right */
    },  /* [10] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf3c,  /* right */
    },  /* [11] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf43,  /* right */
    },  /* [12] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf4b,  /* right */
    },  /* [13] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf54,  /* right */
    },  /* [14] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf5c,  /* right */
    },  /* [15] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf63,  /* right */
    },  /* [16] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0xf6a,  /* right */
    },  /* [17] */
    {
        (xdc_Bits16)0xf6f,  /* left */
        (xdc_Bits16)0xf73,  /* right */
    },  /* [18] */
    {
        (xdc_Bits16)0x8012,  /* left */
        (xdc_Bits16)0xf78,  /* right */
    },  /* [19] */
    {
        (xdc_Bits16)0x8013,  /* left */
        (xdc_Bits16)0xf7f,  /* right */
    },  /* [20] */
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
__FAR__ const CT__xdc_runtime_Text_charCnt xdc_runtime_Text_charCnt__C = (xdc_Int16)0xf94;

/* nodeCnt__C */
#pragma DATA_SECTION(xdc_runtime_Text_nodeCnt__C, ".const:xdc_runtime_Text_nodeCnt__C");
__FAR__ const CT__xdc_runtime_Text_nodeCnt xdc_runtime_Text_nodeCnt__C = (xdc_Int16)0x15;

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
    lab->modId = 32788;
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

