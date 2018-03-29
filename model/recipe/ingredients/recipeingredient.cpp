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

string RecipeIngredient::toString(){
	string result;
	if (std::ceil(this->getQuantity()) == this->getQuantity()){
		result += std::to_string((int)this->getQuantity());
	} else {
		result += StringUtils::toString(this->getQuantity());
	}
	result += " " + this->getUnit().getAbbreviation() + " " + this->getName();
	if (!this->getComment().empty()) result += " (" + this->getComment() + ")";

	return result;
}
