#include "recipetablemodel.h"

RecipeTableModel::RecipeTableModel()
{

}

RecipeTableModel::RecipeTableModel(vector<Recipe> recipes){
	this->setRecipes(recipes);
}

int RecipeTableModel::rowCount(const QModelIndex &parent) const{
	Q_UNUSED(parent);
	return this->recipes.size();
}

int RecipeTableModel::columnCount(const QModelIndex &parent) const{
	Q_UNUSED(parent);
	return 5;//FIX THIS TO BE MORE ADAPTIVE EVENTUALLY.
}

QVariant RecipeTableModel::data(const QModelIndex &index, int role) const{
	int row = index.row();
	int col = index.column();
	Recipe r = this->recipes[row];

	if (role == Qt::DisplayRole){
		switch(col){
			case 0:
				return QString::fromStdString(r.getName());
			case 1:
				return QString::fromStdString(r.getCreatedDate().toString().toStdString());
			case 2:
				return QString::fromStdString(StringUtils::toString(r.getServings()));
			case 3:
				return r.getPrepTime().toString("hh:mm:ss");
			case 4:
				return r.getCookTime().toString("hh:mm:ss");
		}
	}
	return QVariant();
}

QVariant RecipeTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
	if (role != Qt::DisplayRole){
		return QVariant();
	}
	if (orientation == Qt::Horizontal){
		switch (section){
			case 0:
				return "Name";
			case 1:
				return "Created On";
			case 2:
				return "Servings";
			case 3:
				return "Prep Time";
			case 4:
				return "Cook Time";
			default:
				return QVariant();
		}
	} else if (orientation == Qt::Vertical){
		return QString::fromStdString(std::to_string(section));
	}
	return QVariant();
}

void RecipeTableModel::setRecipes(vector<Recipe> recipes){
	beginInsertRows({}, 0, recipes.size()-1);
	this->recipes = recipes;
	endInsertRows();
}

Recipe RecipeTableModel::getRecipeAt(unsigned int index){
	if (index >= this->recipes.size()){
		return Recipe();
	}
	return this->recipes[index];
}

void RecipeTableModel::clear(){
	beginResetModel();
	this->recipes.clear();
	endResetModel();
}
