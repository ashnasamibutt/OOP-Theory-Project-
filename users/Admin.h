#ifndef ADMIN_H
#define ADMIN_H

// DERIVED CLASS (FROM USER)

#include "User.h"

class Admin : public User {
private:
    string adminCode;

public:
    // Constructor & Destructor
    Admin(int id, string name, string email, string password, string adminCode);
    ~Admin();

    // Pure Virtual Implementations
    void   displayInfo()             const override;
    string getRole()                 const override; 
    void   saveToFile(ofstream& out) const override;

    // Getter
    string getAdminCode() const;
};

#endif
