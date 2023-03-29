cmake_minimum_required(VERSION 3.22.1)

project("renderer")

add_library(
        renderer

        STATIC

        egl_core.cpp
        pic_preview_controller.cpp
        pic_preview_render.cpp
        pic_preview_texture.cpp
        rgba_frame.cpp


)

target_link_libraries(
        renderer
        # Links the target library to the log library
        # included in the NDK.
        log
        GLESv2
        EGL)

