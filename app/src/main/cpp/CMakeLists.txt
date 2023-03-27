cmake_minimum_required(VERSION 3.22.1)


project("png")

include_directories(librenderer)
add_subdirectory(librenderer)

include_directories(libpng)
add_subdirectory(libpng)

add_library(
        png

        SHARED

        com_wind_ndk_png_PngPlayer.cpp
        eglcore/egl_core.cpp
)



target_link_libraries(
        png
        # Links the target library to the log library
        # included in the NDK.
        pngDecoder
        renderer
        z
        log
        GLESv2
        EGL)