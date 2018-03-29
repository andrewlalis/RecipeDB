#include "newunitdialog.h"
#include "ui_newunitdialog.h"

NewUnitDialog::NewUnitDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewUnitDialog)
{
	ui->setupUi(this);

	ui->typeComboBox->clear();
	QStringList list({"Mass", "Volume", "Length", "Misc"});
	ui->typeComboBox->insertItems(0, list);

}

NewUnitDialog::~NewUnitDialog()
{
	delete ui;
}

UnitOfMeasure NewUnitDialog::getUnit(){
	return UnitOfMeasure(ui->unitNameEdit->text().toLower().toStdString(),
						 ui->pluralNameEdit->text().toLower().toStdString(),
						 ui->abbreviationEdit->text().toStdString(),
						 this->getSelectedType(),
						 ui->coefficientSpinBox->value());
}

int NewUnitDialog::getSelectedType(){
	return ui->typeComboBox->currentIndex();
}
