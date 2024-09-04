#ifndef DOCK_H
#define DOCK_H

#include <string>
#include <ctime>

class Dock {
public:
    /**
     * @brief 기본 생성자 및 매개변수화된 생성자
     *
     * 기본값 또는 사용자 지정 값으로 Dock 객체를 초기화
     * @param dockId 도크의 고유 ID (기본값: 0)
     * @param vehicleNumber 차량 번호 (기본값: 빈 문자열)
     * @param itemQuantity 상품의 수량 (기본값: 0)
     * @param itemType 상품의 종류 (기본값: 빈 문자열)
     * @param dockStatus 도크의 상태 (기본값: 빈 문자열)
     * @param entryTime 입차 시간 (기본값: 현재 시간)
     * @param exitTime 출차 시간 (기본값: 현재 시간)
     */
    Dock(int dockId, const std::string& vehicleNumber , int itemQuantity ,
         const std::string& itemType , const std::string& dockStatus,
         std::time_t entryTime , std::time_t exitTime );

    /**
     * @brief 차량 번호를 반환합니다.
     *
     * @return 차량 번호
     */
    std::string getVehicleNumber() const;

    /**
     * @brief 차량 번호를 설정합니다.
     *
     * @param vehicleNumber 새 차량 번호
     */
    void setVehicleNumber(const std::string& vehicleNumber);

    /**
     * @brief 상품의 수량을 반환합니다.
     *
     * @return 상품의 수량
     */
    int getItemQuantity() const;

    /**
     * @brief 상품의 수량을 설정합니다.
     *
     * @param quantity 새 상품 수량
     */
    void setItemQuantity(int quantity);

    /**
     * @brief 상품의 종류를 반환합니다.
     *
     * @return 상품의 종류
     */
    std::string getItemType() const;

    /**
     * @brief 상품의 종류를 설정합니다.
     *
     * @param itemType 새 상품 종류
     */
    void setItemType(const std::string& itemType);

    /**
     * @brief 도크의 상태를 반환합니다.
     *
     * @return 도크의 상태
     */
    std::string getDockStatus() const;

    /**
     * @brief 도크의 상태를 설정합니다.
     *
     * @param status 새 도크 상태
     */
    void setDockStatus(const std::string& status);

    /**
     * @brief 입차 시간을 반환합니다.
     *
     * @return 입차 시간 (std::time_t 형식)
     */
    std::time_t getEntryTime() const;

    /**
     * @brief 입차 시간을 설정합니다.
     *
     * @param entryTime 새 입차 시간 (std::time_t 형식)
     */
    void setEntryTime(std::time_t entryTime);

    /**
     * @brief 출차 시간을 반환합니다.
     *
     * @return 출차 시간 (std::time_t 형식)
     */
    std::time_t getExitTime() const;

    /**
     * @brief 출차 시간을 설정합니다.
     *
     * @param exitTime 새 출차 시간 (std::time_t 형식)
     */
    void setExitTime(std::time_t exitTime);

    /**
     * @brief 도크의 고유 ID를 반환합니다.
     *
     * @return 도크의 ID
     */
    int getDockId() const;

    /**
     * @brief 두 Dock 객체의 동등성 비교 연산자
     *
     * 두 Dock 객체가 동일한지 비교합니다. 모든 멤버 변수가 동일할 경우 true를 반환합니다.
     * @param other 비교할 다른 Dock 객체
     * @return 두 Dock 객체가 동일하면 true, 그렇지 않으면 false
     */
    bool operator==(const Dock &other) const;

private:
    int m_dockId;                    ///< 도크의 고유 ID
    std::string m_vehicleNumber; ///< 차량 번호
    int m_itemQuantity;          ///< 상품의 수량
    std::string m_itemType;      ///< 상품의 종류
    std::string m_dockStatus;    ///< 도크의 상태
    std::time_t m_entryTime;     ///< 입차 시간
    std::time_t m_exitTime;      ///< 출차 시간
};

#endif // DOCK_H
