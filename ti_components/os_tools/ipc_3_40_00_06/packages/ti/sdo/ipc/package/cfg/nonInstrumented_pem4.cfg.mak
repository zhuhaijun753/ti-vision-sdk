# invoke SourceDir generated makefile for nonInstrumented.pem4
nonInstrumented.pem4: .libraries,nonInstrumented.pem4
.libraries,nonInstrumented.pem4: package/cfg/nonInstrumented_pem4.xdl
	$(MAKE) -f package/cfg/nonInstrumented_pem4.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/nonInstrumented_pem4.src/makefile.libs clean

