#include "recipetag.h"

RecipeTag::RecipeTag(){
    this->RecipeTag("");
}

RecipeTag::RecipeTag(string val){
    this->value = val;
}

RecipeTag::getValue(){
    return this->value;
}

RecipeTag::setValue(string newValue){
    this->value = newValue;
}
