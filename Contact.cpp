#include "Contact.h"
Contact::Contact() : name(""), phone(""), relationship("") {}

Contact::Contact(string name, string phone, string relationship)
    : name(""), phone(""), relationship("")
{
    setName(name);
    setPhone(phone);
    setRelationship(relationship);
}

bool Contact::isValidName(string value) const
{
    return !value.empty();
}

bool Contact::isValidPhone(string value) const
{
    if (value.length() != 10 || value[0] != '0')
        return false;

    for (char c : value)
        if (!isdigit(static_cast<unsigned char>(c)))
            return false;

    return true;
}

bool Contact::isValidRelationship(string value) const
{
    return !value.empty();
}

string Contact::getName() const
{
    return name;
}

string Contact::getPhone() const
{
    return phone;
}

string Contact::getRelationship() const
{
    return relationship;
}

bool Contact::setName(string name)
{
    if (!isValidName(name)) return false;
    this->name = name;
    return true;
}

bool Contact::setPhone(string phone)
{
    if (!isValidPhone(phone)) return false;
    this->phone = phone;
    return true;
}

bool Contact::setRelationship(string relationship)
{
    if (!isValidRelationship(relationship)) return false;
    this->relationship = relationship;
    return true;
}

bool Contact::isValid() const
{
    return isValidName(name) && isValidPhone(phone) && isValidRelationship(relationship);
}

void Contact::display(int index) const
{
    if (index > 0)
        cout << "\nContact " << index << '\n';

    cout << *this;
}

ostream& operator<<(ostream& out, const Contact& contact)
{
    out << "Tên          : " << contact.name << '\n';
    out << "Số điện thoại : " << contact.phone << '\n';
    out << "Mối quan hệ   : " << contact.relationship << '\n';
    return out;
}

istream& operator>>(istream& in, Contact& contact)
{
    string name;
    string phone;
    string relationship;

    getline(in >> ws, name);
    getline(in, phone);
    getline(in, relationship);

    contact.setName(name);
    contact.setPhone(phone);
    contact.setRelationship(relationship);

    return in;
}

bool Contact::operator==(const Contact& other) const
{
    return name == other.name
        && phone == other.phone
        && relationship == other.relationship;
}
