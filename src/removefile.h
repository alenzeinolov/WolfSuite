#ifndef REMOVEFILE_H
#define REMOVEFILE_H

#include <QFile>
#include <QProgressDialog>
#include <QThread>

namespace wolfsuite {

	class RemoveFile : public QThread {
		Q_OBJECT
	public:
		RemoveFile(const QString& file);
	public:
		QString file;
	public:
		void run();
	private:
		void removeFile(QString f);
	};

}

#endif