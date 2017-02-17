#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	player = new Player();
	QObject::connect(player, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerUI(QImage)));
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
}

void MainWindow::on_pushButton_2_clicked()
{
	if (player->IsStopped())
	{
		player->Play();
		ui.pushButton_2->setText(tr("Stop"));
	}
	else
	{
		player->Stop();
		ui.pushButton_2->setText(tr("Play"));
	}
}

void MainWindow::updatePlayerUI(QImage image)
{
	ui.label->setAlignment(Qt::AlignCenter);
	ui.label->setPixmap(QPixmap::fromImage(image).scaled(ui.label->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
}