#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	bool fullscreen = false;

	instance = new VlcInstance(VlcCommon::args(), this);
	player = new VlcMediaPlayer(instance);

	videoControl = new VlcControlVideo(player, NULL, this);
	audioControl = new VlcControlAudio(player, NULL, this);

	vp = new wolfsuite::VideoParser("C:/Users/Alen/Videos/WSVideos");

	mainMenu = new QMenu(this);
	videoMenu = new QMenu("Video Track", this);
	audioMenu = new QMenu("Audio Track", this);
	subtitlesMenu = new QMenu("Subtitles", this);

	videoGroup = new QActionGroup(videoMenu);
	audioGroup = new QActionGroup(audioMenu);
	subtitlesGroup = new QActionGroup(subtitlesMenu);

	init();
}

MainWindow::~MainWindow() {
	delete player;
	delete videoControl;
	delete audioControl;
	delete media;
	delete instance;
	delete vp;
	delete videoGroup;
	delete audioGroup;
	delete videoMenu;
	delete audioMenu;
	delete subtitlesMenu;
	delete mainMenu;
}

void MainWindow::init() {
	player->setVideoWidget(ui.video);
	ui.video->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(ui.video, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showVideoMenu(const QPoint&)));
	connect(videoControl, SIGNAL(actions(QList<QAction *>, const Vlc::ActionsType)), this, SLOT(updateMenus(QList<QAction *>, const Vlc::ActionsType)));
	connect(audioControl, SIGNAL(actions(QList<QAction *>, const Vlc::ActionsType)), this, SLOT(updateMenus(QList<QAction *>, const Vlc::ActionsType)));
	connect(ui.videoList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(videoDoubleClicked(QListWidgetItem*)));

	ui.video->setMediaPlayer(player);
	ui.volume->setMediaPlayer(player);
	ui.volume->setVolume(50);
	ui.seek->setMediaPlayer(player);

	mainMenu->addMenu(videoMenu);
	mainMenu->addMenu(audioMenu);
	mainMenu->addMenu(subtitlesMenu);
	
	ui.playButton->setEnabled(false);
	ui.pauseButton->setEnabled(false);
	ui.stopButton->setEnabled(false);

	updateVideoList();
}

void MainWindow::videoDoubleClicked(QListWidgetItem* item) {
	ui.stackedWidget->setCurrentIndex(1);
	QString file = item->statusTip();

	if (file.isEmpty())
		return;

	media = new VlcMedia(file, true, instance);

	player->open(media);
	player->stop();

	ui.playButton->setEnabled(true);
}

void MainWindow::on_playButton_clicked() {
	ui.playButton->setEnabled(false);
	ui.pauseButton->setEnabled(true);
	ui.stopButton->setEnabled(true);

	player->play();
}

void MainWindow::on_pauseButton_clicked() {
	ui.playButton->setEnabled(true);
	ui.pauseButton->setEnabled(false);
	ui.stopButton->setEnabled(true);

	player->pause();
}

void MainWindow::on_stopButton_clicked() {
	ui.playButton->setEnabled(true);
	ui.pauseButton->setEnabled(false);
	ui.stopButton->setEnabled(false);

	player->stop();
}

void MainWindow::on_backButton_clicked() {
	player->stop();

	ui.stackedWidget->setCurrentIndex(0);
}

void MainWindow::showVideoMenu(const QPoint& pos) {
	QPoint globalPos = ui.video->mapToGlobal(pos);
	mainMenu->exec(globalPos);
}

void MainWindow::updateMenus(QList<QAction *> list, const Vlc::ActionsType type) {
	QList<QAction *>::iterator i;
	for (i = list.begin(); i != list.end(); ++i) {
		if (type == Vlc::ActionsType::VideoTrack) {
			QAction *act = *i;
			if (act->isEnabled())
				act->setEnabled(true);
			else
				act->setEnabled(false);
			videoGroup->addAction(act);
			videoMenu->addAction(act);
		} else if (type == Vlc::ActionsType::AudioTrack) {
			QAction *act = *i;
			if (act->isEnabled())
				act->setEnabled(true);
			else
				act->setEnabled(false);
			audioGroup->addAction(act);
			audioMenu->addAction(act);
		} else if (type == Vlc::ActionsType::Subtitles) {
			QAction *act = *i;
			if (act->isEnabled())
				act->setEnabled(true);
			else
				act->setEnabled(false);
			subtitlesGroup->addAction(act);
			subtitlesMenu->addAction(act);
		}
	}
}

// TODO - implement full screen
void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (ui.stackedWidget->currentIndex() == 1) {
		switch (event->key()) {
		case Qt::Key_F12:
			if (!fullscreen)
				setFullscreen(true);
			else
				setFullscreen(false);
		}
	}
}

void MainWindow::updateVideoList() {
	vp->scanFolder();
	QList<QListWidgetItem*>::iterator it;
	for (it = vp->videolist.begin(); it != vp->videolist.end(); ++it)
		ui.videoList->addItem(*it);
}

// TODO - implement full screen
void MainWindow::setFullscreen(bool f) {
	if (f) {

	} else {

	}
}