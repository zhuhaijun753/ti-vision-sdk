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

#ifndef BL_RPRC_H_
#define BL_RPRC_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

typedef struct rprcFileHeader {
    uint32_t magic;
    uint32_t entry;
    uint32_t rsvd_addr;
    uint32_t SectionCount;
    uint32_t version;
} rprcFileHeader;

typedef struct rprcSectionHeader {
    uint32_t addr;
    uint32_t rsvd_addr;
    uint32_t size;
    uint32_t rsvdCrc;
    uint32_t rsvd;
} rprcSectionHeader;

#define MAX_INPUT_FILES 10
#define META_HDR_MAGIC_STR 0x5254534D /* MSTR in ascii */
#define META_HDR_MAGIC_END 0x444E454D /* MEND in ascii */

#define OFFSET_SI 0

typedef struct meta_header_start {
    uint32_t magic_str;
    uint32_t num_files;
    uint32_t dev_id;
    uint32_t rsvd;
} meta_header_start;

typedef struct meta_header_core {
    uint32_t core_id;
    uint32_t image_offset;
} meta_header_core;

typedef struct meta_header_end {
    uint32_t rsvd;
    uint32_t magic_string_end;
} meta_header_end;

#define E_PASS       (0)
#define E_FAIL       (-1)

/* Core Id Enum Definition */
#define CORE_A8      0
#define CORE_DSP     1
#define CORE_M3VIDEO 2
#define CORE_M3VPSS  3
#define CORE_ARP32   4

/* Magic number and tokens for RPRC format */
#define RPRC_MAGIC_NUMBER   0x43525052
#define RPRC_RESOURCE       0
#define RPRC_BOOTADDR       5

// Ducati - Warm Reset Clk register
#define DUCATI_BASE_ADDR                  (0x55020000)

int32_t MulticoreImageParse(void *srcAddr, uint32_t ImageOffset);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* BL_RPRC_H_ */
