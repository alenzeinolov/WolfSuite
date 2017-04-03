#ifndef VIDEOLISTDELEGATE_H
#define VIDEOLISTDELEGATE_H

#include <QStyledItemDelegate>

class VideoListDelegate : public QStyledItemDelegate {
	Q_OBJECT
public:
	VideoListDelegate(QWidget* parent = 0) : QStyledItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif