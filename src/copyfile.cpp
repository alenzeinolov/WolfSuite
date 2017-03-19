#include "copyfile.h"

namespace wolfsuite {

	CopyFile::CopyFile(const QStringList& list, const QString& dest) {
		copyList = list;
		destFolder = dest;
	}

	void CopyFile::run() {
		for (int i = 0; i < copyList.count(); ++i) {
			std::size_t found = copyList.at(i).toStdString().find_last_of("/\\");
			std::string d = destFolder.toStdString() + "/" + copyList.at(i).toStdString().substr(found + 1);
			copyFile(copyList.at(i), QString::fromStdString(d));
			emit signalCopyFile(i);
		}
	}

	void CopyFile::copyFile(QString src, QString dest) {
		QFile::copy(src, dest);
	}

}