#include "pixel.h"

Pixel::Pixel(int x, int y, QImage *img, int colorB = 0, int colorG = 0, int colorR = 0)
{
    this->x=x;
    this->y=y;
    this->colorB=colorB;
    this->colorG=colorG;
    this->colorR=colorR;
    this->img=img;

    drawPixel(x,y,colorB,colorG,colorR,img);
}

void Pixel::drawPixel(int x,int y,int colorR, int colorG, int colorB, QImage *img){
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();
    if(colorB>255){
        colorB=255;
    }
    else if(colorB<0){
        colorB=0;
    }

    if(colorG>255){
        colorG=255;
    }
    else if(colorG<0){
        colorG=0;
    }

    if(colorR>255){
        colorR=255;
    }
    else if(colorR<0){
        colorR=0;
    }

    if(x>=szer||x<0||y>=wys||y<0){
        return ;
    }

    ptr[szer*4*y + 4*x]=colorB;
    ptr[szer*4*y + 4*x + 1] = colorG;
    ptr[szer*4*y + 4*x + 2] = colorR;
}
