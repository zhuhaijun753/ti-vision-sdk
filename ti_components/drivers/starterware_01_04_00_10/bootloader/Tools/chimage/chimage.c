/**
 *  \file     chimage.c
 *
 *  \brief    This file contains the code that will add Configuration Header(CH)
 *            for QSPI 4 boot mode and create ch image.
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

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
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t main(int32_t argc, char *argv[])
{
    FILE    *inFp1, *inFp2, *outFp;
    int32_t  chbinSize = 0, tiimageSize = 0, i;
    uint32_t temp;

    if (argc < 3)
    {
        /* Expected usage */
        printf("Usage: \n");
        printf("chimage takes CH bin and QSPI4 tiimage as input \n");
        printf("The output is placed in the output image path \n");
        printf(
            "Syntax: ./<executable file name> <CH bin> <QSPI4 tiimage> <output image path/name>\n");
    }
    else
    {
        inFp1 = fopen(argv[1], "rb");
        if (!inFp1)
        {
            printf("Error opening CH bin file!\n");
        }

        inFp2 = fopen(argv[2], "rb");
        if (!inFp2)
        {
            printf("Error opening QSPI4 tiimage file!\n");
        }

        outFp = fopen(argv[3], "wb+");
        if (!outFp)
        {
            printf("Error opening/creating out chimage file!\n");
        }

        /* Calculate the size of the CH bin and rewind to the begin of file */
        fseek(inFp1, 0, SEEK_END);
        chbinSize = ftell(inFp1);
        rewind(inFp1);

        /* Calculate the size of the tiimage and rewind to the begin of file */
        fseek(inFp2, 0, SEEK_END);
        tiimageSize = ftell(inFp2);
        rewind(inFp2);

        /* Insert the CH bin first */
        for (i = 0; i < (chbinSize / 4); i++)
        {
            fread(&temp, sizeof (temp), 1, inFp1);
            fwrite(&temp, sizeof (temp), 1, outFp);
        }

        /* Insert tiimage */
        for (i = 0; i < (tiimageSize / 4); i++)
        {
            fread(&temp, sizeof (temp), 1, inFp2);
            fwrite(&temp, sizeof (temp), 1, outFp);
        }
    }

    printf("\n");
    return (0);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

