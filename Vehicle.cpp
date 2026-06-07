#include "Vehicle.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor & Destructor

Vehicle::Vehicle(int vehicleId, string vehicleNumber, int capacity, string driverName)
{
    if (vehicleId <= 0)
        throw invalid_argument("Vehicle ID must be positive.");
    if (vehicleNumber.empty())
        throw invalid_argument("Vehicle number cannot be empty.");
    if (capacity <= 0)
        throw invalid_argument("Capacity must be greater than zero.");
    if (driverName.empty())
        throw invalid_argument("Driver name cannot be empty.");

    this->vehicleId     = vehicleId;
    this->vehicleNumber = vehicleNumber;
    this->capacity      = capacity;
    this->driverName    = driverName;
    this->seatsOccupied = 0;
    this->isActive      = true;
}

Vehicle::~Vehicle() {}

// Seat Management

bool Vehicle::hasAvailableSeat() const {
    return isActive && (seatsOccupied < capacity);
}

bool Vehicle::bookSeat() {
    if (!isActive) {
        cout << "[Error] Vehicle " << vehicleNumber << " is inactive.\n";
        return false;
    }
    if (seatsOccupied >= capacity) {
        cout << "[Error] Vehicle " << vehicleNumber << " is at full capacity.\n";
        return false;
    }
    seatsOccupied++;
    return true;
}

bool Vehicle::releaseSeat() {
    if (seatsOccupied <= 0) {
        cout << "[Warning] No seats are occupied in vehicle " << vehicleNumber << ".\n";
        return false;
    }
    seatsOccupied--;
    return true;
}

// Getters & Setters

int    Vehicle::getVehicleId()     const { return vehicleId;              }
string Vehicle::getVehicleNumber() const { return vehicleNumber;          }
int    Vehicle::getCapacity()      const { return capacity;               }
int    Vehicle::getSeatsOccupied() const { return seatsOccupied;          }
int    Vehicle::getAvailableSeats()const { return capacity - seatsOccupied; }
string Vehicle::getDriverName()    const { return driverName;             }
bool   Vehicle::getIsActive()      const { return isActive;               }

void Vehicle::setIsActive(bool val) {
    if (!val && seatsOccupied > 0)
        cout << "[Warning] Vehicle " << vehicleNumber << " has "
             << seatsOccupied << " active passenger(s). Deactivating anyway.\n";
    isActive = val;
}

void Vehicle::setDriverName(string name) {
    if (name.empty())
        throw invalid_argument("Driver name cannot be empty.");
    driverName = name;
}

// Operator Overloading

bool Vehicle::operator>(const Vehicle& other) const {
    return this->getAvailableSeats() > other.getAvailableSeats();
}