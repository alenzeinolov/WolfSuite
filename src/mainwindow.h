#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QDesktopWidget>
#include <QComboBox>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMenu>
#include <QMessageBox>
#include <QStatusBar>
#include <QTime>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include <VLCQtWidgets/ControlVideo.h>
#include <VLCQtWidgets/ControlAudio.h>

#include "copyfile.h"
#include "player.h"
#include "removefile.h"
#include "videoparser.h"
#include "utility.h"

#include "ui_mainwindow.h"

#define LIBRARY_FOLDER "C:/Users/Alen/Videos/WSVideos"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
public:
	bool eventFilter(QObject *watched, QEvent *event);
protected:
	void keyPressEvent(QKeyEvent *event);
	//void mousePressEvent(QMouseEvent * event);
	//void mouseDoubleClickEvent(QMouseEvent * event);
private slots:
	void videoDoubleClicked(QListWidgetItem* item);
	void on_playButton_clicked();
	void on_pauseButton_clicked();
	void on_stopButton_clicked();
	void on_volumeMuteButton_clicked();
	void on_volumeDownButton_clicked();
	void on_volumeUpButton_clicked();
	void on_fullscreenButton_clicked();
	void on_backButton_clicked();
	void on_refreshButton_clicked();
	void on_addButton_clicked();
	void on_deleteButton_clicked();
	void handleSorting(int index);
	
	void showVideoMenu(const QPoint& pos);
	void updateMenus(QList<QAction *> actions, const Vlc::ActionsType type);
private:
	Ui::MainWindowClass ui;

	bool fullscreen, maximized;

	QMenu *mainMenu, *videoMenu, *audioMenu, *subtitlesMenu;
	QActionGroup *audioGroup, *subtitlesGroup, *videoGroup;

	wolfsuite::Player *player;
	wolfsuite::VideoParser *vp;
private:
	void init();
	void updateVideoList();
	void setFullscreen(bool f);
};

#endif
