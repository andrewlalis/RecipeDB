#include "gui/mainwindow.h"
#include "gui/newrecipedialog.h"

#include <QApplication>
#include <QFontDatabase>

#include "model/database/database.h"
#include "model/database/recipedatabase.h"
#include "utils/fileutils.h"

void test(RecipeDatabase *recipeDB){
	vector<RecipeIngredient> ri;
	ri.push_back(RecipeIngredient("flour", "grains", 3.0f, UnitOfMeasure("cup", "cups", "c", UnitOfMeasure::VOLUME, 1.0), ""));
	ri.push_back(RecipeIngredient("baking powder", "additives", 1.0f, UnitOfMeasure("teaspoon", "teaspoons", "tsp", UnitOfMeasure::VOLUME, 1.0), ""));

	Recipe rec("Example",
			   "Andrew Lalis",
			   ri,
			   Instruction("Placeholder Text"),
			   QImage(),
			   vector<RecipeTag>({RecipeTag("testing"),
								  RecipeTag("fake")}),
			   QDate::currentDate(),
			   QTime(0, 30),
			   QTime(0, 25),
			   10.0f);

	bool success = recipeDB->storeRecipe(rec);
	printf("Storage successful: %d\n", success);

}

Recipe checkForFirstRun(RecipeDatabase *recipeDB){
	Recipe r = recipeDB->retrieveRandomRecipe();
	if (r.isEmpty()){//There are no recipes in the database.
		//Add some basic units to the units, and some basic ingredients.
		recipeDB->addBasicUnits();
		recipeDB->addBasicIngredients();
	}
	return r;
}

void loadAndSetFonts(){
	QFontDatabase::
}

int main(int argc, char *argv[])
{
	RecipeDatabase recipeDB(QString(FileUtils::appDataPath+"recipes.db").toStdString());

	QApplication a(argc, argv);
	MainWindow w(&recipeDB);
	w.loadFromRecipe(checkForFirstRun(&recipeDB));
	w.show();

	a.exec();
	recipeDB.closeConnection();

	return 0;
}
