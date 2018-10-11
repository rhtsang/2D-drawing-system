#include "rasterize.h"
#include <vector>
#include "polygon.h"
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;

void rasterize(float* PixelBuffer, vector<Polygon> polygons, int x_min, int x_max, int y_min, int y_max, Coordinate viewport) {

    bool drawEnabled = false;

    // loop through y-coordinates (rows)
    for (int y = y_min; y <= y_max; y++) {
        // loop through x-coordinates (columns)
        for (int x = x_min; x <= x_max; x++) {
            int index = (y * viewport.x + x) * 3;
            // found a pixel set by DDA/Bresenham
            // can be either a vertex or part of line
            if (PixelBuffer[index] == 1) {
                // loop through polygons to find if we intersected one of its
                // vertices
                for (vector<Polygon>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {
                    // loop through each polygon's vertices to see if we
                    // intersected one to deal with special cases
                    for (int i = 0; i < (itr->vertices).size(); i++) {
                        Coordinate point = (itr->vertices).at(i);
                        // if scan line intersects with a vertex
                        if ((x == round(point.x)) && (y == round(point.y)) ) {
                            // check for extrema in these cases
                            if () { // at index 0, wrap to back

                            } else if () { // at end index, wrap to front

                            } else { // middle index, no need to wrap

                            }
                        } else { // did not intersect vertex

                        }
                    }
                }
            } else { // did not find an ON pixel, check if drawEnabled to setPix

            }
        }
    }
}
