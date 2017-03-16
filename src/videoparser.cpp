#include "videoparser.h"

namespace wolfsuite {

	VideoParser::VideoParser(std::string filename) {
		libraryfolder = filename;
	}

	void VideoParser::scanFolder() {
		for (auto& p : fs::directory_iterator(libraryfolder)) {
			QListWidgetItem* item = new QListWidgetItem();
			item->setData(Qt::DisplayRole, QString::fromStdString(p.path().u8string().erase(0, libraryfolder.length() + 1)));
			item->setData(Qt::StatusTipRole, QString::fromStdString(p.path().u8string()));
			item->setData(Qt::UserRole, "JUST SOME VIDEO YOLO");
			item->setData(Qt::DecorationRole, QPixmap("res/images/videoIcon.png"));
			videolist.append(item);
		}
	}
}