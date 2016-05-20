/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2015 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "remapExecute_config.h"
#pragma RESET_MISRA ("required")

uint32_t remapExecute_numTestCases;

sremapExecute_Config gConfig_remapExecute[EVELIB_REMAPEXECUTE_NUM_TESTCASES];

sTokenMapping gsTokenMap_remapExecute[] =
{
        {(char* )"numTestCases",          &remapExecute_numTestCases                , INT_32, SINGLE},
        {(char* )"convertedBinMapFile",   &gConfig_remapExecute[0].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile",       &gConfig_remapExecute[0].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth",            &gConfig_remapExecute[0].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight",           &gConfig_remapExecute[0].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth",            &gConfig_remapExecute[0].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight",           &gConfig_remapExecute[0].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat",           &gConfig_remapExecute[0].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile",             &gConfig_remapExecute[0].inputFile        , STRING, SINGLE},
        {(char* )"outputFile",            &gConfig_remapExecute[0].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile0",          &gConfig_remapExecute[0].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile0",       &gConfig_remapExecute[0].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth0",            &gConfig_remapExecute[0].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight0",           &gConfig_remapExecute[0].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth0",            &gConfig_remapExecute[0].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight0",           &gConfig_remapExecute[0].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat0",           &gConfig_remapExecute[0].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile0",          &gConfig_remapExecute[0].inputFile        , STRING, SINGLE},
        {(char* )"outputFile0",         &gConfig_remapExecute[0].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile1",          &gConfig_remapExecute[1].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile1",       &gConfig_remapExecute[1].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth1",            &gConfig_remapExecute[1].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight1",           &gConfig_remapExecute[1].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth1",            &gConfig_remapExecute[1].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight1",           &gConfig_remapExecute[1].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat1",           &gConfig_remapExecute[1].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile1",          &gConfig_remapExecute[1].inputFile        , STRING, SINGLE},
        {(char* )"outputFile1",         &gConfig_remapExecute[1].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile2",          &gConfig_remapExecute[2].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile2",       &gConfig_remapExecute[2].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth2",            &gConfig_remapExecute[2].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight2",           &gConfig_remapExecute[2].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth2",            &gConfig_remapExecute[2].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight2",           &gConfig_remapExecute[2].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat2",           &gConfig_remapExecute[2].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile2",          &gConfig_remapExecute[2].inputFile        , STRING, SINGLE},
        {(char* )"outputFile2",         &gConfig_remapExecute[2].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile3",          &gConfig_remapExecute[3].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile3",       &gConfig_remapExecute[3].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth3",            &gConfig_remapExecute[3].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight3",           &gConfig_remapExecute[3].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth3",            &gConfig_remapExecute[3].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight3",           &gConfig_remapExecute[3].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat3",           &gConfig_remapExecute[3].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile3",          &gConfig_remapExecute[3].inputFile        , STRING, SINGLE},
        {(char* )"outputFile3",         &gConfig_remapExecute[3].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile4",          &gConfig_remapExecute[4].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile4",       &gConfig_remapExecute[4].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth4",            &gConfig_remapExecute[4].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight4",           &gConfig_remapExecute[4].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth4",            &gConfig_remapExecute[4].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeigh4",           &gConfig_remapExecute[4].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat4",           &gConfig_remapExecute[4].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile4",          &gConfig_remapExecute[4].inputFile        , STRING, SINGLE},
        {(char* )"outputFile4",         &gConfig_remapExecute[4].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile5",          &gConfig_remapExecute[5].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile5",       &gConfig_remapExecute[5].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth5",            &gConfig_remapExecute[5].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight5",           &gConfig_remapExecute[5].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth5",            &gConfig_remapExecute[5].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight5",           &gConfig_remapExecute[5].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat5",           &gConfig_remapExecute[5].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile5",          &gConfig_remapExecute[5].inputFile        , STRING, SINGLE},
        {(char* )"outputFile5",         &gConfig_remapExecute[5].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile6",          &gConfig_remapExecute[6].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile6",       &gConfig_remapExecute[6].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth6",            &gConfig_remapExecute[6].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight6",           &gConfig_remapExecute[6].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth6",            &gConfig_remapExecute[6].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight6",           &gConfig_remapExecute[6].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat6",           &gConfig_remapExecute[6].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile6",          &gConfig_remapExecute[6].inputFile        , STRING, SINGLE},
        {(char* )"outputFile6",         &gConfig_remapExecute[6].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile7",          &gConfig_remapExecute[7].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile7",       &gConfig_remapExecute[7].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth7",            &gConfig_remapExecute[7].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight7",           &gConfig_remapExecute[7].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth7",            &gConfig_remapExecute[7].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight7",           &gConfig_remapExecute[7].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat7",           &gConfig_remapExecute[7].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile7",          &gConfig_remapExecute[7].inputFile        , STRING, SINGLE},
        {(char* )"outputFile7",         &gConfig_remapExecute[7].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile8",          &gConfig_remapExecute[8].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile8",       &gConfig_remapExecute[8].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth8",            &gConfig_remapExecute[8].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight8",           &gConfig_remapExecute[8].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth8",            &gConfig_remapExecute[8].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight8",           &gConfig_remapExecute[8].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat8",           &gConfig_remapExecute[8].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile8",          &gConfig_remapExecute[8].inputFile        , STRING, SINGLE},
        {(char* )"outputFile8",         &gConfig_remapExecute[8].outputFile        , STRING, SINGLE},

        {(char* )"convertedBinMapFile9",          &gConfig_remapExecute[9].convertedBinMapFile     , STRING, SINGLE},
        {(char* )"originalMapFile9",       &gConfig_remapExecute[9].originalMapFile        , STRING, SINGLE},
        {(char* )"remapWidth9",            &gConfig_remapExecute[9].remapWidth       , INT_32, SINGLE},
        {(char* )"remapHeight9",           &gConfig_remapExecute[9].remapHeight      , INT_32, SINGLE},
        {(char* )"inputWidth9",            &gConfig_remapExecute[9].inputWidth       , INT_32, SINGLE},
        {(char* )"inputHeight9",           &gConfig_remapExecute[9].inputHeight      , INT_32, SINGLE},
        {(char* )"colorFormat9",           &gConfig_remapExecute[9].colorFormat      , INT_8, SINGLE},
        {(char* )"inputFile9",          &gConfig_remapExecute[9].inputFile        , STRING, SINGLE},
        {(char* )"outputFile9",         &gConfig_remapExecute[9].outputFile        , STRING, SINGLE},

};
