#ifndef LINIA_H
#define LINIA_H

#include <QImage>

class Linia{
private:
    int startX;
    int startY;
    int endX;
    int endY;

    int colorR;
    int colorG;
    int colorB;

    QImage *img;

public:
    Linia();
    Linia(int sX,int sY,int eX,int eY,int colorR,int colorG,int colorB,QImage *img);
    ~Linia();

    int getStartX();
    int getStartY();
    int getEndX();
    int getEndY();

    static void drawLine(int sX,int sY,int eX,int eY,int colorR,int colorG,int colorB,QImage *img);

};

#endif // LINIA_H
