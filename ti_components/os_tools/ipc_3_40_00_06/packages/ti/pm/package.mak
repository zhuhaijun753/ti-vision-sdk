#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = ti/pm
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/utils.js:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/utils.js
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/xdc.tci:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/xdc.tci
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/template.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/template.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/om2.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/om2.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/xmlgen.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/xmlgen.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/xmlgen2.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/xmlgen2.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/Warnings.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/Warnings.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/IPackage.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/IPackage.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/package.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/package.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/services/global/Clock.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/services/global/Clock.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/services/global/Trace.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/services/global/Trace.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/bld.js:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/bld.js
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/BuildEnvironment.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/BuildEnvironment.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/PackageContents.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/PackageContents.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/_gen.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/_gen.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Library.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Library.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Executable.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Executable.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Repository.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Repository.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Configuration.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Configuration.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Script.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Script.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Manifest.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Manifest.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Utils.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/Utils.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/ITarget.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/ITarget.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/ITarget2.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/ITarget2.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/ITarget3.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/ITarget3.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/ITargetFilter.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/ITargetFilter.xs
/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/package.xs:
package.mak: /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages/xdc/bld/package.xs
/datalocal1/ti_components/os_tools/ipc_3_40_00_06/ipc-bios.bld:
package.mak: /datalocal1/ti_components/os_tools/ipc_3_40_00_06/ipc-bios.bld
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/ITarget.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/ITarget.xs
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/C28_large.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/C28_large.xs
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/C28_float.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/C28_float.xs
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/package.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/package.xs
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arm/elf/IArm.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arm/elf/IArm.xs
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arm/elf/package.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arm/elf/package.xs
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/elf/ITarget.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/elf/ITarget.xs
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/elf/package.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/elf/package.xs
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arp32/elf/IARP32.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arp32/elf/IARP32.xs
/datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arp32/elf/package.xs:
package.mak: /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arp32/elf/package.xs
package.mak: package.bld
endif

ti.targets.arm.elf.M4.rootDir ?= /datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5
ti.targets.arm.elf.packageBase ?= /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/arm/elf/
ti.targets.elf.C66.rootDir ?= /datalocal1/ti_components/cg_tools/linux/c6000_7_4_2
ti.targets.elf.packageBase ?= /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages/ti/targets/elf/
.PRECIOUS: $(XDCCFGDIR)/%.oem4
.PHONY: all,em4 .dlls,em4 .executables,em4 test,em4
all,em4: .executables,em4
.executables,em4: .libraries,em4
.executables,em4: .dlls,em4
.dlls,em4: .libraries,em4
.libraries,em4: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,em4
	@$(ECHO) xdc .executables,em4
	@$(ECHO) xdc .libraries,em4
	@$(ECHO) xdc .dlls,em4

.PRECIOUS: $(XDCCFGDIR)/%.oe66
.PHONY: all,e66 .dlls,e66 .executables,e66 test,e66
all,e66: .executables,e66
.executables,e66: .libraries,e66
.executables,e66: .dlls,e66
.dlls,e66: .libraries,e66
.libraries,e66: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,e66
	@$(ECHO) xdc .executables,e66
	@$(ECHO) xdc .libraries,e66
	@$(ECHO) xdc .dlls,e66

all,earp32 clean,earp32 .libraries,earp32 .dlls,earp32 .executables,earp32 test,earp32:;

all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_ti.pm.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package ti.pm" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

ifeq (,$(MK_NOGENDEPS))
-include package/package.cfg.dep
endif

package/package.cfg.xdc.inc: .interfaces $(XDCROOT)/packages/xdc/cfg/cfginc.js package.xdc
	@$(MSG) generating schema include file list ...
	$(CONFIG) -f $(XDCROOT)/packages/xdc/cfg/cfginc.js ti.pm $@

.libraries,em4 .libraries: lib/debug/ti.pm_smp_omap5.aem4

-include lib/debug/ti.pm_smp_omap5.aem4.mak
lib/debug/ti.pm_smp_omap5.aem4: 
	$(RM) $@
	@$(MSG) archiving package/lib/debug/ti.pm_smp_omap5/package/package_ti.pm.oem4 package/lib/debug/ti.pm_smp_omap5/IpcPower.oem4  into $@ ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armar  rq $@   package/lib/debug/ti.pm_smp_omap5/package/package_ti.pm.oem4 package/lib/debug/ti.pm_smp_omap5/IpcPower.oem4 
lib/debug/ti.pm_smp_omap5.aem4: export C_DIR=
lib/debug/ti.pm_smp_omap5.aem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 clean::
	-$(RM) lib/debug/ti.pm_smp_omap5.aem4
.libraries,em4 .libraries: lib/debug/ti.pm_smp_vayu.aem4

-include lib/debug/ti.pm_smp_vayu.aem4.mak
lib/debug/ti.pm_smp_vayu.aem4: 
	$(RM) $@
	@$(MSG) archiving package/lib/debug/ti.pm_smp_vayu/package/package_ti.pm.oem4 package/lib/debug/ti.pm_smp_vayu/IpcPower.oem4  into $@ ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armar  rq $@   package/lib/debug/ti.pm_smp_vayu/package/package_ti.pm.oem4 package/lib/debug/ti.pm_smp_vayu/IpcPower.oem4 
lib/debug/ti.pm_smp_vayu.aem4: export C_DIR=
lib/debug/ti.pm_smp_vayu.aem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 clean::
	-$(RM) lib/debug/ti.pm_smp_vayu.aem4
.libraries,em4 .libraries: lib/release/ti.pm_smp_omap5.aem4

-include lib/release/ti.pm_smp_omap5.aem4.mak
lib/release/ti.pm_smp_omap5.aem4: 
	$(RM) $@
	@$(MSG) archiving package/lib/release/ti.pm_smp_omap5/package/package_ti.pm.oem4 package/lib/release/ti.pm_smp_omap5/IpcPower.oem4  into $@ ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armar  rq $@   package/lib/release/ti.pm_smp_omap5/package/package_ti.pm.oem4 package/lib/release/ti.pm_smp_omap5/IpcPower.oem4 
lib/release/ti.pm_smp_omap5.aem4: export C_DIR=
lib/release/ti.pm_smp_omap5.aem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 clean::
	-$(RM) lib/release/ti.pm_smp_omap5.aem4
.libraries,em4 .libraries: lib/release/ti.pm_smp_vayu.aem4

-include lib/release/ti.pm_smp_vayu.aem4.mak
lib/release/ti.pm_smp_vayu.aem4: 
	$(RM) $@
	@$(MSG) archiving package/lib/release/ti.pm_smp_vayu/package/package_ti.pm.oem4 package/lib/release/ti.pm_smp_vayu/IpcPower.oem4  into $@ ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armar  rq $@   package/lib/release/ti.pm_smp_vayu/package/package_ti.pm.oem4 package/lib/release/ti.pm_smp_vayu/IpcPower.oem4 
lib/release/ti.pm_smp_vayu.aem4: export C_DIR=
lib/release/ti.pm_smp_vayu.aem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 clean::
	-$(RM) lib/release/ti.pm_smp_vayu.aem4
.libraries,e66 .libraries: lib/debug/ti.pm_vayu.ae66

-include lib/debug/ti.pm_vayu.ae66.mak
lib/debug/ti.pm_vayu.ae66: 
	$(RM) $@
	@$(MSG) archiving package/lib/debug/ti.pm_vayu/package/package_ti.pm.oe66 package/lib/debug/ti.pm_vayu/IpcPowerDsp_dra7xx.oe66 package/lib/debug/ti.pm_vayu/IpcPowerDsp_idle_dra7xx.oe66  into $@ ...
	$(ti.targets.elf.C66.rootDir)/bin/ar6x  rq $@   package/lib/debug/ti.pm_vayu/package/package_ti.pm.oe66 package/lib/debug/ti.pm_vayu/IpcPowerDsp_dra7xx.oe66 package/lib/debug/ti.pm_vayu/IpcPowerDsp_idle_dra7xx.oe66 
lib/debug/ti.pm_vayu.ae66: export C_DIR=
lib/debug/ti.pm_vayu.ae66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

clean,e66 clean::
	-$(RM) lib/debug/ti.pm_vayu.ae66
.libraries,e66 .libraries: lib/release/ti.pm_vayu.ae66

-include lib/release/ti.pm_vayu.ae66.mak
lib/release/ti.pm_vayu.ae66: 
	$(RM) $@
	@$(MSG) archiving package/lib/release/ti.pm_vayu/package/package_ti.pm.oe66 package/lib/release/ti.pm_vayu/IpcPowerDsp_dra7xx.oe66 package/lib/release/ti.pm_vayu/IpcPowerDsp_idle_dra7xx.oe66  into $@ ...
	$(ti.targets.elf.C66.rootDir)/bin/ar6x  rq $@   package/lib/release/ti.pm_vayu/package/package_ti.pm.oe66 package/lib/release/ti.pm_vayu/IpcPowerDsp_dra7xx.oe66 package/lib/release/ti.pm_vayu/IpcPowerDsp_idle_dra7xx.oe66 
lib/release/ti.pm_vayu.ae66: export C_DIR=
lib/release/ti.pm_vayu.ae66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

clean,e66 clean::
	-$(RM) lib/release/ti.pm_vayu.ae66
.libraries,em4 .libraries: lib/debug/ti.pm_null.aem4

-include lib/debug/ti.pm_null.aem4.mak
lib/debug/ti.pm_null.aem4: 
	$(RM) $@
	@$(MSG) archiving package/lib/debug/ti.pm_null/package/package_ti.pm.oem4 package/lib/debug/ti.pm_null/IpcPower_null.oem4  into $@ ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armar  rq $@   package/lib/debug/ti.pm_null/package/package_ti.pm.oem4 package/lib/debug/ti.pm_null/IpcPower_null.oem4 
lib/debug/ti.pm_null.aem4: export C_DIR=
lib/debug/ti.pm_null.aem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 clean::
	-$(RM) lib/debug/ti.pm_null.aem4
.libraries,em4 .libraries: lib/release/ti.pm_null.aem4

-include lib/release/ti.pm_null.aem4.mak
lib/release/ti.pm_null.aem4: 
	$(RM) $@
	@$(MSG) archiving package/lib/release/ti.pm_null/package/package_ti.pm.oem4 package/lib/release/ti.pm_null/IpcPower_null.oem4  into $@ ...
	$(ti.targets.arm.elf.M4.rootDir)/bin/armar  rq $@   package/lib/release/ti.pm_null/package/package_ti.pm.oem4 package/lib/release/ti.pm_null/IpcPower_null.oem4 
lib/release/ti.pm_null.aem4: export C_DIR=
lib/release/ti.pm_null.aem4: PATH:=$(ti.targets.arm.elf.M4.rootDir)/bin/:$(PATH)

clean,em4 clean::
	-$(RM) lib/release/ti.pm_null.aem4
.libraries,e66 .libraries: lib/debug/ti.pm_null.ae66

-include lib/debug/ti.pm_null.ae66.mak
lib/debug/ti.pm_null.ae66: 
	$(RM) $@
	@$(MSG) archiving package/lib/debug/ti.pm_null/package/package_ti.pm.oe66 package/lib/debug/ti.pm_null/IpcPower_null.oe66  into $@ ...
	$(ti.targets.elf.C66.rootDir)/bin/ar6x  rq $@   package/lib/debug/ti.pm_null/package/package_ti.pm.oe66 package/lib/debug/ti.pm_null/IpcPower_null.oe66 
lib/debug/ti.pm_null.ae66: export C_DIR=
lib/debug/ti.pm_null.ae66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

clean,e66 clean::
	-$(RM) lib/debug/ti.pm_null.ae66
.libraries,e66 .libraries: lib/release/ti.pm_null.ae66

-include lib/release/ti.pm_null.ae66.mak
lib/release/ti.pm_null.ae66: 
	$(RM) $@
	@$(MSG) archiving package/lib/release/ti.pm_null/package/package_ti.pm.oe66 package/lib/release/ti.pm_null/IpcPower_null.oe66  into $@ ...
	$(ti.targets.elf.C66.rootDir)/bin/ar6x  rq $@   package/lib/release/ti.pm_null/package/package_ti.pm.oe66 package/lib/release/ti.pm_null/IpcPower_null.oe66 
lib/release/ti.pm_null.ae66: export C_DIR=
lib/release/ti.pm_null.ae66: PATH:=$(ti.targets.elf.C66.rootDir)/bin/:$(PATH)

clean,e66 clean::
	-$(RM) lib/release/ti.pm_null.ae66
test:;
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
.PHONY: package_ti.pm.oem4,copy
package_ti.pm.oem4,copy : package_ti.pm.oem4,0,copy package_ti.pm.oem4,1,copy package_ti.pm.oem4,2,copy package_ti.pm.oem4,3,copy package_ti.pm.oem4,4,copy package_ti.pm.oem4,5,copy 
	@

package_ti.pm.oem4,0,copy : package/lib/debug/ti.pm_null/package/package_ti.pm.oem4
package_ti.pm.oem4,1,copy : package/lib/debug/ti.pm_smp_omap5/package/package_ti.pm.oem4
package_ti.pm.oem4,2,copy : package/lib/debug/ti.pm_smp_vayu/package/package_ti.pm.oem4
package_ti.pm.oem4,3,copy : package/lib/release/ti.pm_null/package/package_ti.pm.oem4
package_ti.pm.oem4,4,copy : package/lib/release/ti.pm_smp_omap5/package/package_ti.pm.oem4
package_ti.pm.oem4,5,copy : package/lib/release/ti.pm_smp_vayu/package/package_ti.pm.oem4
.PHONY: package_ti.pm.sem4,copy
package_ti.pm.sem4,copy : package_ti.pm.sem4,0,copy package_ti.pm.sem4,1,copy package_ti.pm.sem4,2,copy package_ti.pm.sem4,3,copy package_ti.pm.sem4,4,copy package_ti.pm.sem4,5,copy 
	@

package_ti.pm.sem4,0,copy : package/lib/debug/ti.pm_null/package/package_ti.pm.sem4
package_ti.pm.sem4,1,copy : package/lib/debug/ti.pm_smp_omap5/package/package_ti.pm.sem4
package_ti.pm.sem4,2,copy : package/lib/debug/ti.pm_smp_vayu/package/package_ti.pm.sem4
package_ti.pm.sem4,3,copy : package/lib/release/ti.pm_null/package/package_ti.pm.sem4
package_ti.pm.sem4,4,copy : package/lib/release/ti.pm_smp_omap5/package/package_ti.pm.sem4
package_ti.pm.sem4,5,copy : package/lib/release/ti.pm_smp_vayu/package/package_ti.pm.sem4
.PHONY: IpcPower.oem4,copy
IpcPower.oem4,copy : IpcPower.oem4,0,copy IpcPower.oem4,1,copy IpcPower.oem4,2,copy IpcPower.oem4,3,copy 
	@

IpcPower.oem4,0,copy : package/lib/debug/ti.pm_smp_omap5/IpcPower.oem4
IpcPower.oem4,1,copy : package/lib/debug/ti.pm_smp_vayu/IpcPower.oem4
IpcPower.oem4,2,copy : package/lib/release/ti.pm_smp_omap5/IpcPower.oem4
IpcPower.oem4,3,copy : package/lib/release/ti.pm_smp_vayu/IpcPower.oem4
.PHONY: IpcPower.sem4,copy
IpcPower.sem4,copy : IpcPower.sem4,0,copy IpcPower.sem4,1,copy IpcPower.sem4,2,copy IpcPower.sem4,3,copy 
	@

IpcPower.sem4,0,copy : package/lib/debug/ti.pm_smp_omap5/IpcPower.sem4
IpcPower.sem4,1,copy : package/lib/debug/ti.pm_smp_vayu/IpcPower.sem4
IpcPower.sem4,2,copy : package/lib/release/ti.pm_smp_omap5/IpcPower.sem4
IpcPower.sem4,3,copy : package/lib/release/ti.pm_smp_vayu/IpcPower.sem4
.PHONY: package_ti.pm.oe66,copy
package_ti.pm.oe66,copy : package_ti.pm.oe66,0,copy package_ti.pm.oe66,1,copy package_ti.pm.oe66,2,copy package_ti.pm.oe66,3,copy 
	@

package_ti.pm.oe66,0,copy : package/lib/debug/ti.pm_null/package/package_ti.pm.oe66
package_ti.pm.oe66,1,copy : package/lib/debug/ti.pm_vayu/package/package_ti.pm.oe66
package_ti.pm.oe66,2,copy : package/lib/release/ti.pm_null/package/package_ti.pm.oe66
package_ti.pm.oe66,3,copy : package/lib/release/ti.pm_vayu/package/package_ti.pm.oe66
.PHONY: package_ti.pm.se66,copy
package_ti.pm.se66,copy : package_ti.pm.se66,0,copy package_ti.pm.se66,1,copy package_ti.pm.se66,2,copy package_ti.pm.se66,3,copy 
	@

package_ti.pm.se66,0,copy : package/lib/debug/ti.pm_null/package/package_ti.pm.se66
package_ti.pm.se66,1,copy : package/lib/debug/ti.pm_vayu/package/package_ti.pm.se66
package_ti.pm.se66,2,copy : package/lib/release/ti.pm_null/package/package_ti.pm.se66
package_ti.pm.se66,3,copy : package/lib/release/ti.pm_vayu/package/package_ti.pm.se66
.PHONY: IpcPowerDsp_dra7xx.oe66,copy
IpcPowerDsp_dra7xx.oe66,copy : IpcPowerDsp_dra7xx.oe66,0,copy IpcPowerDsp_dra7xx.oe66,1,copy 
	@

IpcPowerDsp_dra7xx.oe66,0,copy : package/lib/debug/ti.pm_vayu/IpcPowerDsp_dra7xx.oe66
IpcPowerDsp_dra7xx.oe66,1,copy : package/lib/release/ti.pm_vayu/IpcPowerDsp_dra7xx.oe66
.PHONY: IpcPowerDsp_dra7xx.se66,copy
IpcPowerDsp_dra7xx.se66,copy : IpcPowerDsp_dra7xx.se66,0,copy IpcPowerDsp_dra7xx.se66,1,copy 
	@

IpcPowerDsp_dra7xx.se66,0,copy : package/lib/debug/ti.pm_vayu/IpcPowerDsp_dra7xx.se66
IpcPowerDsp_dra7xx.se66,1,copy : package/lib/release/ti.pm_vayu/IpcPowerDsp_dra7xx.se66
.PHONY: IpcPowerDsp_idle_dra7xx.oe66,copy
IpcPowerDsp_idle_dra7xx.oe66,copy : IpcPowerDsp_idle_dra7xx.oe66,0,copy IpcPowerDsp_idle_dra7xx.oe66,1,copy 
	@

IpcPowerDsp_idle_dra7xx.oe66,0,copy : package/lib/debug/ti.pm_vayu/IpcPowerDsp_idle_dra7xx.oe66
IpcPowerDsp_idle_dra7xx.oe66,1,copy : package/lib/release/ti.pm_vayu/IpcPowerDsp_idle_dra7xx.oe66
.PHONY: IpcPower_null.oem4,copy
IpcPower_null.oem4,copy : IpcPower_null.oem4,0,copy IpcPower_null.oem4,1,copy 
	@

IpcPower_null.oem4,0,copy : package/lib/debug/ti.pm_null/IpcPower_null.oem4
IpcPower_null.oem4,1,copy : package/lib/release/ti.pm_null/IpcPower_null.oem4
.PHONY: IpcPower_null.sem4,copy
IpcPower_null.sem4,copy : IpcPower_null.sem4,0,copy IpcPower_null.sem4,1,copy 
	@

IpcPower_null.sem4,0,copy : package/lib/debug/ti.pm_null/IpcPower_null.sem4
IpcPower_null.sem4,1,copy : package/lib/release/ti.pm_null/IpcPower_null.sem4
.PHONY: IpcPower_null.oe66,copy
IpcPower_null.oe66,copy : IpcPower_null.oe66,0,copy IpcPower_null.oe66,1,copy 
	@

IpcPower_null.oe66,0,copy : package/lib/debug/ti.pm_null/IpcPower_null.oe66
IpcPower_null.oe66,1,copy : package/lib/release/ti.pm_null/IpcPower_null.oe66
.PHONY: IpcPower_null.se66,copy
IpcPower_null.se66,copy : IpcPower_null.se66,0,copy IpcPower_null.se66,1,copy 
	@

IpcPower_null.se66,0,copy : package/lib/debug/ti.pm_null/IpcPower_null.se66
IpcPower_null.se66,1,copy : package/lib/release/ti.pm_null/IpcPower_null.se66

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg $(XDCROOT)/packages/xdc/cfg/Main.xs | .interfaces
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,ti_pm
ifeq (,$(MK_NOGENDEPS))
-include package/rel/ti_pm.tar.gz.dep
endif
package/rel/ti_pm/ti/pm/package/package.rel.xml: package/package.bld.xml
package/rel/ti_pm/ti/pm/package/package.rel.xml: package/build.cfg
package/rel/ti_pm/ti/pm/package/package.rel.xml: package/package.xdc.inc
package/rel/ti_pm/ti/pm/package/package.rel.xml: IpcPower.h
package/rel/ti_pm/ti/pm/package/package.rel.xml: _IpcPower.h
package/rel/ti_pm/ti/pm/package/package.rel.xml: package.bld
package/rel/ti_pm/ti/pm/package/package.rel.xml: package/package.cfg.xdc.inc
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/debug/ti.pm_smp_omap5.aem4
package/rel/ti_pm/ti/pm/package/package.rel.xml: package/package_ti.pm.c
package/rel/ti_pm/ti/pm/package/package.rel.xml: IpcPower.c
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/debug/ti.pm_smp_vayu.aem4
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/release/ti.pm_smp_omap5.aem4
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/release/ti.pm_smp_vayu.aem4
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/debug/ti.pm_vayu.ae66
package/rel/ti_pm/ti/pm/package/package.rel.xml: IpcPowerDsp_dra7xx.c
package/rel/ti_pm/ti/pm/package/package.rel.xml: IpcPowerDsp_idle_dra7xx.s66
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/release/ti.pm_vayu.ae66
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/debug/ti.pm_null.aem4
package/rel/ti_pm/ti/pm/package/package.rel.xml: IpcPower_null.c
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/release/ti.pm_null.aem4
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/debug/ti.pm_null.ae66
package/rel/ti_pm/ti/pm/package/package.rel.xml: lib/release/ti.pm_null.ae66
package/rel/ti_pm/ti/pm/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

ti_pm.tar.gz: package/rel/ti_pm.xdc.inc package/rel/ti_pm/ti/pm/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/ti_pm.xdc.inc,package/rel/ti_pm.tar.gz.dep)


release release,ti_pm: all ti_pm.tar.gz
clean:: .clean
	-$(RM) ti_pm.tar.gz
	-$(RM) package/rel/ti_pm.xdc.inc
	-$(RM) package/rel/ti_pm.tar.gz.dep

clean:: .clean
	-$(RM) .libraries $(wildcard .libraries,*)
clean:: 
	-$(RM) .dlls $(wildcard .dlls,*)
#
# The following clean rule removes user specified
# generated files or directories.
#
	-$(RMDIR) lib/
	-$(RMDIR) lib/

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard lib))
    $(shell $(MKDIR) lib)
endif
ifeq (,$(wildcard lib/debug))
    $(shell $(MKDIR) lib/debug)
endif
ifeq (,$(wildcard lib/release))
    $(shell $(MKDIR) lib/release)
endif
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/lib/debug))
    $(shell $(MKDIR) package/lib/debug)
endif
ifeq (,$(wildcard package/lib/debug/ti.pm_smp_omap5))
    $(shell $(MKDIR) package/lib/debug/ti.pm_smp_omap5)
endif
ifeq (,$(wildcard package/lib/debug/ti.pm_smp_omap5/package))
    $(shell $(MKDIR) package/lib/debug/ti.pm_smp_omap5/package)
endif
ifeq (,$(wildcard package/lib/debug/ti.pm_smp_vayu))
    $(shell $(MKDIR) package/lib/debug/ti.pm_smp_vayu)
endif
ifeq (,$(wildcard package/lib/debug/ti.pm_smp_vayu/package))
    $(shell $(MKDIR) package/lib/debug/ti.pm_smp_vayu/package)
endif
ifeq (,$(wildcard package/lib/release))
    $(shell $(MKDIR) package/lib/release)
endif
ifeq (,$(wildcard package/lib/release/ti.pm_smp_omap5))
    $(shell $(MKDIR) package/lib/release/ti.pm_smp_omap5)
endif
ifeq (,$(wildcard package/lib/release/ti.pm_smp_omap5/package))
    $(shell $(MKDIR) package/lib/release/ti.pm_smp_omap5/package)
endif
ifeq (,$(wildcard package/lib/release/ti.pm_smp_vayu))
    $(shell $(MKDIR) package/lib/release/ti.pm_smp_vayu)
endif
ifeq (,$(wildcard package/lib/release/ti.pm_smp_vayu/package))
    $(shell $(MKDIR) package/lib/release/ti.pm_smp_vayu/package)
endif
ifeq (,$(wildcard package/lib/debug/ti.pm_vayu))
    $(shell $(MKDIR) package/lib/debug/ti.pm_vayu)
endif
ifeq (,$(wildcard package/lib/debug/ti.pm_vayu/package))
    $(shell $(MKDIR) package/lib/debug/ti.pm_vayu/package)
endif
ifeq (,$(wildcard package/lib/release/ti.pm_vayu))
    $(shell $(MKDIR) package/lib/release/ti.pm_vayu)
endif
ifeq (,$(wildcard package/lib/release/ti.pm_vayu/package))
    $(shell $(MKDIR) package/lib/release/ti.pm_vayu/package)
endif
ifeq (,$(wildcard package/lib/debug/ti.pm_null))
    $(shell $(MKDIR) package/lib/debug/ti.pm_null)
endif
ifeq (,$(wildcard package/lib/debug/ti.pm_null/package))
    $(shell $(MKDIR) package/lib/debug/ti.pm_null/package)
endif
ifeq (,$(wildcard package/lib/release/ti.pm_null))
    $(shell $(MKDIR) package/lib/release/ti.pm_null)
endif
ifeq (,$(wildcard package/lib/release/ti.pm_null/package))
    $(shell $(MKDIR) package/lib/release/ti.pm_null/package)
endif
endif
clean::
	-$(RMDIR) package

