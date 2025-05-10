#ifndef __OS_H
#define __OS_H

#include <iostream>
#include <ctime>
#include <cstdint>
#include "ecu.hpp"

/**
 * @brief   Mô phỏng thời gian RUN của hệ thống
 * @details Cài đặt thời gian chạy của hệ thống tương ứng cho quá trình 
 *          từ khi xe bắt đầu khởi động đến khi xe dừng lại
 * @return  void
 */
void simulation (EngineControlUnit *ECU, uint32_t sample_period, uint32_t simulation_time);

#endif // __OS_H