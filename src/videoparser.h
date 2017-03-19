#ifndef VIDEOPARSER_H
#define VIDEOPARSER_H

#include <experimental/filesystem>
#include <fstream>
#include <set>
#include <string>

#include <QList>
#include <QListWidget>
#include <QListWidgetItem>

#include "utility.h"

#define VIDEOLIST_FILE_NAME "/videolist"

namespace fs = std::experimental::filesystem;

namespace wolfsuite {

	class VideoParser {
	public:
		VideoParser(std::string filename);
	public:
		std::set<std::string> supportedFormats;
		std::string libraryfolder;
		QList<QListWidgetItem*> videolist;
	public:
		void scanFolder();
		void writeFile(QStringList list);
		void updateList();
		bool videoExists(QString path);
	};

}

#endif