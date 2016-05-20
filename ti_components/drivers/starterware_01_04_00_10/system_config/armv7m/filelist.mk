# This file provides files to be compiled in SRC_COMMON, SRC_<CORE> variables

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += interrupt.c

SRCS_m4 += ipu_wugen.c ammu.c unicache.c
SRCS_tda3xx += ipu_ecc.c

# TODO : Add prcm files from SBL
# hal_prcm_cm.c platform_vayu_prcm.c prcm_cm.c
SRCS_ASM_COMMON +=

# Nothing beyond this point
