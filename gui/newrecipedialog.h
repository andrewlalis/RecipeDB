#ifndef NEWRECIPEDIALOG_H
#define NEWRECIPEDIALOG_H

#include <QDialog>

namespace Ui {
class NewRecipeDialog;
}

class NewRecipeDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit NewRecipeDialog(QWidget *parent = 0);
		~NewRecipeDialog();

	private:
		Ui::NewRecipeDialog *ui;
};

#endif // NEWRECIPEDIALOG_H
