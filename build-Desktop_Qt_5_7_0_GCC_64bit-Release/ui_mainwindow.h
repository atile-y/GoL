/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *ruleLabel;
    QLineEdit *ruleLineEdit;
    QLabel *widthLabel;
    QLineEdit *widthLineEdit;
    QLabel *heightLabel;
    QLineEdit *heightLineEdit;
    QLabel *percentLabel;
    QLineEdit *percentLineEdit;
    QSlider *percentHorizontalSlider;
    QPushButton *stopPushButton;
    QPushButton *pausePushButton;
    QPushButton *playPushButton;
    QSlider *delayHorizontalSlider;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(301, 291);
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(20, 20, 261, 161));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        ruleLabel = new QLabel(formLayoutWidget);
        ruleLabel->setObjectName(QStringLiteral("ruleLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, ruleLabel);

        ruleLineEdit = new QLineEdit(formLayoutWidget);
        ruleLineEdit->setObjectName(QStringLiteral("ruleLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, ruleLineEdit);

        widthLabel = new QLabel(formLayoutWidget);
        widthLabel->setObjectName(QStringLiteral("widthLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, widthLabel);

        widthLineEdit = new QLineEdit(formLayoutWidget);
        widthLineEdit->setObjectName(QStringLiteral("widthLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, widthLineEdit);

        heightLabel = new QLabel(formLayoutWidget);
        heightLabel->setObjectName(QStringLiteral("heightLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, heightLabel);

        heightLineEdit = new QLineEdit(formLayoutWidget);
        heightLineEdit->setObjectName(QStringLiteral("heightLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, heightLineEdit);

        percentLabel = new QLabel(formLayoutWidget);
        percentLabel->setObjectName(QStringLiteral("percentLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, percentLabel);

        percentLineEdit = new QLineEdit(formLayoutWidget);
        percentLineEdit->setObjectName(QStringLiteral("percentLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, percentLineEdit);

        percentHorizontalSlider = new QSlider(formLayoutWidget);
        percentHorizontalSlider->setObjectName(QStringLiteral("percentHorizontalSlider"));
        percentHorizontalSlider->setMaximum(1000);
        percentHorizontalSlider->setSingleStep(10);
        percentHorizontalSlider->setPageStep(50);
        percentHorizontalSlider->setValue(500);
        percentHorizontalSlider->setOrientation(Qt::Horizontal);
        percentHorizontalSlider->setInvertedControls(true);

        formLayout->setWidget(4, QFormLayout::SpanningRole, percentHorizontalSlider);

        stopPushButton = new QPushButton(centralWidget);
        stopPushButton->setObjectName(QStringLiteral("stopPushButton"));
        stopPushButton->setEnabled(false);
        stopPushButton->setGeometry(QRect(60, 190, 32, 32));
        stopPushButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopPushButton->setIcon(icon);
        stopPushButton->setIconSize(QSize(32, 32));
        stopPushButton->setFlat(true);
        pausePushButton = new QPushButton(centralWidget);
        pausePushButton->setObjectName(QStringLiteral("pausePushButton"));
        pausePushButton->setEnabled(false);
        pausePushButton->setGeometry(QRect(130, 190, 32, 32));
        pausePushButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pausePushButton->setIcon(icon1);
        pausePushButton->setIconSize(QSize(32, 32));
        pausePushButton->setFlat(true);
        playPushButton = new QPushButton(centralWidget);
        playPushButton->setObjectName(QStringLiteral("playPushButton"));
        playPushButton->setGeometry(QRect(200, 190, 32, 32));
        playPushButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        playPushButton->setIcon(icon2);
        playPushButton->setIconSize(QSize(32, 32));
        playPushButton->setFlat(true);
        delayHorizontalSlider = new QSlider(centralWidget);
        delayHorizontalSlider->setObjectName(QStringLiteral("delayHorizontalSlider"));
        delayHorizontalSlider->setEnabled(false);
        delayHorizontalSlider->setGeometry(QRect(20, 230, 261, 21));
        delayHorizontalSlider->setMaximum(200);
        delayHorizontalSlider->setValue(100);
        delayHorizontalSlider->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Game of Life", 0));
        ruleLabel->setText(QApplication::translate("MainWindow", "Regla", 0));
        ruleLineEdit->setText(QApplication::translate("MainWindow", "B3/S23", 0));
        widthLabel->setText(QApplication::translate("MainWindow", "Ancho", 0));
        widthLineEdit->setText(QApplication::translate("MainWindow", "100", 0));
        heightLabel->setText(QApplication::translate("MainWindow", "Altura", 0));
        heightLineEdit->setText(QApplication::translate("MainWindow", "100", 0));
        percentLabel->setText(QApplication::translate("MainWindow", "Porcentaje 1's", 0));
        percentLineEdit->setText(QApplication::translate("MainWindow", "50", 0));
        stopPushButton->setText(QString());
        pausePushButton->setText(QString());
        playPushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
