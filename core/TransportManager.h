#ifndef TRANSPORTMANAGER_H
#define TRANSPORTMANAGER_H

// CENTRAL CONTROLLER CLASS 

#include "User.h"
#include "Vehicle.h"
#include "Route.h"
#include "TransportPass.h"
#include "DynamicArray.h"
#include <string>
using namespace std;

class TransportManager {
private:
     DynamicArray<User*>             users;
     DynamicArray<Vehicle*>          vehicles;
     DynamicArray<Route*>            routes;
     DynamicArray<TransportPass*>    passes;

     //Auto-incrementing ID counters
     int nextUserId;
     int nextVehicleId;
     int nextRouteId;
     int nextPassId;
public:
     //Constructor and Destructor
     TransportManager();
     ~TransportManager();

     //ID Generators
     int getNextUserId();
     int getNextVehicleId();
     int getNextRouteId();
     int getNextPassId();

     // User Management
     bool registerUser(User* user);
     User* login(string email, string password);
     User* findUserById(int id);
     
     // Vehicle Management
     void addVehicle(Vehicle* v);
     bool removeVehicle(int vehicleId);
     Vehicle* findVehicleById(int vehicleId);
     void displayAllVehicles() const;

     // Route Management
     void addRoute(Route* r);
     bool assignVehicleToRoute(int routeId, int vehicleId);
     Route* findRouteById(int routeId);
     void displayAllRoutes() const;

     // Transport Registration 
     int  applyForTransport(int studentId, int routeId, float monthlyFee);
     bool approvePass(int passId);
     bool rejectPass(int passId);
     bool cancelPass(int passId);
     void displayPendingApplications() const;
     TransportPass* findPassByStudentId(int studentId);

     // Billing
     void applyLateFines(float fineAmount);          
     void generateRevenueReport() const;
     void generateRouteReport() const;

     // File I/O
     void saveAllDate() const;
     void loadAllData();
};
#endif 