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
#include <QtWidgets/QColorDialog>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
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

    // loadImage
    QPushButton *loadImageButton;

    // color
    QColorDialog *colorDialog;
    QPushButton *openColorDialogButton;

    // resetSimulation
    QPushButton *resetSimulationButton;

    // resetParameters
    QPushButton *resetParametersButton;


    // UI element spacing
    const int left = 10;
    const int height = 22;
    const int gap = 10;
    const int width = 100;
    const int textBoxLeft = left + width + left;
    const int textboxWidth = 30;

    int topTotal = 0;
    float top(int y) {
        topTotal += y;
        return topTotal;
    }

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(960, 540);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
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
        dockWidget->setMinimumSize(QSize(100, 160));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 160, 452));

        // dt
        dtLabel  = new QLabel(groupBox);
        dtLabel->setObjectName(QString::fromUtf8("dtLabel"));
        dtLabel->setText("Delta t");
        dtLabel->setGeometry(QRect(left, top(height + gap), width, height));

        dtSlider = new QSlider(groupBox);
        dtSlider->setObjectName(QString::fromUtf8("dtSlider"));
        dtSlider->setOrientation(Qt::Horizontal);
        dtSlider->setGeometry(QRect(left, top(height), width, height));

        dtTextbox = new QLineEdit(groupBox);
        dtTextbox->setObjectName(QString::fromUtf8("dtTextbox"));
        dtTextbox->setGeometry(QRect(textBoxLeft, top(0), textboxWidth, height));

        // diffusionRateA
        diffusionRateALabel = new QLabel(groupBox);
        diffusionRateALabel->setObjectName(QString::fromUtf8("diffusionRateALabel"));
        diffusionRateALabel->setText("Diffusion Rate A");
        diffusionRateALabel->setGeometry(QRect(left, top(height + gap), width, height));

        diffusionRateASlider = new QSlider(groupBox);
        diffusionRateASlider->setObjectName(QString::fromUtf8("diffusionRateASlider"));
        diffusionRateASlider->setOrientation(Qt::Horizontal);
        diffusionRateASlider->setGeometry(QRect(left, top(height), width, height));

        diffusionRateATextbox = new QLineEdit(groupBox);
        diffusionRateATextbox->setObjectName(QString::fromUtf8("diffusionRateATextbox"));
        diffusionRateATextbox->setGeometry(QRect(textBoxLeft, top(0), textboxWidth, height));

        // diffusionRateB
        diffusionRateBLabel = new QLabel(groupBox);
        diffusionRateBLabel->setObjectName(QString::fromUtf8("diffusionRateBLabel"));
        diffusionRateBLabel->setText("Diffusion Rate B");
        diffusionRateBLabel->setGeometry(QRect(left, top(height + gap), width, height));

        diffusionRateBSlider = new QSlider(groupBox);
        diffusionRateBSlider->setObjectName(QString::fromUtf8("diffusionRateBSlider"));
        diffusionRateBSlider->setOrientation(Qt::Horizontal);
        diffusionRateBSlider->setGeometry(QRect(left, top(height), width, height));

        diffusionRateBTextbox = new QLineEdit(groupBox);
        diffusionRateBTextbox->setObjectName(QString::fromUtf8("diffusionRateBTextbox"));
        diffusionRateBTextbox->setGeometry(QRect(textBoxLeft, top(0), textboxWidth, height));

        // feedRate
        feedRateLabel = new QLabel(groupBox);
        feedRateLabel->setObjectName(QString::fromUtf8("feedRateLabel"));
        feedRateLabel->setText("Feed Rate");
        feedRateLabel->setGeometry(QRect(left, top(height + gap), width, height));

        feedRateSlider = new QSlider(groupBox);
        feedRateSlider->setObjectName(QString::fromUtf8("feedRateSlider"));
        feedRateSlider->setOrientation(Qt::Horizontal);
        feedRateSlider->setGeometry(QRect(left, top(height), width, height));

        feedRateTextbox = new QLineEdit(groupBox);
        feedRateTextbox->setObjectName(QString::fromUtf8("feedRateTextbox"));
        feedRateTextbox->setGeometry(QRect(textBoxLeft, top(0), textboxWidth, height));

        // killRate
        killRateLabel = new QLabel(groupBox);
        killRateLabel->setObjectName(QString::fromUtf8("killRateLabel"));
        killRateLabel->setText("Kill Rate");
        killRateLabel->setGeometry(QRect(left, top(height + gap), width, height));

        killRateSlider = new QSlider(groupBox);
        killRateSlider->setObjectName(QString::fromUtf8("killRateSlider"));
        killRateSlider->setOrientation(Qt::Horizontal);
        killRateSlider->setGeometry(QRect(left, top(height), width, height));

        killRateTextbox = new QLineEdit(groupBox);
        killRateTextbox->setObjectName(QString::fromUtf8("killRateTextbox"));
        killRateTextbox->setGeometry(QRect(textBoxLeft, top(0), textboxWidth, height));

        // loadImage
        loadImageButton = new QPushButton(groupBox);
        loadImageButton->setObjectName(QString::fromUtf8("loadImage"));
        loadImageButton->setText("Load Image");
        loadImageButton->setGeometry(QRect(left, top(height + 3*gap), width, height));
        QObject::connect(loadImageButton, SIGNAL(clicked()), MainWindow, SLOT(fileOpen()));

        // color
        colorDialog = new QColorDialog(groupBox);
        QObject::connect(colorDialog, SIGNAL(currentColorChanged(QColor)), MainWindow, SLOT(selectColor(QColor)));

        openColorDialogButton = new QPushButton(groupBox);
        openColorDialogButton->setObjectName(QString::fromUtf8("openColorDialog"));
        openColorDialogButton->setText("Select Color");
        openColorDialogButton->setGeometry(QRect(left, top(height + gap), width, height));
        QObject::connect(openColorDialogButton, SIGNAL(clicked()), MainWindow, SLOT(openColorDialog()));

        // resetSimulation
        resetSimulationButton = new QPushButton(groupBox);
        resetSimulationButton->setObjectName(QString::fromUtf8("resetSimulation"));
        resetSimulationButton->setText("Reset Simulation");
        resetSimulationButton->setGeometry(QRect(left, top(height + gap), width, height));
        QObject::connect(resetSimulationButton, SIGNAL(clicked()), MainWindow, SLOT(resetSimulation()));

        // resetParameters
        resetParametersButton = new QPushButton(groupBox);
        resetParametersButton->setObjectName(QString::fromUtf8("resetParameters"));
        resetParametersButton->setText("Reset Parameters");
        resetParametersButton->setGeometry(QRect(left, top(height + gap), width, height));
        QObject::connect(resetParametersButton, SIGNAL(clicked()), MainWindow, SLOT(resetParameters()));


        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(fileOpen()));
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Reaction Diffusion - Ezra Marks", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
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
