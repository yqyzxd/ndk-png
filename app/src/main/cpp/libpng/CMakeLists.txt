
cmake_minimum_required(VERSION 3.18.1)


project("pngDecoder")

add_library(
        pngDecoder

        STATIC

        png.c
        pngerror.c
        pngget.c
        pngmem.c
        pngpread.c
        pngread.c
        pngrio.c
        pngrtran.c
        pngrutil.c
        pngset.c
        pngtrans.c
        pngwio.c
        pngwrite.c
        pngwtran.c
        pngwutil.c

)


target_link_libraries(
        pngDecoder

        z)