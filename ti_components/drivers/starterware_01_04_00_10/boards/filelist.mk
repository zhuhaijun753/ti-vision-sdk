# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += stw_board.c stw_boardTda2xx.c stw_boardTda3xx.c stw_boardTI814x.c stw_boardTda2ex.c
ifeq ($(SOC),tda2ex)
SRCS_tda2ex += stw_boardTda2exPinmuxData.c
endif
ifeq ($(SOC),tda2xx)
SRCS_tda2xx += stw_boardTda2xxPinmuxData.c
endif
SRCS_tda3xx += stw_boardTda3xxPinmuxData.c

# Nothing beyond this point
