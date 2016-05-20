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
 * \file  bl_rprc.c
 *
 * \brief Parses application image from SPI flash in RPRC format.
 */

/******************************************************************************
**                     Local function Declaration
*******************************************************************************/

#include "stdint.h"
#include "stdlib.h"
#include "bl_rprc.h"
#include "qspi_flash.h"
#include "uartStdio.h"

void BootCore(uint32_t entry, int32_t CoreID);
static int32_t RprcImageParse(void *srcAddr, uint32_t *entryPoint,
                              int32_t CoreId);
extern uint32_t   entryPoint_modena;
uint32_t          entryPoint;
meta_header_start mHdrStr;
meta_header_core  mHdrCore[MAX_INPUT_FILES];
meta_header_end   mHdrEnd;

/******************************************************************************
**                     External variable Declaration
*******************************************************************************/
uint32_t          (*fp_readData)(void *dstAddr, void *srcAddr,
                                 uint32_t length) = NULL;
void (*fp_seek)(void *srcAddr, uint32_t location) = NULL;

int32_t MulticoreImageParse(void *srcAddr, uint32_t ImageOffset)
{
    uint32_t i;
    int32_t  magic_str = META_HDR_MAGIC_STR;
    int32_t  retVal    = E_PASS;

    if (fp_readData == NULL || fp_seek == NULL)
    {
        return E_FAIL;
    }
    /* Read Meta Header Start and get the Number of Input RPRC Files */
    fp_readData(&mHdrStr, srcAddr, sizeof (meta_header_start));
    if (mHdrStr.magic_str != magic_str)
    {
        UARTPuts("Invalid magic number in Single image header\r\n", -1);
        return E_FAIL;
    }
#if 0
    if (mHdrStr.dev_id != GetDeviceId())
    {
        UARTPuts("WARNING: Device Id Doesnot match\r\n", -1);
    }
#endif
    /* Read all the Core offset addresses */
    for (i = 0; i < mHdrStr.num_files; i++)
    {
        fp_readData(&mHdrCore[i], srcAddr, sizeof (meta_header_core));
    }

    /* Add Base Offset address for All core Image start offset */
    for (i = 0; i < mHdrStr.num_files; i++)
    {
        mHdrCore[i].image_offset += ImageOffset;
    }

    /* Read Meta Header End */
    fp_readData(&mHdrEnd, srcAddr, sizeof (meta_header_end));

    /* Now Parse Individual RPRC files and wake up the perticular core */

    for (i = 0; i < mHdrStr.num_files; i++)
    {
        if (mHdrCore[i].core_id != (0xFFFFFFFF))
        {
            fp_seek(srcAddr, mHdrCore[i].image_offset);
            if (RprcImageParse(srcAddr, &entryPoint,
                               mHdrCore[i].core_id) != E_PASS)
            {
                // Error occurred parsing the RPRC file continue to parsing next
                // image and skip booting the particular core
                retVal = E_FAIL;
            }
            else
            {
                BootCore(entryPoint, mHdrCore[i].core_id);
            }
        }
    }
    return retVal;
}

static int32_t RprcImageParse(void *srcAddr, uint32_t *entryPoint,
                              int32_t CoreId)
{
    rprcFileHeader    header;
    rprcSectionHeader section;
    int32_t           i;
    // read application image header
    fp_readData(&header, srcAddr, sizeof (rprcFileHeader));

    // check magic number
    if (header.magic != RPRC_MAGIC_NUMBER)
    {
        UARTPuts("Invalid magic number in boot image\r\n", -1);
        return (E_FAIL);
    }

    /* Set the Entry Point */
    *entryPoint = header.entry;

    // read entrypoint and copy sections to memory
    for (i = 0; i < header.SectionCount; i++)
    {
        // read new section header
        fp_readData(&section, srcAddr, sizeof (rprcSectionHeader));
        // copy section to memory
        // patch for m3
        if (section.addr < 0x80000000)
        {
            switch (CoreId)
            {
                case CORE_A8:
                    // Coretex A8
                    break;
                case CORE_DSP:
                    // DSP
                    if (section.addr >= 0x00800000 && section.addr <=
                        0x0083FFFF)
                        section.addr = (0x40800000) | (0x7FFFFF & section.addr);
                    break;
                case CORE_M3VIDEO:
                case CORE_M3VPSS:
                    // M3
                    section.addr += DUCATI_BASE_ADDR;
                    break;
                case CORE_ARP32:
                    // ARP32
                    section.addr = (0x59000000) | (0x00FFFFFF & section.addr);
                    break;
            }
        }
        fp_readData((void *) section.addr, srcAddr, section.size);
    }

    return E_PASS;
}

void BootCore(uint32_t entry, int32_t CoreID)
{
    switch (CoreID)
    {
        case CORE_A8:
            // Cortex A8
            entryPoint_modena = entry;
            break;
        case CORE_DSP:
            // DSP
            // entryPoint_DSP = entry;
            // DSP_BringUp();
            break;
        case CORE_M3VIDEO:
            // entryPoint_videoM3 = entry;
            // VideoM3_BringUp();
            break;
        case CORE_M3VPSS:
            // entryPoint_VPSSM3 = entry;
            // VPSSM3_BringUp();
            break;
        case CORE_ARP32:
            // entryPoint_ARP32 = entry;
            // ARP32();
            break;
    }
}

/***************************** End Of File ***********************************/
