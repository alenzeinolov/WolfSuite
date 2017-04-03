#ifndef THUMBNAILCREATOR_H
#define THUMBNAILCREATOR_H

#include <fstream>
#include <string>

#include <QFile>
#include <QImage>
#include <QPixmap>

extern "C" {
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
}

namespace wolfsuite {

	class ThumbnailCreator {
	public:
		ThumbnailCreator();
		~ThumbnailCreator();
		bool generateThumbnail(std::string filename);
	private:
		AVFormatContext* formatContext;
		AVCodecContext* codecContext;
		AVCodec* codec;
		AVFrame* frame;
		AVFrame* frameRGB;
		int numBytes;
		uint8_t* buffer;
		SwsContext* swsContext;
	};

}

#endif