#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QAbstractListModel>

#include "model/recipe/recipe.h"
#include "model/recipe/ingredients/recipeingredientlistmodel.h"
#include "gui/newrecipedialog.h"
#include "gui/openrecipedialog.h"
#include "utils/stringutils.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	MainWindow(RecipeDatabase *db, QWidget *parent = 0);
    ~MainWindow();

    //Loads all data from a recipe into the GUI components.
    void loadFromRecipe(Recipe recipe);

	private slots:
	void on_newButton_clicked();

	void on_openButton_clicked();

	void on_exitButton_clicked();

	private:
    Ui::MainWindow *ui;
	RecipeDatabase *recipeDB;
	RecipeIngredientListModel ingredientModel;
	TagListModel tagsListModel;

    //Hidden manipulation methods.
    void setRecipeName(string name);
    void setInstruction(Instruction instruction);
    void setIngredients(vector<RecipeIngredient> ingredients);
	void setImage(QImage img);
	void setPrepTime(QTime prepTime);
	void setCookTime(QTime cookTime);
	void setServings(float servings);
	void setTags(vector<RecipeTag> tags);
};

#endif // MAINWINDOW_H
