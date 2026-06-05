#ifndef VAN_H
#define VAN_H

//DERIVED CLASS (FROM VEHICLE)

#include "Vehicle.h"
#include <fstream>

class Van : public Vehicle {
private:
     string vanModel;
public:
     //Constructor and Destructor
     Van(int vehicleId, string vehicleNumber, int capacity, string driverName, string vanModel);
     ~Van();
     
     //Implementation of all pure virtual functions from Vehicle 
     void displayInfo() const override;
     string getType() const override;
     void saveToFile(ofstream &out) const override;

     //Getter
     string getVanModel() const;
};
#endif
