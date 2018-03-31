#include "gui/mainwindow.h"
#include "gui/newrecipedialog.h"
#include <QApplication>

#include "model/database/database.h"
#include "model/database/recipedatabase.h"
#include "utils/fileutils.h"

void test(RecipeDatabase *recipeDB);

int main(int argc, char *argv[])
{
	RecipeDatabase recipeDB(QString(FileUtils::appDataPath+"recipes.db").toStdString());
    QApplication a(argc, argv);
	MainWindow w(&recipeDB);
    w.show();

	//TESTING CODE
	//test(&recipeDB);

	//END TESTING CODE.

	w.loadFromRecipe(recipeDB.retrieveRandomRecipe());

	a.exec();
	recipeDB.closeConnection();

	return 0;
}

void test(RecipeDatabase *recipeDB){
	vector<RecipeIngredient> ri;
	ri.push_back(RecipeIngredient("flour", "grains", 3.0f, UnitOfMeasure("cup", "cups", "c", UnitOfMeasure::VOLUME, 1.0), ""));
	ri.push_back(RecipeIngredient("baking powder", "additives", 1.0f, UnitOfMeasure("teaspoon", "teaspoons", "tsp", UnitOfMeasure::VOLUME, 1.0), ""));

	Recipe rec("Example",
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
