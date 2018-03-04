#include "model/recipe/ingredients/ingredientlistmodel.h"

IngredientListModel::IngredientListModel(){
    this->ingredients = vector<RecipeIngredient>();
}

int IngredientListModel::rowCount(const QModelIndex &parent) const{
    return this->ingredients.size();
}

QVariant IngredientListModel::data(const QModelIndex &index, int role) const{
    int row = index.row();
	RecipeIngredient i = this->ingredients[row];

	string displayStr;

	if (std::ceil(i.getQuantity()) == i.getQuantity()){
		//The quantity is an integer and should be casted.
		displayStr += std::to_string((int)i.getQuantity());
	} else {
		displayStr += std::to_string(i.getQuantity());
	}

	displayStr += " " + i.getUnit().getAbbreviation() + " " + i.getName();

    switch(role){
    case Qt::DisplayRole:
		return QString::fromStdString(displayStr);
    }

    return QVariant();
}

void IngredientListModel::setIngredients(vector<RecipeIngredient> ingredients){
    this->ingredients = ingredients;
    QModelIndex index = createIndex(0, 0);
    QModelIndex bottomIndex = createIndex(ingredients.size()-1, 0);
    emit dataChanged(index, bottomIndex);
}
