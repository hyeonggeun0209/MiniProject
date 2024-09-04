#ifndef DOCK_H
#define DOCK_H

#include <string>
#include <ctime>

class Dock {
public:
    /**
     * @brief �⺻ ������ �� �Ű�����ȭ�� ������
     *
     * �⺻�� �Ǵ� ����� ���� ������ Dock ��ü�� �ʱ�ȭ
     * @param dockId ��ũ�� ���� ID (�⺻��: 0)
     * @param vehicleNumber ���� ��ȣ (�⺻��: �� ���ڿ�)
     * @param itemQuantity ��ǰ�� ���� (�⺻��: 0)
     * @param itemType ��ǰ�� ���� (�⺻��: �� ���ڿ�)
     * @param dockStatus ��ũ�� ���� (�⺻��: �� ���ڿ�)
     * @param entryTime ���� �ð� (�⺻��: ���� �ð�)
     * @param exitTime ���� �ð� (�⺻��: ���� �ð�)
     */
    Dock(int dockId, const std::string& vehicleNumber , int itemQuantity ,
         const std::string& itemType , const std::string& dockStatus,
         std::time_t entryTime , std::time_t exitTime );

    /**
     * @brief ���� ��ȣ�� ��ȯ�մϴ�.
     *
     * @return ���� ��ȣ
     */
    std::string getVehicleNumber() const;

    /**
     * @brief ���� ��ȣ�� �����մϴ�.
     *
     * @param vehicleNumber �� ���� ��ȣ
     */
    void setVehicleNumber(const std::string& vehicleNumber);

    /**
     * @brief ��ǰ�� ������ ��ȯ�մϴ�.
     *
     * @return ��ǰ�� ����
     */
    int getItemQuantity() const;

    /**
     * @brief ��ǰ�� ������ �����մϴ�.
     *
     * @param quantity �� ��ǰ ����
     */
    void setItemQuantity(int quantity);

    /**
     * @brief ��ǰ�� ������ ��ȯ�մϴ�.
     *
     * @return ��ǰ�� ����
     */
    std::string getItemType() const;

    /**
     * @brief ��ǰ�� ������ �����մϴ�.
     *
     * @param itemType �� ��ǰ ����
     */
    void setItemType(const std::string& itemType);

    /**
     * @brief ��ũ�� ���¸� ��ȯ�մϴ�.
     *
     * @return ��ũ�� ����
     */
    std::string getDockStatus() const;

    /**
     * @brief ��ũ�� ���¸� �����մϴ�.
     *
     * @param status �� ��ũ ����
     */
    void setDockStatus(const std::string& status);

    /**
     * @brief ���� �ð��� ��ȯ�մϴ�.
     *
     * @return ���� �ð� (std::time_t ����)
     */
    std::time_t getEntryTime() const;

    /**
     * @brief ���� �ð��� �����մϴ�.
     *
     * @param entryTime �� ���� �ð� (std::time_t ����)
     */
    void setEntryTime(std::time_t entryTime);

    /**
     * @brief ���� �ð��� ��ȯ�մϴ�.
     *
     * @return ���� �ð� (std::time_t ����)
     */
    std::time_t getExitTime() const;

    /**
     * @brief ���� �ð��� �����մϴ�.
     *
     * @param exitTime �� ���� �ð� (std::time_t ����)
     */
    void setExitTime(std::time_t exitTime);

    /**
     * @brief ��ũ�� ���� ID�� ��ȯ�մϴ�.
     *
     * @return ��ũ�� ID
     */
    int getDockId() const;

    /**
     * @brief �� Dock ��ü�� ��� �� ������
     *
     * �� Dock ��ü�� �������� ���մϴ�. ��� ��� ������ ������ ��� true�� ��ȯ�մϴ�.
     * @param other ���� �ٸ� Dock ��ü
     * @return �� Dock ��ü�� �����ϸ� true, �׷��� ������ false
     */
    bool operator==(const Dock &other) const;

private:
    int m_dockId;                    ///< ��ũ�� ���� ID
    std::string m_vehicleNumber; ///< ���� ��ȣ
    int m_itemQuantity;          ///< ��ǰ�� ����
    std::string m_itemType;      ///< ��ǰ�� ����
    std::string m_dockStatus;    ///< ��ũ�� ����
    std::time_t m_entryTime;     ///< ���� �ð�
    std::time_t m_exitTime;      ///< ���� �ð�
};

#endif // DOCK_H
