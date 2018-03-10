#include "newtagdialog.h"
#include "ui_newtagdialog.h"

NewTagDialog::NewTagDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::newTagDialog)
{
	ui->setupUi(this);
}

NewTagDialog::~NewTagDialog()
{
	delete ui;
}

RecipeTag NewTagDialog::getTag(){
	return RecipeTag(ui->tagEdit->text().toLower().toStdString());
}
