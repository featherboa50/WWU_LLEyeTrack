#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <qpoint.h>
#include <qabstracttextdocumentlayout.h>
#include <qtextedit.h>
#include <ctime>

#define $MW MainWindow::

$MW MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    dictionary()
{
    ui-> setupUi(this);

    // open & read default dictionary

    editorMode = false;
    on_modeSwitch_toggled( false );
    //ui-> wordBox-> setReadOnly( true );

    collectCoordinates();
}


$MW ~MainWindow(){
    delete ui;
}

void $MW initializeEyeTrackerQtShared(QPoint * p, QPoint * mp){
	this->eyePos = p;
	this->MousePos = mp;
}

void $MW run(QApplication * a){
	QTextCursor c = QTextCursor(this->ui->lessonTextBox->document());
	
	std::clock_t start = std::clock(), timeLimit = CLOCKS_PER_SEC * 10;
	
	QString selected = "", newtext;
	
	int hit = 0;


	while (this->isVisible()){
		a->processEvents();

		//c.setPosition(ui->lessonTextBox->document()->documentLayout()->hitTest(*this->eyePos, Qt::FuzzyHit)); Qt::ExactHit
		hit = ui->lessonTextBox->document()->documentLayout()->hitTest(this->mapFromGlobal(*this->eyePos), Qt::FuzzyHit);
		if (hit==-1){
			continue;
		}

		c.setPosition(hit);
		c.select(QTextCursor::WordUnderCursor);
		if (!c.selectedText().isEmpty()){
			newtext = c.selectedText();
			if (QString::compare(selected, newtext, Qt::CaseSensitive)){
				if (std::clock() - start > timeLimit){
					ui->defnBox->setText("DEFINITION GOES HERE");
				}
				else{
					ui->defnBox->setText("DOTH THOU NEEDTH ASSISTANCE?");
				}
			}
			else{
				selected = newtext;
				ui->defnBox->setText(c.selectedText());
				start = std::clock();
			}
		}
		else{
			selected = "";
			newtext = " ";
			ui->defnBox->setText("NOTHING");
			start = std::clock();
		}
		
	}
}

// Finds the highlighted string in the dictionary and displays the definition
void $MW on_viewDefButton_clicked(){
    ui-> wordBox-> setText( ui-> lessonTextBox-> textCursor().selectedText() );
    // TODO: extract definition:
    ui-> defnBox-> setText( "Definition should show up" );
}


// Save the definition into the DB
void $MW on_saveDefButton_clicked(){
    // TODO: save definition
}


void $MW resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent( event ); // Call super
    collectCoordinates();              // Recollect with new x/y values
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
