
cmake_minimum_required(VERSION 3.22.1)


project("pngdecoder")

include_directories(libpng)
add_subdirectory(libpng)


add_library(
        pngdecoder

        STATIC

        png_decoder.cpp
        asset_png_decoder.cpp
        file_png_decoder.cpp
)


target_link_libraries(
        pngdecoder
        libpng
        )