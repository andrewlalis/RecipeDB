#ifndef NEWRECIPEDIALOG_H
#define NEWRECIPEDIALOG_H

#include <QDialog>
#include <QTextCharFormat>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>

#include "model/database/recipedatabase.h"
#include "model/recipe/ingredients/recipeingredientlistmodel.h"
#include "model/recipe/tags/taglistmodel.h"

#include "gui/newDialogs/newingredientdialog.h"
#include "gui/newDialogs/newtagdialog.h"
#include "gui/newDialogs/newunitdialog.h"

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

		Recipe getRecipe();
		bool isAccepted() const;
	private slots:
		void on_addIngredientButton_clicked();

		void on_italicsButton_clicked();

		void on_boldButton_clicked();

		void on_buttonBox_accepted();

		void on_buttonBox_rejected();

		void on_addTagButton_clicked();

		void on_deleteTagButton_clicked();

		void on_selectImageButton_clicked();

		void on_removeIngredientButton_clicked();

		void on_deleteIngredientButton_clicked();

		void on_newIngredientButton_clicked();

		void on_newTagButton_clicked();

		void on_removeTagButton_clicked();

		void on_newUnitButton_clicked();

		void on_deleteUnitButton_clicked();

	private:
		Ui::NewRecipeDialog *ui;
		RecipeDatabase *recipeDB;
		vector<Ingredient> ingredients;
		vector<UnitOfMeasure> units;
		vector<RecipeTag> tags;
		RecipeIngredientListModel ingredientListModel;
		TagListModel tagsListModel;
		bool accepted = false;

		//Helper functions to fill fields.
		void populateIngredientsBox();
		void populateUnitsBox();
		void populateTagsBox();
};

#endif // NEWRECIPEDIALOG_H
