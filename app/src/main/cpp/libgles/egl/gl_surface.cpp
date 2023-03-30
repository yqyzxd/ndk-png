//
// Created by 史浩 on 2023/3/29.
//

#include "gl_surface.h"
#define LOG_TAG "GLSurface"
GLSurface::GLSurface() {
    mRenderMode=RENDER_MODE_CONTINUOUSLY;
    pthread_mutex_init(&mLock,NULL);
    pthread_cond_init(&mCond,NULL);
}

void *GLSurface::threadStartRoutine(void *myself) {
    GLSurface* glSurface= (GLSurface *)myself;
    glSurface->renderLoop();
    return 0;
}

void GLSurface::setRenderer(GLRenderer *renderer) {
    if (mRenderThreadStarted){
        //already started
        return;
    }
    mRenderThreadStarted= true;
    LOGE("GLSurface::setRenderer");
    this->mRenderer=renderer;
    pthread_create(&_rendererThreadId,0,threadStartRoutine,this);
}

GLRenderer *GLSurface::getRenderer() {
    return mRenderer;
}

void GLSurface::surfaceCreated(ANativeWindow *window) {
    LOGE("GLSurface::surfaceCreated");
    this->window=window;
    mSurfaceEvent=SURFACE_EVENT_CREATED;
}

void GLSurface::surfaceChanged(int width, int height) {
    LOGE("GLSurface::surfaceChanged");
    mSurfaceEvent=SURFACE_EVENT_CHANGED;
    mSurfaceWidth=width;
    mSurfaceHeight=height;
}

void GLSurface::surfaceDestroyed() {
    LOGE("GLSurface::surfaceDestroyed");
    mSurfaceEvent=SURFACE_EVENT_DESTROYED;

}

void GLSurface::queueEvent(Runnable* runnable) {
    mRunnable=runnable;
}

void GLSurface::requestRender() {
    pthread_cond_signal(&mCond);
}
void GLSurface::renderLoop() {
    while (true){
        pthread_mutex_lock(&mLock);
        switch (mSurfaceEvent) {
            case SURFACE_EVENT_CREATED:
                if (mRenderer){
                    EGLCore* egl=new EGLCore();
                    egl->init();
                    mSurface=new WindowSurface(egl,window);
                    LOGE("GLSurface::surfaceCreated before");
                    mRenderer->surfaceCreated();
                    LOGE("GLSurface::surfaceCreated after");
                }
                break;
            case SURFACE_EVENT_CHANGED:
                if (mRenderer){
                    mRenderer->surfaceChanged(mSurfaceWidth,mSurfaceHeight);
                    if (mRenderMode==RENDER_MODE_WHEN_DIRTY){
                        requestRender();
                    }
                }
                break;
            case SURFACE_EVENT_DESTROYED:
                if (mRenderer){
                    mRenderer->surfaceDestroyed();
                }
                if (mSurface){
                    mSurface->release();
                }
                break;
        }
        mSurfaceEvent=SURFACE_EVENT_NONE;
        if (mRenderMode == RENDER_MODE_WHEN_DIRTY){
            pthread_cond_wait(&mCond,&mLock);
        }
        if (mRenderer && mSurface){
            mSurface->makeCurrent();
            mRenderer->onDrawFrame();
            mSurface->swapBuffers();
        }

        pthread_mutex_unlock(&mLock);
    }
}
