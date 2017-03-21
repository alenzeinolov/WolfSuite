#ifndef COPYFILE_H
#define COPYFILE_H

#include <QFile>
#include <QProgressDialog>
#include <QThread>

namespace wolfsuite {

	class CopyFile : public QThread {
		Q_OBJECT
	public:
		CopyFile(const QStringList& list, const QString& dest);
	public:
		QStringList copyList;
		QString destFolder;
		bool canceled;
	public:
		void run();
	signals:
		void signalCopyFile(const int);
	public slots:
		void cancelPressed();
	private:
		void copyFile(QString src, QString dest);
	};

}

#endif