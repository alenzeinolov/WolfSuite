#include "editinfo.h"

EditInfo::EditInfo(QListWidgetItem *item, QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	this->item = item;
	config = new wolfsuite::Config();
	config->loadConfig();
	config->loadPlaylist();
	vp = new wolfsuite::VideoParser(config->config.find("libraryfolder")->second);

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
	if (qvariant_cast<QString>(item->data(Qt::UserRole)).compare("0") == 0)
		ui.infoEdit->setText("No info");
	else
		ui.infoEdit->setText(qvariant_cast<QString>(item->data(Qt::UserRole)));
	ui.tagsEdit->setText(qvariant_cast<QString>(item->data(Qt::ToolTipRole)));
	ui.playlistEdit->addItem("None");
	for (int i = 0; i < config->playlists.length(); ++i)
		ui.playlistEdit->addItem(qvariant_cast<QString>(config->playlists.at(i)->data(Qt::DisplayRole)));
	if (qvariant_cast<QString>(item->data(Qt::ToolTipRole)).compare("0") == 0) {
		ui.playlistEdit->setCurrentIndex(0);
	} else {
		for (int i = 0; i < ui.playlistEdit->count(); ++i)
			if (qvariant_cast<QString>(item->data(Qt::WhatsThisRole)).compare(ui.playlistEdit->itemText(i)) == 0)
				ui.playlistEdit->setCurrentIndex(i);
	}
}

void EditInfo::on_editButton_clicked() {
	vp->editVideo(qvariant_cast<QString>(item->data(Qt::StatusTipRole)), ui.nameEdit->text(), ui.infoEdit->toPlainText(), ui.tagsEdit->text(), ui.playlistEdit->currentText());
}
