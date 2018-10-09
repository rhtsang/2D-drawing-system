#include <GL/glut.h>
#include <vector>
#include <iostream>
#include "polygon.h"
#include "filemanipulation.h"
#include "pixel.h"
#include "line.h"

float *PixelBuffer;
void display();

int main(int argc, char *argv[])
{

	// // User interaction
	// int polygonID, viewport_x, viewport_y;
	// //scaling factor, translation vector, rotation angle
	// cout << "Enter the ID of the polygon you want to manipulate: ";
	// cin >> polygonID;
	// cout << "Enter the width (x-length) of the viewport: ";
	// cin >> viewport_x;
	// cout << "Enter the height (y-length) of the viewport: ";
	// cin >> viewport_y;

	//allocate new pixel buffer, need initialization!!
	PixelBuffer = new float[200 * 200 * 3];

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	//set window size to 200*200
	glutInitWindowSize(200, 200);
	//set window position
	glutInitWindowPosition(100, 100);

	//create and set main window title
	int MainWindow = glutCreateWindow("Hello Graphics!");
	glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
	//sets display function
	glutDisplayFunc(display);

	vector<Polygon> polygons;
	readFile(argv[1], polygons);

// do drawing changes here, after reading input and before writing output

	writeFile(argv[2], polygons);

	Coordinate viewport(200,200);

	for (vector<Polygon>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {
		for (int i = 0; i < (itr->vertices).size(); i++) {
			if (i == (itr->vertices).size() - 1) {
				dda(PixelBuffer, (itr->vertices).at(i), (itr->vertices).at(0), viewport);
			} else {
	        	dda(PixelBuffer, (itr->vertices).at(i), (itr->vertices).at(i+1), viewport);
			}
	    }
	}

	glutMainLoop();//main display loop, will display until terminate

	return 0;
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
	//Misc.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//draws pixel on screen, width and height must match pixel buffer dimension
	glDrawPixels(200, 200, GL_RGB, GL_FLOAT, PixelBuffer);

	//window refresh
	glFlush();
}
