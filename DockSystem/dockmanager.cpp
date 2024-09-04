#include "dockmanager.h"
#include <fstream>
#include <sstream>
#include <iomanip>      // �Ű������� ������ ������ �������
#include <ctime>

// DockManager ������
// DockManager ��ü�� �ʱ�ȭ�մϴ�.
// ����� �⺻ �����ڷ� �ʱ�ȭ �۾��� �߰��Ǿ� ���� �ʽ��ϴ�.
DockManager::DockManager() {
    // �ʱ�ȭ �۾��� ���⿡ �߰��� �� ����
    std::ifstream file("docklist.txt");
    if (file) {
        while (file) {
            std::vector<std::string> row = parseCSV(file, ',');
            if (!row.empty()) {
                int id = std::stoi(row[0]);
                const std::string& vehicleNumber = row[1];
                int quantity = std::stoi(row[2]);
                const std::string& itemType = row[3];
                const std::string& status = row[4];
                std::time_t entryTime = std::stoll(row[5]);  // ���ڿ��� time_t�� ��ȯ
                std::time_t exitTime = std::stoll(row[6]);   // ���ڿ��� time_t�� ��ȯ

                // ��ũ ��ü�� �����ϰ� ��ũ ��Ͽ� �߰�
                auto dock = std::make_unique<Dock>(id, vehicleNumber, quantity, itemType, status, entryTime, exitTime);
                dockList.insert({ id, std::move(dock) });
            }
        }
    }
}

// DockManager �Ҹ���
// DockManager ��ü�� �Ҹ�� �� ��ũ ����� ���Ͽ� �����ϰų� ���� �۾��� ������ �� �ֽ��ϴ�.
// ����� Ư���� �۾��� �߰��Ǿ� ���� �ʽ��ϴ�.
DockManager::~DockManager() {
    // �Ҹ��ڿ��� ���� ���� �۾��� �� �� ����
    std::ofstream file("docklist.txt");
    if (file) {
        for (const auto& entry : dockList) {
            const Dock* dock = entry.second.get();
            file << dock->getDockId() << ","
                 << dock->getVehicleNumber() << ","
                 << dock->getItemQuantity() << ","
                 << dock->getItemType() << ","
                 << dock->getDockStatus() << ","
                 << dock->getEntryTime() << ","  // time_t�� �״�� ���
                 << dock->getExitTime() << std::endl;  // time_t�� �״�� ���
        }
    }
}

// ���ο� ��ũ�� ��ũ ��Ͽ� �߰��մϴ�.
// @param dock �߰��� ��ũ ��ü�� ���� ������
void DockManager::addDockToList(std::unique_ptr<Dock> dock) {
    dockList.insert({ dock->getDockId(), std::move(dock) });
}

// �־��� ID�� ��ũ�� ��ũ ��Ͽ��� �����մϴ�.
// @param id ������ ��ũ�� ���� ID
void DockManager::removeDockFromList(int dockId) {

    if(dockList.erase(dockId)>0)
    {
        std::cout<<"Successfully deleted"<<std::endl;
    }
    else
        std::cout << "Dock not found." << std::endl;
}

// �־��� ID�� ��ũ ������ �����մϴ�.
// ��ũ�� ���� ������ ����ϰ� ���ο� ������ �Է¹޾� ������Ʈ�մϴ�.
// @param id ������ ��ũ�� ���� ID
void DockManager::modifyDock(int dockId) {
    Dock* dock = searchDock(dockId);
    if (dock) {
        // ��ũ�� ���� ������ ����մϴ�.
        std::cout << "ID: " << dock->getDockId() << std::endl;
        std::cout << "Vehicle Number: " << dock->getVehicleNumber() << std::endl;
        std::cout << "Quantity: " << dock->getItemQuantity() << std::endl;
        std::cout << "Item Type: " << dock->getItemType() << std::endl;
        std::cout << "Status: " << dock->getDockStatus() << std::endl;

        // ���ο� ������ �Է¹޾� ��ũ ��ü�� �����մϴ�.
        std::string vehicleNumber, itemType, status;
        int quantity;
        std::cout << "Enter new vehicle number: "; std::cin >> vehicleNumber;
        std::cout << "Enter new quantity: "; std::cin >> quantity;
        std::cout << "Enter new item type: "; std::cin >> itemType;
        std::cout << "Enter new status: "; std::cin >> status;

        // ��ũ�� �Ӽ� ������Ʈ
        dock->setVehicleNumber(vehicleNumber);
        dock->setItemQuantity(quantity);
        dock->setItemType(itemType);
        dock->setDockStatus(status);

        std::cout << "Successfully modified"<<std::endl;
    } else {
        std::cout << "Dock not found." << std::endl;
    }
}

// �־��� ID�� ��ũ�� �˻��Ͽ� ��ȯ�մϴ�.
// @param id �˻��� ��ũ�� ���� ID
// @return �־��� ID�� ��ũ ��ü ������. ID�� �������� ������ nullptr
Dock* DockManager::searchDock(int dockId) const {
    auto it = dockList.find(dockId);
    return it != dockList.end() ? it->second.get() : nullptr;
    std::cout<< dockId <<" ID is wrong!"<<std::endl;

}

// ��� ��ũ�� ������ ����մϴ�.
// ��ũ ��Ͽ� �ִ� ��� ��ũ�� ������ ���˿� ���� ����մϴ�.
void DockManager::displayDockList() const {
    std::cout << std::endl;
    std::cout<<std::setw(5) <<  std::setfill(' ')   <<  std::left   <<  "ID"                <<" | "
            <<std::setw(16) <<  std::setfill(' ')   <<  std::left   <<  "Vehicle Numver"    <<" | "
            <<std::setw(14)  <<  std::setfill(' ')   <<  std::left   <<  "Item Quantity"     <<" | "
            <<std::setw(10) <<  std::setfill(' ')   <<  std::left   <<  "Item type"         <<" | "
            <<std::setw(12) <<  std::setfill(' ')   <<  std::left   <<  "Dock Status"       <<" | "
            <<std::setw(19)  <<  std::setfill(' ')   <<  std::left   <<  "Entry Time"        <<" | "
            <<std::setw(19)  <<  std::setfill(' ')   <<  std::left   <<  "Exit Time"         <<" | " <<std::endl;

    for (const auto& entry : dockList) {
        const Dock* dock = entry.second.get();

        // ��ũ�� ���� �� ���� �ð��� ���� �ð����� ��ȯ�մϴ�.
        std::time_t entryTime = dock->getEntryTime();
        std::time_t exitTime = dock->getExitTime();



        std::tm entryTm;
        std::tm exitTm;

        // localtime_s �Լ��� ù ��° �Ű������� std::tm* ����ü�� �ް�, �� ��° �Ű������� std::time_t*�� �޽��ϴ�.
#ifdef _WIN32
        localtime_s(&entryTm, &entryTime);
        localtime_s(&exitTm, &exitTime);
#else
        localtime_l(&entryTm, &entryTime);
        localtime_l(&exitTm, &exitTime);
#endif


        // ��ũ ������ ���˿� ���� ����մϴ�.
        std::cout << std::setw(5)   << std::setfill(' ') << std::left  << dock->getDockId()              << " | "
                  << std::setw(16)  << std::setfill(' ') << std::left  << dock->getVehicleNumber()       << " | "
                  << std::setw(14)   << std::setfill(' ') << std::left  << dock->getItemQuantity()        << " | "
                  << std::setw(10)  << std::setfill(' ') << std::left  << dock->getItemType()            << " | "
                  << std::setw(12)  << std::setfill(' ') << std::left  << dock->getDockStatus()          << " | "
                  << std::put_time(&entryTm, "%Y-%m-%d %H:%M:%S")  << " | ";
        if(exitTime != -1)
            std::cout <<std::put_time(&exitTm, "%Y-%m-%d %H:%M:%S")   << " | " << std::endl;
        else
            std::cout << "N/A" << std::endl;
    }
}

// ��ũ�� �԰� ó���մϴ�.
// ��ũ�� ���¸� '�԰�'�� �����ϰ�, ���� �ð��� ���� �ð����� �����մϴ�.
// @param id �԰� ó���� ��ũ�� ���� ID
// @param vehicleNumber �԰�Ǵ� ���� ��ȣ
// @param quantity �԰�Ǵ� ��ǰ�� ����
// @param itemType ��ǰ�� ����
void DockManager::checkIn(int dockId, const std::string& vehicleNumber, int itemQuantity, const std::string& itemType) {
    // ���ο� ��ũ ��ü�� �����ϰ� ��ũ ��Ͽ� �߰��մϴ�.
    auto dock = std::make_unique<Dock>(dockId, vehicleNumber, itemQuantity, itemType, "Checked In", std::time(nullptr), -1);
    addDockToList(std::move(dock));
}

// ��ũ�� ��� ó���մϴ�.
// ��ũ�� ���¸� '���'�� �����ϰ�, ���� �ð��� ���� �ð����� �����մϴ�.
// @param id ��� ó���� ��ũ�� ���� ID
void DockManager::checkOut(int dockId) {
    Dock* dock = searchDock(dockId);
    if (dock) {
        // ��ũ�� ���¸� '���'�� �����ϰ� ���� �ð��� ���� �ð����� �����մϴ�.
        dock->setDockStatus("Checked Out");
        dock->setExitTime(std::time(nullptr));
        std::cout<< dockId <<" Dock has been cheched out!"<<std::endl;
    } else {
        std::cout << "Dock not found." << std::endl;
    }
}

// CSV ������ �����͸� �Ľ��Ͽ� ���ͷ� ��ȯ�մϴ�.
// @param file �Է� ��Ʈ��
// @param delimiter CSV �������� ������
// @return �Ľ̵� �����Ͱ� ��� ���ڿ� ����
std::vector<std::string> DockManager::parseCSV(std::istream& file, char delimiter) {
    std::stringstream ss;
    std::vector<std::string> row;
    std::string token;
    char c;

    // ���Ͽ��� ���ڸ� �о�ͼ� ��ū���� �и��մϴ�.
    while (file.get(c)) {
        if (c == delimiter || c == '\r' || c == '\n') {
            if (c == '\n' && file.peek() == '\r') file.get(); // Windows�� '\r'�� �����մϴ�.
            token = ss.str();
            row.push_back(token);
            ss.str("");
            ss.clear();
            if (c == '\n') break;
        } else {
            ss << c;
        }
    }
    if (!ss.str().empty()) {
        row.push_back(ss.str());
    }
    return row;
}

// ����ڿ��� �޴��� �����ְ� ���ÿ� ���� ������ �۾��� �����մϴ�.
// @return ����ڰ� ���α׷� ���Ḧ �����ϸ� false, ��� ������ ��� true
bool DockManager::displayMenu() {
    int choice, dockId, itemQuantity;
    std::string vehicleNumber, itemType;

#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H"; // ȭ���� ����� Ŀ���� �� ���� �̵��մϴ�.
#endif
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "              Dock Manager                   " << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "  1. Display Dock List                       " << std::endl;
    std::cout << "  2. Dock Check In                           " << std::endl;
    std::cout << "  3. Dock Check Out                          " << std::endl;
    std::cout << "  4. Modify DockList                         " << std::endl;
    std::cout << "  5. Remove Dock From DockList               " << std::endl;
    std::cout << "  6. Quit this Program                       " << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << " What do you wanna do? ";
    std::cin >> choice;


    switch (choice) {
    case 1:
        displayDockList(); // ��ũ ����� ����մϴ�.
        std::cin.ignore();
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::getchar(); // ����ڰ� ���͸� ���� ������ ��ٸ��ϴ�.
        break;
    case 2:
        std::cout << "Enter Dock ID to check in: "; std::cin >> dockId;
        std::cout << "Enter Vehicle Number: "; std::cin >> vehicleNumber;
        std::cout << "Enter Item Quantity: "; std::cin >> itemQuantity;
        std::cout << "Enter Item Type: "; std::cin >> itemType;
        checkIn(dockId, vehicleNumber, itemQuantity, itemType); // �԰� ó��
        break;
    case 3:
        displayDockList(); // ��ũ ����� ����մϴ�.
        std::cin.ignore();
        std::cout << "\nEnter Dock ID to check out : "; std::cin >> dockId;
        checkOut(dockId); // ��� ó��
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::cin.ignore();
        std::getchar(); // ����ڰ� ���͸� ���� ������ ��ٸ��ϴ�.
        break;
    case 4:
        displayDockList(); // ��ũ ����� ����մϴ�.
        std::cin.ignore();
        std::cout << "Enter Dock ID to modify: "; std::cin >> dockId;
        modifyDock(dockId); // ��ũ ����
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::cin.ignore();
        std::getchar(); // ����ڰ� ���͸� ���� ������ ��ٸ��ϴ�.
        break;
    case 5:
        displayDockList(); // ��ũ ����� ����մϴ�.
        std::cin.ignore();
        std::cout << "Enter Dock ID to remove: "; std::cin >> dockId;
        removeDockFromList(dockId); // ��ũ ����
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::cin.ignore();
        std::getchar(); // ����ڰ� ���͸� ���� ������ ��ٸ��ϴ�.
        break;
    case 6:
        return false; // ���α׷� ����
    default:
        std::cout << "\nInvalid option. Please try again." << std::endl;
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::cin.ignore();
        std::getchar(); // ����ڰ� ���͸� ���� ������ ��ٸ��ϴ�.
    }
    return true; // �޴� ��� ǥ��
}


// ���ο� ��ũ�� �Ҵ��� ���� ID�� �����մϴ�.
// ��ũ ����� ��� ������ 1�� ��ȯ�ϰ�, �׷��� ������ ������ ID���� 1 ū ���� ��ȯ�մϴ�.
// @return �� ��ũ�� ���� ID
int DockManager::makeId() const {
    return dockList.empty() ? 1 : dockList.rbegin()->first + 1;
}
