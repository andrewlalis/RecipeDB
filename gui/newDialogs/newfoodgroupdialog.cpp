#include "newfoodgroupdialog.h"
#include "ui_newfoodgroupdialog.h"

newFoodGroupDialog::newFoodGroupDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::newFoodGroupDialog)
{
	ui->setupUi(this);
}

newFoodGroupDialog::~newFoodGroupDialog()
{
	delete ui;
}

string newFoodGroupDialog::getFoodGroup() const{
	return ui->lineEdit->text().toStdString();
}
