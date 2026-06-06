#ifndef VEHICLE_H
#define VEHICLE_H

// ABSTRACT BASE CLASS 

#include <string>
#include <fstream>
using namespace std;

class Vehicle {
protected:
    int vehicleId;
    string vehicleNumber;
    int capacity;
    int seatsOccupied;
    string driverName;
    bool isActive;
public:
   //Constructor and Destructor
   Vehicle(int vehicleId, string vehicleNumber, int capacity, string driverName);
   virtual ~Vehicle();

   //Pure virtual functions
   virtual void displayInfo() const = 0;
   virtual string getType() const = 0;
   virtual void saveToFile(ofstream &out) const = 0;

   //Concrete methods
    bool hasAvailableSeat() const;
    bool bookSeat();
    bool releaseSeat();

    //Getters and Setters
    int getVehicleId() const;
    string getVehicleNumber() const;
    int getCapacity() const;
    int getSeatsOccupied() const;
    int getAvailableSeats() const;
    string getDriverName() const;
    bool getIsActive() const;

    void setIsActive(bool val);
    void setDriverName(string name);

    //Operator Overloading
    bool operator>(const Vehicle &other) const;
};
#endif
