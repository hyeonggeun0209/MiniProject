#ifndef DOCK_MANAGER_H
#define DOCK_MANAGER_H

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "dock.h"

class DockManager {
public:
    // ������: DockManager ��ü�� �ʱ�ȭ�մϴ�.
    // �ʱ�ȭ �������� ��ũ ����� ���Ͽ��� �ε��ϰų�, �ʱ� ���¸� ������ �� �ֽ��ϴ�.
    DockManager();

    // �Ҹ���: DockManager ��ü�� �Ҹ�� �� ��ũ ����� ���Ͽ� �����մϴ�.
    // ��ũ ����� �����Ͽ� ���� ���α׷� ���� �� ��ũ ���¸� ������ �� �ֵ��� �մϴ�.
    ~DockManager();

    // ���ο� ��ũ�� ��ũ ��Ͽ� �߰��մϴ�.
    // @param dock �߰��� ��ũ ��ü�� ���� ������
    void addDock(std::unique_ptr<Dock> dock);

    // �־��� ID�� ��ũ�� ��ũ ��Ͽ��� �����մϴ�.
    // @param id ������ ��ũ�� ���� ID
    void removeDock(int id);

    // �־��� ID�� ��ũ ������ �����մϴ�.
    // ��ũ�� ���� ���¸� ����ϰ� ���ο� ������ �Է¹޾� ������Ʈ�մϴ�.
    // @param id ������ ��ũ�� ���� ID
    void modifyDock(int id);

    // �־��� ID�� ��ũ�� �˻��Ͽ� ��ȯ�մϴ�.
    // @param id �˻��� ��ũ�� ���� ID
    // @return �־��� ID�� ��ũ ��ü ������. ID�� �������� ������ nullptr
    Dock* searchDock(int id) const;

    // ��� ��ũ�� ������ ����մϴ�.
    void displayDocks() const;

    // ��ũ�� �԰� ó���մϴ�. ��ũ�� ���¸� '�԰�'�� �����ϰ� �ʿ��� ������ ������Ʈ�մϴ�.
    // @param id �԰� ó���� ��ũ�� ���� ID
    // @param vehicleNumber �԰�Ǵ� ���� ��ȣ
    // @param quantity �԰�Ǵ� ��ǰ�� ����
    // @param itemType ��ǰ�� ����
    void checkIn(int id, const std::string& vehicleNumber, int quantity, const std::string& itemType);

    // ��ũ�� ��� ó���մϴ�. ��ũ�� ���¸� '���'�� �����ϰ� ���� �ð��� ������Ʈ�մϴ�.
    // @param id ��� ó���� ��ũ�� ���� ID
    void checkOut(int id);

    // CSV ������ �����͸� �Ľ��Ͽ� ���ͷ� ��ȯ�մϴ�.
    // @param input �Է� ��Ʈ��
    // @param delimiter CSV �������� ������
    // @return �Ľ̵� �����Ͱ� ��� ���ڿ� ����
    std::vector<std::string> parseCSV(std::istream& input, char delimiter);

    // ����ڿ��� �޴��� �����ְ� ���ÿ� ���� ������ �۾��� �����մϴ�.
    // @return ����ڰ� ���α׷� ���Ḧ �����ϸ� false, ��� ������ ��� true
    bool displayMenu();

private:
    // ��ũ ����� �����ϴ� �� (ID -> ��ũ ��ü)
    std::map<int, std::unique_ptr<Dock>> dockList;

    // ���ο� ��ũ�� �Ҵ��� ���� ID�� �����մϴ�.
    // ��ũ ����� ��� ������ 0�� ��ȯ�ϰ�, �׷��� ������ ������ ID���� 1 ū ���� ��ȯ�մϴ�.
    // @return �� ��ũ�� ���� ID
    int makeId() const;
};

#endif // DOCK_MANAGER_H
