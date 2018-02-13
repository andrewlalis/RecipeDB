#include "model/recipe/ingredients/ingredientlistmodel.h"

IngredientListModel::IngredientListModel(){
    this->ingredients = vector<RecipeIngredient>();
}

int IngredientListModel::rowCount(const QModelIndex &parent) const{

}

QVariant IngredientListModel::data(const QModelIndex &index, int role) const{

}

void IngredientListModel::setIngredients(vector<RecipeIngredient> ingredients){
    this->ingredients = ingredients;
}
