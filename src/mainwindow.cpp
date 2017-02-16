#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void MainWindow::on_pushButton_clicked()
{
	ui.stackedWidget->setCurrentIndex(1);
}