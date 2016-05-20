// #include "stw_dataTypes.h"
#include "stdint.h"
#include "ocmc_common.h"
#include "hw_types.h"
#include "uartStdio.h"
#include "ocmc_ecc_l1.h"

uint32_t *write_addr = NULL;
uint32_t *read_addr  = NULL;
uint32_t  nextVal;
uint32_t  gValue[cBufSizeInWord];

void uart_reg_read_print(uint32_t addr, char *mess)
{
    uint32_t val = 0;

    UARTPuts(mess, -1);
    val = HW_RD_REG32(addr);
    UARTPutHexNum(val);
}

void uart_val_print(uint32_t val, char *mess)
{
    UARTPuts(mess, -1);
    UARTPutHexNum(val);
}

uint32_t readSubFrame(uint32_t size, uint32_t *readPointer)
{
    uint32_t i   = 0;
    uint32_t val = 0;

    for (i = 0; i < size; i++)
    {
        val = *readPointer++;
        uart_val_print(val, " ");
    }

    return 0;
}

uint32_t writeSubFrame(uint32_t size, uint32_t *writePointer, uint32_t *value)
{
    uint32_t i = 0;
    for (i = 0; i < size; i++)
    {
        *writePointer++ = *value++;
    }

    return 0;
}

uint32_t fillBuffer(uint32_t *value, uint32_t startValue, uint32_t size)
{
    uint32_t i = 0;

    for (i = 0; i < size; i++)
    {
        *(value + i) = startValue + i;
    }

    return (startValue + i);
}

