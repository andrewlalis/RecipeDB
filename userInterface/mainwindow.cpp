#include "userInterface/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    //TESTING CODE
    vector<RecipeIngredient> ri;
    ri.push_back(RecipeIngredient("flour", "grains", 3.0f, UnitOfMeasure("cup", "cups", "c")));

    Recipe rec("Example", ri, Instruction("<b>BOLD</b><i>iTaLiCs</i>"), QImage(), vector<RecipeTag>(), QDate::currentDate(), QTime(0, 30), QTime(0, 25), 10.0f);

    this->loadFromRecipe(rec);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::loadFromRecipe(Recipe recipe){
    setRecipeName(recipe.getName());
    setInstruction(recipe.getInstruction());
    setIngredients(recipe.getIngredients());
}

void MainWindow::setRecipeName(string name){
    ui->recipeNameLabel->setText(QString::fromStdString(name));
}

void MainWindow::setInstruction(Instruction instruction){
    ui->instructionsTextEdit->setHtml(QString::fromStdString(instruction.getHTML()));
}

void MainWindow::setIngredients(vector<RecipeIngredient> ingredients){
    ///TODO: Implement this.
}
