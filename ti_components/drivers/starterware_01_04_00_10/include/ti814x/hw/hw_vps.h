/*
* hw_vps.h
*
* Register-level header file for VPS of TI814X
*
* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef HW_VPS_H_
#define HW_VPS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define VPS_INTC_INTR1_STATUS_RAW0                                                                          (0x40U)
#define VPS_INTC_INTR1_STATUS_RAW1                                                                          (0x44U)
#define VPS_INTC_INTR1_STATUS0                                                                              (0x48U)
#define VPS_INTC_INTR1_STATUS1                                                                              (0x4cU)
#define VPS_INTC_INTR1_ENA_SET0                                                                             (0x50U)
#define VPS_INTC_INTR1_ENA_SET1                                                                             (0x54U)
#define VPS_INTC_INTR1_ENA_CLR0                                                                             (0x58U)
#define VPS_INTC_INTR1_ENA_CLR1                                                                             (0x5cU)

#define VPS_INTC_INTR2_STATUS_RAW0                                                                          (0x60U)
#define VPS_INTC_INTR2_STATUS_RAW1                                                                          (0x64U)
#define VPS_INTC_INTR2_STATUS0                                                                              (0x68U)
#define VPS_INTC_INTR2_STATUS1                                                                              (0x6cU)
#define VPS_INTC_INTR2_ENA_SET0                                                                             (0x70U)
#define VPS_INTC_INTR2_ENA_SET1                                                                             (0x74U)
#define VPS_INTC_INTR2_ENA_CLR0                                                                             (0x78U)
#define VPS_INTC_INTR2_ENA_CLR1                                                                             (0x7cU)

#define VPS_INTC_INTR3_STATUS_RAW0                                                                          (0x80U)
#define VPS_INTC_INTR3_STATUS_RAW1                                                                          (0x84U)
#define VPS_INTC_INTR3_STATUS0                                                                              (0x88U)
#define VPS_INTC_INTR3_STATUS1                                                                              (0x8cU)
#define VPS_INTC_INTR3_ENA_SET0                                                                             (0x90U)
#define VPS_INTC_INTR3_ENA_SET1                                                                             (0x94U)
#define VPS_INTC_INTR3_ENA_CLR0                                                                             (0x98U)
#define VPS_INTC_INTR3_ENA_CLR1                                                                             (0x9cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#ifdef __cplusplus
}
#endif
#endif  /* HW_VPS_H_ */
