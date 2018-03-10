#include "unitofmeasure.h"

UnitOfMeasure::UnitOfMeasure(string name, string plural, string abbreviation, int type, double coef){
    this->name = name;
    this->plural = plural;
	this->abbreviation = abbreviation;
	this->type = type;
	this->metricCoefficient = coef;
}

UnitOfMeasure::UnitOfMeasure(string name){
	this->name = name;
	this->plural = name + "s";
	this->abbreviation = "NULL";
	this->type = MISC;
	this->metricCoefficient = 1;
	///TODO: Make actual guessing of this stuff.
}

UnitOfMeasure::UnitOfMeasure() : UnitOfMeasure::UnitOfMeasure("", "", "", MISC, 1.0){
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

double UnitOfMeasure::getMetricCoefficient() const{
	return this->metricCoefficient;
}
