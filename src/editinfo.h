/**
 * @file
 * Copyright (C) 2017 by Alen Zeinolov
 * 
 * EditInfo class is a Qt Widget that handles the appearance
 * and functionality of the EditInfo widget that is invoked
 * when user decideds to edit the selected video information
 *
 * @author Alen Zeinolov
 * @version 0.1
 * @date 2017
 */

#ifndef EDITINFO_H
#define EDITINFO_H

#include <QWidget>

#include "config.h"
#include "videoparser.h"

#include "ui_editinfo.h"

class EditInfo : public QWidget
{
	Q_OBJECT

public:
	/**
	 * Creates a new instance of EditInfo class.
	 * @param item containing all the information about the video to be edited.
	 */
	EditInfo(QListWidgetItem *item, QWidget *parent = Q_NULLPTR);
	~EditInfo();
private:
	/**
	 * Initialises the variables and settings required
	 * for EditInfo widget to function properly.
	 */
	void init();
private slots:
	/**
	 * A slot that is invoked when user pressed "Edit" button
	 * Collects all the information that user has entered
	 * and saves it into the videolist file.
	 */
	void on_editButton_clicked();
private:
	Ui::EditInfo ui;

	/**
	 * Item containing all the information about the video to be edited.
	 */
	QListWidgetItem *item;
	wolfsuite::Config *config;
	wolfsuite::VideoParser *vp;
};

#endif