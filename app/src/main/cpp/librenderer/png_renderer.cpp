//
// Created by 史浩 on 2023/3/29.
//

#include "png_renderer.h"

#define  LOG_TAG "PngRenderer"
PngRenderer::PngRenderer() {
}
PngRenderer::~PngRenderer()  {

}

void PngRenderer::surfaceCreated() {
    LOGE("start surfaceCreated");
    char* vertexSource=
            "attribute vec4 a_Position;    \n"
            "attribute vec2 a_Coord;   \n"
            "varying vec2 v_texcoord;     \n"
            "void main(void)               \n"
            "{                            \n"
            "   gl_Position = a_Position;  \n"
            "   v_texcoord = a_Coord;  \n"
            "}                            \n";

    char* fragmentSource=
            "varying highp vec2 v_texcoord;\n"
            "uniform sampler2D u_Texture;\n"
            "void main() {\n"
            "  gl_FragColor = texture2D(u_Texture, v_texcoord);\n"
            "}\n";
    //创建纹理
    pngFilter=new PngFilter(vertexSource,fragmentSource);
    if (texture==NULL){
        texture=new Texture();
        texture->createTexture();
    }

}

void PngRenderer::surfaceChanged(int width, int height) {

    glClearColor(1.0f,1.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    LOGE("surfaceChanged onReady");
    if (pngFilter){
        LOGE("surfaceChanged before onReady pngFilter");
        pngFilter->onReady(width,height);
        LOGE("surfaceChanged after onReady pngFilter");
    }

}

void PngRenderer::surfaceDestroyed() {
    if (pngFilter){
        delete pngFilter;
        pngFilter=NULL;
    }

    if (texture){
        texture->dealloc();
        delete texture;
        texture=NULL;
    }

}

void PngRenderer::updateTexImage(void *bytes, int width, int height) {
    if (texture==NULL){
        texture=new Texture();
        texture->createTexture();

    }
    LOGE("before updateTexImage");
    texture->updateTexImage(bytes,width,height);
    LOGE("after updateTexImage");
}


void PngRenderer::onDrawFrame() {
    if (texture==NULL || pngFilter==NULL){
        return;
    }

    pngFilter->onDrawFrame(texture->getTextureId());
}
