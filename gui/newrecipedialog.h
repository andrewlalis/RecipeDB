#ifndef NEWRECIPEDIALOG_H
#define NEWRECIPEDIALOG_H

#include <QDialog>
#include <QTextCharFormat>

#include "model/database/recipedatabase.h"

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

	private slots:
		void on_toolButton_clicked();

	private:
		Ui::NewRecipeDialog *ui;
		RecipeDatabase *recipeDB;
		vector<Ingredient> ingredients;
		vector<UnitOfMeasure> units;

		//Helper functions to fill fields.
		void populateIngredientsBox();
		void populateUnitsBox();
};

#endif // NEWRECIPEDIALOG_H
