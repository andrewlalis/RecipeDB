#include "newrecipedialog.h"
#include "ui_newrecipedialog.h"

NewRecipeDialog::NewRecipeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewRecipeDialog)
{
	ui->setupUi(this);
}

NewRecipeDialog::~NewRecipeDialog()
{
	delete ui;
}
