#pragma once

#include <string>
#include <iostream>

using namespace std;

class Contact {
private:
    string name;
    string phone;
    string relationship;

    // Validation helpers
    bool isValidName(const string& name) const;
    bool isValidPhone(const string& phone) const;
    bool isValidRelationship(const string& relationship) const;

public:
    // Constructors
    Contact();
    Contact(const string& name, const string& phone, const string& relationship);

    // Getters
    string getName() const;
    string getPhone() const;
    string getRelationship() const;

    // Setters (có validation)
    void setName(const string& name);
    void setPhone(const string& phone);
    void setRelationship(const string& relationship);

    // Hiển thị thông tin
    void display() const;

    // Toán tử so sánh
    bool operator==(const Contact& other) const;
    bool operator<(const Contact& other) const;

    // Toán tử nhập/xuất
    friend ostream& operator<<(ostream& out, const Contact& c);
    friend istream& operator>>(istream& in, Contact& c);
};