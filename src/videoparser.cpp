#include "videoparser.h"

namespace wolfsuite {

	VideoParser::VideoParser(std::string filename) {
		libraryfolder = filename;

		// TODO: ADD MORE FORMATS
		supportedFormats.insert("mkv");
		supportedFormats.insert("mp4");
		supportedFormats.insert("avi");
	}

	void VideoParser::scanFolder() {
		for (auto& p : fs::directory_iterator(libraryfolder)) {
			if (supportedFormats.find(p.path().u8string().substr(p.path().u8string().length() - 3)) != supportedFormats.end()) {
				QStringList list;
				list.append(QString::fromStdString(p.path().u8string()));
				list.append(QString::fromStdString(p.path().u8string().erase(0, libraryfolder.length() + 1)));
				list.append("JUST SOME VIDEO YOLO");
				list.append("NONE");
				list.append("0");
				ThumbnailCreator tc;
				if (tc.generateThumbnail(p.path().u8string()))
					list.append(QString::fromStdString(libraryfolder) + "/thumbnails/" + QString::fromStdString(p.path().u8string().erase(0, libraryfolder.length() + 1)) + ".jpeg");
				else
					list.append(QString::fromStdString("res/images/videoIcon.png"));
				writeFile(list);
			}
		}
		updateList();
	}

	void VideoParser::writeFile(QStringList list) {
		if (!videoExists(list.at(0))) {
			std::ofstream file;
			file.open(libraryfolder + VIDEOLIST_FILE_NAME, std::ios::app);
			file << "[VIDEO]" << std::endl;
			for (int i = 0; i < list.count(); ++i) {
				file << list.at(i).toStdString() << std::endl;
			}
			file << std::endl;
		}
	}

	void VideoParser::updateList() {
		videolist.clear();
		std::ifstream file(libraryfolder + VIDEOLIST_FILE_NAME);
		std::string line;
		while (std::getline(file, line)) {
			if (line.compare("[VIDEO]") == 0) {
				std::getline(file, line);
				if (fileExists(QString::fromStdString(line))) {
					QListWidgetItem* item = new QListWidgetItem();
					item->setData(Qt::StatusTipRole, QString::fromStdString(line));

					std::getline(file, line);
					item->setData(Qt::DisplayRole, QString::fromStdString(line));

					std::getline(file, line);
					item->setData(Qt::UserRole, QString::fromStdString(line));

					std::getline(file, line);
					// TODO: VIDEO TAGS

					std::getline(file, line);
					// TODO: PLAYLIST

					std::getline(file, line);
					item->setIcon(QPixmap(QString::fromStdString(line)));
					//item->setData(Qt::DecorationRole, QPixmap(QString::fromStdString(line)));
					videolist.append(item);
				}
			}
		}
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
			if (line.compare(path.toStdString()) == 0)
				return true;
		return false;
	}
}