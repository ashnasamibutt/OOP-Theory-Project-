#ifndef BILL_H
#define BILL_H

#include <string>
#include <fstream>
using namespace std;

class Bill {
private:
    int    billId;
    float  monthlyFee;
    float  lateFine;
    bool   isPaid;
    string dueDate;
    string paymentDate;
public:
    Bill(int billId, float monthlyFee, string dueDate);
    ~Bill();

    void  applyLateFine(float fineAmount);
    void  markAsPaid(string paymentDate);
    float getTotalAmount()         const;
    void  displayBill()            const;
    void  saveToFile(ofstream& out) const;

    int    getBillId()      const;
    float  getMonthlyFee()  const;
    float  getLateFine()    const;
    bool   getIsPaid()      const;
    string getDueDate()     const;
    string getPaymentDate() const; 

    bool operator<(const Bill& other) const;
};
#endif