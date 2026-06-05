#include "User.h"

User::User (int id, string name,string email, string password,string role) : id(id), name(name),  email(email), password(password), role(role) {}

User:: ~User() {}

int User::getId() const { return id; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getPassword() const { return password; }

bool User::operator == (const User& other) const {
    return this->id == other.id;
} 