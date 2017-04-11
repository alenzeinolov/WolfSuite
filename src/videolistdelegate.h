/**
 * @file
 * Copyright (C) 2017 by Alen Zeinolov
 * 
 * VideoListDelegate is a QStyledItemDelegate class that is responsible for presenting
 * additional information on videolist. It allows for display name and video information
 * to be presented at the same time.
 *
 * @author Alen Zeinolov
 * @version 0.1
 * @date 2017
 */

#ifndef VIDEOLISTDELEGATE_H
#define VIDEOLISTDELEGATE_H

#include <QApplication>
#include <QModelIndex>
#include <QPainter>
#include <QObject>
#include <QStyledItemDelegate>

class VideoListDelegate : public QStyledItemDelegate {
	Q_OBJECT
public:
	VideoListDelegate(QWidget* parent = 0) : QStyledItemDelegate(parent) {}
	/*
	 * Paints the information provided from option item including the additional information such as video info.
	 * @param painter instance to be used for painting
	 * @param an option that is being loaded into the list
	 * @param model index of the option
	 */
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif