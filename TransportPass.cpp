#include "TransportPass.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor & Destructor

TransportPass::TransportPass(int passId, int studentId, int routeId, int vehicleId,
                             string applyDate, float monthlyFee, string dueDate)
{
    if (passId <= 0)    throw invalid_argument("Pass ID must be positive.");
    if (studentId <= 0) throw invalid_argument("Student ID must be positive.");
    if (routeId <= 0)   throw invalid_argument("Route ID must be positive.");
    if (vehicleId <= 0) throw invalid_argument("Vehicle ID must be positive.");
    if (applyDate.empty()) throw invalid_argument("Apply date cannot be empty.");

    this->passId    = passId;
    this->studentId = studentId;
    this->routeId   = routeId;
    this->vehicleId = vehicleId;
    this->applyDate = applyDate;
    this->status    = "Pending";
    this->bill      = new Bill(passId, monthlyFee, dueDate);
}

TransportPass::~TransportPass() {
    delete bill;
    bill = nullptr;
}

// Deep Copy Constructor & Assignment Operator

TransportPass::TransportPass(const TransportPass& other)
    : passId(other.passId), studentId(other.studentId),
      routeId(other.routeId), vehicleId(other.vehicleId),
      status(other.status), applyDate(other.applyDate)
{
    bill = new Bill(*other.bill);
}

TransportPass& TransportPass::operator=(const TransportPass& other) {
    if (this == &other) return *this;
    delete bill;
    passId    = other.passId;
    studentId = other.studentId;
    routeId   = other.routeId;
    vehicleId = other.vehicleId;
    status    = other.status;
    applyDate = other.applyDate;
    bill      = new Bill(*other.bill);
    return *this;
}

// Status Methods

void TransportPass::approve() {
    if (status == "Cancelled" || status == "Rejected") {
        cout << "[Error] Cannot approve a " << status << " pass.\n";
        return;
    }
    if (status == "Approved") {
        cout << "[Warning] Pass " << passId << " is already approved.\n";
        return;
    }
    status = "Approved";
    cout << "[Info] Pass ID " << passId << " approved.\n";
}

void TransportPass::reject() {
    if (status == "Cancelled") {
        cout << "[Error] Cannot reject a cancelled pass.\n";
        return;
    }
    if (status == "Rejected") {
        cout << "[Warning] Pass " << passId << " is already rejected.\n";
        return;
    }
    status = "Rejected";
    cout << "[Info] Pass ID " << passId << " rejected.\n";
}

void TransportPass::cancel() {
    if (status == "Cancelled") {
        cout << "[Warning] Pass " << passId << " is already cancelled.\n";
        return;
    }
    status = "Cancelled";
    cout << "[Info] Pass ID " << passId << " cancelled.\n";
}

// Display & Save

void TransportPass::displayPass() const {
    cout << "\n┌──────────────────────────────────┐\n";
    cout <<   "│         TRANSPORT PASS           │\n";
    cout <<   "├──────────────────────────────────┤\n";
    cout <<   "│ Pass ID    : " << passId     << "\n";
    cout <<   "│ Student ID : " << studentId  << "\n";
    cout <<   "│ Route ID   : " << routeId    << "\n";
    cout <<   "│ Vehicle ID : " << vehicleId  << "\n";
    cout <<   "│ Status     : " << status     << "\n";
    cout <<   "│ Applied On : " << applyDate  << "\n";
    cout <<   "└──────────────────────────────────┘\n";
    if (bill) bill->displayBill();
}

void TransportPass::saveToFile(ofstream& out) const {
    if (!out.is_open())
        throw runtime_error("File stream not open. Cannot save TransportPass.");

    // Format: PASS|passId|studentId|routeId|vehicleId|status|applyDate
    //             |billId|monthlyFee|lateFine|isPaid|dueDate|paymentDate
    out << "PASS|"
        << passId                  << "|"
        << studentId               << "|"
        << routeId                 << "|"
        << vehicleId               << "|"
        << status                  << "|"
        << applyDate               << "|"
        << bill->getBillId()       << "|"
        << bill->getMonthlyFee()   << "|"
        << bill->getLateFine()     << "|"
        << bill->getIsPaid()       << "|"
        << bill->getDueDate()      << "|"
        << bill->getPaymentDate()  << "\n";
}

// Getters

int    TransportPass::getPassId()    const { return passId;    }
int    TransportPass::getStudentId() const { return studentId; }
int    TransportPass::getRouteId()   const { return routeId;   }
int    TransportPass::getVehicleId() const { return vehicleId; }
string TransportPass::getStatus()    const { return status;    }
Bill*  TransportPass::getBill()      const { return bill;      }