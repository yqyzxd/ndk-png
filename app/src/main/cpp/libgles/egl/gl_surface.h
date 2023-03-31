//
// Created by 史浩 on 2023/3/29.
//

#ifndef NDK_PNG_GL_SURFACE_H
#define NDK_PNG_GL_SURFACE_H


#include <pthread.h>
#include "gl_renderer.h"
#include "window_surface.h"
#include "../../libcommon/runnable.h"

enum RenderMode{
    RENDER_MODE_CONTINUOUSLY, RENDER_MODE_WHEN_DIRTY
};
enum SurfaceEvent{
    SURFACE_EVENT_NONE,SURFACE_EVENT_CREATED, SURFACE_EVENT_CHANGED,SURFACE_EVENT_DESTROYED
};
class GLSurface {
public:
    GLSurface();
    virtual  ~GLSurface(){};

    void setRenderMode(RenderMode mode);
    void setRenderer(GLRenderer* renderer);
    virtual GLRenderer* getRenderer();
    virtual void surfaceCreated(ANativeWindow* window);
    virtual void surfaceChanged(int width,int height);
    virtual void surfaceDestroyed(void);
    void requestRender();
    void queueEvent(Runnable* runnable);
    virtual void dealloc();
private:
    pthread_t _rendererThreadId=0;
    pthread_mutex_t mLock;
    pthread_cond_t mCond;
    //是否结束渲染线程
    bool mKillRendererThread= false;
    //渲染线程是否已经启动
    bool mRenderThreadStarted= false;
    //surface事件
    SurfaceEvent mSurfaceEvent= SURFACE_EVENT_NONE;

    int mSurfaceWidth;
    int mSurfaceHeight;
    ANativeWindow* window;
    //渲染器
    GLRenderer* mRenderer=0;
    //EGL Surface
    WindowSurface* mSurface=0;
    //渲染模式
    RenderMode mRenderMode=RENDER_MODE_CONTINUOUSLY;
    Runnable* mRunnable=0;
    bool mWakeUpFromDestoryed= false;


private:
    static void* threadStartRoutine(void *myself);

    void renderLoop();

    void releaseSurface();
};


#endif //NDK_PNG_GL_SURFACE_H
