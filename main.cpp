#include "ergocam.h"
#include <QtWidgets/QApplication>
#include "KinectHelper.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ErgoCam w;
	w.show();
	return a.exec();
}
