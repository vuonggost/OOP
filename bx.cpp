#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;

// ======================================================
// CẤU HÌNH BẢN ĐỒ
// ======================================================

const int ROW = 5;
const int COL = 8;

int parkingMap[ROW][COL] =
{
    {0, 0, 0, 0, 2, 0, 2, 0},
    {0, 1, 1, 0, 2, 0, 2, 0},
    {2, 0, 0, 0, 2, 0, 2, 0},
    {2, 1, 1, 0, 2, 0, 2, 0},
    {2, 2, 2, 2, 2, 2, 2, 2}
};

// 0 = đường đi
// 1 = vật cản
// 2 = chỗ đỗ xe

// ======================================================
// CẤU TRÚC DỮ LIỆU
// ======================================================

struct Position
{
    int x;
    int y;
};

struct Node
{
    Position pos;
    int g;
    int h;
    int f;
    Position parent;
    bool visited;
};

struct QueueNode
{
    Node* nodePtr;
    int priority;
};

struct Slot
{
    char id[10];
    Position pos;
    bool occupied;
};

struct Car
{
    char plate[20];
    char slotID[10];
};

struct HistoryEntry
{
    char text[100];
};

struct ParkingLot
{
    Slot* slots;
    Car* cars;
    HistoryEntry* history;

    int maxSlots;
    int maxCars;
    int maxHistory;

    int slotCount;
    int carCount;
    int historyCount;

    Node nodes[ROW][COL];
};

// ======================================================
// A* PATHFINDING
// ======================================================

bool isValid(int x, int y)
{
    return x >= 0 &&
           x < ROW &&
           y >= 0 &&
           y < COL &&
           parkingMap[x][y] != 1;
}

int heuristic(Position a, Position b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void resetNodes(Node nodes[ROW][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            nodes[i][j].g = 999999;
            nodes[i][j].h = 0;
            nodes[i][j].f = 999999;
            nodes[i][j].visited = false;
            nodes[i][j].parent.x = -1;
            nodes[i][j].parent.y = -1;
        }
    }
}

void insertPriority(
    QueueNode queue[],
    int& size,
    Node* node,
    int priority)
{
    if (size >= ROW * COL)
        return;

    int pos = size;

    while (pos > 0 && queue[pos - 1].priority > priority)
    {
        queue[pos] = queue[pos - 1];
        pos--;
    }

    queue[pos].nodePtr = node;
    queue[pos].priority = priority;
    size++;
}

QueueNode extractMin(QueueNode queue[], int& size)
{
    QueueNode result = queue[0];

    for (int i = 0; i < size - 1; i++)
    {
        queue[i] = queue[i + 1];
    }

    size--;
    return result;
}

int getDistance(
    Node nodes[ROW][COL],
    Position start,
    Position goal)
{
    QueueNode openList[ROW * COL];
    int openSize = 0;

    resetNodes(nodes);

    Node* startNode = &nodes[start.x][start.y];

    startNode->pos = start;
    startNode->g = 0;
    startNode->h = heuristic(start, goal);
    startNode->f = startNode->g + startNode->h;

    insertPriority(
        openList,
        openSize,
        startNode,
        startNode->f
    );

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (openSize > 0)
    {
        QueueNode current =
            extractMin(openList, openSize);

        if (current.nodePtr->visited)
            continue;

        current.nodePtr->visited = true;

        if (current.nodePtr->pos.x == goal.x &&
            current.nodePtr->pos.y == goal.y)
        {
            return current.nodePtr->g;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = current.nodePtr->pos.x + dx[i];
            int ny = current.nodePtr->pos.y + dy[i];

            if (!isValid(nx, ny))
                continue;

            if (nodes[nx][ny].visited)
                continue;

            Node* neighbor = &nodes[nx][ny];

            int newG = current.nodePtr->g + 1;

            if (newG < neighbor->g)
            {
                neighbor->pos.x = nx;
                neighbor->pos.y = ny;

                neighbor->g = newG;
                neighbor->h =
                    heuristic({nx, ny}, goal);

                neighbor->f =
                    neighbor->g + neighbor->h;

                neighbor->parent =
                    current.nodePtr->pos;

                insertPriority(
                    openList,
                    openSize,
                    neighbor,
                    neighbor->f
                );
            }
        }
    }

    return 999999;
}

// ======================================================
// QUẢN LÝ PARKING LOT
// ======================================================

void initializeParkingLot(
    ParkingLot& lot,
    int maxSlots,
    int maxCars,
    int maxHistory)
{
    lot.slots =
        new Slot[maxSlots];

    lot.cars =
        new Car[maxCars];

    lot.history =
        new HistoryEntry[maxHistory];

    lot.maxSlots = maxSlots;
    lot.maxCars = maxCars;
    lot.maxHistory = maxHistory;

    lot.slotCount = 0;
    lot.carCount = 0;
    lot.historyCount = 0;

    int number = 1;

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (parkingMap[i][j] == 2 &&
                lot.slotCount < maxSlots)
            {
                sprintf(
                    lot.slots[lot.slotCount].id,
                    "P%d",
                    number
                );

                lot.slots[lot.slotCount].pos.x = i;
                lot.slots[lot.slotCount].pos.y = j;
                lot.slots[lot.slotCount].occupied = false;

                lot.slotCount++;
                number++;
            }
        }
    }
}

void destroyParkingLot(ParkingLot& lot)
{
    delete[] lot.slots;
    delete[] lot.cars;
    delete[] lot.history;

    lot.slots = nullptr;
    lot.cars = nullptr;
    lot.history = nullptr;
}

int findCar(
    ParkingLot& lot,
    const char* plate)
{
    for (int i = 0; i < lot.carCount; i++)
    {
        if (strcmp(
                lot.cars[i].plate,
                plate) == 0)
        {
            return i;
        }
    }

    return -1;
}

int findSlot(
    ParkingLot& lot,
    const char* id)
{
    for (int i = 0; i < lot.slotCount; i++)
    {
        if (strcmp(
                lot.slots[i].id,
                id) == 0)
        {
            return i;
        }
    }

    return -1;
}

void sortSlotsByDistance(
    Slot temp[],
    int count)
{
    Position start = {0, 0};

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int d1 =
                heuristic(start, temp[i].pos);

            int d2 =
                heuristic(start, temp[j].pos);

            if (d2 < d1)
            {
                Slot tmp = temp[i];
                temp[i] = temp[j];
                temp[j] = tmp;
            }
        }
    }
}

int findNearestSlot(ParkingLot& lot)
{
    if (lot.slotCount == 0)
        return -1;

    Slot* temp =
        new Slot[lot.slotCount];

    int count = 0;

    for (int i = 0; i < lot.slotCount; i++)
    {
        if (!lot.slots[i].occupied)
        {
            temp[count] = lot.slots[i];
            count++;
        }
    }

    if (count == 0)
    {
        delete[] temp;
        return -1;
    }

    sortSlotsByDistance(temp, count);

    Position start = {0, 0};

    for (int i = 0; i < count; i++)
    {
        int distance =
            getDistance(
                lot.nodes,
                start,
                temp[i].pos
            );

        if (distance != 999999)
        {
            int result =
                findSlot(
                    lot,
                    temp[i].id
                );

            delete[] temp;

            return result;
        }
    }

    delete[] temp;

    return -1;
}

// ======================================================
// GỬI XE
// ======================================================

bool parkCar(
    ParkingLot& lot,
    const char* plate,
    char* assignedSlot)
{
    if (plate == nullptr ||
        assignedSlot == nullptr)
    {
        return false;
    }

    if (findCar(lot, plate) != -1)
        return false;

    if (lot.carCount >= lot.maxCars)
        return false;

    int slotIndex =
        findNearestSlot(lot);

    if (slotIndex == -1)
        return false;

    lot.slots[slotIndex].occupied = true;

    strcpy(
        lot.cars[lot.carCount].plate,
        plate
    );

    strcpy(
        lot.cars[lot.carCount].slotID,
        lot.slots[slotIndex].id
    );

    strcpy(
        assignedSlot,
        lot.slots[slotIndex].id
    );

    lot.carCount++;

    char historyText[100];

    sprintf(
        historyText,
        "[IN ] %s -> %s",
        plate,
        lot.slots[slotIndex].id
    );

    if (lot.historyCount < lot.maxHistory)
    {
        strcpy(
            lot.history[lot.historyCount].text,
            historyText
        );

        lot.historyCount++;
    }

    return true;
}

// ======================================================
// LẤY XE
// ======================================================

bool removeCar(
    ParkingLot& lot,
    const char* plate)
{
    int index =
        findCar(lot, plate);

    if (index == -1)
        return false;

    char slotID[10];

    strcpy(
        slotID,
        lot.cars[index].slotID
    );

    int slotIndex =
        findSlot(lot, slotID);

    if (slotIndex != -1)
    {
        lot.slots[slotIndex].occupied = false;
    }

    for (int i = index;
         i < lot.carCount - 1;
         i++)
    {
        lot.cars[i] =
            lot.cars[i + 1];
    }

    lot.carCount--;

    char historyText[100];

    sprintf(
        historyText,
        "[OUT] %s <- %s",
        plate,
        slotID
    );

    if (lot.historyCount < lot.maxHistory)
    {
        strcpy(
            lot.history[lot.historyCount].text,
            historyText
        );

        lot.historyCount++;
    }

    return true;
}

// ======================================================
// LƯU / ĐỌC DỮ LIỆU
// ======================================================

void saveData(
    ParkingLot& lot,
    const char* filename)
{
    ofstream file(filename);

    if (!file.is_open())
        return;

    for (int i = 0; i < lot.carCount; i++)
    {
        file << lot.cars[i].plate
             << " "
             << lot.cars[i].slotID
             << "\n";
    }

    file.close();
}

void loadData(
    ParkingLot& lot,
    const char* filename)
{
    ifstream file(filename);

    if (!file.is_open())
        return;

    char plate[20];
    char slotID[10];

    while (file >> plate >> slotID)
    {
        if (lot.carCount >= lot.maxCars)
            break;

        int slotIndex =
            findSlot(lot, slotID);

        if (slotIndex == -1)
            continue;

        if (lot.slots[slotIndex].occupied)
            continue;

        strcpy(
            lot.cars[lot.carCount].plate,
            plate
        );

        strcpy(
            lot.cars[lot.carCount].slotID,
            slotID
        );

        lot.slots[slotIndex].occupied = true;

        lot.carCount++;
    }

    file.close();
}

void saveHistory(
    ParkingLot& lot,
    const char* filename,
    const char* text)
{
    ofstream file(
        filename,
        ios::app
    );

    if (file.is_open())
    {
        file << text << "\n";
        file.close();
    }

    if (lot.historyCount < lot.maxHistory)
    {
        strcpy(
            lot.history[lot.historyCount].text,
            text
        );

        lot.historyCount++;
    }
}

void loadHistory(
    ParkingLot& lot,
    const char* filename)
{
    ifstream file(filename);

    if (!file.is_open())
        return;

    char line[100];

    while (
        file.getline(
            line,
            sizeof(line)))
    {
        if (lot.historyCount >=
            lot.maxHistory)
        {
            break;
        }

        strcpy(
            lot.history[lot.historyCount].text,
            line
        );

        lot.historyCount++;
    }

    file.close();
}

// ======================================================
// RESET DỮ LIỆU
// ======================================================

void resetParkingLot(
    ParkingLot& lot)
{
    lot.carCount = 0;
    lot.historyCount = 0;

    for (int i = 0;
         i < lot.slotCount;
         i++)
    {
        lot.slots[i].occupied = false;
    }

    ofstream parkingFile(
        "parking_data.txt");

    parkingFile.close();

    ofstream historyFile(
        "history.txt");

    historyFile.close();
}
void runParkingSystem(ParkingLot& lot)
{
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "           SMART PARKING SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Gui xe\n";
        cout << "2. Lay xe\n";
        cout << "3. Xem ban do bai xe\n";
        cout << "4. Xem trang thai slot\n";
        cout << "5. Xem danh sach xe\n";
        cout << "6. Xem lich su\n";
        cout << "7. Reset he thong\n";
        cout << "0. Thoat\n";
        cout << "========================================\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            char plate[20];
            char slotID[10];

            cout << "Nhap bien so xe: ";
            cin >> plate;

            if (parkCar(lot, plate, slotID))
            {
                cout << "Gui xe thanh cong!\n";
                cout << "Slot duoc cap: " << slotID << "\n";

                saveData(lot, "parking_data.txt");
                saveHistory(
                    lot,
                    "history.txt",
                    "Xe da duoc gui"
                );
            }
            else
            {
                cout << "Khong the gui xe.\n";
            }

            break;
        }

        case 2:
        {
            char plate[20];

            cout << "Nhap bien so xe: ";
            cin >> plate;

            if (removeCar(lot, plate))
            {
                cout << "Lay xe thanh cong!\n";
                saveData(lot, "parking_data.txt");
            }
            else
            {
                cout << "Khong tim thay xe.\n";
            }

            break;
        }

        case 3:
        {
            cout << "\nBAN DO BAI XE\n\n";

            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    cout << parkingMap[i][j] << " ";
                }

                cout << "\n";
            }

            break;
        }

        case 4:
        {
            cout << "\nTRANG THAI SLOT\n\n";

            for (int i = 0; i < lot.slotCount; i++)
            {
                cout << lot.slots[i].id
                     << " : "
                     << (lot.slots[i].occupied
                         ? "DA CO XE"
                         : "TRONG")
                     << "\n";
            }

            break;
        }

        case 5:
        {
            cout << "\nDANH SACH XE\n\n";

            if (lot.carCount == 0)
            {
                cout << "Khong co xe trong bai.\n";
            }
            else
            {
                for (int i = 0; i < lot.carCount; i++)
                {
                    cout << "Bien so: "
                         << lot.cars[i].plate
                         << " | Slot: "
                         << lot.cars[i].slotID
                         << "\n";
                }
            }

            break;
        }

        case 6:
        {
            cout << "\nLICH SU\n\n";

            for (int i = 0; i < lot.historyCount; i++)
            {
                cout << lot.history[i].text << "\n";
            }

            break;
        }

        case 7:
        {
            resetParkingLot(lot);
            cout << "Da reset he thong.\n";
            break;
        }

        case 0:
            cout << "Dang thoat...\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}
// ======================================================
// MAIN
// ======================================================
int main()
{
    ParkingLot lot;

    initializeParkingLot(
        lot,
        20,
        100,
        500
    );

    loadData(
        lot,
        "parking_data.txt"
    );

    loadHistory(
        lot,
        "history.txt"
    );

    runParkingSystem(lot);

    saveData(
        lot,
        "parking_data.txt"
    );

    destroyParkingLot(lot);

    return 0;
}