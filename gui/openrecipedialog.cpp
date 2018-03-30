#include "openrecipedialog.h"
#include "ui_openrecipedialog.h"

OpenRecipeDialog::OpenRecipeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OpenRecipeDialog)
{
	ui->setupUi(this);

	ui->recipeTableView->setModel(&this->recipeTableModel);
	ui->ingredientsListView->setModel(&this->ingredientsModel);
	ui->tagsListView->setModel(&this->tagsModel);

	QObject::connect(ui->ingredientsListView->selectionModel(),
			SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
			this,
			SLOT(onIngredientsListViewSelectionChanged(QItemSelection)));
	QObject::connect(ui->tagsListView->selectionModel(),
			SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
			this,
			SLOT(onTagsListViewSelectionChanged(QItemSelection)));
}

OpenRecipeDialog::OpenRecipeDialog(RecipeDatabase *recipeDB, QWidget *parent) : OpenRecipeDialog(parent){
	this->recipeDB = recipeDB;
	this->populateIngredientsList();
	this->populateTagsList();
	this->populateFoodGroupsList();
	this->populateRecipesTable(this->recipeDB->retrieveAllRecipes());
}

OpenRecipeDialog::~OpenRecipeDialog()
{
	delete ui;
}

Recipe OpenRecipeDialog::getSelectedRecipe(){
	return this->selectedRecipe;
}

void OpenRecipeDialog::populateRecipesTable(vector<Recipe> recipes){
	this->recipeTableModel.clear();
	this->recipeTableModel.setRecipes(recipes);
	ui->recipeTableView->resizeColumnsToContents();
	ui->recipeTableView->show();
}

void OpenRecipeDialog::populateIngredientsList(){
	this->ingredientsModel.setIngredients(this->recipeDB->retrieveAllIngredients());
}

void OpenRecipeDialog::populateTagsList(){
	this->tagsModel.setTags(this->recipeDB->retrieveAllTags());
}

void OpenRecipeDialog::populateFoodGroupsList(){
	for (string s : this->recipeDB->retrieveAllFoodGroups()){
		ui->foodGroupsListWidget->addItem(QString::fromStdString(s));
	}
	//ui->foodGroupsListWidget->show();
}

void OpenRecipeDialog::on_deleteRecipeButton_clicked(){
	QItemSelectionModel *selectModel = ui->recipeTableView->selectionModel();
	if (!selectModel->hasSelection()){
		return;
	}
	vector<int> rows;
	QModelIndexList indexes = selectModel->selectedRows();
	for (int i = 0; i < indexes.count(); i++){
		rows.push_back(indexes.at(i).row());
	}
	string recipePlural = (rows.size() == 1) ? "recipe" : "recipes";
	QString title = QString::fromStdString("Delete " + recipePlural);
	QString content = QString::fromStdString("Are you sure you wish to delete the selected "+recipePlural+"?");
	QMessageBox::StandardButton reply = QMessageBox::question(this, title, content);
	if (reply == QMessageBox::Yes){
		for (int row : rows){
			Recipe r = this->recipeTableModel.getRecipeAt(row);
			bool success = this->recipeDB->deleteRecipe(r.getName());
			if (!success){
				QMessageBox::critical(this, QString::fromStdString("Unable to Delete"), QString::fromStdString("Could not delete recipe "+r.getName()));
			} else {
				this->populateRecipesTable(this->recipeDB->retrieveAllRecipes());
			}
		}
	}
}

void OpenRecipeDialog::on_recipeTableView_doubleClicked(const QModelIndex &index){
	this->selectedRecipe = this->recipeTableModel.getRecipeAt(index.row());
	this->close();
}

void OpenRecipeDialog::onIngredientsListViewSelectionChanged(const QItemSelection &selection){
	Q_UNUSED(selection);
	vector<Ingredient> ingredients;
	QModelIndexList indexes = ui->ingredientsListView->selectionModel()->selectedRows();
	for (QModelIndex index : indexes){
		Ingredient i = this->ingredientsModel.getIngredients().at(index.row());
		ingredients.push_back(i);
	}
	this->populateRecipesTable(this->recipeDB->retrieveRecipesWithIngredients(ingredients));
}

void OpenRecipeDialog::onTagsListViewSelectionChanged(const QItemSelection &selection){
	Q_UNUSED(selection);
	vector<RecipeTag> tags;
	QModelIndexList indexes = ui->tagsListView->selectionModel()->selectedRows();
	for (QModelIndex index : indexes){
		RecipeTag t = this->tagsModel.getTags().at(index.row());
		tags.push_back(t);
	}
	this->populateRecipesTable(this->recipeDB->retrieveRecipesWithTags(tags));
}

void OpenRecipeDialog::on_nameEdit_textChanged(const QString &arg1){
	Q_UNUSED(arg1);
	this->populateRecipesTable(this->recipeDB->retrieveRecipesWithSubstring(ui->nameEdit->text().toStdString()));
}

void OpenRecipeDialog::on_foodGroupsListWidget_itemSelectionChanged(){
	vector<string> groups;
	for (QModelIndex index : ui->foodGroupsListWidget->selectionModel()->selectedRows()){
		QListWidgetItem *item = ui->foodGroupsListWidget->item(index.row());
		groups.push_back(item->text().toStdString());
	}
	this->populateRecipesTable(this->recipeDB->retrieveRecipesWithFoodGroups(groups));
}
