#include "unitofmeasure.h"

UnitOfMeasure::UnitOfMeasure(string name, string plural, string abbreviation){
    this->name = name;
    this->plural = plural;
    this->abbreviation = abbreviation;
}

string UnitOfMeasure::getName(){
    return this->name;
}

string UnitOfMeasure::getNamePlural(){
    return this->plural;
}

string UnitOfMeasure::getAbbreviation(){
    return this->abbreviation;
}
