#include "model/recipe/ingredients/ingredient.h"

Ingredient::Ingredient(){
    setId(-1);
    setName("NULL");
    setFoodGroup("NULL");
}

Ingredient::Ingredient(int id, string name, string foodGroup){
    setId(id);
    setName(name);
    setFoodGroup(foodGroup);
}

int Ingredient::getId(){
    return this->id;
}

string Ingredient::getName(){
    return this->name;
}

string Ingredient::getFoodGroup(){
    return this->foodGroup;
}

void Ingredient::setId(int newId){
    this->id = newId;
}

void Ingredient::setName(string newName){
    this->name = newName;
}

void Ingredient::setFoodGroup(string newFoodGroup){
    this->foodGroup = newFoodGroup;
}
