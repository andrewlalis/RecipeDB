#ifndef NEWTAGDIALOG_H
#define NEWTAGDIALOG_H

#include <QDialog>

#include "model/recipe/tags/recipetag.h"

namespace Ui {
class newTagDialog;
}

class NewTagDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit NewTagDialog(QWidget *parent = 0);
		~NewTagDialog();

		//Access values
		RecipeTag getTag();
	private:
		Ui::newTagDialog *ui;
};

#endif // NEWTAGDIALOG_H
