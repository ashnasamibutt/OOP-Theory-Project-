#include "Student.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor

Student::Student(int id, string name, string email,
                 string password, string rollNumber, string department)
    : User(id, name, email, password, "Student")
{
    if (rollNumber.empty())
        throw invalid_argument("Roll number cannot be empty.");

    if (department.empty())
        throw invalid_argument("Department cannot be empty.");

    // Roll number must contain at least one digit
    bool hasDigit = false;
    for (char c : rollNumber)
        if (isdigit(c)) { hasDigit = true; break; }

    if (!hasDigit)
        throw invalid_argument("Roll number must contain at least one digit (e.g. 23F-3045).");

    // Department must contain only letters and spaces
    for (char c : department) {
        if (!isalpha(c) && c != ' ')
            throw invalid_argument("Department name must contain only letters.");
    }

    this->rollNumber       = rollNumber;
    this->department       = department;
    this->hasTransportPass = false;  // No pass at registration
}

// Destructor

Student::~Student() {}

// displayInfo

void Student::displayInfo() const {
    cout << "\n┌──────────────────────────────────┐\n";
    cout <<   "│          STUDENT PROFILE         │\n";
    cout <<   "├──────────────────────────────────┤\n";
    cout <<   "│ ID         : " << id                                           << "\n";
    cout <<   "│ Name       : " << name                                         << "\n";
    cout <<   "│ Email      : " << email                                        << "\n";
    cout <<   "│ Roll No    : " << rollNumber                                   << "\n";
    cout <<   "│ Department : " << department                                   << "\n";
    cout <<   "│ Transport  : " << (hasTransportPass ? "Registered" : "None")  << "\n";
    cout <<   "└──────────────────────────────────┘\n";
}

// getRole

string Student::getRole() const {
    return "Student";
}

// saveToFile

void Student::saveToFile(ofstream& out) const {
    if (!out.is_open())
        throw runtime_error("File stream is not open. Cannot save Student data.");

    // Format: STUDENT|id|name|email|password|rollNumber|department|hasTransportPass
    out << "STUDENT"         << "|"
        << id                << "|"
        << name              << "|"
        << email             << "|"
        << password          << "|"
        << rollNumber        << "|"
        << department        << "|"
        << hasTransportPass  << "\n";
}

// Getters & Setters

string Student::getRollNumber() const {
    return rollNumber;
}

string Student::getDepartment() const {
    return department;
}

bool Student::getHasTransportPass() const {
    return hasTransportPass;
}

void Student::setHasTransportPass(bool val) {
    // Guard: a pass can only be removed through the TransportPass module
    if (hasTransportPass == true && val == false) {
        cout << "[Warning] Transport pass must be cancelled through "
                "the registration module, not directly.\n";
        return;
    }
    hasTransportPass = val;
}