# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
OBJDIR = "..\elf_out"

ARP32_TOOLS ?= "C:\Program Files\Texas Instruments\ARP32_tools"
CC=$(ARP32_TOOLS)\bin\cl-arp32.exe
LN=$(ARP32_TOOLS)\bin\lnk-arp32.exe

SHARED_OBJECTS= vcop_nonMaxSuppress_mxn_16s_c.obj vcop_nonMaxSuppress_mxn_16s_c_tb.obj

CFLAGS  =  -o3 -I $(ARP32_TOOLS)\include -I ..\inc -c --silicon_version=v210
CDFLAGS =  -g -I $(ARP32_TOOLS)\include -I ..\inc -c --silicon_version=v210
LFLAGS =  -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib
BOOT = "..\..\..\common\boot_arp32.obj"

all: $(OBJDIR) vcop_nonMaxSuppress_mxn_16s_C.out

vcop_nonMaxSuppress_mxn_16s_C.out: $(SHARED_OBJECTS)
	${LN} $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_c.obj $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_c_tb.obj $(BOOT) $(LFLAGS) -o $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_C.out -l ..\..\..\common\linker.cmd -m $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_C.map
	del $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_c_tb.obj $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_c.obj

vcop_nonMaxSuppress_mxn_16s_c.obj: .\vcop_nonMaxSuppress_mxn_16s_c.c
	$(CC) $(CFLAGS) .\vcop_nonMaxSuppress_mxn_16s_c.c --obj_directory $(OBJDIR) vcop_nonMaxSuppress_mxn_16s_c.obj

vcop_nonMaxSuppress_mxn_16s_c_tb.obj: .\vcop_nonMaxSuppress_mxn_16s_c_tb.c
	$(CC) $(CDFLAGS) .\vcop_nonMaxSuppress_mxn_16s_c_tb.c --obj_directory $(OBJDIR) vcop_nonMaxSuppress_mxn_16s_c_tb.obj

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR) || cd $(OBJDIR)

clean :  
	if exist $(OBJDIR) @rmdir/s/q $(OBJDIR)
	del $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_c_tb.obj $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_c.obj $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_C.out $(OBJDIR)\vcop_nonMaxSuppress_mxn_16s_C.map
