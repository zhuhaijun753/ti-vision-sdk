/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _CONFIGPARSER_H_
#define _CONFIGPARSER_H_

#define MAX_ITEMS_TO_PARSE (512)

typedef enum
{
  STRING   = 0,
  INT_8    = 1,
  INT_16   = 2,
  INT_32   = 3,
  FLOAT    = 4

}einfoType ;
typedef char infoType_t ;

typedef enum
{
  SINGLE   = 0,
  MULTI    = 1

}eValueCategory ;

typedef char valueCategory_t ;


 /**
 *******************************************************************************
 *  @struct sTokenMapping
 *  @brief  Token Mapping structure for parsing codec specific configuration file
 *
 *  @param  tokenName : Name of the parameter in config file exposed to user
 *  @param  place : Place holder for the data
 *  @param  type : Variable to specify whether the parameter is string or number
 *                 With the help of this parser function will use either memcpy
 *                 or fscanf fucntions
 *
 *******************************************************************************
*/



typedef struct {
  char           *tokenName;
  void           *place;
  infoType_t      type;
  valueCategory_t valCat ;
} sTokenMapping;


int readparamfile(char *configFile, sTokenMapping *sTokenMap);

#endif //_CONFIGPARSER_H
