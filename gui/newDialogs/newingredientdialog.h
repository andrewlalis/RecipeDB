#ifndef NEWINGREDIENTDIALOG_H
#define NEWINGREDIENTDIALOG_H

#include <QDialog>
#include "model/recipe/ingredients/ingredient.h"
#include "model/database/recipedatabase.h"

namespace Ui {
class NewIngredientDialog;
}

class NewIngredientDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit NewIngredientDialog(QWidget *parent = 0);
		NewIngredientDialog(RecipeDatabase *recipeDB, QWidget *parent = 0);
		~NewIngredientDialog();

		//Access values.
		Ingredient getIngredient();

	private:
		Ui::NewIngredientDialog *ui;
		RecipeDatabase *recipeDB;

		void populateFoodGroupBox();
};

#endif // NEWINGREDIENTDIALOG_H
