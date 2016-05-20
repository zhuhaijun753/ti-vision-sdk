# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
OBJDIR = "..\elf_out"

ARP32_TOOLS ?= "C:\Program Files\Texas Instruments\ARP32_tools"
CC=$(ARP32_TOOLS)\bin\cl-arp32.exe
LN=$(ARP32_TOOLS)\bin\lnk-arp32.exe

# host compiler (must be C++)
HOSTCC = "g++"
HOSTCC_FLAGS = -g -fpermissive -I"..\inc"

SHARED_OBJECTS= vcop_block_statistics_cn.obj vcop_block_statistics_cn_tb.obj

CFLAGS  =  -o3 -I $(ARP32_TOOLS)\include -I ..\inc -c --silicon_version=v210
CDFLAGS =  -g -I $(ARP32_TOOLS)\include -I ..\inc -c --silicon_version=v210
LFLAGS =  -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib
BOOT = "..\..\..\common\boot_arp32.obj"

all: $(OBJDIR) $(OBJDIR) vcop_block_statistics_C.out

vcop_block_statistics_C.out: $(SHARED_OBJECTS)
	${LN} $(OBJDIR)\vcop_block_statistics_cn.obj $(OBJDIR)\vcop_block_statistics_cn_tb.obj $(BOOT) $(LFLAGS) -o $(OBJDIR)\vcop_block_statistics_C.out -l ..\..\..\common\linker.cmd -l ..\..\..\common\boot_arp32.obj -m $(OBJDIR)\vcop_block_statistics_C.map
	del $(OBJDIR)\vcop_block_statistics_cn_tb.obj $(OBJDIR)\vcop_block_statistics_cn.obj

vcop_block_statistics_cn.obj: vcop_block_statistics_cn.c
	$(CC) $(CFLAGS) vcop_block_statistics_cn.c --obj_directory $(OBJDIR) vcop_block_statistics_cn.obj

vcop_block_statistics_cn_tb.obj: vcop_block_statistics_cn_tb.c
	$(CC) $(CDFLAGS) vcop_block_statistics_cn_tb.c --obj_directory $(OBJDIR) vcop_block_statistics_cn_tb.obj

host: a.out

a.out: vcop_block_statistics_cn.c
	$(HOSTCC) $(HOSTCC_FLAGS) vcop_block_statistics_cn.c vcop_block_statistics_cn_tb.c

# 'hostrun' rules
hostrun: a.out
	a.out

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR) || cd $(OBJDIR)

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR) || cd $(OBJDIR)

clean :  
	if exist $(OBJDIR) @rmdir/s/q $(OBJDIR)
	del a.exe
	del $(OBJDIR)\vcop_block_statistics_cn_tb.obj $(OBJDIR)\vcop_block_statistics_cn.obj $(OBJDIR)\vcop_block_statistics_C.out $(OBJDIR)\vcop_block_statistics_C.map
	if exist $(OBJDIR) @rmdir/s/q $(OBJDIR)
