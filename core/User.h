#ifndef USER_H
#define USER_H

// ABSTRACT BASE CLASS 

#include <string>
#include <fstream>
using namespace std;

class User {
protected:
   int id;
   string name;
   string email;
   string password;
   string role;
public:
  //Constructor and Destructor
  User(int id, string name, string email, string password, string role);
  virtual ~User();

  //Pure Virtual Functions 
  virtual void displayInfo() const = 0;
  virtual string getrole() const = 0;
  virtual void saveToFile (ofstream &out) const = 0;

  //Getters
  int getId() const;
  string getName() const;
  string getEmail() const;
  string getPassword() const;

  //Ooerator Overloading 
  bool operator == (const User &other) const;
};

























#endif


