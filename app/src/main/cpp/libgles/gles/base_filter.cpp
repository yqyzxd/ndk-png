//
// Created by 史浩 on 2023/3/29.
//

#include "base_filter.h"
#include "gl_utils.h"

BaseFilter::BaseFilter(const char *vertexSource, const char *fragmentSource) {

    mProgram=createProgram(vertexSource,fragmentSource);
}

void BaseFilter::onReady(int width, int height) {
    mWidth=width;
    mHeight=height;
}