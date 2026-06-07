#ifndef DRIVER_H
#define DRIVER_H

// DERIVED CLASS (FROM USER)

#include "User.h"

class Driver : public User {
private:
    string licenseNumber;      
    int    assignedVehicleId;
    bool   isAvailable;
public:
    Driver(int id, string name, string email, string password, string licenseNumber); 
    ~Driver();

    void   displayInfo()             const override;
    string getRole()                 const override; 
    void   saveToFile(ofstream& out) const override;

    string getLicenseNumber()             const; 
    int    getAssignedVehicleId()         const;
    bool   getIsAvailable()               const;

    void   setAssignedVehicleId(int vehicleId);
    void   setIsAvailable(bool val);
};
#endif