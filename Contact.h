#pragma once
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Contact
{
private:
    string name;
    string phone;
    string relationship;

    bool isValidName(string value) const;
    bool isValidPhone(string value) const;
    bool isValidRelationship(string value) const;

public:
    Contact();
    Contact(string name, string phone, string relationship);

    string getName() const;
    string getPhone() const;
    string getRelationship() const;

    bool setName(string name);
    bool setPhone(string phone);
    bool setRelationship(string relationship);

    bool isValid() const;
    void display(int index = 0) const;

    friend ostream& operator<<(ostream& out, const Contact& contact);
    friend istream& operator>>(istream& in, Contact& contact);
    bool operator==(const Contact& other) const;
};
