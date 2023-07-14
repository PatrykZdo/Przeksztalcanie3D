#include "linia.h"
#include "pixel.h"

Linia::Linia(int sX,int sY,int eX,int eY,int colorR,int colorG,int colorB,QImage *img){
    this->startX=sX;
    this->startY=sY;
    this->endX=eX;
    this->endY=eY;
    this->img=img;
    this->colorR=colorR;
    this->colorG=colorG;
    this->colorB=colorB;

    drawLine(this->startX,this->startY,this->endX,this->endY,this->colorR,this->colorG,this->colorB,img);
}

Linia::~Linia(){};


int Linia::getStartX(){
    return this->startX;
}

int Linia::getStartY(){
    return this->startY;
}

int Linia::getEndX(){
    return this->endX;
}

int Linia::getEndY(){
    return this->endY;
}


void Linia::drawLine(int sX,int sY,int eX,int eY,int colorR,int colorG,int colorB,QImage *img){

        float a=(eY-sY)/(float)(eX-sX);
        float b=sY-(a*sX);

        int x=0;
        int y=0;

        if(sX==eX){
            if(sY<eY){
               for (y=sY;y<eY;y++){
                   Pixel::drawPixel(sX,y,colorR,colorG,colorB,img);
               }
            }
            else{
                for (y=sY;y>eY;y--){
                   Pixel::drawPixel(sX,y,colorR,colorG,colorB,img);
                }
            }
        }
        else if(sY==eY){
            if(sX<eX){
               for (x=sX;x<eX;x++){
                   Pixel::drawPixel(x,sY,colorR,colorG,colorB,img);
               }
            }
            else{
                for (x=sX;x>eX;x--){
                    Pixel::drawPixel(x,sY,colorR,colorG,colorB,img);
                }
            }
        }





        else if(abs(sX-eX)<abs(sY-eY)){
             if(sY<eY){
                for (y=sY;y<eY;y++){
                    x=(y-b)/a;
                    Pixel::drawPixel(x,y,colorR,colorG,colorB,img);
                }
             }
             else{
                 for (y=sY;y>eY;y--){
                     x=(y-b)/a;
                     Pixel::drawPixel(x,y,colorR,colorG,colorB,img);
                 }
             }
        }
        else{
            if(sX<eX){
               for (x=sX;x<eX;x++){
                   y=a*x+b;
                   Pixel::drawPixel(x,y,colorR,colorG,colorB,img);
               }
            }
            else{
                for (x=sX;x>eX;x--){
                    y=a*x+b;
                    Pixel::drawPixel(x,y,colorR,colorG,colorB,img);
                }
            }
        }
}
