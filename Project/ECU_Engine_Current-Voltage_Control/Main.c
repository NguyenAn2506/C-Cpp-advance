#include "Os.h"
#include "Torque_Control.h"
// #include "Speed_Control.h"
#include "Current_and_Voltage_Control.h"
#include <stdio.h>

// Task để khởi tạo và cập nhật hệ thống điều khiển mô-men xoắn
void* Task_TorqueControl(void* arg) {
    // Gọi hàm khởi tạo Torque Control
    TorqueControl_Init();

    // Liên tục cập nhật hệ thống điều khiển mô-men xoắn
    while (1) {
        TorqueControl_Update();
        
        // Tạm dừng 1 giây trước khi cập nhật tiếp
        Os_Delay(1000);
    }

    return NULL;
}

// // Task để khởi tạo và cập nhật hệ thống Speed Control
// void* Task_SpeedControl(void* arg) {
//     // Gọi hàm khởi tạo Speed Control
//     SpeedControl_Init();

//     // Liên tục cập nhật hệ thống điều khiển Speed Control
//     while (1) {
//         SpeedControl_Update();
        
//         // Tạm dừng 1 giây trước khi cập nhật tiếp
//         Os_Delay(1000);
//     }

//     return NULL;
// }

// Task để khởi tạo và cập nhật hệ thống điều khiển dòng điện và điện áp
void* Task_Current_Voltage_Control(void* arg) {
    // Gọi hàm khởi tạo Current_Voltage_Control
    CurrentVoltageControl_Init();

    // đọc dữ liệu cảm biến dòng điện và cảm biến điện áp
    float current_actual = 0.0f;
    float voltage_actual = 0.0f;
    Read_CurrentVoltageSensor(&current_actual, &voltage_actual);

    // Liên tục cập nhật hệ thống điều khiển dòng điện và điện áp
    while (1) {
        CurrentVoltageControl_Update();
        
        // Tạm dừng 1 giây trước khi cập nhật tiếp
        Os_Delay(1000);
    }

    return NULL;
}


int main(void) {
    // Khởi tạo hệ điều hành
    Os_Init();

    // Tạo task chung cho Torque Control (khởi tạo + cập nhật)
    Os_CreateTask(Task_TorqueControl, "Torque Control");
    // Os_CreateTask(Task_SpeedControl, "Speed Control");
    Os_CreateTask(Task_Current_Voltage_Control, "Current Voltage Control");

    // Chờ các task hoàn thành
    Os_Shutdown();

    return 0;
}
