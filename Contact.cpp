#include "Contact.h"
#include <cctype>
#include <algorithm>
using namespace std;

// ---------------- Validation helpers ----------------

bool Contact::isValidName(const string& name) const {
    if (name.empty()) return false;

    // Không hợp lệ nếu chuỗi chỉ toàn khoảng trắng
    bool hasNonSpace = any_of(name.begin(), name.end(), [](unsigned char c) {
        return !isspace(c);
    });

    return hasNonSpace;
}

bool Contact::isValidPhone(const string& phone) const {
    // Phải đủ 10 ký tự, bắt đầu bằng '0', toàn bộ là chữ số
    if (phone.length() != 10) return false;
    if (phone[0] != '0') return false;

    for (char c : phone) {
        if (!isdigit(static_cast<unsigned char>(c))) return false;
    }

    return true;
}

bool Contact::isValidRelationship(const string& relationship) const {
    if (relationship.empty()) return false;

    bool hasNonSpace = any_of(relationship.begin(), relationship.end(), [](unsigned char c) {
        return !isspace(c);
    });

    return hasNonSpace;
}

// ---------------- Constructors ----------------

Contact::Contact() : name(""), phone(""), relationship("") {}

Contact::Contact(const string& name, const string& phone, const string& relationship) {
    setName(name);
    setPhone(phone);
    setRelationship(relationship);
}

// ---------------- Getters ----------------

string Contact::getName() const {
    return name;
}

string Contact::getPhone() const {
    return phone;
}

string Contact::getRelationship() const {
    return relationship;
}

// ---------------- Setters ----------------

void Contact::setName(const string& name) {
    if (isValidName(name)) {
        this->name = name;
    } else {
        cerr << "Loi: Ten khong hop le (khong duoc rong hoac chi chua khoang trang)." << endl;
    }
}

void Contact::setPhone(const string& phone) {
    if (isValidPhone(phone)) {
        this->phone = phone;
    } else {
        cerr << "Loi: So dien thoai khong hop le (phai gom 10 chu so, bat dau bang '0')." << endl;
    }
}

void Contact::setRelationship(const string& relationship) {
    if (isValidRelationship(relationship)) {
        this->relationship = relationship;
    } else {
        cerr << "Loi: Moi quan he khong hop le (khong duoc rong hoac chi chua khoang trang)." << endl;
    }
}

// ---------------- Display ----------------

void Contact::display() const {
    cout << "Name         : " << name << endl;
    cout << "Phone        : " << phone << endl;
    cout << "Relationship : " << relationship << endl;
}

// ---------------- Operator overloads ----------------

bool Contact::operator==(const Contact& other) const {
    return phone == other.phone;
}

bool Contact::operator<(const Contact& other) const {
    return name < other.name;
}

ostream& operator<<(ostream& out, const Contact& c) {
    out << c.name << ", " << c.phone << ", " << c.relationship;
    return out;
}

istream& operator>>(istream& in, Contact& c) {
    string inputName, inputPhone, inputRelationship;

    cout << "Nhap ten: ";
    getline(in, inputName);
    c.setName(inputName);

    cout << "Nhap so dien thoai: ";
    getline(in, inputPhone);

    // Loại bỏ khoảng trắng ở đầu và cuối chuỗi số điện thoại
    inputPhone.erase(0, inputPhone.find_first_not_of(" \t"));
    size_t lastNonSpace = inputPhone.find_last_not_of(" \t");
    if (lastNonSpace != string::npos) {
        inputPhone.erase(lastNonSpace + 1);
    }

    c.setPhone(inputPhone);

    cout << "Nhap moi quan he: ";
    getline(in, inputRelationship);
    c.setRelationship(inputRelationship);

    return in;
}