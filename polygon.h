#ifndef POLYGON_H
#define  POLYGON_H

#include <vector>

using namespace std;

class Coordinate {
public:

    float x;
    float y;

    Coordinate(float x1, float y1);

};

class Polygon {
public:
    
    int numVertices;
    vector<Coordinate> vertices;

    Polygon(int num, vector<Coordinate> verts);

};

#endif
