#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets>

enum space_name
{
    rgb=0,
    xyz,
    lab
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




private slots:

    void on_color_pushButton_clicked();

    void on_red_rgb_slider_valueChanged(int value);

    void on_green_rgb_slider_valueChanged(int value);

    void on_blue_rgb_slider_valueChanged(int value);

    void on_red_rgb_spinBox_valueChanged(int arg1);

    void on_green_rgb_spinBox_valueChanged(int arg1);

    void on_blue_rgb_spinBox_valueChanged(int arg1);

    void on_red_xyz_slider_valueChanged(int value);

    void on_green_xyz_slider_valueChanged(int value);

    void on_blue_xyz_slider_valueChanged(int value);

    void on_red_xyz_doubleSpinBox_valueChanged(double arg1);

    void on_green_xyz_doubleSpinBox_valueChanged(double arg1);

    void on_blue_xyz_doubleSpinBox_valueChanged(double arg1);

    void on_L_lab_slider_valueChanged(int value);

    void on_a_lab_slider_valueChanged(int value);

    void on_b_lab_slider_valueChanged(int value);

    void on_L_lab_spinBox_valueChanged(int arg1);

    void on_a_lab_spinBox_valueChanged(int arg1);

    void on_b_lab_spinBox_valueChanged(int arg1);

private:
    QColor color;
    bool f = true;
    void updateColor();
    void updateRGB();
    double fromRGBtoXYZ(double a);
    double fromXYZtoLAB(double a);
    double fromLABtoXYZ(double a);
    double fromXYZtoRGB(double a);
    double changeRGBafterXYZ();
    void turnOff(bool);
    void on_xyz_sliders_to_rgb(double, double, double);
    void on_xyz_sliders_to_lab(double, double, double);
    void on_lab_sliders_to_rgb(double, double, double);
    void on_lab_sliders_to_xyz(double, double, double);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
