#include "model/recipe/instruction.h"

Instruction::Instruction(){
    setHTML("");
}

Instruction::Instruction(string text){
    setHTML(text);
}

string Instruction::getHTML() const{
    return this->htmlText;
}

void Instruction::setHTML(string newText){
    this->htmlText = newText;
}
