#include "newingredientdialog.h"
#include "ui_newingredientdialog.h"

NewIngredientDialog::NewIngredientDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewIngredientDialog)
{
	ui->setupUi(this);
}

NewIngredientDialog::NewIngredientDialog(RecipeDatabase *recipeDB, QWidget *parent) : NewIngredientDialog(parent){
	this->recipeDB = recipeDB;
	this->populateFoodGroupBox();
}

NewIngredientDialog::~NewIngredientDialog()
{
	delete ui;
}

Ingredient NewIngredientDialog::getIngredient(){
	return Ingredient(ui->nameEdit->text().toLower().toStdString(), ui->foodGroupBox->currentText().toStdString());
}

void NewIngredientDialog::populateFoodGroupBox(){
	vector<string> foodGroups = this->recipeDB->retrieveAllFoodGroups();
	ui->foodGroupBox->clear();
	for (unsigned int i = 0; i < foodGroups.size(); i++){
		QString s = QString::fromStdString(foodGroups[i]);
		ui->foodGroupBox->insertItem(i, s);
	}
}

void NewIngredientDialog::on_addFoodGroupButton_clicked(){
	newFoodGroupDialog d(this);
	if (d.exec() == QDialog::Accepted){
		string s = d.getFoodGroup();
		if (!s.empty()){
			ui->foodGroupBox->addItem(QString::fromStdString(s));
			ui->foodGroupBox->setCurrentText(QString::fromStdString(s));
		} else {
			QMessageBox::warning(this, "Empty Food Group", "The food group you entered is empty!");
		}
	}
}

void NewIngredientDialog::on_deleteFoodGroupButton_clicked(){
	ui->foodGroupBox->removeItem(ui->foodGroupBox->currentIndex());
}
