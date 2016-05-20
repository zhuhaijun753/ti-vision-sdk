/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _REMAP_TEST_PRINT_H
#define _REMAP_TEST_PRINT_H

#include <stdint.h>

void testPrintHeader(char *title);
void testPrintResults(int32_t errorFlag, uint64_t setupTimerDiff, uint32_t execGraphCycles,
                          uint64_t execTotalTimerDiff, uint64_t execVcopTimerDiff, char *desc, uint32_t size);
void testPrintFooter(char *title);


#endif /* _REMAP_TEST_PRINT_H */
