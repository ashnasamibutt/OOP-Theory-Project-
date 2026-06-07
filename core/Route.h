#ifndef ROUTE_H
#define ROUTE_H

// STANDALONE CLASS

#include <string>
#include <fstream>
using namespace std;

class Route {
private:
    int    routeId;
    string startPoint;
    string endPoint;
    float  distanceKm;
    int    assignedVehicleId;
public:
    Route(int routeId, string startPoint, string endPoint, float distanceKm);
    ~Route();

    Route(const Route& other);
    Route& operator=(const Route& other);

    void displayInfo()             const;
    void assignVehicle(int vehicleId);
    void removeVehicle();
    void saveToFile(ofstream& out) const;

    int    getRouteId()           const;
    string getStartPoint()        const;
    string getEndPoint()          const;
    float  getDistanceKm()        const; 
    int    getAssignedVehicleId() const;
};
#endif