
#ifndef SAMPLE_H_
#define SAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* MAX ACOUNT */
#define MAX_ACOUNT                  (64U)
/* MAX BCOUNT */
#define MAX_BCOUNT                  (1U)
/* MAX CCOUNT */
#define MAX_CCOUNT                  (1U)
/**
 * Buffers (src and dest) are needed for mem-2-mem data transfers.
 * This define is for the MAXIMUM size and hence the maximum data
 * which could be transferred using the sample test cases below.
 */
#define MAX_BUFFER_SIZE             (MAX_ACOUNT * MAX_BCOUNT * MAX_CCOUNT)

#ifndef TI814X_FAMILY_BUILD
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (38U)
#else
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (20U)
#endif

#define EDMA3_CC_XFER_COMPLETION_INT_A8                 (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VPSS             (63U)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO            (62U)
#define EDMA3_CC_XFER_COMPLETION_INT_A15                (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (34U)

#ifdef BUILD_A8
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A8
#elif defined (BUILD_DSP)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_DSP
#elif defined (BUILD_M3VPSS)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M3VPSS
#elif defined (BUILD_M3VIDEO)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO
#elif defined (BUILD_A15)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A15
#elif defined (BUILD_M4)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M4
#endif

#define EDMA3_CC_REGION_A8                              (0U)
#define EDMA3_CC_REGION_M3VPSS                          (5U)
#define EDMA3_CC_REGION_M3VIDEO                         (4U)
#define EDMA3_CC_REGION_A15                             (0U)
#define EDMA3_CC_REGION_M4                              (1U)

#ifndef TI814X_FAMILY_BUILD
#define EDMA3_CC_REGION_DSP                             (2U)
#else
#define EDMA3_CC_REGION_DSP                             (1U)
#endif

#ifdef BUILD_A8
#define EDMA3_CC_REGION EDMA3_CC_REGION_A8
#elif defined (BUILD_DSP)
#define EDMA3_CC_REGION EDMA3_CC_REGION_DSP
#elif defined (BUILD_M3VPSS)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M3VPSS
#elif defined (BUILD_M3VIDEO)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M3VIDEO
#elif defined (BUILD_A15)
#define EDMA3_CC_REGION EDMA3_CC_REGION_A15
#elif defined (BUILD_M4)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M4
#endif

int32_t dma_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                 uint32_t aCnt, uint32_t bCnt,
                 uint32_t cCnt);
int32_t dma_chain_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t ch_num2, uint32_t tcc_num2, uint32_t evtq_num2,
                       uint32_t aCnt,
                       uint32_t bCnt,
                       uint32_t cCnt);
int32_t dma_link_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                      uint32_t edma_paRAM2, uint32_t edma_paRAM3, uint32_t aCnt,
                      uint32_t bCnt,
                      uint32_t cCnt);

int32_t dma_polled(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                   uint32_t aCnt, uint32_t bCnt,
                   uint32_t cCnt);

int32_t qdma_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                  uint32_t paramId,
                  uint32_t aCnt, uint32_t bCnt,
                  uint32_t cCnt);

int32_t qdma_link_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t edma_paRAMId1, uint32_t edma_paRAMId2,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt);
int32_t dma_ping_pong_test(uint32_t chId, uint32_t tcc, uint32_t evtq_num,
                           uint32_t lChId1, uint32_t lChId2);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* SAMPLE_H_ */

