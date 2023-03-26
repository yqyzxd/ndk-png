package com.wind.ndk.png

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.SurfaceHolder
import android.view.SurfaceHolder.Callback
import android.widget.TextView
import com.wind.ndk.png.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private lateinit var pngPlayer: PngPlayer
    private val pngPath="/mnt/sdcard/1.png"
    private val callback=object :Callback{
        override fun surfaceCreated(holder: SurfaceHolder) {
            pngPlayer=PngPlayer().apply {
                setDataSource(pngPath)
                setSurface(holder.surface)
            }

        }

        override fun surfaceChanged(holder: SurfaceHolder, format: Int, w: Int, h: Int) {
            pngPlayer.resize(w,h)
        }

        override fun surfaceDestroyed(holder: SurfaceHolder) {
        }

    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

       binding.surfaceView.holder.apply {
           addCallback(callback)
           //setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS)
       }

    }


}