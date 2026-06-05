#ifndef BUS_H
#define BUS_H

// DERIVED CLASS (FROM VEHICLE)

#include "Vehicle.h"
#include <fstream>

class Bus : public Vehicle {
private:
      bool hasAC;
public:
     //Constructor and Destructor
     Bus(int vehicleId, string vehicleNumber, int capacity, string driverName, bool hasAC);
     ~Bus();

     //Implementation of all pure virtual functions from Vehicle 
     void displayInfo() const override;
     string getType() const override;
     void saveToFile(ofstream &out) const override;

     //Getter
     bool getHasAC() const;
};
#endif
