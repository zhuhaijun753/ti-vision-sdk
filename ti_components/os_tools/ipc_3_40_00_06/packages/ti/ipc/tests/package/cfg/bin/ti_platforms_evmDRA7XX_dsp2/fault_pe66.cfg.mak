# invoke SourceDir generated makefile for bin/ti_platforms_evmDRA7XX_dsp2/fault.pe66
bin/ti_platforms_evmDRA7XX_dsp2/fault.pe66: .libraries,bin/ti_platforms_evmDRA7XX_dsp2/fault.pe66
.libraries,bin/ti_platforms_evmDRA7XX_dsp2/fault.pe66: package/cfg/bin/ti_platforms_evmDRA7XX_dsp2/fault_pe66.xdl
	$(MAKE) -f package/cfg/bin/ti_platforms_evmDRA7XX_dsp2/fault_pe66.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/bin/ti_platforms_evmDRA7XX_dsp2/fault_pe66.src/makefile.libs clean
