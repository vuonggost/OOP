#include <windows.h>
#include "Operations.h"
#include <iostream>
#include <string>

using namespace std;

void showMenu()
{
    cout << "\n========================================\n";
    cout << "           QUAN LY DANH BA\n";
    cout << "========================================\n";
    cout << "1. Tai danh ba tu contacts.txt\n";
    cout << "2. Hien thi danh ba\n";
    cout << "3. Them lien he\n";
    cout << "4. Tim kiem theo ten\n";
    cout << "5. Tim kiem theo dau so dien thoai\n";
    cout << "6. Cap nhat lien he\n";
    cout << "7. Xoa lien he\n";
    cout << "8. Loc theo moi quan he\n";
    cout << "9. Xem thong ke\n";
    cout << "10. Xuat theo moi quan he\n";
    cout << "11. Luu danh ba vao contacts.txt\n";
    cout << "0. Thoat\n";
    cout << "========================================\n";
    cout << "Lua chon: ";
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ContactManager* manager = new ContactManager;
    const string filename = "contacts.txt";
    if (!manager->loadFromFile(filename))
{
    cout << "Khong the mo file contacts.txt\n";
}
else
{
    cout << "Da tai danh ba tu contacts.txt\n";
}

    int choice;

    cout << "========================================\n";
    cout << "         CHUONG TRINH QUAN LY DANH BA\n";
    cout << "========================================\n";
    cout << "File du lieu: " << filename << '\n';

    while (true)
    {
        showMenu();

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Lua chon khong hop le.\n";
            continue;
        }

        cin.ignore(10000, '\n');

        if (choice == 0)
        {
            cout << "Da thoat chuong trinh.\n";
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
            cout << "Lua chon khong hop le.\n";
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