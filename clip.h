#ifndef CLIP_H
#define CLIP_H

#include "polygon.h"
#include <vector>

vector<Polygon> clip(vector<Polygon> polygons, int x_min, int x_max, int y_min, int y_max);

#endif
