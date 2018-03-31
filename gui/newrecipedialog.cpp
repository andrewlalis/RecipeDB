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

NewRecipeDialog::NewRecipeDialog(RecipeDatabase *db, Recipe recipe, QWidget *parent) : NewRecipeDialog(db, parent){
	ui->recipeNameEdit->setText(QString::fromStdString(recipe.getName()));
	ui->prepTimeEdit->setTime(recipe.getPrepTime());
	ui->cookTimeEdit->setTime(recipe.getCookTime());
	ui->servingsSpinBox->setValue((double)recipe.getServings());
	ui->instructionsTextEdit->setHtml(QString::fromStdString(recipe.getInstruction().getHTML()));
	ui->imageDisplayLabel->setPixmap(QPixmap::fromImage(recipe.getImage()));
	this->tagsListModel.setTags(recipe.getTags());
	this->ingredientListModel.setIngredients(recipe.getIngredients());
}

NewRecipeDialog::~NewRecipeDialog(){
	delete ui;
}

Recipe NewRecipeDialog::getRecipe(){
	Recipe r(ui->recipeNameEdit->text().toStdString(),
			 this->ingredientListModel.getIngredients(),
			 ui->instructionsTextEdit->toHtml().toStdString(),
			 ui->imageDisplayLabel->pixmap()->toImage(),//Image
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
	ui->commentsLineEdit->clear();
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
		ui->imageDisplayLabel->setPixmap(QPixmap(filename));
	}
}

void NewRecipeDialog::on_removeIngredientButton_clicked(){
	QModelIndexList indexList = ui->ingredientsListView->selectionModel()->selectedIndexes();
	for (QModelIndexList::iterator it = indexList.begin(); it != indexList.end(); ++it){
		QModelIndex i = *it;
		this->ingredientListModel.deleteIngredient(i.row());
	}
}

void NewRecipeDialog::on_deleteIngredientButton_clicked(){
	int index = ui->ingredientNameBox->currentIndex();
	Ingredient ing = this->ingredients.at(index);
	QMessageBox::StandardButton reply = QMessageBox::question(this,
															  QString::fromStdString("Delete Ingredient"),
															  QString::fromStdString("Are you sure you want to delete the ingredient " + ing.getName() + "?"));
	if (reply == QMessageBox::Yes){
		bool success = this->recipeDB->deleteIngredient(ing.getName());
		if (!success){
			QMessageBox::critical(this, QString::fromStdString("Error"), QString::fromStdString("Unable to delete ingredient: " + ing.getName() + ", some recipes use it!"));
		} else {
			this->populateIngredientsBox();
		}
	}
}

void NewRecipeDialog::on_newIngredientButton_clicked(){
	NewIngredientDialog d(this->recipeDB, this);
	d.show();
	if (d.exec() == QDialog::Accepted){
		Ingredient i = d.getIngredient();
		if (!i.getName().empty() && !i.getFoodGroup().empty() && this->recipeDB->storeIngredient(i)){
			this->populateIngredientsBox();
			ui->ingredientNameBox->setCurrentText(QString::fromStdString(i.getName()));
		} else {
			QMessageBox::critical(this, "Error", "Unable to add ingredient.");
		}

	}
}

void NewRecipeDialog::on_newTagButton_clicked(){
	NewTagDialog d(this);
	d.show();
	if (d.exec() == QDialog::Accepted){
		RecipeTag tag = d.getTag();
		//Temporarily add this to the tags list, and it will be saved if the recipe is saved.
		if (!tag.getValue().empty()){
			this->tags.push_back(tag);
			this->tagsListModel.addTag(tag);
			ui->tagsComboBox->clear();
			for (unsigned int i = 0; i < this->tags.size(); i++){
				QString s = QString::fromStdString(this->tags[i].getValue());
				ui->tagsComboBox->insertItem(i, s);
			}
		} else {
			QMessageBox::warning(this, "Empty Tag", "The tag you entered is blank!");
		}
	}

}

void NewRecipeDialog::on_removeTagButton_clicked(){
	unsigned int index = ui->tagsComboBox->currentIndex();
	if (index >= this->tags.size()){
		return;
	}
	RecipeTag tag = this->tags[ui->tagsComboBox->currentIndex()];
	string content = "Are you sure you wish to delete the following tag:\n"+tag.getValue()+"\nThis will delete the tag for all recipes that use it.";
	QMessageBox::StandardButton reply = QMessageBox::question(this, QString("Delete Tag"), QString(content.c_str()));
	if (reply == QMessageBox::Yes){
		this->recipeDB->deleteTag(tag);
		this->populateTagsBox();
	}
}

void NewRecipeDialog::on_newUnitButton_clicked(){
	NewUnitDialog d(this);
	d.show();
	if (d.exec() == QDialog::Accepted){
		UnitOfMeasure u = d.getUnit();
		if (u.getName().empty() || u.getNamePlural().empty() || u.getAbbreviation().empty() || !this->recipeDB->storeUnitOfMeasure(u)){
			QMessageBox::critical(this, "Error", "Unable to store new unit. Make sure all the information is filled in!");
		} else {
			this->populateUnitsBox();
			ui->unitComboBox->setCurrentText(QString::fromStdString(u.getName()));
		}
	}
}

void NewRecipeDialog::on_deleteUnitButton_clicked(){
	int index = ui->unitComboBox->currentIndex();
	UnitOfMeasure unit = this->units[index];
	QMessageBox::StandardButton reply = QMessageBox::question(this,
															  QString::fromStdString("Delete Unit Of Measure"),
															  QString::fromStdString("Are you sure you want to delete the unit " + unit.getName() + "?"));
	if (reply == QMessageBox::Yes){
		if (!this->recipeDB->deleteUnitOfMeasure(unit.getName())){
			QMessageBox::critical(this, "Error", "Unable to delete unit. There may be recipes which still use it!");
		} else {
			this->populateUnitsBox();
		}
	}
}
