
cmake_minimum_required(VERSION 3.22.1)


project("libpng")

add_library(
        libpng

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
        arm/arm_init.c
        arm/palette_neon_intrinsics.c
        arm/filter_neon_intrinsics.c
        png_pic_decoder.cpp
        image.c
)


target_link_libraries(
        libpng

        z)