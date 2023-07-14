#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QPushButton>
#include <QGroupBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




    struct PunktyXYZ {
        float x;
        float y;
        float z;

        PunktyXYZ(float X, float Y, float Z){
            x=X;
            y=Y;
            z=Z;
        }
    };
private:

    QImage *img;

    int imageHeight;
    int imageWidth;
    int startX;
    int startY;

    int przesuniecieX;
    int przesuniecieY;
    int przesuniecieZ;
    double rotacjaX;
    double rotacjaY;
    double rotacjaZ;
    double rozmiar;

    QGroupBox *sterowanie;

    QSlider *przesuniecieX_Slider;
    QSlider *przesuniecieY_Slider;
    QSlider *przesuniecieZ_Slider;
    QSlider *RotacjaX_Slider;
    QSlider *RotacjaY_Slider;
    QSlider *RotacjaZ_Slider;
    QSlider *Skala_Slider;

    QPushButton *Exit;
    QPushButton *Reset;



    void clean();
    void inicjalizowanie(double **&Matrix);

    void rysowanieKostki();
    void rysowanieKrawedziKostki(PunktyXYZ srodek,PunktyXYZ przesuniecie, PunktyXYZ rotacja, float skala,float rozmiar);

    double **Matrix_Multiplication_3X3(double** First_Matrix, double** Second_Matrix);

private slots:

    void paintEvent(QPaintEvent *);

    void przesuniecieX_slot();
    void przesuniecieY_slot();
    void przesuniecieZ_slot();
    void rotacjaX_slot();
    void rotacjaY_slot();
    void rotacjaZ_slot();
    void skala_slot();

    void Reset_slot();



};
#endif // MAINWINDOW_H
