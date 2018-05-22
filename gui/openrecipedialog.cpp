#include "openrecipedialog.h"
#include "ui_openrecipedialog.h"

OpenRecipeDialog::OpenRecipeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OpenRecipeDialog)
{
	ui->setupUi(this);

	ui->recipeTableView->setModel(&this->recipeTableModel);
	ui->tagsListView->setModel(&this->tagsModel);

	QObject::connect(ui->tagsListView->selectionModel(),
			SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
			this,
			SLOT(onTagsListViewSelectionChanged(QItemSelection)));
}

OpenRecipeDialog::OpenRecipeDialog(RecipeDatabase *recipeDB, QWidget *parent) : OpenRecipeDialog(parent){
	this->recipeDB = recipeDB;
	this->populateTagsList();
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

void OpenRecipeDialog::populateTagsList(){
	this->tagsModel.setTags(this->recipeDB->retrieveAllTags());
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
	QString content = QString::fromStdString("Are you sure you wish to delete the selected "+recipePlural+"?\nAll deleted recipes are permanently deleted.");
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

void OpenRecipeDialog::on_clearSearchButton_clicked(){
	ui->nameEdit->clear();
	ui->tagsListView->selectionModel()->clearSelection();
	this->populateRecipesTable(this->recipeDB->retrieveAllRecipes());
}

void OpenRecipeDialog::on_exitButton_clicked(){
	this->close();
}
