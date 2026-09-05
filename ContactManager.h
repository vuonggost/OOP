#pragma once
#include "Contact.h"
#include <map>
#include <string>
#include <iostream>


using namespace std;

template <typename T>
T maxValue(T a, T b)
{
    return (a > b) ? a : b;
}


class ContactManager
{
private:
    map<string, Contact> contacts;

    bool phoneExists(string phone) const;

public:
    bool loadFromFile(string filename);
    bool saveToFile(string filename) const;
    bool exportByRelationship(string relationship, string filename) const;

    bool addContact(Contact contact);
    void displayContacts() const;

    void searchByName(string keyword) const;
    void searchByPhonePrefix(string prefix) const;

    bool updateContact(string phone, string newName, string newRelationship);

    bool deleteByName(string name);
    bool deleteByPhone(string phone);

    void filterByRelationship(string relationship) const;
    void showStatistics() const;

    int getContactCount() const;
    bool isEmpty() const;
    void clear();
};
