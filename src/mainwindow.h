/**
 * @file
 * Copyright (C) 2017 by Alen Zeinolov
 * 
 * MainWindow class is a Qt MainWindow that handles the appearance
 * and functionality of the entire WolfSuite application. It handles
 * majority of logical operations that user can do in the program
 * and is a core element of the entire project.
 *
 * It is responsible for handling main window views, presenting lists
 * of playlists and videos, presenting UI for user to interact with,
 * displaying video player, handling video player functionality and
 * much more.
 *
 * @author Alen Zeinolov
 * @version 0.1
 * @date 2017
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QDesktopWidget>
#include <QComboBox>
#include <QFileDialog>
#include <QInputDialog>
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

#include "config.h"
#include "copyfile.h"
#include "editinfo.h"
#include "player.h"
#include "removefile.h"
#include "videoparser.h"
#include "videolistdelegate.h"

#include "ui_mainwindow.h"

/**
 * The name of the main playlist where all videos are presented, by default is "Your Library".
 */
#define ALL_VIDEOS "Your Library"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
public:
	/**
	 * An event filter that can be set to any QWidget.
	 * When set it provides functionality for handling events (mouse, keyboard etc.)
	 * called from those widgets. By default it handles all double click and mouse click
	 * events that can be invoked on various widgets in this application.
	 * @param object that the event was called from.
	 * @param event that has been called.
	 */
	bool eventFilter(QObject *watched, QEvent *event);
protected:
	/**
	 * Creates a new instance of EditInfo class.
	 * @param event that has been called.
	 * @return true of eventFilter found, false otherwise.
	 */
	void keyPressEvent(QKeyEvent *event);
private slots:
	/**
	 * Invoked when user double clicks an item on video list.
	 * It creates a new Player instance with the path to the file
	 * of the video item that has been selected. It sets up basic
	 * configurations and creates a context menu for video widget
	 * and loads track and subtitle information specific for the video into it.
	 * At the end it proceeds to video viewing screen. Video playback is
	 * started automatically.
	 * @param video item that has been selected.
	 */
	void videoDoubleClicked(QListWidgetItem* item);
	/**
	 * Invoked when user clicks on Play button, or presses Space key,
	 * or left clicks on video widget Enables/Disables buttons logically
	 * and starts playback of the video file.
	 */
	void on_playButton_clicked();
	/**
	 * Invoked when user clicks on Pause button, or presses Space key,
	 * or left clicks on video widget Enables/Disables buttons logically
	 * and pauses playback of the video file.
	 */
	void on_pauseButton_clicked();
	/**
	 * Invoked when user clicks on Stop button or when the playback has
	 * reached the end of video file. Enables/Disables buttons logically
	 * and stops playback of the video file (sets video time to 0).
	 */
	void on_stopButton_clicked();
	/**
	 * Invoked when user clicks on Decrease Speed button. 
	 * Decreases the speed of playback of the video file.
	 * Speed is decreased up to 0.25x.
	 */
	void on_decSpeedButton_clicked();
	/**
	 * Invoked when user clicks on Increase Speed button. 
	 * Increases the speed of playback of the video file.
	 * Speed is increased up to 4x.
	 */
	void on_incSpeedButton_clicked();
	/**
	 * Invoked when user clicks on Step button. 
	 * Jumps video time by 30 seconds.
	 */
	void on_stepButton_clicked();
	/**
	 * Invoked when user clicks on Volume Mute button. 
	 * Unmutes/Mutes all the audio of the video and enables/disable audio buttons.
	 * Is a toggle function.
	 */
	void on_volumeMuteButton_clicked();
	/**
	 * Invoked when user clicks on Volume Down button. 
	 * Decreases sound volume by 10 until it reached 0.
	 */
	void on_volumeDownButton_clicked();
	/**
	 * Invoked when user clicks on Volume Up button. 
	 * Increases sound volume by 10 until it reached 200.
	 */
	void on_volumeUpButton_clicked();
	/**
	 * Invoked when user clicks on Full Screen button. 
	 * Enables/Disables fullscreen mode.
	 * Is a toggle function.
	 */
	void on_fullscreenButton_clicked();
	/**
	 * Invoked when user clicks on Back button. 
	 * Decreases sound volume by 10 until it reached 0.
	 */
	void on_backButton_clicked();
	/**
	 * Invoked when user clicks on Refresh button or when
	 * a new video is added to the library.
	 */
	void on_refreshButton_clicked();
	/**
	 * Invoked when user clicks on Add File button.
	 * Invokes a file selection dialog for user to select files to add.
	 * After user selected videos creates a progress bar dialog
	 * presenting user with real time information on adding process.
	 * When adding files operation is finished invokes refresh method to
	 * update video list and sorting.
	 */
	void on_addButton_clicked();
	/**
	 * Invoked when user clicks on Delete File button on a selected video file.
	 * Invokes a dialog prompting user whether they want to delete a file.
	 * After user accepted creates a dialog
	 * presenting user with real time information on deleting process.
	 * Note: it dialog only appears when delete operation takes too long.
	 * When delete file operation is finished invokes refresh method to
	 * update video list and sorting.
	 */
	void on_deleteButton_clicked();
	/**
	 * Invoked when user clicks on Edit File button on a selected video file.
	 * Creates a new EditInfo widget and presents it to the user.
	 */
	void on_infoButton_clicked();
	/**
	 * Invoked when user clicks on Add Playlist button.
	 * Creates an input dialog and presents it to the user where they can
	 * enter the playlist name of the playlist to be added. Once entered,
	 * creates a new playlist and refreshes playlist list widget.
	 */
	void on_addPlaylistButton_clicked();
	/**
	 * Invoked when user clicks on Delete Playlist button on selected playlist.
	 * Creates a dialog and promts a user whether they want to delete selected playlist.
	 * Once accepted, creates a new playlist and refreshes playlist list widget.
	 */
	void on_deletePlaylistButton_clicked();
	/**
	 * Invoked when user interacts with sorting combo box or when playlist is changed.
	 * Sorts the videolist in ascending or descending order depending on the selection.
	 */
	void handleSorting();
	/**
	 * Invoked when user inputs data into the search field.
	 * Searches for videos that contain the string provided in its information
	 * and if so, includes the video in the videolist and updates it and presents to the user.
	 */
	void handleSearch(QString searchString);
	/**
	 * Invoked when user selects a playlist in the playlists list widget.
	 * Updates the videolist with the videos that are contained in the playlist
	 * according to the playlist selected.
	 */
	void playlistChanged(QListWidgetItem * item);
	/**
	 * Invoked when user selects an aspect ratio from context menu
	 * by right clicking on the video widget. Sets the aspect ratio selected.
	 */
	void changeAspectRatio();
	/**
	 * Invoked when user selects a crop ratio from context menu
	 * by right clicking on the video widget. Sets the crop ratio selected.
	 */
	void changeCropRatio();
	
	/**
	 * Invoked when user right clicks on the video widget.
	 * Shows menus with video, audio, aspect ratio, crop ratio and subtiles sub menus.
	 * @param point with x and y value where it was right clicked in order to create context menu
	 * at that position.
	 */
	void showVideoMenu(const QPoint& pos);
	/**
	 * Invoked when user selects video, audio or subtitle tracks.
	 * Updates the video, audio and subtitle tracks of the video being played
	 * according to the user selection.
	 * @param list of actions
	 * @param type of action invoked
	 */
	void updateMenus(QList<QAction *> actions, const Vlc::ActionsType type);
private:
	Ui::MainWindowClass ui;

	/*
	 * Hold informationm whether about current fullscreen state and
	 * whether the window is maximised or not in order to properly
	 * handle fullscreen toggle.
	 */
	bool fullscreen, maximized;

	/*
	 * A set of menus and corresponding action groups for 
	 * context menu that is presented in video widget.
	 */
	QMenu *mainMenu, *videoMenu, *audioMenu, *aspectRatioMenu, *cropRatioMenu, *subtitlesMenu;
	QActionGroup *videoGroup, *audioGroup, *aspectRatioGroup, *cropRatioGroup, *subtitlesGroup;
	QAction *defaultAR, *firstAR, *secondAR, *thirdAR;
	QAction *defaultCR, *firstCR, *secondCR, *thirdCR;

	/*
	 * Item that is created to present all videos (default) general item, cannot be deleted.
	 * name of the current item selected.
	 */
	QListWidgetItem *allItem;
	QString *currentItem;

	/*
	 * Config instance to parse config files.
	 * Player instance to play video files.
	 * VideoParser instance to parse videolist file and user folder.
	 */
	wolfsuite::Config *config;
	wolfsuite::Player *player;
	wolfsuite::VideoParser *vp;
private:
	/**
	 * Initialises the variables and settings to the default
	 * initial state that is requiredfor the application
	 * to function properly.
	 */
	void init();
	/**
	 * Sets up the configuration file.
	 * If configuration file not found it promomts user to createa new one by 
	 * providing the library folder selection at startup of the program.
	 * If configuration file exists it loads it instead.
	 */
	void setupConfig();
	/**
	 * Updates the videlist given the current selected playlist.
	 * Clears all video items and requests new updated list from VideoParser.
	 * If default playlist selected presents all videos regardless of their playlists.
	 * If specific playlist is selected updates videolist only with videos assigned to that playlist.
	 * When videolist is updated, it updates videolist sorting automatically as well.
	 */
	void updateVideoList();
	/**
	 * Updates playlists list when invoked.
	 * Clears all playlist items and requests new updated list from VideoParser.
	 * If the playlist previously selected was removed default (all) playlist is set.
	 */
	void updatePlaylistList();
	/**
	 * Toggles fullscreen mode.
	 * @param if true enters fullscreen mode, if false exits fullscreen mode.
	 */
	void setFullscreen(bool f);
};

#endif
