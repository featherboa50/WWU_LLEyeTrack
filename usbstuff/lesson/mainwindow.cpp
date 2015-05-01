#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dictionary()
{
    ui->setupUi(this);
    // open & read default dictionary

}


MainWindow::~MainWindow(){
    delete ui;
}


// Finds the highlighted string in the dictionary and displays the definition
void MainWindow::on_viewDefButton_clicked(){
    ui-> textEdit_2 ->setText( "Definition should show up" );
    ui-> word       ->setText( ui->textEdit->textCursor().selectedText() );
}


void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);
    collectCoordinates();
}


void MainWindow::collectCoordinates(){
    ui -> textEdit -> clear();
    for( int i = 0 ; i < lessonText.size() ; i++ ){
        // get image1
        ui -> textEdit -> append( " " + lessonText[i] );
        // get image2
        // coordinate temp = getCoordinatePair();
        //
    }
}


// Saves the definition into the DB
void MainWindow::on_saveDefButton_clicked(){

}


// Opens a file and displays it in the main text area
void MainWindow::on_actionOpen_triggered(){

    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                  "C://", // default folder opened
                  "All files (*.*);;Text File (*.txt);;Unicode File (*.u8)"  // file filter
                );
    QFile file(filename);
    if( ! file.open(QIODevice::ReadOnly) )
        QMessageBox::information( 0, tr("error info"), file.errorString() );

    QTextStream in( &file );
    in.setCodec("UTF-8");

    ui->textEdit->setText( in.readAll() );
}


// Saves the current lesson
void MainWindow::on_actionSave_triggered(){
    //QString lesson = QString::fromUtf8(ui->textEdit->toPlainText());
    QString lesson = ui->textEdit->toPlainText();
    QString filename=QFileDialog::getSaveFileName(this, tr("Save File"), "C://",
                                                    "All files (*.*);;Text File (*.txt);;Unicode File (*.u8)"  /*file filter*/
                                                    );
    if(filename.isEmpty())
        return;
    else{
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::information(this, tr("unable to save"),
                                     file.errorString());
            return;
        }
        QTextStream out(&file);
        // SET version??
        //out.setGenerateByteOrderMark(true);
        out.setCodec("UTF-8");
        out << lesson << endl;
        out.flush();
        file.close();
    }

}


// Switch to lesson view
void MainWindow::on_actionLesson_triggered(){

}


// Switch to student view
void MainWindow::on_actionStudent_triggered(){

}
