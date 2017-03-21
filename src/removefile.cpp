#include "removefile.h"

namespace wolfsuite {

	RemoveFile::RemoveFile(const QString& f) {
		file = f;
	}

	void RemoveFile::run() {
		removeFile(file);
	}

	void RemoveFile::removeFile(QString f) {
		QFile::remove(f);
	}
}