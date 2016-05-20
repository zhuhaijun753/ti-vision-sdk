
Steps to build
==============

- Open Rules.make

- Edit paths for the below variables according to your system environment

  In case of windows machine edit below paths,
  CODEGEN_PATH_M4 := C:/ti/tms470_5.0.4
  CODEGEN_PATH_M3 := C:/ti/tms470_5.0.4
  CODEGEN_PATH_DSP := C:/ti/C6000_7.4.2
  bsp_PATH := C:/ti/vayu_drivers/$(bsp_RELPATH)
  bios_PATH := C:/ti/bios_6_35_02_45
  xdc_PATH := C:/ti/xdctools_3_25_01_65
  starterware_PATH := C:/ti/starterware
  edma3_lld_PATH := C:/ti/edma3_lld_02_11_08_05

  In case of linux machine edit below paths,
  CODEGEN_PATH_M4 := /opt/tools/cgtools/TIARMCGT5.0.4
  CODEGEN_PATH_M3 := /opt/tools/cgtools/TIARMCGT5.0.4
  CODEGEN_PATH_DSP := /opt/tools/cgtools/C6000_7.4.2
  bsp_PATH := /opt/ti/bsp/$(bsp_RELPATH)
  bios_PATH := /opt/tools/bios6/bios_6_35_02_45
  xdc_PATH := /opt/tools/xdc/xdctools_3_25_01_65
  starterware_PATH := /opt/ti/starterware/starterware
  edma3_lld_PATH := /opt/tools/edma3/edma3_lld_02_11_08_05

  IMPORTANT:
  Make sure the paths specified above DO NOT have any spaces in them.

- Make sure "gmake" is in your system path.
  Typically when XDC is installed "gmake" is installed along with it and
  it becomes part of the system path by default.

- Open command prompt and type the below
  gmake -s all

  This will clean all and build all BSP drivers as well as all BSP
  examples

- TIP: Always use "-s" option with make to see user friendly prints
       during build.

- Optionally before build, edit the below in Rules.make file,
  depending on the kind of build you want to do:

  PLATFORM:=
  PROFILE_$(CORE):=

  Valid values for PLATFORM are:
  tda2xx-evm    - TDA2XX EVM with Si build
  dra7xx-evm    - DRA7XX EVM with Si build
  tda2ex-evm    - TDA2EX EVM with Si build
  tda3xx-evm    - TDA3XX EVM with Si build
  ti814x-evm    - TI814x EVM with Si build
  tda2xx-virtio - TDA2XX virtio simulator build
  tda2xx-sim    - TDA2XX simulator build
  tda2xx-zebu   - TDA2XX Zebu build
  tda3xx-sim    - TDA3XX simulator build
  tda3xx-zebu   - TDA3XX Zebu build
  ti8149-evm    - TI8149 EVM with Si build
  ti811x-evm    - TI811x EVM with Si build

  Valid values for PROFILE_$(CORE) are:
  debug                 - Debug build with NO compiler optimizations
                          and symbolic debug info included
  release               - Release build with FULL compiler optimizations
                          and symbolic debug info included
  prod_release          - Production release build with FULL compiler
                          optimizations with parameter check and asserts disabled

  $(CORE) should always be "m4vpss" for BSP package.

  When building proxy client example, internally CORE is changed
  to m4video when requried for the app.
  In Rules.make, CORE should always be m4vpss.

- PACKAGE_SELECT (Supported values: all, vps-hal-only, vps-vip-only, vps-vpe-only, vps-vip-dss, vps-vip-vpe)
  all: All libraries are built
  vps-hal-only: Only VPS HAL and common libraries are built
  vps-vip-only: Only VIP libraries are built
  vps-vpe-only: Only VPE libraries are built
  vps-dss-only: Only DSS libraries are built
  vps-vip-dss : VIP and DSS libraries are built
  vps-vip-vpe : VIP and VPE libraries are built

- The generated files are placed in the below folders,
  Executables   - $(DEST_ROOT)/<APP_NAME>/bin/$(PLATFORM)/<APP_NAME>_m4vpss_$(PROFILE).xem4
  Libraries     - $(DEST_ROOT)/<MODULE_RELPATH>/lib/$(PLATFORM)/m4/$(PROFILE)/*.aem4
  Objects       - $(DEST_ROOT)/<MODULE_RELPATH>/obj/$(PLATFORM)/m4/$(PROFILE)/*.oem4
  XDC configuro - $(DEST_ROOT)/<APP_NAME>/obj/$(PLATFORM)/m4vpss/$(PROFILE)/<APP_NAME>_configuro/*
  Dependancies  - $(DEST_ROOT)/<APP_NAME>/obj/$(PLATFORM)/m4vpss/$(PROFILE)/.deps/*.P

- To have a custom frame buffer heap size other than predefined in the package,
  the CUSTOM_MEM_FRAME_HEAP_SIZE variable could be set while building the application.
  The value provided is in MB.
  For example to set the frame buffer memory to 100MB use as

  gmake -s chains CUSTOM_MEM_FRAME_HEAP_SIZE=100

  Make sure to do a clean build while doing the above as it may not recompile the
  bsp libarary again.

- During development the below "gmake" targets can be also used be used for
  convenience:

  gmake -s vps              - incrementally builds only video drivers
  gmake -s examples         - incrementally builds BSP drivers
                              and all examples

  gmake -s platforms        - incrementally builds for all supported PLATFORMs
  gmake -s profiles         - incrementally builds for all supported PROFILEs

  gmake -s all              - clean all and build all drivers, examples
  gmake -s allall           - incrementally builds for all supported PLATFORMs
                              AND PROFILEs

  gmake -s clean            - clean all drivers, examples
  gmake -s examplesclean    - clean all examples ONLY
  gmake -s platformsclean   - cleans for all supported PLATFORMs
  gmake -s profilesclean    - cleans for all supported PROFILEs
  gmake -s allclean         - cleans for all supported PLATFORMs AND PROFILEs

  gmake -s <examplename>    - incrementally builds BSP drivers
                              and the specific example ONLY.

                              Values for <examplename> can be,
                              i2c
                              captureVip
                              m2mVpe
                              display
