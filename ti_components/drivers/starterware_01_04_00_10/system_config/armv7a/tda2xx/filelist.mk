# This file provides files to be compiled in SRC_COMMON, SRC_<CORE> variables 

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += interrupt.c cpu.c cp15.c intvec.c mpu_wugen.c cache_a15.c mmu_a15.c
SRCS_ASM_COMMON += exceptionhandler.asm bl_init.asm initmmu.asm performance_unit.asm mmu_a15_gcc.asm cache_a15_gcc.asm

# Nothing beyond this point
