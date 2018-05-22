#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>
#include <QDate>
#include <QTime>
#include <QImage>
#include <algorithm>

#include "model/recipe/ingredients/ingredient.h"
#include "model/recipe/instruction.h"
#include "model/recipe/tags/recipetag.h"

using namespace std;

/**
 * @brief The Recipe class represents all the data of a recipe:
 * - A name.
 * - List of ingredients.
 * - An instruction object, which represents a block of HTML text which forms the instructions.
 * - An image, if possible.
 * - Created Date
 * - A list of tags.
 * - Makes X Servings.
 * - Prep time.
 * - Cook time.
 * The recipe object can be used to populate the window with a full recipe. Prep time, cook time, servings, will be displayed at the beginning of the instructions block.
 */

class Recipe
{
public:
    //Full constructor
	Recipe(string name, string author, vector<RecipeIngredient> ingredients, Instruction instruction, QImage image, vector<RecipeTag> tags, QDate createdDate, QTime prepTime, QTime cookTime, float servings);
    //Constructor with default values.
    Recipe();

    //Getters
    string getName() const;
	string getAuthor() const;
    vector<RecipeIngredient> getIngredients() const;
	vector<string> getFoodGroups() const;
    Instruction getInstruction() const;
    QImage getImage() const;
    vector<RecipeTag> getTags() const;
    QDate getCreatedDate() const;
    QTime getPrepTime() const;
    QTime getCookTime() const;
    QTime getTotalTime() const;                 //Derived method to add prep and cook times.
    float getServings() const;
	bool isEmpty() const;

    //Setters
    void setName(string newName);
	void setAuthor(string newName);
    void setIngredients(vector<RecipeIngredient> ingredients);
    void setTags(vector<RecipeTag> tags);
    void addIngredient(RecipeIngredient newIngredient);
    void setInstruction(Instruction newInstruction);
    void setImage(QImage newImage);
    void setCreatedDate(QDate newDate);
    void setPrepTime(QTime newTime);
    void setCookTime(QTime newTime);
    void setServings(float newServingsCount);

	void print();
private:
    //Main information.
    string name;                                //The name of the recipe.
	string authorName;							//The name of the author of this recipe.
    vector<RecipeIngredient> ingredients;       //The list of ingredients in the recipe.
    Instruction instruction;                    //The instruction HTML document.
    QImage image;                               //An image displayed alongside the recipe.
    //Auxiliary Information.
    vector<RecipeTag> tags;                     //The list of tags which can be used to categorize the recipe.
    QDate createdDate;                          //The date the recipe was created.
    QTime prepTime;                             //The time taken for preparation.
    QTime cookTime;                             //The time taken to cook.
    float servings;                             //The number of servings which this recipe produces.
};

#endif // RECIPE_H
