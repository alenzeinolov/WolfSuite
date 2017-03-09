#include "mainwindow.h"

#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>

#include <VLCQtCore/Common.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VlcCommon::setPluginPath(a.applicationDirPath() + "/plugins");

	MainWindow w;
	w.show();

	return a.exec();
}
