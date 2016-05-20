# invoke SourceDir generated makefile for instrumented.pem4
instrumented.pem4: .libraries,instrumented.pem4
.libraries,instrumented.pem4: package/cfg/instrumented_pem4.xdl
	$(MAKE) -f package/cfg/instrumented_pem4.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/instrumented_pem4.src/makefile.libs clean

