#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <iostream>

#include <QBUffer>
#include <QImage>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>

extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
}

#define MAX_AUDIO_FRAME_SIZE 192000

namespace wolfsuite {
	
	class VideoPlayer : public QThread {
		Q_OBJECT
	public:
		VideoPlayer();
		~VideoPlayer();
	private:
		QMutex mutex;
		QWaitCondition condition;
		AVFormatContext *formatContext;
		AVCodecContext *codecContext;
		AVCodecContext *audioCodecContext;
		AVCodec *codec;
		AVCodec *audioCodec;
		AVFrame *frame;
		AVFrame *frameRGB;
		AVPacket packet;
		AVPacket audioPacket;
		SwsContext *swsContext;
		int videoStream;
		int audioStream;
		int numBytes;
		int frameFinished;
		uint8_t *buffer;

	public:
		void run();
		bool openFile(std::string filename);
		void readData();
	signals:
		void processedImage(const QImage &image);
	};
}

#endif