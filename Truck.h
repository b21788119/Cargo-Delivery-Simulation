#ifndef TRUCK_H
#define TRUCK_H
#include <string>
#include "Package.h"

class Truck : public Package    // Truck will be a BIG Package in this program.
{
private:
    double power;   // Additional attribute
public:
    Truck();
    Truck(const Truck &source);
    Truck(std::string truckName,std::string station,double truckPower);
    ~Truck();

};

#endif // TRUCK_H
