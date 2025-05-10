/**
 * @file    main.cpp
 * @brief   Chương trình chính triển khai mẫu thiết kế Observer cho hệ thống ô tô.
 * @author  Nta
 */

#include "../inc/ecu.hpp"
#include "../inc/os.hpp"

/**
 * @brief   Hàm main - điểm bắt đầu của chương trình.
 * @param   argc Số lượng tham số truyền vào từ dòng lệnh.
 * @param   argv Mảng các chuỗi tham số từ dòng lệnh.
 * @return  Trả về 0 nếu chương trình kết thúc thành công.
 */
int main(int argc, char const *argv[])
{
    /**
     * @brief   Tạo đối tượng cho ISubject quản lý các hệ thống giám sát.
     */
    EngineManager engine;           

    /**
     * @brief   Tạo các đối tượng quan sát (Observer) trong hệ thống.
     */
    CoolingSystem coolingSystem;     /**< Đối tượng hệ thống làm mát. */
    WarningSystem warningSystem;     /**< Đối tượng hệ thống cảnh báo. */
    EngineControlUnit ECU;           /**< Đối tượng hệ thống điều khiển động cơ (ECU). */
    TransmissionControlUnit transmission; /**< Đối tượng hệ thống điều khiển hộp số. */
    FuelInjectionSystem fuelSystem(&ECU); /**< Đối tượng hệ thống phun nhiên liệu, liên kết với ECU. */

    /**
     * @brief   Đăng ký các đối tượng quan sát với đối tượng EngineManager.
     */
    engine.addObserver(&coolingSystem);
    engine.addObserver(&warningSystem);
    engine.addObserver(&ECU);
    engine.addObserver(&transmission);
    engine.addObserver(&fuelSystem);

    /**
     * @brief   Mô phỏng hoạt động của động cơ trong một khoảng thời gian nhất định.
     * @param   engine          Đối tượng EngineManager để điều khiển động cơ.
     * @param   sample_period   Chu kỳ lấy mẫu (đơn vị: ms).
     * @param   simulation_time Thời gian mô phỏng (số lần lặp).
     */
    simulateEngine(engine, 250, 100);

    return 0;
}
