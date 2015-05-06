#include "mainwindow.h"
#include "EyeTrackerFunctions.h"
#include <QApplication>


QPoint * EyePosition;
QPoint * MousePosition;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	EyePosition = new QPoint(0, 0);
	MousePosition = new QPoint(0, 0);

	Eye_Tracker_Start(EyePosition, MousePosition);

    w.show();

	w.run(&a);

	delete(MousePosition);
	delete(EyePosition);

	return 0;
}
