#ifndef TAGLISTMODEL_H
#define TAGLISTMODEL_H

#include <QAbstractListModel>

#include "model/recipe/tags/recipetag.h"

class TagListModel : public QAbstractListModel
{
	public:
		TagListModel();
		//Overridden methods.
		int rowCount(const QModelIndex &parent = QModelIndex()) const override;
		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


		void setTags(vector<RecipeTag> tags);
		bool addTag(RecipeTag tag);
		void deleteTag(int index);
		vector<RecipeTag> getTags();
	private:
		vector<RecipeTag> tags;
};

#endif // TAGLISTMODEL_H
