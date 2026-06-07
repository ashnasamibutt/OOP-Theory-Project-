#include "Route.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor & Destructor

Route::Route(int routeId, string startPoint, string endPoint, float distanceKm)
{
    if (routeId <= 0)
        throw invalid_argument("Route ID must be positive.");
    if (startPoint.empty())
        throw invalid_argument("Start point cannot be empty.");
    if (endPoint.empty())
        throw invalid_argument("End point cannot be empty.");
    if (startPoint == endPoint)
        throw invalid_argument("Start and end points cannot be the same.");
    if (distanceKm <= 0)
        throw invalid_argument("Distance must be greater than zero.");

    this->routeId           = routeId;
    this->startPoint        = startPoint;
    this->endPoint          = endPoint;
    this->distanceKm        = distanceKm;
    this->assignedVehicleId = -1;   // -1 = no vehicle assigned yet
}

Route::~Route() {}

// Copy Constructor & Assignment Operator

Route::Route(const Route& other)
    : routeId(other.routeId), startPoint(other.startPoint),
      endPoint(other.endPoint), distanceKm(other.distanceKm),
      assignedVehicleId(other.assignedVehicleId)
{}

Route& Route::operator=(const Route& other) {
    if (this == &other) return *this;
    routeId           = other.routeId;
    startPoint        = other.startPoint;
    endPoint          = other.endPoint;
    distanceKm        = other.distanceKm;
    assignedVehicleId = other.assignedVehicleId;
    return *this;
}

 //Core Methods

void Route::displayInfo() const {
    cout << "\n┌──────────────────────────────────┐\n";
    cout <<   "│           ROUTE DETAILS          │\n";
    cout <<   "├──────────────────────────────────┤\n";
    cout <<   "│ Route ID   : " << routeId                                                          << "\n";
    cout <<   "│ From       : " << startPoint                                                        << "\n";
    cout <<   "│ To         : " << endPoint                                                          << "\n";
    cout <<   "│ Distance   : " << distanceKm << " km"                                              << "\n";
    cout <<   "│ Vehicle    : " << (assignedVehicleId == -1
                                     ? "Not Assigned"
                                     : to_string(assignedVehicleId))                                  << "\n";
    cout <<   "└──────────────────────────────────┘\n";
}

void Route::assignVehicle(int vehicleId) {
    if (vehicleId <= 0)
        throw invalid_argument("Invalid vehicle ID.");
    if (assignedVehicleId != -1)
        cout << "[Warning] Route " << routeId << " already has vehicle ID "
             << assignedVehicleId << ". Reassigning to ID " << vehicleId << ".\n";
    assignedVehicleId = vehicleId;
}

void Route::removeVehicle() {
    if (assignedVehicleId == -1) {
        cout << "[Warning] Route " << routeId << " has no assigned vehicle.\n";
        return;
    }
    assignedVehicleId = -1;
}

void Route::saveToFile(ofstream& out) const {
    if (!out.is_open())
        throw runtime_error("File stream not open. Cannot save Route.");

    // Format: ROUTE|routeId|startPoint|endPoint|distanceKm|assignedVehicleId
    out << "ROUTE|"
        << routeId           << "|"
        << startPoint        << "|"
        << endPoint          << "|"
        << distanceKm        << "|"
        << assignedVehicleId << "\n";
}

// Getters

int    Route::getRouteId()           const { return routeId;           }
string Route::getStartPoint()        const { return startPoint;        }
string Route::getEndPoint()          const { return endPoint;          }
float  Route::getDistanceKm()        const { return distanceKm;        }
int    Route::getAssignedVehicleId() const { return assignedVehicleId; }