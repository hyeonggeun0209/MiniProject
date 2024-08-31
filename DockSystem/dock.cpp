#include "dock.h"

using namespace std;

// Dock Ŭ������ ������ ����
// �� �����ڴ� Dock ��ü�� �ʱ�ȭ�ϴ� �� ���˴ϴ�.
// �� �Ű������� Dock ��ü�� �پ��� �Ӽ��� �����ϴ� �� ���˴ϴ�.
Dock::Dock(int id, const string& vehicleNumber, int quantity, const string& itemType, const string& status, time_t entryTime, time_t exitTime)
    : m_id(id), // ��ũ�� ID�� �����մϴ�.
    m_vehicleNumber(vehicleNumber), // ���� ��ȣ�� �����մϴ�.
    m_quantity(quantity), // ��ǰ ������ �����մϴ�.
    m_itemType(itemType), // ��ǰ ������ �����մϴ�.
    m_status(status), // ��ũ�� ���� ���¸� �����մϴ�.
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
int Dock::getQuantity() const
{
    return m_quantity; // ��ǰ ������ ��ȯ�մϴ�.
}

// ��ǰ ������ �����ϴ� �޼���
void Dock::setQuantity(int quantity)
{
    m_quantity = quantity; // �־��� �������� ��ũ�� ��ǰ ������ �����մϴ�.
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
string Dock::getStatus() const
{
    return m_status; // ��ũ�� ���¸� ��ȯ�մϴ�.
}

// ��ũ ���¸� �����ϴ� �޼���
void Dock::setStatus(const string& status)
{
    m_status = status; // �־��� ���·� ��ũ�� ���¸� �����մϴ�.
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
int Dock::getId() const
{
    return m_id; // ��ũ�� ID�� ��ȯ�մϴ�.
}

// ���� �� ������ ����
// �� Dock ��ü�� �������� ���մϴ�. ��� �Ӽ����� �����ϸ� true�� ��ȯ�մϴ�.
bool Dock::operator==(const Dock &other) const {
    return (m_id == other.m_id && // ID ��
            m_vehicleNumber == other.m_vehicleNumber && // ���� ��ȣ ��
            m_quantity == other.m_quantity && // ��ǰ ���� ��
            m_itemType == other.m_itemType && // ��ǰ ���� ��
            m_status == other.m_status && // ���� ��
            m_entryTime == other.m_entryTime && // �԰� �ð� ��
            m_exitTime == other.m_exitTime); // ��� �ð� ��
}
