# invoke SourceDir generated makefile for instrumented.pe66
instrumented.pe66: .libraries,instrumented.pe66
.libraries,instrumented.pe66: package/cfg/instrumented_pe66.xdl
	$(MAKE) -f package/cfg/instrumented_pe66.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/instrumented_pe66.src/makefile.libs clean

