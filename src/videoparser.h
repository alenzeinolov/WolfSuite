#ifndef VIDEOPARSER_H
#define VIDEOPARSER_H

#include <experimental/filesystem>
#include <fstream>
#include <ostream>
#include <string>

#include <QList>

namespace fs = std::experimental::filesystem;

namespace wolfsuite {

	class VideoParser {
	public:
		VideoParser(std::string filename);
	public:
		std::string libraryfolder;
		QList<QString> videolist;
	public:
		void scanFolder();

		//inline QList<QString> getVideolist() const { return videolist; }
	};

}

#endif