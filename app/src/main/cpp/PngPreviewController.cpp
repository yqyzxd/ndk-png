#include "com_phuket_tour_opengl_renderer_PngPreviewController.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/asset_manager_jni.h>

//#include "./librenderer/pic_preview_controller.h"
#include "png_player.h"


static ANativeWindow *window = 0;
//static PicPreviewController *controller = 0;
static PngPlayer* player=0;
JNIEXPORT void JNICALL Java_com_phuket_tour_opengl_renderer_PngPreviewController_init
(JNIEnv * env, jobject obj, jstring pngFilePathParam,jobject jmgr) {
	//controller = new PicPreviewController();
	player=new PngPlayer();
	char* pngFilePath = (char*) env->GetStringUTFChars(pngFilePathParam, NULL);
	player->setAssetSource(AAssetManager_fromJava(env,jmgr),pngFilePath);
	//controller->start(AAssetManager_fromJava(env,jmgr),pngFilePath);
	env->ReleaseStringUTFChars(pngFilePathParam, pngFilePath);
}

JNIEXPORT void JNICALL Java_com_phuket_tour_opengl_renderer_PngPreviewController_setSurface
(JNIEnv * env, jobject obj, jobject surface) {
	if (surface != 0 && NULL != player) {
		window = ANativeWindow_fromSurface(env, surface);
		//controller->setWindow(window);
		player->surfaceCreated(window);
	} else if (window != 0) {
		LOGI("Releasing window");
		ANativeWindow_release(window);
		window = 0;
	}
}

JNIEXPORT void JNICALL Java_com_phuket_tour_opengl_renderer_PngPreviewController_resetSize
(JNIEnv * env, jobject obj, jint width, jint height) {
	//controller->resetSize(width,height);
	player->surfaceChanged(width,height);
}

JNIEXPORT void JNICALL Java_com_phuket_tour_opengl_renderer_PngPreviewController_stop
(JNIEnv * env, jobject obj) {
	//controller->stop();
	player->surfaceDestroyed();

}
