#include "Bill.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor & Destructor

Bill::Bill(int billId, float monthlyFee, string dueDate)
{
    if (billId <= 0)
        throw invalid_argument("Bill ID must be positive.");
    if (monthlyFee <= 0)
        throw invalid_argument("Monthly fee must be greater than zero.");
    if (dueDate.empty())
        throw invalid_argument("Due date cannot be empty.");

    this->billId      = billId;
    this->monthlyFee  = monthlyFee;
    this->dueDate     = dueDate;
    this->lateFine    = 0.0f;
    this->isPaid      = false;
    this->paymentDate = "";
}

Bill::~Bill() {}

// Core Methods

void Bill::applyLateFine(float fineAmount) {
    if (isPaid) {
        cout << "[Warning] Bill " << billId << " is already paid. Fine not applied.\n";
        return;
    }
    if (fineAmount <= 0)
        throw invalid_argument("Fine amount must be greater than zero.");
    lateFine += fineAmount;
}

void Bill::markAsPaid(string date) {
    if (isPaid) {
        cout << "[Warning] Bill " << billId << " is already marked as paid.\n";
        return;
    }
    if (date.empty())
        throw invalid_argument("Payment date cannot be empty.");
    isPaid      = true;
    paymentDate = date;
}

float Bill::getTotalAmount() const {
    return monthlyFee + lateFine;
}

void Bill::displayBill() const {
    cout << "\n┌──────────────────────────────────┐\n";
    cout <<   "│              INVOICE             │\n";
    cout <<   "├──────────────────────────────────┤\n";
    cout <<   "│ Bill ID     : " << billId                               << "\n";
    cout <<   "│ Monthly Fee : Rs. " << monthlyFee                       << "\n";
    cout <<   "│ Late Fine   : Rs. " << lateFine                         << "\n";
    cout <<   "│ Total       : Rs. " << getTotalAmount()                  << "\n";
    cout <<   "│ Due Date    : " << dueDate                              << "\n";
    cout <<   "│ Status      : " << (isPaid ? "PAID" : "UNPAID")        << "\n";
    if (isPaid)
    cout <<   "│ Paid On     : " << paymentDate                         << "\n";
    cout <<   "└──────────────────────────────────┘\n";
}

void Bill::saveToFile(ofstream& out) const {
    if (!out.is_open())
        throw runtime_error("File stream not open. Cannot save Bill.");

    // Format: BILL|billId|monthlyFee|lateFine|isPaid|dueDate|paymentDate
    out << "BILL|"
        << billId       << "|"
        << monthlyFee   << "|"
        << lateFine     << "|"
        << isPaid       << "|"
        << dueDate      << "|"
        << paymentDate  << "\n";
}
// Getters

int    Bill::getBillId()      const { return billId;      }
float  Bill::getMonthlyFee()  const { return monthlyFee;  }
float  Bill::getLateFine()    const { return lateFine;    }
bool   Bill::getIsPaid()      const { return isPaid;      }
string Bill::getDueDate()     const { return dueDate;     }
string Bill::getPaymentDate() const { return paymentDate; }

bool Bill::operator<(const Bill& other) const {
    return this->getTotalAmount() < other.getTotalAmount();
}
