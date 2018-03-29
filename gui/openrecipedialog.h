#ifndef OPENRECIPEDIALOG_H
#define OPENRECIPEDIALOG_H

#include <QDialog>
#include <QMessageBox>

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

		Recipe getSelectedRecipe();

	private slots:
		void on_deleteRecipeButton_clicked();

		void on_recipeTableView_doubleClicked(const QModelIndex &index);

	private:
		Ui::OpenRecipeDialog *ui;
		RecipeDatabase *recipeDB;
		RecipeTableModel recipeTableModel;
		Recipe selectedRecipe;

		void populateRecipesTable();
};

#endif // OPENRECIPEDIALOG_H
