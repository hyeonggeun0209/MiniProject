#include "DockManager.h"
#include <iostream>
#include <chrono>
#include <string>

void showMenu() {
    std::cout << "1. Add Dock\n";
    std::cout << "2. Remove Dock\n";
    std::cout << "3. Display All Docks\n";
    std::cout << "4. Display Single Dock\n";
    std::cout << "5. Add Item to Dock\n";
    std::cout << "6. Remove Item from Dock\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    DockManager manager;
    int choice, dockID;
    std::string vehicleNumber, itemType;
    int quantity;
    std::string status;

    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter Dock ID to add: ";
                std::cin >> dockID;
                manager.addDock(dockID);
                std::cout << "Dock " << dockID << " added.\n";
                break;

            case 2:
                std::cout << "Enter Dock ID to remove: ";
                std::cin >> dockID;
                manager.removeDock(dockID);
                std::cout << "Dock " << dockID << " removed.\n";
                break;

            case 3:
                manager.displayAllDocks();
                break;

            case 4:
                std::cout << "Enter Dock ID to display: ";
                std::cin >> dockID;
                manager.displayDock(dockID);
                break;

            case 5: {
                std::cout << "Enter Dock ID: ";
                std::cin >> dockID;
                Dock* dock = manager.getDock(dockID);
                if (dock) {
                    std::cout << "Enter Vehicle Number: ";
                    std::cin >> vehicleNumber;
                    dock->setVehicleNumber(vehicleNumber);
                    dock->setEntryTime(std::chrono::system_clock::now());

                    std::cout << "Enter Item Type: ";
                    std::cin >> itemType;
                    std::cout << "Enter Quantity: ";
                    std::cin >> quantity;
                    std::cout << "Enter Status (e.g., '입고', '선적'): ";
                    std::cin >> status;

                    Item item = {itemType, quantity, status};
                    dock->addItem(item);
                    std::cout << "Item added to Dock " << dockID << ".\n";
                } else {
                    std::cout << "Dock ID " << dockID << " not found.\n";
                }
                break;
            }

            case 6: {
                std::cout << "Enter Dock ID: ";
                std::cin >> dockID;
                Dock* dock = manager.getDock(dockID);
                if (dock) {
                    std::cout << "Enter Item Type to remove: ";
                    std::cin >> itemType;
                    dock->removeItem(itemType);
                    std::cout << "Item removed from Dock " << dockID << ".\n";
                } else {
                    std::cout << "Dock ID " << dockID << " not found.\n";
                }
                break;
            }

            case 7:
                return 0;

            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
