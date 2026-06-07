#include "Bus.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor & Destructor

Bus::Bus(int vehicleId, string vehicleNumber, int capacity,
         string driverName, bool hasAC)
    : Vehicle(vehicleId, vehicleNumber, capacity, driverName)
{
    this->hasAC = hasAC;
}

Bus::~Bus() {}

// Pure Virtual Implementations

void Bus::displayInfo() const {
    cout << "\n┌──────────────────────────────────┐\n";
    cout <<   "│            BUS DETAILS           │\n";
    cout <<   "├──────────────────────────────────┤\n";
    cout <<   "│ ID          : " << vehicleId                            << "\n";
    cout <<   "│ Number      : " << vehicleNumber                        << "\n";
    cout <<   "│ AC          : " << (hasAC ? "Yes" : "No")              << "\n";
    cout <<   "│ Driver      : " << driverName                           << "\n";
    cout <<   "│ Capacity    : " << capacity                             << "\n";
    cout <<   "│ Occupied    : " << seatsOccupied                        << "\n";
    cout <<   "│ Available   : " << getAvailableSeats()                   << "\n";
    cout <<   "│ Status      : " << (isActive ? "Active" : "Inactive")   << "\n";
    cout <<   "└──────────────────────────────────┘\n";
}

string Bus::getType() const {
    return "Bus";
}

void Bus::saveToFile(ofstream& out) const {
    if (!out.is_open())
        throw runtime_error("File stream not open. Cannot save Bus.");

    // Format: BUS|vehicleId|vehicleNumber|capacity|seatsOccupied|driverName|isActive|hasAC
    out << "BUS|"
        << vehicleId     << "|"
        << vehicleNumber << "|"
        << capacity      << "|"
        << seatsOccupied << "|"
        << driverName    << "|"
        << isActive      << "|"
        << hasAC         << "\n";
}

// Getter

bool Bus::getHasAC() const {
    return hasAC;
}