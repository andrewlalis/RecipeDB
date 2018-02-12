#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>
#include <hash_map>

#include "model/recipe/ingredient.h"
#include "model/recipe/instruction.h"

using namespace std;

class Recipe
{
public:
    Recipe();
    Recipe(string name, vector<Ingredient> ingredients, vector<Instruction> instructions);

    string getName();
    vector<Ingredient> getIngredients();
    vector<Instruction> getInstructions();
private:
    string name;
    vector<string> tags;
    vector<Ingredient> ingredients;
    vector<Instruction> instructions;

};

#endif // RECIPE_H
