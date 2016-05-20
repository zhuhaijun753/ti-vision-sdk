#******************************************************************************
#*      Copyright (C) 2009-2015 Texas Instruments Incorporated.               *
#*                      All Rights Reserved                                   *
#******************************************************************************


##############################################################
DSP_SW_ROOT      := $(abspath ../../..)

ifeq ($(wildcard $(DSP_SW_ROOT)),)
$(error You must define DSP_SW_ROOT!)
endif

ifeq ($(BUILD_FOLDER),)
BUILD_FOLDER := $(DSP_SW_ROOT)\out
endif

SHOW_COMMANDS ?= 1

ifeq ($(SHOW_COMMANDS),1)
Q:=
else
Q:=@
endif

DSP_SW_ROOT:= $(subst /,\,$(DSP_SW_ROOT))

EMPTY:=
SPACE:=$(EMPTY) $(EMPTY)
COMMA:=$(EMPTY),$(EMPTY)

_MAKEPATH := $(abspath .)
_MAKEPATH:= $(subst /,\,$(_MAKEPATH))

_MODPATH  := $(subst $(DSP_SW_ROOT)\,,$(_MAKEPATH))
_MODPATH:= $(subst /,\,$(_MODPATH))

_MODNAME  := $(subst /,.,$(_MODPATH))

#$(info ---------------- $(_MODNAME)---------------------)


DSP_TOOLS ?= "C:\ti\ccsv5\tools\compiler\c6000_7.4.2"
XDAIS_PATH ?= "C:\ti\xdais_7_24_00_04"
# Default platform
# Supported values: vayu,vme
TARGET_SOC ?= vayu
# Default CORE
# Supported values: dsp, eve
CORE ?= dsp
TARGET_PLATFORM ?= DSP
# Default C66
# Supported C64T, C64P, C64, C66, C674, C67, C67P
TARGET_CPU ?= C66

XDAIS_PACKAGES_DIR = $(XDAIS_PATH)/packages
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
CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_BUILD)
endif

CURR_BUILD_FOLDER:= $(subst /,\,$(CURR_BUILD_FOLDER))

##############################################################

##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
  #COMPILE_PATH=C:\MinGW32
  #CC=$(COMPILE_PATH)/bin/g++ -c
  #AR=$(COMPILE_PATH)/bin/ar
  #ARFLAGS = rvs
  CC = CL
  CP = CL
  AS = $(TARGET_CPU)ASM
  AR = LIB
  LD = LINK
ifeq ($(TARGET_BUILD), release)
  CFLAGS := /EHsc /TP /W0 /DHOST_EMULATION /c /nologo /Ox /MD /D_MSC_VER
  LDDEBUG :=
else
  CFLAGS := /EHsc /TP /W0 /DHOST_EMULATION /c /nologo /Od /MDd /Gm /Zi /RTC1 /D_MSC_VER
  LDDEBUG := /DEBUG
endif
	ifeq ($(TARGET_CPU),C64T)
		CFLAGS += -DTMS320C64X
		else ifeq ($(TARGET_CPU),C64P)
		CFLAGS += -DTMS320C64PX
		else ifeq ($(TARGET_CPU),C64)
		CFLAGS += -DTMS320C64X
		else ifeq ($(TARGET_CPU),C66)
		CFLAGS += -DTMS320C66X
		else ifeq ($(TARGET_CPU),C674)
		CFLAGS += -DTMS320C67X
		else ifeq ($(TARGET_CPU),C67)
		CFLAGS += -DTMS320C67X
		else ifeq ($(TARGET_CPU),C67P)
		CFLAGS += -DTMS320C67X
	endif
  		CFLAGS += -DLITTLE_ENDIAN_HOST

  ARFLAGS := /nologo /MACHINE:X86
else
  ifeq ($(CORE),dsp)
    CC = $(DSP_TOOLS)\bin\cl6x
    LD = $(DSP_TOOLS)\bin\lnk6x
    AR = $(DSP_TOOLS)\bin\ar6x
    ifeq ($(TARGET_BUILD), release)
      CFLAGS = -O3 -ml3 -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS) --abi=eabi --rtti -mo
    else
      CFLAGS = -ml3 -g -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS) --abi=eabi --rtti -mo
    endif
	ifeq ($(TARGET_CPU),C64T)
		CFLAGS += --silicon_version=tesla -D=xdc_target_name=C64T
		else ifeq ($(TARGET_CPU),C64P)
		CFLAGS += --silicon_version=6400+ -D=xdc_target_name=C64P
		else ifeq ($(TARGET_CPU),C64)
		CFLAGS += --silicon_version=6400 -D=xdc_target_name=C64
		else ifeq ($(TARGET_CPU),C66)
		CFLAGS += --silicon_version=6600 -D=xdc_target_name=C66
		else ifeq ($(TARGET_CPU),C674)
		CFLAGS += --silicon_version=6740 -D=xdc_target_name=C674
		else ifeq ($(TARGET_CPU),C67)
		CFLAGS += --silicon_version=6700 -D=xdc_target_name=C67
		else ifeq ($(TARGET_CPU),C67P)
		CFLAGS += --silicon_version=6700+ -D=xdc_target_name=C67P
	endif
    ARFLAGS = r
    CFLAGS += -I $(DSP_TOOLS)\include
  endif
endif

##############################################################


##############################################################
ifeq ($(LIBDIR),)
LIBDIR =  .\libs
endif
ifeq ($(OUTDIR),)
OUTDIR =  .\out
endif


##############################################################


##############################################################
CFILES:= $(subst /,\,$(CFILES))

CFILESC:= $(filter %.c,$(CFILES))
CFILESCPP:= $(filter %.cpp,$(CFILES))
CFILESASM:= $(filter %.asm,$(CFILES))
CFILES:= $(CFILESC) $(CFILESASM) $(CFILESCPP)

#OFILES:= $(addsuffix .obj, $(basename $(notdir $(CFILES))))

OFILES:= $(CFILESC:%.c=%.obj)
OFILES+= $(CFILESCPP:%.cpp=%.obj)
ifneq ($(TARGET_PLATFORM) , PC)
OFILES+= $(CFILESASM:%.asm=%.obj)
endif
DEPILES:= $(CFILESC:%.c=%.dep)
DEPILES+= $(CFILESCPP:%.cpp=%.dep)

BUILDDIR := $(CURR_BUILD_FOLDER)/$(_MODPATH)/
BUILDDIR:= $(subst /,\,$(BUILDDIR))

OFILES:= $(addprefix  $(BUILDDIR), $(OFILES))
DEPILES:= $(addprefix $(BUILDDIR), $(DEPILES))

OFILES  := $(subst /,\,$(OFILES))
DEPILES  := $(subst /,\,$(DEPILES))

OBJDIRS := $(foreach file, $(OFILES), $(dir $(file)))
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

$(OUTFILE): $(OFILES)

$(BUILDDIR)\%.obj: ./%.c
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif

$(BUILDDIR)\%.obj: ./%.cpp
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
	echo @$(AR) $(ARFLAGS) $(OUTFILE) $(OFILES) $(ARFILES)
##############################################################
# clean rules
.IGNORE: clean
clean:
	@echo echo OFF > temp_pps.bat
	@FOR %%i IN ($(OFILES)) DO echo del %%i >> temp_pps.bat
ifneq ($(TARGET_PLATFORM) , PC)
	@FOR %%i IN ( $(DEPILES)) DO echo del %%i >> temp_pps.bat
endif
	@echo echo ON >> temp_pps.bat
	@temp_pps.bat
	@-del temp_pps.bat
	@if exist $(LIBDIR) rmdir/s/q "$(LIBDIR)"
	@if exist $(OUTDIR) rmdir/s/q "$(OUTDIR)"
##############################################################


##############################################################
.PHONY: libfile
libfile: $(LIBDIR) $(OFILES) $(ARFILES)
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo Linking $(OUTFILE)
#	@$(AR) $(ARFLAGS) /OUT:$(OUTFILE) $(OFILES) $(ARFILES)
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
else
	$(Q)if exist $(OUTFILE) del $(OUTFILE)
#	@$(AR) $(ARFLAGS) $(OUTFILE) $(OFILES) $(ARFILES)
	$(Q)echo $(ARFLAGS) $(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
endif
$(LIBDIR):
	@if not exist $(LIBDIR) mkdir $(LIBDIR) || cd $(LIBDIR)
##############################################################


##############################################################
.PHONY: outfile
outfile: $(OUTDIR) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)if exist $(OUTFILE).exe del $(OUTFILE).exe
	$(Q)$(LD) $(filter %.lib,$(LDFLAGS)) $(filter %.lib",$(LDFLAGS)) $(filter %.lib"",$(LDFLAGS)) $(LDDEBUG) /nologo /MACHINE:X86 /OUT:$(OUTFILE).exe $(OFILES) $(LDFILES)
else
	$(Q)if exist $(OUTFILE) del $(OUTFILE)
	$(Q)$(LD) $(LDFLAGS) --output_file=$(OUTFILE) $(OFILES) $(LDFILES) -m "$(OUTFILE)".map
endif
$(OUTDIR):
	$(Q)mkdir $(OUTDIR) || cd $(OUTDIR)

##############################################################

    
##############################################################
.PHONY: pllibfile
pllibfile: $(LIBDIR) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo Linking $(OUTFILE)
#	@$(AR) $(ARFLAGS) /OUT:$(OUTFILE) $(OFILES) $(ARFILES)
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
else
	$(Q)if exist $(OUTFILE) del $(OUTFILE)
	$(Q)$(LD) -r $(LDFLAGS) --output_file="plink.out" $(OFILES) $(LDFILES) -m "plink.map"
	$(Q)echo $(ARFLAGS) $(OUTFILE) > ar_cmd.txt
	$(Q)echo plink.out >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt  
	$(Q)-del ar_cmd.txt  
	$(Q)-del plink.map  
	$(Q)-del plink.out   
endif

##############################################################
define INCLUDE_DEPEND
-include $(1).dep
endef

$(foreach obj,$(OFILES),$(eval $(call INCLUDE_DEPEND,$(basename $(obj)))))




