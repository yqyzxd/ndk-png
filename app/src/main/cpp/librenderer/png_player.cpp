//
// Created by 史浩 on 2023/3/29.
//

#include "png_player.h"


void PngPlayer::updateTexImage(void* param){
    PngPlayer* player=(PngPlayer*)param;
    PngRenderer* renderer= (PngRenderer *)player->glSurface->getRenderer();

    png_bytep bytes= player->decoder->decode();
    int width= player->decoder->getWidth();
    int height= player->decoder->getHeight();
    renderer->updateTexImage(bytes,width,height);
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

    glSurface->queueEvent(new Runnable(updateTexImage, this))




}





