#include <assert.h>
#include <fstream>
#include "loader.h"
#include "auto-array.h"

using namespace std;

Image::Image(char* ps, int w, int h): pixels(ps), width(w), height(h) {}

Image::~Image() {
    delete[] pixels;
}

namespace {
    /*
     * Conver 4 bytes to integer using in little-endian order
     * 'bytes' must be at least four units long and if it is longer,
     *  four first will be used.
     */
    int toInt(const char* bytes) {
        return (int) (((unsigned char)bytes[3] << 24) |
                      ((unsigned char)bytes[2] << 16) |
                      ((unsigned char)bytes[1] <<  8) |
                       (unsigned char)bytes[0]);
    }
    /*
     * Convert two chars to short integer using little-endian format
     */
    short toShort(const char a, const char b) {
        return (short) ((unsigned char) b << 8 | (unsigned char) a);
    }
    short toShort(const char* bytes) {
        return toShort(bytes[0], bytes[1]);
    }
    /*
     * Read integer from input file stream
     */
    int readInt(ifstream &input) {
        char buf[4];
        input.read(buf, 4);
        return toInt(buf);
    }
    /*
     * Read short from input file stream
     */
    short readShort(ifstream &input) {
        char buf[2];
        input.read(buf, 2);
        return toShort(buf);
    }
}
Image* loadBMP(const char* filename){
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buf[2];
    input.read(buf, 2);
    assert((buf[0] == 'B' && buf[1] == 'M') || !"This is not a bitmap");
    input.ignore(8);
    int dataOffset = readInt(input);
    int headerSize = readInt(input);
    int width;
    int height;
    switch(headerSize){
        case 40: //V3
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not of 24bit color depth");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12: // OS2 V1
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not of 24bit color depth");
            break;
        default:
            assert(!"Image is of currently unsuported BMP format");
    }
    int bytesPerRow = ((width * 3)/4)*4 + 4;
    int size = bytesPerRow * height;
    AutoArray<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    AutoArray<char> pixels2(new char[width * height * 3]);
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            for(int c = 0; c < 3; c++){
                pixels2[(y*width+x)*3+c] = pixels[y*bytesPerRow+3*x+(2-c)];
            }
        }
    }
    input.close();
    return new Image(pixels2.release(), width, height);
}
