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
    string name;
    string plural;
    string abbreviation;
};

#endif // UNITOFMEASURE_H
