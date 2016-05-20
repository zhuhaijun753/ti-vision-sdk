# invoke SourceDir generated makefile for bin/ti_platforms_evmDRA7XX_ipu1/NameServerApp.pem4
bin/ti_platforms_evmDRA7XX_ipu1/NameServerApp.pem4: .libraries,bin/ti_platforms_evmDRA7XX_ipu1/NameServerApp.pem4
.libraries,bin/ti_platforms_evmDRA7XX_ipu1/NameServerApp.pem4: package/cfg/bin/ti_platforms_evmDRA7XX_ipu1/NameServerApp_pem4.xdl
	$(MAKE) -f package/cfg/bin/ti_platforms_evmDRA7XX_ipu1/NameServerApp_pem4.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/bin/ti_platforms_evmDRA7XX_ipu1/NameServerApp_pem4.src/makefile.libs clean

