#ifndef NEWRECIPEDIALOG_H
#define NEWRECIPEDIALOG_H

#include <QDialog>
#include <QTextCharFormat>

#include "model/database/recipedatabase.h"
#include "model/recipe/ingredients/ingredientlistmodel.h"
#include "model/recipe/tags/taglistmodel.h"

namespace Ui {
class NewRecipeDialog;
}

class NewRecipeDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit NewRecipeDialog(QWidget *parent = 0);
		NewRecipeDialog(RecipeDatabase *db, QWidget *parent = 0);
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

	private:
		Ui::NewRecipeDialog *ui;
		RecipeDatabase *recipeDB;
		vector<Ingredient> ingredients;
		vector<UnitOfMeasure> units;
		vector<RecipeTag> tags;
		IngredientListModel ingredientListModel;
		TagListModel tagsListModel;
		bool accepted = false;

		//Helper functions to fill fields.
		void populateIngredientsBox();
		void populateUnitsBox();
		void populateTagsBox();
};

#endif // NEWRECIPEDIALOG_H
