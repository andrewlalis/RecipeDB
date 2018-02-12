#include "recipetag.h"

RecipeTag::RecipeTag() : RecipeTag(""){
    //Default constructor sets value to empty string.
}

RecipeTag::RecipeTag(string val){
    this->value = val;
}

string RecipeTag::getValue(){
    return this->value;
}

void RecipeTag::setValue(string newValue){
    this->value = newValue;
}
