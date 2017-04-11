/**
 * @file
 * Copyright (C) 2017 by Alen Zeinolov
 * 
 * ThumbnailCreator is a class that is able to create thumbnails from
 * video files for videolist to be presented there.
 *
 * @author Alen Zeinolov
 * @version 0.1
 * @date 2017
 */

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

#include <config.h>

namespace wolfsuite {

	class ThumbnailCreator {
	public:
		ThumbnailCreator();
		~ThumbnailCreator();
		/*
		 * Generates a thumbnail at 25% of the videotime and saves it in the thumbnail folder of user video folder.
		 * @param file path of the video file to get the thumbnail from.
		 * @return true if thumbnail was generated succesfully, false otherwise.
		 */
		bool generateThumbnail(std::string filename);
	private:
		/*
		 * Components required to open the file using ffmpeg, seek the required frame and extract that frame and decode it into an image.
		 */
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