#include "dockmanager.h"
#include <iostream>
#include <iomanip>
#include <ctime>

// ���� �ð��� "YYYY-MM-DD HH:MM:SS" �������� ����ϴ� �Լ�
void displayCurrentTime() {
    // ���� �ð��� time_t �������� �����ɴϴ�.
    std::time_t now = std::time(nullptr);

    std::tm nowTm;
    localtime_s(&nowTm,&now);

    // ���� �ð��� ���� �ð����� ��ȯ�ϰ� ������ �������� ����մϴ�.
    std::cout << std::put_time(&nowTm, "%Y-%m-%d %H:%M:%S") << std::endl;
}

int main() {
    // DockManager ��ü�� �����մϴ�.
    // �� ��ü�� ��ũ�� �߰�, ����, ����, �˻�, �԰�, ��� ���� �����մϴ�.
    DockManager manager;

    // ���α׷��� ��� ����� �� �ֵ��� �ϴ� ������ �����մϴ�.
    bool continueRunning = true;

    // ����ڰ� ���α׷��� ������ ������ �޴��� �ݺ��Ͽ� ǥ���ϰ� �Է��� ó���մϴ�.
    while (continueRunning) {
        // �޴��� ǥ���ϰ� ������� ���ÿ� ���� ������ �۾��� �����մϴ�.
        // ����ڰ� ���α׷� ���Ḧ �����ϸ� continueRunning�� false�� �����˴ϴ�.
        continueRunning = manager.displayMenu();
    }

    // ���α׷��� ����� �� 0�� ��ȯ�Ͽ� ���������� ������� �˸��ϴ�.
    return 0;
}
