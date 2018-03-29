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

void OpenRecipeDialog::populateRecipesTable(){
	vector<Recipe> recipes = this->recipeDB->retrieveAllRecipes();
	printf("Found %d recipes:\n", recipes.size());
	for (Recipe r : recipes){
		r.print();
		printf("\n------------------\n");
	}
	this->recipeTableModel.setRecipes(recipes);
	ui->recipeTableView->show();
}
