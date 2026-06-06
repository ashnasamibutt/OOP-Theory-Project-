#ifndef VAN_H
#define VAN_H

#include "Vehicle.h"   // <fstream> already comes through Vehicle.h ✅ REMOVED duplicate

class Van : public Vehicle {
private:
    string vanModel;
public:
    Van(int vehicleId, string vehicleNumber, int capacity, string driverName, string vanModel);
    ~Van();

    void   displayInfo()             const override;
    string getType()                 const override;
    void   saveToFile(ofstream& out) const override;

    string getVanModel() const;
};
#endif