#ifndef OCMC_COMMON_H_
#define OCMC_COMMON_H_

#include "stdint.h"
#include "irq_xbar_interrupt_ids.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif


#define WIDTH  (uint32_t) 8
#define HEIGHT (uint32_t) 6
#define BPP    (uint32_t) 1
#define FRAME_SIZE (WIDTH * HEIGHT * BPS)

#define N_LINES (uint32_t) 2
#define NUM_SLICES_PER_CBUF (uint32_t) 1
#define CBUF_SIZE (WIDTH * BPP * N_LINES * NUM_SLICES_PER_CBUF)

#define cBufSizeInWord  (CBUF_SIZE / 4)

#define OCMC_RAM1_IRQ_CROSS_BAR          (OCMC_RAM1_IRQ)
#define OCMC_RAM1_IRQ_NO                 (25)
#define OCMC_RAM1_IRQ_CROSS_BAR_INSTANCE (3)

uint32_t readSubFrame(uint32_t size, uint32_t *readPointer);
uint32_t writeSubFrame(uint32_t size, uint32_t *writePointer, uint32_t *value);
uint32_t fillBuffer(uint32_t *value, uint32_t startValue, uint32_t size);

void uart_val_print(uint32_t val, char *mess);
void uart_reg_read_print(uint32_t addr, char *mess);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
