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



void MainWindow::on_actionClose_triggered()
{
    this->close();
}

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
        QMessageBox::information(0, tr("info"),file.errorString());

    QTextStream in(&file);

    ui->textBrowser->setText(in.readAll());
}
