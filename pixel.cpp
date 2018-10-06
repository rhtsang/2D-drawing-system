#include "polygon.h"

void setPixel(float* PixelBuffer, Coordinate point, Coordinate viewport) {
    int index = (3 * viewport.x * point.y) + (3 * point.x);
    PixelBuffer[index] = PixelBuffer[index+1] = PixelBuffer[index+2] = 1;
}
