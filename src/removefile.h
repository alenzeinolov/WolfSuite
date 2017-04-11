/**
 * @file
 * Copyright (C) 2017 by Alen Zeinolov
 * 
 * RemoveFile is a QThread class that handles removing video files
 * from the user library.
 *
 * @author Alen Zeinolov
 * @version 0.1
 * @date 2017
 */

#ifndef REMOVEFILE_H
#define REMOVEFILE_H

#include <QFile>
#include <QProgressDialog>
#include <QThread>

namespace wolfsuite {

	class RemoveFile : public QThread {
		Q_OBJECT
	public:
		/**
		 * Creates a new instance of RemoveFile class.
		 * It assigns file path to the file path provided.
		 * @param path to the video file to be deleted.
		 */
		RemoveFile(const QString& file);
	public:
		/*
		 * File path to the file to be deleted.
		 */
		QString file;
	public:
		void run();
	private:
		/*
		 * Removes the file specified.
		 * @param file path to the file to be removed.
		 */
		void removeFile(QString f);
	};

}

#endif