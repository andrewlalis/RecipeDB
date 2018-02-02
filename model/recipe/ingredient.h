#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

using namespace std;

class Ingredient
{
public:
    Ingredient();
    Ingredient(int id, string name, string foodGroup);

    int getId();
    string getName();
    string getFoodGroup();

    void setId(int newId);
    void setName(string newName);
    void setFoodGroup(string newFoodGroup);
protected:
    int id;
    string name;
    string foodGroup;
};

#endif // INGREDIENT_H
