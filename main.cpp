#include "gui/mainwindow.h"
#include "gui/newrecipedialog.h"

#include <QApplication>
#include <QFontDatabase>

#include "model/database/database.h"
#include "model/database/recipedatabase.h"
#include "utils/fileutils.h"

Recipe checkForFirstRun(RecipeDatabase *recipeDB){
	Recipe r = recipeDB->retrieveRandomRecipe();
	if (r.isEmpty()){//There are no recipes in the database.
		//Add some basic units to the units, and some basic ingredients.

	}
	return r;
}

void loadAndSetFonts(){
	int id = QFontDatabase::addApplicationFont(":/fonts/fonts/NotoSans-Light.ttf");
	if (id == -1){
		return;
	}
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
}

int main(int argc, char *argv[])
{
	RecipeDatabase recipeDB(QString(FileUtils::appDataPath+"recipes.db").toStdString());

	QApplication a(argc, argv);

	loadAndSetFonts();
	QFont notoFont("Noto Sans");
	notoFont.setStyleHint(QFont::SansSerif);
	notoFont.setWeight(QFont::Thin);
	a.setFont(notoFont);

	MainWindow w(&recipeDB);
	w.loadFromRecipe(checkForFirstRun(&recipeDB));
	w.show();

	a.exec();
	recipeDB.closeConnection();

	return 0;
}
