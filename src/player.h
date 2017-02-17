#ifndef PLAYER_H
#define PLAYER_H

#include <QImage>
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
		bool stop;
		int frameRate;
		int currentFrame;
		int numFrames;
		cv::Mat frame;
		cv::Mat RGBframe;
		cv::VideoCapture capture;
		QImage image;
	public:
		void run();
		bool LoadVideo(std::string filename);
		void Play();
		void Pause();
		void Stop();
		inline int getNumFrames() { return numFrames; }
		inline bool IsStopped() { return stop; }
	signals:
		void processedImage(const QImage &image);
		void currentPosition(const int currentPosition);
	};
}

#endif