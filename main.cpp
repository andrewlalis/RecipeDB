#include "userInterface/mainwindow.h"
#include <QApplication>

#include "model/database/database.h"
#include "model/database/recipedatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	//TESTING CODE

	RecipeDatabase recipeDB("recipes");

	//TESTING CODE
//	vector<RecipeIngredient> ri;
//	ri.push_back(RecipeIngredient("flour", "grains", 3.0f, UnitOfMeasure("cup", "cups", "c")));
//	ri.push_back(RecipeIngredient("Baking Powder", "Additives", 1.0f, UnitOfMeasure("Teaspoon", "Teaspoons", "Tsp")));

//	Recipe rec("Example", ri, Instruction("<b>BOLD</b><i>iTaLiCs</i>"), QImage(), vector<RecipeTag>(), QDate::currentDate(), QTime(0, 30), QTime(0, 25), 10.0f);

//	bool success = recipeDB.storeRecipe(rec);
//	printf("Storage successful: %d\n", success);

	Recipe reloadRec = recipeDB.retrieveRecipe("Example");
	reloadRec.print();

	w.loadFromRecipe(reloadRec);

	return a.exec();
}
