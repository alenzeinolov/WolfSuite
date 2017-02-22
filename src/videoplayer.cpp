#include "videoplayer.h"

namespace wolfsuite {

	VideoPlayer::VideoPlayer() {
		av_register_all();
		formatContext = NULL;
		codecContext = NULL;
		codec = NULL;
		frame = NULL;
		frameRGB = NULL;
		swsContext = NULL;
		buffer = NULL;
	}

	VideoPlayer::~VideoPlayer() {
		av_free(buffer);
		av_free(frameRGB);
		av_free(frame);

		avcodec_close(codecContext);

		avformat_close_input(&formatContext);
	}

	bool VideoPlayer::openFile(std::string filename) {
		if (avformat_open_input(&formatContext, filename.c_str(), NULL, NULL))
			return false;
		if (avformat_find_stream_info(formatContext, NULL) < 0)
			return false;
		
		videoStream = -1;
		audioStream = -1;
		for (int i = 0; i < formatContext->nb_streams; i++) {
			if (formatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && videoStream < 0)
				videoStream = i;
			if (formatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && audioStream < 0)
				audioStream = i;
		}
		if (videoStream == -1)
			return false;
		if (audioStream == -1)
			return false;

		codecContext = formatContext->streams[videoStream]->codec;
		audioCodecContext = formatContext->streams[audioStream]->codec;

		codec = avcodec_find_decoder(codecContext->codec_id);
		if (codec == NULL)
			return false;
		// codecContext = avcodec_alloc_context3(codec);

		audioCodec = avcodec_find_decoder(audioCodecContext->codec_id);
		if (audioCodec == NULL)
			return false;

		if (avcodec_open2(codecContext, codec, NULL) < 0)
			return false;

		frame = av_frame_alloc();
		frameRGB = av_frame_alloc();
		if (frameRGB == NULL)
			return false;
		numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, codecContext->width, codecContext->height);
		buffer = (uint8_t*) av_malloc(numBytes * sizeof(uint8_t));
		avpicture_fill((AVPicture*) frameRGB, buffer, AV_PIX_FMT_RGB24, codecContext->width, codecContext->height);
		start(LowPriority);
		return true;
	}

	void VideoPlayer::readData() {
		qint64 written = 0;
		swsContext = sws_getContext(codecContext->width, codecContext->height, codecContext->pix_fmt, codecContext->width, codecContext->height, AV_PIX_FMT_RGB24, SWS_BILINEAR, NULL, NULL, NULL);
		while (av_read_frame(formatContext, &packet) >= 0) {
			if (packet.stream_index == videoStream) {
				avcodec_decode_video2(codecContext, frame, &frameFinished, &packet);
				if (frameFinished) {
					sws_scale(swsContext, (uint8_t const* const*) frame->data, frame->linesize, 0, codecContext->height, frameRGB->data, frameRGB->linesize);
					QImage image = QImage(codecContext->width, codecContext->height, QImage::Format_RGB888);
					for (int y = 0; y < codecContext->height; ++y)
						memcpy(image.scanLine(y), frameRGB->data[0] + y * frameRGB->linesize[0], frameRGB->linesize[0]);
					emit processedImage(image);
				}
			}
			av_free_packet(&packet);
		}
	}

	void VideoPlayer::run() {
		readData();
	}
}