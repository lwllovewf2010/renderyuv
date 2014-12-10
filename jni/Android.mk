LOCAL_PATH:= $(call my-dir)  
include $(CLEAR_VARS)  
LOCAL_SRC_FILES:= showYUV.cpp  

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/frameworks/base/include \
	$(LOCAL_PATH)/include/frameworks/native/include \
	$(LOCAL_PATH)/include/system/core/include \
	$(LOCAL_PATH)/include/libnativehelper/include \
	$(LOCAL_PATH)/include/frameworks/native/include \
	$(LOCAL_PATH)/include/hardware/libhardware/include \
	$(LOCAL_PATH)/include/frameworks/av/include \


LOCAL_LDLIBS += -L$(LOCAL_PATH)/lib -ljnigraphics -lEGL -lGLESv2 -landroid -landroid_runtime -landroidfw -lbinder -lcutils -lexpat -lgui -lmedia -lnativehelper -lskia -lsqlite -lstlport -lui -lutils -llog -lOpenSLES



LOCAL_SHARED_LIBRARIES := \
libEGL \
             libandroid \
         libandroidfw \
       libcutils \
          libgui \
             libnativehelper \
    libsqlite \
          libui \
libGLESv2 \
          libandroid_runtime \
 libbinder \
          libexpat \
           libmedia \
           libskia \
            libstlport \
         libutils \
    libcutils \
    libutils \
    libbinder \
        libui \
            libgui \
                libandroid_runtime \
                    libstagefright_foundation  

LOCAL_MODULE:= libshowYUV  


LOCAL_MODULE_TAGS := tests  


include $(BUILD_SHARED_LIBRARY)  

