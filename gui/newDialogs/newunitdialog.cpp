#include "newunitdialog.h"
#include "ui_newunitdialog.h"

NewUnitDialog::NewUnitDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewUnitDialog)
{
	ui->setupUi(this);

	ui->typeComboBox->clear();
	ui->typeComboBox->setItemData(0, "Mass");
	ui->typeComboBox->setItemData(1, "Volume");
	ui->typeComboBox->setItemData(2, "Length");
	ui->typeComboBox->setItemData(3, "Misc");

}

NewUnitDialog::~NewUnitDialog()
{
	delete ui;
}

UnitOfMeasure NewUnitDialog::getUnit(){
	return UnitOfMeasure(ui->unitNameEdit->text().toLower().toStdString(),
						 ui->pluralNameEdit->text().toLower().toStdString(),
						 ui->abbreviationEdit->text().toLower().toStdString(),
						 this->getSelectedType(),
						 ui->coefficientSpinBox->value());
}

int NewUnitDialog::getSelectedType(){
	return ui->typeComboBox->currentIndex();
}
