package com.phuket.tour.opengl.renderer;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Canvas;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

import com.wind.ndk.png.R;

import java.io.File;

public class MainActivity extends Activity {


	static {
		System.loadLibrary("native");
	}
	private Button go_btn;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		go_btn = (Button) findViewById(R.id.go_btn);
		go_btn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent intent = new Intent(MainActivity.this, PngActivity.class);
				startActivity(intent);
			}
		});
//内置sd卡路径

		requestPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE,Manifest.permission.WRITE_EXTERNAL_STORAGE},1);
	}

}
