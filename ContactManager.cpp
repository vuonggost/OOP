#include "ContactManager.h"
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

bool ContactManager::phoneExists(string phone) const
{
    return contacts.find(phone) != contacts.end();
}

bool ContactManager::loadFromFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open()) return false;

    contacts.clear();
    string line;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        size_t first = line.find('|');
        if (first == string::npos) continue;

        size_t second = line.find('|', first + 1);
        if (second == string::npos) continue;

        string name = line.substr(0, first);
        string phone = line.substr(first + 1, second - first - 1);
        string relationship = line.substr(second + 1);

        Contact contact(name, phone, relationship);
        if (!contact.isValid() || phoneExists(phone)) continue;

        contacts.emplace(phone, contact);
    }

    return true;
}

bool ContactManager::saveToFile(string filename) const
{
    ofstream file(filename);
    if (!file.is_open()) return false;

    for (auto pair : contacts)
    {
        Contact contact = pair.second;
        file << contact.getName() << '|'
             << contact.getPhone() << '|'
             << contact.getRelationship() << '\n';
    }

    return true;
}

bool ContactManager::exportByRelationship(string relationship, string filename) const
{
    if (relationship.empty()) return false;

    ofstream file(filename);
    if (!file.is_open()) return false;

    bool found = false;

    for (auto pair : contacts)
    {
        Contact contact = pair.second;
        if (contact.getRelationship() == relationship)
        {
            file << contact.getName() << '|'
                 << contact.getPhone() << '|'
                 << contact.getRelationship() << '\n';
            found = true;
        }
    }

    return found;
}

bool ContactManager::addContact(Contact contact)
{
    if (!contact.isValid() || phoneExists(contact.getPhone()))
        return false;

    contacts.emplace(contact.getPhone(), contact);
    return true;
}

void ContactManager::displayContacts() const
{
    if (contacts.empty())
    {
        cout << "\nKhông có liên hệ nào.\n";
        return;
    }

    cout << "\n========================================\n"
         << "             DANH SÁCH LIÊN HỆ\n"
         << "========================================\n";

    int index = 1;
    for (auto pair : contacts)
    {
        pair.second.display(index++);
        cout << "----------------------------------------\n";
    }

    cout << "Tổng số liên hệ: " << contacts.size() << '\n';
}

void ContactManager::searchByName(string keyword) const
{
    if (keyword.empty())
    {
        cout << "Từ khóa tìm kiếm không được để trống.\n";
        return;
    }

    bool found = false;
    int count = 0;
    cout << "\n========== TÌM THEO TÊN ==========\n";

    for (auto pair : contacts)
    {
        Contact contact = pair.second;
        if (contact.getName().find(keyword) != string::npos)
        {
            contact.display(++count);
            cout << "----------------------------------------\n";
            found = true;
        }
    }

    if (found) cout << "Tìm thấy " << count << " liên hệ.\n";
    else cout << "Không tìm thấy liên hệ.\n";
}

void ContactManager::searchByPhonePrefix(string prefix) const
{
    if (prefix.empty())
    {
        cout << "Đầu số điện thoại không được để trống.\n";
        return;
    }

    bool found = false;
    int count = 0;
    cout << "\n====== TÌM THEO ĐẦU SỐ ĐIỆN THOẠI ======\n";

    for (auto pair : contacts)
    {
        if (pair.first.compare(0, prefix.length(), prefix) == 0)
        {
            pair.second.display(++count);
            cout << "----------------------------------------\n";
            found = true;
        }
    }

    if (found) cout << "Tìm thấy " << count << " liên hệ.\n";
    else cout << "Không tìm thấy liên hệ có đầu số: " << prefix << '\n';
}

bool ContactManager::updateContact(string phone, string newName, string newRelationship)
{
    auto it = contacts.find(phone);
    if (it == contacts.end() || newName.empty() || newRelationship.empty())
        return false;

    return it->second.setName(newName) && it->second.setRelationship(newRelationship);
}

bool ContactManager::deleteByName(string name)
{
    if (name.empty()) return false;

    string phone;
    int count = 0;

    for (auto pair : contacts)
    {
        if (pair.second.getName() == name)
        {
            count++;
            phone = pair.first;
        }
    }

    if (count != 1) return false;

    contacts.erase(phone);
    return true;
}

bool ContactManager::deleteByPhone(string phone)
{
    return contacts.erase(phone) > 0;
}

void ContactManager::filterByRelationship(string relationship) const
{
    if (relationship.empty())
    {
        cout << "Mối quan hệ không được để trống.\n";
        return;
    }

    bool found = false;
    int count = 0;
    cout << "\n====== LỌC THEO MỐI QUAN HỆ ======\n";

    for (auto pair : contacts)
    {
        Contact contact = pair.second;
        if (contact.getRelationship() == relationship)
        {
            contact.display(++count);
            cout << "----------------------------------------\n";
            found = true;
        }
    }

    if (found) cout << "Tìm thấy " << count << " liên hệ.\n";
    else cout << "Không tìm thấy liên hệ nào.\n";
}

void ContactManager::showStatistics() const
{
    cout << "\n========================================\n"
         << "               THỐNG KÊ\n"
         << "========================================\n"
         << "Tổng số liên hệ: " << contacts.size() << '\n';

    if (contacts.empty()) return;

    map<string, int> statistics;
    int maxCount = 0;

    for (auto pair : contacts)
    {
        int count = ++statistics[pair.second.getRelationship()];
        maxCount = maxValue(maxCount, count);
    }

    cout << "\nSố lượng liên hệ theo mối quan hệ:\n";
    for (auto pair : statistics)
        cout << "  " << pair.first << " : " << pair.second << '\n';

    cout << "Số lượng mối quan hệ nhiều nhất: " << maxCount << '\n';
}

int ContactManager::getContactCount() const
{
    return static_cast<int>(contacts.size());
}

bool ContactManager::isEmpty() const
{
    return contacts.empty();
}

void ContactManager::clear()
{
    contacts.clear();
}
