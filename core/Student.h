#ifndef STUDENT_H
#define STUDENT_H

// DERIVED CLASS (FROM USER)

#include "User.h"
#include <fstream>

class Student : public User {
private:
     string rollNumber;
     string department;
     bool hasTRansportPass;
public:
     //Constructor and Destructor
     Student(int id, string name, string email, string password, string rollNumber, string department);
     ~Student();

     //Implementing all pure virtual functions form User 
     void displayInfo() const override;
     string getrole() const override;
     void saveToFile(ofstream &out) const override;

     //Getters and Setters
     string getRollNumber() const;
     string getDepartment() const;
     bool getHasTransportPass() const;
     void setHasTransportPass(bool val);
};
#endif
