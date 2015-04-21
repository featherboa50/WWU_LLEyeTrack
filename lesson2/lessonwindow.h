#ifndef LESSONWINDOW_H
#define LESSONWINDOW_H

#include <QMainWindow>

namespace Ui {
class lessonWindow;
}

class lessonWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit lessonWindow(QWidget *parent = 0);
    ~lessonWindow();

private slots:
    void on_actionOpen_File_triggered();

    void on_actionSave_File_triggered();

private:
    Ui::lessonWindow *ui;
};

#endif // LESSONWINDOW_H
