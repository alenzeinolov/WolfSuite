#include "videoparser.h"

namespace wolfsuite {

	VideoParser::VideoParser(std::string filename) {
		libraryfolder = filename;
	}

	void VideoParser::scanFolder() {
		for (auto& p : fs::directory_iterator(libraryfolder)) {
			videolist.append(QString::fromStdString(p.path().u8string()));
		}
	}
}