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
		float q = i.getQuantity();
		displayStr += toString(q);
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

bool IngredientListModel::addIngredient(RecipeIngredient ri){
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

vector<RecipeIngredient> IngredientListModel::getIngredients(){
	return this->ingredients;
}

string toString(float val){
	float decimal = std::fmod(val, 1.0f);
	int places = 1;
	while (std::fmod(decimal * 10, 1.0f) > 0){
		decimal *= 10;
		places++;
	}
	char buffer[50];
	string arg = "%."+std::to_string(places)+"f";
	sprintf(buffer, arg.c_str(), val);
	string s = buffer;
	return s;
}
