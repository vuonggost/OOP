#include "Operations.h"
#include <iostream>

using namespace std;

void AddContactOperation::execute(ContactManager* manager)
{
    string name, phone, relationship;

    cout << "\n========== THÊM LIÊN HỆ ==========\n";
    cout << "Nhập tên: "; getline(cin >> ws, name);
    cout << "Nhập số điện thoại: "; getline(cin, phone);
    cout << "Nhập mối quan hệ: "; getline(cin, relationship);

    Contact contact(name, phone, relationship);
    if (!contact.isValid())
    {
        cout << "Thông tin liên hệ không hợp lệ.\n";
        return;
    }

    if (manager->addContact(contact))
        cout << "Đã thêm liên hệ thành công.\n";
    else
        cout << "Không thể thêm liên hệ.\nSố điện thoại đã tồn tại.\n";
}

void SearchByNameOperation::execute(ContactManager* manager)
{
    string keyword;
    cout << "\nNhập tên hoặc từ khóa: ";
    getline(cin >> ws, keyword);
    manager->searchByName(keyword);
}

void SearchByPhonePrefixOperation::execute(ContactManager* manager)
{
    string prefix;
    cout << "\nNhập đầu số điện thoại: ";
    getline(cin >> ws, prefix);
    manager->searchByPhonePrefix(prefix);
}

void UpdateContactOperation::execute(ContactManager* manager)
{
    string phone, newName, newRelationship;

    cout << "\n========== CẬP NHẬT LIÊN HỆ ==========\n";
    cout << "Nhập số điện thoại: "; getline(cin >> ws, phone);
    cout << "Nhập tên mới: "; getline(cin, newName);
    cout << "Nhập mối quan hệ mới: "; getline(cin, newRelationship);

    if (manager->updateContact(phone, newName, newRelationship))
        cout << "Đã cập nhật liên hệ thành công.\n";
    else
        cout << "Cập nhật thất bại.\n";
}

void DeleteContactOperation::execute(ContactManager* manager)
{
    string name;

    cout << "\n========== XÓA LIÊN HỆ ==========\n";
    cout << "Nhập tên: ";
    getline(cin >> ws, name);

    if (manager->deleteByName(name))
    {
        cout << "Đã xóa liên hệ thành công.\n";
        return;
    }

    cout << "\nCó nhiều liên hệ trùng tên.\n"
         << "Vui lòng nhập số điện thoại của liên hệ cần xóa: ";

    string phone;
    getline(cin, phone);

    if (manager->deleteByPhone(phone))
        cout << "Đã xóa liên hệ thành công.\n";
    else
        cout << "Xóa thất bại.\n";
}

void FilterContactOperation::execute(ContactManager* manager)
{
    string relationship;
    cout << "\nNhập mối quan hệ: ";
    getline(cin >> ws, relationship);
    manager->filterByRelationship(relationship);
}

void StatisticsOperation::execute(ContactManager* manager)
{
    manager->showStatistics();
}

void ExportByRelationshipOperation::execute(ContactManager* manager)
{
    string relationship, filename;

    cout << "\n====== XUẤT THEO MỐI QUAN HỆ ======\n";
    cout << "Nhập mối quan hệ: "; getline(cin >> ws, relationship);
    cout << "Nhập tên tệp xuất: "; getline(cin, filename);

    if (filename.empty())
    {
        cout << "Tên tệp không được để trống.\n";
        return;
    }

    if (manager->exportByRelationship(relationship, filename))
        cout << "Xuất dữ liệu thành công.\n";
    else
        cout << "Không có liên hệ phù hợp hoặc xuất dữ liệu thất bại.\n";
}

LoadContactOperation::LoadContactOperation(string filename)
    : filename(filename) {}

void LoadContactOperation::execute(ContactManager* manager)
{
    if (manager->loadFromFile(filename))
    {
        cout << "Đã tải danh bạ thành công.\n"
             << "Tổng số liên hệ: " << manager->getContactCount() << '\n';
    }
    else
    {
        cout << "Không thể mở tệp: " << filename << '\n';
    }
}

SaveContactOperation::SaveContactOperation(string filename)
    : filename(filename) {}

void SaveContactOperation::execute(ContactManager* manager)
{
    if (manager->saveToFile(filename))
        cout << "Đã lưu danh bạ thành công.\n";
    else
        cout << "Lưu thất bại.\n";
}
