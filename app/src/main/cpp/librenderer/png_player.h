//
// Created by 史浩 on 2023/3/29.
//

#ifndef NDK_PNG_PNG_PLAYER_H
#define NDK_PNG_PNG_PLAYER_H


#include "png_renderer.h"
#include "../pngdecoder/png_decoder.h"
#include <android/asset_manager.h>
#include "../pngdecoder/asset_png_decoder.h"
#include "../libgles/egl/gl_surface.h"

class PngPlayer {
public:
    PngPlayer();

    void setAssetSource(AAssetManager *mgr,char* path);
    void surfaceCreated(ANativeWindow* window);
    void surfaceChanged(int width,int height);
    void surfaceDestroyed();
private:
    GLSurface* glSurface;
    PngDecoder* decoder;


    static void updateTexImage(void *param);
};


#endif //NDK_PNG_PNG_PLAYER_H
