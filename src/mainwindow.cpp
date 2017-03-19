#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	bool fullscreen = false;

	vp = new wolfsuite::VideoParser(LIBRARY_FOLDER);

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
	//delete videoControl;
	//delete audioControl;
	//delete media;
	//delete instance;
	delete vp;
	delete videoGroup;
	delete audioGroup;
	delete videoMenu;
	delete audioMenu;
	delete subtitlesMenu;
	delete mainMenu;
}

void MainWindow::init() {
	connect(ui.video, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showVideoMenu(const QPoint&)));
	connect(ui.videoList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(videoDoubleClicked(QListWidgetItem*)));

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

	player = new wolfsuite::Player(file);

	player->player->setVideoWidget(ui.video);
	ui.video->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(player->videoControl, SIGNAL(actions(QList<QAction *>, const Vlc::ActionsType)), this, SLOT(updateMenus(QList<QAction *>, const Vlc::ActionsType)));
	connect(player->audioControl, SIGNAL(actions(QList<QAction *>, const Vlc::ActionsType)), this, SLOT(updateMenus(QList<QAction *>, const Vlc::ActionsType)));

	ui.video->setMediaPlayer(player->player);
	ui.volume->setMediaPlayer(player->player);
	ui.seek->setMediaPlayer(player->player);
	ui.volume->setVolume(50);

	ui.playButton->setEnabled(true);
}

void MainWindow::on_playButton_clicked() {
	ui.playButton->setEnabled(false);
	ui.pauseButton->setEnabled(true);
	ui.stopButton->setEnabled(true);

	player->player->play();
}

void MainWindow::on_pauseButton_clicked() {
	ui.playButton->setEnabled(true);
	ui.pauseButton->setEnabled(false);
	ui.stopButton->setEnabled(true);

	player->player->pause();
}

void MainWindow::on_stopButton_clicked() {
	ui.playButton->setEnabled(true);
	ui.pauseButton->setEnabled(false);
	ui.stopButton->setEnabled(false);

	player->player->stop();
}

void MainWindow::on_backButton_clicked() {

	player->player->stop();

	videoMenu->clear();
	audioMenu->clear();
	subtitlesMenu->clear();

	// POTENTIALLY DANGEROUS
	player = NULL;

	ui.stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_refreshButton_clicked() {
	updateVideoList();
}

void MainWindow::on_addButton_clicked() {
	// TODO: IMPROVE ADDBUTTON VERY DODGY
	QStringList filename = QFileDialog::getOpenFileNames(this, tr("Add videos to library"), "", tr("Video files (*.mkv *.mp4 *.avi)"));

	if (filename.count() == 0)
		qDebug("WHAT");

	wolfsuite::CopyFile* cf = new wolfsuite::CopyFile(filename, QString::fromStdString(LIBRARY_FOLDER) + "/");
	QProgressDialog* progress = new QProgressDialog("Abort copy", "Abort Copy", 0, cf->copyList.count(), this);
	connect(cf, &wolfsuite::CopyFile::finished, progress, &QObject::deleteLater);
	connect(cf, &wolfsuite::CopyFile::finished, this, &MainWindow::updateVideoList);
	connect(cf, &wolfsuite::CopyFile::finished, cf, &QObject::deleteLater);
	connect(cf, &wolfsuite::CopyFile::signalCopyFile, progress, &QProgressDialog::setValue);
	cf->start();
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
	bool toAdd = true;
	QList<QListWidgetItem*>::iterator it;
	if (ui.videoList->count() == 0) {
		for (it = vp->videolist.begin(); it != vp->videolist.end(); ++it)
			ui.videoList->addItem(*it);
	} else {
		for (it = vp->videolist.begin(); it != vp->videolist.end(); ++it) {
			for (int i = 0; i < ui.videoList->count(); i++)
				if (ui.videoList->item(i)->data(Qt::StatusTipRole).compare((*it)->data(Qt::StatusTipRole)) == 0)
					toAdd = false;
			if (toAdd)
				ui.videoList->addItem(*it);
			toAdd = true;
		}
	}
}

// TODO - implement full screen
void MainWindow::setFullscreen(bool f) {
	if (f) {

	} else {

	}
}