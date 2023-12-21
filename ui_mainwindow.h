/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <my_label.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    my_label *frame;
    QLabel *mouse_movement;
    QLabel *label_3;
    QLabel *mouse_pressed;
    QLabel *label_5;
    QFrame *x_axis;
    QFrame *y_axis;
    QCheckBox *show_axes;
    QPushButton *Draw;
    QSpinBox *circle_radius;
    QRadioButton *draw_circle;
    QRadioButton *draw_line;
    QPushButton *set_point1;
    QPushButton *set_point2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label;
    QTextEdit *radius_input;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QTextEdit *RxInput;
    QPushButton *pushButton_12;
    QTextEdit *RyInput;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QTextEdit *textEdit;
    QPushButton *pushButton_21;
    QTextEdit *textEdit_3;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_4;
    QTextEdit *textEdit_5;
    QPushButton *pushButton_22;
    QPushButton *pushButton_23;
    QTextEdit *textEdit_6;
    QTextEdit *textEdit_7;
    QPushButton *pushButton_24;
    QTextEdit *textEdit_8;
    QTextEdit *textEdit_9;
    QTextEdit *textEdit_10;
    QTextEdit *textEdit_11;
    QTextEdit *textEdit_12;
    QPushButton *pushButton_25;
    QTextEdit *textEdit_13;
    QTextEdit *textEdit_14;
    QPushButton *pushButton_26;
    QPushButton *pushButton_27;
    QPushButton *pushButton_28;
    QPushButton *pushButton_29;
    QPushButton *pushButton_30;
    QPushButton *pushButton_31;
    QPushButton *pushButton_32;
    QPushButton *pushButton_33;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1161, 788);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame = new my_label(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 700, 700));
        frame->setCursor(QCursor(Qt::CrossCursor));
        frame->setMouseTracking(true);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        frame->setFrameShape(QFrame::Box);
        frame->setLineWidth(1);
        mouse_movement = new QLabel(centralWidget);
        mouse_movement->setObjectName(QString::fromUtf8("mouse_movement"));
        mouse_movement->setGeometry(QRect(720, 70, 111, 31));
        mouse_movement->setFrameShape(QFrame::Panel);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(720, 50, 111, 20));
        mouse_pressed = new QLabel(centralWidget);
        mouse_pressed->setObjectName(QString::fromUtf8("mouse_pressed"));
        mouse_pressed->setGeometry(QRect(720, 140, 111, 31));
        mouse_pressed->setFrameShape(QFrame::Panel);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(730, 120, 81, 20));
        x_axis = new QFrame(centralWidget);
        x_axis->setObjectName(QString::fromUtf8("x_axis"));
        x_axis->setGeometry(QRect(0, 225, 700, 1));
        x_axis->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 255);"));
        x_axis->setFrameShape(QFrame::HLine);
        x_axis->setFrameShadow(QFrame::Sunken);
        y_axis = new QFrame(centralWidget);
        y_axis->setObjectName(QString::fromUtf8("y_axis"));
        y_axis->setGeometry(QRect(225, 0, 1, 700));
        y_axis->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(85, 255, 255);"));
        y_axis->setFrameShape(QFrame::VLine);
        y_axis->setFrameShadow(QFrame::Sunken);
        show_axes = new QCheckBox(centralWidget);
        show_axes->setObjectName(QString::fromUtf8("show_axes"));
        show_axes->setGeometry(QRect(720, 10, 91, 21));
        Draw = new QPushButton(centralWidget);
        Draw->setObjectName(QString::fromUtf8("Draw"));
        Draw->setGeometry(QRect(710, 290, 101, 41));
        circle_radius = new QSpinBox(centralWidget);
        circle_radius->setObjectName(QString::fromUtf8("circle_radius"));
        circle_radius->setGeometry(QRect(790, 190, 46, 20));
        draw_circle = new QRadioButton(centralWidget);
        draw_circle->setObjectName(QString::fromUtf8("draw_circle"));
        draw_circle->setGeometry(QRect(710, 190, 81, 17));
        draw_line = new QRadioButton(centralWidget);
        draw_line->setObjectName(QString::fromUtf8("draw_line"));
        draw_line->setGeometry(QRect(710, 240, 77, 17));
        set_point1 = new QPushButton(centralWidget);
        set_point1->setObjectName(QString::fromUtf8("set_point1"));
        set_point1->setGeometry(QRect(790, 240, 81, 23));
        set_point2 = new QPushButton(centralWidget);
        set_point2->setObjectName(QString::fromUtf8("set_point2"));
        set_point2->setGeometry(QRect(880, 240, 81, 23));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(710, 340, 101, 41));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(840, 290, 93, 28));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(710, 400, 101, 31));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(710, 450, 93, 28));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(710, 490, 81, 31));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(850, 350, 111, 28));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(710, 620, 81, 31));
        radius_input = new QTextEdit(centralWidget);
        radius_input->setObjectName(QString::fromUtf8("radius_input"));
        radius_input->setGeometry(QRect(840, 410, 91, 41));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(850, 320, 121, 28));
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(710, 530, 101, 31));
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(820, 530, 121, 31));
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(830, 570, 93, 28));
        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(840, 490, 101, 31));
        RxInput = new QTextEdit(centralWidget);
        RxInput->setObjectName(QString::fromUtf8("RxInput"));
        RxInput->setGeometry(QRect(850, 70, 41, 41));
        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(720, 580, 93, 28));
        RyInput = new QTextEdit(centralWidget);
        RyInput->setObjectName(QString::fromUtf8("RyInput"));
        RyInput->setGeometry(QRect(920, 70, 41, 41));
        pushButton_13 = new QPushButton(centralWidget);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(840, 610, 93, 28));
        pushButton_14 = new QPushButton(centralWidget);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(840, 460, 93, 28));
        pushButton_15 = new QPushButton(centralWidget);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setGeometry(QRect(850, 380, 93, 28));
        pushButton_16 = new QPushButton(centralWidget);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setGeometry(QRect(850, 190, 93, 28));
        pushButton_17 = new QPushButton(centralWidget);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setGeometry(QRect(850, 150, 93, 28));
        pushButton_18 = new QPushButton(centralWidget);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));
        pushButton_18->setGeometry(QRect(850, 10, 93, 28));
        pushButton_19 = new QPushButton(centralWidget);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setGeometry(QRect(850, 40, 93, 28));
        pushButton_20 = new QPushButton(centralWidget);
        pushButton_20->setObjectName(QString::fromUtf8("pushButton_20"));
        pushButton_20->setGeometry(QRect(1000, 610, 93, 28));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(993, 576, 101, 31));
        pushButton_21 = new QPushButton(centralWidget);
        pushButton_21->setObjectName(QString::fromUtf8("pushButton_21"));
        pushButton_21->setGeometry(QRect(990, 520, 93, 28));
        textEdit_3 = new QTextEdit(centralWidget);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setGeometry(QRect(1050, 480, 41, 31));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(990, 470, 41, 41));
        textEdit_4 = new QTextEdit(centralWidget);
        textEdit_4->setObjectName(QString::fromUtf8("textEdit_4"));
        textEdit_4->setGeometry(QRect(990, 380, 51, 41));
        textEdit_5 = new QTextEdit(centralWidget);
        textEdit_5->setObjectName(QString::fromUtf8("textEdit_5"));
        textEdit_5->setGeometry(QRect(1050, 380, 61, 41));
        pushButton_22 = new QPushButton(centralWidget);
        pushButton_22->setObjectName(QString::fromUtf8("pushButton_22"));
        pushButton_22->setGeometry(QRect(1000, 430, 93, 28));
        pushButton_23 = new QPushButton(centralWidget);
        pushButton_23->setObjectName(QString::fromUtf8("pushButton_23"));
        pushButton_23->setGeometry(QRect(1000, 330, 101, 31));
        textEdit_6 = new QTextEdit(centralWidget);
        textEdit_6->setObjectName(QString::fromUtf8("textEdit_6"));
        textEdit_6->setGeometry(QRect(1000, 280, 51, 41));
        textEdit_7 = new QTextEdit(centralWidget);
        textEdit_7->setObjectName(QString::fromUtf8("textEdit_7"));
        textEdit_7->setGeometry(QRect(1060, 280, 41, 41));
        pushButton_24 = new QPushButton(centralWidget);
        pushButton_24->setObjectName(QString::fromUtf8("pushButton_24"));
        pushButton_24->setGeometry(QRect(1010, 210, 93, 28));
        textEdit_8 = new QTextEdit(centralWidget);
        textEdit_8->setObjectName(QString::fromUtf8("textEdit_8"));
        textEdit_8->setGeometry(QRect(970, 170, 51, 31));
        textEdit_9 = new QTextEdit(centralWidget);
        textEdit_9->setObjectName(QString::fromUtf8("textEdit_9"));
        textEdit_9->setGeometry(QRect(1030, 170, 51, 31));
        textEdit_10 = new QTextEdit(centralWidget);
        textEdit_10->setObjectName(QString::fromUtf8("textEdit_10"));
        textEdit_10->setGeometry(QRect(1090, 170, 51, 31));
        textEdit_11 = new QTextEdit(centralWidget);
        textEdit_11->setObjectName(QString::fromUtf8("textEdit_11"));
        textEdit_11->setGeometry(QRect(970, 60, 51, 31));
        textEdit_12 = new QTextEdit(centralWidget);
        textEdit_12->setObjectName(QString::fromUtf8("textEdit_12"));
        textEdit_12->setGeometry(QRect(1030, 60, 51, 31));
        pushButton_25 = new QPushButton(centralWidget);
        pushButton_25->setObjectName(QString::fromUtf8("pushButton_25"));
        pushButton_25->setGeometry(QRect(980, 130, 93, 28));
        textEdit_13 = new QTextEdit(centralWidget);
        textEdit_13->setObjectName(QString::fromUtf8("textEdit_13"));
        textEdit_13->setGeometry(QRect(970, 100, 51, 31));
        textEdit_14 = new QTextEdit(centralWidget);
        textEdit_14->setObjectName(QString::fromUtf8("textEdit_14"));
        textEdit_14->setGeometry(QRect(1030, 100, 51, 31));
        pushButton_26 = new QPushButton(centralWidget);
        pushButton_26->setObjectName(QString::fromUtf8("pushButton_26"));
        pushButton_26->setGeometry(QRect(700, 650, 101, 31));
        pushButton_27 = new QPushButton(centralWidget);
        pushButton_27->setObjectName(QString::fromUtf8("pushButton_27"));
        pushButton_27->setGeometry(QRect(810, 680, 93, 28));
        pushButton_28 = new QPushButton(centralWidget);
        pushButton_28->setObjectName(QString::fromUtf8("pushButton_28"));
        pushButton_28->setGeometry(QRect(810, 650, 93, 28));
        pushButton_29 = new QPushButton(centralWidget);
        pushButton_29->setObjectName(QString::fromUtf8("pushButton_29"));
        pushButton_29->setGeometry(QRect(700, 680, 93, 28));
        pushButton_30 = new QPushButton(centralWidget);
        pushButton_30->setObjectName(QString::fromUtf8("pushButton_30"));
        pushButton_30->setGeometry(QRect(930, 680, 93, 28));
        pushButton_31 = new QPushButton(centralWidget);
        pushButton_31->setObjectName(QString::fromUtf8("pushButton_31"));
        pushButton_31->setGeometry(QRect(930, 640, 93, 28));
        pushButton_32 = new QPushButton(centralWidget);
        pushButton_32->setObjectName(QString::fromUtf8("pushButton_32"));
        pushButton_32->setGeometry(QRect(1040, 660, 93, 28));
        pushButton_33 = new QPushButton(centralWidget);
        pushButton_33->setObjectName(QString::fromUtf8("pushButton_33"));
        pushButton_33->setGeometry(QRect(1040, 690, 93, 28));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1161, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        frame->setText(QString());
        mouse_movement->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "    Mouse Movement", nullptr));
        mouse_pressed->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Mouse Pressed", nullptr));
        show_axes->setText(QCoreApplication::translate("MainWindow", "Show Axes", nullptr));
        Draw->setText(QCoreApplication::translate("MainWindow", "Draw", nullptr));
        draw_circle->setText(QCoreApplication::translate("MainWindow", "Draw Circle", nullptr));
        draw_line->setText(QCoreApplication::translate("MainWindow", "Draw Line", nullptr));
        set_point1->setText(QCoreApplication::translate("MainWindow", "Set point 1", nullptr));
        set_point2->setText(QCoreApplication::translate("MainWindow", "Set point 2", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "RESET", nullptr));
        pushButton_2->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Show Grid Real", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "DDA", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Bresenham", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "PolarCircle", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Time", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "BresenhamCircle", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Midpoint Circle", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Cartesian Circle ", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Cartesian", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "EllipseDrawing", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Ellipse", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "PolarEllipse", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "FloodFill4", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "FloodFill8", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "BoundaryFill4", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "BoundaryFill8", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "ClearEdgeList", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "Scanline", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "rotate", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "translate", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "shear", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "scale", nullptr));
        pushButton_24->setText(QCoreApplication::translate("MainWindow", "Rotate(wrt)", nullptr));
        pushButton_25->setText(QCoreApplication::translate("MainWindow", "Shear(wrt)", nullptr));
        pushButton_26->setText(QCoreApplication::translate("MainWindow", "CreateClipWindow", nullptr));
        pushButton_27->setText(QCoreApplication::translate("MainWindow", "ClipLine", nullptr));
        pushButton_28->setText(QCoreApplication::translate("MainWindow", "DrawWindow", nullptr));
        pushButton_29->setText(QCoreApplication::translate("MainWindow", "DrawLineForClip", nullptr));
        pushButton_30->setText(QCoreApplication::translate("MainWindow", "SetVertex", nullptr));
        pushButton_31->setText(QCoreApplication::translate("MainWindow", "ClipPolygon", nullptr));
        pushButton_32->setText(QCoreApplication::translate("MainWindow", "Reflect_x", nullptr));
        pushButton_33->setText(QCoreApplication::translate("MainWindow", "Reflect_y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
