//
// Created by 史浩 on 2023/3/29.
//

#include "gl_surface.h"
#define LOG_TAG "GLSurface"
GLSurface::GLSurface() {
    pthread_mutex_init(&mLock,NULL);
    pthread_cond_init(&mCond,NULL);
}

void *GLSurface::threadStartRoutine(void *myself) {
    GLSurface* glSurface= (GLSurface *)myself;
    glSurface->renderLoop();

    return 0;
}

void GLSurface::setRenderer(GLRenderer *renderer) {
    if (_rendererThreadId>0){
        //already started
        return;
    }
    LOGE("GLSurface::setRenderer");
    this->mRenderer=renderer;
    pthread_create(&_rendererThreadId,0,threadStartRoutine,this);

}

GLRenderer *GLSurface::getRenderer() {
    return mRenderer;
}

void GLSurface::surfaceCreated(ANativeWindow *window) {
    if (mRenderer){
        EGLCore* eglCore=new EGLCore();
        eglCore->init();
        mSurface=new WindowSurface(eglCore,window);
        LOGE("GLSurface::surfaceCreated before");
        mRenderer->surfaceCreated();
        LOGE("GLSurface::surfaceCreated after");
    }
}

void GLSurface::surfaceChanged(int width, int height) {
    LOGE("GLSurface::surfaceChanged");
    if (mRenderer){
        mRenderer->surfaceChanged(width,height);
    }
}

void GLSurface::surfaceDestroyed() {
    if (mRenderer){
        mRenderer->surfaceDestroyed();
    }
    if (mSurface){
        mSurface->release();
    }
}
void GLSurface::renderLoop() {
    while (true){
        pthread_mutex_lock(&mLock);

        if (mRenderer && mSurface){
            mSurface->makeCurrent();
            mRenderer->onDrawFrame();
            mSurface->swapBuffers();
        }

        pthread_mutex_unlock(&mLock);
    }
}
