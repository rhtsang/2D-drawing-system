#include "polygon.h"

#include <vector>

using namespace std;

Coordinate::Coordinate(float x1, float y1) {
    x = x1;
    y = y1;
}

Polygon::Polygon(int num, vector<Coordinate> verts) {
    numVertices = num;
    vertices = verts;
}
