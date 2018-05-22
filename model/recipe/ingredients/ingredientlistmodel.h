#ifndef INGREDIENTLISTMODEL_H
#define INGREDIENTLISTMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>
#include <vector>

#include "model/recipe/ingredients/ingredient.h"

/**
 * @brief The IngredientListModel class
 *
 * The ingredient list model extends the QAbstractListModel and is used for lists of ingredients,
 * whether they appear in the NewRecipe dialog or in the main recipe view.
 */
class IngredientListModel : public QAbstractListModel
{
public:
    IngredientListModel();

    //Overridden methods.
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //Custom methods to handle ingredient data.
	void setIngredients(vector<Ingredient> ingredients);
	bool addIngredient(Ingredient i);
	void deleteIngredient(int index);
	vector<Ingredient> getIngredients();

private:
	vector<Ingredient> ingredients;

};

#endif // INGREDIENTLISTMODEL_H
