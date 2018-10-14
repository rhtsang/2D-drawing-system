#include "clip.h"

#include "polygon.h"
#include <vector>
#include <iostream>

using namespace std;

vector<Polygon> clip(vector<Polygon> polygons, float x_min, float x_max, float y_min, float y_max) {

    vector<Polygon> clippedPolygons;

    // loop through each polygon
    for (vector<Polygon>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {

        vector<Coordinate> clippedCoordinates;

        for (int i = 0; i < (itr->vertices).size(); i++) {

            Coordinate* start;
            Coordinate* end;
            start = &((itr->vertices).at(i));

            // if start point is already within the clip window, just add it
            if (start->x >= x_min && start->x <= x_max && start->y >= y_min && start->y <= y_max) {
                clippedCoordinates.push_back(*start);
                continue;
            }

            // else we need to calculate new vertex to push_back
            if (i == (itr->vertices).size() - 1) {
                end = &((itr->vertices).at(0));
            } else {
                end = &((itr->vertices).at(i+1));
            }

            if (start->x == end->x) { // if vertical line, can't calculate slope due to division by zero
            // check for horizontal line as well
                    ;
            } else { // normal line, so can calculate slope and use it
                float slope = (end->y - start->y) / (end->x - start->x);
                float b = start->y - (slope * start->x);
                // clip clockwise around clip window

                float left = slope * x_min + b;
                if (left >= y_min && left <= y_max) {
                    Coordinate newVertex(x_min, left);
                    clippedCoordinates.push_back(newVertex);
                } else if (left < y_min) {
                    Coordinate newVertex(x_min, y_min);
                    clippedCoordinates.push_back(newVertex);
                } else if (left > y_max) {
                    Coordinate newVertex(x_min, y_max);
                    clippedCoordinates.push_back(newVertex);
                }

                float top = (y_max - b) / slope;
                if (top >= x_min && top <= x_max) {
                    Coordinate newVertex(top, y_max);
                    clippedCoordinates.push_back(newVertex);
                } else if (top < x_min) {
                    Coordinate newVertex(x_min, y_max);
                    clippedCoordinates.push_back(newVertex);
                } else if (top > x_max) {
                    Coordinate newVertex(x_max, y_max);
                    clippedCoordinates.push_back(newVertex);
                }

                float right = (slope * x_max) + b;
                if (right >= y_min && right <= y_max) {
                    Coordinate newVertex(x_max, right);
                    clippedCoordinates.push_back(newVertex);
                } else if (right < y_min) {
                    Coordinate newVertex(x_max, y_min);
                    clippedCoordinates.push_back(newVertex);
                } else if (right > y_max) {
                    Coordinate newVertex(x_max, y_max);
                    clippedCoordinates.push_back(newVertex);
                }

                float bottom = (y_min - b) / slope;
                if (bottom >= x_min && bottom <= x_max) {
                    Coordinate newVertex(bottom, y_min);
                    clippedCoordinates.push_back(newVertex);
                } else if (bottom < x_min) {
                    Coordinate newVertex(x_min, y_min);
                    clippedCoordinates.push_back(newVertex);
                } else if (bottom > x_max) {
                    Coordinate newVertex(x_max, y_min);
                    clippedCoordinates.push_back(newVertex);
                }
            }

        }

        Polygon poly(clippedCoordinates.size(), clippedCoordinates);
        clippedPolygons.push_back(poly);

    }

    return clippedPolygons;
}
