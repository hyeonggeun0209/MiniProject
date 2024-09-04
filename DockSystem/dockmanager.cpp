#include "dockmanager.h"
#include <fstream>
#include <sstream>
#include <iomanip>      // 매개변수를 가지는 조작자 헤더파일
#include <ctime>

// DockManager 생성자
// DockManager 객체를 초기화합니다.
// 현재는 기본 생성자로 초기화 작업이 추가되어 있지 않습니다.
DockManager::DockManager() {
    // 초기화 작업을 여기에 추가할 수 있음
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
                std::time_t entryTime = std::stoll(row[5]);  // 문자열을 time_t로 변환
                std::time_t exitTime = std::stoll(row[6]);   // 문자열을 time_t로 변환

                // 도크 객체를 생성하고 도크 목록에 추가
                auto dock = std::make_unique<Dock>(id, vehicleNumber, quantity, itemType, status, entryTime, exitTime);
                dockList.insert({ id, std::move(dock) });
            }
        }
    }
}

// DockManager 소멸자
// DockManager 객체가 소멸될 때 도크 목록을 파일에 저장하거나 정리 작업을 수행할 수 있습니다.
// 현재는 특별한 작업이 추가되어 있지 않습니다.
DockManager::~DockManager() {
    // 소멸자에서 파일 저장 작업을 할 수 있음
    std::ofstream file("docklist.txt");
    if (file) {
        for (const auto& entry : dockList) {
            const Dock* dock = entry.second.get();
            file << dock->getDockId() << ","
                 << dock->getVehicleNumber() << ","
                 << dock->getItemQuantity() << ","
                 << dock->getItemType() << ","
                 << dock->getDockStatus() << ","
                 << dock->getEntryTime() << ","  // time_t를 그대로 출력
                 << dock->getExitTime() << std::endl;  // time_t를 그대로 출력
        }
    }
}

// 새로운 도크를 도크 목록에 추가합니다.
// @param dock 추가할 도크 객체의 고유 포인터
void DockManager::addDockToList(std::unique_ptr<Dock> dock) {
    dockList.insert({ dock->getDockId(), std::move(dock) });
}

// 주어진 ID의 도크를 도크 목록에서 제거합니다.
// @param id 제거할 도크의 고유 ID
void DockManager::removeDockFromList(int dockId) {

    if(dockList.erase(dockId)>0)
    {
        std::cout<<"Successfully deleted"<<std::endl;
    }
    else
        std::cout << "Dock not found." << std::endl;
}

// 주어진 ID의 도크 정보를 수정합니다.
// 도크의 현재 정보를 출력하고 새로운 정보를 입력받아 업데이트합니다.
// @param id 수정할 도크의 고유 ID
void DockManager::modifyDock(int dockId) {
    Dock* dock = searchDock(dockId);
    if (dock) {
        // 도크의 현재 정보를 출력합니다.
        std::cout << "ID: " << dock->getDockId() << std::endl;
        std::cout << "Vehicle Number: " << dock->getVehicleNumber() << std::endl;
        std::cout << "Quantity: " << dock->getItemQuantity() << std::endl;
        std::cout << "Item Type: " << dock->getItemType() << std::endl;
        std::cout << "Status: " << dock->getDockStatus() << std::endl;

        // 새로운 정보를 입력받아 도크 객체를 갱신합니다.
        std::string vehicleNumber, itemType, status;
        int quantity;
        std::cout << "Enter new vehicle number: "; std::cin >> vehicleNumber;
        std::cout << "Enter new quantity: "; std::cin >> quantity;
        std::cout << "Enter new item type: "; std::cin >> itemType;
        std::cout << "Enter new status: "; std::cin >> status;

        // 도크의 속성 업데이트
        dock->setVehicleNumber(vehicleNumber);
        dock->setItemQuantity(quantity);
        dock->setItemType(itemType);
        dock->setDockStatus(status);

        std::cout << "Successfully modified"<<std::endl;
    } else {
        std::cout << "Dock not found." << std::endl;
    }
}

// 주어진 ID의 도크를 검색하여 반환합니다.
// @param id 검색할 도크의 고유 ID
// @return 주어진 ID의 도크 객체 포인터. ID가 존재하지 않으면 nullptr
Dock* DockManager::searchDock(int dockId) const {
    auto it = dockList.find(dockId);
    return it != dockList.end() ? it->second.get() : nullptr;
    std::cout<< dockId <<" ID is wrong!"<<std::endl;

}

// 모든 도크의 정보를 출력합니다.
// 도크 목록에 있는 모든 도크의 정보를 포맷에 맞춰 출력합니다.
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

        // 도크의 입차 및 출차 시간을 로컬 시간으로 변환합니다.
        std::time_t entryTime = dock->getEntryTime();
        std::time_t exitTime = dock->getExitTime();



        std::tm entryTm;
        std::tm exitTm;

        // localtime_s 함수는 첫 번째 매개변수로 std::tm* 구조체를 받고, 두 번째 매개변수로 std::time_t*를 받습니다.
#ifdef _WIN32
        localtime_s(&entryTm, &entryTime);
        localtime_s(&exitTm, &exitTime);
#else
        localtime_l(&entryTm, &entryTime);
        localtime_l(&exitTm, &exitTime);
#endif


        // 도크 정보를 포맷에 맞춰 출력합니다.
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

// 도크를 입고 처리합니다.
// 도크의 상태를 '입고'로 변경하고, 입차 시간을 현재 시간으로 설정합니다.
// @param id 입고 처리할 도크의 고유 ID
// @param vehicleNumber 입고되는 차량 번호
// @param quantity 입고되는 물품의 수량
// @param itemType 물품의 종류
void DockManager::checkIn(int dockId, const std::string& vehicleNumber, int itemQuantity, const std::string& itemType) {
    // 새로운 도크 객체를 생성하고 도크 목록에 추가합니다.
    auto dock = std::make_unique<Dock>(dockId, vehicleNumber, itemQuantity, itemType, "Checked In", std::time(nullptr), -1);
    addDockToList(std::move(dock));
}

// 도크를 출고 처리합니다.
// 도크의 상태를 '출고'로 변경하고, 출차 시간을 현재 시간으로 설정합니다.
// @param id 출고 처리할 도크의 고유 ID
void DockManager::checkOut(int dockId) {
    Dock* dock = searchDock(dockId);
    if (dock) {
        // 도크의 상태를 '출고'로 변경하고 출차 시간을 현재 시간으로 설정합니다.
        dock->setDockStatus("Checked Out");
        dock->setExitTime(std::time(nullptr));
        std::cout<< dockId <<" Dock has been cheched out!"<<std::endl;
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
    int choice, dockId, itemQuantity;
    std::string vehicleNumber, itemType;

#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H"; // 화면을 지우고 커서를 맨 위로 이동합니다.
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
        displayDockList(); // 도크 목록을 출력합니다.
        std::cin.ignore();
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
        break;
    case 2:
        std::cout << "Enter Dock ID to check in: "; std::cin >> dockId;
        std::cout << "Enter Vehicle Number: "; std::cin >> vehicleNumber;
        std::cout << "Enter Item Quantity: "; std::cin >> itemQuantity;
        std::cout << "Enter Item Type: "; std::cin >> itemType;
        checkIn(dockId, vehicleNumber, itemQuantity, itemType); // 입고 처리
        break;
    case 3:
        displayDockList(); // 도크 목록을 출력합니다.
        std::cin.ignore();
        std::cout << "\nEnter Dock ID to check out : "; std::cin >> dockId;
        checkOut(dockId); // 출고 처리
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::cin.ignore();
        std::getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
        break;
    case 4:
        displayDockList(); // 도크 목록을 출력합니다.
        std::cin.ignore();
        std::cout << "Enter Dock ID to modify: "; std::cin >> dockId;
        modifyDock(dockId); // 도크 수정
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::cin.ignore();
        std::getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
        break;
    case 5:
        displayDockList(); // 도크 목록을 출력합니다.
        std::cin.ignore();
        std::cout << "Enter Dock ID to remove: "; std::cin >> dockId;
        removeDockFromList(dockId); // 도크 삭제
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::cin.ignore();
        std::getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
        break;
    case 6:
        return false; // 프로그램 종료
    default:
        std::cout << "\nInvalid option. Please try again." << std::endl;
        std::cout<<"If you go back, pleas press Enter!"<<std::endl;
        std::cin.ignore();
        std::getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
    }
    return true; // 메뉴 계속 표시
}


// 새로운 도크에 할당할 고유 ID를 생성합니다.
// 도크 목록이 비어 있으면 1을 반환하고, 그렇지 않으면 마지막 ID보다 1 큰 값을 반환합니다.
// @return 새 도크의 고유 ID
int DockManager::makeId() const {
    return dockList.empty() ? 1 : dockList.rbegin()->first + 1;
}
