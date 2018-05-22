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
	this->beginTransaction();
	ResultTable t = this->selectFrom("recipe", "*", "WHERE name="+surroundString(recipe.getName(), "'"));
	if (!t.isEmpty()){
		fprintf(stderr, "Error storing recipe: Recipe with name %s already exists.\n", recipe.getName().c_str());
	} else {
		bool success = this->insertInto("recipe",
						 vector<string>({
											"name",
											"authorName",
											"createdDate",
											"cookTime",
											"prepTime",
											"servingCount"
										}),
						 vector<string>({
											recipe.getName(),
											recipe.getAuthor(),
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
				this->commitTransaction();
				return true;
			}
		}
	}
	this->rollbackTransaction();
	return false;
}

bool RecipeDatabase::storeRecipeIngredient(Ingredient i, int recipeId){
	return this->insertInto("recipeIngredient",
					 vector<string>({
										"content",
										"recipeId"
									}),
					 vector<string>({
										i.getContent(),
										std::to_string(recipeId)
									}));
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

vector<Recipe> RecipeDatabase::retrieveAllRecipes(){
	ResultTable t = this->executeSQL("SELECT * FROM recipe ORDER BY name;");
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

vector<Ingredient> RecipeDatabase::retrieveRecipeIngredients(int recipeId){
	ResultTable t = this->executeSQL("SELECT content "
									 "FROM recipeIngredient "
									 "WHERE recipeId = "+std::to_string(recipeId)+";");
	vector<Ingredient> ingredients;
	for (TableRow row : t.rows()){
		ingredients.push_back(Ingredient(row.at(0)));
	}
	return ingredients;
}

bool RecipeDatabase::deleteRecipeTags(int recipeId){
	return this->deleteFrom("recipeTag", "WHERE recipeId = "+std::to_string(recipeId));
}

bool RecipeDatabase::deleteRecipeIngredients(int recipeId){
	return this->deleteFrom("recipeIngredient", "WHERE recipeId = "+std::to_string(recipeId));
}

vector<Ingredient> RecipeDatabase::retrieveAllIngredients(){
	ResultTable t = this->selectFrom("recipeIngredient", "content", "ORDER BY content");
	vector<Ingredient> ings;
	for (TableRow row : t.rows()){
		ings.push_back(Ingredient(row.at(0)));
	}
	return ings;
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
	this->beginTransaction();
	bool tagsDeleted = this->deleteFrom("recipeTag", "WHERE recipeId="+idString);
	bool recipeIngredientDeleted = this->deleteFrom("recipeIngredient", "WHERE recipeId="+idString);
	bool recipeDeleted = this->deleteFrom("recipe", "WHERE recipeId="+idString);
	bool instructionDeleted = FileUtils::deleteInstruction(recipeId);
	bool imageDeleted = FileUtils::deleteImage(recipeId);
	Q_UNUSED(instructionDeleted);
	Q_UNUSED(imageDeleted);
	if (tagsDeleted && recipeIngredientDeleted && recipeDeleted){
		this->commitTransaction();
		return true;
	} else {
		this->rollbackTransaction();
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

bool RecipeDatabase::deleteTag(RecipeTag tag){
	return this->deleteFrom("recipeTag", "WHERE tagName='"+tag.getValue()+"'");
}

bool RecipeDatabase::updateRecipe(Recipe recipe, string originalName) {
	string idS = this->selectFrom("recipe", "recipeId", "WHERE name="+surroundString(originalName, "'")).at(0, 0);
	int id = std::stoi(idS);
	this->beginTransaction();
	ResultTable t = this->executeSQL("UPDATE recipe "
									 "SET name = '"+recipe.getName()+"', "
									 "authorName = '"+recipe.getAuthor()+"', "
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
	for (Ingredient i : recipe.getIngredients()){
		ingredientsSuccess = ingredientsSuccess && this->insertInto(
					"recipeIngredient",
					vector<string>({
									   "recipeId",
									   "content"
								   }),
					vector<string>({
									   idS,
									   i.getContent()
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

	this->beginTransaction();
	//Recipe table. Each recipe can have at most one instruction, and one image.
	this->executeSQL("CREATE TABLE IF NOT EXISTS recipe("
					 "recipeId INTEGER PRIMARY KEY,"
					 "name varchar UNIQUE,"
					 "authorName varchar,"
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
					 "recipeId int,"
					 "content,"
					 "FOREIGN KEY (recipeId) REFERENCES recipe(recipeId));");
	this->commitTransaction();
}

Recipe RecipeDatabase::readFromResultTable(ResultTable t, int tRow){
	Recipe r;
	TableRow row = t.rows().at(tRow);
	int id = std::stoi(row.at(0));											//id
	r.setName(row.at(1));													//Name
	r.setAuthor(row.at(2));													//author
	r.setCreatedDate(QDate::fromString(QString::fromStdString(row.at(3))));	//createdDate
	r.setPrepTime(QTime::fromString(QString::fromStdString(row.at(4))));	//prepTime
	r.setCookTime(QTime::fromString(QString::fromStdString(row.at(5))));	//cookTime
	r.setServings(std::stof(row.at(6)));									//servings
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
