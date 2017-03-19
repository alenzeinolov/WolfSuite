#ifndef COPYFILE_H
#define COPYFILE_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QStatusBar>
#include <QTime>

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
	public:
		void run();
	signals:
		void signalCopyFile(const int);
	private:
		void copyFile(QString src, QString dest);
	};

}

#endif