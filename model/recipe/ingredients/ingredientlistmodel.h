#ifndef INGREDIENTLISTMODEL_H
#define INGREDIENTLISTMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>

#include "model/recipe/ingredients/recipeingredient.h"

class IngredientListModel : public QAbstractListModel
{
public:
    IngredientListModel();

    //Overridden methods.
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //Custom methods to handle ingredient data.
	void setIngredients(vector<Ingredient> ingredients);
	bool addIngredient(Ingredient ri);
	void deleteIngredient(int index);
	vector<Ingredient> getIngredients();

private:
	vector<Ingredient> ingredients;

	//Helper for printing.

};

#endif // INGREDIENTLISTMODEL_H
