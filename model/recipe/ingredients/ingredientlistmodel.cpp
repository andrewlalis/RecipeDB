#include "model/recipe/ingredients/ingredientlistmodel.h"

IngredientListModel::IngredientListModel(){
	this->ingredients = vector<Ingredient>();
}

int IngredientListModel::rowCount(const QModelIndex &parent) const{
	Q_UNUSED(parent);
    return this->ingredients.size();
}

QVariant IngredientListModel::data(const QModelIndex &index, int role) const{
    int row = index.row();
	Ingredient i = this->ingredients[row];

	string displayStr = i.toString();

    switch(role){
    case Qt::DisplayRole:
		return QString::fromStdString(displayStr);
    }

    return QVariant();
}

void IngredientListModel::setIngredients(vector<Ingredient> ingredients){
    this->ingredients = ingredients;
    QModelIndex index = createIndex(0, 0);
    QModelIndex bottomIndex = createIndex(ingredients.size()-1, 0);
	emit dataChanged(index, bottomIndex);
}

bool IngredientListModel::addIngredient(Ingredient ri){
	//Add only if it doesn't exist already.
	for (unsigned int i = 0; i < this->ingredients.size(); i++){
		if (!this->ingredients[i].getName().compare(ri.getName())){
			return false;
		}
	}
	this->ingredients.push_back(ri);
	QModelIndex index = createIndex(this->ingredients.size()-1, 0);
	QModelIndex bottomIndex = createIndex(this->ingredients.size()-1, 0);
	emit dataChanged(index, bottomIndex);
	return true;
}

void IngredientListModel::deleteIngredient(int index){
	this->ingredients.erase(this->ingredients.begin() + index);
	emit dataChanged(createIndex(0, 0), createIndex(this->ingredients.size()-1, 0));
}

vector<Ingredient> IngredientListModel::getIngredients(){
	return this->ingredients;
}
