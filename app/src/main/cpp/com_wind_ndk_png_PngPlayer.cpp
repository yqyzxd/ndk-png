//
// Created by 史浩 on 2023/4/1.
//

#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>
#include "com_wind_ndk_png_PngPlayer.h"
#include "png_player.h"


JNIEXPORT jlong JNICALL Java_com_wind_ndk_png_PngPlayer_nativeInit
        (JNIEnv *, jobject){
    PngPlayer *player=new PngPlayer();
    return reinterpret_cast<jlong>(player);
  }


JNIEXPORT void JNICALL Java_com_wind_ndk_png_PngPlayer_nativeSetDataSource
(JNIEnv *env, jobject, jlong handle, jobject jmgr, jstring jpath){
PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
char* cPath = (char*) env->GetStringUTFChars(jpath, NULL);
player->setAssetSource(AAssetManager_fromJava(env,jmgr),cPath);
env->ReleaseStringUTFChars(jpath, cPath);
}


JNIEXPORT void JNICALL Java_com_wind_ndk_png_PngPlayer_nativeSurfaceCreated
(JNIEnv *env, jobject, jlong handle,  jobject surface){
PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
if (surface != 0 && NULL != player) {
ANativeWindow * window = ANativeWindow_fromSurface(env, surface);
player->surfaceCreated(window);
}
}


JNIEXPORT void JNICALL Java_com_wind_ndk_png_PngPlayer_nativeSurfaceChanged
(JNIEnv *, jobject, jlong handle, jint width, jint height){
PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
player->surfaceChanged(width,height);
}


JNIEXPORT void JNICALL Java_com_wind_ndk_png_PngPlayer_nativeSurfaceDestroyed
(JNIEnv *, jobject, jlong handle){
PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
player->surfaceDestroyed();
}

JNIEXPORT void JNICALL Java_com_wind_ndk_png_PngPlayer_nativeRelease
(JNIEnv *, jobject, jlong handle){
PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
player->dealloc();
}