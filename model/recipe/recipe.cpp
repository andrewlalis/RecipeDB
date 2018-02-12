#include "model/recipe/recipe.h"

Recipe::Recipe(){
    this->name = "NULL";
    this->ingredients = vector<RecipeIngredient>();
    this->instruction = Instruction();
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
