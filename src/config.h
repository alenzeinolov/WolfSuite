/**
 * @file
 * Copyright (C) 2017 by Alen Zeinolov
 * 
 * Config class creates and manages configuration settings and playlist
 * information of the application.
 *
 * @author Alen Zeinolov
 * @version 0.1
 * @date 2017
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QList>
#include <QListWidgetItem>

#include <experimental/filesystem>
#include <fstream>
#include <map>
#include <string>

#define CONFIG_FILE_NAME "config"
#define PLAYLIST_FILE_NAME "playlist"

namespace fs = std::experimental::filesystem;

namespace wolfsuite {

	class Config {
	public:
		Config();
		~Config();
	public:
		/**
		 * Map (key, value) structure with key value being the configuration setting
		 * and value is the value of that configuration setting.
		 */
		std::map<std::string, std::string> config;
		/**
		 * List of playlist items that are parsed from the playlist text file.
		 */
		QList<QListWidgetItem*> playlists;
	public:
		/**
		 * Loads configuration from a text file stored in
		 * the folder of the final executable into a map.
		 */
		void loadConfig();
		/**
		 * Creates a new configuration file and inputs
		 * the folder path provided.
		 * @param path of the user library folder.
		 */
		void createConfig(std::string libraryPath);
		/**
		 * Edits the configurations stored in the configuration file.
		 * It finds the field provided and changes its value with value provided.
		 * @param configuration setting (field) to change.
		 * @param the value to change the field with.
		 */
		void editConfig(std::string field, std::string value);
		/**
		 * Returns whether the config file exists or not.
		 * @return true if config file exists, false otherwise.
		 */
		bool configExists();

		/**
		 * Loads playlists list from a text file stored in
		 * the folder of the final executable into a list.
		 */
		void loadPlaylist();
		/**
		 * Adds new playlist to the playlist text file.
		 * @param name of the new playlist.
		 */
		void addPlaylist(QString playlist);
		/**
		 * Deletes playlist from the playlist text file.
		 * @param name of the playlist to delete.
		 */
		void deletePlaylist(QString playlist);
		/**
		 * Returns whether playlist provided exists in the playlist text file.
		 * @param name of the playlist to check exsistence for.
		 * @return true of provided playlist exists, false otherwise.
		 */
		bool playlistExists(QString playlist);
	};

}

#endif