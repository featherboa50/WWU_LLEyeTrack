#include "lessonwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lessonWindow w;
    w.show();

    return a.exec();
}
