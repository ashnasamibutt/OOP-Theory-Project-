#ifndef TRANSPORTMANAGER_H
#define TRANSPORTMANAGER_H

// AGGREGATOR CLASS
// Owns: Vehicle** (aggregation), Route** (aggregation), TransportPass** (aggregation)

#include "../core/DynamicArray.h"
#include "../vehicles/Vehicle.h"
#include "../core/Route.h"
#include "../core/TransportPass.h"
using namespace std;

class TransportManager {
private:
    DynamicArray<Vehicle*>       vehicles;
    DynamicArray<Route*>         routes;
    DynamicArray<TransportPass*> passes;

public:
    TransportManager();
    ~TransportManager();

    // Vehicle Management
    void     addVehicle(Vehicle* vehicle);
    bool     removeVehicle(int vehicleId);
    Vehicle* findVehicleById(int vehicleId)    const;
    void     displayAllVehicles()              const;

    // Route Management
    void   addRoute(Route* route);
    bool   removeRoute(int routeId);
    Route* findRouteById(int routeId)          const;
    void   assignVehicleToRoute(int vehicleId, int routeId);
    void   displayAllRoutes()                  const;

    // Pass Management
    void           addPass(TransportPass* pass);
    TransportPass* findPassById(int passId)           const;
    TransportPass* findPassByStudentId(int studentId) const;
    void           approvePass(int passId);
    void           rejectPass(int passId);
    void           displayAllPasses()                 const;
    void           displayPendingPasses()             const;

    // Persistence
    void saveAll() const;
    void loadAll();

    // Getters
    int getVehicleCount() const;
    int getRouteCount()   const;
    int getPassCount()    const;
};

#endif