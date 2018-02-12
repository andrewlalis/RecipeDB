#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>

#include "model/recipe/ingredients/recipeingredient.h"
#include "model/recipe/instruction.h"

using namespace std;

/**
 * @brief The Recipe class represents all the data of a recipe:
 * - A name.
 * - List of ingredients.
 * - An instruction object, which represents a block of HTML text which forms the instructions.
 * - An image, if possible.
 * - Created Date
 * - A list of tags.
 * - Makes X Servings.
 * - Prep time.
 * - Cook time.
 * The recipe object can be used to populate the window with a full recipe. Prep time, cook time, servings, will be displayed at the beginning of the instructions block.
 */

class Recipe
{
public:
    Recipe();
    Recipe(string name, vector<RecipeIngredient> ingredients, Instruction instruction);

    string getName();
    vector<RecipeIngredient> getIngredients();
    Instruction getInstruction();
private:
    string name;
    vector<string> tags;
    vector<RecipeIngredient> ingredients;
    Instruction instruction;

};

#endif // RECIPE_H
