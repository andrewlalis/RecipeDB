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

string Recipe::getName(){
    return this->name;
}

vector<RecipeIngredient> Recipe::getIngredients(){
    return this->ingredients;
}

Instruction Recipe::getInstruction(){
    return this->instruction;
}

QImage Recipe::getImage(){
    return this->image;
}

QDate Recipe::getCreatedDate(){
    return this->createdDate;
}

QTime Recipe::getPrepTime(){
    return this->prepTime;
}

QTime Recipe::getCookTime(){
    return this->cookTime;
}

QTime Recipe::getTotalTime(){
    return QTime(this->cookTime.hour() + this->prepTime.hour(), this->cookTime.minute() + this->prepTime.minute(), this->cookTime.second() + this->prepTime.second());
}

float Recipe::getServings(){
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
