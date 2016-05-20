/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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

/**
 *  \file      pmhal_prcm_includes.h
 *
 *  \brief     This file contains header files to be used by StarterWare PRCM
 *             (internal) implementation.
 */

#ifndef PMHAL_PRCM_INCLUDES_H_
#define PMHAL_PRCM_INCLUDES_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include "hw_pciectrl_ti_conf.h"
#include "hw_mcasp.h"
#include "hw_mpu_prcm_prmc0.h"
#include "hw_mpu_prcm_prmc1.h"
#include "hw_device_prm.h"
#include "hw_mpu_prm.h"
#include "hw_ocp_socket_cm_core.h"
#include "hw_cam_cm_core.h"
#include "hw_ckgen_cm_core_aon.h"
#include "hw_ocp_socket_prm.h"
#include "hw_coreaon_cm_core.h"
#include "hw_vpe_cm_core_aon.h"
#include "hw_core_prm.h"
#include "hw_wkupaon_cm.h"
#include "hw_mpu_cm_core_aon.h"
#include "hw_eve3_cm_core_aon.h"
#include "hw_eve1_prm.h"
#include "hw_ipu_prm.h"
#include "hw_dsp1_prm.h"
#include "hw_dsp1_cm_core_aon.h"
#include "hw_restore_cm_core_aon.h"
#include "hw_iva_prm.h"
#include "hw_eve4_cm_core_aon.h"
#include "hw_eve2_prm.h"
#include "hw_eve3_prm.h"
#include "hw_eve4_prm.h"
#include "hw_emu_cm.h"
#include "hw_emu_prm.h"
#include "hw_ckgen_prm.h"
#include "hw_dsp2_prm.h"
#include "hw_l4per_cm_core.h"
#include "hw_cam_prm.h"
#include "hw_restore_cm_core.h"
#include "hw_gpu_cm_core.h"
#include "hw_ocp_socket_cm_core_aon.h"
#include "hw_eve1_cm_core_aon.h"
#include "hw_iva_cm_core.h"
#include "hw_dss_cm_core.h"
#include "hw_gpu_prm.h"
#include "hw_eve2_cm_core_aon.h"
#include "hw_l3init_prm.h"
#include "hw_ckgen_cm_core.h"
#include "hw_custefuse_prm.h"
#include "hw_custefuse_cm_core.h"
#include "hw_cmi.h"
#include "hw_l3init_cm_core.h"
#include "hw_dsp2_cm_core_aon.h"
#include "hw_core_cm_core.h"
#include "hw_ipu_cm_core_aon.h"
#include "hw_vpe_prm.h"
#include "hw_dss_prm.h"
#include "hw_rtc_cm_core_aon.h"
#include "hw_l4per_prm.h"
#include "hw_dsp_system.h"
#include "hw_dispc.h"
#include "hw_eve_control.h"
#include "hw_i2c.h"
#include "hw_gpmc.h"
#include "hw_mmu.h"
#include "hw_ipu_mmu.h"
#include "hw_ocmc_ram.h"
#include "hw_spinlock.h"
#include "hw_mailbox.h"
#include "hw_mcspi.h"
#include "hw_uart.h"
#include "hw_gpio.h"
#include "hw_qspi.h"
#include "hw_vip.h"
#include "hw_vpe.h"
#include "hw_counter_32k.h"
#include "hw_sysconfig.h"
#include "hw_mmc.h"
#include "hw_edma_tc.h"
#include "hw_ctrl_core.h"
#if defined (TDA2EX_BUILD)
#include "hw_cal.h"
#endif

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#endif /* PMHAL_PRCM_INCLUDES_H_ */
