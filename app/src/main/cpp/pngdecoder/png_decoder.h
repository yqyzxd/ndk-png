//
// Created by wind on 2023/3/28.
//

#ifndef NDK_OPENGLES_PNG_DECODER_H
#define NDK_OPENGLES_PNG_DECODER_H

#define LOG_TAG "PngDecoder"
#include <string.h>
#include "libpng/png.h"

class PngDecoder {
public:
    PngDecoder(char* fileName);
    virtual ~PngDecoder();

    png_bytep decode();
    virtual void pngReadCallback(png_bytep data, png_size_t length)=0;

    int getWidth();
    int getHeight();

private:
    int width;
    int height;
    bool isPng();

protected:
    char* fileName=0;
    //关闭文件资源
    virtual void fClose()=0;

    virtual png_bytep readHead()=0;
};


#endif //NDK_OPENGLES_PNG_DECODER_H
