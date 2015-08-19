/*
 * Loader contains funtions and classes for loading different kind of files.
 * Mostly images so far.
 */

#pragma once

class Image {
    public:
        Image(char* ps, int width, int height);
        ~Image();
        char* pixels;
        int width;
        int height;
};

Image* loadBMP(const char* filename);
