ifeq ($(PACKAGE_ISS_DEF), yes)
   PACKAGE_SRCS_COMMON += isscore
   SRCS_COMMON += vpscore_isscommon.c
endif

ifeq ($(PACKAGE_SIMCOP),yes)
  SRCS_COMMON += vpscore_simcop.c
endif
ifeq ($(PACKAGE_ISS),yes)
  SRCS_COMMON += vpscore_ispapi.c vpscore_isp.c vpscore_captureapi.c
endif
