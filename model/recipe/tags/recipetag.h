#ifndef RECIPETAG_H
#define RECIPETAG_H

#include <string>

using namespace std;

/**
 * @brief The RecipeTag class is used to represent tags which can be used to categorize recipes for easy retrieval.
 */

class RecipeTag
{
public:
    RecipeTag();
    RecipeTag(string val);

    //Getters
    string getValue();
    //Setters
    void setValue(string newValue);
private:
    string value;
};

#endif // RECIPETAG_H
