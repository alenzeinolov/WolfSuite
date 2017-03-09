#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QTime>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
private slots:
	QString getFormattedTime(int s);
	void on_pushButton_clicked();
	void on_playButton_clicked();
	void on_pauseButton_clicked();
	void on_stopButton_clicked();
	void on_videotimeSlider_sliderPressed();
	void on_videotimeSlider_sliderReleased();
	void on_videotimeSlider_sliderMoved(int position);

	void updatePlayerUI(QImage image);
private:
	Ui::MainWindowClass ui;
};

#endif
