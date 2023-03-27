//
// Created by wind on 2023/3/27.
//

#ifndef NDK_PNG_LOG_H
#define NDK_PNG_LOG_H
#include <android/log.h>
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //NDK_PNG_LOG_H
