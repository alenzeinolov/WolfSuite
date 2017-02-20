#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <thread>
#include <vector>

#include <QImage>
#include <QTime>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

namespace wolfsuite {
	class Player : public QThread {
		Q_OBJECT
	public:
		Player(QObject *parent = 0);
		~Player();
	private:
		QMutex mutex;
		QWaitCondition condition;
		bool paused, toBuffer;
		int frameRate;
		int numFrames;
		cv::Mat frame;
		cv::Mat RGBframe;
		cv::VideoCapture* capture;
		QImage image;
	public:
		void run();
		bool loadVideo(std::string filename);
		void play();
		void pause();
		void stop();
		void setCurrentFrame(int frame);
		inline int getFrameRate() { return frameRate; }
		inline int getCurrentFrame() { return capture->get(CV_CAP_PROP_POS_FRAMES); }
		inline int getNumFrames() { return numFrames; }
		inline bool isPaused() { return paused; }
	signals:
		void processedImage(const QImage &image);
	};
}

#endif