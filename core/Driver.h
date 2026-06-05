#ifndef DRIVER_H
#define DRIVER_H

// DERIVED CLASS (FROM USER)

#include "User.h"
#include <fstream>

class Driver : public User {
private:
     string licenseNumber;
     int assignedVehicleId;
     bool isAvailable;
public:
      //Constructor and Destructor 
      Driver(int id, string name, string email, string password, string liceseNumber);
      ~Driver();

     //Implementing all pure virtual functions form User 
     void displayInfo() const override;
     string getrole() const override;
     void saveToFile(ofstream &out) const override;

     // Getters and Setters
     string getLiceseNumber() const;
     int getAssignedVehicleId() const;
     bool getIsAvailable() const;

     void setAssignedVehicleId(int vehicleId);
     void setIsAvailable(bool val);
};
#endif