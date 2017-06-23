#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glwidget.h"

#include <QLabel>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void on_actionAcerca_de_triggered();
    void on_ruleLineEdit_editingFinished();
    void on_widthLineEdit_editingFinished();
    void on_heightLineEdit_editingFinished();
    void on_taoLineEdit_editingFinished();
    void on_functionComboBox_currentIndexChanged(int);
    void on_percentLineEdit_editingFinished();
    void on_percentHorizontalSlider_valueChanged(int);
    void on_stopPushButton_clicked();
    void on_pausePushButton_clicked();
    void on_playPushButton_clicked();
    void on_delayHorizontalSlider_valueChanged(int);

private:
    Ui::MainWindow *ui;
    GLWidget *gl;
    QLabel *statusLabel;
};

#endif // MAINWINDOW_H
