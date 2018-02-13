#include "model/recipe/ingredients/ingredientlistmodel.h"

IngredientListModel::IngredientListModel(){
    this->ingredients = vector<RecipeIngredient>();
}

int IngredientListModel::rowCount(const QModelIndex &parent) const{
    return this->ingredients.size();
}

QVariant IngredientListModel::data(const QModelIndex &index, int role) const{
    int row = index.row();

    switch(role){
    case Qt::DisplayRole:
        return QString::fromStdString(ingredients[row].getName());
    }

    return QVariant();
}

void IngredientListModel::setIngredients(vector<RecipeIngredient> ingredients){
    this->ingredients = ingredients;
    QModelIndex index = createIndex(0, 0);
    QModelIndex bottomIndex = createIndex(ingredients.size()-1, 0);
    emit dataChanged(index, bottomIndex);
}
