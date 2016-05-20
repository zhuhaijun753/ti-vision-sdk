#*******************************************************************************
#                                                                              *
# Copyright (c) 2013 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# Filename: rules_a15.mk
#
# Make rules for A15 - This file has all the common rules and defines required
#                     for Cortex-A15 ISA
#
# This file needs to change when:
#     1. Code generation tool chain changes (This file uses Code Sourcery)
#     2. Internal switches (which are normally not touched) has to change
#     3. XDC specific switches change
#     4. a rule common for A15 ISA has to be added or modified

# Set compiler/archiver/linker commands and include paths
CODEGEN_INCLUDE = $(CODEGEN_PATH_A15)/arm-none-eabi/include
CC = $(CODEGEN_PATH_A15)/bin/arm-none-eabi-gcc
AR = $(CODEGEN_PATH_A15)/bin/arm-none-eabi-ar
LNK = $(CODEGEN_PATH_A15)/bin/arm-none-eabi-ld

# Derive a part of RTS Library name based on ENDIAN: little/big
ifeq ($(ENDIAN),little)
  RTSLIB_ENDIAN = le
else
  RTSLIB_ENDIAN = be
endif

# Derive compiler switch and part of RTS Library name based on FORMAT: COFF/ELF
ifeq ($(FORMAT),COFF)
  CSWITCH_FORMAT = ti_arm9_abi
  RTSLIB_FORMAT = tiarm9
endif
ifeq ($(FORMAT),ELF)
  CSWITCH_FORMAT = eabi
  RTSLIB_FORMAT = eabi
endif

# Internal CFLAGS - normally doesn't change
CFLAGS_INTERNAL = -c -mcpu=cortex-a15 -g -mfpu=neon -mfloat-abi=hard -mabi=aapcs -mapcs-frame  -ffunction-sections -fdata-sections
CFLAGS_DIROPTS =

# CFLAGS based on profile selected
ifeq ($(PROFILE_$(CORE)), debug)
CFLAGS_INTERNAL += -D_DEBUG_=1
endif
ifeq ($(PROFILE_$(CORE)), release)
 LNKFLAGS_INTERNAL_PROFILE =
endif

ifeq ($(TREAT_WARNINGS_AS_ERROR), yes)
CFLAGS_INTERNAL += -Werror
endif

# XDC specific CFLAGS
CFLAGS_XDCINTERNAL = -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_target_name__=A15F -Dxdc_bld__profile_$(PROFILE_$(CORE))  -Dxdc_bld__vers_1_0_4_3_3 -DBIOS_BUILD
ifndef MODULE_NAME
  CFLAGS_XDCINTERNAL += -Dxdc_cfg__header__='$(CONFIGURO_DIR)/package/cfg/a15_app_pa15fg.h'
endif
LNKFLAGS_INTERNAL_PROFILE =

# Following 'if...' block is for an application; to add a #define for each
#   component in the build. This is required to know - at compile time - which
#   components are on which core.
ifndef MODULE_NAME
  # Derive list of all packages from each of the components needed by the app
  PKG_LIST_A15_LOCAL = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the local CORE...
  CFLAGS_APP_DEFINES = $(foreach PKG,$(PKG_LIST_A15_LOCAL),-D_LOCAL_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_A15_LOCAL),-D_BUILD_$(PKG)_)

  ifeq ($(CORE),a15_0)
    PKG_LIST_A15_REMOTE = $(foreach COMP,$(COMP_LIST_$(CORE)),$($(COMP)_PKG_LIST))
    CFLAGS_APP_DEFINES += -D_LOCAL_CORE_$(CORE)_
  endif

  # Defines for the app and cfg source code to know which components/packages
  # are included in the build for the remote CORE...
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_A15_REMOTE),-D_REMOTE_$(PKG)_)
  CFLAGS_APP_DEFINES += $(foreach PKG,$(PKG_LIST_A15_REMOTE),-D_BUILD_$(PKG)_)
endif

# This CFLAG is added to include header files for re-entrancy support when migrating to BIOS version 6.37.01.24. XDC tools version 3.25.05.94
CFLAGS_FOR_REENTRANCY_SUPPORT = -I$(XDCROOT)/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include

# Assemble CFLAGS from all other CFLAGS definitions
_CFLAGS = $(CFLAGS_GLOBAL_$(CORE)) $(CFLAGS_INTERNAL) $(CFLAGS_XDCINTERNAL) $(CFLAGS_LOCAL_COMMON) $(CFLAGS_LOCAL_$(CORE)) $(CFLAGS_LOCAL_$(PLATFORM)) $(CFLAGS_LOCAL_$(SOCFAMILY)) $(CFLAGS_LOCAL_$(SOC)) $(CFLAGS_APP_DEFINES) $(CFLAGS_COMP_COMMON) $(CFLAGS_GLOBAL_$(PLATFORM)) $(CFLAGS_FOR_REENTRANCY_SUPPORT)

#Add some additional include paths
INCLUDES += -I$(evealg_PATH)/apps/apps_nonbam/inc
INCLUDES += -I$(evealg_PATH)/
INCLUDES += -I$(evealg_PATH)/common

# Object file creation
# The first $(CC) generates the dependency make files for each of the objects
# The second $(CC) compiles the source to generate object
$(OBJ_PATHS): $(OBJDIR)/%.$(OBJEXT): %.c
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -MD -MF $(DEPDIR)/$(basename $(notdir $<)).P $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT) $<

$(OBJ_PATHS_CPP): $(OBJDIR)/%.$(OBJEXT): %.cpp
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -MD -MF $(DEPDIR)/$(basename $(notdir $<)).P $(_CFLAGS) -Wno-write-strings $(INCLUDES) $(CFLAGS_DIROPTS) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT) $<

ASMFLAGS = $(ASMFLAGS_INTERNAL) $(ASMFLAGS_GLOBAL_$(CORE)) $(ASMFLAGS_LOCAL_COMMON) $(ASMFLAGS_LOCAL_$(CORE)) $(ASMFLAGS_LOCAL_$(PLATFORM)) $(ASMFLAGS_LOCAL_$(SOCFAMILY)) $(ASMFLAGS_LOCAL_$(SOC)) $(ASMFLAGS_APP_DEFINES) $(ASMFLAGS_COMP_COMMON) $(ASMFLAGS_GLOBAL_$(PLATFORM))
# Object file creation
$(OBJ_PATHS_ASM): $(OBJDIR)/%.$(OBJEXT): %.asm
	$(ECHO) \# Compiling $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(APP_NAME)$(MODULE_NAME): $<
	$(CC) -c -x assembler-with-cpp $(_CFLAGS) $(ASMFLAGS) $(INCLUDES) -o $(OBJDIR)/$(basename $(notdir $<)).$(OBJEXT) $<

$(PACKAGE_PATHS): $(PACKAGEDIR)/%: %
	$(ECHO) \# Copying $(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)/$<
	$(MKDIR) -p $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)
	$(CP) --parents -rf $< $(DEST_ROOT)/package/$(PACKAGE_SELECT)/$(PACKAGE_NAME)/$($(MODULE_NAME)_RELPATH)

# Archive flags - normally doesn't change
ARFLAGS = cr

# Archive/library file creation
$(LIBDIR)/$(MODULE_NAME).$(LIBEXT) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP)
	$(ECHO) \#
	$(ECHO) \# Archiving $(PLATFORM):$(CORE):$(PROFILE_$(CORE)):$(MODULE_NAME)
	$(ECHO) \#
	$(AR) $(ARFLAGS) $@ $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP)

# Linker options and rules
LNKFLAGS_INTERNAL_COMMON = --gc-sections

# Assemble Linker flags from all other LNKFLAGS definitions
_LNKFLAGS = $(LNKFLAGS_INTERNAL_COMMON) $(LNKFLAGS_INTERNAL_PROFILE) $(LNKFLAGS_GLOBAL_$(CORE)) $(LNKFLAGS_LOCAL_COMMON) $(LNKFLAGS_LOCAL_$(CORE))

# Path of the RTS library - normally doesn't change for a given tool-chain
RTSLIB_PATH =

LIB_PATHS += $(APP_LIBS_$(CORE))
LIB_PATHS += $(EXT_LIB_a15_0) $(CODEGEN_PATH_A15)/lib/gcc/arm-none-eabi/4.7.3/fpu/libgcc.a $(CODEGEN_PATH_A15)/arm-none-eabi/lib/fpu/libc.a $(CODEGEN_PATH_A15)/arm-none-eabi/lib/fpu/libm.a  $(CODEGEN_PATH_A15)/arm-none-eabi/lib/fpu/librdimon.a $(CODEGEN_PATH_A15)/arm-none-eabi/lib/fpu/libg.a
LIB_PATHS += $(DEST_ROOT)/ti/sdo/edma3/rm/lib/tda2xx-evm/$(ISA)/$(PROFILE_$(CORE))/edma3_lld_rm.$(LIBEXT)
LIB_PATHS += $(DEST_ROOT)/ti/sdo/edma3/drv/lib/$(ISA)/$(PROFILE_$(CORE))/edma3_lld_drv.$(LIBEXT)
LIB_PATHS += $(RTSLIB_PATH)


LIB_PATHS_DIR = $(xdc_PATH)/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/fpu
LIB_PATHS_DIR += $(CODEGEN_PATH_A15)/lib/gcc/arm-none-eabi/4.7.3/fpu
LIB_PATHS_DIR += $(CODEGEN_PATH_A15)/arm-none-eabi/lib/fpu

LNK_LIBS = $(addprefix -L,$(LIB_PATHS_DIR))
#LNK_LIBS += $(LIB_PATHS)
LNK_LIBS += $(addprefix -L,$(LIB_PATHS))
# Added -lgcc twice to support both "before" and "after" order with -lm
# This is required to satisfy some linking order to support
# some Math/Algo kernals on A15
LNK_LIBS += -lstdc++ -lgcc -lm -lgcc -lc -lrdimon


# Linker - to create executable file
ifeq ($(LOCAL_APP_NAME),)
 EXE_NAME = $(BINDIR)/$(APP_NAME)_$(CORE)_$(PROFILE_$(CORE)).$(EXEEXT)
else
 ifeq ($(PROFILE_$(CORE)),prod_release)
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME).$(EXEEXT)
 else
  EXE_NAME = $(BINDIR)/$(LOCAL_APP_NAME)_$(PROFILE_$(CORE)).$(EXEEXT)
 endif
endif

$(EXE_NAME) : $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) $(LIB_PATHS) $(LNKCMD_FILE) $(OBJDIR)/$(CFG_COBJ_XDC)
	$(ECHO) \# Linking into $(EXE_NAME)...
	$(ECHO) \#
	$(CP) $(OBJDIR)/$(CFG_COBJ_XDC) $(CONFIGURO_DIR)/package/cfg
	$(LNK) $(_LNKFLAGS) $(OBJ_PATHS_ASM) $(OBJ_PATHS) $(OBJ_PATHS_CPP) -T $(LNKCMD_FILE) $(LNK_LIBS) -Map=$@.map -o $@ $(EXT_LIB_a15_0) --start-group $(LIB_PATHS) --end-group
	$(ECHO) \#
	$(ECHO) \# $@ created.
	$(ECHO) \#

# XDC specific - assemble XDC-Configuro command
ifeq ($(PROFILE_$(CORE)),prod_release)
  CONFIGURO_PROFILE = release
else
  CONFIGURO_PROFILE = $(PROFILE_$(CORE))
endif
CONFIGURO_CMD = $(xdc_PATH)/xs xdc.tools.configuro --generationOnly -o $(CONFIGURO_DIR) -t $(TARGET_XDC) -p $(PLATFORM_XDC) \
               -r $(CONFIGURO_PROFILE) -b $(CONFIG_BLD_XDC_$(ISA)) --cfgArgs $(CFGARGS_XDC) $(XDC_CFG_FILE_NAME)
_XDC_GREP_STRING = \"$(XDC_GREP_STRING)\"
EGREP_CMD = $(EGREP) -ivw $(XDC_GREP_STRING) $(XDCLNKCMD_FILE)

ifeq ($(OS),Windows_NT)
EVERYONE := $(word 1,$(shell whoami -groups | findstr "S-1-1-0"))
endif

# Invoke configuro for the rest of the components
#  NOTE: 1. String handling is having issues with various make versions when the
#           cammand is directly tried to be given below. Hence, as a work-around,
#           the command is re-directed to a file (shell or batch file) and then
#           executed
#        2. The linker.cmd file generated, includes the libraries generated by
#           XDC. An egrep to search for these and omit in the .cmd file is added
#           after configuro is done
xdc_configuro : $(XDC_CFG_FILE)
	$(ECHO) \# Invoking configuro...
	$(MKDIR) -p $(DEST_ROOT)
	$(ECHO) -e $(CONFIGURO_CMD) > $(DEST_ROOT)/maketemp_configuro_cmd_$(CORE).bat
ifeq ($(OS),Windows_NT)
	CACLS $(DEST_ROOT)/maketemp_configuro_cmd_$(CORE).bat /E /P $(EVERYONE):F
else
	$(CHMOD) a+x $(DEST_ROOT)/maketemp_configuro_cmd_$(CORE).bat
endif
	$(DEST_ROOT)/maketemp_configuro_cmd_$(CORE).bat
	$(CP) $(XDCLNKCMD_FILE) $(LNKCMD_FILE)
	$(ECHO) \# Configuro done!

$(LNKCMD_FILE) :

ifndef MODULE_NAME
$(OBJDIR)/$(CFG_COBJ_XDC) : $(CFG_C_XDC)
	$(ECHO) \# Compiling generated $< to $@ ...
	$(CC) $(_CFLAGS) $(INCLUDES) $(CFLAGS_DIROPTS)-o $@ $(CFG_C_XDC)
endif

# Include dependency make files that were generated by $(CC)
-include $(SRCS:%.c=$(DEPDIR)/%.P)
-include $(SRCS_CPP:%.cpp=$(DEPDIR)/%.P)

# Nothing beyond this point