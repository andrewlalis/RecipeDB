#ifndef NEWINGREDIENTDIALOG_H
#define NEWINGREDIENTDIALOG_H

#include <QDialog>
#include "model/recipe/ingredients/ingredient.h"

namespace Ui {
class NewIngredientDialog;
}

class NewIngredientDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit NewIngredientDialog(QWidget *parent = 0);
		~NewIngredientDialog();

		//Access values.
		Ingredient getIngredient();

	private:
		Ui::NewIngredientDialog *ui;
};

#endif // NEWINGREDIENTDIALOG_H
