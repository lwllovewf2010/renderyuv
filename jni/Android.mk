LOCAL_PATH:= $(call my-dir)  
include $(CLEAR_VARS)  
LOCAL_SRC_FILES:= showYUV.cpp  \
					mkrender.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/frameworks/base/include \
	$(LOCAL_PATH)/include/frameworks/native/include \
	$(LOCAL_PATH)/include/system/core/include \
	$(LOCAL_PATH)/include/libnativehelper/include \
	$(LOCAL_PATH)/include/frameworks/native/include \
	$(LOCAL_PATH)/include/hardware/libhardware/include \
	$(LOCAL_PATH)/include/frameworks/av/include \
	$(LOCAL_PATH)/include


LOCAL_LDLIBS += -L$(LOCAL_PATH)/lib -ljnigraphics -lEGL -lGLESv2 -landroid -landroid_runtime -lbinder -lcutils -lexpat -lgui -lmedia -lnativehelper -lskia -lsqlite -lstlport -lui -lutils -llog -lOpenSLES

LOCAL_CFLAGS += -DHAVE_PTHREADS


LOCAL_MODULE:= libshowYUV  


LOCAL_MODULE_TAGS := tests  


include $(BUILD_SHARED_LIBRARY)  

