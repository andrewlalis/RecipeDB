#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

#include "model/recipe/recipe.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Loads all data from a recipe into the GUI components.
    void loadFromRecipe(Recipe recipe);
private:
    Ui::MainWindow *ui;

    //Hidden manipulation methods.
    void setRecipeName(string name);
    void setInstructions(vector<Instruction> instructions);
    void setIngredients(vector<Ingredient> ingredients);
};

#endif // MAINWINDOW_H
