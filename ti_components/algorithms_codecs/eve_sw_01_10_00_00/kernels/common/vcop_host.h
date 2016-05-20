/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_host.h                                                  */
/*                                                                          */
/*     @brief : This file contains macros required for adding host          */
/*     emulation support with minimal changes to existing test codes.       */
/*     Basically, this file defines the macros from vcop.h that will be     */
/*     called when the kernel init and vloops functions are called          */
/*     separately by a user.                                                */
/*                                                                          */
/*     Currently the vcop.h files doesn't define these functions in         */
/*     VCOP_HOST_EMULATION mode. This file is just a placeholder till this  */
/*     is included into vcop.h provided by the ARP32 compiler.              */
/*                                                                          */
/*  @version 1.0 (Sept 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_HOST_H
#define _VCOP_HOST_H  1

#if VCOP_HOST_EMULATION || VCOP_7X_TRANSLATION

#define VCOP_SET_MEM_VIEW(VIEW)
#define ALIAS_128K_VIEW (0)
#define ibufla ((void*) 0x40050000)
#define ibufha ((void*) 0x40054000)
#define ibuflb ((void*) 0x40070000)
#define ibufhb ((void*) 0x40074000)
#define wbuf   ((void*) 0x40044000)
#define BUF_PING (0)
#define BUF_PONG (0)
#define WBUF_SYST (0)
#define IBUFHB_SYST (0)
#define IBUFLB_SYST (0)
#define IBUFHA_SYST (0)
#define IBUFLA_SYST (0)
#define VCOP_BUF_SWITCH_SET(w, hb, lb, ha, la)
#define VCOP_BUF_SWITCH_TOGGLE(f) f
#define VCOP_READ_BUF_SWITCH() (1)
#define VCOP_WRITE_BUF_SWITCH(v)
#define VCOP_WRITE_BUF_SWITCH_REG(v)
#define _vcop_vloop_done()

#endif

#endif /* _VCOP_HOST_H */
