# invoke SourceDir generated makefile for bin/ti_platforms_evmDRA7XX_dsp2/test_omx_dsp2_vayu.pe66
bin/ti_platforms_evmDRA7XX_dsp2/test_omx_dsp2_vayu.pe66: .libraries,bin/ti_platforms_evmDRA7XX_dsp2/test_omx_dsp2_vayu.pe66
.libraries,bin/ti_platforms_evmDRA7XX_dsp2/test_omx_dsp2_vayu.pe66: package/cfg/bin/ti_platforms_evmDRA7XX_dsp2/test_omx_dsp2_vayu_pe66.xdl
	$(MAKE) -f package/cfg/bin/ti_platforms_evmDRA7XX_dsp2/test_omx_dsp2_vayu_pe66.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/bin/ti_platforms_evmDRA7XX_dsp2/test_omx_dsp2_vayu_pe66.src/makefile.libs clean

