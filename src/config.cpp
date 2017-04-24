#include "config.h"

namespace wolfsuite {

	Config::Config() {}

	Config::~Config() {}

	void Config::createConfig(std::string libraryPath) {
		if (!fs::exists(CONFIG_FILE_NAME)) {
			//TODO: ADD MORE CONFIG ELEMENTS
			std::ofstream file(CONFIG_FILE_NAME, std::ios::app);
			file << "libraryfolder:" << libraryPath << std::endl;
		}
		loadConfig();
	}

	void Config::loadConfig() {
		std::ifstream file(CONFIG_FILE_NAME);

		std::string line;
		while (std::getline(file, line)) {
			int pos = line.find(':');
			config[line.substr(0, pos)] = line.substr(pos + 1);
		}
	}

	void Config::editConfig(std::string field, std::string value) {
		std::ifstream ifile(CONFIG_FILE_NAME);
		std::ofstream ofile(CONFIG_FILE_NAME + std::string("_TMP"), std::ios::app);

		std::string line;
		while (std::getline(ifile, line)) {
			int pos = line.find(':');
			if (line.substr(0, pos).compare(field) == 0)
				ofile << field << ":" << value << std::endl;
			else
				ofile << line << std::endl;
		}

		ifile.close();
		ofile.close();

		QFile::remove(QString::fromStdString(CONFIG_FILE_NAME));
		std::rename(std::string(CONFIG_FILE_NAME + std::string("_TMP")).c_str(), std::string(CONFIG_FILE_NAME).c_str());
		loadConfig();
	}

	bool Config::configExists() {
		return fs::exists(CONFIG_FILE_NAME);
	}

	void Config::loadPlaylist() {
		playlists.clear();
		std::ifstream file(PLAYLIST_FILE_NAME);
		std::string line;
		while (std::getline(file, line)) {
			QListWidgetItem* item = new QListWidgetItem();
			item->setData(Qt::DisplayRole, QString::fromStdString(line));
			item->setIcon(QPixmap(":/MainWindow/playlist.png"));
			playlists.append(item);
		}
	}

	void Config::addPlaylist(QString playlist) {
		if (playlist.length() != 0) {
			if (!playlistExists(playlist)) {
				std::ofstream file(PLAYLIST_FILE_NAME, std::ios::app);
				file << playlist.toStdString() << std::endl;
			}
		}
	}

	void Config::deletePlaylist(QString playlist) {
		std::ifstream ifile(PLAYLIST_FILE_NAME);
		std::ofstream ofile(PLAYLIST_FILE_NAME + std::string("_TMP"));

		std::string line;
		while (std::getline(ifile, line)) {
			if (line.compare(playlist.toStdString()))
				ofile << line << std::endl;
		}

		ifile.close();
		ofile.close();

		QFile::remove(QString::fromStdString(PLAYLIST_FILE_NAME));
		std::rename(std::string(PLAYLIST_FILE_NAME + std::string("_TMP")).c_str(), std::string(PLAYLIST_FILE_NAME).c_str());
		loadPlaylist();
	}

	bool Config::playlistExists(QString playlist) {
		std::ifstream file(PLAYLIST_FILE_NAME);
		std::string line;
		while (std::getline(file, line))
			if (line.compare(playlist.toStdString()) == 0)
				return true;
		return false;
	}

}
