#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.arm.elf.M4{1,0,5.2,5
#
ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.oem4.dep
package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.oem4.dep: ;
endif

package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.oem4: | .interfaces
package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.oem4: package/package_ti.sdo.fc.ires.hdvicp.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2/package -fr=./package/lib/lib/debug/hdvicp2/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2/package -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2/package -fr=./package/lib/lib/debug/hdvicp2/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.oem4: export C_DIR=
package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.sem4: | .interfaces
package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.sem4: package/package_ti.sdo.fc.ires.hdvicp.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2/package -fr=./package/lib/lib/debug/hdvicp2/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2/package -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2/package -fr=./package/lib/lib/debug/hdvicp2/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.sem4: export C_DIR=
package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/hdvicp2/iresman_hdvicp2.oem4.dep
package/lib/lib/debug/hdvicp2/iresman_hdvicp2.oem4.dep: ;
endif

package/lib/lib/debug/hdvicp2/iresman_hdvicp2.oem4: | .interfaces
package/lib/lib/debug/hdvicp2/iresman_hdvicp2.oem4: iresman_hdvicp2.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2 -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/iresman_hdvicp2.oem4: export C_DIR=
package/lib/lib/debug/hdvicp2/iresman_hdvicp2.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/debug/hdvicp2/iresman_hdvicp2.sem4: | .interfaces
package/lib/lib/debug/hdvicp2/iresman_hdvicp2.sem4: iresman_hdvicp2.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2 -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/iresman_hdvicp2.sem4: export C_DIR=
package/lib/lib/debug/hdvicp2/iresman_hdvicp2.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/hdvicp2/ires_hdvicp2.oem4.dep
package/lib/lib/debug/hdvicp2/ires_hdvicp2.oem4.dep: ;
endif

package/lib/lib/debug/hdvicp2/ires_hdvicp2.oem4: | .interfaces
package/lib/lib/debug/hdvicp2/ires_hdvicp2.oem4: ires_hdvicp2.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2 -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/ires_hdvicp2.oem4: export C_DIR=
package/lib/lib/debug/hdvicp2/ires_hdvicp2.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/debug/hdvicp2/ires_hdvicp2.sem4: | .interfaces
package/lib/lib/debug/hdvicp2/ires_hdvicp2.sem4: ires_hdvicp2.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2 -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/ires_hdvicp2.sem4: export C_DIR=
package/lib/lib/debug/hdvicp2/ires_hdvicp2.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.oem4.dep
package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.oem4.dep: ;
endif

package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.oem4: | .interfaces
package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.oem4: iresman_hdvicp2_setup.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2 -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.oem4: export C_DIR=
package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.sem4: | .interfaces
package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.sem4: iresman_hdvicp2_setup.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2 -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.sem4: export C_DIR=
package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

ifeq (,$(MK_NOGENDEPS))
-include package/lib/lib/debug/hdvicp2/hdvicp2cfg.oem4.dep
package/lib/lib/debug/hdvicp2/hdvicp2cfg.oem4.dep: ;
endif

package/lib/lib/debug/hdvicp2/hdvicp2cfg.oem4: | .interfaces
package/lib/lib/debug/hdvicp2/hdvicp2cfg.oem4: hdvicp2cfg.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c  -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2 -s oem4 $< -C   -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/hdvicp2cfg.oem4: export C_DIR=
package/lib/lib/debug/hdvicp2/hdvicp2cfg.oem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

package/lib/lib/debug/hdvicp2/hdvicp2cfg.sem4: | .interfaces
package/lib/lib/debug/hdvicp2/hdvicp2cfg.sem4: hdvicp2cfg.c lib/debug/hdvicp2.aem4.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clem4 -n $< ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armcl -c -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2 -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/debug/hdvicp2 -s oem4 $< -C  -n -s --symdebug:none -qq -pdsw225 --endian=little -mv7M4 --float_support=vfplib --abi=eabi -eo.oem4 -ea.sem4  --symdebug:none -ms --gcc -O3 -D___DSPBIOS___ -D___DUCATI_FW___ -DPLATFORM_EVM_SI -DUTILS_ASSERT_ENABLE -D_DEBUG_=1 -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_5_2_5 --symdebug:dwarf  $(XDCINCS) -I$(ti.targets.arm.elf.M4.rootDir)/include/rts -I$(ti.targets.arm.elf.M4.rootDir)/include  -fs=./package/lib/lib/debug/hdvicp2 -fr=./package/lib/lib/debug/hdvicp2
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/debug/hdvicp2/hdvicp2cfg.sem4: export C_DIR=
package/lib/lib/debug/hdvicp2/hdvicp2cfg.sem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 ::
	-$(RM) package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.oem4
	-$(RM) package/lib/lib/debug/hdvicp2/iresman_hdvicp2.oem4
	-$(RM) package/lib/lib/debug/hdvicp2/ires_hdvicp2.oem4
	-$(RM) package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.oem4
	-$(RM) package/lib/lib/debug/hdvicp2/hdvicp2cfg.oem4
	-$(RM) package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.sem4
	-$(RM) package/lib/lib/debug/hdvicp2/iresman_hdvicp2.sem4
	-$(RM) package/lib/lib/debug/hdvicp2/ires_hdvicp2.sem4
	-$(RM) package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.sem4
	-$(RM) package/lib/lib/debug/hdvicp2/hdvicp2cfg.sem4

lib/debug/hdvicp2.aem4: package/lib/lib/debug/hdvicp2/package/package_ti.sdo.fc.ires.hdvicp.oem4 package/lib/lib/debug/hdvicp2/iresman_hdvicp2.oem4 package/lib/lib/debug/hdvicp2/ires_hdvicp2.oem4 package/lib/lib/debug/hdvicp2/iresman_hdvicp2_setup.oem4 package/lib/lib/debug/hdvicp2/hdvicp2cfg.oem4 lib/debug/hdvicp2.aem4.mak

clean::
	-$(RM) lib/debug/hdvicp2.aem4.mak