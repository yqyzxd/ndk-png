//
// Created by 史浩 on 2023/3/29.
//

#ifndef NDK_PNG_GL_SURFACE_H
#define NDK_PNG_GL_SURFACE_H


#include <pthread.h>
#include "gl_renderer.h"
#include "window_surface.h"

class GLSurface {
public:
    GLSurface();
    virtual  ~GLSurface(){};

    void setRenderer(GLRenderer* renderer);
    virtual GLRenderer* getRenderer();
    virtual void surfaceCreated(ANativeWindow* window);
    virtual void surfaceChanged(int width,int height);
    virtual void surfaceDestroyed(void);
private:
    pthread_t _rendererThreadId=0;
    pthread_mutex_t mLock;
    pthread_cond_t mCond;

    GLRenderer* mRenderer=0;
    WindowSurface* mSurface=0;

private:
    static void* threadStartRoutine(void *myself);

    void renderLoop();
};


#endif //NDK_PNG_GL_SURFACE_H
