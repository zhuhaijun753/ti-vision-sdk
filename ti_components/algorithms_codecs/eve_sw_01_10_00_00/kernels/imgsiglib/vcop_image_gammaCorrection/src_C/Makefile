# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
OBJDIR = "..\elf_out"

ARP32_TOOLS ?= "C:\Program Files\Texas Instruments\ARP32_tools"
CC=$(ARP32_TOOLS)\bin\cl-arp32.exe
LN=$(ARP32_TOOLS)\bin\lnk-arp32.exe

SHARED_OBJECTS= vcop_gammaCorrection_cn.obj vcop_gamma_correction_tb.obj 

CFLAGS  =  -g -I $(ARP32_TOOLS)\include -I ..\inc\ -c --silicon_version=v210 
CDFLAGS =  -g -I $(ARP32_TOOLS)\include -I ..\inc\ -c  --silicon_version=v210
LFLAGS =  -c -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib


all: $(OBJDIR) vcop_gammaCorrection.out

vcop_gammaCorrection.out: $(SHARED_OBJECTS) 
	${LN} $(OBJDIR)\vcop_gammaCorrection_cn.obj $(OBJDIR)\vcop_gamma_correction_tb.obj $(LFLAGS) -o $(OBJDIR)\vcop_gammaCorrection.out -l ..\..\..\common\linker.cmd -l ..\..\..\common\boot_arp32.obj -m $(OBJDIR)\apps.map 

vcop_gammaCorrection_cn.obj: .\vcop_gammaCorrection_cn.c
	$(CC) $(CFLAGS) .\vcop_gammaCorrection_cn.c --obj_directory $(OBJDIR) vcop_gammaCorrection_cn.obj 

vcop_gamma_correction_tb.obj: .\vcop_gamma_correction_tb.c
	$(CC) $(CDFLAGS) .\vcop_gamma_correction_tb.c --obj_directory $(OBJDIR) vcop_gamma_correction_tb.obj

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR) || cd $(OBJDIR)

clean :  
	if exist $(OBJDIR) @rmdir/s/q $(OBJDIR)
