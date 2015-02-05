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
static int ALIGN(int x, int y) {  
    // y must be a power of 2.  
    return (x + y - 1) & ~(y - 1);  
} 

using namespace android;
void render(void*y, void*u, void*v, int ylen, int ulen, int vlen, size_t size, ANativeWindow* nativeWindow,int width,int height) {  

    ANativeWindow*  mNativeWindow = nativeWindow;  
    int err;  
    int mCropWidth = width;  
    int mCropHeight = height;  
      
    int halFormat = HAL_PIXEL_FORMAT_YV12;//颜色空间  
    int bufWidth = (mCropWidth + 1) & ~1;//按2对齐  
    int bufHeight = (mCropHeight + 1) & ~1;  
      
            native_window_set_usage(  
                mNativeWindow,
            GRALLOC_USAGE_SW_READ_NEVER | GRALLOC_USAGE_SW_WRITE_OFTEN  
            | GRALLOC_USAGE_HW_TEXTURE | GRALLOC_USAGE_EXTERNAL_DISP);  
  
            native_window_set_scaling_mode(  
                mNativeWindow,
                1);
                //NATIVE_WINDOW_SCALING_MODE_SCALE_CROP);  
  
    // Width must be multiple of 32???  
    //很重要,配置宽高和和指定颜色空间yuv420  
    //如果这里不配置好，下面deque_buffer只能去申请一个默认宽高的图形缓冲区  
            native_window_set_buffers_geometry(  
                mNativeWindow,
                bufWidth,  
                bufHeight,  
                halFormat);  
      
      
    ANativeWindowBuffer *buf;//描述buffer  
    //申请一块空闲的图形缓冲区  
    if ((err = mNativeWindow->dequeueBuffer(mNativeWindow,
                                            &buf)) != 0) {  
        ALOGW("Surface::dequeueBuffer returned error %d", err);  
        return;  
    }  
  
    GraphicBufferMapper &mapper = GraphicBufferMapper::get();  
  
    Rect bounds(mCropWidth, mCropHeight);  
  
    void *dst;  
    mapper.lock(//用来锁定一个图形缓冲区并将缓冲区映射到用户进程  
                buf->handle, GRALLOC_USAGE_SW_WRITE_OFTEN, bounds, &dst);//dst就指向图形缓冲区首地址  
  
    if (true){  
/*
        size_t dst_y_size = buf->stride * buf->height;  
        size_t dst_c_stride = ALIGN(buf->stride / 2, 16);//1行v/u的大小  
        size_t dst_c_size = dst_c_stride * buf->height / 2;//u/v的大小  
*/
//        ALOGW("mamk memcpy %d %d %d", dst, data, dst_y_size + dst_c_size*2);            
     memcpy(dst, y, ylen);
     memcpy((uint8_t*)(dst)+ylen, u, ulen);
     memcpy((uint8_t*)(dst)+ylen+ulen, v, vlen);

//        memcpy(dst, data, size);//将yuv数据copy到图形缓冲区  
    }  
  
    mapper.unlock(buf->handle);  
  
    if ((err = mNativeWindow->queueBuffer(mNativeWindow, buf)) != 0) {  
    }  
    buf = NULL;  
}  
