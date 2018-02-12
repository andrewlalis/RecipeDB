#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

using namespace std;

/**
 * @brief The Ingredient class represents an ingredient, which is classified by a food group, and has a name and an ID.
 * An ingredient cannot be included on its own in a recipe, and must be paired with a Unit in a RecipeIngredient Object.
 */

class Ingredient
{
public:
    Ingredient();
    Ingredient(string name, string foodGroup);

    //Getters
    string getName();
    string getFoodGroup();

    //Setters
    void setName(string newName);
    void setFoodGroup(string newFoodGroup);
protected:
    string name;
    string foodGroup;
};

#endif // INGREDIENT_H
