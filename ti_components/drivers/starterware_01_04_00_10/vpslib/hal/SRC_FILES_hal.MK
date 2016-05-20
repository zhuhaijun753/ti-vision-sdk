SRCS_COMMON += vpshal.c

ifeq ($(PACKAGE_VIP),yes)
  SRCS_COMMON += vpshal_csc.c vpshal_sc.c vpshal_vpdma.c
  SRCS_COMMON += vpshal_vipPort.c vpshal_vipTop.c
  PACKAGE_SRCS_COMMON += vpshal_vipPort.h vpshal_vipTop.h
  PACKAGE_SRCS_COMMON += vpshal_csc.h vpshal_sc.h                                  \
                         vpshal_vpdma.h vpshalVpdmaTda2xx.h vpshalVpdmaTI814x.h  \
                         vpshal_cscDefaults.h vpshal_scDefaults.h vpshal_scPriv.h  \
                         vpshal_vpdmaPriv.h                                        \
                         vpshalVpdmaDefaultsTda2xx.h vpshalVpdmaDefaultsTI814x.h \
                         vpshal_vpdmaFirmwareTda2xx_v1B8.h                       \
                         vpshal_vpdmaFirmwareTda2xx_v288.h
endif

ifeq ($(PACKAGE_VPE),yes)
  ifneq ($(PACKAGE_VIP),yes)
    SRCS_COMMON += vpshal_csc.c vpshal_sc.c vpshal_vpdma.c
    PACKAGE_SRCS_COMMON += vpshal_csc.h vpshal_sc.h                                  \
                           vpshal_vpdma.h vpshalVpdmaTda2xx.h vpshalVpdmaTI814x.h  \
                           vpshal_cscDefaults.h vpshal_scDefaults.h vpshal_scPriv.h  \
                           vpshal_vpdmaPriv.h                                        \
                           vpshalVpdmaDefaultsTda2xx.h vpshalVpdmaDefaultsTI814x.h \
                           vpshal_vpdmaFirmwareTda2xx_v1B8.h                       \
                           vpshal_vpdmaFirmwareTda2xx_v288.h
  endif
  SRCS_COMMON += vpshal_vpeTop.c vpshal_dei.c vpshal_chrus.c
  PACKAGE_SRCS_COMMON += vpshal_chrus.h vpshal_dei.h vpshal_vpeTop.h           \
                         vpshalChrusDefaults.h vpshalDeiDefaults.h
endif

ifeq ($(PACKAGE_DSS),yes)
  SRCS_tda2xx += vpshal_dssDispcVid.c vpshal_dssDispcOvly.c vpshal_dssHdmi.c
  SRCS_tda3xx += vpshal_dssDispcPipeTda3xx.c vpshal_dssDispcOvlyTda3xx.c vpshal_dssSdVenc.c
  PACKAGE_SRCS_COMMON += vpshal_dssDispcVid.h vpshal_dssDispcOvly.h vpshal_dssHdmi.h vpshal_dssSdVenc.h
endif

ifeq ($(PACKAGE_ISS_DEF),yes)
  SRCS_COMMON += vpshal_iss.c
  PACKAGE_SRCS_COMMON += vpshal_iss.h
endif

ifeq ($(PACKAGE_SIMCOP),yes)
  SRCS_COMMON += vpshal_issvtnf.c vpshal_isssimcop.c
  PACKAGE_SRCS_COMMON += vpshal_issvtnf.h vpshal_issldc.h vpshal_isssimcop.h
  ifeq ($(INCLUDE_WDR_LDC), yes)
    SRCS_COMMON += vpshal_issldc.c
  else
    SRCS_COMMON += vpshal_issldcdm.c
  endif
endif

ifeq ($(PACKAGE_ISS),yes)
  SRCS_COMMON += vpshal_issnsf3.c vpshal_isslvdsrx.c vpshal_issipipe.c \
                 vpshal_issisif.c vpshal_issrsz.c vpshal_issipipeif.c \
                 vpshal_issh3a.c vpshal_isscal.c
  PACKAGE_SRCS_COMMON += vpshal_issnsf3.h vpshal_isslvdsrx.h vpshal_issipipe.h \
                         vpshal_issisif.h vpshal_issrsz.h vpshal_issipipeif.h \
                         vpshal_issh3a.h vpshal_issglbce.h vpshal_isscal.h
  ifeq ($(INCLUDE_WDR_LDC), yes)
    SRCS_COMMON += vpshal_issglbce.c
  else
    SRCS_COMMON += vpshal_issglbcedm.c
  endif
endif

PACKAGE_SRCS_COMMON += $(SRCS_COMMON) vpshal.h SRC_FILES_hal.MK vpshal_platform.h
