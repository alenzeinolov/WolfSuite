#include "thumbnailcreator.h"

namespace wolfsuite {

	ThumbnailCreator::ThumbnailCreator() {
		av_register_all();

		formatContext = NULL;
		codecContext = NULL;
		codec = NULL;
		frame = NULL;
		frameRGB = NULL;
		buffer = NULL;
		swsContext = NULL;
	}

	ThumbnailCreator::~ThumbnailCreator() {

	}

	bool ThumbnailCreator::generateThumbnail(std::string filename) {
		if (avformat_open_input(&formatContext, filename.c_str(), NULL, NULL))
			return false;
		if (avformat_find_stream_info(formatContext, NULL) < 0)
			return false;

		int videoStream = -1;
		for (int i = 0; i < formatContext->nb_streams; ++i) {
			if (formatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
				videoStream = i;
				break;
			}
		}
		if (videoStream == -1)
			return false;

		codecContext = formatContext->streams[videoStream]->codec;

		codec = avcodec_find_decoder(codecContext->codec_id);
		if (codec == NULL)
			return false;
		
		if (avcodec_open2(codecContext, codec, NULL))
			return false;

		frame = av_frame_alloc();
		frameRGB = av_frame_alloc();

		numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, codecContext->width, codecContext->height);
		buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

		avpicture_fill((AVPicture*)frameRGB, buffer, AV_PIX_FMT_RGB24, codecContext->width, codecContext->height);
		QImage image(codecContext->width, codecContext->height, QImage::Format_RGB888);

		swsContext = sws_getContext(codecContext->width, codecContext->height, codecContext->pix_fmt, codecContext->width, codecContext->height, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

		int64_t duration = (formatContext->duration / AV_TIME_BASE) * 0.25;
		int seekTime = (duration * (formatContext->streams[videoStream]->time_base.den)) / (formatContext->streams[videoStream]->time_base.num);
		int64_t timeBase = (int64_t(codecContext->time_base.num) * AV_TIME_BASE) / int64_t(codecContext->time_base.den);
		if (av_seek_frame(formatContext, videoStream, seekTime, AVSEEK_FLAG_ANY) < 0)
			return false;

		int frameFinished;
		AVPacket packet;
		while(av_read_frame(formatContext, &packet) >= 0) {
			if (packet.stream_index == videoStream) {
				avcodec_decode_video2(codecContext, frame, &frameFinished, &packet);
				if (frameFinished) {
					sws_scale(swsContext, frame->data, frame->linesize, 0, codecContext->height, frameRGB->data, frameRGB->linesize);
					for (int y = 0; y < codecContext->height; ++y)
						memcpy(image.scanLine(y), frameRGB->data[0] + y * frameRGB->linesize[0], frameRGB->linesize[0]);

					Config config;
					config.loadConfig();

					std::string libraryfolder = config.config.find("libraryfolder")->second;
					std::string thumbnailfolder = config.config.find("libraryfolder")->second + "/thumbnails/";
					if (!fs::exists(thumbnailfolder))
						fs::create_directory(thumbnailfolder);
					image.save(QString::fromStdString(thumbnailfolder) + QString::fromStdString(filename.erase(0, libraryfolder.length())) + ".jpeg");
					break;
				}
			}
		}
		av_free_packet(&packet);
		av_free(buffer);
		av_free(frameRGB);
		av_free(frame);
		avcodec_close(codecContext);
		avformat_close_input(&formatContext);
		return true;
	}
}