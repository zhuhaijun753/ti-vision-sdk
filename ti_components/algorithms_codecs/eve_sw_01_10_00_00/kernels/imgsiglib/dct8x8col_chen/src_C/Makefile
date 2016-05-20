# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
OBJDIR = "..\elf_out"

ARP32_TOOLS ?= "C:\Program Files\Texas Instruments\ARP32_tools"
CC=$(ARP32_TOOLS)\bin\cl-arp32.exe
LN=$(ARP32_TOOLS)\bin\lnk-arp32.exe

SHARED_OBJECTS= vcop_dct8x8col_cn.obj eve_dct8x8col_tb.obj 

CFLAGS =  -g -I $(ARP32_TOOLS)\include -I ..\inc\ -c 
LFLAGS =  -c -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib


all: $(OBJDIR) vcop_dct8x8col_C.out
	
vcop_dct8x8col_C.out: $(SHARED_OBJECTS) 
	${LN} $(OBJDIR)\vcop_dct8x8col_cn.obj $(OBJDIR)\eve_dct8x8col_tb.obj $(LFLAGS) -o $(OBJDIR)\vcop_dct8x8col_C.out -l ..\..\..\common\linker.cmd -l ..\..\..\common\boot_arp32.obj -m $(OBJDIR)\apps.map 

vcop_dct8x8col_cn.obj: .\vcop_dct8x8col_cn.c
	$(CC) $(CFLAGS) .\vcop_dct8x8col_cn.c --obj_directory $(OBJDIR) vcop_dct8x8col_cn.obj 

eve_dct8x8col_tb.obj: .\eve_dct8x8col_tb.c
	$(CC) $(CFLAGS) .\eve_dct8x8col_tb.c --obj_directory $(OBJDIR) eve_dct8x8col_tb.obj

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR) || cd $(OBJDIR)

clean :
	if exist $(OBJDIR) @rmdir/s/q $(OBJDIR)  
	del $(OBJDIR)\*.obj $(OBJDIR)\*.out
