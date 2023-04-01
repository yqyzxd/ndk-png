package com.wind.ndk.png;

import android.content.res.AssetManager;
import android.view.Surface;

public class PngPlayer {
	private long nativeHandle;
	public PngPlayer(){
		nativeHandle= nativeInit();
	}



	public void setDataSource(AssetManager mgr, String picPath){
		nativeSetDataSource(nativeHandle,mgr,picPath);
	}


	public void surfaceCreated(Surface surface){
		nativeSurfaceCreated(nativeHandle,surface);
	}



	public void surfaceChanged( int width, int height){
		nativeSurfaceChanged(nativeHandle,width,height);
	}



	public void surfaceDestroyed(){
		nativeSurfaceDestroyed(nativeHandle);
	}



	public void release(){
		nativeRelease(nativeHandle);
	}


	private native long nativeInit();
	private native void nativeSetDataSource(long nativeHandle, AssetManager mgr, String picPath);
	private native void nativeSurfaceCreated(long nativeHandle, Surface surface);
	private native void nativeSurfaceChanged(long nativeHandle, int width, int height);
	private native void nativeSurfaceDestroyed(long nativeHandle);
	private native void nativeRelease(long nativeHandle);


}
