package com.wind.ndk.png


import android.view.Surface

class PngPlayer {
    external fun setDataSource(path:String)
    external fun setSurface(surface: Surface)
    external fun resize(width:Int,height:Int)
    external fun release()

    companion object {
        // Used to load the 'png' library on application startup.
        init {
            System.loadLibrary("png")
        }
    }
}