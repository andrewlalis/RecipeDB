#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

using namespace std;

/**
 * @brief The Ingredient class represents an ingredient, which is a string representing one component of a recipe.
 * The user is free to compose a recipe string however they like. However, the program will restrict obviously
 * invalid input, and try to be smart about determining if an ingredient is valid.
 */

class Ingredient
{
public:
    Ingredient();
	Ingredient(string content);

    //Getters
	string getContent() const;

    //Setters
	void setContent(string newContent);

protected:
	string content;
};

#endif // INGREDIENT_H
