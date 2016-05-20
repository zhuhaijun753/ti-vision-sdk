#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages
override XDCROOT = /datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core
override XDCBUILDCFG = /datalocal1/ti_components/os_tools/ipc_3_40_00_06/ipc-bios.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = PLATFORM="DRA7XX" BIOS_SMPENABLED="1" ti.targets.C28_large="" ti.targets.C28_float="" ti.targets.C64P="" ti.targets.C64P_big_endian="" ti.targets.C674="" ti.targets.arm.elf.Arm9="" ti.targets.arm.elf.A8F="" ti.targets.arm.elf.A8Fnv="" ti.targets.arm.elf.M3="" ti.targets.arm.elf.M4="/datalocal1/ti_components/cg_tools/linux/ti-cgt-arm_5.2.5" ti.targets.arm.elf.M4F="" ti.targets.elf.C64P="" ti.targets.elf.C64P_big_endian="" ti.targets.elf.C64T="" ti.targets.elf.C66="/datalocal1/ti_components/cg_tools/linux/c6000_7_4_2" ti.targets.elf.C66_big_endian="" ti.targets.elf.C674="" ti.targets.arp32.elf.ARP32="/datalocal1/ti_components/cg_tools/linux/arp32_1_0_6" ti.targets.arp32.elf.ARP32_far="" gnu.targets.arm.A8F="" gnu.targets.arm.A15F="" GOAL=release
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /datalocal1/ti_components/os_tools/bios_6_42_02_29/packages;/datalocal1/ti_components/os_tools/linux/xdctools_3_31_02_38_core/packages;../../../../..
HOSTOS = Linux
endif
