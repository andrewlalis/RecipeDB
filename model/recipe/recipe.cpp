#include "model/recipe/recipe.h"

Recipe::Recipe(){
    //Set default values when none are specified.
    this->Recipe("Unnamed Recipe",
                 vector<RecipeIngredient>(),
                 Instruction(),
                 QImage(),
                 vector<string>())
    this->name = "Unnamed Recipe";
    this->ingredients = vector<RecipeIngredient>();
    this->instruction = Instruction();
    this->image = QImage();
    this->tags = vector<string>();
    this->createdDate = QDate.currentDate();
    this->prepTime = QTime(1, 0);
    this->cookTime = QTime(0, 30);
    this->servings = 10;
}

Recipe::Recipe(string name, vector<RecipeIngredient> ingredients, Instruction instruction, QImage image, vector<string> tags, QDate createdDate, QTime prepTime, QTime cookTime, float servings){
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

Recipe::Recipe(string name, vector<RecipeIngredient> ingredients, Instruction instruction)
{
    this->name = name;
    this->ingredients = ingredients;
    this->instruction = instruction;
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
