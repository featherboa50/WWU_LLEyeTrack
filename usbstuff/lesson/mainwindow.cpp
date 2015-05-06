#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>


#define $MW MainWindow::


$MW MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    dictionary()
{
    ui-> setupUi(this);

    // open & read default dictionary

    QString path = QCoreApplication::applicationDirPath();
    path.append("/EyetrackerDictionary.txt");
    QFile dictFile( "//stuhome/home/mccormk5/Desktop/CS_493/WWU_LLEyeTrack/usbstuff/lesson/EyetrackerDictionary.txt" );

    if( !dictFile.open( QIODevice::ReadOnly ) )
        ui-> lessonTextBox-> append( "Failed to open dictionary file.\n" );
    else
        readDictionary( dictFile );

    showFullScreen();

    editorMode = false;
    on_modeSwitch_toggled( false );
}


$MW ~MainWindow(){
    delete ui;
}


// Finds the highlighted string in the dictionary and displays the definition
void $MW on_viewDefButton_clicked(){
    auto word = ui-> lessonTextBox-> textCursor().selectedText();
    ui-> wordBox-> setText( word );
    ui-> defnBox-> setText( dictionary[word] );
}


// Save the definition into the DB
void $MW on_saveDefButton_clicked(){
    auto word          = ui-> lessonTextBox-> textCursor().selectedText();
    dictionary[ word ] = ui-> defnBox-> toPlainText();
}


void $MW resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent( event ); // Call super
    //collectCoordinates();              // Recollect with new x/y values
}


void $MW collectCoordinates(){
    ui-> lessonTextBox-> clear();
    for( int i = 0 ; i < lessonText.size() ; i++ ){

        saveFirstImage();

        ui-> lessonTextBox-> append( " " + lessonText[i] );

        coordinate temp = getCoordinatePair();

        // TODO: append temp & lessonText[i] to coordinate / word list
    }
}


void $MW saveFirstImage(){
    // TODO:
    // Save off screen capture of the first image
}


coordinate $MW getCoordinatePair(){
    // TODO:
    // Screen capture the second image.
    // Compare w/ first image using openCV.
    // Return text box coordinates.

    return coordinate( 0, 0, 0, 0 ); // placeholder
}


// Opens a file and displays it in the main text area
void $MW on_actionOpen_triggered(){

    QString filename = QFileDialog::getOpenFileName(
                this,
                tr( "Open File" ),
                "C://",                                                    // Default folder opened
                "All files (*.*);;Text File (*.txt);;Unicode File (*.u8)"  // File filter
              );

    QFile file(filename);

    if( ! file.open( QIODevice::ReadOnly ) ){
        QMessageBox::information( 0, tr("error info"), file.errorString() );
        return;
    }

    QTextStream in( &file );
    in.setCodec( "UTF-8" );

    // TODO: replace the call below with coordinate collection when
    //       collectCoordinates() has been fully written.
    ui-> lessonTextBox-> setText( in.readAll() );
}


// Saves the current lesson
void $MW on_actionSave_triggered(){

    QString lesson = ui-> lessonTextBox-> toPlainText();

    QString filename = QFileDialog::getSaveFileName(
                         this,
                         tr("Save File"),
                         "C://",
                         "All files (*.*);;Text File (*.txt);;Unicode File (*.u8)"  // file filter
                       );

    if( filename.isEmpty() )
        return;

    QFile file( filename );

    if( ! file.open( QIODevice::WriteOnly ) ){
        QMessageBox::information(
                                 this,
                                 tr("unable to save"),
                                 file.errorString()
                                );
        return;
    }

    QTextStream out( &file );
    // SET version??
    //out.setGenerateByteOrderMark(true);
    out.setCodec( "UTF-8" );
    out << lesson << endl;
    out.flush();
    file.close();
}


void $MW on_modeSwitch_toggled( bool inEditorMode ){
    ui-> saveDefButton-> setVisible( inEditorMode );
    ui-> viewDefButton-> setVisible( inEditorMode );
    ui->  editorLabel -> setVisible( inEditorMode );

    ui-> lessonTextBox-> setReadOnly( !inEditorMode );
    ui-> defnBox      -> setReadOnly( !inEditorMode );

    editorMode = inEditorMode;
}


void $MW readDictionary( QFile& dict ){
    int x = 0;
    while( !dict.atEnd() ){
        QString     line = dict.readLine();
        QStringList splt = line.split("\t");
        if( splt.size() < 2 )
            continue;
        dictionary.insert( splt.at(0), splt.at(1) );
    }
}


void MainWindow::on_minimize_triggered(){
    showMinimized();
}


void MainWindow::on_close_triggered(){
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Closing application", "Are you sure you want to close?",
                                    QMessageBox::Yes | QMessageBox::No);
      if (reply == QMessageBox::Yes)
        QApplication::quit();
}
