#ifndef PACKAGE_H
#define PACKAGE_H
#include <string>


class Package
{
protected: // I will create a baby class so I am using protected modifier here.
    std::string name;  //Packet name
    std::string cargoStation;  //City name (İstanbul,Ankara...)
public:
    Package();
    Package(const Package &source);
    Package(std::string packageName,std::string stationName);
    std::string getName(){return name;}
    std::string getCargoStation(){return cargoStation;}
    void setName(std::string packageName);
    void setCargoStation(std::string station);
    ~Package();
};

#endif // PACKAGE_H
