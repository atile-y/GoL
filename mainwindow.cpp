#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    double per = ui->percentHorizontalSlider->value()/10.0;
    ui->percentLineEdit->setText(QString::number(per));

    gl = new GLWidget();
    gl->setRule(ui->ruleLineEdit->text());
    gl->setWidth(ui->widthLineEdit->text().toUInt());
    gl->setHeight(ui->heightLineEdit->text().toUInt());
    gl->setTao(ui->taoLineEdit->text().toUInt());
    gl->setPercent(per);

    connect(ui->actionAcerca_de_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    setFixedSize(geometry().width(), geometry().height());
    move(100, 100);

    statusLabel = new QLabel(tr(""), this);
    ui->statusBar->addWidget(statusLabel);
    ui->statusBar->setSizeGripEnabled(false);
}

MainWindow::~MainWindow(){
    delete ui;
    delete gl;
}

void MainWindow::closeEvent(QCloseEvent *event){
    gl->reset();
    gl->close();
    event->accept();
}

void MainWindow::on_actionAcerca_de_triggered(){
    QString str;
    str =   "<h3 style=\"text-align: center\"><b>Instituto Politécnico Nacional</b></h3>"
            "<h3 style=\"text-align: center\"><b>Escuela Superior de Cómputo</b></h3>"
            "<table style=\"margin: 25px 30px 25px 0px\">"
                "<tr>"
                    "<td style=\"padding-right: 20px\">Unidad de Aprendizaje:</td>"
                    "<td><b>Sistemas Complejos</b></td>"
                "</tr>"
                "<tr>"
                    "<td>Grupo:</td>"
                    "<td><b>3CM5</b></td>"
                "</tr>"
                "<tr>"
                    "<td>Periodo:</td>"
                    "<td><b>2017/2</b></td>"
                "</tr>"
                "<tr>"
                    "<td>Desarrollado por:</td>"
                    "<td><b>Alejandro Alberto Yescas Benítez</b></td>"
                "</tr>"
                "<tr>"
                    "<td>Correo:</td>"
                    "<td><b>alex.yescas.b@gmail.com</b></td>"
                "</tr>"
            "</table>";

    QMessageBox::about(this, tr("Acerca de"), str);
}

void MainWindow::on_ruleLineEdit_editingFinished(){
    int pos = 0;
    QString str = ui->ruleLineEdit->text();
    QRegExpValidator *v = new QRegExpValidator(QRegExp("B[0-8]{1,2}/S[0-8]{1,2}"), this);

    if( v->validate(str, pos) != QValidator::Acceptable ){
        ui->ruleLineEdit->setText(gl->getRule());
        return;
    }
    if( gl->getRule() == str )
        return;

    gl->setRule(str);
}

void MainWindow::on_widthLineEdit_editingFinished(){
    int pos = 0;
    QString str = ui->widthLineEdit->text();

    QIntValidator *v = new QIntValidator(this);
    v->setBottom(2);

    if( v->validate(str, pos) != QValidator::Acceptable ){
        ui->widthLineEdit->setText(QString::number(gl->getWidth()));
        return;
    }
    if( gl->getWidth() == str.toUInt() )
        return;

    gl->setWidth(str.toUInt());
}

void MainWindow::on_heightLineEdit_editingFinished(){
    int pos = 0;
    QString str = ui->heightLineEdit->text();

    QIntValidator *v = new QIntValidator(this);
    v->setBottom(2);

    if( v->validate(str, pos) != QValidator::Acceptable ){
        ui->heightLineEdit->setText(QString::number(gl->getHeight()));
        return;
    }
    if( gl->getHeight() == str.toUInt() )
        return;

    gl->setHeight(str.toUInt());
}

void MainWindow::on_taoLineEdit_editingFinished(){
    int pos = 0;
    QString str = ui->taoLineEdit->text();

    QIntValidator *v = new QIntValidator(2, 20, this);

    if( v->validate(str, pos) != QValidator::Acceptable ){
        ui->taoLineEdit->setText(QString::number(gl->getTao()));
        return;
    }
    if( gl->getTao() == str.toUInt() )
        return;

    gl->setTao(str.toUInt());
}

void MainWindow::on_functionComboBox_currentIndexChanged(int index){
    switch(index){
    case 0:
        if( gl->getFunction() == Function::MAX )
            return;
        gl->setFunction(Function::MAX);
        break;

    case 1:
        if( gl->getFunction() == Function::MIN )
            return;
        gl->setFunction(Function::MIN);
        break;

    case 2:
        if( gl->getFunction() == Function::PAR )
            return;
        gl->setFunction(Function::PAR);
        break;

    default:
        return;
    }
}

void MainWindow::on_percentLineEdit_editingFinished(){
    int pos = 0;
    QString str = ui->percentLineEdit->text();
    QDoubleValidator *v = new QDoubleValidator(0.0, 100.0, 6, this);

    if( v->validate(str, pos) != QValidator::Acceptable ){
        ui->percentLineEdit->setText(QString::number(gl->getPercent()));
        return;
    }
    if( gl->getPercent() == str.toDouble() )
        return;

    gl->setPercent(str.toDouble());
    bool s = ui->percentHorizontalSlider->blockSignals(true);
    ui->percentHorizontalSlider->setValue((int)(gl->getPercent()*10 + 0.5));
    ui->percentHorizontalSlider->blockSignals(s);
}

void MainWindow::on_percentHorizontalSlider_valueChanged(int value){
    gl->setPercent(value/10.0);
    ui->percentLineEdit->setText(QString::number(gl->getPercent()));
}

void MainWindow::on_stopPushButton_clicked(){
    gl->reset();
    gl->hide();

    ui->stopPushButton->setEnabled(false);
    ui->pausePushButton->setEnabled(false);
    ui->playPushButton->setEnabled(true);
    ui->delayHorizontalSlider->setEnabled(false);
    ui->ruleLineEdit->setEnabled(true);
    ui->widthLineEdit->setEnabled(true);
    ui->heightLineEdit->setEnabled(true);
    ui->taoLineEdit->setEnabled(true);
    ui->functionComboBox->setEnabled(true);
    ui->percentLineEdit->setEnabled(true);
    ui->percentHorizontalSlider->setEnabled(true);

    statusLabel->setText(tr(""));
    ui->statusBar->showMessage(tr("Detenido"), 2000);
}

void MainWindow::on_pausePushButton_clicked(){
    gl->pause();

    ui->pausePushButton->setEnabled(false);
    ui->playPushButton->setEnabled(true);
    ui->delayHorizontalSlider->setEnabled(false);

    statusLabel->setText(tr("Pausado"));
}

void MainWindow::on_playPushButton_clicked(){
    gl->play();
    gl->show();
    gl->setDelay(ui->delayHorizontalSlider->value());

    ui->stopPushButton->setEnabled(true);
    ui->pausePushButton->setEnabled(true);
    ui->playPushButton->setEnabled(false);
    ui->delayHorizontalSlider->setEnabled(true);
    ui->ruleLineEdit->setEnabled(false);
    ui->widthLineEdit->setEnabled(false);
    ui->heightLineEdit->setEnabled(false);
    ui->taoLineEdit->setEnabled(false);
    ui->functionComboBox->setEnabled(false);
    ui->percentLineEdit->setEnabled(false);
    ui->percentHorizontalSlider->setEnabled(false);

    statusLabel->setText(QString("Corriendo a %1 ms").arg(gl->getDelay()));
}

void MainWindow::on_delayHorizontalSlider_valueChanged(int value){
    gl->setDelay(value);
    statusLabel->setText(QString("Corriendo a %1 ms").arg(gl->getDelay()));
}
