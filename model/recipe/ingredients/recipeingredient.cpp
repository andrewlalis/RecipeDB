#include "model/recipe/ingredients/recipeingredient.h"

RecipeIngredient::RecipeIngredient(int id, string name, string foodGroup, int quantity, UnitOfMeasure unit) : Ingredient(id, name, foodGroup){
    setQuantity(quantity);
    setUnit(unit);
}

RecipeIngredient::RecipeIngredient(Ingredient i, int quantity, UnitOfMeasure unit){
    setId(i.getId());
    setName(i.getName());
    setFoodGroup(i.getFoodGroup());
    setQuantity(quantity);
    setUnit(unit);
}

string RecipeIngredient::getComment(){
    return this->comment;
}

void RecipeIngredient::setQuantity(int newQuantity){
    this->quantity = newQuantity;
}

void RecipeIngredient::setUnit(UnitOfMeasure newUnit){
    this->unit = newUnit;
}

void RecipeIngredient::setComment(string newComment){
    this->comment = newComment;
}
