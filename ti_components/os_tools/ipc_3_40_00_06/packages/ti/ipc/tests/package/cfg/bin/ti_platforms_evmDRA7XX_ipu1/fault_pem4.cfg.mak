# invoke SourceDir generated makefile for bin/ti_platforms_evmDRA7XX_ipu1/fault.pem4
bin/ti_platforms_evmDRA7XX_ipu1/fault.pem4: .libraries,bin/ti_platforms_evmDRA7XX_ipu1/fault.pem4
.libraries,bin/ti_platforms_evmDRA7XX_ipu1/fault.pem4: package/cfg/bin/ti_platforms_evmDRA7XX_ipu1/fault_pem4.xdl
	$(MAKE) -f package/cfg/bin/ti_platforms_evmDRA7XX_ipu1/fault_pem4.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/bin/ti_platforms_evmDRA7XX_ipu1/fault_pem4.src/makefile.libs clean

