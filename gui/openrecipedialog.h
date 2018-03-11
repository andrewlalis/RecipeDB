#ifndef OPENRECIPEDIALOG_H
#define OPENRECIPEDIALOG_H

#include <QDialog>

#include "model/database/recipedatabase.h"
#include "model/recipe/recipetablemodel.h"

namespace Ui {
class OpenRecipeDialog;
}

class OpenRecipeDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit OpenRecipeDialog(QWidget *parent = 0);
		OpenRecipeDialog(RecipeDatabase *recipeDB, QWidget *parent = 0);
		~OpenRecipeDialog();

	private:
		Ui::OpenRecipeDialog *ui;
		RecipeDatabase *recipeDB;
		RecipeTableModel recipeTableModel;

		void populateRecipesTable();
};

#endif // OPENRECIPEDIALOG_H
