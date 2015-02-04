#include <jni.h>
#include <android_runtime/AndroidRuntime.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>

#include <gui/Surface.h>
#include <assert.h>
#include <utils/Log.h>
#include <nativehelper/JNIHelp.h>
#include <ui/egl/android_natives.h>
//#include <system/window.h>
#include <ui/GraphicBufferMapper.h>
#include <cutils/properties.h>
#include "mkrender.h"
using namespace android;
ANativeWindow* surface;  

#define CHECK_EQ
  
static int ALIGN(int x, int y) {  
    // y must be a power of 2.  
    return (x + y - 1) & ~(y - 1);  
} 

  
  
static void nativeTest(){  
    ALOGE("[%s]%d",__FILE__,__LINE__);  
}  
  
static jboolean  
nativeSetVideoSurface(JNIEnv *env, jobject thiz, jobject jsurface){  
    surface = ANativeWindow_fromSurface(env, jsurface);
    /*
    ALOGE("[%s]%d",__FILE__,__LINE__);  
    surface = android_view_Surface_getSurface(env, jsurface).get();  
    if(android::Surface::isValid(surface)){  
        ALOGE("surface is valid ");  
    }else {  
        ALOGE("surface is invalid ");  
        return false;  
    }  
    ALOGE("[%s][%d]\n",__FILE__,__LINE__);  
    */
    return true;  
}  
static void  
nativeShowYUV(JNIEnv *env, jobject thiz,jbyteArray yuvData,jint width,jint height){  
    ALOGE("width = %d,height = %d",width,height);  
    jint len = env->GetArrayLength(yuvData);  
    ALOGE("len = %d",len);  
    jbyte *byteBuf = env->GetByteArrayElements(yuvData, 0);  
    render(byteBuf,len,surface,width,height);  
}  
static JNINativeMethod gMethods[] = {  
    {"nativeTest",                  "()V",                              (void *)nativeTest},  
    {"nativeSetVideoSurface",       "(Landroid/view/Surface;)Z",        (void *)nativeSetVideoSurface},  
    {"nativeShowYUV",               "([BII)V",                          (void *)nativeShowYUV},  
};  
  
static const char* const kClassPathName = "com/example/hello_jni/MainActivity";
  
// This function only registers the native methods  
static int register_com_example_myyuvviewer(JNIEnv *env)  
{  
    ALOGE("[%s]%d",__FILE__,__LINE__);  
    return AndroidRuntime::registerNativeMethods(env,  
                kClassPathName, gMethods, NELEM(gMethods));  
}  
  
jint JNI_OnLoad(JavaVM* vm, void* reserved)  
{  
    ALOGE("[%s]%d",__FILE__,__LINE__);  
    JNIEnv* env = NULL;  
    jint result = -1;  
  
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {  
        ALOGE("ERROR: GetEnv failed\n");  
        goto bail;  
    }  
    assert(env != NULL);  
    ALOGE("[%s]%d",__FILE__,__LINE__);  
   if (register_com_example_myyuvviewer(env) < 0) {  
        ALOGE("ERROR: MediaPlayer native registration failed\n");  
        goto bail;  
    }  
  
    /* success -- return valid version number */  
    result = JNI_VERSION_1_4;  
  
bail:  
    return result;  
} 
