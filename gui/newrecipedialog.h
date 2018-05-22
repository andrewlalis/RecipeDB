#ifndef NEWRECIPEDIALOG_H
#define NEWRECIPEDIALOG_H

#include <QDialog>
#include <QTextCharFormat>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>

#include "model/database/recipedatabase.h"
#include "model/recipe/ingredients/ingredientlistmodel.h"
#include "model/recipe/tags/taglistmodel.h"

#include "gui/newDialogs/newtagdialog.h"

namespace Ui {
class NewRecipeDialog;
}

class NewRecipeDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit NewRecipeDialog(QWidget *parent = 0);
		NewRecipeDialog(RecipeDatabase *db, QWidget *parent = 0);
		NewRecipeDialog(RecipeDatabase *db, Recipe recipe, QWidget *parent = 0);
		~NewRecipeDialog();

		//Extracts a recipe from all the information entered in the ui.
		Recipe getRecipe();
		bool isAccepted() const;
	private slots:
		void on_addIngredientButton_clicked();

		void on_italicsButton_clicked();

		void on_boldButton_clicked();

		//Sets the dialog as accepted, as in, the user accepts that they want to create the recipe.
		void on_buttonBox_accepted();

		//The user has rejected the creation of the recipe.
		void on_buttonBox_rejected();

		void on_addTagButton_clicked();

		void on_deleteTagButton_clicked();

		void on_selectImageButton_clicked();

		void on_removeIngredientButton_clicked();

		void on_newTagButton_clicked();

		void on_removeTagButton_clicked();

	private:
		Ui::NewRecipeDialog *ui;
		RecipeDatabase *recipeDB;
		vector<Ingredient> ingredients;
		vector<RecipeTag> tags;
		IngredientListModel ingredientListModel;
		TagListModel tagsListModel;
		bool accepted = false;

		//Helper functions to fill fields.
		void populateTagsBox();
};

#endif // NEWRECIPEDIALOG_H
