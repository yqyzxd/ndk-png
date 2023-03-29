//
// Created by 史浩 on 2023/3/29.
//

#include "window_surface.h"
WindowSurface::WindowSurface(EGLCore *eglCore, ANativeWindow *window) :BaseEGLSurface(eglCore){

    mSurface=window;
    createWindowSurface(mSurface);
}
WindowSurface::WindowSurface(EGLCore *eglCore, ANativeWindow *window, bool releaseSurface):BaseEGLSurface(eglCore) {

    this->mSurface=window;
    createWindowSurface(window);
    this->mReleaseSurface=releaseSurface;
}
WindowSurface::~WindowSurface() {

}
void WindowSurface::release() {
    releaseEglSurface();
    if (mSurface!=NULL){
        ANativeWindow_release(mSurface);
        mSurface=NULL;
    }
    if (mEGLCore){
        mEGLCore->release();
        mEGLCore=NULL;
    }

}

void WindowSurface::recreate(EGLCore *eglCore) {
    if (mSurface==NULL){
        return;
    }
    mEGLCore=eglCore;
    createWindowSurface(mSurface);
}