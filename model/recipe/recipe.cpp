#include "model/recipe/recipe.h"

Recipe::Recipe(string name, vector<RecipeIngredient> ingredients, Instruction instruction, QImage image, vector<RecipeTag> tags, QDate createdDate, QTime prepTime, QTime cookTime, float servings){
    setName(name);
    setIngredients(ingredients);
    setInstruction(instruction);
    setImage(image);
    setTags(tags);
    setCreatedDate(createdDate);
    setPrepTime(prepTime);
    setCookTime(cookTime);
    setServings(servings);
}

Recipe::Recipe() : Recipe::Recipe("Unnamed Recipe", vector<RecipeIngredient>(), Instruction(), QImage(), vector<RecipeTag>(), QDate::currentDate(), QTime(1, 0), QTime(0, 30), 10.0f){
    //Set default values when none are specified.
}

string Recipe::getName() const{
    return this->name;
}

vector<RecipeIngredient> Recipe::getIngredients() const{
    return this->ingredients;
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

void Recipe::setName(string newName){
    this->name = newName;
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
	printf("Recipe: %s, Created on: %s, Prep time: %s, Cook time: %s, Serves: %f\n",
		   this->name.c_str(),
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
