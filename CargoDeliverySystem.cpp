#include "CargoDeliverySystem.h"
#include <string>
#include "Station.h"
#include "Package.h"
#include "Truck.h"
#include "PackageNode.h"
#include <fstream>
#include <sstream>
#include <iostream>
CargoDeliverySystem::CargoDeliverySystem()
{
    head = nullptr;
}
void CargoDeliverySystem::createStations(std::string destinations)
{  // This function takes dests.txt as an argument,creates stations and adds them to our vector named stations.
    std::string destination;
    std::vector<std::string> dests;         
    std::ifstream myFile(destinations);
    if (myFile.is_open()){ 
        while(myFile.good()){
            getline(myFile,destination);
            dests.push_back(destination);
        }
        myFile.close(); 
    }
    else {
        std::cout << "Unable To Open File";  
    }
    for(int i=0;i<dests.size();i++){
        Station station(dests.at(i));
        stations.push_back(station);
    }
}
void CargoDeliverySystem::createAndAddTrucks(std::string trucks){
    // This function takes trucks file as an argument,creates our trucks and adds them appproppriate stations.
    std::string line;
    std::vector<std::string> lines;
    std::ifstream truckFile(trucks);
    if(truckFile.is_open()){
        while(truckFile.good()){
            getline(truckFile,line);
            lines.push_back(line);
        }
        truckFile.close();
    }
    else {
        std::cout << "Unable To Open File";  
    }
    for(int j=0 ;j<lines.size();j++){
        std::string attributes[3];
        std::istringstream ss(lines.at(j));
        std::string attribute;
        int index = 0;
        while(ss >> attribute){
            attributes[index] = attribute;
            index++;
        }
        double power;
        std::string _power = attributes[2];
        power = std::stod(_power);
        Truck newTruck(attributes[0],attributes[1],power);  // attributes[2] must be a double.
        for(int i=0;i<stations.size();i++){
            if(stations.at(i).getCityName() == newTruck.getCargoStation()){
                stations.at(i).addTruck(newTruck);
            }
        }
    }
}
void CargoDeliverySystem::createAndAddPackages(std::string packages){
    // This function takes packages file as an argument,create packages and add them approppriate stations.
    std::string line;
    std::vector<std::string> lines;
    std::ifstream packageFile(packages);
    if(packageFile.is_open()){
        while(packageFile.good()){
            getline(packageFile,line);
            lines.push_back(line);
        }
        packageFile.close();
    }
    else {
        std::cout << "Unable To Open File";  
    }
    std::string whiteSpace = " ";
    for(size_t i=0;i<lines.size();i++){
        std::string attributes[2];
        std::string line = lines.at(i);
        size_t space = line.find(whiteSpace);
        attributes[0] = line.substr(0,space);
        attributes[1]=line.substr(space+1,line.length()-space-1);
        Package newPackage(attributes[0],attributes[1]);
        for(size_t j=0;j<stations.size();j++){
            if(stations.at(j).getCityName() == newPackage.getCargoStation()){
                stations.at(j).addPackage(newPackage);
                break;
            }
        }
    }
}
void CargoDeliverySystem::completeDelivery(std::string newMission){
    size_t first = newMission.find("-",0);
    size_t second = newMission.find("-",first+1);
    size_t third = newMission.find("-",second+1);
    size_t fourth = newMission.find("-",third+1);
    size_t fifth = newMission.find("-",fourth+1);
    
    std::string startingStation = newMission.substr(0,first);
    std::string midwayStation = newMission.substr(first+1,second-first-1);
    std::string targetStation = newMission.substr(second+1,third-second-1);
    std::string firstPackages = newMission.substr(third+1,fourth-third-1);
    std::string secondPackages = newMission.substr(fourth+1,fifth-fourth-1);
    std::string ourIndices = newMission.substr(fifth+1,newMission.length()-fifth-1);
    
    std::vector<int> allIndices;
    std::stringstream s_stream(ourIndices); //create string stream from the string
    while(s_stream.good()) {
        std::string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        int index;
        std::istringstream(substr) >> index;
        allIndices.push_back(index);
   }
   // Delivery is is starting---------------------------------------------------------
   Truck selectedTruck; // I am creating this variable here to prevent errors when I try to add truck to the last station.
   PackageNode *lastNode;
   for(size_t j=0;j<stations.size();j++){
       if(stations.at(j).getCityName() == startingStation){
           PackageNode *truck = new PackageNode();
           selectedTruck = stations.at(j).useTruck();  // dequeue 
           truck->package = selectedTruck;
           truck->previous = nullptr;
           truck->next = nullptr;
           head = truck;  // Our doubly linked list will always have a truck in its head node.
           lastNode = truck;
           int numberOfPackages1;  // Number of packages we take from starting station.
           std::istringstream(firstPackages) >> numberOfPackages1;  // I am converting string form to the int form.
           for(int i=0;i<numberOfPackages1;i++){  // New for loop to take all packages from selected station.
               PackageNode *newNode = new PackageNode();
               Package takenPackage =  stations.at(j).takePackage();
               newNode->package = takenPackage;  //For every step of our for loop,we take only one package from selected station's stack.
               lastNode->next = newNode;
               newNode->previous = lastNode;
               newNode->next = nullptr;
               lastNode=newNode; // From now on,our last node is our new node.
           }
        }
   }
   // All packages was taken from starting station.
   // ------------------------------------------------------------------------------------------
   // Now,I will take packages from midway station and leave some packages taken before.
   
   for(size_t k=0;k<stations.size();k++)  // New for loop to find our midway station.
    {
       if(stations.at(k).getCityName() == midwayStation)
        {
           int numberOfPackages2; // Number of packages we take from starting station.
           std::istringstream(secondPackages) >> numberOfPackages2;  // I am converting it to the int.
            for(int i = 0;i<numberOfPackages2;i++)
            {
               PackageNode *newNode = new PackageNode();
               Package midwayPackage =  stations.at(k).takePackage(); 
               newNode->package = midwayPackage;  //takeTop and pop again.
               lastNode->next = newNode;
               newNode->previous = lastNode;
               newNode->next = nullptr;
               lastNode = newNode;
           }
           // New packages are taken from midway station.
          // -----------------------------------------------------------------------------------------------
           std::vector<PackageNode *> nodePointers; //Vector of pointers.They will point to the nodes at specified indexes.
           for(size_t i = 0 ;i<allIndices.size();i++){
               int control = -1; // This is our control index and it starts from -1.Because our head node will always has a truck and it is not counted.
               int index = allIndices.at(i);
               Package newPackage;
               PackageNode *temp1 = head;
               while(control < index){  // Traversin our doubly linked list to assign temp1 approppriate node.
                   temp1 = temp1->next;
                   control ++;
               }
               nodePointers.push_back(temp1); // I'm pushing back temp1 to delete it later.
               newPackage = temp1->package;  //I'm taking package from temp1
               stations.at(k).addPackage(newPackage);  // Finally,push it to the midway station's stack.
           }
           int _size = nodePointers.size();
           for(size_t n=0; n<_size;n++){
               if(nodePointers.at(n) == lastNode){
                   lastNode = lastNode->previous;
                   lastNode->next = nullptr;
                   delete nodePointers.at(n);
               }
               else{
                   nodePointers.at(n)->next->previous = nodePointers.at(n)->previous;
                   nodePointers.at(n)->previous->next = nodePointers.at(n)->next;

               }
           }
        }
    }
    // I'am leaving our selected truck and all remaining packages to the last station.
    for(size_t y=0;y<stations.size();y++){
        if(stations.at(y).getCityName() == targetStation){
            stations.at(y).addTruck(selectedTruck);
            head = head->next;
            PackageNode *temp = head;
            while(true){
                if(temp){
                    // Traversing all packages 
                    Package package = temp->package;
                    stations.at(y).addPackage(package);
                    temp = temp->next;
                }
                else{
                    break;
                }
            }
        }
    }
}
void CargoDeliverySystem::shareCurrentStatus(std::string resultFile){
    // Takes result.txt that comes from command line and writes all station's content in it.
    std::string result="";
    for(size_t r=0;r<stations.size();r++){
        result+= stations.at(r).display();
    }
    std::ofstream output(resultFile);
    output << result;
    output.close();

}
CargoDeliverySystem::~CargoDeliverySystem()
{
    delete head;
}

