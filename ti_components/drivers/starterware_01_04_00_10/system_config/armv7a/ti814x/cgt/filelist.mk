# This file provides files to be compiled in SRC_COMMON, SRC_<CORE> variables

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += interrupt.c cpu.c cp15.c intvec.c
SRCS_ASM_COMMON += exceptionhandler.asm performance_unit.asm

# Nothing beyond this point
