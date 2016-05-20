# invoke SourceDir generated makefile for smpInstrumented.pem4
smpInstrumented.pem4: .libraries,smpInstrumented.pem4
.libraries,smpInstrumented.pem4: package/cfg/smpInstrumented_pem4.xdl
	$(MAKE) -f package/cfg/smpInstrumented_pem4.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/smpInstrumented_pem4.src/makefile.libs clean

