#include "rasterize.h"
#include <vector>
#include "polygon.h"
#include <algorithm>

using namespace std;

void rasterize(float* PixelBuffer, vector<Polygon> polygons, int x_min, int x_max, int y_min, int y_max, Coordinate viewport) {

    for (int y = y_min; y <= y_max; y++) {

        for (int x = x_min; x <= x_max; x++) {

            for (vector<Polygon>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {

                // for (vector<Coordinate>::iterator itr2 = (itr->vertices).begin(); itr2 != (itr->vertices).end(); itr2++) {
                //     if () {
                //
                //     }
                // }

                for (int i = 0; i < (itr->vertices).size(); i++) {

                    if (i == (itr->vertices).size() - 1) {
                        Coordinate start = (itr->vertices).at(i);
                        Coordinate end = (itr->vertices).at(0);
                        if ( (x >= min(start.x, end.x)) &&
                             (x <= max(start.x, end.x)) &&
                             (y >= min(start.y, end.y)) &&
                             (y <= max(start.y, end.y)) ) {

                                int index = (y * viewport.x + x) * 3;
                                PixelBuffer[index] = PixelBuffer[index+1] = PixelBuffer[index+2] = 1;

                        }
                    } else {
                        Coordinate start = (itr->vertices).at(i);
                        Coordinate end = (itr->vertices).at(i+1);
                        if ( (x >= min(start.x, end.x)) &&
                             (x <= max(start.x, end.x)) &&
                             (y >= min(start.y, end.y)) &&
                             (y <= max(start.y, end.y)) ) {

                                int index = (y * viewport.x + x) * 3;
                                PixelBuffer[index] = PixelBuffer[index+1] = PixelBuffer[index+2] = 1;

                        }
                    }

                }

            }

        }

    }

}
