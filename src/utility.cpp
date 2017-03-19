#include "utility.h"

namespace wolfsuite {

	bool copyFile(QString s, QString d) {
		std::size_t found = s.toStdString().find_last_of("/\\");
		std::string dS = d.toStdString() + "/" + s.toStdString().substr(found + 1);

		return QFile::copy(s, QString::fromStdString(dS));
	}

}