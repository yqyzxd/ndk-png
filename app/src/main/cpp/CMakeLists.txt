cmake_minimum_required(VERSION 3.22.1)


project("png")

include_directories(librenderer)
add_subdirectory(librenderer)


include_directories(pngdecoder)
add_subdirectory(pngdecoder)

include_directories(libgles/egl)
include_directories(libgles/gles)
add_subdirectory(libgles)

add_library(
        native

        SHARED

        com_phuket_tour_opengl_renderer_PngPreviewController.h
        PngPreviewController.cpp
)



target_link_libraries(
        native
        # Links the target library to the log library
        # included in the NDK.
        android
        jnigraphics
        pngdecoder
        eglcore
        renderer
        z
        log
        GLESv2
        EGL)