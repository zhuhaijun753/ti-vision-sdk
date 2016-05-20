/*****************************************************************************
*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
*
*   Property of Texas Instruments
*   For  Unrestricted  Internal  Use  Only
*   Unauthorized reproduction and/or distribution is strictly prohibited.
*   This product is protected under copyright law and trade secret law
*   as an unpublished work.
*   Created 2003, (C) Copyright 2003 Texas Instruments.  All rights reserved.
*
*
*
*   File content:        C Header file
*
*   Filename:            INTCTL.c
*
*   Description:         Copied from /cdb/libComap4/IP/src/INTCTL.c and then modified
*                        INTCTL library function configures the MPU interrupt handler
*                        with basic functions like routing (to fiq or irq) ,enabling ,
*                        prioritizing, masking each interrupt.
*
*   Module name:         INTCTL
*
*   Module version:      1.1
*
*****************************************************************************/
/*****************************************************************************
* INCLUDE FILES
******************************************************************************
*/

#include "GlobalTypes.h"
#include "cram.h"
#pragma CHECK_MISRA ("none")
#include "baseaddress.h"
#include "eve_control_cred.h"
#pragma RESET_MISRA ("required")
#include "INTCTL.h"

/*
****************************************************************************
* GLOBAL VARIABLES DECLARATIONS
******************************************************************************
*/
#ifdef VAYU_PLATFORM
#define INTCTL_INT_TABLE_SIZE     128U
#define INTCTL_PRIORITY_MAX     (INTCTL_INT15)
#endif

#ifdef VME_PLATFORM
#define INTCTL_INT_TABLE_SIZE     32U
#define INTCTL_PRIORITY_MAX     (INTCTL_INT7)
#endif


UWORD32 currentInterruptNumber = 0U;
#pragma DATA_SECTION(intctl_IrqPriority, ".dmem_int_sec")
static UWORD8 intctl_IrqPriority[INTCTL_INT_TABLE_SIZE];


/*
****************************************************************************
* LOCAL TYPES AND DEFINITIONS
******************************************************************************
*/

/*
*****************************************************************************
* LOCAL VARIABLES DECLARATIONS
******************************************************************************
*/

/*
****************************************************************************
* LOCAL FUNCTIONS PROTOTYPES
******************************************************************************
*/

/*
****************************************************************************
* FUNCTIONS
******************************************************************************
*/
/*
****************************************************************************
* INTCTLInitLevel
*****************************************************************************
*/

ReturnCode_t EVE_INTCTL_LevelInit (const UWORD32                 baseAddress,
                               const UWORD8                  itNumber,
                               const INTCTL_InterruptKind_t  interruptKind,
                               const INTCTL_Priority_t       priority)
{
    ReturnCode_t returnCode = RET_OK;
    if(itNumber > INTCTL_INT_TABLE_SIZE) {
      returnCode = RET_FAIL;
    }

    if (priority > INTCTL_PRIORITY_MAX) {
      returnCode = RET_FAIL;
    }

    if((itNumber < 32U) && (priority < INTCTL_INT8)) {
      switch ( priority ) {
        case INTCTL_NMI:
          intctl_IrqPriority[itNumber] = INTCTL_NMI;
          break;
        case INTCTL_INT4:
          intctl_IrqPriority[itNumber] = INTCTL_INT4;
          break;
        case INTCTL_INT5:
          intctl_IrqPriority[itNumber] = INTCTL_INT5;
          break;
        case INTCTL_INT6:
          intctl_IrqPriority[itNumber] = INTCTL_INT6;
          break;
        case INTCTL_INT7:
          intctl_IrqPriority[itNumber] = INTCTL_INT7;
          break;
        default:
          break;
      }
    }
#ifdef VAYU_PLATFORM
    else if(((itNumber >= 32U) && (itNumber < 64U)) && ((priority >= INTCTL_INT8) && (priority < INTCTL_INT12))) {
      switch ( priority ) {
        case INTCTL_INT8:
          intctl_IrqPriority[itNumber] = INTCTL_INT8;
          break;
        case INTCTL_INT9:
          intctl_IrqPriority[itNumber] = INTCTL_INT9;
          break;
        case INTCTL_INT10:
          intctl_IrqPriority[itNumber] = INTCTL_INT10;
          break;
        case INTCTL_INT11:
          intctl_IrqPriority[itNumber] = INTCTL_INT11;
          break;
        default:
          break;
      }
    }
    else if(((itNumber >= 64U) && (itNumber < 96U)) && ((priority >= INTCTL_INT12) && (priority < INTCTL_INT14))) {
      switch ( priority ) {
        case INTCTL_INT12:
          intctl_IrqPriority[itNumber] = INTCTL_INT12;
          break;
        case INTCTL_INT13:
          intctl_IrqPriority[itNumber] = INTCTL_INT13;
          break;
        default:
          break;
      }
    }
    else if(((itNumber >= 96U) && (itNumber < 128U)) && ((priority >= INTCTL_INT14) && (priority <= INTCTL_INT15))) {
      switch ( priority ) {
        case INTCTL_INT14:
          intctl_IrqPriority[itNumber] = INTCTL_INT14;
          break;
        case INTCTL_INT15:
          intctl_IrqPriority[itNumber] = INTCTL_INT15;
          break;
        default:
          break;
      }
    }
#endif
    else {
      returnCode = RET_FAIL;
    }

    return(returnCode);
}/*EVE_INTCTL_LevelInit()*/


/*
*****************************************************************************
* INTCTLEnableOneIT
*****************************************************************************
*/

ReturnCode_t EVE_INTCTL_OneITEnable(const UWORD32            baseAddress,
                                const UWORD8             itNumber,
                                const INTCTL_Enable_t    enableNdisable)
{
    ReturnCode_t returnCode = RET_OK;
    UWORD8 checkPriority;

    checkPriority = intctl_IrqPriority[itNumber];

    if(checkPriority == INTCTL_NMI) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_nmi_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_NMI_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_nmi_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_NMI_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT4) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int4_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT4_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_int4_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT4_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT5) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int5_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT5_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_int5_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT5_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT6) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int6_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT6_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_int6_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT6_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT7) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int7_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT7_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_int7_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT7_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
#ifdef VAYU_PLATFORM
    if(checkPriority == INTCTL_INT8) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int8_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT8_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int8_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT8_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT9) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int9_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT9_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int9_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT9_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT10) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int10_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT10_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int10_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT10_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT11) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int11_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT11_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int11_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT11_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT12) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int12_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT12_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 64U));
      }
      else {
        /*write_int12_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT12_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 64U));
      }
    }
    if(checkPriority == INTCTL_INT13) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int13_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT13_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 64U));
      }
      else {
        /*write_int13_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT13_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 64U));
      }
    }
    if(checkPriority == INTCTL_INT14) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int14_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT14_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 96U));
      }
      else {
        /*write_int14_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT14_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 96U));
      }
    }
    if(checkPriority == INTCTL_INT15) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int15_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT15_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 96U));
      }
      else {
        /*write_int15_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT15_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 96U));
      }
    }
#endif
    return (returnCode);
}/*INTCTLEnableOneIT()*/

ReturnCode_t EVE_INTCTL_Ack(const UWORD32                   baseAddress,
                        const INTCTL_Priority_t         interruptPriority,
                        UWORD16 *const                  interruptNumber)
{
    UWORD32 status_reg;
    UWORD32 i;

    switch(interruptPriority) {
      case INTCTL_NMI:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_NMI_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = i;
            break;
          }
        }
        break;
      case INTCTL_INT4:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT4_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = i;
            break;
          }
        }
        break;
      case INTCTL_INT5:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT5_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = i;
            break;
          }
        }
        break;
      case INTCTL_INT6:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT6_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = i;
            break;
          }
        }
        break;
      case INTCTL_INT7:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT7_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = i;
            break;
          }
        }
        break;
#ifdef VAYU_PLATFORM
      case INTCTL_INT8:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT8_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT9:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT9_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT10:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT10_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT11:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT11_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT12:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT12_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (i + 64U);
            break;
          }
        }
        break;
      case INTCTL_INT13:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT13_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (i + 64U);
            break;
          }
        }
        break;
      case INTCTL_INT14:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT14_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (i + 96U);
            break;
          }
        }
        break;
      case INTCTL_INT15:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT15_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (i + 96U);
            break;
          }
        }
        break;
#endif
      default:
        break;
    }
    return(RET_OK);
}/*EVE_INTCTL_Ack()*/

/*
*****************************************************************************
* EVE_INTCTL_NextValid
*****************************************************************************
*/
ReturnCode_t EVE_INTCTL_NextValid(const UWORD32                   baseAddress,
                              const INTCTL_Priority_t         interruptPriority)
{
    switch(interruptPriority) {
      case INTCTL_NMI:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_NMI_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT4:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT4_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT5:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT5_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT6:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT6_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT7:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT7_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
#ifdef VAYU_PLATFORM
      case INTCTL_INT8:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT8_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT9:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT9_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT10:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT10_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT11:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT11_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT12:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT12_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT13:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT13_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT14:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT14_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT15:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT15_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
#endif
      default:
        break;
    }

  return ( RET_OK );

}/*EVE_INTCTL_NextValid()*/
