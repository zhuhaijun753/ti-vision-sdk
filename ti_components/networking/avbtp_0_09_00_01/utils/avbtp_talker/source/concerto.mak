include $(PRELUDE)
TARGET := avbtp_talker
TARGETTYPE := exe
CPPSOURCES := $(all-cpp-files)
CFLAGS := -std=c++0x -static-libgcc
include $(FINALE)
