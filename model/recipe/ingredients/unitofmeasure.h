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
    //Full constructor.
    UnitOfMeasure(string name, string plural, string abbreviation);
    //Constructor with default values.
    UnitOfMeasure();

    //Getters
    string getName();
    string getNamePlural();
    string getAbbreviation();
private:
    string name;                //The name of the unit of measure.
    string plural;              //The plural name.
    string abbreviation;        //A short version of the unit.
};

#endif // UNITOFMEASURE_H
