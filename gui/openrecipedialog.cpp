#include "openrecipedialog.h"
#include "ui_openrecipedialog.h"

OpenRecipeDialog::OpenRecipeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OpenRecipeDialog)
{
	ui->setupUi(this);
}

OpenRecipeDialog::~OpenRecipeDialog()
{
	delete ui;
}
