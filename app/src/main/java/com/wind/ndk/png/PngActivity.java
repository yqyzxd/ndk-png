package com.wind.ndk.png;

import android.app.Activity;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;
import android.widget.RelativeLayout;

public class PngActivity extends Activity {

	private SurfaceView surfaceView;

	private String pngPath = "/storage/emulated/0/Android/data/com.wind.ndk.png/files/2.png";
	
	private PngPlayer mPngPlayer;
	private Callback previewCallback = new Callback() {

		public void surfaceCreated(SurfaceHolder holder) {

			String assetPath="1.png";
			mPngPlayer.setDataSource( getAssets(),assetPath);
			mPngPlayer.surfaceCreated(holder.getSurface());

		}

		public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
			mPngPlayer.surfaceChanged(width, height);
		}

		public void surfaceDestroyed(SurfaceHolder holder) {
			mPngPlayer.surfaceDestroyed();
		}
	};

	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_png);
		findView();
		mPngPlayer = new PngPlayer();

	}

	private void findView() {

		surfaceView = findViewById(R.id.surface_view);
		SurfaceHolder mSurfaceHolder = surfaceView.getHolder();
		mSurfaceHolder.addCallback(previewCallback);

	}



	protected void release() {
		if (mPngPlayer!=null) {
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