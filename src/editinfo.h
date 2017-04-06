#pragma once

#include <QWidget>

#include "videoparser.h"

#include "ui_editinfo.h"

class EditInfo : public QWidget
{
	Q_OBJECT

public:
	EditInfo(QListWidgetItem *item, QWidget *parent = Q_NULLPTR);
	~EditInfo();
private:
	void init();
private slots:
	void on_editButton_clicked();
private:
	Ui::EditInfo ui;

	QListWidgetItem *item;
	wolfsuite::VideoParser *vp;
};
