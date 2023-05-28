#include "Station.h"
#include <string>
#include <vector>
#include "Truck.h"
#include "Package.h"
#include "Stack.h"
#include "Queue.h"

Station::Station()
{
    cityName = "";
}
Station::Station(const Station &source){
    cityName = source.cityName;
    truckGarage = source.truckGarage;
    availablePackages = source.availablePackages;
}
Station::Station(std::string city){
    cityName = city;
}
Truck Station::useTruck(){
    // When our program needs a truck,we first create a truck from front of our queue.Then dequeue.
    Truck availableTruck;
    truckGarage.getFront(availableTruck);
    truckGarage.dequeue();
    return availableTruck;
}
Package Station::takePackage(){
    // When our program needs to take a package from a station,it wil take it from top of our stack.Thank pop()
    Package package;
    availablePackages.getTop(package);
    availablePackages.pop();
    return package;
}
void Station::addPackage(Package newPackage){
    availablePackages.push(newPackage);
}
void Station::addTruck(Truck newTruck){
    truckGarage.enqueue(newTruck);
}
std::string Station::display(){
    std::string status = cityName+"\n"+"Packages:\n";
    while(true){
        if(availablePackages.size() == 0){
            break;
        }
        Package package;
        availablePackages.getTop(package);
        status+= package.getName()+"\n";
        availablePackages.pop();
    }
    status+="Trucks:\n";
   while(true){
        if(truckGarage.size() == 0){
            break;
        }
        Truck truck;
        truckGarage.getFront(truck);
        status+= truck.getName()+"\n";
        truckGarage.dequeue();
    }
    status+="-------------\n";
    return status;
}

Station::~Station()
{
}

