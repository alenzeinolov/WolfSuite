#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_mainwindow.h"

#include "player.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void updatePlayerUI(QImage image);
private:
	Ui::MainWindowClass ui;
	Player* player;
};

#endif
