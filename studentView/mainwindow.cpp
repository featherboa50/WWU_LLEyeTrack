#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* closes the program down*/
void MainWindow::on_actionClose_triggered()
{
    this->close();
}

/* opens a file(.txt,.u8) and displays*/
void MainWindow::on_actionOpen_triggered()
{
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://", /*default folder opened*/
                "All files (*.*);;Text File (*.txt);;Unicode File (*.u8)"  /*file filter*/
                );
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0, tr("error info"),file.errorString());


    QTextStream in(&file);
    in.setCodec("UTF-8");

    ui->textBrowser->setText(in.readAll());

    /*start thread here for eyetracking?*/
}
