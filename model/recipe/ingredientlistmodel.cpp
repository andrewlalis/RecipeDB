#include "model/recipe/ingredientlistmodel.h"

IngredientListModel::IngredientListModel(){
    this->ingredients = vector<Ingredient>();
}

int IngredientListModel::rowCount(const QModelIndex &parent){
    return this->ingredients.size();
}

QVariant IngredientListModel::data(const QModelIndex &index, int role){

}

void IngredientListModel::setIngredients(vector<Ingredient> ingredients){
    this->ingredients = ingredients;
}
