#include "Van.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor & Destructor

Van::Van(int vehicleId, string vehicleNumber, int capacity,
         string driverName, string vanModel)
    : Vehicle(vehicleId, vehicleNumber, capacity, driverName)
{
    if (vanModel.empty())
        throw invalid_argument("Van model cannot be empty.");
    this->vanModel = vanModel;
}

Van::~Van() {}

// Pure Virtual Implementations

void Van::displayInfo() const {
    cout << "\n┌──────────────────────────────────┐\n";
    cout <<   "│            VAN DETAILS           │\n";
    cout <<   "├──────────────────────────────────┤\n";
    cout <<   "│ ID          : " << vehicleId                            << "\n";
    cout <<   "│ Number      : " << vehicleNumber                        << "\n";
    cout <<   "│ Model       : " << vanModel                             << "\n";
    cout <<   "│ Driver      : " << driverName                           << "\n";
    cout <<   "│ Capacity    : " << capacity                             << "\n";
    cout <<   "│ Occupied    : " << seatsOccupied                        << "\n";
    cout <<   "│ Available   : " << getAvailableSeats()                   << "\n";
    cout <<   "│ Status      : " << (isActive ? "Active" : "Inactive")   << "\n";
    cout <<   "└──────────────────────────────────┘\n";
}

string Van::getType() const {
    return "Van";
}

void Van::saveToFile(ofstream& out) const {
    if (!out.is_open())
        throw runtime_error("File stream not open. Cannot save Van.");

    // Format: VAN|vehicleId|vehicleNumber|capacity|seatsOccupied|driverName|isActive|vanModel
    out << "VAN|"
        << vehicleId     << "|"
        << vehicleNumber << "|"
        << capacity      << "|"
        << seatsOccupied << "|"
        << driverName    << "|"
        << isActive      << "|"
        << vanModel      << "\n";
}
// Getter

string Van::getVanModel() const {
    return vanModel;
}