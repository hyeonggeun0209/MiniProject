#include "dockmanager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

// DockManager 생성자
// DockManager 객체를 초기화합니다.
// 현재는 기본 생성자로 초기화 작업이 추가되어 있지 않습니다.
DockManager::DockManager() {
    // 초기화 작업을 여기에 추가할 수 있음
}

// DockManager 소멸자
// DockManager 객체가 소멸될 때 도크 목록을 파일에 저장하거나 정리 작업을 수행할 수 있습니다.
// 현재는 특별한 작업이 추가되어 있지 않습니다.
DockManager::~DockManager() {
    // 소멸자에서 파일 저장 작업을 할 수 있음
}

// 새로운 도크를 도크 목록에 추가합니다.
// @param dock 추가할 도크 객체의 고유 포인터
void DockManager::addDock(std::unique_ptr<Dock> dock) {
    dockList.insert({ dock->getId(), std::move(dock) });
}

// 주어진 ID의 도크를 도크 목록에서 제거합니다.
// @param id 제거할 도크의 고유 ID
void DockManager::removeDock(int id) {
    dockList.erase(id);
}

// 주어진 ID의 도크 정보를 수정합니다.
// 도크의 현재 정보를 출력하고 새로운 정보를 입력받아 업데이트합니다.
// @param id 수정할 도크의 고유 ID
void DockManager::modifyDock(int id) {
    Dock* dock = searchDock(id);
    if (dock) {
        // 도크의 현재 정보를 출력합니다.
        std::cout << "ID: " << dock->getId() << std::endl;
        std::cout << "Vehicle Number: " << dock->getVehicleNumber() << std::endl;
        std::cout << "Quantity: " << dock->getQuantity() << std::endl;
        std::cout << "Item Type: " << dock->getItemType() << std::endl;
        std::cout << "Status: " << dock->getStatus() << std::endl;

        // 새로운 정보를 입력받아 도크 객체를 갱신합니다.
        std::string vehicleNumber, itemType, status;
        int quantity;
        std::cout << "Enter new vehicle number: "; std::cin >> vehicleNumber;
        std::cout << "Enter new quantity: "; std::cin >> quantity;
        std::cout << "Enter new item type: "; std::cin >> itemType;
        std::cout << "Enter new status: "; std::cin >> status;

        // 도크의 속성 업데이트
        dock->setVehicleNumber(vehicleNumber);
        dock->setQuantity(quantity);
        dock->setItemType(itemType);
        dock->setStatus(status);
    } else {
        std::cout << "Dock not found." << std::endl;
    }
}

// 주어진 ID의 도크를 검색하여 반환합니다.
// @param id 검색할 도크의 고유 ID
// @return 주어진 ID의 도크 객체 포인터. ID가 존재하지 않으면 nullptr
Dock* DockManager::searchDock(int id) const {
    auto it = dockList.find(id);
    return it != dockList.end() ? it->second.get() : nullptr;
}

// 모든 도크의 정보를 출력합니다.
// 도크 목록에 있는 모든 도크의 정보를 포맷에 맞춰 출력합니다.
void DockManager::displayDocks() const {
    std::cout << std::endl << "  ID  | Vehicle Number | Quantity | Item Type | Status | Entry Time | Exit Time" << std::endl;
    for (const auto& entry : dockList) {
        const Dock* dock = entry.second.get();

        // 도크의 입차 및 출차 시간을 로컬 시간으로 변환합니다.
        std::time_t entryTime = dock->getEntryTime();
        std::time_t exitTime = dock->getExitTime();
        std::tm* entryTm = std::localtime(&entryTime);
        std::tm* exitTm = std::localtime(&exitTime);

        // 도크 정보를 포맷에 맞춰 출력합니다.
        std::cout << std::setw(5) << std::setfill(' ') << std::right << dock->getId() << " | "
                  << std::setw(15) << std::left << dock->getVehicleNumber() << " | "
                  << std::setw(8) << dock->getQuantity() << " | "
                  << std::setw(9) << dock->getItemType() << " | "
                  << std::setw(6) << dock->getStatus() << " | "
                  << std::put_time(entryTm, "%Y-%m-%d %H:%M:%S") << " | "
                  << std::put_time(exitTm, "%Y-%m-%d %H:%M:%S") << std::endl;
    }
}

// 도크를 입고 처리합니다.
// 도크의 상태를 '입고'로 변경하고, 입차 시간을 현재 시간으로 설정합니다.
// @param id 입고 처리할 도크의 고유 ID
// @param vehicleNumber 입고되는 차량 번호
// @param quantity 입고되는 물품의 수량
// @param itemType 물품의 종류
void DockManager::checkIn(int id, const std::string& vehicleNumber, int quantity, const std::string& itemType) {
    // 새로운 도크 객체를 생성하고 도크 목록에 추가합니다.
    auto dock = std::make_unique<Dock>(id, vehicleNumber, quantity, itemType, "Checked In", std::time(nullptr), std::time(nullptr));
    addDock(std::move(dock));
}

// 도크를 출고 처리합니다.
// 도크의 상태를 '출고'로 변경하고, 출차 시간을 현재 시간으로 설정합니다.
// @param id 출고 처리할 도크의 고유 ID
void DockManager::checkOut(int id) {
    Dock* dock = searchDock(id);
    if (dock) {
        // 도크의 상태를 '출고'로 변경하고 출차 시간을 현재 시간으로 설정합니다.
        dock->setStatus("Checked Out");
        dock->setExitTime(std::time(nullptr));
    } else {
        std::cout << "Dock not found." << std::endl;
    }
}

// CSV 형식의 데이터를 파싱하여 벡터로 반환합니다.
// @param file 입력 스트림
// @param delimiter CSV 데이터의 구분자
// @return 파싱된 데이터가 담긴 문자열 벡터
std::vector<std::string> DockManager::parseCSV(std::istream& file, char delimiter) {
    std::stringstream ss;
    std::vector<std::string> row;
    std::string token;
    char c;

    // 파일에서 문자를 읽어와서 토큰으로 분리합니다.
    while (file.get(c)) {
        if (c == delimiter || c == '\r' || c == '\n') {
            if (c == '\n' && file.peek() == '\r') file.get(); // Windows의 '\r'을 무시합니다.
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

// 사용자에게 메뉴를 보여주고 선택에 따라 적절한 작업을 수행합니다.
// @return 사용자가 프로그램 종료를 선택하면 false, 계속 실행할 경우 true
bool DockManager::displayMenu() {
    int choice, id, quantity;
    std::string vehicleNumber, itemType;

    std::cout << "\033[2J\033[1;1H"; // 화면을 지우고 커서를 맨 위로 이동합니다.
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
        displayDocks(); // 도크 목록을 출력합니다.
        std::cin.ignore();
        std::getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
        break;
    case 2:
        std::cout << "Enter Dock ID: "; std::cin >> id;
        std::cout << "Enter Vehicle Number: "; std::cin >> vehicleNumber;
        std::cout << "Enter Quantity: "; std::cin >> quantity;
        std::cout << "Enter Item Type: "; std::cin >> itemType;
        checkIn(id, vehicleNumber, quantity, itemType); // 입고 처리
        break;
    case 3:
        std::cout << "Enter Dock ID: "; std::cin >> id;
        checkOut(id); // 출고 처리
        break;
    case 4:
        std::cout << "Enter Dock ID to modify: "; std::cin >> id;
        modifyDock(id); // 도크 수정
        break;
    case 5:
        std::cout << "Enter Dock ID to remove: "; std::cin >> id;
        removeDock(id); // 도크 삭제
        break;
    case 6:
        return false; // 프로그램 종료
    default:
        std::cout << "Invalid option. Please try again." << std::endl;
    }
    return true; // 메뉴 계속 표시
}

// 새로운 도크에 할당할 고유 ID를 생성합니다.
// 도크 목록이 비어 있으면 1을 반환하고, 그렇지 않으면 마지막 ID보다 1 큰 값을 반환합니다.
// @return 새 도크의 고유 ID
int DockManager::makeId() const {
    return dockList.empty() ? 1 : dockList.rbegin()->first + 1;
}
