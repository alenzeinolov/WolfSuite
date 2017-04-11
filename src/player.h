/**
 * @file
 * Copyright (C) 2017 by Alen Zeinolov
 * 
 * Player provides basic struct like structure to combine
 * playback related components into one file for easy interaction
 * with video player and its controls.
 *
 * @author Alen Zeinolov
 * @version 0.1
 * @date 2017
 */

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
		/**
		 * Creates a new instance of Player class.
		 * It assigns media to the video file provided so the player is ready for playback
		 * of that video file.
		 * @param path to the video file that this player will play.
		 */
		Player(QString path);
		~Player();
	public:
		/*
		 * VlcInstance - instance of a VLC instance, required to be able for any VLC object to function properly.
		 * VlcMedia - instance of VLC media, required for VlcMediaPlayer to specify which media file to play.
		 * VlcMediaPlayer - instance of VLC media player, a player that plays the media that is provided from VlcMedia instance.
		 */
		VlcInstance *instance;
		VlcMedia *media;
		VlcMediaPlayer *player;

		/*
		 * VlcControlVideo - provides function calls to control video playback: select video streams, select subtitles etc.
		 * VlcControlAudio - provides function calls to control audio playback: select audio track etc.
		 */
		VlcControlVideo *videoControl;
		VlcControlAudio *audioControl;
	};

}

#endif