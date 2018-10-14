#include "clip.h"

#include "polygon.h"
#include <vector>
#include <cstdlib>

using namespace std;

// implementation of Sutherland-Hodgman polygon clipping, described on page 259 of the textbook
vector<Polygon> clip(vector<Polygon> polygons, float x_min, float x_max, float y_min, float y_max) {

    vector<Polygon> clippedPolygons;

    // loop through all polygons to clip each of its edges
    for (vector<Polygon>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {

        // clip left at x_min
        vector<Coordinate> postClipLeft;
        for (int i = 0; i < (itr->vertices).size(); i++) {

            Coordinate* start;
            Coordinate* end;
            if (i == (itr->vertices).size() - 1) {
                start = &((itr->vertices).at(i));
                end = &((itr->vertices).at(0));
            } else {
                start = &((itr->vertices).at(i));
                end = &((itr->vertices).at(i+1));
            }

            if (start->x < x_min) { // from out
                if (end->x < x_min) { // to out
                    continue;
                } else if (end->x >= x_min) { // to in
                    float slope = (end->y - start->y) / (end->x - start->x);
                    float b = start->y - (slope * start->x);
                    float new_y = slope * x_min + b;
                    Coordinate newVertex(x_min, new_y);
                    postClipLeft.push_back(newVertex);
                    postClipLeft.push_back(*end);
                }
            } else if (start->x >= x_min ) { // from in
                if (end->x < x_min) { // to out
                    float slope = (end->y - start->y) / (end->x - start->x);
                    float b = start->y - (slope * start->x);
                    float new_y = slope * x_min + b;
                    Coordinate newVertex(x_min, new_y);
                    postClipLeft.push_back(newVertex);
                } else if (end->x >= x_min) { // to in
                    postClipLeft.push_back(*end);
                }
            }
        }

        // clip right at x_max
        vector<Coordinate> postClipRight;
        for (int i = 0; i < postClipLeft.size(); i++) {

            Coordinate* start;
            Coordinate* end;
            if (i == postClipLeft.size() - 1) {
                start = &(postClipLeft.at(i));
                end = &(postClipLeft.at(0));
            } else {
                start = &(postClipLeft.at(i));
                end = &(postClipLeft.at(i+1));
            }

            if (start->x > x_max) { // from out
                if (end->x > x_max) { // to out
                    continue;
                } else if (end->x <= x_max) { // to in
                    float slope = (end->y - start->y) / (end->x - start->x);
                    float b = start->y - (slope * start->x);
                    float new_y = slope * x_max + b;
                    Coordinate newVertex(x_max, new_y);
                    postClipRight.push_back(newVertex);
                    postClipRight.push_back(*end);
                }
            } else if (start->x <= x_max ) { // from in
                if (end->x > x_max) { // to out
                    float slope = (end->y - start->y) / (end->x - start->x);
                    float b = start->y - (slope * start->x);
                    float new_y = slope * x_max + b;
                    Coordinate newVertex(x_max, new_y);
                    postClipRight.push_back(newVertex);
                } else if (end->x <= x_max) { // to in
                    postClipRight.push_back(*end);
                }
            }
        }

        // clip bottom at y_min
        vector<Coordinate> postClipBottom;
        for (int i = 0; i < postClipRight.size(); i++) {

            Coordinate* start;
            Coordinate* end;
            if (i == postClipRight.size() - 1) {
                start = &(postClipRight.at(i));
                end = &(postClipRight.at(0));
            } else {
                start = &(postClipRight.at(i));
                end = &(postClipRight.at(i+1));
            }

            if (start->y < y_min) { // from out
                if (end->y < y_min) { // to out
                    continue;
                } else if (end->y >= y_min) { // to in
                    if (start->x == end->x) { // vertical line
                        Coordinate newVertex(start->x, y_min);
                        postClipBottom.push_back(newVertex);
                        postClipBottom.push_back(*end);
                    } else {
                        float slope = (end->y - start->y) / (end->x - start->x);
                        float b = start->y - (slope * start->x);
                        float new_x = (y_min - b) / slope;
                        Coordinate newVertex(new_x, y_min);
                        postClipBottom.push_back(newVertex);
                        postClipBottom.push_back(*end);
                    }
                }
            } else if (start->y >= y_min ) { // from in
                if (end->y < y_min) { // to out
                    if (start->x == end->x) { // vertical line
                        Coordinate newVertex(start->x, y_min);
                        postClipBottom.push_back(newVertex);
                    } else {
                        float slope = (end->y - start->y) / (end->x - start->x);
                        float b = start->y - (slope * start->x);
                        float new_x = (y_min - b) / slope;
                        Coordinate newVertex(new_x, y_min);
                        postClipBottom.push_back(newVertex);
                    }
                } else if (end->y >= y_min) { // to in
                    postClipBottom.push_back(*end);
                }
            }
        }

        // clip top at y_max
        vector<Coordinate> postClipTop;
        for (int i = 0; i < postClipBottom.size(); i++) {

            Coordinate* start;
            Coordinate* end;
            if (i == postClipBottom.size() - 1) {
                start = &(postClipBottom.at(i));
                end = &(postClipBottom.at(0));
            } else {
                start = &(postClipBottom.at(i));
                end = &(postClipBottom.at(i+1));
            }

            if (start->y > x_max) { // from out
                if (end->y > x_max) { // to out
                    continue;
                } else if (end->y <= y_max) { // to in
                    if (start->x == end->x) { // vertical line
                        Coordinate newVertex(start->x, y_max);
                        postClipTop.push_back(newVertex);
                        postClipTop.push_back(*end);
                    } else {
                        float slope = (end->y - start->y) / (end->x - start->x);
                        float b = start->y - (slope * start->x);
                        float new_x = (y_max - b) / slope;
                        Coordinate newVertex(new_x, y_max);
                        postClipTop.push_back(newVertex);
                        postClipTop.push_back(*end);
                    }
                }
            } else if (start->y <= y_max ) { // from in
                if (end->y > y_max) { // to out
                    if (start->x == end->x) { // vertical line
                        Coordinate newVertex(start->x, y_max);
                        postClipTop.push_back(newVertex);
                    } else {
                        float slope = (end->y - start->y) / (end->x - start->x);
                        float b = start->y - (slope * start->x);
                        float new_x = (y_max - b) / slope;
                        Coordinate newVertex(new_x, y_max);
                        postClipTop.push_back(newVertex);
                    }
                } else if (end->y <= y_max) { // to in
                    postClipTop.push_back(*end);
                }
            }
        }

        // construct a new Polygon object with its new clipped vertices
        Polygon poly(postClipTop.size(), postClipTop);
        clippedPolygons.push_back(poly);
    }

    return clippedPolygons;
}
