#ifndef STUDENT_H
#define STUDENT_H

// DERIVED CLASS (FROM USER)

#include "User.h"

class Student : public User {
private:
    string rollNumber;
    string department;
    bool   hasTransportPass;  

public:
    // Constructor & Destructor
    Student(int id, string name, string email, string password,
            string rollNumber, string department);
    ~Student();

    // Pure Virtual Implementations
    void   displayInfo()             const override;
    string getRole()                 const override; 
    void   saveToFile(ofstream& out) const override;

    // Getters & Setters
    string getRollNumber()         const;
    string getDepartment()         const;
    bool   getHasTransportPass()   const;
    void   setHasTransportPass(bool val);
};

#endif