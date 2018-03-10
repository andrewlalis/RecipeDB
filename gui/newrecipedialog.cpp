#include "newrecipedialog.h"
#include "ui_newrecipedialog.h"

NewRecipeDialog::NewRecipeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewRecipeDialog){
	ui->setupUi(this);

	ui->ingredientsListView->setModel(&this->ingredientListModel);
}

NewRecipeDialog::NewRecipeDialog(RecipeDatabase *db, QWidget *parent) : NewRecipeDialog(parent){
	this->recipeDB = db;


	this->populateIngredientsBox();
	this->populateUnitsBox();
}

NewRecipeDialog::~NewRecipeDialog(){
	delete ui;
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

void NewRecipeDialog::on_addIngredientButton_clicked(){
	//Construct a recipe ingredient from the supplied data.
	Ingredient i = this->ingredients[ui->ingredientNameBox->currentIndex()];
	UnitOfMeasure u = this->units[ui->unitComboBox->currentIndex()];
	RecipeIngredient ri(i, ui->quantitySpinBox->value(), u, ui->commentsLineEdit->text().toStdString());
	this->ingredientListModel.addIngredient(ri);
}

void NewRecipeDialog::on_italicsButton_clicked(){
	ui->instructionsTextEdit->setFontItalic(ui->italicsButton->isChecked());
}

void NewRecipeDialog::on_boldButton_clicked(){
	if (ui->boldButton->isChecked()){
		ui->instructionsTextEdit->setFontWeight(QFont::Bold);
	} else {
		ui->instructionsTextEdit->setFontWeight(QFont::Normal);
	}
}
