# invoke SourceDir generated makefile for smpNonInstrumented.pem4
smpNonInstrumented.pem4: .libraries,smpNonInstrumented.pem4
.libraries,smpNonInstrumented.pem4: package/cfg/smpNonInstrumented_pem4.xdl
	$(MAKE) -f package/cfg/smpNonInstrumented_pem4.src/makefile.libs

clean::
	$(MAKE) -f package/cfg/smpNonInstrumented_pem4.src/makefile.libs clean

