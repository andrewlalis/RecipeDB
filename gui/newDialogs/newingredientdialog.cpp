#include "newingredientdialog.h"
#include "ui_newingredientdialog.h"

NewIngredientDialog::NewIngredientDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewIngredientDialog)
{
	ui->setupUi(this);
}

NewIngredientDialog::~NewIngredientDialog()
{
	delete ui;
}

Ingredient NewIngredientDialog::getIngredient(){
	return Ingredient(ui->nameEdit->text().toLower().toStdString(), ui->foodGroupEdit->text().toLower().toStdString());
}
