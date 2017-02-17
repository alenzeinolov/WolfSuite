#ifndef PLAYER_H
#define PLAYER_H

#include <chrono>
#include <thread>

#include <QImage>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

class Player : public QThread\
{
	Q_OBJECT
private:
	bool stop;
	QMutex mutex;
	QWaitCondition condition;
	cv::Mat frame;
	int frameRate;
	cv::VideoCapture capture;
	cv::Mat RGBframe;
	QImage image;
signals:
	void processedImage(const QImage &image);
protected:
	void run();
	void msleep(int ms);
public:
	Player(QObject *parent = 0);
	~Player();
	bool LoadVideo(std::string filename);
	void Play();
	void Stop();
	bool IsStopped() const;
};

#endif