#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	player = new wolfsuite::VideoPlayer();
	QObject::connect(player, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerUI(QImage)));
	ui.setupUi(this);

	ui.playButton->setEnabled(false);
	ui.pauseButton->setEnabled(false);
	ui.stopButton->setEnabled(false);
	ui.videotimeSlider->setEnabled(false);
	ui.currentTime->setText("00:00:00");
	ui.maxTime->setText("00:00:00");

	this->statusBar()->showMessage("Loading");
}

MainWindow::~MainWindow()
{
	delete player;
}

void MainWindow::on_pushButton_clicked()
{
	ui.stackedWidget->setCurrentIndex(1);
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files (*.mkv *.avi *.mpg *.mp4)"));
	QFileInfo info = filename;
	if (!filename.isEmpty()) {
		if (!player->openFile(filename.toLatin1().data())) {
			QMessageBox msgBox;
			msgBox.setText("The selected video could not be opened!");
			msgBox.exec();
		} else {
			this->setWindowTitle(QString(info.fileName()).append(" - WolfSuite"));

			/*ui.playButton->setEnabled(true);
			ui.pauseButton->setEnabled(false);
			ui.stopButton->setEnabled(false);
			ui.videotimeSlider->setEnabled(true);
			ui.videotimeSlider->setMaximum(player->getNumFrames());
			ui.maxTime->setText(getFormattedTime(player->getNumFrames() / player->getFrameRate()));*/

			this->statusBar()->showMessage("Ready");
		}
	}
}

void MainWindow::on_playButton_clicked() {
	/*if (player->isPaused()) {
		player->play();
		ui.playButton->setEnabled(false);
		ui.pauseButton->setEnabled(true);
		ui.stopButton->setEnabled(true);

		this->statusBar()->showMessage("Playing");
	}*/
}

void MainWindow::on_pauseButton_clicked() {
	/*if (!player->isPaused()) {
		player->pause();
		ui.playButton->setEnabled(true);
		ui.pauseButton->setEnabled(false);
		ui.stopButton->setEnabled(true);

		this->statusBar()->showMessage("Paused");
	}*/
}

void MainWindow::on_stopButton_clicked() {
	/*player->stop();
	ui.playButton->setEnabled(true);
	ui.pauseButton->setEnabled(false);
	ui.stopButton->setEnabled(false);
	ui.currentTime->setText(getFormattedTime(0 / player->getFrameRate()));
	ui.videotimeSlider->setValue(player->getCurrentFrame());

	this->statusBar()->showMessage("Stopped");*/
}

void MainWindow::on_videotimeSlider_sliderPressed() {
	/*player->pause();*/
}

void MainWindow::on_videotimeSlider_sliderReleased() {
	/*player->play();*/
}

void MainWindow::on_videotimeSlider_sliderMoved(int position) {
	/*player->setCurrentFrame(position);
	ui.currentTime->setText(getFormattedTime(position / player->getFrameRate()));*/
}

QString MainWindow::getFormattedTime(int s) {
	int seconds = s % 60;
	int minutes = ((s / 60) % 60);
	int hours = (s / (60 * 60)) % 24;

	QTime time(hours, minutes, seconds);
	return time.toString("hh:mm:ss");
}

void MainWindow::updatePlayerUI(QImage image)
{
	if (!image.isNull()) {
		ui.videoArea->setAlignment(Qt::AlignCenter);
		ui.videoArea->setPixmap(QPixmap::fromImage(image).scaled(ui.videoArea->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
		//ui.videotimeSlider->setValue(player->getCurrentFrame());
		//ui.currentTime->setText(getFormattedTime(player->getCurrentFrame() / player->getFrameRate()));
	} else {
		on_stopButton_clicked();
	}
}