#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QVector>
#include <QPair>
#include <QString>
#include <QStringList>
#include <QFile>

typedef enum {STUDENT,EDITOR} GuiMode_t;

struct coordinate{
    int x;
    int y;
    int height;
    int width;
    coordinate( int X, int Y, int Height, int Width ){
        x      = X;
        y      = Y;
        height = Height;
        width  = Width;
    }
};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

  public:

    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

  private slots:

    void on_saveDefButton_clicked();

    void on_viewDefButton_clicked();

    void on_actionOpen_triggered();

    void resizeEvent( QResizeEvent* event );

    void collectCoordinates();

    void saveFirstImage();

    coordinate getCoordinatePair();
        // openCV call to gather coordinate data

    void on_actionSave_triggered();

    void on_modeSwitch_toggled(bool arg1);

    void readDictionary( QFile& dict );

    void on_minimize_triggered();

    void on_close_triggered();

private:

    Ui::MainWindow *ui;

    QMap< QString, QString > dictionary;

    QVector< QString > lessonText;

    QMap< QPair<int,int>, QString > coordinateMapping;

    GuiMode_t GuiMode;

    bool editorMode;


};

#endif // MAINWINDOW_H
