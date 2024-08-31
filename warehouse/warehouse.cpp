#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "product.h"
#include "productmanager.h"
#include "inventory.h"
#include "inventorymanager.h"
#include "warehouse.h"

WareHouse::WareHouse() {}

bool WareHouse::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 WareHouse                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Product Manager                     " << endl;
    cout << "  2. Inventory Manager                            " << endl;
    cout << "  3. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    cin >> ch;
    switch(ch) {
        case 1: {
            bool a = true;
            while(a) {
                a = bm.displayMenu();
            }
            break;
        }
        case 2: {
            bool a = true;
            while(a) {
                a = im.displayMenu();
            }
            break;
        }
        case 3:
            return false;
        default:
            return false;
    }
    return true;
}