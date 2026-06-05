#ifndef ROUTE_H
#define ROUTE_H

// STANDALONE CLASS

#include <string>
#include <fstream>
using namespace std;

class Route {
private:
     int routeId;
     string startPoint;
     string endPoint;
     float distanceKm;
     int assignedVehicleId;
public:
     //Constructor and Destructor
     Route(int routeId, string startPoint, string endPoint, float distanceKm);
     ~Route();

     //Copy Constructor
     Route(const Route& other);

     //Assignment Operator
     Route& operator=(const Route& other);

     //Core Methods
     void displayInfo() const;
     void assignVehicle(int vehicleId);
     void removeVehicle();
     void saveToFile(ofstream& out) const;

     //Getters
     int getRouteId() const;
     string getStartPoint() const;
     string getEndPoint() const;
     float getdistanceKm() const;
     int getAssignedVehicleId() const;
};
#endif