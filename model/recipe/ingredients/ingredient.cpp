#include "model/recipe/ingredients/ingredient.h"

Ingredient::Ingredient(){
	setContent("NULL");
}

Ingredient::Ingredient(string content){
	setContent(content);
}

string Ingredient::getContent() const{
	return this->content;
}

void Ingredient::setContent(string newContent){
	this->content = newContent;
}

