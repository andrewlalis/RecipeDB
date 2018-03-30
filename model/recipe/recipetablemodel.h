#ifndef RECIPETABLEMODEL_H
#define RECIPETABLEMODEL_H

#include <QAbstractTableModel>

#include "model/recipe/recipe.h"
#include "utils/stringutils.h"

class RecipeTableModel : public QAbstractTableModel
{
	public:
		RecipeTableModel();
		RecipeTableModel(vector<Recipe> recipes);

		//Overridden methods.
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		//Normal methods.
		void setRecipes(vector<Recipe> recipes);
		Recipe getRecipeAt(unsigned int index);
		void clear();
	private:
		vector<Recipe> recipes;
};

#endif // RECIPETABLEMODEL_H
