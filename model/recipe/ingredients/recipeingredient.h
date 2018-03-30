#ifndef RECIPEINGREDIENT_H
#define RECIPEINGREDIENT_H

#include <string>
#include <cmath>

#include "model/recipe/ingredients/ingredient.h"
#include "model/recipe/ingredients/unitofmeasure.h"
#include "utils/stringutils.h"

using namespace std;

/**
 * @brief The RecipeIngredient class represents both an ingredient and a unit of measure, to be used in a recipe object.
 */

class RecipeIngredient : public Ingredient
{
public:
    //Constructor for new RecipeIngredient without starting child ingredient.
	RecipeIngredient(string name, string foodGroup, float quantity, UnitOfMeasure unit, string comment);
    //Constructor using data from a child ingredient.
	RecipeIngredient(Ingredient i, float quantity, UnitOfMeasure unit, string comment);
	RecipeIngredient(Ingredient &i);
	RecipeIngredient();

    //Getters
    float getQuantity() const;
    UnitOfMeasure getUnit() const;
    string getComment() const;

    //Setters
    void setQuantity(float newQuantity);
    void setUnit(UnitOfMeasure newUnit);
    void setComment(string newComment);
	string toString();
private:
    float quantity;
    UnitOfMeasure unit;
    string comment;
};

#endif // RECIPEINGREDIENT_H
