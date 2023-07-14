#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <iostream>
#include "linia.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{

    setWindowTitle("Bryla 3D");

    resize(800,700);

    this->imageHeight = 600;
    this->imageWidth = 600;
    this->startX =25;
    this->startY = 25;

    img = new QImage(imageWidth,imageHeight,QImage::Format_RGB32);
    clean();

    sterowanie = new QGroupBox("Sterowanie",this);
    sterowanie->setGeometry(QRect(startX+imageWidth+startX,startY,800-imageWidth-2*startX,startY+300));

    QVBoxLayout *boxLayout = new QVBoxLayout;



    Exit = new QPushButton("Wyjscie");
    Reset = new QPushButton("Reset");
    connect(Reset,SIGNAL(clicked(bool)),this,SLOT(Reset_slot()));

    przesuniecieX_Slider = new QSlider(Qt::Horizontal,this);

    przesuniecieX_Slider -> setMinimum(-200);
    przesuniecieX_Slider -> setMaximum(200);
    przesuniecieX_Slider -> setValue(0);
    connect(przesuniecieX_Slider,SIGNAL(valueChanged(int)),this,SLOT(przesuniecieX_slot()));


    przesuniecieY_Slider = new QSlider(Qt::Horizontal,this);

    przesuniecieY_Slider -> setMinimum(-200);
    przesuniecieY_Slider -> setMaximum(200);
    przesuniecieY_Slider -> setValue(0);
    connect(przesuniecieY_Slider,SIGNAL(valueChanged(int)),this,SLOT(przesuniecieY_slot()));


    przesuniecieZ_Slider = new QSlider(Qt::Horizontal,this);

    przesuniecieZ_Slider -> setMinimum(-200);
    przesuniecieZ_Slider -> setMaximum(200);
    przesuniecieZ_Slider -> setValue(0);
    connect(przesuniecieZ_Slider,SIGNAL(valueChanged(int)),this,SLOT(przesuniecieZ_slot()));


    RotacjaX_Slider = new QSlider(Qt::Horizontal,this);

    RotacjaX_Slider -> setMinimum(0);
    RotacjaX_Slider -> setMaximum(360);
    RotacjaX_Slider -> setValue(0);
    connect(RotacjaX_Slider,SIGNAL(valueChanged(int)),this,SLOT(rotacjaX_slot()));


    RotacjaY_Slider = new QSlider(Qt::Horizontal,this);

    RotacjaY_Slider -> setMinimum(0);
    RotacjaY_Slider -> setMaximum(360);
    RotacjaY_Slider -> setValue(0);
    connect(RotacjaY_Slider,SIGNAL(valueChanged(int)),this,SLOT(rotacjaY_slot()));


    RotacjaZ_Slider = new QSlider(Qt::Horizontal,this);

    RotacjaZ_Slider -> setMinimum(0);
    RotacjaZ_Slider -> setMaximum(360);
    RotacjaZ_Slider -> setValue(0);
    connect(RotacjaZ_Slider,SIGNAL(valueChanged(int)),this,SLOT(rotacjaZ_slot()));


    Skala_Slider = new QSlider(Qt::Horizontal,this);

    Skala_Slider ->setMaximum(150);
    Skala_Slider ->setMinimum(10);
    Skala_Slider ->setValue(75);
    connect(Skala_Slider,SIGNAL(valueChanged(int)),this,SLOT(skala_slot()));


    boxLayout -> addWidget(Exit);
    boxLayout -> addWidget(przesuniecieX_Slider);
    boxLayout -> addWidget(przesuniecieY_Slider);
    boxLayout -> addWidget(przesuniecieZ_Slider);
    boxLayout -> addWidget(RotacjaX_Slider);
    boxLayout -> addWidget(RotacjaY_Slider);
    boxLayout -> addWidget(RotacjaZ_Slider);
    boxLayout -> addWidget(Skala_Slider);
    boxLayout -> addWidget(Reset);

    sterowanie -> setLayout(boxLayout);

    connect(Exit,SIGNAL(clicked()),this,SLOT(close()));

    przesuniecieX = 0;
    przesuniecieY = 0;
    przesuniecieZ = 0;
    rotacjaX = 0;
    rotacjaY = 0;
    rotacjaZ = 0;
    rozmiar = Skala_Slider->value();


    rysowanieKostki();
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(startX,startY,*img);
}

void MainWindow::clean(){
    unsigned char *ptr;
            ptr = img->bits();

            int i,j;
            for(i=0; i<imageHeight; i++)
            {
                for(j=0; j<imageWidth; j++)
                {
                    ptr[imageWidth*4*i + 4*j]=255; // Skladowa BLUE
                    ptr[imageWidth*4*i + 4*j + 1] = 255; // Skladowa GREEN
                    ptr[imageWidth*4*i + 4*j + 2] = 255; // Skladowa RED
                }
            }
    update();
}

void MainWindow::inicjalizowanie(double **&Matrix){
    Matrix = new double*[3];
    for(int i=0;i<3;i++){
        Matrix[i]=new double[3];
    }

}

double **MainWindow::Matrix_Multiplication_3X3(double** First_Matrix, double** Second_Matrix){
    double **Result_Matrix = new double*[3];
    for(int i=0;i<3;i++){
        Result_Matrix[i] = new double[3];
        for(int j=0;j<3;j++){
            Result_Matrix[i][j]=0;
        }
    }

    for (int i = 0; i < 3; i++ ){
        for (int j=0; j<3; j++){
            for(int k=0;k<3;k++){

                Result_Matrix[i][j]= Result_Matrix[i][j] + (First_Matrix[i][k]*Second_Matrix[k][j]);
            }
        }

    }
    return Result_Matrix;
}


void MainWindow::rysowanieKostki()
{
    PunktyXYZ srodekKostki(0,0,0);
    PunktyXYZ przesuniecie(przesuniecieX, przesuniecieY, przesuniecieZ);
    PunktyXYZ rotacja(rotacjaX, rotacjaY, rotacjaZ);
    clean();
    rysowanieKrawedziKostki(srodekKostki, przesuniecie, rotacja, 1, rozmiar);
    update();
}


void MainWindow::rysowanieKrawedziKostki(PunktyXYZ srodek, PunktyXYZ przesuniecie, PunktyXYZ obrot, float skala, float rozmiar) {
    PunktyXYZ wierzcholki[8] = {
        PunktyXYZ(srodek.x - rozmiar / 2, srodek.y - rozmiar / 2, srodek.z - rozmiar / 2),
        PunktyXYZ(srodek.x + rozmiar / 2, srodek.y - rozmiar / 2, srodek.z - rozmiar / 2),
        PunktyXYZ(srodek.x + rozmiar / 2, srodek.y + rozmiar / 2, srodek.z - rozmiar / 2),
        PunktyXYZ(srodek.x - rozmiar / 2, srodek.y + rozmiar / 2, srodek.z - rozmiar / 2),
        PunktyXYZ(srodek.x - rozmiar / 2, srodek.y - rozmiar / 2, srodek.z + rozmiar / 2),
        PunktyXYZ(srodek.x + rozmiar / 2, srodek.y - rozmiar / 2, srodek.z + rozmiar / 2),
        PunktyXYZ(srodek.x + rozmiar / 2, srodek.y + rozmiar / 2, srodek.z + rozmiar / 2),
        PunktyXYZ(srodek.x - rozmiar / 2, srodek.y + rozmiar / 2, srodek.z + rozmiar / 2)
    };

    for (int i=0;i<8;i++) {

        float x = obrot.x * M_PI / 180;
        float y = obrot.y * M_PI / 180;
        float z = obrot.z * M_PI / 180;

        double** macierzObrotuX = new double*[3] {
            new double[3] {1.0, 0.0, 0.0},
            new double[3] {0.0, cos(x), -sin(x)},
            new double[3] {0.0, sin(x), cos(x)}
        };

        double** macierzObrotuY = new double*[3] {
            new double[3]{cos(y), 0, sin(y)},
            new double[3]{0, 1, 0},
            new double[3]{-sin(y), 0, cos(y)}
        };

        double** macierzObrotuZ = new double*[3]{
            new double[3] {cos(z), -sin(z), 0},
            new double[3] {sin(z), cos(z), 0},
            new double[3] {0, 0, 1}
        };

        double** macierzObrotu = new double*[3]{
            new double[3] {1, 0, 0},
            new double[3] {0, 1, 0},
            new double[3] {0, 0, 1}
        };

        macierzObrotu = Matrix_Multiplication_3X3(macierzObrotuX,macierzObrotuY);

        double **aktualnaMacierz;
        inicjalizowanie(aktualnaMacierz);

        aktualnaMacierz = Matrix_Multiplication_3X3(macierzObrotu,macierzObrotuZ);


        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                macierzObrotu[i][j] = aktualnaMacierz[i][j];
            }
        }

        float rotacjaX = macierzObrotu[0][0] * wierzcholki[i].x + macierzObrotu[0][1] * wierzcholki[i].y + macierzObrotu[0][2] * wierzcholki[i].z;
        float rotacjaY = macierzObrotu[1][0] * wierzcholki[i].x + macierzObrotu[1][1] * wierzcholki[i].y + macierzObrotu[1][2] * wierzcholki[i].z;
        float rotacjaZ = macierzObrotu[2][0] * wierzcholki[i].x + macierzObrotu[2][1] * wierzcholki[i].y + macierzObrotu[2][2] * wierzcholki[i].z;

        wierzcholki[i] = PunktyXYZ(rotacjaX, rotacjaY, rotacjaZ);

        wierzcholki[i].x = wierzcholki[i].x + przesuniecie.x;
        wierzcholki[i].y = wierzcholki[i].y + przesuniecie.y;
        wierzcholki[i].z = wierzcholki[i].z + przesuniecie.z;

        wierzcholki[i].x = wierzcholki[i].x * skala;
        wierzcholki[i].y = wierzcholki[i].y * skala;
        wierzcholki[i].z = wierzcholki[i].z * skala;

        float Perspektywa= 180.0 / (180.0 + wierzcholki[i].z);
        if(Perspektywa < 11 && Perspektywa > 0){
        wierzcholki[i].x *= Perspektywa;
        wierzcholki[i].y *= Perspektywa;
        }
        else if(Perspektywa <0){
            wierzcholki[i].x *= 100;
            wierzcholki[i].y *= 100;
        }
        else if(Perspektywa > 11){
            wierzcholki[i].x *= 100;
            wierzcholki[i].y *= 100;
        }
    }

    int polowa = imageWidth / 2;

    int krawedzie[12][2]={
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4},
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7}
    };

    for (int i=0;i<12;i++) {
        int index1 = krawedzie[i][0];
        int index2 = krawedzie[i][1];

        int pixelX1 = (polowa + wierzcholki[index1].x);
        int pixelY1 = (polowa + wierzcholki[index1].y);

        int pixelX2 = (polowa + wierzcholki[index2].x);
        int pixelY2 = (polowa + wierzcholki[index2].y);

        Linia::drawLine(pixelX1, pixelY1, pixelX2, pixelY2,0,0,0,img);
    }
}

void MainWindow::przesuniecieX_slot(){
    this -> przesuniecieX = przesuniecieX_Slider ->value();
    rysowanieKostki();
}
void MainWindow::przesuniecieY_slot(){
    this -> przesuniecieY = przesuniecieY_Slider ->value();
    rysowanieKostki();
}
void MainWindow::przesuniecieZ_slot(){
    this -> przesuniecieZ = przesuniecieZ_Slider ->value();
    rysowanieKostki();
}
void MainWindow::rotacjaX_slot(){
    this -> rotacjaX = RotacjaX_Slider ->value();
    rysowanieKostki();
}
void MainWindow::rotacjaY_slot(){
    this -> rotacjaY = RotacjaY_Slider ->value();
    rysowanieKostki();
}
void MainWindow::rotacjaZ_slot(){
    this -> rotacjaZ = RotacjaZ_Slider ->value();
    rysowanieKostki();
}
void MainWindow::skala_slot(){
    this -> rozmiar = Skala_Slider ->value();
    rysowanieKostki();
}


void MainWindow::Reset_slot(){
    przesuniecieX_Slider ->setValue(0);
    przesuniecieY_Slider ->setValue(0);
    przesuniecieZ_Slider ->setValue(0);
    RotacjaX_Slider -> setValue(0);
    RotacjaY_Slider -> setValue(0);
    RotacjaZ_Slider -> setValue(0);
    Skala_Slider -> setValue(50);

    this -> przesuniecieX = przesuniecieX_Slider ->value();
    this -> przesuniecieY = przesuniecieY_Slider ->value();
    this -> przesuniecieZ = przesuniecieZ_Slider ->value();
    this -> rotacjaX = RotacjaX_Slider ->value();
    this -> rotacjaY = RotacjaY_Slider ->value();
    this -> rotacjaZ = RotacjaZ_Slider ->value();
    this -> rozmiar = Skala_Slider ->value();
    clean();
    rysowanieKostki();
}
