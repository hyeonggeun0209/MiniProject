#include "dockmanager.h"
#include <iostream>
#include <iomanip>
#include <ctime>

// 현재 시간을 "YYYY-MM-DD HH:MM:SS" 형식으로 출력하는 함수
void displayCurrentTime() {
    // 현재 시간을 time_t 형식으로 가져옵니다.
    std::time_t now = std::time(nullptr);

    std::tm nowTm;
    localtime_s(&nowTm,&now);

    // 현재 시간을 로컬 시간으로 변환하고 지정된 형식으로 출력합니다.
    std::cout << std::put_time(&nowTm, "%Y-%m-%d %H:%M:%S") << std::endl;
}

int main() {
    // DockManager 객체를 생성합니다.
    // 이 객체는 도크의 추가, 삭제, 수정, 검색, 입고, 출고 등을 관리합니다.
    DockManager manager;

    // 프로그램이 계속 실행될 수 있도록 하는 변수를 설정합니다.
    bool continueRunning = true;

    // 사용자가 프로그램을 종료할 때까지 메뉴를 반복하여 표시하고 입력을 처리합니다.
    while (continueRunning) {
        // 메뉴를 표시하고 사용자의 선택에 따라 적절한 작업을 수행합니다.
        // 사용자가 프로그램 종료를 선택하면 continueRunning이 false로 설정됩니다.
        continueRunning = manager.displayMenu();
    }

    // 프로그램이 종료될 때 0을 반환하여 성공적으로 종료됨을 알립니다.
    return 0;
}
