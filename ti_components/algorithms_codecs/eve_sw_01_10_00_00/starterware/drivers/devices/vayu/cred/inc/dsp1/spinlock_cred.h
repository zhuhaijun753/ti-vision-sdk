
/* ============================================================================
 *
 *            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *  Property of Texas Instruments
 *  For Unrestricted Internal Use Only
 *  Unauthorized reproduction and/or distribution is strictly prohibited.
 *  This product is protected under copyright law and trade secret law
 *  as an unpublished work.
 *  Created 2008, (C) Copyright 2008 Texas Instruments.  All rights reserved.
 *
 */

/**
 *  @Component:   SPINLOCK
 *
 *  @Filename:    spinlock_cred.h
 *
 *  @Description: Component description is not available
 *
 *  Generated by: Socrates CRED generator prototype
 *
 *//* ====================================================================== */

#ifndef __SPINLOCK_H
#define __SPINLOCK_H

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Instance SPINLOCK0 of component SPINLOCK mapped in NETRA at address 0x480CA000
 */

 /*-------------------------------------------------------------------------*//**
 * @DEFINITION   BITFIELD
 *
 * @BRIEF        The bitfield must be defined according to register width
 *               of the component - 64/32/16/8
 *
 *//*------------------------------------------------------------------------ */
#define BITFIELD BITFIELD_32

/*
 *  List of Register arrays for component SPINLOCK
 *
 */

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__LOCK_REG
 *
 * @BRIEF        This register is read when attempting to acquire a lock.  
 *               The lock is automatically taken if it was not taken and the 
 *               value returned by the read is zero.  If the lock was already 
 *               taken, then the read returns one. 
 *               Writing a zero to this register frees the lock. 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__LOCK_REG                                 0x800u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__LOCK_REG__ELSIZE
 *
 * @BRIEF        LOCK_REG register array element size in Bytes
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__LOCK_REG__ELSIZE                         0x4u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__LOCK_REG__NELEMS
 *
 * @BRIEF        LOCK_REG register array number of elements
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__LOCK_REG__NELEMS                         32


/*
 *  List of bundle arrays for component SPINLOCK
 *
 */

/*
 *  List of bundles for component SPINLOCK
 *
 */


/*
 * List of registers for component SPINLOCK
 *
 */

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION
 *
 * @BRIEF        Read-only IP revision identifier (X.Y.R) used by software to 
 *               determine features, bugs and compatibility of an instance of 
 *               this the Spin Lock module. 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION                                 0x0u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG
 *
 * @BRIEF        This register controls the various parameters of the OCP 
 *               interface.  Note that several fields are present by 
 *               read-only. 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG                                0x10u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS
 *
 * @BRIEF        This register provides status information about this 
 *               instance of the Spin Lock module. 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS                                 0x14u


/*
 * List of register bitfields for component SPINLOCK
 *
 */
 
/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__SCHEME   
 *
 * @BRIEF        Revision encoding Scheme. - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__SCHEME                    BITFIELD(31, 30)
#define SPINLOCK__REVISION__SCHEME__POS               30

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__RESERVED   
 *
 * @BRIEF        Indicates organization originating this IP: 
 *               0 = DSPS 
 *               1 = WTBU 
 *               2 reserved 
 *               3 reserved - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__RESERVED                  BITFIELD(29, 28)
#define SPINLOCK__REVISION__RESERVED__POS             28

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__FUNC   
 *
 * @BRIEF        Module function.  Indicates a software compatible module 
 *               family. - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__FUNC                      BITFIELD(27, 16)
#define SPINLOCK__REVISION__FUNC__POS                 16

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__R_RTL   
 *
 * @BRIEF        RTL version (R) maintained by the IP design owner. - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__R_RTL                     BITFIELD(15, 11)
#define SPINLOCK__REVISION__R_RTL__POS                11

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__X_MAJOR   
 *
 * @BRIEF        Major revision (X) maintained by the IP specification owner. 
 *               - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__X_MAJOR                   BITFIELD(10, 8)
#define SPINLOCK__REVISION__X_MAJOR__POS              8

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__CUSTOM   
 *
 * @BRIEF        Indicates a special version for a particular device.  0 
 *               indicates a standard (non-custom) device. - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__CUSTOM                    BITFIELD(7, 6)
#define SPINLOCK__REVISION__CUSTOM__POS               6

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__Y_MINOR   
 *
 * @BRIEF        Minor revision (Y) maintained by the IP specification owner. 
 *               - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__Y_MINOR                   BITFIELD(5, 0)
#define SPINLOCK__REVISION__Y_MINOR__POS              0

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__CLOCKACTIVITYOCP   
 *
 * @BRIEF        Indicates whether the module requires the OCP when in IDLE 
 *               mode. - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__CLOCKACTIVITYOCP         BITFIELD(8, 8)
#define SPINLOCK__SYSCONFIG__CLOCKACTIVITYOCP__POS    8

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__SIDLEMODE   
 *
 * @BRIEF        Control of the slave interface power management IDLE request 
 *               acknowledgement. - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__SIDLEMODE                BITFIELD(4, 3)
#define SPINLOCK__SYSCONFIG__SIDLEMODE__POS           3

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__ENWAKEUP   
 *
 * @BRIEF        Asynchronous wakeup gereration. - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__ENWAKEUP                 BITFIELD(2, 2)
#define SPINLOCK__SYSCONFIG__ENWAKEUP__POS            2

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__SOFTRESET   
 *
 * @BRIEF        Module software reset. - (WO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__SOFTRESET                BITFIELD(1, 1)
#define SPINLOCK__SYSCONFIG__SOFTRESET__POS           1

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__AUTOGATING   
 *
 * @BRIEF        Internal OCP clock gating strategy. - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__AUTOGATING               BITFIELD(0, 0)
#define SPINLOCK__SYSCONFIG__AUTOGATING__POS          0

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__NUMLOCKS   
 *
 * @BRIEF        Bitfield description is not available - (RO)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__NUMLOCKS                  BITFIELD(31, 24)
#define SPINLOCK__SYSTATUS__NUMLOCKS__POS             24

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__IU7   
 *
 * @BRIEF        Bitfield description is not available - (RO)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__IU7                       BITFIELD(7, 7)
#define SPINLOCK__SYSTATUS__IU7__POS                  7

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__IU6   
 *
 * @BRIEF        Bitfield description is not available - (RO)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__IU6                       BITFIELD(6, 6)
#define SPINLOCK__SYSTATUS__IU6__POS                  6

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__IU5   
 *
 * @BRIEF        Bitfield description is not available - (RO)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__IU5                       BITFIELD(5, 5)
#define SPINLOCK__SYSTATUS__IU5__POS                  5

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__IU4   
 *
 * @BRIEF        Bitfield description is not available - (RO)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__IU4                       BITFIELD(4, 4)
#define SPINLOCK__SYSTATUS__IU4__POS                  4

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__IU3   
 *
 * @BRIEF        Bitfield description is not available - (RO)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__IU3                       BITFIELD(3, 3)
#define SPINLOCK__SYSTATUS__IU3__POS                  3

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__IU2   
 *
 * @BRIEF        Bitfield description is not available - (RO)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__IU2                       BITFIELD(2, 2)
#define SPINLOCK__SYSTATUS__IU2__POS                  2

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__IU1   
 *
 * @BRIEF        In-Use flag 1, covering lock registers 32 - 63.  Reads as 
 *               one only if one or more lock registers in this range are 
 *               TAKEN. 
 *               If no lock registers are implemented in this range, then 
 *               this flag always reads as 0. - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__IU1                       BITFIELD(1, 1)
#define SPINLOCK__SYSTATUS__IU1__POS                  1

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__IU0   
 *
 * @BRIEF        In-Use flag 0, covering lock registers 0 - 31.  Reads as one 
 *               only if one or more lock registers in this range are TAKEN. 
 *               - (RO) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__IU0                       BITFIELD(0, 0)
#define SPINLOCK__SYSTATUS__IU0__POS                  0

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__LOCK_REG__RESERVED   
 *
 * @BRIEF        Bitfield description is not available - (RO)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__LOCK_REG__RESERVED                  BITFIELD(31, 1)
#define SPINLOCK__LOCK_REG__RESERVED__POS             1

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__LOCK_REG__TAKEN   
 *
 * @BRIEF        Bitfield description is not available - (RW)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__LOCK_REG__TAKEN                     BITFIELD(0, 0)
#define SPINLOCK__LOCK_REG__TAKEN__POS                0


/*
 * List of register bitfields values for component SPINLOCK
 *
 */

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__SCHEME__LEGACY
 *
 * @BRIEF        Legacy ASP or WTBU revision encoding scheme. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__SCHEME__LEGACY            0x0u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__SCHEME__HIGHLANDER
 *
 * @BRIEF        Highlander v0.8 revision encoding scheme. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__SCHEME__HIGHLANDER        0x1u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__RESERVED__DSPS
 *
 * @BRIEF        Originated by DSPS. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__RESERVED__DSPS            0x0u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__RESERVED__WTBU
 *
 * @BRIEF        Originated by WTBU. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__RESERVED__WTBU            0x1u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__RESERVED__RES2
 *
 * @BRIEF        Reserved. Do not use. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__RESERVED__RES2            0x2u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__REVISION__RESERVED__RES3
 *
 * @BRIEF        Reserved. Do not use. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__REVISION__RESERVED__RES3            0x3u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__CLOCKACTIVITYOCP__NOTREQUIRED
 *
 * @BRIEF        OCP clock is not required by the module during IDLE mode and 
 *               may be switched off. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__CLOCKACTIVITYOCP__NOTREQUIRED 0x0u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__CLOCKACTIVITYOCP__REQUIRED
 *
 * @BRIEF        OCP clock is required by the module, even during idle mode. 
 *               - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__CLOCKACTIVITYOCP__REQUIRED 0x1u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__SIDLEMODE__FORCEIDLE
 *
 * @BRIEF        IDLE request is acknowledged unconditionally and 
 *               immediately. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__SIDLEMODE__FORCEIDLE     0x0u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__SIDLEMODE__NOIDLE
 *
 * @BRIEF        IDLE request is never acknowledged. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__SIDLEMODE__NOIDLE        0x1u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__SIDLEMODE__SMARTIDLE
 *
 * @BRIEF        IDLE request acknowledgement is based on the internal module 
 *               activity. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__SIDLEMODE__SMARTIDLE     0x2u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__SIDLEMODE__UNUSED3
 *
 * @BRIEF        Reserved.  Do not use. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__SIDLEMODE__UNUSED3       0x3u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__ENWAKEUP__NOWAKEUPGEN
 *
 * @BRIEF        Wakeup generation is disabled. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__ENWAKEUP__NOWAKEUPGEN    0x0u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__ENWAKEUP__WAKEUPGEN1
 *
 * @BRIEF        Enable wakeup generation. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__ENWAKEUP__WAKEUPGEN1     0x1u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__SOFTRESET__NOOP
 *
 * @BRIEF        Enumeration value description is not available - (Write)
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__SOFTRESET__NOOP          0x0u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__SOFTRESET__DORESET
 *
 * @BRIEF        Start a soft reset sequence of the Spin Lock module. - 
 *               (Write) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__SOFTRESET__DORESET       0x1u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__AUTOGATING__FREERUNNING
 *
 * @BRIEF        OCP clock is not gated when OCP interface is idle. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__AUTOGATING__FREERUNNING  0x0u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSCONFIG__AUTOGATING__GATED
 *
 * @BRIEF        Automatic internal OCP clock gating strategy is applied, 
 *               based on the OCP interface activity. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSCONFIG__AUTOGATING__GATED        0x1u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__NUMLOCKS__32LOCKS
 *
 * @BRIEF        This instance has 32 lock registers. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__NUMLOCKS__32LOCKS         0x1u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__NUMLOCKS__64LOCKS
 *
 * @BRIEF        This instance has 64 lock registers. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__NUMLOCKS__64LOCKS         0x2u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__NUMLOCKS__128LOCKS
 *
 * @BRIEF        This instance has 128 lock registers. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__NUMLOCKS__128LOCKS        0x4u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__SYSTATUS__NUMLOCKS__256LOCKS
 *
 * @BRIEF        This instance has 256 lock registers. - (Read) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__SYSTATUS__NUMLOCKS__256LOCKS        0x8u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__LOCK_REG__TAKEN__FREE
 *
 * @BRIEF        On a read, indicates that the lock was previously free.  On 
 *               a write, sets the lock to not taken (free). - (RW) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__LOCK_REG__TAKEN__FREE               0x0u

/*-------------------------------------------------------------------------*//**
 * @DEFINITION   SPINLOCK__LOCK_REG__TAKEN__BUSY
 *
 * @BRIEF        On a read, indicates that the lock was already taken (busy). 
 *                Writes of BUSY are ignored. - (RW) 
 *
 *//*------------------------------------------------------------------------ */
#define SPINLOCK__LOCK_REG__TAKEN__BUSY               0x1u


#ifdef __cplusplus
}
#endif
#endif  /* __SPINLOCK_H */