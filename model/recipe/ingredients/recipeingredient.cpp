#include "model/recipe/ingredients/recipeingredient.h"

RecipeIngredient::RecipeIngredient(string name, string foodGroup, float quantity, UnitOfMeasure unit, string comment) : Ingredient(name, foodGroup){
    setQuantity(quantity);
    setUnit(unit);
	setComment(comment);
}

RecipeIngredient::RecipeIngredient(Ingredient i, float quantity, UnitOfMeasure unit, string comment){
    setName(i.getName());
    setFoodGroup(i.getFoodGroup());
    setQuantity(quantity);
	setUnit(unit);
	setComment(comment);
}

RecipeIngredient::RecipeIngredient(){

}

float RecipeIngredient::getQuantity() const{
    return this->quantity;
}

UnitOfMeasure RecipeIngredient::getUnit() const{
    return this->unit;
}

string RecipeIngredient::getComment() const{
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
