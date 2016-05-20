/*
* hw_iss_stpmi2atb.h
*
* Register-level header file for ISS_STPMI2ATB
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

#ifndef HW_ISS_STPMI2ATB_H_
#define HW_ISS_STPMI2ATB_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define ISS_STPMI2ATB_STPTCR                                        (0x0U)
#define ISS_STPMI2ATB_STPTID                                        (0x4U)
#define ISS_STPMI2ATB_STPASYNC                                      (0x10U)
#define ISS_STPMI2ATB_STPFFCR                                       (0x14U)
#define ISS_STPMI2ATB_STPFEAT1                                      (0x18U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ISS_STPMI2ATB_STPTCR_TSEN_SHIFT                                                 (1U)
#define ISS_STPMI2ATB_STPTCR_TSEN_MASK                                                  (0x00000002U)

#define ISS_STPMI2ATB_STPTCR_SYNCEN_SHIFT                                               (2U)
#define ISS_STPMI2ATB_STPTCR_SYNCEN_MASK                                                (0x00000004U)

#define ISS_STPMI2ATB_STPTCR_COMPEN_SHIFT                                               (5U)
#define ISS_STPMI2ATB_STPTCR_COMPEN_MASK                                                (0x00000020U)

#define ISS_STPMI2ATB_STPTCR_DATA_FIFOFULL_SHIFT                                        (23U)
#define ISS_STPMI2ATB_STPTCR_DATA_FIFOFULL_MASK                                         (0x00800000U)

#define ISS_STPMI2ATB_STPTCR_MID_FIFOFULL_SHIFT                                         (24U)
#define ISS_STPMI2ATB_STPTCR_MID_FIFOFULL_MASK                                          (0x01000000U)

#define ISS_STPMI2ATB_STPTID_TRACEID_SHIFT                                              (0U)
#define ISS_STPMI2ATB_STPTID_TRACEID_MASK                                               (0x0000007fU)

#define ISS_STPMI2ATB_STPASYNC_COUNT_SHIFT                                              (0U)
#define ISS_STPMI2ATB_STPASYNC_COUNT_MASK                                               (0x00000fffU)

#define ISS_STPMI2ATB_STPASYNC_MODE_SHIFT                                               (12U)
#define ISS_STPMI2ATB_STPASYNC_MODE_MASK                                                (0x00001000U)

#define ISS_STPMI2ATB_STPFFCR_AUTOFLUSH_SHIFT                                           (0U)
#define ISS_STPMI2ATB_STPFFCR_AUTOFLUSH_MASK                                            (0x00000001U)

#define ISS_STPMI2ATB_STPFFCR_ASYNCPE_SHIFT                                             (1U)
#define ISS_STPMI2ATB_STPFFCR_ASYNCPE_MASK                                              (0x00000002U)

#define ISS_STPMI2ATB_STPFFCR_FORCEFLULSH_SHIFT                                         (5U)
#define ISS_STPMI2ATB_STPFFCR_FORCEFLULSH_MASK                                          (0x00000020U)

#define ISS_STPMI2ATB_STPFEAT1_PROT_SHIFT                                               (0U)
#define ISS_STPMI2ATB_STPFEAT1_PROT_MASK                                                (0x0000000fU)

#define ISS_STPMI2ATB_STPFEAT1_VERSION_SHIFT                                            (4U)
#define ISS_STPMI2ATB_STPFEAT1_VERSION_MASK                                             (0x00000070U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ISS_STPMI2ATB_H_ */

