#include "com_phuket_tour_opengl_renderer_PngPreviewController.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/asset_manager_jni.h>

//#include "./librenderer/pic_preview_controller.h"
#include "png_player.h"


//static ANativeWindow *window = 0;
//static PicPreviewController *controller = 0;
//static PngPlayer* player=0;

extern "C"
JNIEXPORT jlong JNICALL
Java_com_phuket_tour_opengl_renderer_PngPlayer_init(JNIEnv *env, jobject thiz) {
	PngPlayer *player=new PngPlayer();
	return reinterpret_cast<jlong>(player);
}

JNIEXPORT void JNICALL Java_com_phuket_tour_opengl_renderer_PngPlayer_setDataSource
(JNIEnv * env, jobject obj,jlong handle, jstring pngFilePathParam,jobject jmgr) {
	//controller = new PicPreviewController();
	//player=new PngPlayer();
	PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
	char* pngFilePath = (char*) env->GetStringUTFChars(pngFilePathParam, NULL);
	player->setAssetSource(AAssetManager_fromJava(env,jmgr),pngFilePath);
	//controller->start(AAssetManager_fromJava(env,jmgr),pngFilePath);
	env->ReleaseStringUTFChars(pngFilePathParam, pngFilePath);
}

JNIEXPORT void JNICALL Java_com_phuket_tour_opengl_renderer_PngPlayer_surfaceCreated
(JNIEnv * env, jobject obj,jlong handle, jobject surface) {
	PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
	if (surface != 0 && NULL != player) {
		ANativeWindow * window = ANativeWindow_fromSurface(env, surface);
		player->surfaceCreated(window);
	}
}

JNIEXPORT void JNICALL Java_com_phuket_tour_opengl_renderer_PngPlayer_surfaceChanged
(JNIEnv * env, jobject obj,jlong handle, jint width, jint height) {
	//controller->resetSize(width,height);
	PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
	player->surfaceChanged(width,height);
}

JNIEXPORT void JNICALL Java_com_phuket_tour_opengl_renderer_PngPlayer_surfaceDestroyed
(JNIEnv * env, jobject obj,jlong handle) {
	//controller->stop();
	PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
	player->surfaceDestroyed();

}

JNIEXPORT void JNICALL Java_com_phuket_tour_opengl_renderer_PngPlayer_nativeRelease(JNIEnv * env, jobject obj,jlong handle){
	PngPlayer *player= reinterpret_cast<PngPlayer *>(handle);
	player->dealloc();
}
