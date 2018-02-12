#ifndef RECIPEINGREDIENT_H
#define RECIPEINGREDIENT_H

#include <string>

#include "model/recipe/ingredients/ingredient.h"
#include "model/recipe/ingredients/unitofmeasure.h"

using namespace std;

/**
 * @brief The RecipeIngredient class represents both an ingredient and a unit of measure, to be used in a recipe object.
 */

class RecipeIngredient : public Ingredient
{
public:
    //Constructor for new RecipeIngredient without starting child ingredient.
    RecipeIngredient(int id, string name, string foodGroup, float quantity, UnitOfMeasure unit);
    //Constructor using data from a child ingredient.
    RecipeIngredient(Ingredient i, float quantity, UnitOfMeasure unit);

    //Getters
    float getQuantity();
    UnitOfMeasure getUnit();
    string getComment();

    //Setters
    void setQuantity(float newQuantity);
    void setUnit(UnitOfMeasure newUnit);
    void setComment(string newComment);
private:
    float quantity;
    UnitOfMeasure unit;
    string comment;
};

#endif // RECIPEINGREDIENT_H
