#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CargoDeliverySystem.h"

using namespace std;
int main(int argc, char* argv[]){
   
    string dests = argv[1];
    string packages = argv[2];
    string trucks = argv[3];
    string missions = argv[4];
    string resultFile = argv[5];
    
    vector<string> allMissions;
    string mission;
    ifstream myFile(missions);
    if (myFile.is_open()){ 
        while(myFile.good()){
            getline(myFile,mission);
            allMissions.push_back(mission);
        }
        myFile.close(); 
    }
    else {
        cout << "Unable To Open File";  
    }
    
    CargoDeliverySystem deliverySystem;
    deliverySystem.createStations(dests);
    deliverySystem.createAndAddPackages(packages);
    deliverySystem.createAndAddTrucks(trucks);
    
    for(size_t i=0;i<allMissions.size();i++){
        deliverySystem.completeDelivery(allMissions.at(i));
    }
    deliverySystem.shareCurrentStatus(resultFile);
    return 0;
}

