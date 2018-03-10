#include "newrecipedialog.h"
#include "ui_newrecipedialog.h"

NewRecipeDialog::NewRecipeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewRecipeDialog){
	ui->setupUi(this);
}

NewRecipeDialog::NewRecipeDialog(RecipeDatabase *db, QWidget *parent) : NewRecipeDialog(parent){
	this->recipeDB = db;


	this->populateIngredientsBox();
	this->populateUnitsBox();
}

NewRecipeDialog::~NewRecipeDialog(){
	delete ui;
}

void NewRecipeDialog::on_toolButton_clicked(){
	ui->instructionsTextEdit->setFontItalic(!ui->instructionsTextEdit->fontItalic());
}

void NewRecipeDialog::populateIngredientsBox(){
	this->ingredients = this->recipeDB->retrieveAllIngredients();
	ui->ingredientNameBox->clear();
	for (unsigned int i = 0; i < this->ingredients.size(); i++){
		QString s = QString::fromStdString(this->ingredients[i].getName());
		ui->ingredientNameBox->insertItem(i, s);
	}
}

void NewRecipeDialog::populateUnitsBox(){
	this->units = this->recipeDB->retrieveAllUnitsOfMeasure();
	ui->unitComboBox->clear();
	for (unsigned int i = 0; i < this->units.size(); i++){
		QString s = QString::fromStdString(this->units[i].getName());
		ui->unitComboBox->insertItem(i, s);
	}
}
