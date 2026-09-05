#include "Operations.h"
#include <iostream>

using namespace std;

void showMenu()
{
    cout << "\n========================================\n";
    cout << "         QUẢN LÝ DANH BẠ\n";
    cout << "========================================\n";
    cout << "1. Tải danh bạ từ contacts.txt\n";
    cout << "2. Hiển thị danh bạ\n";
    cout << "3. Thêm liên hệ\n";
    cout << "4. Tìm theo tên\n";
    cout << "5. Tìm theo đầu số điện thoại\n";
    cout << "6. Cập nhật liên hệ\n";
    cout << "7. Xóa liên hệ\n";
    cout << "8. Lọc theo mối quan hệ\n";
    cout << "9. Xem thống kê\n";
    cout << "10. Xuất theo mối quan hệ\n";
    cout << "11. Lưu danh bạ vào contacts.txt\n";
    cout << "0. Thoát\n";
    cout << "========================================\n";
    cout << "Chọn: ";
}

int main()
{
    ContactManager* manager = new ContactManager;
    const string filename = "contacts.txt";
    int choice;

    cout << "========================================\n";
    cout << "      QUẢN LÝ DANH BẠ PROGRAM\n";
    cout << "========================================\n";
    cout << "Tệp dữ liệu: " << filename << '\n';

    while (true)
    {
        showMenu();

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Lựa chọn không hợp lệ.\n";
            continue;
        }

        cin.ignore(10000, '\n');

        if (choice == 0)
        {
            cout << "Đã thoát chương trình.\n";
            break;
        }

        ContactOperation* operation = nullptr;

        switch (choice)
        {
        case 1:
            operation = new LoadContactOperation(filename);
            break;
        case 2:
            manager->displayContacts();
            break;
        case 3:
            operation = new AddContactOperation;
            break;
        case 4:
            operation = new SearchByNameOperation;
            break;
        case 5:
            operation = new SearchByPhonePrefixOperation;
            break;
        case 6:
            operation = new UpdateContactOperation;
            break;
        case 7:
            operation = new DeleteContactOperation;
            break;
        case 8:
            operation = new FilterContactOperation;
            break;
        case 9:
            operation = new StatisticsOperation;
            break;
        case 10:
            operation = new ExportByRelationshipOperation;
            break;
        case 11:
            operation = new SaveContactOperation(filename);
            break;
        default:
            cout << "Lựa chọn không hợp lệ.\n";
            break;
        }

        if (operation != nullptr)
        {
            operation->execute(manager);
            delete operation;
        }
    }

    delete manager;
    return 0;
}
