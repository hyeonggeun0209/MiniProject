#include "dock.h"

using namespace std;

// Dock Ŭ������ ������ ����
// �� �����ڴ� Dock ��ü�� �ʱ�ȭ�ϴ� �� ���˴ϴ�.
// �� �Ű������� Dock ��ü�� �پ��� �Ӽ��� �����ϴ� �� ���˴ϴ�.
Dock::Dock(int dockId, const string& vehicleNumber, int itemQuantity, const string& itemType, const string& dockStatus, time_t entryTime, time_t exitTime)
    : m_dockId(dockId), // ��ũ�� ID�� �����մϴ�.
    m_vehicleNumber(vehicleNumber), // ���� ��ȣ�� �����մϴ�.
    m_itemQuantity(itemQuantity), // ��ǰ ������ �����մϴ�.
    m_itemType(itemType), // ��ǰ ������ �����մϴ�.
    m_dockStatus(dockStatus), // ��ũ�� ���� ���¸� �����մϴ�.
    m_entryTime(entryTime), // ��ǰ�� ��ũ�� �԰�� �ð��� �����մϴ�.
    m_exitTime(exitTime) // ��ǰ�� ��ũ���� ���� �ð��� �����մϴ�.
{
}

// ���� ��ȣ�� ��ȯ�ϴ� �޼���
string Dock::getVehicleNumber() const
{
    return m_vehicleNumber; // ���� ��ȣ�� ��ȯ�մϴ�.
}

// ���� ��ȣ�� �����ϴ� �޼���
void Dock::setVehicleNumber(const string& vehicleNumber)
{
    m_vehicleNumber = vehicleNumber; // �־��� ���� ��ȣ�� ��ũ�� ���� ��ȣ�� �����մϴ�.
}

// ��ǰ ������ ��ȯ�ϴ� �޼���
int Dock::getItemQuantity() const
{
    return m_itemQuantity; // ��ǰ ������ ��ȯ�մϴ�.
}

// ��ǰ ������ �����ϴ� �޼���
void Dock::setItemQuantity(int itemQuantity)
{
    m_itemQuantity = itemQuantity; // �־��� �������� ��ũ�� ��ǰ ������ �����մϴ�.
}

// ��ǰ ������ ��ȯ�ϴ� �޼���
string Dock::getItemType() const
{
    return m_itemType; // ��ǰ ������ ��ȯ�մϴ�.
}

// ��ǰ ������ �����ϴ� �޼���
void Dock::setItemType(const string& itemType)
{
    m_itemType = itemType; // �־��� ��ǰ ������ ��ũ�� ��ǰ ������ �����մϴ�.
}

// ��ũ ���¸� ��ȯ�ϴ� �޼���
string Dock::getDockStatus() const
{
    return m_dockStatus; // ��ũ�� ���¸� ��ȯ�մϴ�.
}

// ��ũ ���¸� �����ϴ� �޼���
void Dock::setDockStatus(const string& dockStatus)
{
    m_dockStatus = dockStatus; // �־��� ���·� ��ũ�� ���¸� �����մϴ�.
}

// �԰� �ð��� ��ȯ�ϴ� �޼���
time_t Dock::getEntryTime() const
{
    return m_entryTime; // �԰� �ð��� ��ȯ�մϴ�.
}

// �԰� �ð��� �����ϴ� �޼���
void Dock::setEntryTime(time_t entryTime)
{
    m_entryTime = entryTime; // �־��� �԰� �ð����� ��ũ�� �԰� �ð��� �����մϴ�.
}

// ��� �ð��� ��ȯ�ϴ� �޼���
time_t Dock::getExitTime() const
{
    return m_exitTime; // ��� �ð��� ��ȯ�մϴ�.
}

// ��� �ð��� �����ϴ� �޼���
void Dock::setExitTime(time_t exitTime)
{
    m_exitTime = exitTime; // �־��� ��� �ð����� ��ũ�� ��� �ð��� �����մϴ�.
}

// ��ũ�� ID�� ��ȯ�ϴ� �޼���
int Dock::getDockId() const
{
    return m_dockId; // ��ũ�� ID�� ��ȯ�մϴ�.
}

// ���� �� ������ ����
// �� Dock ��ü�� �������� ���մϴ�. ��� �Ӽ����� �����ϸ� true�� ��ȯ�մϴ�.
bool Dock::operator==(const Dock &other) const {
    return (m_dockId == other.m_dockId && // ID ��
            m_vehicleNumber == other.m_vehicleNumber && // ���� ��ȣ ��
            m_itemQuantity == other.m_itemQuantity && // ��ǰ ���� ��
            m_itemType == other.m_itemType && // ��ǰ ���� ��
            m_dockStatus == other.m_dockStatus && // ���� ��
            m_entryTime == other.m_entryTime && // �԰� �ð� ��
            m_exitTime == other.m_exitTime); // ��� �ð� ��
}
