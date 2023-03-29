package com.phuket.tour.opengl.renderer;

import android.content.res.AssetManager;
import android.view.Surface;

public class PngPreviewController {

	public native void init(String picPath, AssetManager mgr);

	public native void setSurface(Surface surface);

	public native void resetSize(int width, int height);

	public native void stop();

}
