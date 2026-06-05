#ifndef TRANSPORTPASS_H
#define TRANSPORTPASS_H

#include "Bill.h"
#include <string>
#include <fstream>
using namespace std;

class TransportPass {
private:
     int passId;
     int studentId;
     int routeId;
     int vehicleId;
     string status;
     string applyDate;

     Bill* bill;
public: 
     //Constructor and Destructor
     TransportPass(int passId, int studentId, int routeId, int vehicleId, string applyDate, float monthlyFee, string dueDate);
     ~TransportPass();

     //Deep Copy Constructor 
     TransportPass(const TransportPass& other);

     //Deep Assignment Operator
     TransportPass& operator=(const TransportPass& other);

     //Status Methods
     void approve();
     void reject();
     void cancel();

     //Display / Save 
     void displayPass() const;
     void saveToFile(ofstream& out) const;

     //Getters
     int getPassId() const;
     int getStudentId() const;
     int getRouteId() const;
     int getVehicleId() const;
     string gtStatus() const;
     Bill* getBill() const;   
};
#endif
