#include "unitofmeasure.h"

UnitOfMeasure::UnitOfMeasure(string name, string plural, string abbreviation){
    this->name = name;
    this->plural = plural;
    this->abbreviation = abbreviation;
}

UnitOfMeasure::UnitOfMeasure() : UnitOfMeasure::UnitOfMeasure("", "", ""){
    //Default constructor initializes all fields to empty strings.
}

string UnitOfMeasure::getName() const{
    return this->name;
}

string UnitOfMeasure::getNamePlural() const{
    return this->plural;
}

string UnitOfMeasure::getAbbreviation() const{
    return this->abbreviation;
}
