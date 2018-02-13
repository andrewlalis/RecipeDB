#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

using namespace std;

/**
 * @brief The Instruction class is meant to hold an HTML document in string form, which holds formatted text as the instructions for the recipe.
 */

class Instruction
{
public:
    Instruction();
    Instruction(string text);

    //Getters
    string getHTML() const;

    //Setters
    void setHTML(string newText);
private:
    string htmlText;
};

#endif // INSTRUCTION_H
