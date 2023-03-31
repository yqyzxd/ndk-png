//
// Created by 史浩 on 2023/3/29.
//

#include "gl_surface.h"
#define LOG_TAG "GLSurface"
GLSurface::GLSurface() {
    mRenderMode=RENDER_MODE_WHEN_DIRTY;
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

    LOGE("setRenderer");
    this->mRenderer=renderer;
    pthread_create(&_rendererThreadId,0,threadStartRoutine,this);
}

GLRenderer *GLSurface::getRenderer() {
    return mRenderer;
}

void GLSurface::surfaceCreated(ANativeWindow *window) {
    pthread_mutex_lock(&mLock);
    LOGE("surfaceCreated %d",mRenderThreadStarted);
    this->window=window;
    mSurfaceEvent=SURFACE_EVENT_CREATED;
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);
}

void GLSurface::surfaceChanged(int width, int height) {
    pthread_mutex_lock(&mLock);
    LOGE("surfaceChanged %d",mRenderThreadStarted);
    mSurfaceEvent=SURFACE_EVENT_CHANGED;
    mSurfaceWidth=width;
    mSurfaceHeight=height;
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);
}

void GLSurface::surfaceDestroyed() {
    pthread_mutex_lock(&mLock);
    LOGE("GLSurface::surfaceDestroyed");
    mSurfaceEvent=SURFACE_EVENT_DESTROYED;
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);

}

void GLSurface::queueEvent(Runnable* runnable) {
    pthread_mutex_lock(&mLock);
    mRunnable=runnable;
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);

}

void GLSurface::requestRender() {
    pthread_mutex_lock(&mLock);
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);
}
void GLSurface::renderLoop() {
    mRenderThreadStarted= true;

    while (true){
        pthread_mutex_lock(&mLock);
        //LOGE("renderLoop %d",SURFACE_EVENT_CREATED);
        switch (mSurfaceEvent) {
            case SURFACE_EVENT_CREATED:
                mSurfaceEvent=SURFACE_EVENT_NONE;
                if (mRenderer){
                    EGLCore* egl=new EGLCore();
                    egl->init();
                    mSurface=new WindowSurface(egl,window);
                    mSurface->makeCurrent();
                    LOGE("surfaceCreated before");
                    mRenderer->surfaceCreated();
                    LOGE("surfaceCreated after");
                }
                break;
            case SURFACE_EVENT_CHANGED:
                mSurfaceEvent=SURFACE_EVENT_NONE;
                if (mRenderer){
                    mSurface->makeCurrent();
                    mRenderer->surfaceChanged(mSurfaceWidth,mSurfaceHeight);
                    if (mRenderMode==RENDER_MODE_WHEN_DIRTY){
                        requestRender();
                    }
                }
                break;
            case SURFACE_EVENT_DESTROYED:
                mSurfaceEvent=SURFACE_EVENT_NONE;
                if (mRenderer){
                    mRenderer->surfaceDestroyed();
                }
                if (mSurface){
                    mSurface->release();
                }
                LOGE("GL_THREAD FINISH");
                return;
        }




        if (mRenderer && mSurface){
            if (mRunnable){
                LOGE("GLSurface before run");
                mRunnable->run();
                mRunnable= nullptr;
                LOGE("GLSurface after run");
            }
            mSurface->makeCurrent();
            LOGE("before onDrawFrame");
            mRenderer->onDrawFrame();
            LOGE("after onDrawFrame");
            mSurface->swapBuffers();
        }
        if (mRenderMode == RENDER_MODE_WHEN_DIRTY){
            pthread_cond_wait(&mCond,&mLock);
        }
        pthread_mutex_unlock(&mLock);
    }
}
