/**
 * @file
 * Copyright (C) 2017 by Alen Zeinolov
 * 
 * CopyFile is a QThread class handles adding single and multiple videos
 * into the user folder.
 *
 * @author Alen Zeinolov
 * @version 0.1
 * @date 2017
 */

#ifndef COPYFILE_H
#define COPYFILE_H

#include <QFile>
#include <QProgressDialog>
#include <QThread>

namespace wolfsuite {

	class CopyFile : public QThread {
		Q_OBJECT
	public:
		/**
		 * Creates a new CopyFile instance with given arguments.
		 * @param list of paths to video files to copy to the user library folder.
		 * @param destination path where the files will be copied to.
		 */
		CopyFile(const QStringList& list, const QString& dest);
	public:
		/**
		 * List of paths to video files to be copied.
		 */
		QStringList copyList;
		/**
		 * Path of the destination folder to copy the files from copyList to.
		 */
		QString destFolder;
		/**
		 * Holds information whether the user decided to cancel the copying operation.
		 */
		bool canceled;
	public:
		void run();
	signals:
		/**
		 * A signal that is emitted when the a file has been copied.
		 * It is used to update the progress bar that is presented to the user
		 * during copy operation.
		 * @param the number of file that has just been copied
		 */
		void signalCopyFile(const int);
	public slots:
		/**
		 * Slot that is called from by the user when they decided to cancel
		 * the copying operation, changes canceled variable to true,
		 * indicating that the copying task is canceled by user.
		 */
		void cancelPressed();
	private:
		/**
		 * Internal operation that copies file from the
		 * source path provided into the destination path.
		 * @param source path of the file to copy
		 * @param destination path where to copy the source file to
		 */
		void copyFile(QString src, QString dest);
	};

}

#endif