#include "clip.h"

#include "polygon.h"
#include <vector>
#include <iostream>

using namespace std;

vector<Polygon> clip(vector<Polygon> polygons, int x_min, int x_max, int y_min, int y_max) {
    vector<Polygon> clippedPolygons;

    // loop through each polygon
    for (vector<Polygon>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {

        vector<Coordinate> clippedCoordinates;

        // loop through current polygon's vertices
        for (int i = 0; i < (itr->vertices).size(); i++) {

            Coordinate* start;
            Coordinate* end;

            if (i == (itr->vertices).size() - 1) { // if at last vertex, wrap around to beginning
                start = &((itr->vertices).at(i));
                end = &((itr->vertices).at(0));
            } else {
                start = &((itr->vertices).at(i));
                end = &((itr->vertices).at(i+1));
            }

            //cout << "reading: " << start->x << " " << start->y << endl;

            if (start->x == end->x || start->y == end->y) { // if vertical or horizontal line, use this block to avoid division by 0
                //cout << "straight line at " << start->x << " " <<  start->y << " to " << end->x << " " << end->y << endl;
                if (start->x >= x_min && start->x <= x_max && start->y >= y_min && start->y <= y_max) { // start vertex in window
                    clippedCoordinates.push_back(*start);
                    cout << start->x << " " << start->y << endl;
                    // continue;
                // start vertex not in window
                // so clip along vertical edge
                } else if (start->x == end->x) {
                    if (start->x < x_min) { // use x_min
                        if (start->y < y_min) { // use y_min
                            Coordinate newVertex(x_min, y_min);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else if (start->y > y_max) { // use y_max
                            Coordinate newVertex(x_min, y_max);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else { // inside y ranges
                            Coordinate newVertex(x_min, start->y);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        }
                    } else if (start->x > x_max) { // use x_max
                        if (start->y < y_min) { // use y_min
                            Coordinate newVertex(x_max, y_min);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else if (start->y > y_max) { // use y_max
                            Coordinate newVertex(x_max, y_max);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else { // inside y ranges
                            Coordinate newVertex(x_max, start->y);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        }
                    } else { // use current x
                        if (start->y < y_min) { // use y_min
                            Coordinate newVertex(start->x, y_min);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else if (start->y > y_max) { // use y_max
                            Coordinate newVertex(start->x, y_max);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else { // inside y ranges
                            Coordinate newVertex(start->x, start->y);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        }
                    }
                // clip along horizontal edge
                } else if (start->y == end->y) {
                    if (start->y < y_min) {
                        if (start->x < x_min) { // use x_min
                            Coordinate newVertex(x_min, y_min);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else if (start->x > x_max) { // use x_max
                            Coordinate newVertex(x_max, y_min);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else { // inside x ranges
                            Coordinate newVertex(start->x, start->y);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        }
                    } else if (start->y > y_max) {
                        if (start->x < x_min) { // use x_min
                            Coordinate newVertex(x_min, y_max);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else if (start->x > x_max) { // use x_max
                            Coordinate newVertex(x_max, y_max);
                            clippedCoordinates.push_back(newVertex);
                            cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        } else { // inside x ranges
                            Coordinate newVertex(start->x, start->y);
                            clippedCoordinates.push_back(newVertex);
                            //cout << newVertex.x << " " << newVertex.y << endl;
                            //continue;
                        }
                    }
                }
                continue;
            }
//cout << "slope" << endl;


            float slope = (end->y - start->y) / (end->x - start->x);
            float b = start->y - (slope * start->x);
            //cout << slope << endl;
            //cout << b << endl;

            if (start->x >= x_min && start->x <= x_max && start->y >= y_min && start->y <= y_max) { // start vertex in window
                clippedCoordinates.push_back(*start);
                //cout << "what" << endl;
            } else { // current vertex not in window, need to find new vertex to push

                // check which edge to clip on
                if (start->x < x_min) { // use x_min
                    if (start->y < y_min) { // use y_min
                        Coordinate newVertex(x_min, y_min);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    } else if (start->y > y_max) { // use y_max
                        Coordinate newVertex(x_min, y_max);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    } else { // inside y ranges
                        float y = slope * x_min + b;
                        Coordinate newVertex(x_min, y);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    }
                } else if (start->x > x_max) { // use x_max
                    if (start->y < y_min) { // use y_min
                        Coordinate newVertex(x_max, y_min);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    } else if (start->y > y_max) { // use y_max
                        Coordinate newVertex(x_max, y_max);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    } else { // inside y ranges
                        float y = slope * x_max + b;
                        Coordinate newVertex(x_max, y);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    }
                } else if (start->y < y_min) {
                    float x = (y_min - b) / slope;
                    Coordinate newVertex(x, y_min);
                    clippedCoordinates.push_back(newVertex);
                } else if (start->y > y_max) {
                    float x = (y_max - b) / slope;
                    Coordinate newVertex(x, y_max);
                    clippedCoordinates.push_back(newVertex);
                }
            }

//if (i != (itr->vertices).size() - 1) {
            if (end->x >= x_min && end->x <= x_max && end->y >= y_min && end->y <= y_max) { // end vertex in window
                // do nothing? and just continue to next iteration?
            } else { // end vertex not in window, so need to find new vertex
                if (end->x < x_min) { // use x_min
                    if (end->y < y_min) { // use y_min
                        Coordinate newVertex(x_min, y_min);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    } else if (end->y > y_max) { // use y_max
                        Coordinate newVertex(x_min, y_max);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    } else { // inside y ranges
                        float y = slope * x_min + b;
                        Coordinate newVertex(x_min, y);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    }
                } else if (end->x > x_max) { // use x_max
                    if (end->y < y_min) { // use y_min
                        Coordinate newVertex(x_max, y_min);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    } else if (end->y > y_max) { // use y_max
                        Coordinate newVertex(x_max, y_max);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    } else { // inside y ranges
                        float y = slope * x_max + b;
                        Coordinate newVertex(x_max, y);
                        clippedCoordinates.push_back(newVertex);
                        //continue;
                    }
                } else if (end->y < y_min) {
                    float x = (y_min - b) / slope;
                    Coordinate newVertex(x, y_min);
                    clippedCoordinates.push_back(newVertex);
                } else if (end->y > y_max) {
                    float x = (y_max - b) / slope;
                    Coordinate newVertex(x, y_max);
                    clippedCoordinates.push_back(newVertex);
                }
            }
//}
        }

        Polygon poly(clippedCoordinates.size(), clippedCoordinates);
        clippedPolygons.push_back(poly);

    }

    return clippedPolygons;
}
