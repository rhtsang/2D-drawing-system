#ifndef LINE_H
#define  LINE_H

#include "polygon.h"

void dda(float* PixelBuffer, Coordinate start, Coordinate end, Coordinate viewport);
void bresenham(float* PixelBuffer, Coordinate start, Coordinate end, Coordinate viewport);

#endif
