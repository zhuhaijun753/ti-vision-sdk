#******************************************************************************
#*      Copyright (C) 2009-2012 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************


##############################################################

ifeq ($(wildcard $(EVE_SW_ROOT)),)
$(error You must define EVE_SW_ROOT!)
endif

ifeq ($(BUILD_FOLDER),)
BUILD_FOLDER := $(EVE_SW_ROOT)\out
endif

SHOW_COMMANDS ?= 0

ifeq ($(SHOW_COMMANDS),1)
Q:=
else
Q:=@
endif

EVE_SW_ROOT:= $(subst /,\,$(EVE_SW_ROOT))

EMPTY:=
SPACE:=$(EMPTY) $(EMPTY)
COMMA:=$(EMPTY),$(EMPTY)

_MAKEPATH := $(abspath .)
_MAKEPATH:= $(subst /,\,$(_MAKEPATH))

_MODPATH  := $(subst $(EVE_SW_ROOT)\,,$(_MAKEPATH))
_MODPATH:= $(subst /,\,$(_MODPATH))

_MODNAME  := $(subst /,.,$(_MODPATH))

BUILD_MODE ?=OBJ

#$(info ---------------- $(_MODNAME)---------------------)


ARP32_TOOLS ?= "C:\ti\ARP32_tools"
xdais_PATH ?= "C:\ti\xdais_7_23_00_06"
# Default platform
# Supported values: vayu,vme
TARGET_SOC ?= vayu
# Default CORE
# Supported values: dsp, eve
CORE ?= eve
TARGET_PLATFORM ?= EVE


PC_LIB_EXTN:=_pc.lib

XDAIS_PACKAGES_DIR = $(xdais_PATH)/packages
#if platform is vayu
ifeq ($(TARGET_SOC),vayu)
    DEFINE_FLAGS := VAYU_PLATFORM
endif

#if platform is vme
ifeq ($(TARGET_SOC),vme)
    DEFINE_FLAGS := VME_PLATFORM
endif

ifeq ($(TARGET_BUILD), )
ifeq ($(TARGET_PLATFORM) , PC)
	TARGET_BUILD := debug
else
	TARGET_BUILD := release
endif
endif

ifeq ($(TARGET_PLATFORM) , PC)
CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_PLATFORM)/$(TARGET_BUILD)
else
CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_SOC)/$(CORE)/$(TARGET_BUILD)
endif

CURR_BUILD_FOLDER:= $(subst /,\,$(CURR_BUILD_FOLDER))


STARTERWARE      := $(EVE_SW_ROOT)\starterware
BASE_ADDRESS_DIR := $(STARTERWARE)/inc/baseaddress/$(TARGET_SOC)/$(CORE)
ifeq ($(TARGET_PLATFORM) , PC)
STARTERWARE_LIB  := $(STARTERWARE)/libs/$(TARGET_PLATFORM)/$(TARGET_BUILD)/libevestarterware_eve.lib$(PC_LIB_EXTN)
else
STARTERWARE_LIB  := $(STARTERWARE)/libs/$(TARGET_SOC)/$(CORE)/$(TARGET_BUILD)/libevestarterware_$(CORE).lib
endif
VCOP_HOST_DIR    := ../kernels/common
##############################################################

##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
  #COMPILE_PATH=C:\MinGW32
  #CC=$(COMPILE_PATH)/bin/g++ -c
  #AR=$(COMPILE_PATH)/bin/ar
  #ARFLAGS = rvs
  #CFLAGS = -O3 -D VCOP_HOST_EMULATION
  CC = CL
  CP = CL
  AS = $(TARGET_CPU)ASM
  AR = LIB
  LD = LINK
ifeq ($(TARGET_BUILD), release)
  CFLAGS += /EHsc /TP /W0 /DVCOP_HOST_EMULATION /DHOST_EMULATION /c /nologo /Ox /MD
  LDDEBUG :=
else
  CFLAGS += /EHsc /TP /W0 /DVCOP_HOST_EMULATION /DHOST_EMULATION /c /nologo /Od /MDd /Gm /Zi /RTC1
  LDDEBUG := /DEBUG
endif
  CFLAGS += -I $(VCOP_HOST_DIR)
  ARFLAGS := /nologo /MACHINE:X86
#  LDFLAGS :=
else
  ifeq ($(CORE),eve)
    CC = $(ARP32_TOOLS)\bin\cl-arp32.exe
    LD = $(ARP32_TOOLS)\bin\lnk-arp32.exe
    AR = $(ARP32_TOOLS)\bin\ar-arp32.exe
    ifeq ($(TARGET_BUILD), release)
      CFLAGS += -kh -kv -lu -o3 --silicon_version=v210 -D$(DEFINE_FLAGS) --gen_func_subsections --display_error_number --diag_suppress=496 --diag_suppress=1311
    else
      CFLAGS += -kh -kv -lu -g --silicon_version=v210  -D$(DEFINE_FLAGS) --gen_func_subsections --display_error_number --diag_suppress=496 --diag_suppress=1311
    endif
    ARFLAGS = r
    LDFLAGS += -cr -x --display_error_number --diag_suppress=num=10063  --diag_suppress=num=10068
    CFLAGS += -I $(ARP32_TOOLS)\include
  endif
  ifeq ($(CORE),dsp)
    CC = $(DSP_TOOLS)\bin\cl6x
    LD = $(DSP_TOOLS)\bin\lnk6x
    AR = $(DSP_TOOLS)\bin\ar6x
    ifeq ($(TARGET_BUILD), release)
      CFLAGS += -O3 -mv6740+ -ml3 -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS)
    else
      CFLAGS +=-mv6740+ -ml3 -g -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS)
    endif
    ARFLAGS = r
    LDFLAGS += -cr -x
    CFLAGS += -I $(DSP_TOOLS)\include
  endif
  ifneq ($(VCOP_H_DIR),)
    CFLAGS += --temp_directory=$(VCOP_H_DIR)
  endif
endif

CFLAGS += -I $(ARP32_TOOLS)/include/vcop
CFLAGS += -I $(BASE_ADDRESS_DIR)
CFLAGS += -I $(STARTERWARE)\inc\edma_csl
CFLAGS += -I $(STARTERWARE)\inc\edma_utils
CFLAGS += -I $(STARTERWARE)\inc

#LDFLAGS += -l $(STARTERWARE_LIB)

##############################################################


##############################################################
ifeq ($(LIBDIR),)
LIBDIR =  .\lib\$(TARGET_BUILD)
endif
ifeq ($(OUTDIR),)
OUTDIR =  .\elf_out
endif

CFLAGS += -I $(ARP32_TOOLS)\include\vcop

#CFLAGS += -DEN_ZEBU_TEST

ifeq ($(ENABLE_FASTFILEIO),1)
CFLAGS += -DUSE_HOST_FILE_IO
endif

##############################################################

# In case there are no sources, it is better to not generate any lib
ifeq (,$(wildcard $(CFILES)))
OUTFILE=
endif
##############################################################
CFILES:= $(subst /,\,$(CFILES))

CFILESK:= $(filter %.k,$(CFILES))
CFILESC:= $(filter %.c,$(CFILES))
CFILESASM:= $(filter %.asm,$(CFILES))
CFILES:= $(CFILESK) $(CFILESC) $(CFILESASM)

#OFILES:= $(addsuffix .obj, $(basename $(notdir $(CFILES))))

OFILES:= $(CFILESC:%.c=%.obj)
ifneq ($(TARGET_PLATFORM) , PC)
OFILES+= $(CFILESASM:%.asm=%.obj)
endif
DEPILES:= $(CFILESC:%.c=%.dep)
KOFILES:= $(CFILESK:%.k=%.obj)

BUILDDIR := $(CURR_BUILD_FOLDER)/$(_MODPATH)/
BUILDDIR:= $(subst /,\,$(BUILDDIR))

OFILES:= $(addprefix  $(BUILDDIR), $(OFILES))
KOFILES:= $(addprefix $(BUILDDIR), $(KOFILES))
DEPILES:= $(addprefix $(BUILDDIR), $(DEPILES))

OFILES  := $(subst /,\,$(OFILES))
KOFILES  := $(subst /,\,$(KOFILES))
DEPILES  := $(subst /,\,$(DEPILES))

OBJDIRS := $(foreach file, $(OFILES), $(dir $(file)))
OBJDIRS += $(foreach file, $(KOFILES), $(dir $(file)))
OBJDIRS += $(BUILDDIR)
OBJDIRS := $(sort $(OBJDIRS))
OBJDIRS := $(addsuffix \.gitignore, $(OBJDIRS))

##############################################################


##############################################################
# 'all' rules
all : dir $(OUTFILE)

# Define a ".gitignore" file which will help in making sure the module's output
# folder always exists.
%.gitignore:
#	@echo creating $@
	$(Q)if not exist $(dir $@) mkdir $(dir $@)
	$(Q)echo .> $@
dir: $(OBJDIRS)

$(OUTFILE): $(KOFILES) $(OFILES)

$(BUILDDIR)\%.obj: ./%.k
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --compile_only -fr=$(dir $@) "$<"
endif

$(BUILDDIR)\%.obj: ./%.c
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif

ifneq ($(TARGET_PLATFORM) , PC)
$(BUILDDIR)\%.obj : ./%.asm
	$(Q)$(CC) $(CFLAGS) -c $^ --output_file=$@
endif
##############################################################

print :
	echo $(LDFLAGS)
	echo $(OFILES)
	echo $(OUTFILE)
	echo $(CFILES)
	echo $(HFILES)
	echo @$(AR) $(ARFLAGS) $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
##############################################################
# clean rules
.IGNORE: clean
clean:
	@echo echo OFF > temp_pps.bat
	@FOR %%i IN ($(OFILES) $(KOFILES)) DO echo del %%i >> temp_pps.bat
ifneq ($(TARGET_PLATFORM) , PC)
	@FOR %%i IN ( $(DEPILES)) DO echo del %%i >> temp_pps.bat
endif
	@echo echo ON >> temp_pps.bat
	@temp_pps.bat
	@-del temp_pps.bat
ifneq ($(BUILD_MODE),OBJ)
	@if exist $(LIBDIR) rmdir/s/q "$(LIBDIR)"
endif
	@if exist $(OUTDIR) rmdir/s/q "$(OUTDIR)"
##############################################################


##############################################################
.PHONY: libfile
libfile: $(LIBDIR) $(KOFILES) $(OFILES) $(ARFILES)
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo Linking $(OUTFILE)
#	@$(AR) $(ARFLAGS) /OUT:$(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE)$(PC_LIB_EXTN) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(KOFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
else
	$(Q)if exist $(OUTFILE) del $(OUTFILE)
#	@$(AR) $(ARFLAGS) $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
	$(Q)echo $(ARFLAGS) $(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(KOFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
endif
$(LIBDIR):
	@if not exist $(LIBDIR) mkdir $(LIBDIR) || cd $(LIBDIR)
##############################################################

PC_LDFLAGS1 = $(filter-out %rtsarp32_v200.lib,$(LDFLAGS))
PC_LDFLAGS = $(filter-out %rtsarp32_v200.lib",$(PC_LDFLAGS1))
ALL_LIBS1 = $(filter %.lib,$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib",$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib"",$(PC_LDFLAGS))

ALL_LIBS  = $(subst .lib,.lib$(PC_LIB_EXTN),$(ALL_LIBS1))

##############################################################
.PHONY: outfile
outfile: $(OUTDIR) $(KOFILES) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)if exist $(OUTFILE).exe del $(OUTFILE).exe
	$(Q)$(LD) $(STARTERWARE_LIB) $(ALL_LIBS) $(LDDEBUG) /nologo /MACHINE:X86 /OUT:$(OUTFILE).exe $(KOFILES) $(OFILES) $(LDFILES)
else
	$(Q)if exist $(OUTFILE) del $(OUTFILE)
	$(Q)$(LD) -l $(STARTERWARE_LIB) $(LDFLAGS) --output_file=$(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) -m "$(OUTFILE)".map
endif
$(OUTDIR):
	$(Q)mkdir $(OUTDIR) || cd $(OUTDIR)

##############################################################


##############################################################
.PHONY: mergefile
mergefile: 
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)$(AR) $(ARFLAGS) /OUT:lib\$(TARGET_BUILD)\libevekernels.eve.lib$(PC_LIB_EXTN) lib\$(TARGET_BUILD)\libevekernels.eve.lib$(PC_LIB_EXTN) lib\$(TARGET_BUILD)\libeveprivkernels.eve.lib$(PC_LIB_EXTN)
	$(Q)$(AR) $(ARFLAGS) /OUT:lib\$(TARGET_BUILD)\libevenatckernels.eve.lib$(PC_LIB_EXTN) lib\$(TARGET_BUILD)\libevenatckernels.eve.lib$(PC_LIB_EXTN) lib\$(TARGET_BUILD)\libeveprivnatckernels.eve.lib$(PC_LIB_EXTN)
else
	$(Q)$(AR) x lib\$(TARGET_BUILD)\libevekernels.eve.lib
	$(Q)$(AR) x lib\$(TARGET_BUILD)\libeveprivkernels.eve.lib
	$(Q)$(AR) a lib\$(TARGET_BUILD)\libevekernels.eve.lib *.obj
	$(Q)-del *.obj
	$(Q)$(AR) x lib\$(TARGET_BUILD)\libevenatckernels.eve.lib
	$(Q)$(AR) x lib\$(TARGET_BUILD)\libeveprivnatckernels.eve.lib
	$(Q)$(AR) a lib\$(TARGET_BUILD)\libevenatckernels.eve.lib *.obj
	$(Q)-del *.obj
endif
##############################################################


define INCLUDE_DEPEND
-include $(1).dep
endef

$(foreach obj,$(OFILES),$(eval $(call INCLUDE_DEPEND,$(basename $(obj)))))




