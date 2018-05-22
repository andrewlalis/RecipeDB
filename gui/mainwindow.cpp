#include "gui/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

	ui->ingredientsListView->setModel(&this->ingredientModel);
	ui->tagsListView->setModel(&this->tagsListModel);
}

MainWindow::MainWindow(RecipeDatabase *db, QWidget *parent) : MainWindow(parent){
	this->recipeDB = db;
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::loadFromRecipe(Recipe recipe){
	if (recipe.isEmpty()){
		setRecipeName("No recipes found.");
		setAuthorName("Click 'New' to get started.");
	} else {
		setRecipeName(recipe.getName());
		setAuthorName(recipe.getAuthor());
		setInstruction(recipe.getInstruction());
		setIngredients(recipe.getIngredients());
		if (recipe.getImage().isNull()){
			setImage(QImage(QString(":/images/images/no_image.png")));
		} else {
			setImage(recipe.getImage());
		}
		setPrepTime(recipe.getPrepTime());
		setCookTime(recipe.getCookTime());
		setServings(recipe.getServings());
		setTags(recipe.getTags());
		this->currentRecipe = recipe;
	}
}

void MainWindow::setRecipeName(string name){
    ui->recipeNameLabel->setText(QString::fromStdString(name));
}

void MainWindow::setInstruction(Instruction instruction){
    ui->instructionsTextEdit->setHtml(QString::fromStdString(instruction.getHTML()));
}

void MainWindow::setIngredients(vector<Ingredient> ingredients){
	this->ingredientModel.setIngredients(ingredients);
}

void MainWindow::setImage(QImage img){
	ui->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::setPrepTime(QTime prepTime){
	ui->prepTimeLabel->setText(QString("Prep Time: ")+prepTime.toString("hh:mm:ss"));
}

void MainWindow::setCookTime(QTime cookTime){
	ui->cookTimeLabel->setText(QString("Cook Time: ")+cookTime.toString("hh:mm:ss"));
}

void MainWindow::setServings(float servings){
	ui->servingsLabel->setText(QString(QString::fromStdString(StringUtils::toString(servings) + " Serving" + ((servings != 1.0f) ? "s" : ""))));
}

void MainWindow::setTags(vector<RecipeTag> tags){
	this->tagsListModel.setTags(tags);
}

void MainWindow::setAuthorName(string name){
	if (name.empty()){
		ui->authorLabel->setText("");
	} else {
		ui->authorLabel->setText(QString::fromStdString("By "+name));
	}
}

void MainWindow::on_newButton_clicked(){
	NewRecipeDialog d(this->recipeDB, this);
	d.show();
	d.exec();
	if (d.isAccepted()){
		Recipe r = d.getRecipe();
		if (!this->recipeDB->storeRecipe(r)){
			QMessageBox::critical(this, QString("Unable to Save Recipe"), QString("The program was not able to successfully save the recipe. Make sure to give the recipe a name, instructions, and some ingredients!"));
		} else {
			this->loadFromRecipe(r);
		}
	}
}

void MainWindow::on_openButton_clicked(){
	OpenRecipeDialog d(this->recipeDB, this);
	d.show();
	d.exec();
	if (!d.getSelectedRecipe().isEmpty()){
		this->loadFromRecipe(d.getSelectedRecipe());
	}
}

void MainWindow::on_exitButton_clicked(){
	this->close();
}

void MainWindow::on_editButton_clicked(){
	NewRecipeDialog d(this->recipeDB, this->currentRecipe, this);
	string originalName = this->currentRecipe.getName();
	d.show();
	d.exec();
	if (d.isAccepted()){
		Recipe r = d.getRecipe();
		if (!this->recipeDB->updateRecipe(r, originalName)){
			QMessageBox::critical(this, QString("Unable to Save Recipe"), QString("The program was not able to successfully save the recipe. Make sure to give the recipe a name, instructions, and some ingredients!"));
		} else {
			this->loadFromRecipe(r);
		}
	}
}
