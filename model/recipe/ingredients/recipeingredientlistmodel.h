#ifndef RECIPEINGREDIENTLISTMODEL_H
#define RECIPEINGREDIENTLISTMODEL_H

#include <QAbstractListModel>

#include "model/recipe/ingredients/recipeingredient.h"

class RecipeIngredientListModel : public QAbstractListModel
{
	public:
		RecipeIngredientListModel();

		//Overridden methods.
		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

		//Custom methods to handle ingredient data.
		void setIngredients(vector<RecipeIngredient> ingredients);
		bool addIngredient(RecipeIngredient ri);
		void deleteIngredient(int index);
		vector<RecipeIngredient> getIngredients();

	private:
		vector<RecipeIngredient> ingredients;

};

#endif // RECIPEINGREDIENTLISTMODEL_H
