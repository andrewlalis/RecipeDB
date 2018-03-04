#ifndef UNITOFMEASURE_H
#define UNITOFMEASURE_H

#include <string>

using namespace std;

/**
 * @brief The UnitOfMeasure class represents a way to measure an ingredient. It contains a name, an abbreviation, plural name, and some information on conversion.
 */

class UnitOfMeasure
{
public:
	//Constants Declarations.
	static const int MASS = 1;
	static const int VOLUME = 2;
	static const int LENGTH = 3;
	static const int MISC = 4;

    //Full constructor.
	UnitOfMeasure(string name, string plural, string abbreviation, int type);
	//Attempt to guess unit from just a string.
	UnitOfMeasure(string name);
    //Constructor with default values.
    UnitOfMeasure();

    //Getters
    string getName() const;
    string getNamePlural() const;
    string getAbbreviation() const;
	int getType() const;
private:
    string name;                //The name of the unit of measure.
    string plural;              //The plural name.
    string abbreviation;        //A short version of the unit.
	int type;					//The type of unit, as one of the constants above.
	double metricCoefficient;	//The conversion from this unit to the standard metric unit.
};

#endif // UNITOFMEASURE_H
