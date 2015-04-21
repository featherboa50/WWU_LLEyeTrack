#include "lessonwindow.h"
#include "ui_lessonwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

lessonWindow::lessonWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lessonWindow)
{
    ui->setupUi(this);
}

lessonWindow::~lessonWindow()
{
    delete ui;
}

/*Opens a file and displays it in the main text area*/
void lessonWindow::on_actionOpen_File_triggered()
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
    in.setCodec("UTF-8");

    ui->textEdit->setText(in.readAll());
}


void lessonWindow::on_actionSave_File_triggered()
{

}
