/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "remap_test_print.h"

uint16_t getARP32mhz(){

    return 250;
}

uint16_t getVCOPmhz(){

    return 500;

}

static float ratioVcopArp32;
static uint16_t testId;

void testPrintHeader(char *title){

    uint16_t arp32Mhz, vcopMhz;

    printf("               %s testing starts.\n", title);
    printf("               ARP32 freq: %d Mhz  VCOP freq: %d Mhz\n", arp32Mhz=getARP32mhz(), vcopMhz=getVCOPmhz());
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| No | Status |Graph create| Graph init | Graph exec | Total exec | VCOP busy  | Description\n");
    printf("|    |        | ARP cycles | ARP cycles | cyc/point  | cyc/point  | cyc/point  |            \n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");

    testId= 0;
    ratioVcopArp32= (float)vcopMhz/arp32Mhz;
}

#define MAX_LINELEN  60
#define MAX_NUMLINES 5

void testPrintResults(int32_t errorFlag, uint64_t setupTimerDiff, uint32_t execGraphCycles,
                         uint64_t execTotalTimerDiff, uint64_t execVcopTimerDiff, char *desc, uint32_t size){

    uint16_t index, maxIndex;
    char *descString;
    char *curStr;
    char *line[MAX_NUMLINES+1];
    char *emptyString="";

    index= 1;

    if (desc== NULL) {
        descString= emptyString;
        line[0]= descString;
        }
    else {
        descString= desc;
/* Code below is to break up a long description string into multiple lines
   so everything fits nicely in the display.
   The algorithm looks for last space before the line exceeeds
   MAX_LINELEN int8_tacters to determine end of each line
   */
        curStr= descString;
        line[0]= descString;
        index= 1;
        while ((strlen(curStr) > MAX_LINELEN) && (index < MAX_NUMLINES)){
           curStr+= MAX_LINELEN;
           while (*curStr!= ' ' && curStr != descString)
              curStr--;
           if (curStr != descString)
              line[index++]= curStr;
           else
              line[index++]= descString + strlen(descString);
           curStr++;
        }

    }

    maxIndex= index;
    line[index]= descString + strlen(descString);

    index= 0;

    if (errorFlag == 0)
        printf("|%3d | PASS  ", testId++);
    else if (errorFlag == 1)
        printf("|%3d | FAIL  ", testId++);
    else if (errorFlag == 2)
        printf("|%3d | NO REF", testId++);

    *(line[index+1])= 0; // we set the end of line to '0'

    printf(" |%8lld    |%8lld    | %6.2f     | %6.2f     | %6.2f     | %s\n",
            (setupTimerDiff/(uint64_t)ratioVcopArp32),
            ((execTotalTimerDiff/(uint64_t)ratioVcopArp32) - execGraphCycles),
            (ratioVcopArp32*execGraphCycles)/size,
            ((float)execTotalTimerDiff)/size, ((float)execVcopTimerDiff)/size, line[0]);

    if (index != maxIndex - 1)
       *(line[index+1])= ' '; // we set back the end of line to ' ' if not last line
    index++;
    line[index]++; // advance pointer line[index] by 1 to skip the 0

    while (index != maxIndex) {
     *(line[index+1])= 0;
     printf("|    |        |            |            |            |            |            | %s\n", line[index]);
     if (index != maxIndex - 1)
       *(line[index+1])= ' ';
     index++;
     line[index]++; // advance pointer line[index] by 1 to skip the 0
    }
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
}

void testPrintFooter(char *title){
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("               %s testing ends\n\n", title);
}
