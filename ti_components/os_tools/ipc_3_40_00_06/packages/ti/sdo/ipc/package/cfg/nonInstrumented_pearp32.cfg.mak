# invoke SourceDir generated makefile for nonInstrumented.pearp32
nonInstrumented.pearp32: .libraries,nonInstrumented.pearp32
.libraries,nonInstrumented.pearp32: package/cfg/nonInstrumented_pearp32.xdl
	$(MAKE) -f package/cfg/nonInstrumented_pearp32.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/nonInstrumented_pearp32.src/makefile.libs clean

