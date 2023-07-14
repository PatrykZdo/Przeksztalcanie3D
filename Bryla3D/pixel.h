#ifndef PIXEL_H
#define PIXEL_H

#include <Qimage>

class Pixel{
private:

    int x;
    int y;
    int colorB;
    int colorG;
    int colorR;

    QImage *img;


public:

    Pixel();
    Pixel(int x, int y, QImage *img, int colorB, int colorG, int colorR);
    ~Pixel();

    static void drawPixel(int x,int y,int colorR, int colorG, int colorB, QImage *img);
};

#endif // PIXEL_H
