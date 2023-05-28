#ifndef CARGODELIVERYSYSTEM_H
#define CARGODELIVERYSYSTEM_H
#include <vector>
#include <string>
#include "Station.h"
#include "Package.h"
#include "Truck.h"
#include "PackageNode.h"

class CargoDeliverySystem
{
private:
    std::vector<Station> stations;   // I will store all active stations which comes as an input in this vector.
    PackageNode *head;   // Head of our doubly linked list to simulate delivery process.
public:
    CargoDeliverySystem();
    void createStations(std::string dests);
    void createAndAddTrucks(std::string trucks);
    void createAndAddPackages(std::string packages);
    void completeDelivery(std::string newMission);
    void shareCurrentStatus(std::string resultFile);
    ~CargoDeliverySystem();

};

#endif // CARGODELIVERYSYSTEM_H
