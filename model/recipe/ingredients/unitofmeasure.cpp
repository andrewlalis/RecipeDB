#include "unitofmeasure.h"

UnitOfMeasure::UnitOfMeasure(string name, string plural, string abbreviation, int type){
    this->name = name;
    this->plural = plural;
	this->abbreviation = abbreviation;
	this->type = type;
}

UnitOfMeasure::UnitOfMeasure(string name){
	this->name = name;
	this->plural = name + "s";
	this->abbreviation = "NULL";
	this->type = MISC;
	///TODO: Make actual guessing of this stuff.
}

UnitOfMeasure::UnitOfMeasure() : UnitOfMeasure::UnitOfMeasure("", "", "", MISC){
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

int UnitOfMeasure::getType() const{
	return this->type;
}
