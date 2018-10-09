#include "polygon.h"
#include <iostream>
using namespace std;

void setPixel(float* PixelBuffer, Coordinate point, Coordinate viewport) {
    //int index = (3 * (viewport.x) * point.y) + (3 * point.x);
    int index = (point.y * viewport.x + point.x) * 3;
    //cout << "setting pix at "  << point.x << " " << point.y << endl;
    PixelBuffer[index] = PixelBuffer[index+1] = PixelBuffer[index+2] = 1;
}
