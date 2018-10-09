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

    float slope = (end.y - start.y) / (end.x - start.x);
if (fabs(slope) < 1) {
    int dx = fabs(end.x - start.x),
        dy = fabs(end.y - start.y),
        p = 2 * dy - dx,
        twoDy = 2 * dy,
        twoDyMinusDx = 2 * (dy - dx),
        x, y;

    if (start.x > end.x) {
        x = end.x;
        y = end.y;
        end.x = start.x;
    } else {
        x = start.x;
        y = start.y;
    }

    Coordinate roundedStart(round(x), round(y));
    setPixel(PixelBuffer, roundedStart, viewport);


    while (x < end.x) {
        x++;
        if (p < 0) {
            p += twoDy;
        } else {
            y++;
            p += twoDyMinusDx;
        }
        Coordinate point(round(x), round(y));
        setPixel(PixelBuffer, point, viewport);
    }
} else if (fabs(slope) > 1) {
    int dx = fabs(end.x - start.x),
        dy = fabs(end.y - start.y),
        p = 2 * dx - dy,
        twoDy = 2 * dx,
        twoDyMinusDx = 2 * (dx - dy),
        x, y;

    if (start.y > end.y) {
        x = end.x;
        y = end.y;
        end.y = start.y;
    } else {
        x = start.x;
        y = start.y;
    }

    Coordinate roundedStart(round(x), round(y));
    setPixel(PixelBuffer, roundedStart, viewport);


    while (y < end.y) {
        y++;
        if (p < 0) {
            p += twoDy;
        } else {
            x++;
            p += twoDyMinusDx;
        }
        Coordinate point(round(x), round(y));
        setPixel(PixelBuffer, point, viewport);
    }
}
}
