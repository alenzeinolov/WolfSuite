#include "videoparser.h"

#include <iostream>

namespace wolfsuite {

	VideoParser::VideoParser(std::string filename) {
		libraryfolder = filename;

		// TODO: ADD MORE FORMATS
		supportedFormats.insert("mkv");
		supportedFormats.insert("mp4");
		supportedFormats.insert("avi");
	}

	void VideoParser::scanFolder(QString playlist) {
		for (auto& p : fs::directory_iterator(libraryfolder)) {
			if (supportedFormats.find(p.path().u8string().substr(p.path().u8string().length() - 3)) != supportedFormats.end()) {
				QStringList list;
				list.append(QString::fromStdString(p.path().u8string()));
				list.append(QString::fromStdString(p.path().u8string().erase(0, libraryfolder.length() + 1)));
				list.append("0");
				list.append("0");
				list.append("0");
				ThumbnailCreator tc;
				if (tc.generateThumbnail(p.path().u8string()))
					list.append(QString::fromStdString(libraryfolder) + "/thumbnails/" + QString::fromStdString(p.path().u8string().erase(0, libraryfolder.length() + 1)) + ".jpeg");
				else
					list.append(QString::fromStdString(":/MainWindow/videoicon.png"));
				writeFile(list);
			}
		}
		updateList(playlist);
	}

	void VideoParser::writeFile(QStringList list) {
		if (!videoExists(list.at(0))) {
			std::ofstream file;
			file.open(libraryfolder + VIDEOLIST_FILE_NAME, std::ios::app);
			file << "video:" << list.at(0).toStdString() << std::endl;
			file << "name:" << list.at(1).toStdString() << std::endl;
			file << "info:" << list.at(2).toStdString() << std::endl;
			file << "tags:" << list.at(3).toStdString() << std::endl;
			file << "playlist:" << list.at(4).toStdString() << std::endl;
			file << "thumbnail:" << list.at(5).toStdString() << std::endl;
		}
	}

	void VideoParser::updateList(QString playlist) {
		videolist.clear();
		std::ifstream file(libraryfolder + VIDEOLIST_FILE_NAME);
		std::list<std::map<std::string, std::string>> list;
		std::string line;

		int counter = 0;
		std::map<std::string, std::string> map;
		while (std::getline(file, line)) {
			counter++;
			int pos = line.find(':');
			map[line.substr(0, pos)] = line.substr(pos + 1);
			if (counter == 6) {
				counter = 0;
				list.push_back(map);
				map.clear();
			}
		}

		for (auto i = list.begin(); i != list.end(); ++i) {
			QListWidgetItem* item = new QListWidgetItem();
			std::map<std::string, std::string>::iterator it;

			it = i->find("playlist");
			if (playlist.compare("Your Library") == 0 || it->second.compare(playlist.toStdString()) == 0) {
				it = i->find("video");
				item->setData(Qt::StatusTipRole, QString::fromStdString(it->second));

				it = i->find("name");
				item->setData(Qt::DisplayRole, QString::fromStdString(it->second));

				it = i->find("info");
				item->setData(Qt::UserRole, QString::fromStdString(it->second));

				it = i->find("tags");
				if (QString::fromStdString(it->second).compare("0") != 0)
					item->setData(Qt::ToolTipRole, QString::fromStdString(it->second));
				else
					item->setData(Qt::ToolTipRole, QString::fromStdString(""));

				it = i->find("playlist");
				item->setData(Qt::WhatsThisRole, QString::fromStdString(it->second));

				it = i->find("thumbnail");
				item->setIcon(QPixmap(QString::fromStdString(it->second)));

				videolist.append(item);
			}
		}
	}

	void VideoParser::searchList(QString searchString) {
		searchlist.clear();
		std::ifstream file(libraryfolder + VIDEOLIST_FILE_NAME);
		std::list<std::map<std::string, std::string>> list;
		std::string line;

		int counter = 0;
		std::map<std::string, std::string> map;
		while (std::getline(file, line)) {
			counter++;
			int pos = line.find(':');
			map[line.substr(0, pos)] = line.substr(pos + 1);
			if (counter == 6) {
				counter = 0;
				list.push_back(map);
				map.clear();
			}
		}

		for (auto i = list.begin(); i != list.end(); ++i) {
			QListWidgetItem* item = new QListWidgetItem();
			std::map<std::string, std::string>::iterator it;
			bool found = false;
			std::string name, info, playlist, tags;

			it = i->find("name");
			name = it->second;
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			found ? true : found = name.find(searchString.toLower().toStdString()) != std::string::npos;
			it = i->find("info");
			info = it->second;
			std::transform(info.begin(), info.end(), info.begin(), ::tolower);
			found ? true : found = info.find(searchString.toLower().toStdString()) != std::string::npos;
			it = i->find("tags");
			tags = it->second;
			std::transform(tags.begin(), tags.end(), tags.begin(), ::tolower);
			found ? true : found = playlist.find(searchString.toLower().toStdString()) != std::string::npos;
			it = i->find("playlist");
			playlist = it->second;
			std::transform(playlist.begin(), playlist.end(), playlist.begin(), ::tolower);
			found ? true : found = tags.find(searchString.toLower().toStdString()) != std::string::npos;
			if (found) {
				it = i->find("video");
				item->setData(Qt::StatusTipRole, QString::fromStdString(it->second));

				it = i->find("name");
				item->setData(Qt::DisplayRole, QString::fromStdString(it->second));

				it = i->find("info");
				item->setData(Qt::UserRole, QString::fromStdString(it->second));

				it = i->find("tags");
				if (QString::fromStdString(it->second).compare("0") != 0)
					item->setData(Qt::ToolTipRole, QString::fromStdString(it->second));
				else
					item->setData(Qt::ToolTipRole, QString::fromStdString(""));

				it = i->find("playlist");
				item->setData(Qt::WhatsThisRole, QString::fromStdString(it->second));

				it = i->find("thumbnail");
				item->setIcon(QPixmap(QString::fromStdString(it->second)));

				searchlist.append(item);
			}
		}
	}

	void VideoParser::editVideo(QString path, QString name, QString info, QString tags, QString playlist) {
		std::ifstream ifile(libraryfolder + VIDEOLIST_FILE_NAME);
		std::ofstream ofile(libraryfolder + VIDEOLIST_FILE_NAME + "_TMP", std::ios::app);

		std::string line;
		while (std::getline(ifile, line)) {
			if (line.compare("video:" + path.toStdString()) == 0) {
				ofile << line << std::endl;
				if (name.compare("") != 0)
					ofile << "name:" << name.toStdString() << std::endl;
				else
					ofile << "name:" << "No name" << std::endl;
				if (info.compare("") != 0)
					ofile << "info:" << info.toStdString() << std::endl;
				else
					ofile << "info:" << "No info" << std::endl;
				if (tags.compare("") != 0)
					ofile << "tags:" << tags.toStdString() << std::endl;
				else
					ofile << "tags:" << "0" << std::endl;
				if (playlist.compare("None") != 0)
					ofile << "playlist:" << playlist.toStdString() << std::endl;
				else
					ofile << "playlist:" << "0" << std::endl;
				for (int i = 0; i < 5; ++i)
					std::getline(ifile, line);
				ofile << line << std::endl;
				std::getline(ifile, line);
				ofile << line << std::endl;
			} else {
				ofile << line << std::endl;
			}
		}

		ifile.close();
		ofile.close();

		QFile::remove(QString::fromStdString(libraryfolder + VIDEOLIST_FILE_NAME));
		std::rename(std::string(libraryfolder + VIDEOLIST_FILE_NAME + "_TMP").c_str(), std::string(libraryfolder + VIDEOLIST_FILE_NAME).c_str());
	}

	void VideoParser::deleteVideo(QString path) {
		std::ifstream ifile(libraryfolder + VIDEOLIST_FILE_NAME);
		std::ofstream ofile(libraryfolder + VIDEOLIST_FILE_NAME + "_TMP", std::ios::app);

		std::string line;
		while (std::getline(ifile, line)) {
			if (line.compare("video:" + path.toStdString()) == 0) {
				for (int i = 0; i < 5; ++i)
					std::getline(ifile, line);
			} else {
				ofile << line << std::endl;
			}
		}

		ifile.close();
		ofile.close();

		QFile::remove(QString::fromStdString(libraryfolder + VIDEOLIST_FILE_NAME));
		std::rename(std::string(libraryfolder + VIDEOLIST_FILE_NAME + "_TMP").c_str(), std::string(libraryfolder + VIDEOLIST_FILE_NAME).c_str());
	}

	bool VideoParser::fileExists(QString path) {
		for (auto& p : fs::directory_iterator(libraryfolder))
			if (p.path().u8string().compare(path.toStdString()) == 0)
				return true;
		return false;
	}

	bool VideoParser::videoExists(QString path) {
		std::ifstream file(libraryfolder + VIDEOLIST_FILE_NAME);
		std::string line;
		while (std::getline(file, line))
			if (line.compare("video:" + path.toStdString()) == 0)
				return true;
		return false;
	}
}