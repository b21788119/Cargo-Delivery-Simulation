#include "Truck.h"
#include <string>
Truck::Truck()
{
    name = "None";
    cargoStation = "None";
    power = 0.0;
}
Truck::Truck(const Truck &source){
    name = source.name;
    cargoStation = source.cargoStation;
    power = source.power;
}
Truck::Truck(std::string truckName,std::string station,double truckPower){
    name = truckName;
    cargoStation = station;
    power = truckPower;
}
Truck::~Truck()
{
    //Nothing
}

