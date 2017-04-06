#include "videolistdelegate.h"

void VideoListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	if (index.data().canConvert<QString>()) {
		if (option.state & QStyle::State_Selected) {
			painter->save();
			painter->setPen(Qt::white);
			painter->setPen(Qt::DashLine);
			painter->setOpacity(0.5);
			painter->fillRect(option.rect, option.palette.highlight());
			painter->restore();
		} else if (option.state & QStyle::State_MouseOver) {
			painter->save();
			painter->setPen(Qt::white);
			painter->setPen(Qt::DashLine);
			painter->setOpacity(0.25);
			painter->fillRect(option.rect, option.palette.highlight());
			painter->restore();
		}

		QFont font = QApplication::font();
		QFont subFont = QApplication::font();
		font.setBold(true);
		subFont.setWeight(subFont.weight() - 2);
		QFontMetrics fm(font);

		QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
		QString name = qvariant_cast<QString>(index.data(Qt::DisplayRole));
		QString info = qvariant_cast<QString>(index.data(Qt::UserRole));

		QSize iconsize = icon.actualSize(option.decorationSize);

		QRect iconRect = option.rect;
		QRect nameRect = option.rect;
		QRect infoRect = option.rect;

		iconRect.setLeft(0);
		iconRect.setRight(iconsize.width() + 2);
		iconRect.setBottom(iconsize.height());
		nameRect.setLeft(iconRect.right());
		nameRect.setBottom(nameRect.top() + fm.height());
		infoRect.setLeft(iconRect.right());
		infoRect.setTop(nameRect.bottom() + 2);

		painter->drawPixmap(QPoint(0, iconRect.top()), icon.pixmap(iconsize.width(), iconsize.height()));

		painter->setFont(font);
		painter->drawText(nameRect, name);

		painter->setFont(subFont);
		painter->drawText(infoRect, info);
	} else {
		QStyledItemDelegate::paint(painter, option, index);
	}
}

QSize VideoListDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	if (index.data().canConvert<QString>()) {
		QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
		QSize iconsize = icon.actualSize(option.decorationSize);
		return(QSize(iconsize.width(), iconsize.height()));
	}
	else {
		return QStyledItemDelegate::sizeHint(option, index);
	}
}
