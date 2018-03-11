#ifndef OPENRECIPEDIALOG_H
#define OPENRECIPEDIALOG_H

#include <QDialog>

namespace Ui {
class OpenRecipeDialog;
}

class OpenRecipeDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit OpenRecipeDialog(QWidget *parent = 0);
		~OpenRecipeDialog();

	private:
		Ui::OpenRecipeDialog *ui;
};

#endif // OPENRECIPEDIALOG_H
