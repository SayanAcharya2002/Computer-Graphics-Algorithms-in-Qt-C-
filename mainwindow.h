#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <utility>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void Mouse_Pressed();
    void showMousePosition(QPoint& pos);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_show_axes_clicked();

    void on_Draw_clicked();

    void on_set_point1_clicked();

    void on_set_point2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_textEdit_textChanged();

    void on_radius_input_textChanged();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_RxInput_textChanged();

    void on_RyInput_textChanged();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

private:
    Ui::MainWindow *ui;
    QPoint p1,p2;
    std::pair<int,int> first_point;
    std::pair<int,int> second_point;
    std::pair<int,int> axis_boxes;

    void point(int,int);
    void fill_box(std::pair<int,int>,QRgb=qRgb(3, 252, 236));
    void toggle_box(std::pair<int,int> p,QRgb color_now=qRgb(3, 252, 236));
    bool in_map(int x,int y);
    void draw_axes(QRgb=qRgb(252, 3, 173));
    QRgb axis_color=qRgb(252, 3, 173);
    std::pair<int,int> convert_to_xy(int,int);
    std::pair<int,int> convert_to_ij(int,int);
    void draw_line(const std::pair<int,int>&,const std::pair<int,int>&);
};

#endif // MAINWINDOW_H
