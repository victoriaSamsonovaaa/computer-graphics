#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColor>
#include <QColorDialog>
#include <QtGlobal>
#include <QWidget>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //color = Qt::white;
    ui->red_rgb_spinBox->setRange(0, 255);
    ui->green_rgb_spinBox->setRange(0, 255);
    ui->blue_rgb_spinBox->setRange(0, 255);
    ui->red_rgb_slider->setRange(0, 255);
    ui->green_rgb_slider->setRange(0, 255);
    ui->blue_rgb_slider->setRange(0, 255);

    ui->red_xyz_doubleSpinBox->setRange(0, 96);
    ui->green_xyz_doubleSpinBox->setRange(0, 100);
    ui->blue_xyz_doubleSpinBox->setRange(0, 108);
    ui->red_xyz_slider->setRange(0, 96);
    ui->green_xyz_slider->setRange(0, 100);
    ui->blue_xyz_slider->setRange(0, 109);

    ui->L_lab_spinBox->setRange(0, 100);
    ui->L_lab_slider->setRange(0, 100);
    ui->a_lab_spinBox->setRange(-127, 128);
    ui->a_lab_slider->setRange(-127, 128);
    ui->b_lab_spinBox->setRange(-127, 128);
    ui->b_lab_slider->setRange(-127, 128);

    bool f = true;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateColor()
{
    ui->label->setStyleSheet("background-color: rgb(" + QString::number(color.red()) + ", " + QString::number(color.green()) +
                             ", " + QString::number(color.blue()) + ");");

    turnOff(1);
    updateRGB();
    double X,Y,Z;
    double r = color.red();
    double g = color.green();
    double b = color.blue();

    double Rn, Gn, Bn;
    Rn = qMin(qMax(0.0, fromRGBtoXYZ (r / 255.0) *100.0), 100.0);
    Gn = qMin(qMax(0.0, fromRGBtoXYZ (g / 255.0) *100.0), 100.0);
    Bn = qMin(qMax(0.0, fromRGBtoXYZ (b / 255.0) *100.0), 100.0);

    X = 0.412453*Rn + 0.357580*Gn + 0.180423* Bn;
    Y = 0.212671*Rn + 0.715160*Gn + 0.072169*Bn;
    Z = 0.019334*Rn + 0.119193*Gn + 0.950227*Bn;


    ui->blue_xyz_doubleSpinBox->setValue(Z);
    ui->blue_xyz_slider->setValue(Z);
    ui->red_xyz_doubleSpinBox->setValue(X);
    ui->red_xyz_slider->setValue(X);
    ui->green_xyz_doubleSpinBox->setValue(Y);
    ui->green_xyz_slider->setValue(Y);

    double L,A,B;

    double Xw = 95.047;
    double Yw = 100.0;
    double Zw = 108.883;

    L = 116.0 * fromXYZtoLAB(Y/Yw) -16.0;
    A = 500.0 * (fromXYZtoLAB(X/Xw) - fromXYZtoLAB(Y/Yw));
    B = 200.0 * (fromXYZtoLAB(Y/Yw) - fromXYZtoLAB(Z/Zw));

    ui->L_lab_slider->setValue(L);
    ui->L_lab_spinBox->setValue(L);
    ui->a_lab_slider->setValue(A);
    ui->a_lab_spinBox->setValue(A);
    ui->b_lab_slider->setValue(B);
    ui->b_lab_spinBox->setValue(B);

    turnOff(0);

}


void MainWindow::on_color_pushButton_clicked()
{
    QColorDialog* dialog = new QColorDialog;
    color = dialog->getColor();
    updateColor();
}

void MainWindow::updateRGB() {
    ui->red_rgb_spinBox->setValue(color.red());
    ui->green_rgb_spinBox->setValue(color.green());
    ui->blue_rgb_spinBox->setValue(color.blue());
    ui->red_rgb_slider->setValue(color.red());
    ui->green_rgb_slider->setValue(color.green());
    ui->blue_rgb_slider->setValue(color.blue());
}

double MainWindow::fromRGBtoXYZ(double a)
{
    double x = a;
    if (x >=  0.04045)
        return pow(( x + 0.055) / 1.055, 2.4);
    else return (x / 12.92);
}

double MainWindow::fromXYZtoLAB(double a)
{
    double x=a;
    if (x>= 0.008856)
        return pow(x,1.0/3.0);
    else return (7.787*x + 16.0/116.0);
}


double MainWindow::fromLABtoXYZ(double a)
{
    double x = a;
    if(pow(x,3)>= 0.008856)
    {
        return pow(x,3);
    }
    else return (x-16.0/116.0)/7.787;
}

double MainWindow::fromXYZtoRGB(double a)
{
    double x=a;
    if(x >= 0.0031308)
    {
        return (1.055*pow(x,1.0/2.4)-0.055);
    }
    else return 12.92*x;
}

void MainWindow::turnOff(bool flag)
{
    ui->red_rgb_slider->blockSignals(flag);
    ui->green_rgb_slider->blockSignals(flag);
    ui->blue_rgb_slider->blockSignals(flag);
    ui->red_xyz_slider->blockSignals(flag);
    ui->green_xyz_slider->blockSignals(flag);
    ui->blue_xyz_slider->blockSignals(flag);
    ui->L_lab_slider->blockSignals(flag);
    ui->a_lab_slider->blockSignals(flag);
    ui->b_lab_slider->blockSignals(flag);

    ui->red_rgb_spinBox->blockSignals(flag);
    ui->green_rgb_spinBox->blockSignals(flag);
    ui->blue_rgb_spinBox->blockSignals(flag);
    ui->red_xyz_doubleSpinBox->blockSignals(flag);
    ui->green_xyz_doubleSpinBox->blockSignals(flag);
    ui->blue_xyz_doubleSpinBox->blockSignals(flag);
    ui->L_lab_spinBox->blockSignals(flag);
    ui->a_lab_spinBox->blockSignals(flag);
    ui->b_lab_spinBox->blockSignals(flag);
}


void MainWindow::on_red_rgb_slider_valueChanged(int value)
{
    color.setRed(value);
    updateColor();
}


void MainWindow::on_green_rgb_slider_valueChanged(int value)
{
    color.setGreen(value);
    updateColor();
}


void MainWindow::on_blue_rgb_slider_valueChanged(int value)
{
    color.setBlue(value);
    updateColor();
}


void MainWindow::on_red_rgb_spinBox_valueChanged(int arg1)
{
    color.setRed(arg1);
    updateColor();
}


void MainWindow::on_green_rgb_spinBox_valueChanged(int arg1)
{
    color.setGreen(arg1);
    updateColor();
}


void MainWindow::on_blue_rgb_spinBox_valueChanged(int arg1)
{
    color.setBlue(arg1);
    updateColor();
}


void MainWindow::on_red_xyz_slider_valueChanged(int value)
{
    ui->red_xyz_doubleSpinBox->setValue(double(value));
    double X = double(value);
    double Y = double(ui->green_xyz_slider->value());
    double Z = double(ui->blue_xyz_slider->value());
    on_xyz_sliders_to_rgb(X, Y, Z);
    on_xyz_sliders_to_lab(X, Y, Z);
}


void MainWindow::on_green_xyz_slider_valueChanged(int value)
{
    ui->green_xyz_doubleSpinBox->setValue(double(value));
    double X = double(ui->red_xyz_slider->value());
    double Y = double(value);
    double Z = double(ui->blue_xyz_slider->value());
    on_xyz_sliders_to_rgb(X, Y, Z);
    on_xyz_sliders_to_lab(X, Y, Z);
}

void MainWindow::on_blue_xyz_slider_valueChanged(int value)
{
    ui->blue_xyz_doubleSpinBox->setValue(int(value));
    double X = double(ui->red_xyz_slider->value());
    double Y = double(ui->green_xyz_slider->value());
    double Z = double(value);
    on_xyz_sliders_to_rgb(X, Y, Z);
    on_xyz_sliders_to_lab(X, Y, Z);
}


void MainWindow::on_red_xyz_doubleSpinBox_valueChanged(double arg1)
{
    ui->red_rgb_slider->setValue(int(arg1));
    double X = double(arg1);
    double Y = double(ui->green_xyz_doubleSpinBox->value());
    double Z = double(ui->blue_xyz_doubleSpinBox->value());
    on_xyz_sliders_to_rgb(X, Y, Z);
    on_xyz_sliders_to_lab(X, Y, Z);
}


void MainWindow::on_green_xyz_doubleSpinBox_valueChanged(double arg1)
{
    ui->green_xyz_slider->setValue(int(arg1));
    double X = double(ui->red_xyz_doubleSpinBox->value());
    double Y = double(arg1);
    double Z = double(ui->blue_xyz_doubleSpinBox->value());
    on_xyz_sliders_to_rgb(X, Y, Z);
    on_xyz_sliders_to_lab(X, Y, Z);

}



void MainWindow::on_blue_xyz_doubleSpinBox_valueChanged(double arg1)
{
    ui->blue_xyz_slider->setValue(int(arg1));
    double X = double(ui->red_xyz_doubleSpinBox->value());
    double Y = double(ui->green_xyz_doubleSpinBox->value());
    double Z = double(arg1);
    on_xyz_sliders_to_rgb(X, Y, Z);
    on_xyz_sliders_to_lab(X, Y, Z);
}




void MainWindow::on_L_lab_slider_valueChanged(int value)
{
    ui->L_lab_spinBox->setValue(value);
    double L = double(value);
    double A = double(ui->a_lab_slider->value());
    double B = double(ui->a_lab_slider->value());
    on_lab_sliders_to_xyz(L, A, B);
    on_lab_sliders_to_rgb(L, A, B);

}


void MainWindow::on_a_lab_slider_valueChanged(int value)
{
    ui->a_lab_spinBox->setValue(value);
    double L = double(ui->L_lab_slider->value());
    double A = double(value);
    double B = double(ui->a_lab_slider->value());
    on_lab_sliders_to_xyz(L, A, B);
    on_lab_sliders_to_rgb(L, A, B);
}


void MainWindow::on_b_lab_slider_valueChanged(int value)
{
    ui->b_lab_spinBox->setValue(value);
    double L = double(ui->L_lab_slider->value());
    double A = double(ui->a_lab_slider->value());
    double B = double(value);
    on_lab_sliders_to_xyz(L, A, B);
    on_lab_sliders_to_rgb(L, A, B);
}


void MainWindow::on_L_lab_spinBox_valueChanged(int arg1)
{
    ui->L_lab_slider->setValue(arg1);
    double L = double(arg1);
    double A = double(ui->a_lab_spinBox->value());
    double B = double(ui->b_lab_spinBox->value());
    on_lab_sliders_to_xyz(L, A, B);
    on_lab_sliders_to_rgb(L, A, B);
}


void MainWindow::on_a_lab_spinBox_valueChanged(int arg1)
{
    ui->a_lab_slider->setValue(arg1);
    double L = double(ui->L_lab_spinBox->value());
    double A = double(arg1);
    double B = double(ui->b_lab_spinBox->value());
    on_lab_sliders_to_xyz(L, A, B);
    on_lab_sliders_to_rgb(L, A, B);
}


void MainWindow::on_b_lab_spinBox_valueChanged(int arg1)
{
    ui->b_lab_slider->setValue(arg1);
    double L = double(ui->L_lab_spinBox->value());
    double A = double(ui->a_lab_spinBox->value());
    double B = double(arg1);
    on_lab_sliders_to_xyz(L, A, B);
    on_lab_sliders_to_rgb(L, A, B);
}


void MainWindow::on_xyz_sliders_to_rgb(double X, double Y, double Z) {

    double R, G, B;
    double Rn = 3.2406*X/100 + (-1.5372)*Y/100 + (-0.4986)*Z/100;
    double Gn = (0.9689)*X/100 + 1.8758*Y/100 + 0.0415*Z/100;
    double Bn = 0.0557*X/100 + (0.2040)*Y/100 + 1.0570*Z/100;

    R = fromXYZtoRGB(Rn)*255;
    G = fromXYZtoRGB(Gn)*255;
    B = fromXYZtoRGB(Bn)*255;

    if (R == 0 || R > 255 || G == 0 || G > 255 || B == 0 || B > 255) {
        R = 255;
        G = 255;
        B = 255;
    }

    color.setRed(R);
    color.setGreen(G);
    color.setBlue(B);
    turnOff(1);
    updateRGB();
    turnOff(0);
    ui->label->setStyleSheet("background-color: rgb(" + QString::number(color.red()) + ", " + QString::number(color.green()) +
                             ", " + QString::number(color.blue()) + ");");

}

void MainWindow::on_xyz_sliders_to_lab(double X, double Y, double Z)
{
    double L,A,B;
    double Xw = 95.047;
    double Yw = 100.0;
    double Zw = 108.883;

    L = 116.0 * fromXYZtoLAB(Y/Yw) -16.0;
    A = 500.0 * (fromXYZtoLAB(X/Xw) - fromXYZtoLAB(Y/Yw));
    B = 200.0 * (fromXYZtoLAB(Y/Yw) - fromXYZtoLAB(Z/Zw));

    if (L < 0 || L > 100 || A < -127 || A > 127 || B < -127 || B > 127) {
        L = 100;
        A = 0;
        B = 0;
    }

    turnOff(1);
    ui->L_lab_slider->setValue(L);
    ui->L_lab_spinBox->setValue(L);
    ui->a_lab_slider->setValue(A);
    ui->a_lab_spinBox->setValue(A);
    ui->b_lab_slider->setValue(B);
    ui->b_lab_spinBox->setValue(B);
    turnOff(0);
}

void MainWindow::on_lab_sliders_to_rgb(double L, double A, double B)
{
    f = false;
    on_lab_sliders_to_xyz(L, A, B);
    f = true;
}

void MainWindow::on_lab_sliders_to_xyz(double L, double A, double B)
{
    double X, Y, Z;
    double Xw = 95.047;
    double Yw = 100.0;
    double Zw = 108.883;
    X = fromLABtoXYZ(A/500.0 + (L+16.0)/116.0)*Xw;
    Y = fromLABtoXYZ((L+16.0)/116.0)*Yw;
    Z = fromLABtoXYZ((L+16.0)/116.0 - B/200.0)*Zw;

    turnOff(1);
    ui->blue_xyz_doubleSpinBox->setValue(Z);
    ui->blue_xyz_slider->setValue(Z);
    ui->red_xyz_doubleSpinBox->setValue(X);
    ui->red_xyz_slider->setValue(X);
    ui->green_xyz_doubleSpinBox->setValue(Y);
    ui->green_xyz_slider->setValue(Y);
    turnOff(0);

    if (f = false) {
        on_xyz_sliders_to_rgb(X, Y, Z);
    }
}


