#include "TransportManager.h"
#include "Van.h"
#include "Bus.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

// Constructor & Destructor

TransportManager::TransportManager()
{
    vehicleCapacity = 10;
    vehicleCount    = 0;
    vehicles        = new Vehicle*[vehicleCapacity];

    routeCapacity   = 10;
    routeCount      = 0;
    routes          = new Route*[routeCapacity];

    passCapacity    = 10;
    passCount       = 0;
    passes          = new TransportPass*[passCapacity];
}

TransportManager::~TransportManager() {
    for (int i = 0; i < vehicleCount; i++) delete vehicles[i];
    delete[] vehicles;

    for (int i = 0; i < routeCount; i++) delete routes[i];
    delete[] routes;

    for (int i = 0; i < passCount; i++) delete passes[i];
    delete[] passes;
}

// Resize Helpers

void TransportManager::resizeVehicles() {
    vehicleCapacity *= 2;
    Vehicle** temp = new Vehicle*[vehicleCapacity];
    for (int i = 0; i < vehicleCount; i++) temp[i] = vehicles[i];
    delete[] vehicles;
    vehicles = temp;
}

void TransportManager::resizeRoutes() {
    routeCapacity *= 2;
    Route** temp = new Route*[routeCapacity];
    for (int i = 0; i < routeCount; i++) temp[i] = routes[i];
    delete[] routes;
    routes = temp;
}

void TransportManager::resizePasses() {
    passCapacity *= 2;
    TransportPass** temp = new TransportPass*[passCapacity];
    for (int i = 0; i < passCount; i++) temp[i] = passes[i];
    delete[] passes;
    passes = temp;
}

// Vehicle Management

void TransportManager::addVehicle(Vehicle* vehicle) {
    if (!vehicle)
        throw invalid_argument("Cannot add a null vehicle.");
    if (findVehicleById(vehicle->getVehicleId())) {
        cout << "[Error] Vehicle ID " << vehicle->getVehicleId() << " already exists.\n";
        return;
    }
    if (vehicleCount == vehicleCapacity) resizeVehicles();
    vehicles[vehicleCount++] = vehicle;
    cout << "[Info] Vehicle ID " << vehicle->getVehicleId() << " ("
         << vehicle->getType() << ") added.\n";
}

bool TransportManager::removeVehicle(int vehicleId) {
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i]->getVehicleId() == vehicleId) {
            if (vehicles[i]->getSeatsOccupied() > 0) {
                cout << "[Error] Vehicle has active passengers. Cannot remove.\n";
                return false;
            }
            delete vehicles[i];
            vehicles[i] = vehicles[--vehicleCount];
            cout << "[Info] Vehicle ID " << vehicleId << " removed.\n";
            return true;
        }
    }
    cout << "[Error] Vehicle ID " << vehicleId << " not found.\n";
    return false;
}

Vehicle* TransportManager::findVehicleById(int vehicleId) const {
    for (int i = 0; i < vehicleCount; i++)
        if (vehicles[i]->getVehicleId() == vehicleId)
            return vehicles[i];
    return nullptr;
}

void TransportManager::displayAllVehicles() const {
    if (vehicleCount == 0) { cout << "[Info] No vehicles registered.\n"; return; }
    cout << "\n=== ALL VEHICLES (" << vehicleCount << ") ===\n";
    for (int i = 0; i < vehicleCount; i++)
        vehicles[i]->displayInfo();
}

// Route Management

void TransportManager::addRoute(Route* route) {
    if (!route)
        throw invalid_argument("Cannot add a null route.");
    if (findRouteById(route->getRouteId())) {
        cout << "[Error] Route ID " << route->getRouteId() << " already exists.\n";
        return;
    }
    if (routeCount == routeCapacity) resizeRoutes();
    routes[routeCount++] = route;
    cout << "[Info] Route ID " << route->getRouteId() << " added.\n";
}

bool TransportManager::removeRoute(int routeId) {
    for (int i = 0; i < routeCount; i++) {
        if (routes[i]->getRouteId() == routeId) {
            delete routes[i];
            routes[i] = routes[--routeCount];
            cout << "[Info] Route ID " << routeId << " removed.\n";
            return true;
        }
    }
    cout << "[Error] Route ID " << routeId << " not found.\n";
    return false;
}

Route* TransportManager::findRouteById(int routeId) const {
    for (int i = 0; i < routeCount; i++)
        if (routes[i]->getRouteId() == routeId)
            return routes[i];
    return nullptr;
}

void TransportManager::assignVehicleToRoute(int vehicleId, int routeId) {
    Vehicle* vehicle = findVehicleById(vehicleId);
    Route*   route   = findRouteById(routeId);

    if (!vehicle) { cout << "[Error] Vehicle ID " << vehicleId << " not found.\n"; return; }
    if (!route)   { cout << "[Error] Route ID "   << routeId   << " not found.\n"; return; }
    if (!vehicle->getIsActive()) { cout << "[Error] Vehicle is inactive.\n";        return; }

    route->assignVehicle(vehicleId);
    cout << "[Info] Vehicle ID " << vehicleId
         << " assigned to Route ID " << routeId << ".\n";
}

void TransportManager::displayAllRoutes() const {
    if (routeCount == 0) { cout << "[Info] No routes registered.\n"; return; }
    cout << "\n=== ALL ROUTES (" << routeCount << ") ===\n";
    for (int i = 0; i < routeCount; i++)
        routes[i]->displayInfo();
}

// Pass Management

void TransportManager::addPass(TransportPass* pass) {
    if (!pass)
        throw invalid_argument("Cannot add a null transport pass.");

    if (findPassByStudentId(pass->getStudentId())) {
        cout << "[Error] Student ID " << pass->getStudentId()
             << " already has an active pass.\n";
        return;
    }

    Vehicle* vehicle = findVehicleById(pass->getVehicleId());
    if (!vehicle)               { cout << "[Error] Vehicle not found.\n";              return; }
    if (!vehicle->hasAvailableSeat()) { cout << "[Error] Vehicle is at full capacity.\n"; return; }

    if (passCount == passCapacity) resizePasses();
    passes[passCount++] = pass;
    cout << "[Info] Application submitted. Pass ID: " << pass->getPassId()
         << " — awaiting admin approval.\n";
}

TransportPass* TransportManager::findPassById(int passId) const {
    for (int i = 0; i < passCount; i++)
        if (passes[i]->getPassId() == passId)
            return passes[i];
    return nullptr;
}

TransportPass* TransportManager::findPassByStudentId(int studentId) const {
    for (int i = 0; i < passCount; i++)
        if (passes[i]->getStudentId() == studentId &&
            passes[i]->getStatus()    != "Cancelled" &&
            passes[i]->getStatus()    != "Rejected")
            return passes[i];
    return nullptr;
}

void TransportManager::approvePass(int passId) {
    TransportPass* pass = findPassById(passId);
    if (!pass) { cout << "[Error] Pass ID " << passId << " not found.\n"; return; }

    Vehicle* vehicle = findVehicleById(pass->getVehicleId());
    if (!vehicle) { cout << "[Error] Vehicle for this pass no longer exists.\n"; return; }

    if (!vehicle->bookSeat()) return;   // bookSeat() prints its own capacity error
    pass->approve();
}

void TransportManager::rejectPass(int passId) {
    TransportPass* pass = findPassById(passId);
    if (!pass) { cout << "[Error] Pass ID " << passId << " not found.\n"; return; }
    pass->reject();
}

void TransportManager::displayAllPasses() const {
    if (passCount == 0) { cout << "[Info] No transport passes found.\n"; return; }
    cout << "\n=== ALL PASSES (" << passCount << ") ===\n";
    for (int i = 0; i < passCount; i++)
        passes[i]->displayPass();
}

void TransportManager::displayPendingPasses() const {
    cout << "\n=== PENDING APPLICATIONS ===\n";
    bool found = false;
    for (int i = 0; i < passCount; i++) {
        if (passes[i]->getStatus() == "Pending") {
            passes[i]->displayPass();
            found = true;
        }
    }
    if (!found) cout << "[Info] No pending applications.\n";
}

// Persistence — Save

void TransportManager::saveAll() const {
    ofstream vFile("vehicles.txt");
    if (!vFile.is_open()) cout << "[Error] Could not open vehicles.txt.\n";
    else {
        for (int i = 0; i < vehicleCount; i++) vehicles[i]->saveToFile(vFile);
        vFile.close();
    }

    ofstream rFile("routes.txt");
    if (!rFile.is_open()) cout << "[Error] Could not open routes.txt.\n";
    else {
        for (int i = 0; i < routeCount; i++) routes[i]->saveToFile(rFile);
        rFile.close();
    }

    ofstream pFile("registrations.txt");
    if (!pFile.is_open()) cout << "[Error] Could not open registrations.txt.\n";
    else {
        for (int i = 0; i < passCount; i++) passes[i]->saveToFile(pFile);
        pFile.close();
    }

    cout << "[Info] All data saved successfully.\n";
}

// Persistence — Load

void TransportManager::loadAll() {

    // Vehicles

    ifstream vFile("vehicles.txt");
    if (vFile.is_open()) {
        string line;
        while (getline(vFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string type;
            getline(ss, type, '|');

            if (type == "VAN") {
                string vid, vnum, cap, seats, drv, active, model;
                getline(ss, vid,    '|');  getline(ss, vnum,   '|');
                getline(ss, cap,    '|');  getline(ss, seats,  '|');
                getline(ss, drv,    '|');  getline(ss, active, '|');
                getline(ss, model,  '|');

                Van* van = new Van(stoi(vid), vnum, stoi(cap), drv, model);
                for (int i = 0; i < stoi(seats); i++) van->bookSeat();
                van->setIsActive(stoi(active));
                addVehicle(van);
            }
            else if (type == "BUS") {
                string vid, vnum, cap, seats, drv, active, ac;
                getline(ss, vid,    '|');  getline(ss, vnum,   '|');
                getline(ss, cap,    '|');  getline(ss, seats,  '|');
                getline(ss, drv,    '|');  getline(ss, active, '|');
                getline(ss, ac,     '|');

                Bus* bus = new Bus(stoi(vid), vnum, stoi(cap), drv, stoi(ac));
                for (int i = 0; i < stoi(seats); i++) bus->bookSeat();
                bus->setIsActive(stoi(active));
                addVehicle(bus);
            }
        }
        vFile.close();
    }

    //  Routes 

    ifstream rFile("routes.txt");
    if (rFile.is_open()) {
        string line;
        while (getline(rFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string type;
            getline(ss, type, '|');

            if (type == "ROUTE") {
                string rid, start, end, dist, vid;
                getline(ss, rid,   '|');  getline(ss, start, '|');
                getline(ss, end,   '|');  getline(ss, dist,  '|');
                getline(ss, vid,   '|');

                Route* route = new Route(stoi(rid), start, end, stof(dist));
                if (stoi(vid) != -1) route->assignVehicle(stoi(vid));
                addRoute(route);
            }
        }
        rFile.close();
    }

    //  Passes 

    ifstream pFile("registrations.txt");
    if (pFile.is_open()) {
        string line;
        while (getline(pFile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string type;
            getline(ss, type, '|');

            if (type == "PASS") {
                string pid, sid, rid, vid, stat, adate;
                string billId, mfee, lfine, paid, ddate, pdate;

                getline(ss, pid,    '|');  getline(ss, sid,    '|');
                getline(ss, rid,    '|');  getline(ss, vid,    '|');
                getline(ss, stat,   '|');  getline(ss, adate,  '|');
                getline(ss, billId, '|');  getline(ss, mfee,   '|');
                getline(ss, lfine,  '|');  getline(ss, paid,   '|');
                getline(ss, ddate,  '|');  getline(ss, pdate,  '|');

                TransportPass* pass = new TransportPass(
                    stoi(pid), stoi(sid), stoi(rid), stoi(vid),
                    adate, stof(mfee), ddate
                );

                // Restore bill state
                if (stof(lfine) > 0)
                    pass->getBill()->applyLateFine(stof(lfine));
                if (stoi(paid) && !pdate.empty())
                    pass->getBill()->markAsPaid(pdate);

                // Restore pass status (bypass addPass checks during load)
                if      (stat == "Approved")  pass->approve();
                else if (stat == "Rejected")  pass->reject();
                else if (stat == "Cancelled") pass->cancel();

                if (passCount == passCapacity) resizePasses();
                passes[passCount++] = pass;
            }
        }
        pFile.close();
    }

    cout << "[Info] Data loaded — Vehicles: " << vehicleCount
         << " | Routes: " << routeCount
         << " | Passes: " << passCount << "\n";
}

// Getters

int TransportManager::getVehicleCount() const { return vehicleCount; }
int TransportManager::getRouteCount()   const { return routeCount;   }
int TransportManager::getPassCount()    const { return passCount;     }