package com.phuket.tour.opengl.renderer;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;
import android.widget.RelativeLayout;

import com.wind.ndk.png.R;

public class PngActivity extends Activity {

	private SurfaceView surfaceView;
	private RelativeLayout preview_parent_layout;

	private String picPath = "/storage/emulated/0/Android/data/com.wind.ndk.png/files/2.png";
	
	private PngPlayer mPngPlayer;
	private Callback previewCallback = new Callback() {

		public void surfaceCreated(SurfaceHolder holder) {

			String assetPath="1.png";
			mPngPlayer.setSource( assetPath, getAssets());
			mPngPlayer.onSurfaceCreated(holder.getSurface());

		}

		public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
			mPngPlayer.onSurfaceChanged(width, height);
		}

		public void surfaceDestroyed(SurfaceHolder holder) {
			mPngPlayer.onSurfaceDestroyed();
		}
	};

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.texture_pic_preview_layout);
		findView();
		mPngPlayer = new PngPlayer();

	}

	private void findView() {
		preview_parent_layout = (RelativeLayout) findViewById(R.id.preview_parent_layout);
		surfaceView = new SurfaceView(PngActivity.this);
		SurfaceHolder mSurfaceHolder = surfaceView.getHolder();
		mSurfaceHolder.addCallback(previewCallback);
		mSurfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
		preview_parent_layout.addView(surfaceView, 0);
		surfaceView.getLayoutParams().width = getWindowManager().getDefaultDisplay().getWidth();
		surfaceView.getLayoutParams().height = getWindowManager().getDefaultDisplay().getHeight();
	}



	protected void release() {
		if (null != mPngPlayer) {
			mPngPlayer.release();
			mPngPlayer = null;
		}
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		release();
	}



}