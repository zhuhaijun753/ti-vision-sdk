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
*   Component:				SBL_TOOLS
*    
*   Filename:				 tiimage.c
*    
*   Description:			Add tiimage header on the input bin file. ROM bootloader check for tiimage header to boot the next stage application
							
*/ 

/****************************************************************
*  INCLUDE FILES                                                 
****************************************************************/
#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ============================================================================
* GLOBAL VARIABLES DECLARATIONS
* =============================================================================
*/

/* ============================================================================
* LOCAL VARIABLES DECLARATIONS
* =============================================================================
*/
typedef struct _ti_header_
{
    uint32_t image_size;
    uint32_t load_addr;
}ti_header;

/* ============================================================================
* LOCAL FUNCTIONS PROTOTYPES
* =============================================================================
*/
static uint32_t tiimage_swap32(uint32_t data);


/* ============================================================================
* FUNCTIONS
* =============================================================================
*/
static uint32_t tiimage_swap32(uint32_t data)
{
    uint32_t result = 0;

    result  = (data & 0xFF000000) >> 24;
    result |= (data & 0x00FF0000) >> 8;
    result |= (data & 0x0000FF00) << 8;
    result |= (data & 0x000000FF) << 24;
   
    return result;
}

int32_t main (int32_t argc, char *argv[])
{
    FILE *in_fp, *out_fp;
    int32_t image_size = 0;
    ti_header    hdr;
    int32_t i = 0, len;
    char *boot; 

    if (argc < 5)
    {
        /* expect : tiimage </path/to/boot.bin> <path/to/place/modified/boot.bin> */
        printf("Usage : \n");
        printf("tiimage takes the input image and adds the TI Image Header \n");
        printf("The resulting output is placed in the output image path\n");
        printf("Syntax: ./<executable file name> <load address> <ENDIANESS> <input image path/name> <output image path/name>\n");
		printf("ENDIAN: BE/LE --> specifies whether TI header is in Big or Little Endian format\n");
        return -1;
    }

    in_fp = fopen(argv[3], "rb");
    if(!in_fp) {
        printf("Error opening input image file!\n");
        return -1;
    }

    out_fp = fopen(argv[4], "wb+");
    if(!out_fp) {
        printf("Error opening/creating out image file!\n");
        return -1;
    }

    /* Calcualte the size of the input image and rewind to the begin of file */
    fseek(in_fp, 0, SEEK_END);
    image_size = ftell(in_fp);
    rewind(in_fp);

    /* Size of  new image is actual bin image size + header */
    hdr.image_size = image_size + sizeof(hdr);
    hdr.load_addr = strtoul(argv[1], NULL, 0);
  
    if(0 == strcmp(argv[2], "BE"))
    { 
        hdr.image_size = tiimage_swap32(hdr.image_size);
        hdr.load_addr = tiimage_swap32(hdr.load_addr);
    }

    /* Insert the header first */
    fwrite(&hdr, sizeof(hdr), 1, out_fp);

    /* Insert the actual image */
    for (i = 0; i < (image_size / 4); i++) {
        uint32_t temp;
        fread(&temp, sizeof(temp), 1, in_fp);

        if(0 == strcmp(argv[2], "BE"))
        {  
            temp = tiimage_swap32(temp);
        }

        fwrite(&temp, sizeof(temp), 1, out_fp);
    }

    printf("\n");

    return 0;
}
