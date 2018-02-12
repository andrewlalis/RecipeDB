#include "model/recipe/ingredients/recipeingredient.h"

RecipeIngredient::RecipeIngredient(int id, string name, string foodGroup, float quantity, UnitOfMeasure unit) : Ingredient(id, name, foodGroup){
    setQuantity(quantity);
    setUnit(unit);
}

RecipeIngredient::RecipeIngredient(Ingredient i, float quantity, UnitOfMeasure unit){
    setId(i.getId());
    setName(i.getName());
    setFoodGroup(i.getFoodGroup());
    setQuantity(quantity);
    setUnit(unit);
}

float RecipeIngredient::getQuantity(){
    return this->quantity;
}

UnitOfMeasure RecipeIngredient::getUnit(){
    return this->unit;
}

string RecipeIngredient::getComment(){
    return this->comment;
}

void RecipeIngredient::setQuantity(float newQuantity){
    this->quantity = newQuantity;
}

void RecipeIngredient::setUnit(UnitOfMeasure newUnit){
    this->unit = newUnit;
}

void RecipeIngredient::setComment(string newComment){
    this->comment = newComment;
}
