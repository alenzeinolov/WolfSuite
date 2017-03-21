#include "copyfile.h"

namespace wolfsuite {

	CopyFile::CopyFile(const QStringList& list, const QString& dest) {
		copyList = list;
		destFolder = dest;
		canceled = false;
	}

	void CopyFile::run() {
		for (int i = 0; i < copyList.count(); ++i) {
			if (canceled)
				break;
			std::size_t found = copyList.at(i).toStdString().find_last_of("/\\");
			std::string d = destFolder.toStdString() + "/" + copyList.at(i).toStdString().substr(found + 1);
			copyFile(copyList.at(i), QString::fromStdString(d));
			emit signalCopyFile(i + 1);
		}
	}

	void CopyFile::copyFile(QString src, QString dest) {
		QFile::copy(src, dest);
	}

	void CopyFile::cancelPressed() {
		canceled = true;
	}

}