#ifndef TRANSFORM_H
#define  TRANSFORM_H

#include "polygon.h"
#include <vector>

void translate(vector<Polygon>& polygons, int index, float translate_x, float translate_y);
void scale(vector<Polygon>& polygons, int index, float factor);
void rotate(vector<Polygon>& polygons, int index, float angle);

#endif
