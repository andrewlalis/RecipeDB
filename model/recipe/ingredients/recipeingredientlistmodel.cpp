#include "recipeingredientlistmodel.h"

RecipeIngredientListModel::RecipeIngredientListModel(){
	this->ingredients = vector<RecipeIngredient>();
}

int RecipeIngredientListModel::rowCount(const QModelIndex &parent) const{
	Q_UNUSED(parent);
	return this->ingredients.size();
}

QVariant RecipeIngredientListModel::data(const QModelIndex &index, int role) const{
	int row = index.row();
	RecipeIngredient i = this->ingredients[row];

	string displayStr = i.toString();

	switch(role){
	case Qt::DisplayRole:
		return QString::fromStdString(displayStr);
	}

	return QVariant();
}

void RecipeIngredientListModel::setIngredients(vector<RecipeIngredient> ingredients){
	this->ingredients = ingredients;
	QModelIndex index = createIndex(0, 0);
	QModelIndex bottomIndex = createIndex(ingredients.size()-1, 0);
	emit dataChanged(index, bottomIndex);
}

bool RecipeIngredientListModel::addIngredient(RecipeIngredient ri){
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

void RecipeIngredientListModel::deleteIngredient(int index){
	this->ingredients.erase(this->ingredients.begin() + index);
	emit dataChanged(createIndex(0, 0), createIndex(this->ingredients.size()-1, 0));
}

vector<RecipeIngredient> RecipeIngredientListModel::getIngredients(){
	return this->ingredients;
}
