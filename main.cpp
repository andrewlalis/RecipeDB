#include "userInterface/mainwindow.h"
#include "gui/newrecipedialog.h"
#include <QApplication>

#include "model/database/database.h"
#include "model/database/recipedatabase.h"

int main(int argc, char *argv[])
{
	RecipeDatabase recipeDB("recipes");
    QApplication a(argc, argv);
	MainWindow w(&recipeDB);
    w.show();

	//TESTING CODE
//	vector<RecipeIngredient> ri;
//	ri.push_back(RecipeIngredient("flour", "grains", 3.0f, UnitOfMeasure("cup", "cups", "c", UnitOfMeasure::VOLUME, 1.0), ""));
//	ri.push_back(RecipeIngredient("baking powder", "additives", 1.0f, UnitOfMeasure("teaspoon", "teaspoons", "tsp", UnitOfMeasure::VOLUME, 1.0), ""));

//	Recipe rec("Example",
//			   ri,
//			   Instruction("<b>BOLD</b><i>iTaLiCs</i>"),
//			   QImage(),
//			   vector<RecipeTag>({RecipeTag("testing"),
//								  RecipeTag("fake")}),
//			   QDate::currentDate(),
//			   QTime(0, 30),
//			   QTime(0, 25),
//			   10.0f);

//	bool success = recipeDB.storeRecipe(rec);
//	printf("Storage successful: %d\n", success);

//	recipeDB.storeUnitOfMeasure(UnitOfMeasure("tablespoon", "tablespoons", "tbsp", UnitOfMeasure::VOLUME, 1.0));
//	recipeDB.storeUnitOfMeasure(UnitOfMeasure("pinch", "pinches", "pch", UnitOfMeasure::VOLUME, 1.0));
//	recipeDB.storeUnitOfMeasure(UnitOfMeasure("gram", "grams", "g", UnitOfMeasure::MASS, 1.0));

//	Recipe reloadRec = recipeDB.retrieveRecipe("Example");
//	reloadRec.print();

//	w.loadFromRecipe(reloadRec);

//	NewRecipeDialog d(&recipeDB);
//	d.show();
//	d.exec();

//	if (d.isAccepted()){
//		printf("Accepted the dialog.\n");
//	}

	return a.exec();
}
