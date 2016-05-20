# This file provides files to be compiled in SRC_COMMON, SRC_<CORE> variables

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += inth.c intctl.c arp32_wugen.c
SRCS_ASM_COMMON += boot_arp32.asm

# Nothing beyond this point
