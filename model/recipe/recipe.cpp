#include "model/recipe/recipe.h"

Recipe::Recipe(){
    this->name = "NULL";
    this->ingredients = vector<Ingredient>();
    this->instructions = vector<Instruction>();
}

Recipe::Recipe(string name, vector<Ingredient> ingredients, vector<Instruction> instructions){
    this->name = name;
    this->ingredients = ingredients;
    this->instructions = instructions;
}

string Recipe::getName(){
    return this->name;
}

vector<Ingredient> Recipe::getIngredients(){
    return this->ingredients;
}

vector<Instruction> Recipe::getInstructions(){
    return this->instructions;
}
