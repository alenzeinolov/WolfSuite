#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	instance = new VlcInstance(VlcCommon::args(), this);
	player = new VlcMediaPlayer(instance);
	player->setVideoWidget(ui.video);

	videoControl = new VlcControlVideo(player, NULL, this);
	audioControl = new VlcControlAudio(player, NULL, this);

	vp = new wolfsuite::VideoParser("C:/Users/Alen/Videos/WSVideos");

	updateVideoList();

	bool fullscreen = false;

	ui.video->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.video, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showVideoMenu(const QPoint&)));

	mainMenu = new QMenu(this);
	videoMenu = new QMenu("Video Track", this);
	audioMenu = new QMenu("Audio Track", this);
	subtitlesMenu = new QMenu("Subtitles", this);

	videoGroup = new QActionGroup(videoMenu);
	audioGroup = new QActionGroup(audioMenu);
	subtitlesGroup = new QActionGroup(subtitlesMenu);

	mainMenu->addMenu(videoMenu);
	mainMenu->addMenu(audioMenu);
	mainMenu->addMenu(subtitlesMenu);

	connect(videoControl, SIGNAL(actions(QList<QAction *>, const Vlc::ActionsType)), this, SLOT(updateMenus(QList<QAction *>, const Vlc::ActionsType)));
	connect(audioControl, SIGNAL(actions(QList<QAction *>, const Vlc::ActionsType)), this, SLOT(updateMenus(QList<QAction *>, const Vlc::ActionsType)));

	connect(ui.videoList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_pushButton_clicked(QListWidgetItem*)));

	ui.video->setMediaPlayer(player);
	ui.volume->setMediaPlayer(player);
	ui.volume->setVolume(50);
	ui.seek->setMediaPlayer(player);

	ui.playButton->setEnabled(false);
	ui.pauseButton->setEnabled(false);
	ui.stopButton->setEnabled(false);
}

MainWindow::~MainWindow() {
	delete player;
	delete videoControl;
	delete audioControl;
	delete media;
	delete instance;
}

void MainWindow::init() {

}

void MainWindow::on_pushButton_clicked(QListWidgetItem* item) {
	ui.stackedWidget->setCurrentIndex(1);
	//QString file = QFileDialog::getOpenFileName(this, tr("Open file"),QDir::homePath(), tr("Multimedia files(*)"));
	QString file = item->text();

	if (file.isEmpty())
		return;

	media = new VlcMedia(file, true, instance);

	audioControl->setDefaultAudioLanguage("eng");
	audioControl->reset();

	QMap<QString, int>::Iterator iterator;

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
	QList<QString>::iterator it;
	for (it = vp->videolist.begin(); it != vp->videolist.end(); ++it)
		ui.videoList->addItem(*it);
}

void MainWindow::setFullscreen(bool f) {
	if (f) {

	} else {

	}
}