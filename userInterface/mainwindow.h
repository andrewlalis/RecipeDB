#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QAbstractListModel>

#include "model/recipe/recipe.h"
#include "model/recipe/ingredients/ingredientlistmodel.h"

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
    IngredientListModel ingredientModel;

    //Hidden manipulation methods.
    void setRecipeName(string name);
    void setInstruction(Instruction instruction);
    void setIngredients(vector<RecipeIngredient> ingredients);
};

#endif // MAINWINDOW_H
