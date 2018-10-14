#include "transform.h"

#include "polygon.h"
#include <vector>
#include <cmath>

using namespace std;

void translate(vector<Polygon>& polygons, int index, float translate_x, float translate_y) {
    for (int i = 0; i < polygons.at(index).vertices.size(); i++) {
        polygons.at(index).vertices.at(i).x += translate_x;
        polygons.at(index).vertices.at(i).y += translate_y;
    }
}

void scale(vector<Polygon>& polygons, int index, float factor) {

    float centroid_x = 0;
    float centroid_y = 0;
    for (int i = 0; i < polygons.at(index).vertices.size(); i++) {
        centroid_x += polygons.at(index).vertices.at(i).x;
        centroid_y += polygons.at(index).vertices.at(i).y;
    }
    centroid_x /= polygons.at(index).numVertices;
    centroid_y /= polygons.at(index).numVertices;

    translate(polygons, index, -1 * centroid_x, -1 * centroid_y);

    for (int i = 0; i < polygons.at(index).vertices.size(); i++) {
        polygons.at(index).vertices.at(i).x *= factor;
        polygons.at(index).vertices.at(i).y *= factor;
    }

    translate(polygons, index, centroid_x, centroid_y);

}

void rotate(vector<Polygon>& polygons, int index, float angle) {

    float centroid_x = 0;
    float centroid_y = 0;
    for (int i = 0; i < polygons.at(index).vertices.size(); i++) {
        centroid_x += polygons.at(index).vertices.at(i).x;
        centroid_y += polygons.at(index).vertices.at(i).y;
    }
    centroid_x /= polygons.at(index).numVertices;
    centroid_y /= polygons.at(index).numVertices;

    translate(polygons, index, -1 * centroid_x, -1 * centroid_y);

    for (int i = 0; i < polygons.at(index).vertices.size(); i++) {
        float old_x = polygons.at(index).vertices.at(i).x;
        float old_y = polygons.at(index).vertices.at(i).y;
        polygons.at(index).vertices.at(i).x = (cos(3.14159f / 180 * angle) * old_x) + (-1 *sin(3.14159 / 180 * angle) * old_y);
        polygons.at(index).vertices.at(i).y = (sin(3.14159f / 180 * angle) * old_x) + (cos(3.14159 / 180 * angle) * old_y);
    }

    translate(polygons, index, centroid_x, centroid_y);
}
