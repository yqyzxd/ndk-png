cmake_minimum_required(VERSION 3.22.1)


project("native")

include_directories(librenderer)
add_subdirectory(librenderer)



include_directories(pngdecoder)
add_subdirectory(pngdecoder)

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
        renderer
        z
        log
        GLESv2
        EGL)