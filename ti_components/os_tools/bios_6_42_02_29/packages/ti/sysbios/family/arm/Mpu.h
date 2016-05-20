/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-A71
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef ti_sysbios_family_arm_Mpu__include
#define ti_sysbios_family_arm_Mpu__include

#ifndef __nested__
#define __nested__
#define ti_sysbios_family_arm_Mpu__top__
#endif

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif

#define ti_sysbios_family_arm_Mpu___VERS 160


/*
 * ======== INCLUDES ========
 */

#include <xdc/std.h>

#include <xdc/runtime/xdc.h>
#include <xdc/runtime/Types.h>
#include <ti/sysbios/family/arm/package/package.defs.h>

#include <xdc/runtime/IModule.h>
#include <xdc/runtime/Assert.h>


/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* RegionSize */
enum ti_sysbios_family_arm_Mpu_RegionSize {
    ti_sysbios_family_arm_Mpu_RegionSize_32 = 0x8,
    ti_sysbios_family_arm_Mpu_RegionSize_64 = 0xA,
    ti_sysbios_family_arm_Mpu_RegionSize_128 = 0xC,
    ti_sysbios_family_arm_Mpu_RegionSize_256 = 0xE,
    ti_sysbios_family_arm_Mpu_RegionSize_512 = 0x10,
    ti_sysbios_family_arm_Mpu_RegionSize_1K = 0x12,
    ti_sysbios_family_arm_Mpu_RegionSize_2K = 0x14,
    ti_sysbios_family_arm_Mpu_RegionSize_4K = 0x16,
    ti_sysbios_family_arm_Mpu_RegionSize_8K = 0x18,
    ti_sysbios_family_arm_Mpu_RegionSize_16K = 0x1A,
    ti_sysbios_family_arm_Mpu_RegionSize_32K = 0x1C,
    ti_sysbios_family_arm_Mpu_RegionSize_64K = 0x1E,
    ti_sysbios_family_arm_Mpu_RegionSize_128K = 0x20,
    ti_sysbios_family_arm_Mpu_RegionSize_256K = 0x22,
    ti_sysbios_family_arm_Mpu_RegionSize_512K = 0x24,
    ti_sysbios_family_arm_Mpu_RegionSize_1M = 0x26,
    ti_sysbios_family_arm_Mpu_RegionSize_2M = 0x28,
    ti_sysbios_family_arm_Mpu_RegionSize_4M = 0x2A,
    ti_sysbios_family_arm_Mpu_RegionSize_8M = 0x2C,
    ti_sysbios_family_arm_Mpu_RegionSize_16M = 0x2E,
    ti_sysbios_family_arm_Mpu_RegionSize_32M = 0x30,
    ti_sysbios_family_arm_Mpu_RegionSize_64M = 0x32,
    ti_sysbios_family_arm_Mpu_RegionSize_128M = 0x34,
    ti_sysbios_family_arm_Mpu_RegionSize_256M = 0x36,
    ti_sysbios_family_arm_Mpu_RegionSize_512M = 0x38,
    ti_sysbios_family_arm_Mpu_RegionSize_1G = 0x3A,
    ti_sysbios_family_arm_Mpu_RegionSize_2G = 0x3C,
    ti_sysbios_family_arm_Mpu_RegionSize_4G = 0x3E
};
typedef enum ti_sysbios_family_arm_Mpu_RegionSize ti_sysbios_family_arm_Mpu_RegionSize;

/* RegionAttrs */
struct ti_sysbios_family_arm_Mpu_RegionAttrs {
    xdc_Bool enable;
    xdc_Bool bufferable;
    xdc_Bool cacheable;
    xdc_Bool shareable;
    xdc_Bool noExecute;
    xdc_UInt8 accPerm;
    xdc_UInt8 tex;
    xdc_UInt8 subregionDisableMask;
};


/*
 * ======== INTERNAL DEFINITIONS ========
 */

/* RegionEntry */
struct ti_sysbios_family_arm_Mpu_RegionEntry {
    xdc_UInt32 baseAddress;
    xdc_UInt32 sizeAndEnable;
    xdc_UInt32 regionAttrs;
};

/* Module_State */
typedef ti_sysbios_family_arm_Mpu_RegionEntry __T1_ti_sysbios_family_arm_Mpu_Module_State__regionEntry;
typedef ti_sysbios_family_arm_Mpu_RegionEntry *__ARRAY1_ti_sysbios_family_arm_Mpu_Module_State__regionEntry;
typedef __ARRAY1_ti_sysbios_family_arm_Mpu_Module_State__regionEntry __TA_ti_sysbios_family_arm_Mpu_Module_State__regionEntry;


/*
 * ======== MODULE-WIDE CONFIGS ========
 */

/* Module__diagsEnabled */
typedef xdc_Bits32 CT__ti_sysbios_family_arm_Mpu_Module__diagsEnabled;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__diagsEnabled ti_sysbios_family_arm_Mpu_Module__diagsEnabled__C;

/* Module__diagsIncluded */
typedef xdc_Bits32 CT__ti_sysbios_family_arm_Mpu_Module__diagsIncluded;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__diagsIncluded ti_sysbios_family_arm_Mpu_Module__diagsIncluded__C;

/* Module__diagsMask */
typedef xdc_Bits16 *CT__ti_sysbios_family_arm_Mpu_Module__diagsMask;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__diagsMask ti_sysbios_family_arm_Mpu_Module__diagsMask__C;

/* Module__gateObj */
typedef xdc_Ptr CT__ti_sysbios_family_arm_Mpu_Module__gateObj;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__gateObj ti_sysbios_family_arm_Mpu_Module__gateObj__C;

/* Module__gatePrms */
typedef xdc_Ptr CT__ti_sysbios_family_arm_Mpu_Module__gatePrms;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__gatePrms ti_sysbios_family_arm_Mpu_Module__gatePrms__C;

/* Module__id */
typedef xdc_runtime_Types_ModuleId CT__ti_sysbios_family_arm_Mpu_Module__id;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__id ti_sysbios_family_arm_Mpu_Module__id__C;

/* Module__loggerDefined */
typedef xdc_Bool CT__ti_sysbios_family_arm_Mpu_Module__loggerDefined;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__loggerDefined ti_sysbios_family_arm_Mpu_Module__loggerDefined__C;

/* Module__loggerObj */
typedef xdc_Ptr CT__ti_sysbios_family_arm_Mpu_Module__loggerObj;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__loggerObj ti_sysbios_family_arm_Mpu_Module__loggerObj__C;

/* Module__loggerFxn0 */
typedef xdc_runtime_Types_LoggerFxn0 CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn0;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn0 ti_sysbios_family_arm_Mpu_Module__loggerFxn0__C;

/* Module__loggerFxn1 */
typedef xdc_runtime_Types_LoggerFxn1 CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn1;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn1 ti_sysbios_family_arm_Mpu_Module__loggerFxn1__C;

/* Module__loggerFxn2 */
typedef xdc_runtime_Types_LoggerFxn2 CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn2;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn2 ti_sysbios_family_arm_Mpu_Module__loggerFxn2__C;

/* Module__loggerFxn4 */
typedef xdc_runtime_Types_LoggerFxn4 CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn4;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn4 ti_sysbios_family_arm_Mpu_Module__loggerFxn4__C;

/* Module__loggerFxn8 */
typedef xdc_runtime_Types_LoggerFxn8 CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn8;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__loggerFxn8 ti_sysbios_family_arm_Mpu_Module__loggerFxn8__C;

/* Module__startupDoneFxn */
typedef xdc_Bool (*CT__ti_sysbios_family_arm_Mpu_Module__startupDoneFxn)(void);
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Module__startupDoneFxn ti_sysbios_family_arm_Mpu_Module__startupDoneFxn__C;

/* Object__count */
typedef xdc_Int CT__ti_sysbios_family_arm_Mpu_Object__count;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Object__count ti_sysbios_family_arm_Mpu_Object__count__C;

/* Object__heap */
typedef xdc_runtime_IHeap_Handle CT__ti_sysbios_family_arm_Mpu_Object__heap;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Object__heap ti_sysbios_family_arm_Mpu_Object__heap__C;

/* Object__sizeof */
typedef xdc_SizeT CT__ti_sysbios_family_arm_Mpu_Object__sizeof;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Object__sizeof ti_sysbios_family_arm_Mpu_Object__sizeof__C;

/* Object__table */
typedef xdc_Ptr CT__ti_sysbios_family_arm_Mpu_Object__table;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_Object__table ti_sysbios_family_arm_Mpu_Object__table__C;

/* A_nullPointer */
#define ti_sysbios_family_arm_Mpu_A_nullPointer (ti_sysbios_family_arm_Mpu_A_nullPointer__C)
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_Mpu_A_nullPointer;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_A_nullPointer ti_sysbios_family_arm_Mpu_A_nullPointer__C;

/* A_invalidRegionId */
#define ti_sysbios_family_arm_Mpu_A_invalidRegionId (ti_sysbios_family_arm_Mpu_A_invalidRegionId__C)
typedef xdc_runtime_Assert_Id CT__ti_sysbios_family_arm_Mpu_A_invalidRegionId;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_A_invalidRegionId ti_sysbios_family_arm_Mpu_A_invalidRegionId__C;

/* defaultAttrs */
#define ti_sysbios_family_arm_Mpu_defaultAttrs (ti_sysbios_family_arm_Mpu_defaultAttrs__C)
typedef ti_sysbios_family_arm_Mpu_RegionAttrs CT__ti_sysbios_family_arm_Mpu_defaultAttrs;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_defaultAttrs ti_sysbios_family_arm_Mpu_defaultAttrs__C;

/* enableMPU */
#ifdef ti_sysbios_family_arm_Mpu_enableMPU__D
#define ti_sysbios_family_arm_Mpu_enableMPU (ti_sysbios_family_arm_Mpu_enableMPU__D)
#else
#define ti_sysbios_family_arm_Mpu_enableMPU (ti_sysbios_family_arm_Mpu_enableMPU__C)
typedef xdc_Bool CT__ti_sysbios_family_arm_Mpu_enableMPU;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_enableMPU ti_sysbios_family_arm_Mpu_enableMPU__C;
#endif

/* enableBackgroundRegion */
#ifdef ti_sysbios_family_arm_Mpu_enableBackgroundRegion__D
#define ti_sysbios_family_arm_Mpu_enableBackgroundRegion (ti_sysbios_family_arm_Mpu_enableBackgroundRegion__D)
#else
#define ti_sysbios_family_arm_Mpu_enableBackgroundRegion (ti_sysbios_family_arm_Mpu_enableBackgroundRegion__C)
typedef xdc_Bool CT__ti_sysbios_family_arm_Mpu_enableBackgroundRegion;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_enableBackgroundRegion ti_sysbios_family_arm_Mpu_enableBackgroundRegion__C;
#endif

/* numRegions */
#ifdef ti_sysbios_family_arm_Mpu_numRegions__D
#define ti_sysbios_family_arm_Mpu_numRegions (ti_sysbios_family_arm_Mpu_numRegions__D)
#else
#define ti_sysbios_family_arm_Mpu_numRegions (ti_sysbios_family_arm_Mpu_numRegions__C)
typedef xdc_UInt8 CT__ti_sysbios_family_arm_Mpu_numRegions;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_numRegions ti_sysbios_family_arm_Mpu_numRegions__C;
#endif

/* isMemoryMapped */
#ifdef ti_sysbios_family_arm_Mpu_isMemoryMapped__D
#define ti_sysbios_family_arm_Mpu_isMemoryMapped (ti_sysbios_family_arm_Mpu_isMemoryMapped__D)
#else
#define ti_sysbios_family_arm_Mpu_isMemoryMapped (ti_sysbios_family_arm_Mpu_isMemoryMapped__C)
typedef xdc_Bool CT__ti_sysbios_family_arm_Mpu_isMemoryMapped;
__extern __FAR__ const CT__ti_sysbios_family_arm_Mpu_isMemoryMapped ti_sysbios_family_arm_Mpu_isMemoryMapped__C;
#endif


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/* Module_startup */
#define ti_sysbios_family_arm_Mpu_Module_startup( state ) (-1)

/* Module__startupDone__S */
xdc__CODESECT(ti_sysbios_family_arm_Mpu_Module__startupDone__S, "ti_sysbios_family_arm_Mpu_Module__startupDone__S")
__extern xdc_Bool ti_sysbios_family_arm_Mpu_Module__startupDone__S( void );

/* disable__E */
#define ti_sysbios_family_arm_Mpu_disable ti_sysbios_family_arm_Mpu_disable__E
xdc__CODESECT(ti_sysbios_family_arm_Mpu_disable__E, "ti_sysbios_family_arm_Mpu_disable")
__extern xdc_Void ti_sysbios_family_arm_Mpu_disable__E( void );

/* disableBR__E */
#define ti_sysbios_family_arm_Mpu_disableBR ti_sysbios_family_arm_Mpu_disableBR__E
xdc__CODESECT(ti_sysbios_family_arm_Mpu_disableBR__E, "ti_sysbios_family_arm_Mpu_disableBR")
__extern xdc_Void ti_sysbios_family_arm_Mpu_disableBR__E( void );

/* enable__E */
#define ti_sysbios_family_arm_Mpu_enable ti_sysbios_family_arm_Mpu_enable__E
xdc__CODESECT(ti_sysbios_family_arm_Mpu_enable__E, "ti_sysbios_family_arm_Mpu_enable")
__extern xdc_Void ti_sysbios_family_arm_Mpu_enable__E( void );

/* enableBR__E */
#define ti_sysbios_family_arm_Mpu_enableBR ti_sysbios_family_arm_Mpu_enableBR__E
xdc__CODESECT(ti_sysbios_family_arm_Mpu_enableBR__E, "ti_sysbios_family_arm_Mpu_enableBR")
__extern xdc_Void ti_sysbios_family_arm_Mpu_enableBR__E( void );

/* initRegionAttrs__E */
#define ti_sysbios_family_arm_Mpu_initRegionAttrs ti_sysbios_family_arm_Mpu_initRegionAttrs__E
xdc__CODESECT(ti_sysbios_family_arm_Mpu_initRegionAttrs__E, "ti_sysbios_family_arm_Mpu_initRegionAttrs")
__extern xdc_Void ti_sysbios_family_arm_Mpu_initRegionAttrs__E( ti_sysbios_family_arm_Mpu_RegionAttrs *regionAttrs );

/* isEnabled__E */
#define ti_sysbios_family_arm_Mpu_isEnabled ti_sysbios_family_arm_Mpu_isEnabled__E
xdc__CODESECT(ti_sysbios_family_arm_Mpu_isEnabled__E, "ti_sysbios_family_arm_Mpu_isEnabled")
__extern xdc_Bool ti_sysbios_family_arm_Mpu_isEnabled__E( void );

/* setRegion__E */
#define ti_sysbios_family_arm_Mpu_setRegion ti_sysbios_family_arm_Mpu_setRegion__E
xdc__CODESECT(ti_sysbios_family_arm_Mpu_setRegion__E, "ti_sysbios_family_arm_Mpu_setRegion")
__extern xdc_Void ti_sysbios_family_arm_Mpu_setRegion__E( xdc_UInt8 regionId, xdc_Ptr regionBaseAddr, ti_sysbios_family_arm_Mpu_RegionSize regionSize, ti_sysbios_family_arm_Mpu_RegionAttrs *attrs );

/* startup__E */
#define ti_sysbios_family_arm_Mpu_startup ti_sysbios_family_arm_Mpu_startup__E
xdc__CODESECT(ti_sysbios_family_arm_Mpu_startup__E, "ti_sysbios_family_arm_Mpu_startup")
__extern xdc_Void ti_sysbios_family_arm_Mpu_startup__E( void );

/* disableAsm__I */
#define ti_sysbios_family_arm_Mpu_disableAsm ti_sysbios_family_arm_Mpu_disableAsm__I
xdc__CODESECT(ti_sysbios_family_arm_Mpu_disableAsm__I, "ti_sysbios_family_arm_Mpu_disableAsm")
__extern xdc_Void ti_sysbios_family_arm_Mpu_disableAsm__I( void );

/* enableAsm__I */
#define ti_sysbios_family_arm_Mpu_enableAsm ti_sysbios_family_arm_Mpu_enableAsm__I
xdc__CODESECT(ti_sysbios_family_arm_Mpu_enableAsm__I, "ti_sysbios_family_arm_Mpu_enableAsm")
__extern xdc_Void ti_sysbios_family_arm_Mpu_enableAsm__I( void );

/* initRegions__I */
#define ti_sysbios_family_arm_Mpu_initRegions ti_sysbios_family_arm_Mpu_initRegions__I
xdc__CODESECT(ti_sysbios_family_arm_Mpu_initRegions__I, "ti_sysbios_family_arm_Mpu_initRegions")
__extern xdc_Void ti_sysbios_family_arm_Mpu_initRegions__I( void );

/* setRegionAsm__I */
#define ti_sysbios_family_arm_Mpu_setRegionAsm ti_sysbios_family_arm_Mpu_setRegionAsm__I
xdc__CODESECT(ti_sysbios_family_arm_Mpu_setRegionAsm__I, "ti_sysbios_family_arm_Mpu_setRegionAsm")
__extern xdc_Void ti_sysbios_family_arm_Mpu_setRegionAsm__I( xdc_UInt8 regionId, xdc_UInt32 regionBaseAddr, xdc_UInt32 regionSize, xdc_UInt32 regionAttrs );


/*
 * ======== SYSTEM FUNCTIONS ========
 */

/* Module_startupDone */
#define ti_sysbios_family_arm_Mpu_Module_startupDone() ti_sysbios_family_arm_Mpu_Module__startupDone__S()

/* Object_heap */
#define ti_sysbios_family_arm_Mpu_Object_heap() ti_sysbios_family_arm_Mpu_Object__heap__C

/* Module_heap */
#define ti_sysbios_family_arm_Mpu_Module_heap() ti_sysbios_family_arm_Mpu_Object__heap__C

/* Module_id */
static inline CT__ti_sysbios_family_arm_Mpu_Module__id ti_sysbios_family_arm_Mpu_Module_id( void ) 
{
    return ti_sysbios_family_arm_Mpu_Module__id__C;
}

/* Module_hasMask */
static inline xdc_Bool ti_sysbios_family_arm_Mpu_Module_hasMask( void ) 
{
    return ti_sysbios_family_arm_Mpu_Module__diagsMask__C != NULL;
}

/* Module_getMask */
static inline xdc_Bits16 ti_sysbios_family_arm_Mpu_Module_getMask( void ) 
{
    return ti_sysbios_family_arm_Mpu_Module__diagsMask__C != NULL ? *ti_sysbios_family_arm_Mpu_Module__diagsMask__C : 0;
}

/* Module_setMask */
static inline xdc_Void ti_sysbios_family_arm_Mpu_Module_setMask( xdc_Bits16 mask ) 
{
    if (ti_sysbios_family_arm_Mpu_Module__diagsMask__C != NULL) *ti_sysbios_family_arm_Mpu_Module__diagsMask__C = mask;
}


/*
 * ======== EPILOGUE ========
 */

#ifdef ti_sysbios_family_arm_Mpu__top__
#undef __nested__
#endif

#endif /* ti_sysbios_family_arm_Mpu__include */


/*
 * ======== STATE STRUCTURES ========
 */

#if defined(__config__) || (!defined(__nested__) && defined(ti_sysbios_family_arm_Mpu__internalaccess))

#ifndef ti_sysbios_family_arm_Mpu__include_state
#define ti_sysbios_family_arm_Mpu__include_state

/* Module_State */
struct ti_sysbios_family_arm_Mpu_Module_State {
    __TA_ti_sysbios_family_arm_Mpu_Module_State__regionEntry regionEntry;
};

/* Module__state__V */
extern struct ti_sysbios_family_arm_Mpu_Module_State__ ti_sysbios_family_arm_Mpu_Module__state__V;

#endif /* ti_sysbios_family_arm_Mpu__include_state */

#endif


/*
 * ======== PREFIX ALIASES ========
 */

#if !defined(__nested__) && !defined(ti_sysbios_family_arm_Mpu__nolocalnames)

#ifndef ti_sysbios_family_arm_Mpu__localnames__done
#define ti_sysbios_family_arm_Mpu__localnames__done

/* module prefix */
#define Mpu_RegionSize ti_sysbios_family_arm_Mpu_RegionSize
#define Mpu_RegionAttrs ti_sysbios_family_arm_Mpu_RegionAttrs
#define Mpu_RegionEntry ti_sysbios_family_arm_Mpu_RegionEntry
#define Mpu_Module_State ti_sysbios_family_arm_Mpu_Module_State
#define Mpu_RegionSize_32 ti_sysbios_family_arm_Mpu_RegionSize_32
#define Mpu_RegionSize_64 ti_sysbios_family_arm_Mpu_RegionSize_64
#define Mpu_RegionSize_128 ti_sysbios_family_arm_Mpu_RegionSize_128
#define Mpu_RegionSize_256 ti_sysbios_family_arm_Mpu_RegionSize_256
#define Mpu_RegionSize_512 ti_sysbios_family_arm_Mpu_RegionSize_512
#define Mpu_RegionSize_1K ti_sysbios_family_arm_Mpu_RegionSize_1K
#define Mpu_RegionSize_2K ti_sysbios_family_arm_Mpu_RegionSize_2K
#define Mpu_RegionSize_4K ti_sysbios_family_arm_Mpu_RegionSize_4K
#define Mpu_RegionSize_8K ti_sysbios_family_arm_Mpu_RegionSize_8K
#define Mpu_RegionSize_16K ti_sysbios_family_arm_Mpu_RegionSize_16K
#define Mpu_RegionSize_32K ti_sysbios_family_arm_Mpu_RegionSize_32K
#define Mpu_RegionSize_64K ti_sysbios_family_arm_Mpu_RegionSize_64K
#define Mpu_RegionSize_128K ti_sysbios_family_arm_Mpu_RegionSize_128K
#define Mpu_RegionSize_256K ti_sysbios_family_arm_Mpu_RegionSize_256K
#define Mpu_RegionSize_512K ti_sysbios_family_arm_Mpu_RegionSize_512K
#define Mpu_RegionSize_1M ti_sysbios_family_arm_Mpu_RegionSize_1M
#define Mpu_RegionSize_2M ti_sysbios_family_arm_Mpu_RegionSize_2M
#define Mpu_RegionSize_4M ti_sysbios_family_arm_Mpu_RegionSize_4M
#define Mpu_RegionSize_8M ti_sysbios_family_arm_Mpu_RegionSize_8M
#define Mpu_RegionSize_16M ti_sysbios_family_arm_Mpu_RegionSize_16M
#define Mpu_RegionSize_32M ti_sysbios_family_arm_Mpu_RegionSize_32M
#define Mpu_RegionSize_64M ti_sysbios_family_arm_Mpu_RegionSize_64M
#define Mpu_RegionSize_128M ti_sysbios_family_arm_Mpu_RegionSize_128M
#define Mpu_RegionSize_256M ti_sysbios_family_arm_Mpu_RegionSize_256M
#define Mpu_RegionSize_512M ti_sysbios_family_arm_Mpu_RegionSize_512M
#define Mpu_RegionSize_1G ti_sysbios_family_arm_Mpu_RegionSize_1G
#define Mpu_RegionSize_2G ti_sysbios_family_arm_Mpu_RegionSize_2G
#define Mpu_RegionSize_4G ti_sysbios_family_arm_Mpu_RegionSize_4G
#define Mpu_A_nullPointer ti_sysbios_family_arm_Mpu_A_nullPointer
#define Mpu_A_invalidRegionId ti_sysbios_family_arm_Mpu_A_invalidRegionId
#define Mpu_defaultAttrs ti_sysbios_family_arm_Mpu_defaultAttrs
#define Mpu_enableMPU ti_sysbios_family_arm_Mpu_enableMPU
#define Mpu_enableBackgroundRegion ti_sysbios_family_arm_Mpu_enableBackgroundRegion
#define Mpu_numRegions ti_sysbios_family_arm_Mpu_numRegions
#define Mpu_isMemoryMapped ti_sysbios_family_arm_Mpu_isMemoryMapped
#define Mpu_disable ti_sysbios_family_arm_Mpu_disable
#define Mpu_disableBR ti_sysbios_family_arm_Mpu_disableBR
#define Mpu_enable ti_sysbios_family_arm_Mpu_enable
#define Mpu_enableBR ti_sysbios_family_arm_Mpu_enableBR
#define Mpu_initRegionAttrs ti_sysbios_family_arm_Mpu_initRegionAttrs
#define Mpu_isEnabled ti_sysbios_family_arm_Mpu_isEnabled
#define Mpu_setRegion ti_sysbios_family_arm_Mpu_setRegion
#define Mpu_startup ti_sysbios_family_arm_Mpu_startup
#define Mpu_Module_name ti_sysbios_family_arm_Mpu_Module_name
#define Mpu_Module_id ti_sysbios_family_arm_Mpu_Module_id
#define Mpu_Module_startup ti_sysbios_family_arm_Mpu_Module_startup
#define Mpu_Module_startupDone ti_sysbios_family_arm_Mpu_Module_startupDone
#define Mpu_Module_hasMask ti_sysbios_family_arm_Mpu_Module_hasMask
#define Mpu_Module_getMask ti_sysbios_family_arm_Mpu_Module_getMask
#define Mpu_Module_setMask ti_sysbios_family_arm_Mpu_Module_setMask
#define Mpu_Object_heap ti_sysbios_family_arm_Mpu_Object_heap
#define Mpu_Module_heap ti_sysbios_family_arm_Mpu_Module_heap

#endif /* ti_sysbios_family_arm_Mpu__localnames__done */
#endif
