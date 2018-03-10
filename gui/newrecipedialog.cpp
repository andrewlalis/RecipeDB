#include "newrecipedialog.h"
#include "ui_newrecipedialog.h"

NewRecipeDialog::NewRecipeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewRecipeDialog){
	ui->setupUi(this);

	setModal(true);

	ui->ingredientsListView->setModel(&this->ingredientListModel);
	ui->tagsListView->setModel(&this->tagsListModel);
}

NewRecipeDialog::NewRecipeDialog(RecipeDatabase *db, QWidget *parent) : NewRecipeDialog(parent){
	this->recipeDB = db;


	this->populateIngredientsBox();
	this->populateUnitsBox();
	this->populateTagsBox();
}

NewRecipeDialog::~NewRecipeDialog(){
	delete ui;
}

Recipe NewRecipeDialog::getRecipe(){
	Recipe r(ui->recipeNameEdit->text().toStdString(),
			 this->ingredientListModel.getIngredients(),
			 ui->instructionsTextEdit->toHtml().toStdString(),
			 this->img,//Image
			 this->tagsListModel.getTags(),//Tags
			 QDate::currentDate(),
			 ui->prepTimeEdit->time(),
			 ui->cookTimeEdit->time(),
			 (float)ui->servingsSpinBox->value());
	return r;
}

bool NewRecipeDialog::isAccepted() const{
	return this->accepted;
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

void NewRecipeDialog::populateTagsBox(){
	this->tags = this->recipeDB->retrieveAllTags();
	ui->tagsComboBox->clear();
	for (unsigned int i = 0; i < this->tags.size(); i++){
		QString s = QString::fromStdString(this->tags[i].getValue());
		ui->tagsComboBox->insertItem(i, s);
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

void NewRecipeDialog::on_buttonBox_accepted(){
	this->accepted = true;
	this->close();
}

void NewRecipeDialog::on_buttonBox_rejected(){
	this->close();
}

void NewRecipeDialog::on_addTagButton_clicked(){
	//Add a tag to the list of those prepared to be added.
	this->tagsListModel.addTag(this->tags[ui->tagsComboBox->currentIndex()]);
}

void NewRecipeDialog::on_deleteTagButton_clicked(){
	QModelIndexList indexList = ui->tagsListView->selectionModel()->selectedIndexes();
	for (QModelIndexList::iterator it = indexList.begin(); it != indexList.end(); ++it){
		QModelIndex i = *it;
		this->tagsListModel.deleteTag(i.row());
	}
}

void NewRecipeDialog::on_selectImageButton_clicked(){
	QString filename = QFileDialog::getOpenFileName(this, "Open Image", QString(), "Image Files (*.png *.jpg *.bmp)");
	if (!filename.isEmpty()){
		this->img = QImage(filename);
		ui->imageDisplayLabel->setPixmap(QPixmap(filename));
	}
}
