#ifndef ADMIN_H
#define ADMIN_H

 // DERIVED CLASS (FROM USER)

 #include "User.h"
 #include <fstream>

 class Admin : public User {
private:
    string adminCode;
public:
    //Constructor and Destructor 
    Admin(int id, string name, string email, string password, string adminCode);
    ~Admin();

    //Implementing all pure virtual functions form User 
    void displayInfo() const override;
    string getrole() const override;
    void saveToFile(ofstream &out) const override;

    //Getter
    string getAdminCode() const;
 };






















#endif

