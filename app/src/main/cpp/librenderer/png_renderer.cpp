//
// Created by 史浩 on 2023/3/29.
//

#include "png_renderer.h"

PngRenderer::PngRenderer() {


}

void PngRenderer::surfaceCreated() {
    const char* vertexSource="attribute vec4 a_Position;\n"
                             "attribute vec2 a_Coord;\n"
                             "varying vec2 v_Coord;\n"
                             "\n"
                             "void main(){\n"
                             "    gl_Position=a_Position;\n"
                             "    v_Coord=a_Coord;\n"
                             "}";

    const char* fragmentSource="precision mediump float;\n"
                               "varying vec2 v_Coord;\n"
                               "uniform sampler2D u_Texture;\n"
                               "void main(){\n"
                               "    gl_FragColor=texture2D(u_Texture,v_Coord);\n"
                               "}";
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
    pngFilter->onReady(width,height);
}

void PngRenderer::surfaceDestroyed() {

}

void PngRenderer::updateTexImage(void *bytes, int width, int height) {
    if (texture==NULL){
        texture=new Texture();
        texture->createTexture();
    }
    texture->updateTexImage(bytes,width,height);
}


void PngRenderer::onDrawFrame() {
    if (texture==NULL || pngFilter==NULL){
        return;
    }
    pngFilter->onDrawFrame(texture->getTextureId());

}
