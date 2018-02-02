#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>
#include <hash_map>

#include "headers/ingredient.h"
#include "headers/instruction.h"

using namespace std;

class Recipe
{
public:
    Recipe();

    string getName();
private:
    string name;
    vector<string> tags;
    vector<Ingredient> ingredients;
    vector<Instruction> instructions;
};

#endif // RECIPE_H
