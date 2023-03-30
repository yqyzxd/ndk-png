//
// Created by 史浩 on 2023/3/29.
//

#ifndef NDK_PNG_PNG_FILTER_H
#define NDK_PNG_PNG_FILTER_H


#include "../libgles/gles/base_filter.h"
#include "../libgles/gles/texture.h"

class PngFilter : public BaseFilter{
public:
    PngFilter(const char *vertexSource, const char *fragmentSource);
    virtual GLuint onDrawFrame(GLuint textureId);
private:
    GLint  mPositionLocation;
    GLint  mCoordLocation;
    GLint  mTextureLocation;
};


#endif //NDK_PNG_PNG_FILTER_H
