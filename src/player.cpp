#include "player.h"

namespace wolfsuite {

	Player::Player(QObject *parent) {
		stop = true;
	}

	Player::~Player() {
		mutex.lock();
		stop = true;
		capture.release();
		condition.wakeOne();
		mutex.unlock();
		wait();
	}

	bool Player::LoadVideo(std::string filename) {
		capture.open(filename);
		capture.set(CV_CAP_PROP_BUFFERSIZE, 3);
		if (capture.isOpened()) {
			frameRate = (int) capture.get(CV_CAP_PROP_FPS);
			numFrames = (int) capture.get(CV_CAP_PROP_FRAME_COUNT);
			currentFrame = 0;
			return true;
		} else {
			return false;
		}
	}

	void Player::Play() {
		if (!isRunning()) {
			if (IsStopped()) {
				stop = false;
			}
			start(LowPriority);
		}
	}

	void Player::Stop() {
		stop = true;
	}

	void Player::run()
	{
		int delay = (1000 / frameRate);
		while (!stop) {
			currentFrame++;
			if (!capture.read(frame))
			{
				stop = true;
			}
			if (frame.channels() == 3) {
				cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
				image = QImage((const unsigned char*)(RGBframe.data), RGBframe.cols, RGBframe.rows, QImage::Format_RGB888);
			}
			else
			{
				image = QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_Indexed8);
			}
			emit processedImage(image);
			emit currentPosition(currentFrame);
			msleep(delay);
		}
	}
}