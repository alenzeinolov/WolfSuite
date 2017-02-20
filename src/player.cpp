#include "player.h"

namespace wolfsuite {

	Player::Player(QObject *parent) {
		paused = true;
	}

	Player::~Player() {
		paused = true;
		mutex.lock();
		capture->release();
		condition.wakeOne();
		mutex.unlock();
		wait();
		delete capture;
	}

	bool Player::loadVideo(std::string filename) {
		capture = new cv::VideoCapture(0 + cv::CAP_FFMPEG);
		capture->open(filename);
		capture->set(CV_CAP_PROP_BUFFERSIZE, 25);

		if (capture->isOpened()) {
			frameRate = (int) capture->get(CV_CAP_PROP_FPS);
			numFrames = (int) capture->get(CV_CAP_PROP_FRAME_COUNT);
			return true;
		} else {
			return false;
		}
	}

	void Player::play() {
		if (!isRunning()) {
			if (isPaused()) {
				paused = false;
			}
			start(LowPriority);
		}
	}

	void Player::pause() {
		paused = true;
	}

	void Player::stop() {
		setCurrentFrame(0);
		paused = true;
	}

	void Player::setCurrentFrame(int frame) {
		capture->set(CV_CAP_PROP_POS_FRAMES, frame);
	}

	void Player::run()
	{
		int delay = (1000 / frameRate);
		while (!paused) {
			if (!capture->read(frame))
				stop();
			if (frame.channels() == 3) {
				cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
				image = (QImage((const unsigned char*)(RGBframe.data), RGBframe.cols, RGBframe.rows, QImage::Format_RGB888));
			} else {
				image = (QImage((const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_Indexed8));
			}
			emit processedImage(image);
			msleep(delay);
		}
	}
}