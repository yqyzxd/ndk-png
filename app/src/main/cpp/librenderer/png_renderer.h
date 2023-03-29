//
// Created by 史浩 on 2023/3/29.
//

#ifndef NDK_PNG_PNG_RENDERER_H
#define NDK_PNG_PNG_RENDERER_H


#include "../libgles/egl/gl_renderer.h"
#include "../libgles/gles//texture.h"
#include "png_filter.h"

class PngRenderer: public GLRenderer{

private:

    PngFilter* pngFilter=0;
    Texture* texture=0;
public:
    PngRenderer();

    virtual void surfaceCreated();

    virtual void surfaceChanged(int width, int height);

    virtual void surfaceDestroyed();

    virtual void onDrawFrame();

    void updateTexImage(void* bytes,int width,int height);
};


#endif //NDK_PNG_PNG_RENDERER_H
