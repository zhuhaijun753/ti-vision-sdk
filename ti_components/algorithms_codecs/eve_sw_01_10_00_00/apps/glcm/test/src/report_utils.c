/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       report_utils.cpp
 *
 *  @brief      This is a temperary file. After migrating all the test
 benches to adopting to code size reporting method, functions in the
 file can be moved to generic file
 *  @version 0.0 (Sep 2014) : Base version.
 */

#include <stdio.h>
#include <stdint.h>
#define TEST_PRINTF printf
#if !(VCOP_HOST_EMULATION)
extern uint32_t  _bam_text_size;
extern uint32_t  _bam_neardata_size;
extern uint32_t  _bam_fardata_size;
extern uint32_t  _algo_fardata_size;
extern uint32_t  _algo_neardata_size;
extern uint32_t  _algo_text_size;
extern uint32_t  _starterware_fardata_size;
extern uint32_t  _starterware_neardata_size;
extern uint32_t  _starterware_text_size;
extern uint32_t  _rts_fardata_size;
extern uint32_t  _rts_neardata_size;
extern uint32_t  _rts_text_size;

extern uint32_t  _text_size;
#endif


void report_printAppletInfo(int8_t * name)
{
  TEST_PRINTF("\n\nTEST_REPORT_APPLET_NAME : %s Test application\n",name);
#if !(VCOP_HOST_EMULATION)
    TEST_PRINTF("\nTEST_REPORT_TEXT_CONST : \n ");

    TEST_PRINTF("\n%-28s %25s %20s %20s  %s", \
            "Module", "Far data (DDR)", "Near data DMEM", "Program(.text)", "Comments");
    TEST_PRINTF("\n%-28s %25d %20d %20d  %s", name, &_algo_fardata_size, &_algo_neardata_size,  &_algo_text_size, "");
    TEST_PRINTF("\n%-28s %25d %20d %20d  %s", "BAM", &_bam_fardata_size, &_bam_neardata_size,  &_bam_text_size, "");
    TEST_PRINTF("\n%-28s %25d %20d %20d  %s", "Starterware", &_starterware_fardata_size, &_starterware_neardata_size,  &_starterware_text_size,"");
    TEST_PRINTF("\n%-28s %25d %20d %20d  %s\n", "rtsarp32_v200.lib", &_rts_fardata_size, &_rts_neardata_size,  &_rts_text_size,"");
#endif
}
