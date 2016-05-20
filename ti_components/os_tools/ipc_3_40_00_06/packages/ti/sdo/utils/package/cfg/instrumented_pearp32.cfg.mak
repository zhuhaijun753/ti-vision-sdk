# invoke SourceDir generated makefile for instrumented.pearp32
instrumented.pearp32: .libraries,instrumented.pearp32
.libraries,instrumented.pearp32: package/cfg/instrumented_pearp32.xdl
	$(MAKE) -f package/cfg/instrumented_pearp32.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/instrumented_pearp32.src/makefile.libs clean

