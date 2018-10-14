#ifndef CLIP_H
#define CLIP_H

#include "polygon.h"
#include <vector>

vector<Polygon> clip(vector<Polygon> polygons, float x_min, float x_max, float y_min, float y_max);

#endif
