#ifndef BUS_H
#define BUS_H

#include "Vehicle.h"   

class Bus : public Vehicle {
private:
    bool hasAC;
public:
    Bus(int vehicleId, string vehicleNumber, int capacity, string driverName, bool hasAC);
    ~Bus();

    void   displayInfo()             const override;
    string getType()                 const override;
    void   saveToFile(ofstream& out) const override;

    bool getHasAC() const;
};
#endif