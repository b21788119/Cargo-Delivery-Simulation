#include "Package.h"
#include <string>

Package::Package()
{
    name = "?";
    cargoStation = "?";
}
Package::Package(const Package &source){
    name = source.name;
    cargoStation = source.cargoStation;
}
Package::Package(std::string packageName,std::string stationName){
    name = packageName;
    cargoStation = stationName;
}
void Package::setName(std::string packageName){
    name = packageName;
}
void Package::setCargoStation(std::string station){
    cargoStation = station;
}
Package::~Package()
{
}

