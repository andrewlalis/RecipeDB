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
	return 2;//FIX THIS TO BE MORE ADAPTIVE EVENTUALLY.
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
