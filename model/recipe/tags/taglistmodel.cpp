#include "taglistmodel.h"

TagListModel::TagListModel(){

}

int TagListModel::rowCount(const QModelIndex &parent) const{
	return this->tags.size();
}

QVariant TagListModel::data(const QModelIndex &index, int role) const{
	string displayString = this->tags[index.row()].getValue();
	switch(role){
	case Qt::DisplayRole:
		return QString::fromStdString(displayString);
	}

	return QVariant();
}

void TagListModel::setTags(vector<RecipeTag> tags){
	this->tags = tags;
	QModelIndex index = createIndex(0, 0);
	QModelIndex bottomIndex = createIndex(this->tags.size()-1, 0);
	emit dataChanged(index, bottomIndex);
}

bool TagListModel::addTag(RecipeTag tag){
	//Add only if it's different.
	for (unsigned int i = 0; i < this->tags.size(); i++){
		if (!this->tags[i].getValue().compare(tag.getValue())){
			return false;
		}
	}
	this->tags.push_back(tag);
	QModelIndex index = createIndex(this->tags.size()-1, 0);
	QModelIndex bottomIndex = createIndex(this->tags.size()-1, 0);
	emit dataChanged(index, bottomIndex);
	return true;
}

void TagListModel::deleteTag(int index){
	this->tags.erase(this->tags.begin() + index);
	emit dataChanged(createIndex(0, 0), createIndex(this->tags.size()-1, 0));
}

vector<RecipeTag> TagListModel::getTags(){
	return this->tags;
}
