#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->append("Hello world");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit_2->clear();
    ui->plainTextEdit->clear();
    ui->textEdit_2->append("Definition should show up");
    ui->plainTextEdit->appendPlainText("Definition Name?");
}


