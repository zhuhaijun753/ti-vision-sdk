/******************************************************************************
*
* hw_ipu_unicache_cfg.h - register-level header file for IPU
*
* Copyright (c) 2008-2013 Texas Instruments Incorporated.  All rights reserved.
* Software License Agreement
*
* Texas Instruments (TI) is supplying this software for use solely and
* exclusively on TI devices. The software is owned by TI and/or its
* suppliers, and is protected under applicable patent and copyright laws.
*
* You may not combine this software with any open-source software if such
* combination would cause this software to become subject to any of the
* license terms applicable to such open source software.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
* NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
* NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
* CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
* DAMAGES, FOR ANY REASON WHATSOEVER.
* 
******************************************************************************
*/
#ifndef HW_IPU_UNICACHE_CFG_H_
#define HW_IPU_UNICACHE_CFG_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define IPU_UNICACHE_INFO                                                                                            (0x0U)
#define IPU_UNICACHE_CONFIG                                                                                          (0x4U)
#define IPU_UNICACHE_INT                                                                                             (0x8U)
#define IPU_UNICACHE_OCP                                                                                             (0xcU)
#define IPU_UNICACHE_MAINT                                                                                           (0x10U)
#define IPU_UNICACHE_MTSTART                                                                                         (0x14U)
#define IPU_UNICACHE_MTEND                                                                                           (0x18U)
#define IPU_UNICACHE_CTADDR                                                                                          (0x1cU)
#define IPU_UNICACHE_CTDATA                                                                                          (0x20U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define IPU_UNICACHE_INFO_VERSION_SHIFT                                                                              (0U)
#define IPU_UNICACHE_INFO_VERSION_MASK                                                                               (0x0000000fU)

#define IPU_UNICACHE_INFO_WAYS_SHIFT                                                                                 (4U)
#define IPU_UNICACHE_INFO_WAYS_MASK                                                                                  (0x00000030U)
#define IPU_UNICACHE_INFO_WAYS_2WAY                                                                                   (0U)
#define IPU_UNICACHE_INFO_WAYS_4WAY                                                                                   (1U)
#define IPU_UNICACHE_INFO_WAYS_8WAY                                                                                   (2U)
#define IPU_UNICACHE_INFO_WAYS_RESERVED                                                                               (3U)

#define IPU_UNICACHE_INFO_SIZE_SHIFT                                                                                 (6U)
#define IPU_UNICACHE_INFO_SIZE_MASK                                                                                  (0x0000ffc0U)

#define IPU_UNICACHE_INFO_SLAVES_SHIFT                                                                               (16U)
#define IPU_UNICACHE_INFO_SLAVES_MASK                                                                                (0x00070000U)

#define IPU_UNICACHE_INFO_MASTERS_SHIFT                                                                              (19U)
#define IPU_UNICACHE_INFO_MASTERS_MASK                                                                               (0x00180000U)

#define IPU_UNICACHE_INFO_RESERVED_SHIFT                                                                             (21U)
#define IPU_UNICACHE_INFO_RESERVED_MASK                                                                              (0xffe00000U)

#define IPU_UNICACHE_CONFIG_RESERVED_SHIFT                                                                           (5U)
#define IPU_UNICACHE_CONFIG_RESERVED_MASK                                                                            (0xffffffe0U)

#define IPU_UNICACHE_CONFIG_SCACHE_LOCK_SHIFT                                                                        (0U)
#define IPU_UNICACHE_CONFIG_SCACHE_LOCK_MASK                                                                         (0x00000001U)
#define IPU_UNICACHE_CONFIG_SCACHE_LOCK_NON_SECURE                                                                    (0U)
#define IPU_UNICACHE_CONFIG_SCACHE_LOCK_SECURE                                                                        (1U)

#define IPU_UNICACHE_CONFIG_BYPASS_SHIFT                                                                             (1U)
#define IPU_UNICACHE_CONFIG_BYPASS_MASK                                                                              (0x00000002U)
#define IPU_UNICACHE_CONFIG_BYPASS_BYPASS                                                                             (0U)
#define IPU_UNICACHE_CONFIG_BYPASS_NORMAL                                                                             (1U)

#define IPU_UNICACHE_CONFIG_LOCK_INT_SHIFT                                                                           (2U)
#define IPU_UNICACHE_CONFIG_LOCK_INT_MASK                                                                            (0x00000004U)
#define IPU_UNICACHE_CONFIG_LOCK_INT_SECURE                                                                           (0U)
#define IPU_UNICACHE_CONFIG_LOCK_INT_NON_SECURE                                                                       (1U)

#define IPU_UNICACHE_CONFIG_LOCK_PORT_SHIFT                                                                          (3U)
#define IPU_UNICACHE_CONFIG_LOCK_PORT_MASK                                                                           (0x00000008U)
#define IPU_UNICACHE_CONFIG_LOCK_PORT_SECURE                                                                          (0U)
#define IPU_UNICACHE_CONFIG_LOCK_PORT_NON_SECURE                                                                      (1U)

#define IPU_UNICACHE_CONFIG_LOCK_MAIN_SHIFT                                                                          (4U)
#define IPU_UNICACHE_CONFIG_LOCK_MAIN_MASK                                                                           (0x00000010U)
#define IPU_UNICACHE_CONFIG_LOCK_MAIN_SECURE                                                                          (0U)
#define IPU_UNICACHE_CONFIG_LOCK_MAIN_NON_SECURE                                                                      (1U)

#define IPU_UNICACHE_INT_RESERVED_SHIFT                                                                              (9U)
#define IPU_UNICACHE_INT_RESERVED_MASK                                                                               (0xfffffe00U)

#define IPU_UNICACHE_INT_CONFIG_SHIFT                                                                                (0U)
#define IPU_UNICACHE_INT_CONFIG_MASK                                                                                 (0x00000001U)

#define IPU_UNICACHE_INT_PAGEFAULT_SHIFT                                                                             (1U)
#define IPU_UNICACHE_INT_PAGEFAULT_MASK                                                                              (0x00000002U)

#define IPU_UNICACHE_INT_MAINT_SHIFT                                                                                 (2U)
#define IPU_UNICACHE_INT_MAINT_MASK                                                                                  (0x00000004U)

#define IPU_UNICACHE_INT_WRITE_SHIFT                                                                                 (3U)
#define IPU_UNICACHE_INT_WRITE_MASK                                                                                  (0x00000008U)

#define IPU_UNICACHE_INT_READ_SHIFT                                                                                  (4U)
#define IPU_UNICACHE_INT_READ_MASK                                                                                   (0x00000010U)

#define IPU_UNICACHE_INT_PORT_SHIFT                                                                                  (5U)
#define IPU_UNICACHE_INT_PORT_MASK                                                                                   (0x000001e0U)

#define IPU_UNICACHE_OCP_RESERVED_SHIFT                                                                              (6U)
#define IPU_UNICACHE_OCP_RESERVED_MASK                                                                               (0xffffffc0U)

#define IPU_UNICACHE_OCP_WRAP_SHIFT                                                                                  (0U)
#define IPU_UNICACHE_OCP_WRAP_MASK                                                                                   (0x00000001U)
#define IPU_UNICACHE_OCP_WRAP_NON_WRAP                                                                                (0U)
#define IPU_UNICACHE_OCP_WRAP_WRAP                                                                                    (1U)

#define IPU_UNICACHE_OCP_WRBUFFER_SHIFT                                                                              (1U)
#define IPU_UNICACHE_OCP_WRBUFFER_MASK                                                                               (0x00000002U)
#define IPU_UNICACHE_OCP_WRBUFFER_NO_BUFFERED                                                                         (0U)
#define IPU_UNICACHE_OCP_WRBUFFER_BUFFERED                                                                            (1U)

#define IPU_UNICACHE_OCP_WRALLOCATE_SHIFT                                                                            (2U)
#define IPU_UNICACHE_OCP_WRALLOCATE_MASK                                                                             (0x00000004U)
#define IPU_UNICACHE_OCP_WRALLOCATE_NO_ALLOC                                                                          (0U)
#define IPU_UNICACHE_OCP_WRALLOCATE_SIDEBAND                                                                          (1U)

#define IPU_UNICACHE_OCP_CACHED_SHIFT                                                                                (3U)
#define IPU_UNICACHE_OCP_CACHED_MASK                                                                                 (0x00000008U)
#define IPU_UNICACHE_OCP_CACHED_NO_CACHE                                                                              (0U)
#define IPU_UNICACHE_OCP_CACHED_CACHE                                                                                 (1U)

#define IPU_UNICACHE_OCP_PREFETCH_SHIFT                                                                              (4U)
#define IPU_UNICACHE_OCP_PREFETCH_MASK                                                                               (0x00000010U)
#define IPU_UNICACHE_OCP_PREFETCH_MMU                                                                                 (0U)
#define IPU_UNICACHE_OCP_PREFETCH_PREFETCH                                                                            (1U)

#define IPU_UNICACHE_OCP_CLEANBUF_SHIFT                                                                              (5U)
#define IPU_UNICACHE_OCP_CLEANBUF_MASK                                                                               (0x00000020U)
#define IPU_UNICACHE_OCP_CLEANBUF_NO_CLEAN                                                                            (0U)
#define IPU_UNICACHE_OCP_CLEANBUF_CLEAN                                                                               (1U)

#define IPU_UNICACHE_MAINT_RESERVED_SHIFT                                                                            (6U)
#define IPU_UNICACHE_MAINT_RESERVED_MASK                                                                             (0xffffffc0U)

#define IPU_UNICACHE_MAINT_PRELOAD_SHIFT                                                                             (0U)
#define IPU_UNICACHE_MAINT_PRELOAD_MASK                                                                              (0x00000001U)
#define IPU_UNICACHE_MAINT_PRELOAD_DISABLE                                                                            (0U)
#define IPU_UNICACHE_MAINT_PRELOAD_ENABLE                                                                             (1U)

#define IPU_UNICACHE_MAINT_LOCK_SHIFT                                                                                (1U)
#define IPU_UNICACHE_MAINT_LOCK_MASK                                                                                 (0x00000002U)
#define IPU_UNICACHE_MAINT_LOCK_DISABLE                                                                               (0U)
#define IPU_UNICACHE_MAINT_LOCK_ENABLE                                                                                (1U)

#define IPU_UNICACHE_MAINT_UNLOCK_SHIFT                                                                              (2U)
#define IPU_UNICACHE_MAINT_UNLOCK_MASK                                                                               (0x00000004U)
#define IPU_UNICACHE_MAINT_UNLOCK_DISABLE                                                                             (0U)
#define IPU_UNICACHE_MAINT_UNLOCK_ENABLE                                                                              (1U)

#define IPU_UNICACHE_MAINT_CLEAN_SHIFT                                                                               (3U)
#define IPU_UNICACHE_MAINT_CLEAN_MASK                                                                                (0x00000008U)
#define IPU_UNICACHE_MAINT_CLEAN_DISABLE                                                                              (0U)
#define IPU_UNICACHE_MAINT_CLEAN_ENABLE                                                                               (1U)

#define IPU_UNICACHE_MAINT_INVALIDATE_SHIFT                                                                          (4U)
#define IPU_UNICACHE_MAINT_INVALIDATE_MASK                                                                           (0x00000010U)
#define IPU_UNICACHE_MAINT_INVALIDATE_DISABLE                                                                         (0U)
#define IPU_UNICACHE_MAINT_INVALIDATE_ENABLE                                                                          (1U)

#define IPU_UNICACHE_MAINT_INTERRUPT_SHIFT                                                                           (5U)
#define IPU_UNICACHE_MAINT_INTERRUPT_MASK                                                                            (0x00000020U)
#define IPU_UNICACHE_MAINT_INTERRUPT_NO_INT                                                                           (0U)
#define IPU_UNICACHE_MAINT_INTERRUPT_GEN_INT                                                                          (1U)

#define IPU_UNICACHE_MTSTART_START_ADDR_SHIFT                                                                        (0U)
#define IPU_UNICACHE_MTSTART_START_ADDR_MASK                                                                         (0xffffffffU)

#define IPU_UNICACHE_MTEND_END_ADDR_SHIFT                                                                            (0U)
#define IPU_UNICACHE_MTEND_END_ADDR_MASK                                                                             (0xffffffffU)

#define IPU_UNICACHE_CTADDR_ADDRESS_SHIFT                                                                            (0U)
#define IPU_UNICACHE_CTADDR_ADDRESS_MASK                                                                             (0xffffffffU)

#define IPU_UNICACHE_CTDATA_DATA_SHIFT                                                                               (0U)
#define IPU_UNICACHE_CTDATA_DATA_MASK                                                                                (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_IPU_UNICACHE_CFG_H_ */
