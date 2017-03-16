#ifndef VIDEOPARSER_H
#define VIDEOPARSER_H

#include <experimental/filesystem>
#include <fstream>
#include <ostream>
#include <string>

#include <QList>
#include <QListWidget>
#include <QListWidgetItem>

#include "utility.h"

namespace fs = std::experimental::filesystem;

namespace wolfsuite {

	class VideoParser {
	public:
		VideoParser(std::string filename);
	public:
		std::string libraryfolder;
		QList<QListWidgetItem*> videolist;
	public:
		void scanFolder();
	};

}

#endif