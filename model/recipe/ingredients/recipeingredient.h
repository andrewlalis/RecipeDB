#ifndef RECIPEINGREDIENT_H
#define RECIPEINGREDIENT_H

#include <string>

#include "model/recipe/ingredients/ingredient.h"

using namespace std;

class RecipeIngredient : public Ingredient
{
public:
    RecipeIngredient(int id, string name, string foodGroup, int quantity, string unit);
    RecipeIngredient(Ingredient i, int quantity, string unit);

    int getQuantity();
    string getUnit();
    string getComment();

    void setQuantity(int newQuantity);
    void setUnit(string newUnit);
    void setComment(string newComment);
private:
    int quantity;
    string unit;
    string comment;
};

#endif // RECIPEINGREDIENT_H
