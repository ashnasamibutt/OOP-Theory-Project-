#ifndef BILL_H
#define BILL_H

#include <string>
#include <fstream>
using namespace std;

class Bill {
private:
     int billId;
     float monthlyFee;
     float lateFine;
     bool isPaid;
     string dueDate;
     string paymentDate;
public:
     //Constructor and Destructor
     Bill(int billId, float monthlyFee, string dueDate);
     ~Bill();

     //Core Methods
     void applyLateFine(float fineAmount);
     void markAsPaid(string paymentDate);
     float getTotalAmount() const;
     void displayBill() const;
     void saveToFile(ofstream &out) const;

     //Getters
     int getBillId() const;
     float getMonthlyFee() const;
     float getLateFine() const;
     bool getIsPaid() const;
     string getDueDate() const;

     //Operator Overloading
     bool operator<(const Bill& other) const;
};
#endif