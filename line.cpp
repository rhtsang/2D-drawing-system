#include "line.h"
#include "pixel.h"
#include <math.h>
#include "polygon.h"
#include <iostream>

using namespace std;

void dda(float* PixelBuffer, Coordinate start, Coordinate end, Coordinate viewport) {

    // pretty much copy pasted from the book page 134
    int dx = end.x - start.x,
        dy = end.y - start.y,
        steps,
        k;
    float xIncrement, yIncrement, x = start.x, y = start.y;

    if (fabs(dx) > fabs(dy)) {
        steps = fabs(dx);
    } else {
        steps = fabs(dy);
    }

    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

    Coordinate roundedStart(round(start.x), round(start.y));
    setPixel(PixelBuffer, roundedStart, viewport);
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        Coordinate point(round(x), round(y));

        setPixel(PixelBuffer, point, viewport);
    }

}

void bresenham(float* PixelBuffer, Coordinate start, Coordinate end, Coordinate viewport) {

}
