#include "clip.h"

#include "polygon.h"
#include <vector>
#include <iostream>
#include <cstdlib>

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
                float new_x, new_y;
                if (start->x >= x_min && start->x <= x_max) {
                    new_x = start->x;
                } else if (start->x < x_min) {
                    new_x = x_min;
                } else if (start->x > x_max) {
                    new_x = x_max;
                }
                //cout << new_x << endl;
                if (start->y < y_min) {
                    if ((end->y >= y_min && end->y < y_max) || (end->y < y_min)) {
                        new_y = y_min;
                        Coordinate newVertex(new_x, new_y);
                        clippedCoordinates.push_back(newVertex);
                    } else if (end->y >= y_max) {
                        new_y = y_min;
                        Coordinate newVertex(new_x, new_y);
                        clippedCoordinates.push_back(newVertex);
                        new_y = y_max;
                        Coordinate newVertex2(new_x, new_y);
                        clippedCoordinates.push_back(newVertex2);
                    }
                } else if (start->y > y_max) {
                    if ((end->y > y_min && end->y <= y_max) || (end->y > y_max)) {
                        new_y = y_max;
                        Coordinate newVertex(new_x, new_y);
                        clippedCoordinates.push_back(newVertex);
                    } else if (end->y <= y_min) {
                        new_y = y_max;
                        Coordinate newVertex(new_x, new_y);
                        clippedCoordinates.push_back(newVertex);
                        new_y = y_min;
                        Coordinate newVertex2(new_x, new_y);
                        clippedCoordinates.push_back(newVertex2);
                    }
                } else if (start->y >= y_min && start->y <= y_max) {
                    if (end->y >= y_min && end->y <= y_max) {
                        Coordinate newVertex(new_x, start->y);
                        clippedCoordinates.push_back(newVertex);
                        Coordinate newVertex2(new_x, end->y);
                        clippedCoordinates.push_back(newVertex2);
                    } else if (end->y < y_min) {
                        Coordinate newVertex(new_x, start->y);
                        clippedCoordinates.push_back(newVertex);
                        Coordinate newVertex2(new_x, y_min);
                        clippedCoordinates.push_back(newVertex2);
                    } else if (end->y > y_max) {
                        Coordinate newVertex(new_x, start->y);
                        clippedCoordinates.push_back(newVertex);
                        Coordinate newVertex2(new_x, y_max);
                        clippedCoordinates.push_back(newVertex2);
                    }
                }
            } else if (start->y == end->y) { // same thing w horizontal lines
                float new_x, new_y;
                if (start->y >= y_min && start->y <= y_max) {
                    new_y = start->y;
                } else if (start->y < y_min) {
                    new_y = y_min;
                } else if (start->y > y_max) {
                    new_y = y_max;
                }
                if (start->x < x_min) {
                    if ((end->x >= x_min && end->x < x_max) || (end->x < x_min)) {
                        new_x = x_min;
                        Coordinate newVertex(new_x, new_y);
                        clippedCoordinates.push_back(newVertex);
                    } else if (end->x >= x_max) {
                        new_x = x_min;
                        Coordinate newVertex(new_x, new_y);
                        clippedCoordinates.push_back(newVertex);
                        new_x = x_max;
                        Coordinate newVertex2(new_x, new_y);
                        clippedCoordinates.push_back(newVertex2);
                    }
                } else if (start->x > x_max) {
                    if ((end->x > x_min && end->x <= x_max) || (end->x > x_max)) {
                        new_x = x_max;
                        Coordinate newVertex(new_x, new_y);
                        clippedCoordinates.push_back(newVertex);
                    } else if (end->x <= x_min) {
                        new_x = x_max;
                        Coordinate newVertex(new_x, new_y);
                        clippedCoordinates.push_back(newVertex);
                        new_x = x_min;
                        Coordinate newVertex2(new_x, new_y);
                        clippedCoordinates.push_back(newVertex2);
                    }
                } else if (start->x >= x_min && start->x <= x_max) {
                    if (end->x >= x_min && end->x <= x_max) {
                        Coordinate newVertex(start->x, new_y);
                        clippedCoordinates.push_back(newVertex);
                        Coordinate newVertex2(end->x, new_y);
                        clippedCoordinates.push_back(newVertex2);
                    } else if (end->x < x_min) {
                        Coordinate newVertex(start->x, new_y);
                        clippedCoordinates.push_back(newVertex);
                        Coordinate newVertex2(x_min, new_y);
                        clippedCoordinates.push_back(newVertex2);
                    } else if (end->x > x_max) {
                        Coordinate newVertex(start->x, new_y);
                        clippedCoordinates.push_back(newVertex);
                        Coordinate newVertex2(x_max, new_y);
                        clippedCoordinates.push_back(newVertex2);
                    }
                }
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
