//# VIDEOLIST FILE FORMAT
//# 0 - FILE PATH
//# 1 - FILE NAME
//# 2 - VIDEO INFO
//# 3 - TAGS
//# 4 - PLAYLIST(0 IF IN NONE)
//# 5 - THUMBNAIL PATH

#ifndef VIDEOPARSER_H
#define VIDEOPARSER_H

#include <experimental/filesystem>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <string>

#include <QList>
#include <QListWidget>
#include <QListWidgetItem>

#include "thumbnailcreator.h"
#include "utility.h"

#define VIDEOLIST_FILE_NAME "/videolist"

namespace fs = std::experimental::filesystem;

namespace wolfsuite {

	class VideoParser {
	public:
		VideoParser(std::string filename);
	private:
		std::set<std::string> supportedFormats;
	public:
		std::string libraryfolder;
		QList<QListWidgetItem*> videolist;
	public:
		void scanFolder(QString playlist);
		void writeFile(QStringList list);
		void updateList(QString playlist);
		QList<QListWidgetItem*> getPlaylist(QString playlist);
		void editVideo(QString path, QString name, QString info, QString tags, QString playlist);
		void deleteVideo(QString path);
		bool fileExists(QString path);
		bool videoExists(QString path);
	};

}

#endif