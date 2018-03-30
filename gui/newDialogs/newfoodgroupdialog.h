#ifndef NEWFOODGROUPDIALOG_H
#define NEWFOODGROUPDIALOG_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class newFoodGroupDialog;
}

class newFoodGroupDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit newFoodGroupDialog(QWidget *parent = 0);
		~newFoodGroupDialog();

		string getFoodGroup() const;

	private:
		Ui::newFoodGroupDialog *ui;
};

#endif // NEWFOODGROUPDIALOG_H
