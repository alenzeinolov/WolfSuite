#include "editinfo.h"

EditInfo::EditInfo(QListWidgetItem *item, QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	this->item = item;
	vp = new wolfsuite::VideoParser("C:/Users/Alen/Videos/WSVideos");

	init();
}

EditInfo::~EditInfo() {
	delete vp;
}

void EditInfo::init() {
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(deleteLater()));
	connect(ui.editButton, SIGNAL(clicked()), this, SLOT(deleteLater()));

	setWindowTitle("Edit Video");

	ui.thumbnail->setPixmap(item->icon().pixmap(item->icon().actualSize(QSize(320, 180))));
	ui.nameEdit->setText(qvariant_cast<QString>(item->data(Qt::DisplayRole)));
	ui.infoEdit->setText(qvariant_cast<QString>(item->data(Qt::UserRole)));
	ui.tagsEdit->setText(qvariant_cast<QString>(item->data(Qt::ToolTipRole)));
}

void EditInfo::on_editButton_clicked() {
	vp->editVideo(qvariant_cast<QString>(item->data(Qt::StatusTipRole)), ui.nameEdit->text(), ui.infoEdit->toPlainText(), ui.tagsEdit->text());
}
