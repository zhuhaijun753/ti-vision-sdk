# invoke SourceDir generated makefile for nonInstrumented.pe66
nonInstrumented.pe66: .libraries,nonInstrumented.pe66
.libraries,nonInstrumented.pe66: package/cfg/nonInstrumented_pe66.xdl
	$(MAKE) -f package/cfg/nonInstrumented_pe66.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/nonInstrumented_pe66.src/makefile.libs clean

