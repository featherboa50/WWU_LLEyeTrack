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

/*Finds the highlighted string in the dictionary and displays the info about it*/
void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_2->append("Definition should show up");
    ui->textEdit_3->append("Definition Name?");
}


/*Opens a file and displays it in the main text area*/
void MainWindow::on_pushButton_3_clicked()
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

    ui->textEdit->setText(in.readAll());
}

/*saves the current lesson*/
void MainWindow::on_pushButton_4_clicked()
{

}

/*saves the definition into the DB*/
void MainWindow::on_pushButton_clicked()
{

}
