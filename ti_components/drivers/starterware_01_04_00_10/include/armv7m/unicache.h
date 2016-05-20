/**
 *  \file     unicache.h
 *
 *  \brief    This file contains the interfaces present in the Uni-cache HAL.
 *            This also contains some related macros, structures and enums.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

#ifndef UNICACHE_H_
#define UNICACHE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief UNICACHE_WAIT_INFINITE: Macro defining the flag for infinite wait
 */
#define UNICACHE_WAIT_INFINITE                         (0xFFFFFFFFU)

/**
 * \brief UNICACHE_WAIT_NOWAIT: Macro defining the flag for no wait
 */
#define UNICACHE_WAIT_NOWAIT                           (0x0U)

/* Macros defining mask, shift, enable and disable values for performing clean
 * and invalidate operation at same time.
 */
#define IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_SHIFT               ( \
        IPU_UNICACHE_MAINT_CLEAN_SHIFT)
#define IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_MASK                ( \
        IPU_UNICACHE_MAINT_CLEAN_MASK | IPU_UNICACHE_MAINT_INVALIDATE_MASK)
#define IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_DISABLE             (0U)
#define IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_ENABLE              (3U)

/* Macros defining mask, shift, enable and disable values for performing preload
 * and lock operation at same time.
 */
#define IPU_UNICACHE_MAINT_PRELOADANDLOCK_SHIFT                   ( \
        IPU_UNICACHE_MAINT_PRELOAD_SHIFT)
#define IPU_UNICACHE_MAINT_PRELOADANDLOCK_MASK                    ( \
        IPU_UNICACHE_MAINT_PRELOAD_MASK | IPU_UNICACHE_MAINT_LOCK_MASK)
#define IPU_UNICACHE_MAINT_PRELOADANDLOCK_DISABLE                 (0U)
#define IPU_UNICACHE_MAINT_PRELOADANDLOCK_ENABLE                  (3U)

/**
 * \brief  This macro defines the size of the uni-cache line in bytes.
 */
#define UNICACHE_LINE_SIZE                             ((uint32_t) 32U)

/**
 * \brief  This macro defines the mask value used to calculate uni-cache line
 *         address.
 */
#define UNICACHE_LINE_ADDRESS_MASK                     ((uint32_t) ~(0x1FU))

/**
 * \brief  This macro defines the maximum buffer size for doing discrete cache
 *         line operations in bytes.
 *
 * For buffers below a certain size, cache maintenance operations are more
 * efficient if performed on single cache lines at a time rather than on an
 * entire region. For buffer sizes equal to or less than this value,
 * the invalidate and write back APIs use a series of individual cache line
 * operations. For buffer sizes large than this value, a a single block mode
 * operation will be performed.
 */
#define UNICACHE_MAX_LINE_MODE_BUFF_SIZE               ((uint32_t) 1024U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function first checks if unicache is enabled and enables it if
 *          it is not enabled.
 *
 * \param   baseAddr       Base Address of Uni-cache registers.
 *
 * \return  None.
 *
 * \note    The check is needed because hard fault is created on IPU if unicache
 *          is enabled when the enable bit was set previously only.
 */
void UNICACHEEnable(uint32_t baseAddr);

/**
 * \brief   This function disables the unicache.
 *
 * \param   baseAddr       Base Address of Uni-cache registers.
 *
 * \return  None.
 */
void UNICACHEDisable(uint32_t baseAddr);

/**
 * \brief   This function invalidates one cache line.
 *
 * \param   baseAddr        Base Address of Uni-cache registers.
 * \param   maintenanceAddr Maintenance Address. Should be aligned
 *                          as per cache line size #UNICACHE_LINE_SIZE.
 *
 * \return  None.
 *
 * \note    This API does not wait for maintenance operation to complete. App
 *          should take care of timing considerations.
 */
void UNICACHEInvalidateCacheLine(uint32_t baseAddr,
                                 uint32_t maintenanceAddr);
/**
 * \brief   This function invalidates the cache lines in the region defined by
 *          maintenance start/end address.
 *
 * \param   baseAddr      Base Address of Uni-cache registers.
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 * \param   wait          Wait Time for maintenance operation completion.
 *
 * \return  status        Whether maintenance operation completed successfully.
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
int32_t UNICACHEInvalidate(uint32_t baseAddr,
                           uint32_t startAddress,
                           uint32_t byteCount,
                           uint32_t wait);

/**
 * \brief   This function evicts one dirty cache line.
 *
 * \param   baseAddr        Base Address of Uni-cache registers.
 * \param   maintenanceAddr Maintenance Address. Should be aligned
 *                          as per cache line size #UNICACHE_LINE_SIZE.
 *
 * \return  None.
 *
 * \note    This API does not wait for maintenance operation to complete. App
 *          should take care of timing considerations.
 */
void UNICACHEWriteBackCacheLine(uint32_t baseAddr,
                                uint32_t maintenanceAddr);

/**
 * \brief   This function evicts the dirty cache lines in the region defined by
 *          maintenance start/end address.
 *
 * \param   baseAddr      Base Address of Uni-cache registers.
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 * \param   wait          Wait Time for maintenance operation completion.
 *
 * \return  status        Whether maintenance operation completed successfully.
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
int32_t UNICACHEWriteBack(uint32_t baseAddr,
                          uint32_t startAddress,
                          uint32_t byteCount,
                          uint32_t wait);

/**
 * \brief   This function locks one cache line.
 *
 * \param   baseAddr        Base Address of Uni-cache registers.
 * \param   maintenanceAddr Maintenance Address. Should be aligned
 *                          as per cache line size #UNICACHE_LINE_SIZE.
 *
 * \return  None.
 *
 * \note    This API does not wait for maintenance operation to complete. App
 *          should take care of timing considerations.
 */
void UNICACHELockCacheLine(uint32_t baseAddr,
                           uint32_t maintenanceAddr);

/**
 * \brief   This function locks the region defined by maintenance start/end
 *          address.
 *
 * \param   baseAddr      Base Address of Uni-cache registers.
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 * \param   wait          Wait Time for maintenance operation completion.
 *
 * \return  status        Whether maintenance operation completed successfully.
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
int32_t UNICACHELock(uint32_t baseAddr,
                     uint32_t startAddress,
                     uint32_t byteCount,
                     uint32_t wait);

/**
 * \brief   This function unlocks one cache line.
 *
 * \param   baseAddr        Base Address of Uni-cache registers.
 * \param   maintenanceAddr Maintenance Address. Should be aligned
 *                          as per cache line size #UNICACHE_LINE_SIZE.
 *
 * \return  None.
 *
 * \note    This API does not wait for maintenance operation to complete. App
 *          should take care of timing considerations.
 */
void UNICACHEUnlockCacheLine(uint32_t baseAddr,
                             uint32_t maintenanceAddr);

/**
 * \brief   This function unlocks the region defined by maintenance start/end
 *          address.
 *
 * \param   baseAddr      Base Address of Uni-cache registers.
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 * \param   wait          Wait Time for maintenance operation completion.
 *
 * \return  status        Whether maintenance operation completed successfully.
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
int32_t UNICACHEUnlock(uint32_t baseAddr,
                       uint32_t startAddress,
                       uint32_t byteCount,
                       uint32_t wait);

/**
 * \brief   This function pre-loads one cache line.
 *
 * \param   baseAddr        Base Address of Uni-cache registers.
 * \param   maintenanceAddr Maintenance Address. Should be aligned
 *                          as per cache line size #UNICACHE_LINE_SIZE.
 *
 * \return  None.
 *
 * \note    This API does not wait for maintenance operation to complete. App
 *          should take care of timing considerations.
 */
void UNICACHEPreloadCacheLine(uint32_t baseAddr,
                              uint32_t maintenanceAddr);

/**
 * \brief   This function pre-loads the region defined by maintenance start/end
 *          address.
 *
 * \param   baseAddr      Base Address of Uni-cache registers.
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 * \param   wait          Wait Time for maintenance operation completion.
 *
 * \return  status        Whether maintenance operation completed successfully.
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
int32_t UNICACHEPreload(uint32_t baseAddr,
                        uint32_t startAddress,
                        uint32_t byteCount,
                        uint32_t wait);

/**
 * \brief   This function invalidates and evicts one cache line.
 *
 * \param   baseAddr        Base Address of Uni-cache registers.
 * \param   maintenanceAddr Maintenance Address. Should be aligned
 *                          as per cache line size #UNICACHE_LINE_SIZE.
 *
 * \return  None.
 *
 * \note    This API does not wait for maintenance operation to complete. App
 *          should take care of timing considerations.
 */
void UNICACHEWriteBackAndInvalidateCacheLine(uint32_t baseAddr,
                                             uint32_t maintenanceAddr);

/**
 * \brief   This function invalidates and evicts the cache lines in the region
 *          defined by maintenance start/end address.
 *
 * \param   baseAddr      Base Address of Uni-cache registers.
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 * \param   wait          Wait Time for maintenance operation completion.
 *
 * \return  status        Whether maintenance operation completed successfully.
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
int32_t UNICACHEWriteBackAndInvalidate(uint32_t baseAddr,
                                       uint32_t startAddress,
                                       uint32_t byteCount,
                                       uint32_t wait);

/**
 * \brief   This function pre-loads and locks one cache line.
 *
 * \param   baseAddr        Base Address of Uni-cache registers.
 * \param   maintenanceAddr Maintenance Address. Should be aligned
 *                          as per cache line size #UNICACHE_LINE_SIZE.
 *
 * \return  None.
 *
 * \note    This API does not wait for maintenance operation to complete. App
 *          should take care of timing considerations.
 */
void UNICACHEPreloadAndLockCacheLine(uint32_t baseAddr,
                                     uint32_t maintenanceAddr);

/**
 * \brief   This function pre-loads and locks the region defined by maintenance
 *          start/end address.
 *
 * \param   baseAddr      Base Address of Uni-cache registers.
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 * \param   wait          Wait Time for maintenance operation completion.
 *
 * \return  status        Whether maintenance operation completed successfully.
 *                        STW_SOK   : Success
 *                        STW_EFAIL : Failure
 */
int32_t UNICACHEPreloadAndLock(uint32_t baseAddr,
                               uint32_t startAddress,
                               uint32_t byteCount,
                               uint32_t wait);

/**
 * \brief   This function evicts the whole unicache.
 *
 * \param   baseAddr Base Address of Uni-cache registers.
 * \param   wait     Wait Time for maintenance operation completion.
 *
 * \return  status   Whether maintenance operation completed successfully.
 *                   STW_SOK   : Success
 *                   STW_EFAIL : Failure
 */
int32_t UNICACHEWriteBackAll(uint32_t baseAddr, uint32_t wait);

/**
 * \brief   This function invalidates the whole unicache.
 *
 * \param   baseAddr Base Address of Uni-cache registers.
 * \param   wait     Wait Time for maintenance operation completion.
 *
 * \return  status   Whether maintenance operation completed successfully.
 *                   STW_SOK   : Success
 *                   STW_EFAIL : Failure
 */
int32_t UNICACHEInvalidateAll(uint32_t baseAddr, uint32_t wait);

/**
 * \brief   This function invalidates and evicts the whole unicache.
 *
 * \param   baseAddr Base Address of Uni-cache registers.
 * \param   wait     Wait Time for maintenance operation completion.
 *
 * \return  status   Whether maintenance operation completed successfully.
 *                   STW_SOK   : Success
 *                   STW_EFAIL : Failure
 */
int32_t UNICACHEWriteBackAndInvalidateAll(uint32_t baseAddr, uint32_t wait);

#ifdef __cplusplus
}

#endif

#endif

