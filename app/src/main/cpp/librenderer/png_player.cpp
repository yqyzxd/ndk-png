//
// Created by 史浩 on 2023/3/29.
//

#include "png_player.h"


void PngPlayer::updateTexImage(void* param){
    LOGE("PngPlayer start updateTexImage");
    PngPlayer* player=(PngPlayer*)param;
    LOGE("PngPlayer  updateTexImage 1");
    PngRenderer* renderer=(PngRenderer*)player->glSurface->getRenderer();
    png_bytep bytes= player->decoder->decode();
    LOGE("PngPlayer  updateTexImage 2");
    int width= player->decoder->getWidth();
    int height= player->decoder->getHeight();
    LOGE("PngPlayer  updateTexImage 3");
    renderer->updateTexImage(bytes,width,height);
    LOGE("PngPlayer end updateTexImage");
}
PngPlayer::PngPlayer() {
     glSurface=new GLSurface();
     GLRenderer* renderer=new PngRenderer();
     glSurface->setRenderer(renderer);
}

void PngPlayer::surfaceCreated(ANativeWindow *window) {
    glSurface->surfaceCreated(window);
}

void PngPlayer::surfaceChanged(int width, int height) {
    glSurface->surfaceChanged(width,height);
}

void PngPlayer::surfaceDestroyed() {
    glSurface->surfaceDestroyed();
}

void PngPlayer::setAssetSource(AAssetManager *mgr, char *path) {
    decoder=new AssetPngDecoder(mgr,path);
    //png_bytep bytes=decoder->decode();
    //int width=decoder->getWidth();
    //int height=decoder->getHeight();
    LOGE("PngPlayer before queueEvent");
    glSurface->queueEvent(new Runnable(updateTexImage, this));

    LOGE("PngPlayer after queueEvent");


}





