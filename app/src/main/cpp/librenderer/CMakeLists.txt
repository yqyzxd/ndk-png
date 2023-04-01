cmake_minimum_required(VERSION 3.22.1)

project("renderer")

add_library(
        renderer

        STATIC


        png_player.cpp
        png_renderer.cpp
        png_filter.cpp

)

target_link_libraries(
        renderer
        # Links the target library to the log library
        # included in the NDK.
        log
        GLESv2
        EGL)

