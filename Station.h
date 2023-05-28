#ifndef STATION_H
#define STATION_H
#include <string>
#include "Stack.h"
#include "Queue.h"
#include "Truck.h"
#include "Package.h"
#include <string>
class Station
{
private:
    std::string cityName;
    Queue<Truck> truckGarage;  // Available trucks will be stored in our Queue.
    Stack<Package> availablePackages; // Available packages will be stored in our stack.
public:
    Station();
    Station(const  Station &source);
    Station(std::string city);
    std::string getCityName(){return cityName;}
    Truck useTruck();
    Package takePackage();
    void addPackage(Package newPackage);
    void addTruck(Truck newTruck);
    std::string display();
    ~Station();
};

#endif // STATION_H
