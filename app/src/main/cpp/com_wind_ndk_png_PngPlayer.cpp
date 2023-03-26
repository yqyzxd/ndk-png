#include <jni.h>
#include <string>

extern "C"
JNIEXPORT void JNICALL
Java_com_wind_ndk_png_PngPlayer_setDataSource(JNIEnv *env, jobject thiz, jstring jpath) {
       const char* path= env->GetStringUTFChars(jpath,0);


       env->ReleaseStringUTFChars(jpath,path);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_wind_ndk_png_PngPlayer_setSurface(JNIEnv *env, jobject thiz, jobject surface) {
    // TODO: implement setSurface()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_wind_ndk_png_PngPlayer_resize(JNIEnv *env, jobject thiz, jint width, jint height) {
    // TODO: implement resize()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_wind_ndk_png_PngPlayer_release(JNIEnv *env, jobject thiz) {
    // TODO: implement release()
}