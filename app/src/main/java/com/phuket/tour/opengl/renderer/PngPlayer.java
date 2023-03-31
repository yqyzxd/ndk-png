package com.phuket.tour.opengl.renderer;

import android.content.res.AssetManager;
import android.view.Surface;

public class PngPlayer {
	private long nativeHandle;
	public PngPlayer(){
		nativeHandle= init();
	}
	public void setSource( String picPath, AssetManager mgr){
		setDataSource(nativeHandle,picPath,mgr);
	}

	public void onSurfaceCreated(Surface surface){
		surfaceCreated(nativeHandle,surface);
	}

	public void onSurfaceChanged( int width, int height){
		surfaceChanged(nativeHandle,width,height);
	}

	public void onSurfaceDestroyed(){
		surfaceDestroyed(nativeHandle);
	}

	public void release(){
		nativeRelease(nativeHandle);
	}
	private native long init();

	private native void setDataSource(long nativeHandle, String picPath, AssetManager mgr);

	private native void surfaceCreated(long nativeHandle, Surface surface);

	public native void surfaceChanged(long nativeHandle, int width, int height);

	public native void surfaceDestroyed(long nativeHandle);

	public native void nativeRelease(long nativeHandle);

}
