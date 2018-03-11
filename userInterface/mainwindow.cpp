#include "userInterface/mainwindow.h"
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
    setRecipeName(recipe.getName());
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
}

void MainWindow::setRecipeName(string name){
    ui->recipeNameLabel->setText(QString::fromStdString(name));
}

void MainWindow::setInstruction(Instruction instruction){
    ui->instructionsTextEdit->setHtml(QString::fromStdString(instruction.getHTML()));
}

void MainWindow::setIngredients(vector<RecipeIngredient> ingredients){
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
	ui->servingsLabel->setText(QString("Servings: ")+QString::fromStdString(StringUtils::toString(servings)));
}

void MainWindow::setTags(vector<RecipeTag> tags){
	this->tagsListModel.setTags(tags);
}

void MainWindow::on_newButton_clicked(){
	NewRecipeDialog d(this->recipeDB, this);
	d.show();
	d.exec();
	if (d.isAccepted()){
		Recipe r = d.getRecipe();
		if (!this->recipeDB->storeRecipe(r)){
			QMessageBox::critical(this, QString("Unable to Save Recipe"), QString("The program was not able to successfully save the recipe."));
		}
		this->loadFromRecipe(r);
	}
}
