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
private:
    pthread_t _rendererThreadId=0;
    pthread_mutex_t mLock;
    pthread_cond_t mCond;
    bool mRenderThreadStarted= false;
    SurfaceEvent mSurfaceEvent= SURFACE_EVENT_NONE;
    int mSurfaceWidth;
    int mSurfaceHeight;
    ANativeWindow* window;

    GLRenderer* mRenderer=0;
    WindowSurface* mSurface=0;

    RenderMode mRenderMode=RENDER_MODE_WHEN_DIRTY;

    Runnable* mRunnable=0;


private:
    static void* threadStartRoutine(void *myself);

    void renderLoop();

};


#endif //NDK_PNG_GL_SURFACE_H
