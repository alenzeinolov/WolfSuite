#ifndef PLAYER_H
#define PLAYER_H

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

#include <VLCQtWidgets/ControlVideo.h>
#include <VLCQtWidgets/ControlAudio.h>

namespace wolfsuite {

	class Player : public QObject {
	public:
		Player(QString path);
		~Player();
	public:
		VlcInstance *instance;
		VlcMedia *media;
		VlcMediaPlayer *player;

		VlcControlVideo *videoControl;
		VlcControlAudio *audioControl;
	};

}

#endif