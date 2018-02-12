#include "model/recipe/recipe.h"

Recipe::Recipe(){
    //Set default values when none are specified.
    this->Recipe("Unnamed Recipe",
                 vector<RecipeIngredient>(),
                 Instruction(),
                 QImage(),
                 vector<RecipeTag>(),
                 QDate.currentDate(),
                 QTime(1, 0),
                 QTime(0, 30),
                 10.0f);
}

Recipe::Recipe(string name, vector<RecipeIngredient> ingredients, Instruction instruction, QImage image, vector<RecipeTag> tags, QDate createdDate, QTime prepTime, QTime cookTime, float servings){
    this->name = name;
    this->ingredients = ingredients;
    this->instruction = instruction;
    this->image = image;
    this->tags = tags;
    this->createdDate = createdDate;
    this->prepTime = prepTime;
    this->cookTime = cookTime;
    this->servings = servings;
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
