#include "filemanipulation.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "polygon.h"

using namespace std;

void readFile(char* fileName, vector<Polygon>& polygons) {

    ifstream inputFile(fileName);
    string line;
    int numPolygons;

    // General parsing algorithm taken from
    // https://stackoverflow.com/questions/39970420/c-parsing-data-from-file-i-o
    // and modified to fit this assignment

    // Get the number of polygons from the first line, then skip to description
    // of polygons
    inputFile >> numPolygons;
    getline(inputFile, line);
    getline(inputFile, line);

    for (int i = 0; i < numPolygons; i++) {

        // Get info about the current polygon
        int numVertices;
        inputFile >> numVertices;
        getline(inputFile, line);

        // Get info about the current polygon's vertices
        vector<Coordinate> coordinates;
        for (int j = 0; j < numVertices; j++) {

            float float_x, float_y;
            string string_x, string_y;
            getline(inputFile, line);
            istringstream coordinate(line);
            getline(coordinate, string_x, ' ');
            getline(coordinate, string_y);
            float_x = stof(string_x);
            float_y = stof(string_y);

            // Store current polygon's vertices info in a vector
            Coordinate point(float_x, float_y);
            coordinates.push_back(point);

        }

        // Store current polygon's info in a vector
        Polygon polygon(numVertices, coordinates);
        polygons.push_back(polygon);
        getline(inputFile, line);
    }

}

void writeFile(char* fileName, vector<Polygon>& polygons) {

    ofstream outputFile(fileName);

    outputFile << polygons.size() << "\n\n";

    for (vector<Polygon>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {
        outputFile << itr->numVertices << endl;
        for (vector<Coordinate>::iterator itr2 = (itr->vertices).begin(); itr2 != (itr->vertices).end(); itr2++) {
            outputFile << itr2->x << ' ' << itr2->y << endl;
        }
        outputFile << endl;
    }

}
