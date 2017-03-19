#include "player.h"

namespace wolfsuite {

	Player::Player(QString path) {
		instance = new VlcInstance(VlcCommon::args(), this);
		player = new VlcMediaPlayer(instance);
		media = new VlcMedia(path, true, instance);

		videoControl = new VlcControlVideo(player, NULL, this);
		audioControl = new VlcControlAudio(player, NULL, this);

		player->open(media);
		player->stop();
	}

	Player::~Player() {
		delete player;
		delete videoControl;
		delete audioControl;
		delete media;
		delete instance;
	}

}