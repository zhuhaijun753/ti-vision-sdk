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
 * \file    pmlib_videopll_data.h
 *
 * \brief   PMLIB Videopll Data Base.
 */

#ifndef PMHAL_VIDEOPLL_DATA_H_
#define PMHAL_VIDEOPLL_DATA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include "pmhal_prcm.h"
#if defined (TDA2XX_BUILD) || defined (DRA7XX_BUILD) || defined (TDA2EX_BUILD)
#include "pmhal_videopll.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< PMLIB VIDEOPLL FEAT PARAM DSS PCLK index value */
#define PMLIB_VIDEOPLL_FEAT_PARAM_DSS_PCLK             ((uint32_t) 0U)
/**< PMLIB VIDEOPLL FEAT PARAM DSS FINT index value */
#define PMLIB_VIDEOPLL_FEAT_PARAM_DSS_FINT             ((uint32_t) 1U)
/**< PMLIB VIDEOPLL FEAT PARAM DSS DCOFRindex valueEQ  */
#define PMLIB_VIDEOPLL_FEAT_PARAM_DSS_DCOFREQ          ((uint32_t) 2U)
/**< PMLIB VIDEOPLL FEAT PARAM DSS REGN index value */
#define PMLIB_VIDEOPLL_FEAT_PARAM_DSS_REGN             ((uint32_t) 3U)
/**< PMLIB VIDEOPLL FEAT PARAM DSS REGM index value */
#define PMLIB_VIDEOPLL_FEAT_PARAM_DSS_REGM             ((uint32_t) 4U)
/**< PMLIB VIDEOPLL FEAT PARAM DSS HSDIV index value  */
#define PMLIB_VIDEOPLL_FEAT_PARAM_DSS_HSDIV            ((uint32_t) 5U)
/**< PMLIB VIDEOPLL FEAT NUMBEER OF PARAM  */
#define PMLIB_VIDEOPLL_FEAT_NUMBER_OF_PARAMS           (6U)
/**< PMLIB VIDEOPLL FEAT ATTRIBUTES OF PARAMS  */
#define PMLIB_VIDEOPLL_FEAT_ATTRIBUTES_OF_PARAMS       (2U)

#if defined (TDA3XX_BUILD)
/**< Maximun Post Divider Elements Present */
#define PMLIB_VIDEOPLL_DATA_MAX_POST_DIV_ID         (1U)
#else
#define PMLIB_VIDEOPLL_DATA_MAX_POST_DIV_ID         (2U)
#endif
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
#if defined (TDA2XX_BUILD) || defined (DRA7XX_BUILD) || defined (TDA2EX_BUILD)
typedef struct videoPllConfig
{
    uint32_t frequency;
    /**< Frequency for the videopll in kHz */
    uint16_t multiplier;
    /**< Multiplier value for the given frequency */
    uint16_t divider;
    /**< Divider value for the given frequency */
    uint32_t m2Divider;
    /**< M2 Divider value of the dpll */
}videopllConfig_t;

#else
typedef struct videoPllConfig
{
    uint32_t frequency;
    /**< Frequency for the videopll in kHz*/
    uint16_t multiplier;
    /**< Multiplier value for the given frequency */
    uint16_t divider;
    /**< Divider value for the given frequency */
    uint32_t m2Divider;
    /**< M2 Divider value of the dpll */
    uint32_t postDivider;
    /**< Post Divider for EVE_DSp_VID PLL,
     *  valid values are 1,2 and 4. */
}videopllConfig_t;

#endif
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const uint64_t gPllMinmMaxVal[
    PMLIB_VIDEOPLL_FEAT_NUMBER_OF_PARAMS][
    PMLIB_VIDEOPLL_FEAT_ATTRIBUTES_OF_PARAMS];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if defined (TDA2XX_BUILD) || defined (DRA7XX_BUILD) || defined (TDA2EX_BUILD)
/**
 * \brief   Api to gets the VideoPll structure for given frequency .
 *
 * \param   freq                Frequency at which video pll needs to be
 *                              configured.
 * \param   pVideoPllConfigure  Videopll params structure
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                  PM_SUCCESS  If the desired frequency was set.
 *                  PM_FAIL     If the desired frequency was not set.
 */
int32_t PmlibVideopllGetpllStructure(uint32_t               freq,
                                     pmhalVideopllConfig_t *pVideoPllConfigure);
#else
/**
 * \brief   Api to gets the VideoPll structure for given frequency .
 *
 * \param   freq          Frequency at which video pll needs to be configured.
 * \param   pllParams     Videopll params structure
 * \param   postDivider   Post divider structure.
 *
 * \return  status  Returns the status of the API. This can be the following
 *                  values:
 *                  PM_SUCCESS  If the desired frequency was set.
 *                  PM_FAIL     If the desired frequency was not set.
 */
int32_t PmlibVideopllGetpllStructure(uint32_t               freq,
                                     pmhalPrcmDpllConfig_t *pllParams,
                                     uint32_t              *postDivider);
#endif

#endif /* PMHAL_VIDEOPLL_DATA_H_ */

