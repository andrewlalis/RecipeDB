#include "userInterface/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::loadFromRecipe(Recipe recipe){
    setRecipeName(recipe.getName());
    setInstructions(recipe.getInstructions());
    setIngredients(recipe.getIngredients());
}

void MainWindow::setRecipeName(string name){
    ui->recipeNameLabel->setText(QString::fromStdString(name));
}

void MainWindow::setInstructions(vector<Instruction> instructions){

}

void MainWindow::setIngredients(vector<Ingredient> ingredients){

}
