#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QStatusBar>
#include <QTime>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include <VLCQtWidgets/ControlVideo.h>
#include <VLCQtWidgets/ControlAudio.h>

#include <videoparser.h>

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
protected:
	void keyPressEvent(QKeyEvent *event);
signals:
	void getActions();
private slots:
	void on_pushButton_clicked(QListWidgetItem* item);
	void on_playButton_clicked();
	void on_pauseButton_clicked();
	void on_stopButton_clicked();
	void on_backButton_clicked();
	
	void showVideoMenu(const QPoint& pos);
	void updateMenus(QList<QAction *> actions, const Vlc::ActionsType type);
private:
	Ui::MainWindowClass ui;

	bool fullscreen;

	QMenu *mainMenu, *videoMenu, *audioMenu, *subtitlesMenu;
	QActionGroup *audioGroup, *subtitlesGroup,*videoGroup;

	VlcInstance *instance;
	VlcMedia *media;
	VlcMediaPlayer *player;

	VlcControlVideo *videoControl;
	VlcControlAudio *audioControl;

	wolfsuite::VideoParser *vp;
private:
	void init();
	void updateVideoList();
	void setFullscreen(bool f);
};

#endif
