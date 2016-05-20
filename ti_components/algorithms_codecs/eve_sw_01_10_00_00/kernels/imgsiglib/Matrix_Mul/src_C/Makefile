# /*==========================================================================*/
# /*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
# /*                      All Rights Reserved                                 */
# /*==========================================================================*/
OBJDIR = "..\elf_out"

ARP32_TOOLS ?= "C:\Program Files\Texas Instruments\ARP32_tools"
CC=$(ARP32_TOOLS)\bin\cl-arp32.exe
LN=$(ARP32_TOOLS)\bin\lnk-arp32.exe

SHARED_OBJECTS= vcop_mat_mul_cn.obj eve_mat_mul_tb.obj 

CFLAGS =   -I $(ARP32_TOOLS)\include -I ..\inc\ -c --silicon_version=v210
CDFLAGS =  -g -I $(ARP32_TOOLS)\include -I ..\inc\ -c --silicon_version=v210
LFLAGS =  -c -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib

# location of eve files
EDEN_INCLUDE = "\..\..\common\libCeden\inc\eve1"
LIBCEDEN = "c:\GForge\eve_sw_dev\QT_kernels\common\libCeden\lib\eve1\libCeden_eve1.lib"
EVE_LIB = $(ARP32_TOOLS)\lib\rtsarp32_v200.lib
EVE_LCF ="..\..\..\common\linker.cmd" 
LFLAGS =  -c -l $(ARP32_TOOLS)\lib\rtsarp32_v200.lib

all: $(OBJDIR) vcop_mat_mul_C.out
#-l$(LIBCEDEN)	
vcop_mat_mul_C.out: $(SHARED_OBJECTS) 
	${LN} $(OBJDIR)\vcop_mat_mul_cn.obj $(OBJDIR)\eve_mat_mul_tb.obj  -l$(EVE_LCF) -l$(EVE_LIB) -l ..\..\..\common\boot_arp32.obj -o $(OBJDIR)\vcop_mat_mul_C.out -m $(OBJDIR)\apps.map 


vcop_mat_mul_cn.obj: .\vcop_mat_mul_cn.c
	$(CC) $(CDFLAGS) .\vcop_mat_mul_cn.c --obj_directory $(OBJDIR) vcop_mat_mul_cn.obj 

eve_mat_mul_tb.obj: .\eve_mat_mul_tb.c
	$(CC) $(CDFLAGS) .\eve_mat_mul_tb.c --obj_directory $(OBJDIR) eve_mat_mul_tb.obj

$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR) || cd $(OBJDIR)

clean :
	if exist $(OBJDIR) @rmdir/s/q $(OBJDIR)  
	del $(OBJDIR)\*.obj $(OBJDIR)\*.out
