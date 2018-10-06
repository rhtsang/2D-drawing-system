

void setPixel(float* PixelBuffer, int x, int y, int viewport_x, int viewport_y) {
    int index = (3 * viewport_x * y) + (3 * x);
    PixelBuffer[index] = PixelBuffer[index+1] = PixelBuffer[index+2] = 1;
}
