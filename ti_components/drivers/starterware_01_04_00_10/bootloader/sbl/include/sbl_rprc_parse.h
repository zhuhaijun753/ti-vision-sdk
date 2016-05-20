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
 *   Component:         SBL
 *
 *   Filename:              sbl_rprc_parse.h
 *
 *   Description:           This file contains functions to parse the multi-core
 *                          image file & loads into CPU internal memory &
 *                          external memory.
 */
#ifndef SBL_RPRC_PARSE_H_
#define SBL_RPRC_PARSE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include "hw_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define E_PASS                (0)
#define E_FAIL                (-1)

/* Magic numbers for gforge and sourceforge */
#define MAGIC_NUM_GF          (0xA1ACED00)
#define MAGIC_NUM_SF          (0x55424CBB)

/* Magic number and tokens for RPRC format */
#define RPRC_MAGIC_NUMBER   0x43525052
#define RPRC_RESOURCE       0
#define RPRC_BOOTADDR       5

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct rprcFileHeader {
    uint32_t magic;
    uint32_t entry;
    uint32_t rsvd_addr;
    uint32_t SectionCount;
    uint32_t version;
} rprcFileHeader_t;

typedef struct rprcSectionHeader {
    uint32_t addr;
    uint32_t rsvd_addr;
    uint32_t size;
    uint32_t rsvdCrc;
    uint32_t rsvd;
} rprcSectionHeader_t;

#define MAX_INPUT_FILES 10
#define META_HDR_MAGIC_STR 0x5254534D /* MSTR in ascii */
#define META_HDR_MAGIC_END 0x444E454D /* MEND in ascii */

typedef struct meta_header_start
{
    uint32_t magic_str;
    uint32_t num_files;
    uint32_t dev_id;
    uint32_t rsvd;
}meta_header_start_t;
typedef struct meta_header_core
{
    uint32_t core_id;
    uint32_t image_offset;
}meta_header_core_t;
typedef struct meta_header_end
{
    uint32_t rsvd;
    uint32_t magic_string_end;
}meta_header_end_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern void BootAbort(void);
extern void Entry(void);

#if defined (MMCSD)
int32_t MMCSDBootRprc(void);
#elif defined (NOR)
int32_t NORBootRprc(void);
#elif defined (QSPI)
int32_t QSPIBootRprc(void);
#elif defined (ZEBU_DDR3)
int32_t DDR3BootRprc(void);
#elif defined (SBL_REGRESSION)
int32_t MMCSDBootRprc_Regression(void);
#else
#error Unsupported boot mode !!
#endif

#ifdef __cplusplus
}
#endif

#endif /*SBL_RPRC_PARSE_H_*/

