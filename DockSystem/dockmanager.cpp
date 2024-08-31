#include "dockmanager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

// DockManager ������
// DockManager ��ü�� �ʱ�ȭ�մϴ�.
// ����� �⺻ �����ڷ� �ʱ�ȭ �۾��� �߰��Ǿ� ���� �ʽ��ϴ�.
DockManager::DockManager() {
    // �ʱ�ȭ �۾��� ���⿡ �߰��� �� ����
}

// DockManager �Ҹ���
// DockManager ��ü�� �Ҹ�� �� ��ũ ����� ���Ͽ� �����ϰų� ���� �۾��� ������ �� �ֽ��ϴ�.
// ����� Ư���� �۾��� �߰��Ǿ� ���� �ʽ��ϴ�.
DockManager::~DockManager() {
    // �Ҹ��ڿ��� ���� ���� �۾��� �� �� ����
}

// ���ο� ��ũ�� ��ũ ��Ͽ� �߰��մϴ�.
// @param dock �߰��� ��ũ ��ü�� ���� ������
void DockManager::addDock(std::unique_ptr<Dock> dock) {
    dockList.insert({ dock->getId(), std::move(dock) });
}

// �־��� ID�� ��ũ�� ��ũ ��Ͽ��� �����մϴ�.
// @param id ������ ��ũ�� ���� ID
void DockManager::removeDock(int id) {
    dockList.erase(id);
}

// �־��� ID�� ��ũ ������ �����մϴ�.
// ��ũ�� ���� ������ ����ϰ� ���ο� ������ �Է¹޾� ������Ʈ�մϴ�.
// @param id ������ ��ũ�� ���� ID
void DockManager::modifyDock(int id) {
    Dock* dock = searchDock(id);
    if (dock) {
        // ��ũ�� ���� ������ ����մϴ�.
        std::cout << "ID: " << dock->getId() << std::endl;
        std::cout << "Vehicle Number: " << dock->getVehicleNumber() << std::endl;
        std::cout << "Quantity: " << dock->getQuantity() << std::endl;
        std::cout << "Item Type: " << dock->getItemType() << std::endl;
        std::cout << "Status: " << dock->getStatus() << std::endl;

        // ���ο� ������ �Է¹޾� ��ũ ��ü�� �����մϴ�.
        std::string vehicleNumber, itemType, status;
        int quantity;
        std::cout << "Enter new vehicle number: "; std::cin >> vehicleNumber;
        std::cout << "Enter new quantity: "; std::cin >> quantity;
        std::cout << "Enter new item type: "; std::cin >> itemType;
        std::cout << "Enter new status: "; std::cin >> status;

        // ��ũ�� �Ӽ� ������Ʈ
        dock->setVehicleNumber(vehicleNumber);
        dock->setQuantity(quantity);
        dock->setItemType(itemType);
        dock->setStatus(status);
    } else {
        std::cout << "Dock not found." << std::endl;
    }
}

// �־��� ID�� ��ũ�� �˻��Ͽ� ��ȯ�մϴ�.
// @param id �˻��� ��ũ�� ���� ID
// @return �־��� ID�� ��ũ ��ü ������. ID�� �������� ������ nullptr
Dock* DockManager::searchDock(int id) const {
    auto it = dockList.find(id);
    return it != dockList.end() ? it->second.get() : nullptr;
}

// ��� ��ũ�� ������ ����մϴ�.
// ��ũ ��Ͽ� �ִ� ��� ��ũ�� ������ ���˿� ���� ����մϴ�.
void DockManager::displayDocks() const {
    std::cout << std::endl << "  ID  | Vehicle Number | Quantity | Item Type | Status | Entry Time | Exit Time" << std::endl;
    for (const auto& entry : dockList) {
        const Dock* dock = entry.second.get();

        // ��ũ�� ���� �� ���� �ð��� ���� �ð����� ��ȯ�մϴ�.
        std::time_t entryTime = dock->getEntryTime();
        std::time_t exitTime = dock->getExitTime();
        std::tm* entryTm = std::localtime(&entryTime);
        std::tm* exitTm = std::localtime(&exitTime);

        // ��ũ ������ ���˿� ���� ����մϴ�.
        std::cout << std::setw(5) << std::setfill(' ') << std::right << dock->getId() << " | "
                  << std::setw(15) << std::left << dock->getVehicleNumber() << " | "
                  << std::setw(8) << dock->getQuantity() << " | "
                  << std::setw(9) << dock->getItemType() << " | "
                  << std::setw(6) << dock->getStatus() << " | "
                  << std::put_time(entryTm, "%Y-%m-%d %H:%M:%S") << " | "
                  << std::put_time(exitTm, "%Y-%m-%d %H:%M:%S") << std::endl;
    }
}

// ��ũ�� �԰� ó���մϴ�.
// ��ũ�� ���¸� '�԰�'�� �����ϰ�, ���� �ð��� ���� �ð����� �����մϴ�.
// @param id �԰� ó���� ��ũ�� ���� ID
// @param vehicleNumber �԰�Ǵ� ���� ��ȣ
// @param quantity �԰�Ǵ� ��ǰ�� ����
// @param itemType ��ǰ�� ����
void DockManager::checkIn(int id, const std::string& vehicleNumber, int quantity, const std::string& itemType) {
    // ���ο� ��ũ ��ü�� �����ϰ� ��ũ ��Ͽ� �߰��մϴ�.
    auto dock = std::make_unique<Dock>(id, vehicleNumber, quantity, itemType, "Checked In", std::time(nullptr), std::time(nullptr));
    addDock(std::move(dock));
}

// ��ũ�� ��� ó���մϴ�.
// ��ũ�� ���¸� '���'�� �����ϰ�, ���� �ð��� ���� �ð����� �����մϴ�.
// @param id ��� ó���� ��ũ�� ���� ID
void DockManager::checkOut(int id) {
    Dock* dock = searchDock(id);
    if (dock) {
        // ��ũ�� ���¸� '���'�� �����ϰ� ���� �ð��� ���� �ð����� �����մϴ�.
        dock->setStatus("Checked Out");
        dock->setExitTime(std::time(nullptr));
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
    int choice, id, quantity;
    std::string vehicleNumber, itemType;

    std::cout << "\033[2J\033[1;1H"; // ȭ���� ����� Ŀ���� �� ���� �̵��մϴ�.
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "              Dock Manager                   " << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "  1. Display Dock List                       " << std::endl;
    std::cout << "  2. Check In                               " << std::endl;
    std::cout << "  3. Check Out                              " << std::endl;
    std::cout << "  4. Modify Dock                            " << std::endl;
    std::cout << "  5. Remove Dock                            " << std::endl;
    std::cout << "  6. Quit this Program                      " << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << " What do you wanna do? ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        displayDocks(); // ��ũ ����� ����մϴ�.
        std::cin.ignore();
        std::getchar(); // ����ڰ� ���͸� ���� ������ ��ٸ��ϴ�.
        break;
    case 2:
        std::cout << "Enter Dock ID: "; std::cin >> id;
        std::cout << "Enter Vehicle Number: "; std::cin >> vehicleNumber;
        std::cout << "Enter Quantity: "; std::cin >> quantity;
        std::cout << "Enter Item Type: "; std::cin >> itemType;
        checkIn(id, vehicleNumber, quantity, itemType); // �԰� ó��
        break;
    case 3:
        std::cout << "Enter Dock ID: "; std::cin >> id;
        checkOut(id); // ��� ó��
        break;
    case 4:
        std::cout << "Enter Dock ID to modify: "; std::cin >> id;
        modifyDock(id); // ��ũ ����
        break;
    case 5:
        std::cout << "Enter Dock ID to remove: "; std::cin >> id;
        removeDock(id); // ��ũ ����
        break;
    case 6:
        return false; // ���α׷� ����
    default:
        std::cout << "Invalid option. Please try again." << std::endl;
    }
    return true; // �޴� ��� ǥ��
}

// ���ο� ��ũ�� �Ҵ��� ���� ID�� �����մϴ�.
// ��ũ ����� ��� ������ 1�� ��ȯ�ϰ�, �׷��� ������ ������ ID���� 1 ū ���� ��ȯ�մϴ�.
// @return �� ��ũ�� ���� ID
int DockManager::makeId() const {
    return dockList.empty() ? 1 : dockList.rbegin()->first + 1;
}
