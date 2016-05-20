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

#ifndef SAMPLE_H_
#define SAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

int32_t intrC66x[] = {32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
                      43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
                      54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
                      65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
                      76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
                      87, 88, 89, 90, 91, 92, 93, 94, 95};

int32_t intrM4[] = {23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
                    34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
                    45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
                    56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66,
                    67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
                    78, 79};

/*
** Crossbar Instance 5 does not allow crossbar input,
** instance 132 and 133 are not connected to INTC;
** therefore these three instances cannot be used
*/
int32_t intrA15[] = {4,   7,   8,   9,   -1,  11,  12,  13,  14,  15,  16, 17,
                     18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,
                     29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
                     40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,
                     51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,
                     62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,
                     73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,
                     84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,
                     95,  96,  97,  98,  99,  100, 101, 102, 103, 104,
                     105, 106, 107, 108, 109, 110, 111, 112, 113,
                     114, 115, 116, 117, 118, 119, 120, 121, 122,
                     123, 124, 125, 126, 127, 128, 129, 130, 133,
                     134, 135, 136, 137, 138, -1,  -1,  141, 142,
                     143, 144, 145, 146, 147, 148, 149, 150, 151,
                     152, 153, 154, 155, 156, 157, 158, 159};

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* SAMPLE_H_ */
