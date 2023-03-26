//
// Created by 史浩 on 2023/3/26.
//

#ifndef NDK_PNG_PNG_PLAYER_H
#define NDK_PNG_PNG_PLAYER_H
#include <android/native_window.h>

class PngPlayer {
public:
    PngPlayer();
    virtual ~PngPlayer();

    bool start(char * pngPath);
    void release();
    void setWindow(ANativeWindow* window);
    void resize(int width,int height);
};


#endif //NDK_PNG_PNG_PLAYER_H
