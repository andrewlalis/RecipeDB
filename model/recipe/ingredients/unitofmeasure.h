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
    UnitOfMeasure();
private:
    string name;                //The name of the unit of measure.
    string plural;              //The plural name.
    string abbreviation;        //A short version of the unit.
    float siBaseUnitEquivalent; //The ratio when compared to the base SI unit for this unit. For example: 1 cup = 237mL.
};

#endif // UNITOFMEASURE_H
