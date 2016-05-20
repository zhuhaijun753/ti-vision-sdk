demo:
	$(MAKE) -fMAKEFILE_tda2xx_hello_world.MK libs TARGET=depend
	$(MAKE) -fMAKEFILE_tda2xx_hello_world.MK libs TARGET=lib
	$(MAKE) -fMAKEFILE_tda2xx_hello_world.MK kermod
	$(MAKE) -fMAKEFILE_tda2xx_hello_world.MK apps TARGET=exe

vision_sdk_linux_demo:
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/examples/common MODULE=vision_sdk_linux_demo_hello_world $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/examples/tda2xx/src/common_hello_world MODULE=vision_sdk_linux_demo_hello_world $(TARGET)

vision_sdk_linux_lib:
ifneq ($(TARGET),depend)
# Copy IPU1-0 generated memory map file to library include folder.
# If header file is not present then use previously generated file
	-cp $(vision_sdk_PATH)/binaries/obj/vision_sdk/$(PLATFORM)/ipu1_0/$(PROFILE_ipu1_0)/vision_sdk_configuro/osa_mem_map.h $(vision_sdk_PATH)/linux/src/osa/include
endif
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/src/links/ipcOut MODULE=vision_sdk_linux_lib $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/src/links/ipcIn  MODULE=vision_sdk_linux_lib $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/src/links/null  MODULE=vision_sdk_linux_lib $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/src/utils/multiproc MODULE=vision_sdk_linux_lib $(TARGET)
	$(MAKE) -fMAKEFILE_tda2xx.MK -C$(vision_sdk_PATH)/linux/src/system MODULE=vision_sdk_linux_lib $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/src/osa/src MODULE=vision_sdk_linux_lib $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/src/links/sgxDisplay MODULE=vision_sdk_linux_lib $(TARGET)
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/src/links/sgx3Dsrv MODULE=vision_sdk_linux_lib $(TARGET)

libs: vision_sdk_linux_lib vision_sdk_linux_demo

apps:
	$(MAKE) -fMAKEFILE.MK -C$(vision_sdk_PATH)/linux/examples/tda2xx/src/common_hello_world MODULE=vision_sdk_linux_demo_hello_world $(TARGET)

clean:
	$(MAKE) -fMAKEFILE_tda2xx_hello_world.MK libs TARGET=clean

all: clean demo

.PHONY: libs apps clean demo all vision_sdk_linux_lib vision_sdk_linux_demo kermod kermod_clean kermod_build

