#ifndef TRANSPORTPASS_H
#define TRANSPORTPASS_H

#include "Bill.h"
#include <string>
#include <fstream>
using namespace std;

class TransportPass {
private:
    int    passId;
    int    studentId;
    int    routeId;
    int    vehicleId;
    string status;
    string applyDate;
    Bill*  bill;
public:
    TransportPass(int passId, int studentId, int routeId, int vehicleId,
                  string applyDate, float monthlyFee, string dueDate);
    ~TransportPass();

    TransportPass(const TransportPass& other);
    TransportPass& operator=(const TransportPass& other);

    void approve();
    void reject();
    void cancel();

    void displayPass()             const;
    void saveToFile(ofstream& out) const;

    int    getPassId()    const;
    int    getStudentId() const;
    int    getRouteId()   const;
    int    getVehicleId() const;
    string getStatus()    const; 
    Bill*  getBill()      const;
};
#endif