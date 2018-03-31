#include "recipedatabase.h"

RecipeDatabase::RecipeDatabase(string filename) : Database(filename){
	this->ensureTablesExist();
}

bool RecipeDatabase::storeRecipe(Recipe recipe){
	//Some primary checks to avoid garbage in the database.
	if (recipe.getName().empty() ||
			recipe.getInstruction().getHTML().empty() ||
			recipe.getIngredients().empty()){
		return false;
	}
	//Store a recipe, if it doesn't already exist. This first tries to create the recipe entry, then all subsequent supporting table entries.
	this->executeSQL("BEGIN;");
	ResultTable t = this->selectFrom("recipe", "*", "WHERE name="+surroundString(recipe.getName(), "'"));
	if (!t.isEmpty()){
		fprintf(stderr, "Error storing recipe: Recipe with name %s already exists.\n", recipe.getName().c_str());
	} else {
		bool success = this->insertInto("recipe",
						 vector<string>({
											"name",
											"createdDate",
											"cookTime",
											"prepTime",
											"servingCount"
										}),
						 vector<string>({
											recipe.getName(),
											recipe.getCreatedDate().toString().toStdString(),
											recipe.getCookTime().toString().toStdString(),
											recipe.getPrepTime().toString().toStdString(),
											std::to_string(recipe.getServings())
										}));
		if (success){
			//If successful, proceed to insert instructions, image, and ingredients, and tags.
			int recipeId = this->getLastInsertedRowId();
			bool ingredientSuccess = true;
			for (unsigned int i = 0; i < recipe.getIngredients().size(); i++){
				if (!this->storeRecipeIngredient(recipe.getIngredients()[i], recipeId)){
					ingredientSuccess = false;
					break;
				}
			}
			if (ingredientSuccess &&
					this->storeInstruction(recipe.getInstruction(), recipeId) &&
					this->storeImage(recipe.getImage(), recipeId) &&
					this->storeTags(recipe.getTags(), recipeId)){
				this->executeSQL("COMMIT;");
				return true;
			}
		}
	}
	this->executeSQL("ROLLBACK;");
	return false;
}

bool RecipeDatabase::storeRecipeIngredient(RecipeIngredient ri, int recipeId){
	int ingId = this->storeIngredient(ri);
	if (ingId < 0) return false;

	if (!this->storeUnitOfMeasure(ri.getUnit())) return false;

	return this->insertInto("recipeIngredient",
					 vector<string>({
										"ingredientId",
										"recipeId",
										"quantity",
										"unitName",
										"comment"
									}),
					 vector<string>({
										std::to_string(ingId),
										std::to_string(recipeId),
										std::to_string(ri.getQuantity()),
										ri.getUnit().getName(),
										ri.getComment()
									}));
}

int RecipeDatabase::storeIngredient(Ingredient ingredient){
	ResultTable t = this->selectFrom("ingredient", "*", "WHERE name="+surroundString(ingredient.getName(), "'"));
	if (t.isEmpty()){
		bool success = this->insertInto("ingredient", vector<string>({"foodGroup", "name"}), vector<string>({ingredient.getFoodGroup(), ingredient.getName()}));
		if (success){
			return this->getLastInsertedRowId();
		} else {
			return -1;
		}
	} else {
		return std::stoi(t.at(0, 0));
	}
}

bool RecipeDatabase::storeUnitOfMeasure(UnitOfMeasure u){
	ResultTable t = this->selectFrom("unitOfMeasure", "name", "WHERE name="+surroundString(u.getName(), "'"));
	if (!t.isEmpty()){
		return true;
	}
	bool success = this->insertInto("unitOfMeasure",
									vector<string>({
													   "name",
													   "plural",
													   "abbreviation",
													   "type",
													   "metricCoefficient"
												   }),
									vector<string>({
													   u.getName(),
													   u.getNamePlural(),
													   u.getAbbreviation(),
													   std::to_string(u.getType()),
													   std::to_string(u.getMetricCoefficient())
												   }));
	return success;
}

bool RecipeDatabase::storeInstruction(Instruction instruction, int recipeId){
	return FileUtils::saveInstruction(recipeId, instruction);
}

bool RecipeDatabase::storeImage(QImage image, int recipeId){
	return FileUtils::saveImage(recipeId, image);
}

bool RecipeDatabase::storeTags(vector<RecipeTag> tags, int recipeId){
	for (vector<RecipeTag>::iterator it = tags.begin(); it != tags.end(); ++it){
		bool s = this->insertInto("recipeTag",
								  vector<string>({
													 "recipeId",
													 "tagName"
												 }),
								  vector<string>({
													 std::to_string(recipeId),
													 (*it).getValue()
												 }));
		if (!s){
			return false;
		}
	}
	return true;
}

Recipe RecipeDatabase::retrieveRecipe(string name){
	ResultTable t = this->selectFrom("recipe", "*", "WHERE name="+surroundString(name, "'"));
	if (t.isEmpty()){
		fprintf(stderr, "Error: No recipe with name %s found!\n", name.c_str());
		return Recipe();
	}
	return this->readFromResultTable(t);
}

Recipe RecipeDatabase::retrieveRandomRecipe(){
	ResultTable t = this->selectFrom("recipe", "*", "ORDER BY RANDOM() LIMIT 1");
	if (t.isEmpty()){
		fprintf(stderr, "Unable to find a random recipe.\n");
		return Recipe();
	}
	return this->readFromResultTable(t);
}
//TODO: Change this to be more efficient! One query per recipe is not good!
vector<Recipe> RecipeDatabase::retrieveAllRecipes(){
	ResultTable t = this->executeSQL("SELECT * FROM recipe ORDER BY name;");
	return this->readRecipesFromTable(t);
}

vector<Recipe> RecipeDatabase::retrieveRecipesWithIngredients(vector<Ingredient> ingredients){
	vector<Recipe> recipes;
	if (ingredients.empty()){
		return recipes;
	}
	string filterList = surroundString(ingredients.at(0).getName(), "'");
	for (unsigned int i = 1; i < ingredients.size(); i++){
		filterList += ", " + surroundString(ingredients[i].getName(), "'");
	}
	filterList = '(' + filterList + ')';
	ResultTable t = this->executeSQL("SELECT * "
									 "FROM recipe "
									 "WHERE recipeId IN ("
									 "	SELECT recipeIngredient.recipeId "
									 "	FROM recipeIngredient "
									 "	INNER JOIN ("
									 "		SELECT ingredientId "
									 "		FROM ingredient "
									 "		WHERE name IN "+filterList+""
									 "	) filteredIngredients "
									 "	ON recipeIngredient.ingredientId = filteredIngredients.ingredientId"
									 ") ORDER BY name;");
	return this->readRecipesFromTable(t);
}

vector<Recipe> RecipeDatabase::retrieveRecipesWithTags(vector<RecipeTag> tags){
	vector<Recipe> recipes;
	if (tags.empty()){
		return recipes;
	}
	string filterList = surroundString(tags.at(0).getValue(), "'");
	for (unsigned int i = 1; i < tags.size(); i++){
		filterList += ", " + surroundString(tags[i].getValue(), "'");
	}
	filterList = '(' + filterList + ')';
	ResultTable t = this->executeSQL("SELECT * FROM recipe WHERE recipeId IN (SELECT recipeId FROM recipeTag WHERE tagName IN "+filterList+" );");
	return this->readRecipesFromTable(t);
}

vector<Recipe> RecipeDatabase::retrieveRecipesWithSubstring(string s){
	ResultTable t = this->executeSQL("SELECT * FROM recipe WHERE name LIKE '%"+s+"%' COLLATE NOCASE ORDER BY name;");
	return this->readRecipesFromTable(t);
}

vector<Recipe> RecipeDatabase::retrieveRecipesWithFoodGroups(vector<string> groups){
	vector<Recipe> recipes;
	if (groups.empty()){
		return recipes;
	}
	string filterList = surroundString(groups.at(0), "'");
	for (unsigned int i = 1; i < groups.size(); i++){
		filterList += ", " + surroundString(groups.at(i), "'");
	}
	filterList = '(' + filterList + ')';
	ResultTable t = this->executeSQL("SELECT * FROM recipe WHERE recipeId IN (SELECT recipeId FROM recipeIngredient WHERE ingredientId IN (SELECT ingredientId FROM ingredient WHERE foodGroup IN "+filterList+" ) ) ORDER BY name;");
	return this->readRecipesFromTable(t);
}

vector<string> RecipeDatabase::retrieveAllFoodGroups(){
	ResultTable t = this->executeSQL("SELECT DISTINCT foodGroup FROM ingredient ORDER BY foodGroup;");
	vector<string> foodGroups;
	for (TableRow row : t.rows()){
		foodGroups.push_back(row.at(0));
	}
	return foodGroups;
}

vector<RecipeIngredient> RecipeDatabase::retrieveRecipeIngredients(int recipeId){
	ResultTable t = this->executeSQL("SELECT ingredient.name, ingredient.foodGroup, "//0, 1
									 "recipeIngredient.quantity, recipeIngredient.unitName, recipeIngredient.comment,"//2, 3, 4
									 "unitOfMeasure.name, unitOfMeasure.plural, unitOfMeasure.abbreviation, unitOfMeasure.type, unitOfMeasure.metricCoefficient "//5, 6, 7, 8, 9
									 "FROM ingredient "
									 "INNER JOIN recipeIngredient "
									 "ON ingredient.ingredientId = recipeIngredient.ingredientId "
									 "INNER JOIN unitOfMeasure "
									 "ON recipeIngredient.unitName = unitOfMeasure.name "
									 "WHERE recipeIngredient.recipeId = "+std::to_string(recipeId)+";");
	vector<RecipeIngredient> ings;
	for (TableRow row : t.rows()){
		RecipeIngredient r(row.at(0),
						   row.at(1),
						   std::stof(row.at(2)),
						   UnitOfMeasure(row.at(5), row.at(6), row.at(7), std::stoi(row.at(8)), std::stod(row.at(9))),
						   row.at(4));
		ings.push_back(r);
	}
	return ings;
}

int RecipeDatabase::retrieveIngredientId(string ingredientName){
	return std::stoi(this->selectFrom("ingredient", "ingredientId", "WHERE name = '"+ingredientName+"'").at(0, 0));
}

bool RecipeDatabase::deleteRecipeTags(int recipeId){
	return this->deleteFrom("recipeTag", "WHERE recipeId = "+std::to_string(recipeId));
}

bool RecipeDatabase::deleteRecipeIngredients(int recipeId){
	return this->deleteFrom("recipeIngredient", "WHERE recipeId = "+std::to_string(recipeId));
}

vector<Ingredient> RecipeDatabase::retrieveAllIngredients(){
	ResultTable t = this->selectFrom("ingredient", "name, foodGroup", "ORDER BY name");
	vector<Ingredient> ings;
	for (TableRow row : t.rows()){
		Ingredient i(row.at(0), row.at(1));
		ings.push_back(i);
	}
	return ings;
}

vector<UnitOfMeasure> RecipeDatabase::retrieveAllUnitsOfMeasure(){
	ResultTable t = this->selectFrom("unitOfMeasure", "name, plural, abbreviation, type, metricCoefficient", "ORDER BY name");
	vector<UnitOfMeasure> units;
	if (!t.isEmpty()){
		for (TableRow row : t.rows()){
			UnitOfMeasure u(row.at(0), row.at(1), row.at(2), std::stoi(row.at(3)), std::stod(row.at(4)));
			units.push_back(u);
		}
	}
	return units;
}

vector<RecipeTag> RecipeDatabase::retrieveTags(int recipeId){
	ResultTable t = this->selectFrom("recipeTag", "tagName", "WHERE recipeId="+std::to_string(recipeId)+" ORDER BY tagName");
	vector<RecipeTag> tags;
	if (!t.isEmpty()){
		for (TableRow row : t.rows()){
			RecipeTag tag(row.at(0));
			tags.push_back(tag);
		}
	}
	return tags;
}

vector<RecipeTag> RecipeDatabase::retrieveAllTags(){
	ResultTable t = this->executeSQL("SELECT DISTINCT tagName FROM recipeTag ORDER BY tagName;");
	vector<RecipeTag> tags;
	if (!t.isEmpty()){
		for (TableRow row : t.rows()){
			RecipeTag tag(row.at(0));
			tags.push_back(tag);
		}
	}
	return tags;
}

bool RecipeDatabase::deleteRecipe(string name){
	ResultTable t = this->selectFrom("recipe", "recipeId", "WHERE name='"+name+"'");
	if (t.rowCount() != 1){
		return false;
	}
	string recipeId = t.at(0, 0);
	return this->deleteRecipe(std::stoi(recipeId));
}

bool RecipeDatabase::deleteRecipe(int recipeId){
	string idString = std::to_string(recipeId);
	if (this->selectFrom("recipe", "recipeId", "WHERE recipeId="+idString).isEmpty()){
		printf("Cannot delete. No recipe with ID %d exists.\n", recipeId);
		return false;
	}
	this->executeSQL("BEGIN;");
	bool tagsDeleted = this->deleteFrom("recipeTag", "WHERE recipeId="+idString);
	bool recipeIngredientDeleted = this->deleteFrom("recipeIngredient", "WHERE recipeId="+idString);
	bool recipeDeleted = this->deleteFrom("recipe", "WHERE recipeId="+idString);
	bool instructionDeleted = FileUtils::deleteInstruction(recipeId);
	bool imageDeleted = FileUtils::deleteImage(recipeId);
	Q_UNUSED(instructionDeleted);
	Q_UNUSED(imageDeleted);
	if (tagsDeleted && recipeIngredientDeleted && recipeDeleted){
		this->executeSQL("COMMIT;");
		return true;
	} else {
		this->executeSQL("ROLLBACK;");
		return false;
	}
}

bool RecipeDatabase::deleteIngredient(string name){
	ResultTable t = this->executeSQL("SELECT recipeId "
									 "FROM recipeIngredient "
									 "INNER JOIN ingredient "
									 "ON recipeIngredient.ingredientId = ingredient.ingredientId "
									 "WHERE ingredient.name='"+name+"';");
	if (!t.isEmpty()){
		//There is at least one recipe dependent on the ingredient.
		return false;
	}
	return this->deleteFrom("ingredient", "WHERE name='"+name+"'");
}

bool RecipeDatabase::deleteUnitOfMeasure(string name){
	ResultTable t = this->selectFrom("recipeIngredient", "recipeId", "WHERE unitName='"+name+"'");
	if (!t.isEmpty()){
		return false;
	}
	return this->deleteFrom("unitOfMeasure", "WHERE name='"+name+"'");
}

bool RecipeDatabase::deleteTag(RecipeTag tag){
	return this->deleteFrom("recipeTag", "WHERE tagName='"+tag.getValue()+"'");
}

bool RecipeDatabase::updateRecipe(Recipe recipe, string originalName) {
	string idS = this->selectFrom("recipe", "recipeId", "WHERE name="+surroundString(originalName, "'")).at(0, 0);
	int id = std::stoi(idS);
	this->beginTransaction();
	ResultTable t = this->executeSQL("UPDATE recipe "
									 "SET name = '"+recipe.getName()+"', "
									 "createdDate = '"+recipe.getCreatedDate().toString().toStdString()+"', "
									 "prepTime = '"+recipe.getPrepTime().toString().toStdString()+"', "
									 "cookTime = '"+recipe.getCookTime().toString().toStdString()+"', "
									 "servingCount = "+std::to_string(recipe.getServings())+" "
									 "WHERE recipeId = "+idS+";");
	bool recipeSuccess = t.getReturnCode() == SQLITE_DONE;
	if (!recipeSuccess){
		this->rollbackTransaction();
		return false;
	}
	bool tagsSuccess = this->deleteRecipeTags(id);
	for (RecipeTag tag : recipe.getTags()){
		tagsSuccess = tagsSuccess && this->insertInto(
					"recipeTag",
					  vector<string>({
										 "recipeId",
										 "tagName"
									 }),
					  vector<string>({
										 idS,
										 tag.getValue()
									 }));
	}
	if (!tagsSuccess){
		this->rollbackTransaction();
		return false;
	}
	bool ingredientsSuccess = this->deleteRecipeIngredients(id);
	for (RecipeIngredient ri : recipe.getIngredients()){
		ingredientsSuccess = ingredientsSuccess && this->insertInto(
					"recipeIngredient",
					vector<string>({
									   "recipeId",
									   "ingredientId",
									   "unitName",
									   "quantity",
									   "comment"
								   }),
					vector<string>({
									   idS,
									   std::to_string(this->retrieveIngredientId(ri.getName())),
									   ri.getUnit().getName(),
									   std::to_string(ri.getQuantity()),
									   ri.getComment()
								   }));
	}
	if (!ingredientsSuccess){
		this->rollbackTransaction();
		return false;
	}
	bool instructionSuccess = FileUtils::saveInstruction(id, recipe.getInstruction());
	bool imageSuccess = FileUtils::saveImage(id, recipe.getImage());
	if (!(instructionSuccess && imageSuccess)){
		this->rollbackTransaction();
		return false;
	} else {
		this->commitTransaction();
		return true;
	}
}

void RecipeDatabase::ensureTablesExist(){
	//Make sure that foreign keys are enabled.
	this->executeSQL("PRAGMA foreign_keys = ON;");

	this->executeSQL("BEGIN;");
	//Ingredients table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS ingredient("
					 "ingredientId INTEGER PRIMARY KEY,"
					 "foodGroup varchar,"
					 "name varchar UNIQUE);");
	//Unit of Measure table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS unitOfMeasure("
					 "name varchar UNIQUE PRIMARY KEY,"
					 "plural varchar,"
					 "abbreviation varchar,"
					 "type int,"
					 "metricCoefficient real);");
	//Recipe table. Each recipe can have at most one instruction, and one image.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipe("
					 "recipeId INTEGER PRIMARY KEY,"
					 "name varchar UNIQUE,"
					 "createdDate date,"
					 "prepTime time,"
					 "cookTime time,"
					 "servingCount real);");
	//Recipe tags table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeTag("
					 "recipeId int,"
					 "tagName varchar,"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
	//RecipeIngredient table.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipeIngredient("
					 "ingredientId int,"
					 "recipeId int,"
					 "quantity real,"
					 "unitName varchar,"
					 "comment varchar,"
					 "FOREIGN KEY (ingredientId) REFERENCES ingredient(ingredientId),"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId),"
					 "FOREIGN KEY (unitName) REFERENCES unitOfMeasure(name));");
	this->executeSQL("COMMIT;");
}

Recipe RecipeDatabase::readFromResultTable(ResultTable t, int tRow){
	Recipe r;
	TableRow row = t.rows().at(tRow);
	int id = std::stoi(row.at(0));
	r.setName(row.at(1));
	r.setCreatedDate(QDate::fromString(QString::fromStdString(row.at(2))));
	r.setPrepTime(QTime::fromString(QString::fromStdString(row.at(3))));
	r.setCookTime(QTime::fromString(QString::fromStdString(row.at(4))));
	r.setServings(std::stof(row.at(5)));
	r.setInstruction(FileUtils::loadInstruction(id));
	r.setImage(FileUtils::loadImage(id));
	r.setIngredients(this->retrieveRecipeIngredients(id));
	r.setTags(this->retrieveTags(id));
	return r;
}

//Retrieves recipes from a table with the following format:
// id, name, createdDate, prepTime, cookTime, servings
vector<Recipe> RecipeDatabase::readRecipesFromTable(ResultTable t){
	vector<Recipe> recipes;
	for (unsigned int row = 0; row < t.rowCount(); row++){
		recipes.push_back(readFromResultTable(t, row));
	}
	return recipes;
}
