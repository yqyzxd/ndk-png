//
// Created by 史浩 on 2023/3/29.
//

#include "base_filter.h"
#include "gl_utils.h"
#include "../../libcommon/CommonTools.h"

#define LOG_TAG "BaseFilter"
BaseFilter::BaseFilter(const char *vertexSource, const char *fragmentSource) {

    LOGE( "before createProgram");
    mProgram=createProgram(vertexSource,fragmentSource);
    LOGE( "after createProgram mProgram:%d",mProgram);
    checkGlError("createProgram");
}

void BaseFilter::onReady(int width, int height) {
    mWidth=width;
    mHeight=height;
}