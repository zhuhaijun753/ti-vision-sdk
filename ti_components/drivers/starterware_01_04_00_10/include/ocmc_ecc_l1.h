/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
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
/**
 * \file  ocmc_ecc_l1.h
 *
 * \brief This module defines the OCMC HAL.
 *        This file contains the OCMC Hardware Abstraction Layer API used for
 *        low-level programming of the OCMC IP
 */

#ifndef OCMC_ECC_L1_H_
#define OCMC_ECC_L1_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include <stdio.h>
#include "soc.h"
#include "hw_ocmc_ram.h"

typedef uint32_t ocmc_addr_t;
typedef uint8_t  ocmc_buf_id_t;

#define OCMC_BUF_ENABLE           ((uint32_t) 1U)
#define OCMC_BUF_DISABLE          ((uint32_t) 0U)

/*Arguments passed as flag to set or get interrupt status*/
#define OCMC_ECC_SEC_ERROR_FOUND \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_SEC_ERR_FOUND_MASK)
#define OCMC_ECC_DED_ERROR_FOUND \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_DED_ERR_FOUND_MASK)
#define OCMC_ECC_ADDR_ERROR_FOUND \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_ADDR_ERR_FOUND_MASK)
#define OCMC_ADDR_OUT_OF_RANGE \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_OUT_OF_RANGE_ERR_FOUND_MASK)
#define OCMC_CBUF_VIRT_ADDR_ERROR \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_VIRTUAL_ADDR_ERR_FOUND_MASK)
#define OCMC_CBUF_WR_OUT_OF_RANGE \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_MASK)
#define OCMC_CBUF_WR_VBUF_START_ERR \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_VBUF_WRITE_START_ERR_FOUND_MASK)
#define OCMC_CBUF_WR_ADDR_SEQ_ERR \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_WRITE_SEQUENCE_ERR_FOUND_MASK)
#define OCMC_CBUF_RD_OUT_OF_RANGE \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_MASK)
#define OCMC_CBUF_RD_VBUF_START_ERR \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_VBUF_READ_START_ERR_FOUND_MASK)
#define OCMC_CBUF_RD_ADDR_SEQ_ERR \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_READ_SEQUENCE_ERR_FOUND_MASK)
#define OCMC_CBUF_OVERFLOW_MID_FOUND \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_OVERFLOW_MID_ERR_FOUND_MASK)
#define OCMC_CBUF_OVER_FLOW_WRAP_FOUND \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_OVERFLOW_WRAP_ERR_FOUND_MASK)
#define OCMC_CBUF_UNDERFLOW \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_UNDERFLOW_ERR_FOUND_MASK)
#define OCMC_CBUF_SHORT_FRAME_DETECT \
    (OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_SHORT_FRAME_DETECT_FOUND_MASK)
#define OCMC_INTERRUPT_ALL             (0x7FFFU)

/* Macros to be passed to OCMCEccErrClearTraceHist API as errflag to clear error
 * history
 * CLEAR_SEC_ERR_HIST - Clear stored SEC error history
 * CLEAR_DEC_ERR_HIST - Clear stored DED error history
 * CLEAR_ADDR_ERR_HIST - Clear stored ADDR error history
 * CLESR_SEC_BIT_DIST_HIST - Clear stored SEC bit distribution history
 * CLEAR_ALL_HIST - CLears all history
 */
#define CLEAR_SEC_ERR_HIST \
    (OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_SEC_ERR_CNT_MASK)
#define CLEAR_DEC_ERR_HIST \
    (OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_DED_ERR_CNT_MASK)
#define CLEAR_ADDR_ERR_HIST \
    (OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_ADDR_ERR_CNT_MASK)
#define CLESR_SEC_BIT_DIST_HIST \
    (OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_SEC_BIT_DISTR_MASK)
#define CLEAR_ALL_HIST                 (0x0FU)

/*err flag to be passed to OCMCEccErrClearTraceHist API*/
#define OCMC_CLEAR_SEC_ERROR_HIST \
    (OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_SEC_ERR_CNT_MASK)
#define OCMC_CLEAR_DED_ERROR_HIST \
    (OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_DED_ERR_CNT_MASK)
#define OCMC_CLEAR_ADDR_ERROR_HIST \
    (OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_ADDR_ERR_CNT_MASK)
#define OCMC_CLEAR_SEC_BIT_DIST_HIST \
    (OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_SEC_BIT_DISTR_MASK)
#define OCMC_ALL_HIST                  (0x0FU)

/* enum to set ocmc sysconfig mode */
typedef enum
{
    FORCE_IDLE,
    NO_IDLE,
    SMART_IDLE,
    SMART_IDLE_WAKEUP_CAPABLE
}ocmc_sysconfig_mode;

typedef enum
{
    OCMC_NON_ECC_DATA_ACCESS,
    OCMC_NON_ECC_CODE_ACCESS,
    OCMC_FULL_ECC_ENABLE,
    OCMC_BLOCK_ECC_ENABLE
}ocmc_cfg_ecc_mode;

/* used by OCMCErrCntStatusGet */
typedef enum
{
    OCMC_ECC_SEC_ERR_CNT,
    OCMC_ECC_DED_ERR_CNT,
    OCMC_ECC_ADDR_ERR_CNT,
    OCMC_ECC_ALL_ERR_CNT
}ocmc_err_cnt_type;

/**
 * \enum ocmc_wr_overflow_handler_t
 * \brief  Enumeration that specifies possible write overflow handling options
 *
 */
typedef enum
{
    e_wr_overflow_disable_on_cbuf_overflow_wrap,
    e_wr_overflow_disable_on_all_overflow,
    e_wr_overflow_no_disable
} ocmc_wr_overflow_handler_t;

/**
 * \enum ocmc_wr_overflow_reenable_t
 * \brief  Enumeration that specifies possible write overflow check re-enable
 *         options
 *
 */
typedef enum
{
    e_overflow_reenable_after_next_write_read,
    e_overflow_reenable_after_next_write,
    e_overflow_reenable_after_next_read,
    e_overflow_reenable_immediate
} ocmc_wr_overflow_reenable_t;

/**
 * \enum ocmc_cbuf_err_t
 * \brief  Enumeration that specifies possible CBUF errors
 *
 */
typedef enum
{
    e_cbuf_stat_wr_out_of_range,
    e_cbuf_stat_wr_vbuf_start_error,
    e_cbuf_stat_wr_addr_seq_error,
    e_cbuf_stat_rd_out_of_range,
    e_cbuf_stat_rd_vbuf_start_error,
    e_cbuf_stat_rd_addr_seq_error,
    e_cbuf_stat_overflow_mid,
    e_cbuf_stat_overflow_wrap,
    e_cbuf_stat_underflow,
    e_cbuf_stat_short_frame_detect
} ocmc_cbuf_err_t;

/**
 * \enum ocmc_ecc_err_t
 * \brief  Enumeration that specifies possible ECC errors
 *
 */
typedef enum
{
    OCMC_ECC_SEC_ERR,
    /**< SEC - Single Error Correction */
    OCMC_ECC_DED_ERR,
    /**< DED - Double Error detection */
    OCMC_ECC_ADDR_ERR
    /**< Address Error
     * You can induce an address error by corrupting the stored the
     * CODE word[8* :1] by applying XOR with a value (137..154) so that the
     * error_bit_code(code_saved[8:1] ^ code_gen[8:1]) ends up in the
     * (137..154) range. Error_bit_code=137 indicates addr[0] error.
     * 138 indicates addr[1].  And so on.  Note that info on which addr bit had
     * an error is not available.
     * Note that an addr error supercedes SEC/DED.
     */
}ocmc_ecc_err_t;

/**
 * \enum ocmc_sec_ecc_err_dist_t
 * \brief  Enumeration that specifies possible SEC ECC error Distribution Type
 *
 */
typedef enum
{
    OCMC_ECC_SEC_ERR_DIST_0,
    OCMC_ECC_SEC_ERR_DIST_1,
    OCMC_ECC_SEC_ERR_DIST_2,
    OCMC_ECC_SEC_ERR_DIST_3
}ocmc_sec_ecc_err_dist_t;

/** \brief API to configure OCMC Mode
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] mode Modes as defined in enum ocmc_sysconfig_mode
 * \returns   None
 */
void OCMCModeSet(uint32_t baseAddr, ocmc_sysconfig_mode mode);

/** \brief API to soft-reset entire OCMC
 * \param[in] baseAddr OCMC Instance baseAddr
 * \returns   None
 */
void OCMCSoftReset(uint32_t baseAddr);

/** \brief API to return the size of the OCMC memory in bytes
 * \param[in] baseAddr OCMC Instance baseAddr
 * \returns Size of OCMC RAM in bytes
 */
uint32_t OCMCGetRAMSize(uint32_t baseAddr);

/** \brief API to get the Circular buffer capability for the ocmc instance
 * passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \returns   non zero value if supports circular buffer
 *            0 if not supported
 */
uint32_t OCMCCbufCapabilityGet(uint32_t baseAddr);

/** \brief API to get the ECC capability for the ocmc instance passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \returns   non zero value if supports ECC
 *            0 if not supported
 */
uint32_t OCMCEccCapabilityGet(uint32_t baseAddr);

/** \brief API to get raw interrupt status for the interrupt flag passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] intr_group Argument to select interrupt group (0 or 1)
 * \param[in] intFlag To select interrupt type below are the values. These macro
 *            can be ORed and passed to get multiple interrupt status.
 *
 * OCMC_ECC_SEC_ERROR_FOUND
 * OCMC_ECC_DED_ERROR_FOUND
 * OCMC_ECC_ADDR_ERROR_FOUND
 * OCMC_ADDR_OUT_OF_RANGE
 * OCMC_CBUF_VIRT_ADDR_ERROR
 * OCMC_CBUF_WR_OUT_OF_RANGE
 * OCMC_CBUF_WR_VBUF_START_ERR
 * OCMC_CBUF_WR_ADDR_SEQ_ERR
 * OCMC_CBUF_RD_OUT_OF_RANGE
 * OCMC_CBUF_RD_VBUF_START_ERR
 * OCMC_CBUF_RD_ADDR_SEQ_ERR
 * OCMC_CBUF_OVERFLOW_MID_FOUND
 * OCMC_CBUF_OVER_FLOW_WRAP_FOUND
 * OCMC_CBUF_UNDERFLOW
 * OCMC_CBUF_SHORT_FRAME_DETECT
 * OCMC_INTERRUPT_ALL
 *
 * \returns Interrupt status for the intFlag passed
 */
uint32_t OCMCIntStatusRawGet(uint32_t baseAddr, uint8_t intr_group,
                             uint32_t intFlag);

/** \brief API to set raw interrupt status for the interrupt flag passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] intr_group Argument to select interrupt group (0 or 1)
 * \param[in] intFlag To select interrupt type below are the values. These macro
 *            can be ORed and passed to set multiple interrupt status.
 *
 * OCMC_ECC_SEC_ERROR_FOUND
 * OCMC_ECC_DED_ERROR_FOUND
 * OCMC_ECC_ADDR_ERROR_FOUND
 * OCMC_ADDR_OUT_OF_RANGE
 * OCMC_CBUF_VIRT_ADDR_ERROR
 * OCMC_CBUF_WR_OUT_OF_RANGE
 * OCMC_CBUF_WR_VBUF_START_ERR
 * OCMC_CBUF_WR_ADDR_SEQ_ERR
 * OCMC_CBUF_RD_OUT_OF_RANGE
 * OCMC_CBUF_RD_VBUF_START_ERR
 * OCMC_CBUF_RD_ADDR_SEQ_ERR
 * OCMC_CBUF_OVERFLOW_MID_FOUND
 * OCMC_CBUF_OVER_FLOW_WRAP_FOUND
 * OCMC_CBUF_UNDERFLOW
 * OCMC_CBUF_SHORT_FRAME_DETECT
 * OCMC_INTERRUPT_ALL
 *
 * \returns None
 *
 */
void OCMCIntStatusRawSet(uint32_t baseAddr, uint8_t intr_group,
                         uint32_t intFlag);

/** \brief API to get status of generated interrupt for the interrupt flag
 * passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] intr_group Argument to select interrupt group (0 or 1)
 * \param[in] intFlag To select interrupt type below are the values. These macro
 *            can be ORed and passed to get multiple interrupt status.
 *
 * OCMC_ECC_SEC_ERROR_FOUND
 * OCMC_ECC_DED_ERROR_FOUND
 * OCMC_ECC_ADDR_ERROR_FOUND
 * OCMC_ADDR_OUT_OF_RANGE
 * OCMC_CBUF_VIRT_ADDR_ERROR
 * OCMC_CBUF_WR_OUT_OF_RANGE
 * OCMC_CBUF_WR_VBUF_START_ERR
 * OCMC_CBUF_WR_ADDR_SEQ_ERR
 * OCMC_CBUF_RD_OUT_OF_RANGE
 * OCMC_CBUF_RD_VBUF_START_ERR
 * OCMC_CBUF_RD_ADDR_SEQ_ERR
 * OCMC_CBUF_OVERFLOW_MID_FOUND
 * OCMC_CBUF_OVER_FLOW_WRAP_FOUND
 * OCMC_CBUF_UNDERFLOW
 * OCMC_CBUF_SHORT_FRAME_DETECT
 * OCMC_INTERRUPT_ALL
 *
 * \returns Interrupt status for the intFlag passed
 */
uint32_t OCMCIntStatusEnableGet(uint32_t baseAddr, uint8_t intr_group,
                                uint32_t intFlag);

/** \brief API to clear the status of generated interrupt for the interrupt flag
 * passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] intr_group Argument to select interrupt group (0 or 1)
 * \param[in] intFlag To select interrupt type below are the values. These macro
 *            can be ORed and passed to clear multiple interrupt status.
 *
 * OCMC_ECC_SEC_ERROR_FOUND
 * OCMC_ECC_DED_ERROR_FOUND
 * OCMC_ECC_ADDR_ERROR_FOUND
 * OCMC_ADDR_OUT_OF_RANGE
 * OCMC_CBUF_VIRT_ADDR_ERROR
 * OCMC_CBUF_WR_OUT_OF_RANGE
 * OCMC_CBUF_WR_VBUF_START_ERR
 * OCMC_CBUF_WR_ADDR_SEQ_ERR
 * OCMC_CBUF_RD_OUT_OF_RANGE
 * OCMC_CBUF_RD_VBUF_START_ERR
 * OCMC_CBUF_RD_ADDR_SEQ_ERR
 * OCMC_CBUF_OVERFLOW_MID_FOUND
 * OCMC_CBUF_OVER_FLOW_WRAP_FOUND
 * OCMC_CBUF_UNDERFLOW
 * OCMC_CBUF_SHORT_FRAME_DETECT
 * OCMC_INTERRUPT_ALL
 *
 * \returns None
 */
void OCMCIntStatusEnableClear(uint32_t baseAddr, uint8_t intr_group,
                              uint32_t intFlag);

/** \brief API to enable interrupt for the interrupt flag passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] intr_group Argument to select interrupt group (0 or 1)
 * \param[in] intFlag To select interrupt type below are the values. These macro
 *            can be ORed and passed to enable multiple interrupt status.
 *
 * OCMC_ECC_SEC_ERROR_FOUND
 * OCMC_ECC_DED_ERROR_FOUND
 * OCMC_ECC_ADDR_ERROR_FOUND
 * OCMC_ADDR_OUT_OF_RANGE
 * OCMC_CBUF_VIRT_ADDR_ERROR
 * OCMC_CBUF_WR_OUT_OF_RANGE
 * OCMC_CBUF_WR_VBUF_START_ERR
 * OCMC_CBUF_WR_ADDR_SEQ_ERR
 * OCMC_CBUF_RD_OUT_OF_RANGE
 * OCMC_CBUF_RD_VBUF_START_ERR
 * OCMC_CBUF_RD_ADDR_SEQ_ERR
 * OCMC_CBUF_OVERFLOW_MID_FOUND
 * OCMC_CBUF_OVER_FLOW_WRAP_FOUND
 * OCMC_CBUF_UNDERFLOW
 * OCMC_CBUF_SHORT_FRAME_DETECT
 * OCMC_INTERRUPT_ALL
 *
 * \returns None
 */
void OCMCIntEnable(uint32_t baseAddr, uint8_t intr_group, uint32_t intFlag);

/** \brief API to disable interrupt for the interrupt flag passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] intr_group Argument to select interrupt group (0 or 1)
 * \param[in] intFlag To select interrupt type below are the values. These macro
 *            can be ORed and passed to disable multiple interrupt status.
 *
 * OCMC_ECC_SEC_ERROR_FOUND
 * OCMC_ECC_DED_ERROR_FOUND
 * OCMC_ECC_ADDR_ERROR_FOUND
 * OCMC_ADDR_OUT_OF_RANGE
 * OCMC_CBUF_VIRT_ADDR_ERROR
 * OCMC_CBUF_WR_OUT_OF_RANGE
 * OCMC_CBUF_WR_VBUF_START_ERR
 * OCMC_CBUF_WR_ADDR_SEQ_ERR
 * OCMC_CBUF_RD_OUT_OF_RANGE
 * OCMC_CBUF_RD_VBUF_START_ERR
 * OCMC_CBUF_RD_ADDR_SEQ_ERR
 * OCMC_CBUF_OVERFLOW_MID_FOUND
 * OCMC_CBUF_OVER_FLOW_WRAP_FOUND
 * OCMC_CBUF_UNDERFLOW
 * OCMC_CBUF_SHORT_FRAME_DETECT
 * OCMC_INTERRUPT_ALL
 *
 * \returns None
 */
void OCMCIntDisable(uint32_t baseAddr, uint8_t intr_group, uint32_t intFlag);

/** \brief API to get enabled interrupt status for the interrupt flag passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] intr_group Argument to select interrupt group (0 or 1)
 * \param[in] intFlag To select interrupt type below are the values. These macro
 *            can be ORed and passed to get multiple interrupt status.
 *
 * OCMC_ECC_SEC_ERROR_FOUND
 * OCMC_ECC_DED_ERROR_FOUND
 * OCMC_ECC_ADDR_ERROR_FOUND
 * OCMC_ADDR_OUT_OF_RANGE
 * OCMC_CBUF_VIRT_ADDR_ERROR
 * OCMC_CBUF_WR_OUT_OF_RANGE
 * OCMC_CBUF_WR_VBUF_START_ERR
 * OCMC_CBUF_WR_ADDR_SEQ_ERR
 * OCMC_CBUF_RD_OUT_OF_RANGE
 * OCMC_CBUF_RD_VBUF_START_ERR
 * OCMC_CBUF_RD_ADDR_SEQ_ERR
 * OCMC_CBUF_OVERFLOW_MID_FOUND
 * OCMC_CBUF_OVER_FLOW_WRAP_FOUND
 * OCMC_CBUF_UNDERFLOW
 * OCMC_CBUF_SHORT_FRAME_DETECT
 * OCMC_INTERRUPT_ALL
 *
 * \returns Enabled interrupt status for the intFlag passed
 */
uint32_t OCMCIntEnableGet(uint32_t baseAddr, uint8_t intr_group,
                          uint32_t intFlag);

/** \brief API to configure OCMC ECC
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] ocmc_ecc_mode_cfg OCMC_ECC module memory access modes
 *            000  :  non-ECC mode (data access)
 *            001  :  non-ECC mode (code access)
 *            010  :  full ECC enabled mode
 *            011  :  block ECC enabled mode
 *            1xx  :  reserved
 *
 * \param[in] cfgEccSecAutoCorrectEn
 * \param[in] cfgEccErrSrespEn
 * \param[in] cfgEccOptNonEccReadEn
 *
 * \returns None
 */
void OCMCEccConfig(uint32_t baseAddr, ocmc_cfg_ecc_mode ocmc_ecc_mode_cfg,
                   uint32_t cfgEccSecAutoCorrectEn, uint32_t cfgEccErrSrespEn,
                   uint32_t cfgEccOptNonEccReadEn);

/** \brief API  gets status of enable ECC blocks
 *
 * \param[in] baseAddr     OCMC Instance baseAddr
 *
 * \return word containing enabled cbuf status
 */
uint32_t OCMCRAMBlockEnableStatusGet(uint32_t baseAddr);

/** \brief API  enables or disables ECC for the block number passed
 *
 * \param[in] baseAddr     OCMC Instance baseAddr
 * \param[in] enable       enable = 1 enable block
 *                         enable = 0 disable block
 * \param[in] blockNum     block number to be enabled or disabled
 * \return    None
 */
void OCMCRAMBlockEnableCtrl(uint32_t baseAddr, uint32_t enable,
                            uint32_t blockNum);

/** \brief API to configure OCMC ECC Err trace
 *
 * \param[in] baseAddr     OCMC Instance baseAddr
 * \param[in] secErrCnt -  Number of SEC error to trigger an interrupt
 *                         (Must be > 0 to generate an interrupt)
 * \param[in] dedErrCnt -  Number of DED errors to trigger an interrupt
 *                         (Must be > 0 to generate an interrupt)
 * \param[in] addrErrCnt - Number of ADDR errors to trigger an interrupt
 *                         (Must be > 0 to generate an interrupt)
 * \param[in] discardDupErrAddr - 0 :  Save even the duplicated addresses
 *                         1 :  Save only the unique addresses
 * \return    None
 */
void OCMCEccErrTraceConfig(uint32_t baseAddr, uint32_t secErrCnt,
                           uint32_t dedErrCnt, uint32_t addrErrCnt,
                           uint32_t discardDupErrAddr);

/** \brief API to clear OCMC ECC Err trace history
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] errFlag flag to indicate the err history to be cleared.
 *            errFlag can take the possible values
 *            OCMC_CLEAR_SEC_ERROR_HIST
 *            OCMC_CLEAR_DED_ERROR_HIST
 *            OCMC_CLEAR_ADDR_ERROR_HIST
 *            OCMC_CLEAR_SEC_BIT_DIST_HIST
 *            OCMC_ALL_HIST
 * \return    None
 */
void OCMCEccErrClearTraceHist(uint32_t baseAddr, uint32_t errFlag);

/** \brief API Returns Error Count for the error type passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] errType errtype as define in enum ocmc_err_cnt_type
 *
 * \return Error count for the error type passed
 */
uint32_t OCMCErrCntStatusGet(uint32_t baseAddr, ocmc_err_cnt_type errType);

/** \brief API to set virtual buffer start address for the buffer id passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] vbuf_start virtual buffer start address
 * \returns None
 */
void OCMCVBufStartAddrSet(uint32_t baseAddr, ocmc_buf_id_t buf_id,
                          ocmc_addr_t vbuf_start);

/** \brief API to get virtual buffer start address for the buffer id passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \returns virtual buffer start address for the buffer id passed
 */
uint32_t OCMCVBufStartAddrGet(uint32_t baseAddr, ocmc_buf_id_t buf_id);

/** \brief API to set virtual buffer end address for the buffer id passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] vbuf_end virtual buffer end address
 * \returns None
 */
void OCMCVBufEndAddrSet(uint32_t baseAddr, ocmc_buf_id_t buf_id,
                        ocmc_addr_t vbuf_end);

/** \brief API to get virtual buffer end address for the buffer id passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \returns virtual buffer end address for the buffer id passed
 */
uint32_t OCMCVBufEndAddrGet(uint32_t baseAddr, ocmc_buf_id_t buf_id);

/** \brief API to set ocmc circular buffer start address for the buffer id
 * passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] cbuf_start ocmc circular buffer start address
 * \returns None
 */
void OCMCCBufStartAddrSet(uint32_t baseAddr, ocmc_buf_id_t buf_id,
                          ocmc_addr_t cbuf_start);

/** \brief API to get ocmc circular buffer start address for the buffer id
 * passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] cbuf_start ocmc circular buffer start address
 * \returns   ocmc circular buffer start address for the buffer id passed
 */
uint32_t OCMCCBufStartAddrGet(uint32_t baseAddr, ocmc_buf_id_t buf_id);

/** \brief API to set ocmc circular buffer size for the buffer id passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] cbuf_size ocmc circular buffer size
 * \returns   None
 */
void OCMCCBufSizeSet(uint32_t baseAddr, ocmc_buf_id_t buf_id,
                     uint32_t cbuf_size);

/** \brief API to get ocmc circular buffer size for the buffer id passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \returns   ocmc circular buffer size for the buffer id passed
 */
uint32_t OCMCCBufSizeGet(uint32_t baseAddr, ocmc_buf_id_t buf_id);

/** \brief API to enable/disable a specified VBUF
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] buf_enable Buffer enable / disable flag - use OCMC_BUF_DISABLE to
 *            disable, OCMC_BUF_ENABLE to enable
 * \returns None
 */
void OCMCCbufEnableCtrl(uint32_t baseAddr, ocmc_buf_id_t buf_id,
                        uint8_t buf_enable);

/** \brief API to Get state of the cbuf(enabled or disabled)
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \returns Non zero value if circular buffer is enabled.
 *          zero if disabled
 */
uint32_t OCMCCbufEnableStatusGet(uint32_t baseAddr, ocmc_buf_id_t buf_id);

/** \brief API to enable/disable global circular buffer mode of operations
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] cbuf_enable Circular buffering mode enable / disable flag - use
 *            OCMC_BUF_DISABLE to disable, OCMC_BUF_ENABLE to enable
 * \returns   None
 */
void OCMCCbufModeEnableCtrl(uint32_t baseAddr, uint8_t cbuf_enable);

/** \brief API to reset a specified CBUF
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id to be reset
 * \returns None
 */
void OCMCCBufReset(uint32_t baseAddr, ocmc_buf_id_t buf_id);

/** \brief API to enable/disable int16_t frame detect, and also specify prev_eof
 * selection
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] int16_t_frame_detect Boolean flag to enable/disable int16_t frame
 *            detection
 * \param[in] prev_eof_sel Boolean flag to specify prev_eof history
 * \returns   None
 */
void OCMCShortFrameDetectEnableCtrl(uint32_t baseAddr,
                                    uint8_t  short_frame_detect,
                                    uint8_t  prev_eof_sel);

/** \brief API to configure overflow handling
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] overflow_detect Boolean flag to enable/disable overflow detection
 * \param[in] overflow_handler Specify write overflow handler type once an
 *            overflow has occurred
 * \param[in] overflow_check_reenable Specify when the write overflow check is
 *            to be re-enabled following an overflow
 * \returns   None
 */
void OCMCOverflowConfigure(uint32_t baseAddr, uint8_t overflow_detect,
                           ocmc_wr_overflow_handler_t overflow_handler,
                           ocmc_wr_overflow_reenable_t overflow_check_reenable);

/** \brief API to configure underflow handling
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] underflow_detect Boolean flag to enable/disable underflow
 *            detection
 * \param[in] underflow_last_cbuf_slice_disable Specify if underflow check is on
 *            at last cbuf slice
 * \returns   None
 */
void OCMCUnderflowConfigure(uint32_t baseAddr, uint8_t underflow_detect,
                            uint8_t underflow_last_cbuf_slice_disable);

/** \brief API to get cbuf error status for the buffer id passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] cbuf_err_type  Cbuf error type defined by enum ocmc_cbuf_err_t
 * \param[in] cBufId circular buffer id (cBufId = 0 to 11 for circular buffers 1
 *            to 12)
 * \returns   cbuf error status for the buffer id passed
 */
uint32_t OCMCCbufErrorStatusGet(uint32_t        baseAddr,
                                ocmc_cbuf_err_t cbuf_err_type,
                                uint32_t        cBufId);

/** \brief API to clear cbuf error status for the buffer id passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] cbuf_err_type  Cbuf error type defined by enum ocmc_cbuf_err_t
 * \param[in] cBufId circular buffer id (cBufId = 0 to 11 for circular buffers 1
 *            to 12)
 * \returns   None
 */
void OCMCCbufErrorStatusClear(uint32_t baseAddr, ocmc_cbuf_err_t cbuf_err_type,
                              uint32_t cBufId);

/** \brief API to read a CBUF's "last read address"
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id whose "last read address" is to be read
 *
 * \returns Address of the last read on this CBUF
 */
uint32_t OCMCCBufLastRdAddrGet(uint32_t baseAddr, ocmc_buf_id_t buf_id);

/** \brief API to read a CBUF's "last write address"
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id whose "last write address" is to be read
 *
 * \returns Address of the last write on this CBUF
 */
uint32_t OCMCCBufLastWrAddrGet(uint32_t baseAddr, ocmc_buf_id_t buf_id);

/** \brief API returns the OCMC physical memory base address.
 * \param[in] baseAddr OCMC Instance baseAddr
 *
 * \returns OCMC physical memory base address.
 */
uint32_t OCMCBaseAddrGet(uint32_t baseAddr);

/** \brief API returns the OCMC cbuf base address.
 * \param[in] baseAddr OCMC Instance baseAddr
 *
 * \returns OCMC cbuf base address
 */
uint32_t OCMCCBUFBaseAddrGet(uint32_t baseAddr);

/** \brief API returns OCMC cbuf size
 * \param[in] baseAddr OCMC Instance baseAddr
 *
 * \returns OCMC cbuf size
 */
uint32_t OCMCCBUFSizeGet(uint32_t baseAddr);

/** \brief API Returns OCMC offset address of ECC error for the error type
 *         passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] errType errtype as define in enum ocmc_ecc_err_t
 *
 * \return OCMC offset address of ECC error for the error type passed
 */
uint32_t OCMCEccErrTraceAddrGet(uint32_t baseAddr, ocmc_ecc_err_t errType);

/** \brief API Returns OCMC SEC data error bit distribution status for the SEC
 *         ECC error Distribution Type passed
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] errType errtype as define in enum ocmc_ecc_err_t
 *
 * \return OCMC SEC data error bit distribution status for the SEC ECC error
 *         Distribution Type passed
 */
uint32_t OCMCSecEccErrDistributionStatusGet(uint32_t                baseAddr,
                                            ocmc_sec_ecc_err_dist_t errType);

#ifdef __cplusplus
}
#endif

#endif

