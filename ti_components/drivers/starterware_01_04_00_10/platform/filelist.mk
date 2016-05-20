# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += platform.c stw_platform.c stw_platformEcc.c
SRCS_tda2xx += platform_tda2xx.c platform_tda2xx_pad_config.c stw_platformTda2xx.c
SRCS_tda3xx += platform_tda3xx.c platform_tda3xx_pad_config.c stw_platformTda3xx.c
ASMS_a8host +=

# Nothing beyond this point
