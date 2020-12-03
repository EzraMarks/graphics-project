/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDial>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QGroupBox *groupBox;

    // Pointers to UI elements
    // dt
    QLabel *dtLabel;
    QLineEdit *dtTextbox;
    QSlider *dtSlider;
    // diffusionRateA
    QLabel *diffusionRateALabel;
    QLineEdit *diffusionRateATextbox;
    QSlider *diffusionRateASlider;
    // diffusionRateB
    QLabel *diffusionRateBLabel;
    QLineEdit *diffusionRateBTextbox;
    QSlider *diffusionRateBSlider;
    // feedRate
    QLabel *feedRateLabel;
    QLineEdit *feedRateTextbox;
    QSlider *feedRateSlider;
    // killRate
    QLabel *killRateLabel;
    QLineEdit *killRateTextbox;
    QSlider *killRateSlider;


    // UI element spacing
    const int height = 20;
    const int labelWidth = 140;
    const int sliderWidth = 120;
    const int textboxWidth = 40;

    int uiElementIndex = 1;
    float verticalOffset(bool incrementIndex = true) {
        int offset = uiElementIndex * (height + 5);
        if (incrementIndex) {
            uiElementIndex++;
        }
        return offset;
    }

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(960, 540);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setMinimumSize(QSize(100, 160));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 160, 334));
        groupBox->setMinimumSize(QSize(0, 0));

        // dt
        dtLabel  = new QLabel(groupBox);
        dtLabel->setObjectName(QString::fromUtf8("dtLabel"));
        dtLabel->setText("Delta t");
        dtLabel->setGeometry(QRect(0, verticalOffset(), labelWidth, height));

        dtSlider = new QSlider(groupBox);
        dtSlider->setObjectName(QString::fromUtf8("dtSlider"));
        dtSlider->setOrientation(Qt::Horizontal);
        dtSlider->setGeometry(QRect(0, verticalOffset(false), sliderWidth, height));

        dtTextbox = new QLineEdit(groupBox);
        dtTextbox->setObjectName(QString::fromUtf8("dtTextbox"));
        dtTextbox->setGeometry(QRect(120, verticalOffset(), textboxWidth, height));

        // diffusionRate
        diffusionRateALabel  = new QLabel(groupBox);
        diffusionRateALabel->setObjectName(QString::fromUtf8("diffusionRateALabel"));
        diffusionRateALabel->setText("Diffusion Rate A");
        diffusionRateALabel->setGeometry(QRect(0, verticalOffset(), labelWidth, height));

        diffusionRateASlider = new QSlider(groupBox);
        diffusionRateASlider->setObjectName(QString::fromUtf8("diffusionRateASlider"));
        diffusionRateASlider->setOrientation(Qt::Horizontal);
        diffusionRateASlider->setGeometry(QRect(0, verticalOffset(false), sliderWidth, height));

        diffusionRateATextbox = new QLineEdit(groupBox);
        diffusionRateATextbox->setObjectName(QString::fromUtf8("diffusionRateATextbox"));
        diffusionRateATextbox->setGeometry(QRect(sliderWidth, verticalOffset(), textboxWidth, height));






        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Lab 7 - Framebuffers", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
