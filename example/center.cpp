#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "center.h"
using namespace std;

Center::Center(ProductManager& pm, StockManager& sm)
    : pm(pm), sm(sm) {}

void Center::run() {
    int num;
    while (true) {
        displayMainMenu();
        cin >> num;
        switch (num) {
            case 1:
                DockerManagement();
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
    cout << "  1. Docker Manager                     " << endl;
    cout << "  2. Stock Manager                     " << endl;
    cout << "  3. Product Manager                            " << endl;
    cout << "  4. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::displayDockerMenu() {
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Center                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Product Manager                     " << endl;
    cout << "  2. Stock Manager                            " << endl;
    cout << "  3. Quit this Program                       " << endl;
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
    cout << "  2. input Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. Modify Product                           " << endl;
    cout << "  5. Quit Product Manager                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::DockerManagement() {

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
                pm.inputProduct();
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