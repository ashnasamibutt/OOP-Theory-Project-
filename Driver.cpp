#include "Driver.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor & Destructor

Driver::Driver(int id, string name, string email,
               string password, string licenseNumber)
    : User(id, name, email, password, "Driver")
{
    if (licenseNumber.empty())
        throw invalid_argument("License number cannot be empty.");

    bool hasDigit = false;
    for (char c : licenseNumber)
        if (isdigit(c)) { hasDigit = true; break; }
    if (!hasDigit)
        throw invalid_argument("License number must contain at least one digit.");

    this->licenseNumber     = licenseNumber;
    this->assignedVehicleId = -1;    // -1 = no vehicle assigned
    this->isAvailable       = true;
}

Driver::~Driver() {}

// Pure Virtual Implementations

void Driver::displayInfo() const {
    cout << "\n┌──────────────────────────────────┐\n";
    cout <<   "│          DRIVER PROFILE          │\n";
    cout <<   "├──────────────────────────────────┤\n";
    cout <<   "│ ID        : " << id                                          << "\n";
    cout <<   "│ Name      : " << name                                        << "\n";
    cout <<   "│ Email     : " << email                                       << "\n";
    cout <<   "│ License   : " << licenseNumber                               << "\n";
    cout <<   "│ Vehicle   : " << (assignedVehicleId == -1
                                    ? "None"
                                    : to_string(assignedVehicleId))            << "\n";
    cout <<   "│ Available : " << (isAvailable ? "Yes" : "No")               << "\n";
    cout <<   "└──────────────────────────────────┘\n";
}

string Driver::getRole() const {
    return "Driver";
}

void Driver::saveToFile(ofstream& out) const {
    if (!out.is_open())
        throw runtime_error("File stream not open. Cannot save Driver.");

    // Format: DRIVER|id|name|email|password|licenseNumber|assignedVehicleId|isAvailable
    out << "DRIVER|"
        << id                 << "|"
        << name               << "|"
        << email              << "|"
        << password           << "|"
        << licenseNumber      << "|"
        << assignedVehicleId  << "|"
        << isAvailable        << "\n";
}

// Getters & Setters

string Driver::getLicenseNumber()    const { return licenseNumber;     }
int    Driver::getAssignedVehicleId()const { return assignedVehicleId; }
bool   Driver::getIsAvailable()      const { return isAvailable;       }

void Driver::setAssignedVehicleId(int vehicleId) {
    // -1 is the only valid "unassign" value
    if (vehicleId != -1 && vehicleId <= 0)
        throw invalid_argument("Invalid vehicle ID.");

    assignedVehicleId = vehicleId;
    isAvailable       = (vehicleId == -1);
}

void Driver::setIsAvailable(bool val) {
    if (val && assignedVehicleId != -1) {
        cout << "[Warning] Driver still has vehicle ID " << assignedVehicleId
             << " assigned. Unassign the vehicle first.\n";
        return;
    }
    isAvailable = val;
}