#include "Operation.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

// ================= ADD =================

void AddContactOperation::execute(ContactManager& manager) {
    string name, phone, relationship;

    cout << "\n===== ADD CONTACT =====\n";

    cout << "Nhap ten: ";
    getline(cin >> ws, name);

    cout << "Nhap so dien thoai: ";
    getline(cin, phone);

    cout << "Nhap moi quan he: ";
    getline(cin, relationship);

    if (manager.addContact(
            Contact(name, phone, relationship))) {
        cout << "Them Contact thanh cong!\n";
    }
    else {
        cout << "So dien thoai da ton tai!\n";
    }
}

// ================= SEARCH =================

void SearchContactOperation::execute(ContactManager& manager) {
    string name;

    cout << "\n===== SEARCH CONTACT =====\n";
    cout << "Nhap ten can tim: ";
    getline(cin >> ws, name);

    auto result = manager.searchByName(name);

    if (result.empty()) {
        cout << "Khong tim thay Contact!\n";
        return;
    }

    for (const auto& [phone, contact] : result)
        contact.display();
}

// ================= UPDATE =================

void UpdateContactOperation::execute(ContactManager& manager) {
    string phone, name, relationship;

    cout << "\n===== UPDATE CONTACT =====\n";

    cout << "Nhap so dien thoai: ";
    getline(cin >> ws, phone);

    cout << "Nhap ten moi: ";
    getline(cin, name);

    cout << "Nhap moi quan he moi: ";
    getline(cin, relationship);

    if (manager.updateContact(phone, name, relationship))
        cout << "Cap nhat thanh cong!\n";
    else
        cout << "Khong tim thay Contact!\n";
}

// ================= DELETE =================

void DeleteContactOperation::execute(ContactManager& manager) {
    string phone;

    cout << "\n===== DELETE CONTACT =====\n";
    cout << "Nhap so dien thoai can xoa: ";
    getline(cin >> ws, phone);

    if (manager.deleteContactByPhone(phone))
        cout << "Xoa Contact thanh cong!\n";
    else
        cout << "Khong tim thay Contact!\n";
}

// ================= FILTER =================

void FilterContactOperation::execute(ContactManager& manager) {
    string relationship;

    cout << "\n===== FILTER CONTACT =====\n";
    cout << "Nhap moi quan he: ";
    getline(cin >> ws, relationship);

    auto result = manager.filterByRelationship(relationship);

    if (result.empty()) {
        cout << "Khong co Contact phu hop!\n";
        return;
    }

    for (const auto& [phone, contact] : result)
        contact.display();
}

// ================= SORT =================

void SortContactOperation::execute(ContactManager& manager) {
    int choice;

    cout << "\n===== SORT CONTACT =====\n";
    cout << "1. Theo ten\n";
    cout << "2. Theo so dien thoai\n";
    cout << "Nhap lua chon: ";
    cin >> choice;

    const auto& contacts = manager.getAllContacts();

    if (contacts.empty()) {
        cout << "Danh ba rong!\n";
        return;
    }

    if (choice == 1) {
        map<string, Contact> sorted;

        for (const auto& [phone, contact] : contacts)
            sorted[contact.getName()] = contact;

        for (const auto& [name, contact] : sorted)
            contact.display();
    }
    else if (choice == 2) {
        for (const auto& [phone, contact] : contacts)
            contact.display();
    }
    else {
        cout << "Lua chon khong hop le!\n";
    }
}

// ================= STATISTICS =================

void StatisticsOperation::execute(ContactManager& manager) {
    const auto& contacts = manager.getAllContacts();

    cout << "\n===== STATISTICS =====\n";
    cout << "Tong so Contact: "
              << contacts.size() << '\n';

    map<string, int> statistics;

    for (const auto& [phone, contact] : contacts)
        ++statistics[contact.getRelationship()];

    for (const auto& [relationship, count] : statistics)
        cout << relationship
                  << ": "
                  << count << '\n';
}

// ================= LOAD =================

LoadOperation::LoadOperation(const string& fileName)
    : fileName(fileName) {
}

void LoadOperation::execute(ContactManager& manager) {
    ifstream file(fileName);

    cout << "\n===== LOAD CONTACT =====\n";

    if (!file) {
        cout << "Khong the mo file: "
                  << fileName << '\n';
        return;
    }

    string line;
    int count = 0;

    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);

        string name, phone, relationship;

        getline(ss, name, '|');
        getline(ss, phone, '|');
        getline(ss, relationship);

        if (manager.addContact(
                Contact(name, phone, relationship))) {
            ++count;
        }
    }

    cout << "Da load "
              << count
              << " Contact.\n";
}

// ================= SAVE =================

SaveOperation::SaveOperation(const string& fileName)
    : fileName(fileName) {
}

void SaveOperation::execute(ContactManager& manager) {
    ofstream file(fileName);

    cout << "\n===== SAVE CONTACT =====\n";

    if (!file) {
        cout << "Khong the mo file: "
                  << fileName << '\n';
        return;
    }

    const auto& contacts = manager.getAllContacts();

    for (const auto& [phone, contact] : contacts) {
        file << contact.getName() << '|'
             << contact.getPhone() << '|'
             << contact.getRelationship()
             << '\n';
    }

    cout << "Da luu "
              << contacts.size()
              << " Contact.\n";
}
