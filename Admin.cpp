#include "Admin.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor

Admin::Admin(int id, string name, string email,
             string password, string adminCode)
    : User(id, name, email, password, "Admin")
{
    if (adminCode.empty())
        throw invalid_argument("Admin code cannot be empty.");

    if (adminCode.length() < 4)
        throw invalid_argument("Admin code must be at least 4 characters.");

    // Admin code must be alphanumeric only
    for (char c : adminCode) {
        if (!isalnum(c))
            throw invalid_argument("Admin code must contain only letters and digits.");
    }

    this->adminCode = adminCode;
}

// Destructor

Admin::~Admin() {}

// displayInfo

void Admin::displayInfo() const {
    cout << "\n┌─────────────────────────────┐\n";
    cout <<   "│        ADMIN PROFILE        │\n";
    cout <<   "├─────────────────────────────┤\n";
    cout <<   "│ ID    : " << id         << "\n";
    cout <<   "│ Name  : " << name       << "\n";
    cout <<   "│ Email : " << email      << "\n";
    cout <<   "│ Role  : " << role       << "\n";
    cout <<   "│ Code  : " << adminCode  << "\n";
    cout <<   "└─────────────────────────────┘\n";
}

// getRole

string Admin::getRole() const {
    return "Admin";
}

// saveToFile

void Admin::saveToFile(ofstream& out) const {
    if (!out.is_open())
        throw runtime_error("File stream is not open. Cannot save Admin data.");

    // Format: ADMIN|id|name|email|password|adminCode
    out << "ADMIN"    << "|"
        << id         << "|"
        << name       << "|"
        << email      << "|"
        << password   << "|"
        << adminCode  << "\n";
}

// Getter

string Admin::getAdminCode() const {
    return adminCode;
}