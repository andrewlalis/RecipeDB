#include "userInterface/mainwindow.h"
#include <QApplication>

#include "model/database/database.h"
#include "model/database/recipedatabase.h"
#include "utils/fileutils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	//TESTING CODE
//	Database db("test.db");
//	printf("Table exists: %d\n", db.tableExists("ingredients"));
//	db.executeSQL("SELECT * FROM ingredients;").printData();
//	db.executeSQL("PRAGMA table_info('ingredients');").printData();
//	db.executeSQL("SELECT name FROM ingredients WHERE foodGroup == 'fruit';").printData();

	RecipeDatabase recipeDB("recipes");
	recipeDB.storeIngredient(Ingredient("Apple", "Fruit"));
	recipeDB.storeIngredient(Ingredient("Corn", "Vegetable"));
	recipeDB.executeSQL("SELECT * FROM ingredient;").printData();

	FileUtils::saveInstruction(1, Instruction("This is some plain text with no HTML markup."));

	return a.exec();
}
