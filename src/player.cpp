#include "player.h"

Player::Player(QObject *parent) : QThread(parent)
{
	stop = true;
}

Player::~Player()
{
	mutex.lock();
	stop = true;
	capture.release();
	condition.wakeOne();
	mutex.unlock();
	wait();
}

bool Player::LoadVideo(std::string filename) {
	capture.open(filename);
	if (capture.isOpened())
	{
		frameRate = (int)capture.get(CV_CAP_PROP_FPS);
		return true;
	}
	else
		return false;
}

void Player::Play()
{
	if (!isRunning()) {
		if (IsStopped()) {
			stop = false;
		}
		start(LowPriority);
	}
}

void Player::Stop()
{
	stop = true;
}

void Player::msleep(int ms)
{
	// struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
	// nanosleep(&ts, NULL);
}

bool Player::IsStopped() const
{
	return this->stop;
}

void Player::run()
{
	int delay = (1000 / frameRate);
	while (!stop) {
		if (!capture.read(frame))
		{
			stop = true;
		}
		if (frame.channels() == 3) {
			cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
			image = QImage((const unsigned char*)(RGBframe.data),
				RGBframe.cols, RGBframe.rows, QImage::Format_RGB888);
		}
		else
		{
			image = QImage((const unsigned char*)(frame.data),
				frame.cols, frame.rows, QImage::Format_Indexed8);
		}
		emit processedImage(image);
		std::this_thread::sleep_for(std::chrono::milliseconds(3));
	}
}

