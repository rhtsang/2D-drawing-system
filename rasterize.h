#ifndef RASTERIZE_H
#define RASTERIZE_H

#include <vector>
#include "polygon.h"

using namespace std;

void rasterize(float* PixelBuffer, vector<Polygon> polygons, int x_min, int x_max, int y_min, int y_max, Coordinate viewport);

#endif
