//
// Created by 史浩 on 2023/3/29.
//

#ifndef NDK_PNG_BASE_FILTER_H
#define NDK_PNG_BASE_FILTER_H

#include <GLES2/gl2.h>

class BaseFilter {

public:
    BaseFilter(const char* vertexSource, const char* fragmentSource);
    virtual ~BaseFilter(){};
    void onReady(int width,int height);

    virtual GLuint onDrawFrame(GLuint textureId)=0;
    virtual void dealloc();
protected:
    GLuint mProgram;
    int mWidth;
    int mHeight;
};


#endif //NDK_PNG_BASE_FILTER_H
