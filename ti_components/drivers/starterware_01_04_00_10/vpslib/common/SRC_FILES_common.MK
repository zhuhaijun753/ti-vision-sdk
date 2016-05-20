SRCS_COMMON += vpslib_init.c vps_evtMgr.c vps_resrcMgr.c vps_graph.c
PACKAGE_SRCS_COMMON += common

ifeq ($(PACKAGE_ISS_DEF),yes)
  SRCS_COMMON += iem_evtmgr.c irm_resrcMgr.c
  PACKAGE_SRCS_COMMON += iem_evtmgr.h irm_resrcMgr.h
endif


