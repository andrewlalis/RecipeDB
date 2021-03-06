#include "model/recipe/recipe.h"

Recipe::Recipe(string name, string author, vector<RecipeIngredient> ingredients, Instruction instruction, QImage image, vector<RecipeTag> tags, QDate createdDate, QTime prepTime, QTime cookTime, float servings){
    setName(name);
	setAuthor(author);
    setIngredients(ingredients);
    setInstruction(instruction);
    setImage(image);
    setTags(tags);
    setCreatedDate(createdDate);
    setPrepTime(prepTime);
    setCookTime(cookTime);
    setServings(servings);
}

Recipe::Recipe() : Recipe::Recipe("", "", vector<RecipeIngredient>(), Instruction(), QImage(), vector<RecipeTag>(), QDate::currentDate(), QTime(), QTime(), 1.0f){
    //Set default values when none are specified.
}

string Recipe::getName() const{
	return this->name;
}

string Recipe::getAuthor() const{
	return this->authorName;
}

vector<RecipeIngredient> Recipe::getIngredients() const{
	return this->ingredients;
}

vector<string> Recipe::getFoodGroups() const{
	vector<string> foodGroups;
	for (RecipeIngredient ri : this->ingredients){
		if (find(foodGroups.begin(), foodGroups.end(), ri.getFoodGroup()) == foodGroups.end()){
			foodGroups.push_back(ri.getFoodGroup());
		}
	}
	return foodGroups;
}

Instruction Recipe::getInstruction() const{
    return this->instruction;
}

QImage Recipe::getImage() const{
	return this->image;
}

vector<RecipeTag> Recipe::getTags() const{
	return this->tags;
}

QDate Recipe::getCreatedDate() const{
    return this->createdDate;
}

QTime Recipe::getPrepTime() const{
    return this->prepTime;
}

QTime Recipe::getCookTime() const{
    return this->cookTime;
}

QTime Recipe::getTotalTime() const{
    return QTime(this->cookTime.hour() + this->prepTime.hour(), this->cookTime.minute() + this->prepTime.minute(), this->cookTime.second() + this->prepTime.second());
}

float Recipe::getServings() const{
	return this->servings;
}

bool Recipe::isEmpty() const{
	return this->name.empty();
}

void Recipe::setName(string newName){
	this->name = newName;
}

void Recipe::setAuthor(string newName){
	this->authorName = newName;
}

void Recipe::setIngredients(vector<RecipeIngredient> ingredients){
    this->ingredients = ingredients;
}

void Recipe::setTags(vector<RecipeTag> tags){
    this->tags = tags;
}

void Recipe::addIngredient(RecipeIngredient newIngredient){
    this->ingredients.push_back(newIngredient);
}

void Recipe::setInstruction(Instruction newInstruction){
    this->instruction = newInstruction;
}

void Recipe::setImage(QImage newImage){
    this->image = newImage;
}

void Recipe::setCreatedDate(QDate newDate){
    this->createdDate = newDate;
}

void Recipe::setPrepTime(QTime newTime){
    this->prepTime = newTime;
}

void Recipe::setCookTime(QTime newTime){
    this->cookTime = newTime;
}

void Recipe::setServings(float newServingsCount){
	this->servings = newServingsCount;
}

void Recipe::print(){
	printf("Recipe: %s, Created on: %s, by %s, Prep time: %s, Cook time: %s, Serves: %f\n",
		   this->name.c_str(),
		   this->authorName.c_str(),
		   this->createdDate.toString().toStdString().c_str(),
		   this->prepTime.toString().toStdString().c_str(),
		   this->cookTime.toString().toStdString().c_str(),
		   this->servings);
	printf("\tInstruction: %s\n", this->instruction.getHTML().c_str());
	printf("\tIngredients:\n");
	for (vector<RecipeIngredient>::iterator it = this->ingredients.begin(); it != this->ingredients.end(); ++it){
		RecipeIngredient ri = *it;
		printf("\t\t%s, Food Group: %s, Quantity: %f, Unit: %s\n",
			   ri.getName().c_str(),
			   ri.getFoodGroup().c_str(),
			   ri.getQuantity(),
			   ri.getUnit().getName().c_str());
	}
	printf("\tTags:\n");
	for (vector<RecipeTag>::iterator it = this->tags.begin(); it != this->tags.end(); ++it){
		RecipeTag t = *it;
		printf("\t\t%s\n", t.getValue().c_str());
	}
}
