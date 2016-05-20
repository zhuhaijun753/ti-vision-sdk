/*==========================================================================*/
/*      Copyright (C) 2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/**
*  @file       eve_platform.h
*
*  @brief      Contains platform specific parameters
*
*
*/
#ifndef EVE_PLATFORM_H
#define EVE_PLATFORM_H

#ifdef VAYU_PLATFORM
#define EVE1__MAILBOX (EVE1__MLB0)
#define MBOX_DSP_USER_ID  (MBOX_USER_1)

#ifndef MAILBOX
  #define MAILBOX    (MLB0)
#endif
#endif /* VAYU_PLATFORM */

#ifdef VME_PLATFORM
#define EVE1__MAILBOX (EVE1__MAILBOX)
#define MBOX_DSP_USER_ID (MBOX_USER_2)
#endif /* VME_PLATFORM */


#endif /*EVE_PLATFORM_H*/

