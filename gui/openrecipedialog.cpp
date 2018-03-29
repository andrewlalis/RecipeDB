#include "openrecipedialog.h"
#include "ui_openrecipedialog.h"

OpenRecipeDialog::OpenRecipeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OpenRecipeDialog)
{
	ui->setupUi(this);

	ui->recipeTableView->setModel(&this->recipeTableModel);
}

OpenRecipeDialog::OpenRecipeDialog(RecipeDatabase *recipeDB, QWidget *parent) : OpenRecipeDialog(parent){
	this->recipeDB = recipeDB;
	this->populateRecipesTable();
}

OpenRecipeDialog::~OpenRecipeDialog()
{
	delete ui;
}

Recipe OpenRecipeDialog::getSelectedRecipe(){
	return this->selectedRecipe;
}

void OpenRecipeDialog::populateRecipesTable(){
	this->recipeTableModel.clear();
	vector<Recipe> recipes = this->recipeDB->retrieveAllRecipes();
	this->recipeTableModel.setRecipes(recipes);
	ui->recipeTableView->resizeColumnsToContents();
	ui->recipeTableView->show();
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
			}
		}
		this->populateRecipesTable();
	}
}

void OpenRecipeDialog::on_recipeTableView_doubleClicked(const QModelIndex &index){
	this->selectedRecipe = this->recipeTableModel.getRecipeAt(index.row());
	this->close();
}
