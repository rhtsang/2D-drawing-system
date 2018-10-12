#include "rasterize.h"
#include <vector>
#include "polygon.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include "line.h"
#include "pixel.h"

using namespace std;

void rasterize(float* PixelBuffer, vector<Polygon> polygons, Coordinate viewport) {

    for (vector<Polygon>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {

        // intermediate buffer to draw single polygon at a time
        float* DrawBuffer = new float[int(viewport.x) * int(viewport.y) * 3];

        // draw all edges for current polygon
		for (int i = 0; i < (itr->vertices).size(); i++) {
			if (i == (itr->vertices).size() - 1) {
				//dda(PixelBuffer, (itr->vertices).at(i), (itr->vertices).at(0), viewport);
				bresenham(DrawBuffer, (itr->vertices).at(i), (itr->vertices).at(0), viewport);
			} else {
	        	//dda(PixelBuffer, (itr->vertices).at(i), (itr->vertices).at(i+1), viewport);
				bresenham(DrawBuffer, (itr->vertices).at(i), (itr->vertices).at(i+1), viewport);
			}
	    }

        // fill in current polygon
        for (int y = 0; y < viewport.y; y++) {
            int x_start, x_end;

            // find start intersection
            for (x_start = 0; x_start < viewport.x; x_start++) {
                int index = (y * viewport.x + x_start) * 3;
                if (DrawBuffer[index] == 1) {
                    break;
                }
            }

            // find end intersection
            for (x_end = viewport.x - 1; x_end >= 0; x_end--) {
                int index = (y * viewport.x + x_end) * 3;
                if (DrawBuffer[index] == 1) {
                    break;
                }
            }

            // set pixels in between intersections
            for (int x = x_start; x <= x_end; x++) {
                int index = (y * viewport.x + x) * 3;
                Coordinate point(x,y);
                setPixel(DrawBuffer, point, viewport);
            }
        }

        // copy DrawBuffer to PixelBuffer
        for (int y = 0; y < viewport.y; y++) {
            for (int x = 0; x < viewport.x; x++) {
                int index = (y * viewport.x + x) * 3;
                if (DrawBuffer[index] == 1) {
                    Coordinate point(x,y);
                    setPixel(PixelBuffer, point, viewport);
                }
            }
        }

	}


    // bool drawEnabled = false;
    //
    // // loop through y-coordinates (rows)
    // for (int y = y_min; y <= y_max; y++) {
    //     // loop through x-coordinates (columns)
    //     for (int x = x_min; x <= x_max; x++) {
    //         int index = (y * viewport.x + x) * 3;
    //         // found a pixel set by DDA/Bresenham
    //         // can be either a vertex or part of line
    //         if (PixelBuffer[index] == 1) {
    //             // loop through polygons to find if we intersected one of its
    //             // vertices
    //             for (vector<Polygon>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {
    //                 // loop through each polygon's vertices to see if we
    //                 // intersected one to deal with special cases
    //                 for (int i = 0; i < (itr->vertices).size(); i++) {
    //                     Coordinate point = (itr->vertices).at(i);
    //                     // if scan line intersects with a vertex
    //                     if ((x == round(point.x)) && (y == round(point.y)) ) {
    //                         // check for extrema in these cases
    //                         if () { // at index 0, wrap to back
    //
    //                         } else if () { // at end index, wrap to front
    //
    //                         } else { // middle index, no need to wrap
    //
    //                         }
    //                     } else { // did not intersect vertex
    //
    //                     }
    //                 }
    //             }
    //         } else { // did not find an ON pixel, check if drawEnabled to setPix
    //
    //         }
    //     }
    // }
}
