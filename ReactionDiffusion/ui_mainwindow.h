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
#include <QtWidgets/QPushButton>

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

    // resetSimulation
    QPushButton *resetSimulationButton;

    // resetParameters
    QPushButton *resetParametersButton;


    // UI element spacing
    const int left = 10;
    const int height = 20;
    const int width = 100;
    const int textBoxLeft = left + width + left;
    const int textboxWidth = 30;

    int uiElementIndex = 1;
    float top(bool incrementIndex = true) {
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
        groupBox->setGeometry(QRect(10, 10, 160, 360));
        groupBox->setMinimumSize(QSize(0, 0));

        // dt
        dtLabel  = new QLabel(groupBox);
        dtLabel->setObjectName(QString::fromUtf8("dtLabel"));
        dtLabel->setText("Delta t");
        dtLabel->setGeometry(QRect(left, top(), width, height));

        dtSlider = new QSlider(groupBox);
        dtSlider->setObjectName(QString::fromUtf8("dtSlider"));
        dtSlider->setOrientation(Qt::Horizontal);
        dtSlider->setGeometry(QRect(left, top(false), width, height));

        dtTextbox = new QLineEdit(groupBox);
        dtTextbox->setObjectName(QString::fromUtf8("dtTextbox"));
        dtTextbox->setGeometry(QRect(textBoxLeft, top(), textboxWidth, height));

        // diffusionRateA
        diffusionRateALabel = new QLabel(groupBox);
        diffusionRateALabel->setObjectName(QString::fromUtf8("diffusionRateALabel"));
        diffusionRateALabel->setText("Diffusion Rate A");
        diffusionRateALabel->setGeometry(QRect(left, top(), width, height));

        diffusionRateASlider = new QSlider(groupBox);
        diffusionRateASlider->setObjectName(QString::fromUtf8("diffusionRateASlider"));
        diffusionRateASlider->setOrientation(Qt::Horizontal);
        diffusionRateASlider->setGeometry(QRect(left, top(false), width, height));

        diffusionRateATextbox = new QLineEdit(groupBox);
        diffusionRateATextbox->setObjectName(QString::fromUtf8("diffusionRateATextbox"));
        diffusionRateATextbox->setGeometry(QRect(textBoxLeft, top(), textboxWidth, height));

        // diffusionRateB
        diffusionRateBLabel = new QLabel(groupBox);
        diffusionRateBLabel->setObjectName(QString::fromUtf8("diffusionRateBLabel"));
        diffusionRateBLabel->setText("Diffusion Rate B");
        diffusionRateBLabel->setGeometry(QRect(left, top(), width, height));

        diffusionRateBSlider = new QSlider(groupBox);
        diffusionRateBSlider->setObjectName(QString::fromUtf8("diffusionRateBSlider"));
        diffusionRateBSlider->setOrientation(Qt::Horizontal);
        diffusionRateBSlider->setGeometry(QRect(left, top(false), width, height));

        diffusionRateBTextbox = new QLineEdit(groupBox);
        diffusionRateBTextbox->setObjectName(QString::fromUtf8("diffusionRateBTextbox"));
        diffusionRateBTextbox->setGeometry(QRect(textBoxLeft, top(), textboxWidth, height));

        // feedRate
        feedRateLabel = new QLabel(groupBox);
        feedRateLabel->setObjectName(QString::fromUtf8("feedRateLabel"));
        feedRateLabel->setText("Feed Rate");
        feedRateLabel->setGeometry(QRect(left, top(), width, height));

        feedRateSlider = new QSlider(groupBox);
        feedRateSlider->setObjectName(QString::fromUtf8("feedRateSlider"));
        feedRateSlider->setOrientation(Qt::Horizontal);
        feedRateSlider->setGeometry(QRect(left, top(false), width, height));

        feedRateTextbox = new QLineEdit(groupBox);
        feedRateTextbox->setObjectName(QString::fromUtf8("feedRateTextbox"));
        feedRateTextbox->setGeometry(QRect(textBoxLeft, top(), textboxWidth, height));

        // killRate
        killRateLabel = new QLabel(groupBox);
        killRateLabel->setObjectName(QString::fromUtf8("killRateLabel"));
        killRateLabel->setText("Kill Rate");
        killRateLabel->setGeometry(QRect(left, top(), width, height));

        killRateSlider = new QSlider(groupBox);
        killRateSlider->setObjectName(QString::fromUtf8("killRateSlider"));
        killRateSlider->setOrientation(Qt::Horizontal);
        killRateSlider->setGeometry(QRect(left, top(false), width, height));

        killRateTextbox = new QLineEdit(groupBox);
        killRateTextbox->setObjectName(QString::fromUtf8("killRateTextbox"));
        killRateTextbox->setGeometry(QRect(textBoxLeft, top(), textboxWidth, height));

        // resetSimulation
        top(); // creates additional vertical space
        resetSimulationButton = new QPushButton(groupBox);
        resetSimulationButton->setObjectName(QString::fromUtf8("resetSimulation"));
        resetSimulationButton->setText("Reset Simulation");
        resetSimulationButton->setGeometry(QRect(left, top(), width, height));
        QObject::connect(resetSimulationButton, SIGNAL(clicked()), MainWindow, SLOT(resetSimulation()));

        // resetParameters
        resetParametersButton = new QPushButton(groupBox);
        resetParametersButton->setObjectName(QString::fromUtf8("resetParameters"));
        resetParametersButton->setText("Reset Parameters");
        resetParametersButton->setGeometry(QRect(left, top(), width, height));
        QObject::connect(resetParametersButton, SIGNAL(clicked()), MainWindow, SLOT(resetParameters()));


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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Reaction Diffusion - Ezra Marks", nullptr));
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
