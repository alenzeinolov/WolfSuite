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
		std::map<std::string, std::string> config;
		QList<QListWidgetItem*> playlists;
	public:
		void loadConfig();
		void createConfig(std::string libraryPath);
		void editConfig(std::string field, std::string value);
		bool configExists();

		void loadPlaylist();
		void addPlaylist(QString playlist);
		void deletePlaylist(QString playlist);
		bool playlistExists(QString playlist);
	};

}

#endif