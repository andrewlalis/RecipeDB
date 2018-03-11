#ifndef NEWUNITDIALOG_H
#define NEWUNITDIALOG_H

#include <QDialog>

#include "model/recipe/ingredients/unitofmeasure.h"

namespace Ui {
class NewUnitDialog;
}

class NewUnitDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit NewUnitDialog(QWidget *parent = 0);
		~NewUnitDialog();

		UnitOfMeasure getUnit();
	private:
		Ui::NewUnitDialog *ui;

		int getSelectedType();
};

#endif // NEWUNITDIALOG_H
