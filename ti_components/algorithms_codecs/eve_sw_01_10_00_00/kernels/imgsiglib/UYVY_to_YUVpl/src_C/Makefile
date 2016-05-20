# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/


OBJDIR = "..\elf_out"

ARP32_TOOLS ?= "C:\Program Files\Texas Instruments\ARP32_tools"
CC=$(ARP32_TOOLS)\bin\cl-arp32.exe
LN=$(ARP32_TOOLS)\bin\lnk-arp32.exe

SHARED_OBJECTS= UYVY_to_YUVpl_in_data.obj UYVY_to_YUVpl_out_data.obj UYVY_to_YUVpl_c.obj UYVY_to_YUVpl_tb.obj 

CFLAGS =  -g -I $(ARP32_TOOLS)\include -I ..\inc\ -c --silicon_version=v210 
LFLAGS =  -c -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib


all: $(OBJDIR) UYVY_to_YUVpl.out

UYVY_to_YUVpl.out: $(SHARED_OBJECTS) 
	${LN} $(OBJDIR)\UYVY_to_YUVpl_in_data.obj  $(OBJDIR)\UYVY_to_YUVpl_out_data.obj $(OBJDIR)\UYVY_to_YUVpl_c.obj $(OBJDIR)\UYVY_to_YUVpl_tb.obj $(LFLAGS) -o $(OBJDIR)\UYVY_to_YUVpl.out -l ..\..\..\common\linker.cmd -l ..\..\..\common\boot_arp32.obj -m $(OBJDIR)\apps.map 

UYVY_to_YUVpl_in_data.obj: ..\src_C\UYVY_to_YUVpl_in_data.c
	$(CC) $(CFLAGS) ..\src_C\UYVY_to_YUVpl_in_data.c --obj_directory $(OBJDIR) UYVY_to_YUVpl_in_data.obj

UYVY_to_YUVpl_out_data.obj: ..\src_C\UYVY_to_YUVpl_out_data.c
	$(CC) $(CFLAGS) ..\src_C\UYVY_to_YUVpl_out_data.c --obj_directory $(OBJDIR) UYVY_to_YUVpl_out_data.obj

UYVY_to_YUVpl_c.obj: .\UYVY_to_YUVpl_c.c
	$(CC) $(CFLAGS) .\UYVY_to_YUVpl_c.c --obj_directory $(OBJDIR) UYVY_to_YUVpl_c.obj 

UYVY_to_YUVpl_tb.obj: .\UYVY_to_YUVpl_tb.c
	$(CC) $(CFLAGS) .\UYVY_to_YUVpl_tb.c --obj_directory $(OBJDIR) UYVY_to_YUVpl_tb.obj

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR) || cd $(OBJDIR)

clean :  
	if exist $(OBJDIR) @rmdir/s/q $(OBJDIR)
