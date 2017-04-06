#include "mainwindow.h"

#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>

#include <VLCQtCore/Common.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Q_INIT_RESOURCE(mainwindow);
	VlcCommon::setPluginPath(a.applicationDirPath() + "/plugins");

	MainWindow w;
	w.setStyleSheet("QMainWindow {background: 'white';}");
	w.show();

	return a.exec();
}
