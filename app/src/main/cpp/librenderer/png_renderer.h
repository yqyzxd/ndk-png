//
// Created by 史浩 on 2023/3/29.
//

#ifndef NDK_PNG_PNG_RENDERER_H
#define NDK_PNG_PNG_RENDERER_H


#include "../libgles/egl/gl_renderer.h"
#include "../libgles/gles/texture.h"
#include "png_filter.h"
#include "../libcommon/CommonTools.h"
class PngRenderer: public GLRenderer{

private:

    PngFilter* pngFilter=0;
    Texture* texture=0;
public:
    PngRenderer();
    ~PngRenderer();
     void surfaceCreated() override;
     void surfaceChanged(int width, int height) override;
     void surfaceDestroyed() override;
     void onDrawFrame() override;

    void updateTexImage(void* bytes,int width,int height);
};


#endif //NDK_PNG_PNG_RENDERER_H
