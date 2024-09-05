#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "center.h"
using namespace std;

Center::Center(DockManager& dm, ProductManager& pm, StockManager& sm)
    : dm(dm), pm(pm), sm(sm) {}

void Center::run() {
    int num;
    while (true) {
        displayMainMenu();
        cin >> num;
        switch (num) {
            case 1:
                DockManagement();
                break;
            case 2:
                StockManagement();
                break;
            case 3:
                ProductManagement();
                break;
            case 4:
                cout << "\033[1;33m프로그램을 종료합니다.\033[0m" << endl;
                return;
        }
    }
}
void Center::displayMainMenu() {
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Center                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Dock Manager                     " << endl;
    cout << "  2. Stock Manager                     " << endl;
    cout << "  3. Product Manager                            " << endl;
    cout << "  4. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::displayDockMenu() {
    cout << "\033[2J\033[1;1H"; // 화면을 지우고 커서를 맨 위로 이동합니다.
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Dock Manager                   " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Dock List                       " << endl;
    cout << "  2. Dock Check In                           " << endl;
    cout << "  3. Dock Check Out                          " << endl;
    cout << "  4. Modify DockList                         " << endl;
    cout << "  5. Remove Dock From DockList               " << endl;
    cout << "  6. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::displayStockMenu() {
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Stock Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Stock List                     " << endl;
    cout << "  2. input Stock                            " << endl;
    cout << "  3. Store Product                          " << endl;
    cout << "  4. Delete Stock                           " << endl;
    cout << "  5. Modify Stock                           " << endl;
    cout << "  6. Quit Stock Manager                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::displayProductMenu() {
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Product Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                     " << endl;
    cout << "  2. Receive Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. Modify Product                           " << endl;
    cout << "  5. Quit Product Manager                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::DockManagement() {
    int choice, dockId, itemQuantity;
    string vehicleNumber, itemType;
    while(true) {
        displayDockMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            dm.displayDockList(); // 도크 목록을 출력합니다.
            cin.ignore();
            cout<<"If you go back, pleas press Enter!"<<endl;
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 2:
            cout << "Enter Dock ID to check in: "; cin >> dockId;
            cout << "Enter Vehicle Number: "; cin >> vehicleNumber;
            cout << "Enter Item Quantity: "; cin >> itemQuantity;
            cout << "Enter Item Type: "; cin >> itemType;
            dm.checkIn(dockId, vehicleNumber, itemQuantity, itemType); // 입고 처리
            break;
        case 3:
            dm.displayDockList(); // 도크 목록을 출력합니다.
            cin.ignore();
            cout << "\nEnter Dock ID to check out : "; cin >> dockId;
            dm.checkOut(dockId); // 출고 처리
            cout<<"If you go back, pleas press Enter!"<<endl;
            cin.ignore();
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 4:
            dm.displayDockList(); // 도크 목록을 출력합니다.
            cin.ignore();
            cout << "Enter Dock ID to modify: "; cin >> dockId;
            dm.modifyDock(dockId); // 도크 수정
            cout<<"If you go back, pleas press Enter!"<<endl;
            cin.ignore();
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 5:
            dm.displayDockList(); // 도크 목록을 출력합니다.
            cin.ignore();
            cout << "Enter Dock ID to remove: "; cin >> dockId;
            dm.removeDockFromList(dockId); // 도크 삭제
            cout<<"If you go back, pleas press Enter!"<<endl;
            cin.ignore();
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 6:
            return; // 프로그램 종료
        default:
            cout << "\nInvalid option. Please try again." << endl;
            cout<<"If you go back, pleas press Enter!"<<endl;
            cin.ignore();
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
        }
    }
}

void Center::StockManagement() {
    int num, key;
    while(true) {
        displayStockMenu();
        cin >> num;
        switch(num) {
            case 1: default:
                sm.displayInfo();
                cin.ignore();
                getchar();
                break;
            case 2:
                sm.inputStock();
                break;
            case 3:
                sm.storeProduct(pm);
                pauseScreen();
                break;
            case 4:
                sm.displayInfo();
                cout << "   Choose Key : ";
                cin >> key;
                sm.deleteStock(key);
                break;
            case 5:
                sm.displayInfo();
                cout << "   Choose Key : ";
                cin >> key;
                sm.modifyStock(key);
                break;
            case 6:
                return;
        }
    }
}

void Center::ProductManagement() {
    int num, key;
    while(true) {
        displayProductMenu();
        cin >> num;
        switch(num) {
            case 1: default:
                pm.displayInfo();
                cin.ignore();
                getchar();
                break;
            case 2:
                pm.receiveProduct(dm);
                pauseScreen();
                break;
            case 3:
                pm.displayInfo();
                cout << "   Choose Key : ";
                cin >> key;
                pm.deleteProduct(key);
                break;
            case 4:
                pm.displayInfo();
                cout << "   Choose Key : ";
                cin >> key;
                pm.modifyProduct(key);
                break;
            case 5:
                return;
        }
    }
}

void Center::pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}