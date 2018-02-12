#ifndef INGREDIENTLISTMODEL_H
#define INGREDIENTLISTMODEL_H

#include <QAbstractListModel>

#include "model/recipe/ingredients/ingredient.h"

class IngredientListModel : public QAbstractListModel
{
public:
    IngredientListModel();

    //Overridden methods.
    int rowCount(const QModelIndex &parent = QModelIndex());
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole);

    //Custom methods to handle ingredient data.
    void setIngredients(vector<Ingredient> ingredients);

private:
    vector<Ingredient> ingredients;
};

#endif // INGREDIENTLISTMODEL_H
