/*
 *
 * Bridging ASM function to make SMC calls to secure world
 *
 * (C) Copyright 2015
 * Texas Instruments, <www.ti.com>
 *
 * Daniel Allred    <d-allred@ti.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

/****************************** Global Symbols*********************************/

    .global SEC_ENTRY_Pub2SecBridgeEntry


/******************************* Code Section *********************************/
    .text
    .code 32
    .arch_extension sec

/*______________________________________________________________________________
 * FUNCTION: SEC_ENTRY_Pub2SecBridgeEntry
 *
 * DESCRIPTION: ASM function running in privilege mode to generate the
 * SMC ARM instruction to enter the Monitor Mode.
 * This function must save/restore CPU registers that could
 * be destroyed during the Secure Service excecution.
 *
 * Note:
 * R0 = Secure Service ID R1 = Process ID
 * R2 = Call flags R3 = pointer on the va_list
 *
 * RETURNS: Return value in R0
 *______________________________________________________________________________
 */

SEC_ENTRY_Pub2SecBridgeEntry:
    PUSH    {r4-r12, lr}

    /* Indicate new Task call */
    MOV     r6, #0xFF

    /* Copy the Secure Service ID in R12 */
    MOV     r12, #0x00

    /* Clean data before entering secure mode */
    MCR     p15, 0, r0, c7, c5, 6
    MCR     p15, 0, r0, c7, c10, 4
    MCR     p15, 0, r0, c7, c5, 4
    MCR     p15, 0, r0, c7, c10, 5

    /* Use SMC #1 to enter Monitor */
    SMC     1
    B SEC_ENTRY_ServiceEnd /* At end of the service execution, SW comes here */
    NOP

    /* In case of IRQ happening in Secure, then ARM will branch here.       */
    /* At that moment, IRQ will be pending and ARM will jump to Non Secure  */
    /* IRQ handler                                                          */
    MOV     R12, #0xFE

    /* Clean data before entering secure mode */
    MCR     p15, 0, r0, c7, c5, 6
    MCR     p15, 0, r0, c7, c10, 4
    MCR     p15, 0, r0, c7, c5, 4
    MCR     p15, 0, r0, c7, c10, 5

    /* Use SMC #1 to enter Monitor */
    SMC     1

SEC_ENTRY_ServiceEnd:
    POP     {r4-r12, lr}
    BX      lr

/* End of file */
