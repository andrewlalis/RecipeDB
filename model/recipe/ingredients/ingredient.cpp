#include "model/recipe/ingredients/ingredient.h"

Ingredient::Ingredient(){
    setName("NULL");
    setFoodGroup("NULL");
}

Ingredient::Ingredient(string name, string foodGroup){
    setName(name);
    setFoodGroup(foodGroup);
}

string Ingredient::getName() const{
    return this->name;
}

string Ingredient::getFoodGroup() const{
    return this->foodGroup;
}

void Ingredient::setName(string newName){
    this->name = newName;
}

void Ingredient::setFoodGroup(string newFoodGroup){
	this->foodGroup = newFoodGroup;
}

string Ingredient::toString(){
	return this->getName();
}
