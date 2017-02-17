#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	player = new wolfsuite::Player();
	QObject::connect(player, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerUI(QImage)));
	QObject::connect(player, SIGNAL(currentPosition(QImage)), this, SLOT(updateSlider(QImage)));
	ui.setupUi(this);
}

MainWindow::~MainWindow()
{
	delete player;
}

void MainWindow::on_pushButton_clicked()
{
	ui.stackedWidget->setCurrentIndex(1);
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files (*.avi *.mpg *.mp4)"));
	if (!filename.isEmpty())
		if (!player->LoadVideo(filename.toLatin1().data()))
		{
			QMessageBox msgBox;
			msgBox.setText("The selected video could not be opened!");
			msgBox.exec();
		}
	ui.playButton->setEnabled(true);
	ui.pauseButton->setEnabled(false);
	ui.videotimeSlider->setMaximum(1000 / player->getNumFrames());
}

void MainWindow::on_playButton_clicked() {
	if (player->IsStopped()) {
		player->Play();
		ui.playButton->setEnabled(false);
		ui.pauseButton->setEnabled(true);
	}
}

void MainWindow::on_pauseButton_clicked() {
	if (!player->IsStopped()) {
		player->Stop();
		ui.playButton->setEnabled(true);
		ui.pauseButton->setEnabled(false);
	}
}

void MainWindow::updatePlayerUI(QImage image)
{
	ui.videoArea->setAlignment(Qt::AlignCenter);
	ui.videoArea->setPixmap(QPixmap::fromImage(image).scaled(ui.videoArea->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
}

void MainWindow::updateSlider(int currentFrame) {
	ui.videotimeSlider->setSliderPosition(currentFrame);
}