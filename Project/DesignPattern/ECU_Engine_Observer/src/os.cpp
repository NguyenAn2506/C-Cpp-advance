#include "../inc/os.hpp"
#include <chrono>
#include <thread>

/** Cách 1
 * @brief       Tạm dừng chương trình theo đơn vị mili-giây bằng clock()
 * @details     Sử dụng hàm clock() để tạo độ trễ bằng cách đo thời gian thực thi của CPU. 
 *              Thời gian trễ được tính theo số tick kể từ thời điểm bắt đầu, quy đổi từ mili-giây 
 *              sang số tick tương ứng dựa vào hằng số CLOCKS_PER_SEC (1000).
 * @param[in]   ms  Thời gian trễ tính bằng mili-giây
 * @return      void
 * @note        Độ chính xác phụ thuộc vào độ phân giải của hàm clock() và hệ thống. 
 *              Không nên dùng cho delay chính xác cao trong hệ thống thời gian thực.
 */
static void delay_ms(uint32_t ms) {
    clock_t start_time = clock();

    // Tính số tick tương ứng với ms
    clock_t wait_ticks = (ms * CLOCKS_PER_SEC) / 1000;

    while (clock() - start_time < wait_ticks);
}

// /** Cách 2
//  * @brief       Tạm dừng chương trình trong một khoảng thời gian (milliseconds).
//  * @param[in]   ms  Thời gian trễ tính bằng mili-giây.
//  * @return      void
//  * @bug         this_thread 
//  *              name followed by '::' must be a class or namespace name
//  */
// void delay_ms(int ms)
// {
//     std::this_thread::sleep_for(std::chrono::milliseconds(ms));
// }


/**
 * @brief   mô phỏng chương trình
 * @details hàm này set thời gian để hệ thống hoạt động
 * @return  void
 */
void simulateEngine (EngineManager &Engine, uint32_t sample_period, uint32_t simulation_time)
{
    cout<<" Car has started " << endl;
    while(simulation_time-- > 0)
    {
        cout << "=================" <<endl;
        Engine.setEngineState();
        // Engine.getState();
        cout<<"================="<<endl;
        delay_ms(sample_period);
    }
    cout<<" Car has stopped " << endl;
}

