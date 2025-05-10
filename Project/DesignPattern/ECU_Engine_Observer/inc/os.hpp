#ifndef __OS_H
#define __OS_H

#include <iostream>
#include <ctime>
#include <cstdint>
#include "ecu.hpp"

/** 
 * @brief       Tạm dừng chương trình theo đơn vị mili-giây bằng clock()
 * @details     Sử dụng hàm clock() để tạo độ trễ bằng cách đo thời gian thực thi của CPU. 
 *              Thời gian trễ được tính theo số tick kể từ thời điểm bắt đầu, quy đổi từ mili-giây 
 *              sang số tick tương ứng dựa vào hằng số CLOCKS_PER_SEC (1000).
 * @param[in]   ms  Thời gian trễ tính bằng mili-giây
 * @return      void
 * @note        Độ chính xác phụ thuộc vào độ phân giải của hàm clock() và hệ thống. 
 *              Không nên dùng cho delay chính xác cao trong hệ thống thời gian thực.
 */
void delay_ms(size_t ms);

/**
 * @brief   Mô phỏng thời gian RUN của hệ thống
 * @details Cài đặt thời gian chạy của hệ thống tương ứng cho quá trình 
 *          từ khi xe bắt đầu khởi động đến khi xe dừng lại
 * @return  void
 */
void simulateEngine (EngineManager &Engine, uint32_t sample_period, uint32_t simulation_time);

#endif // __OS_H