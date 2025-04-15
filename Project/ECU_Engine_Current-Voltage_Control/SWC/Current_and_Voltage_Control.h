#ifndef CURRENT_AND_VOLTAGE_CONTROL_H
#define CURRENT_AND_VOLTAGE_CONTROL_H

#include <stdint.h>
#include "Std_Types.h"

/**
 * Định nghĩa giá trị dòng điện quá tải và dòng điện shutdown
 * 
 */
// Ngưỡng dòng điện (cho từng khối thiết bị hoặc hệ thống điều khiển)
#define MIN_CURRENT        0.2f   // A – dưới mức này là lỗi hoặc cảm biến hỏng
#define CURRENT_OVERLOAD   5.0f   // A – bắt đầu cảnh báo quá tải
#define CURRENT_CRITICAL   7.0f   // A – cần shutdown hệ thống
#define MAX_CURRENT        6.0f   // A – dùng để giới hạn setpoint


/**
 * Định nghĩa giá trị điện áp quá tải và điện áp shutdown
 * VOLTAGE_OVERLOAD: điện áp quá tải (>15V)
 * VOLTAGE_CRITICAL: điện áp nguy hiểm gây hỏng hóc
 */
// Ngưỡng điện áp (cho hệ thống 12V thông dụng trên xe con)
#define MIN_VOLTAGE        11.0f   // V – dưới là ắc quy yếu
#define VOLTAGE_OVERLOAD   14.2f   // V – bắt đầu quá tải
#define VOLTAGE_CRITICAL   15.5f   // V – shutdown nếu vượt
#define MAX_VOLTAGE        15.0f   // V – setpoint không bao giờ vượt mức này



/**
 * Định nghĩa kiểu enum các mức cảnh bảo hệ thống
 */
typedef enum {
    WARNING_NONE = 0,
    WARNING_OVERLOAD,
    WARNING_CRITICAL
} WarningStatus_t;

/***********************************************/
/* Khai báo các hàm chính cho Current và Voltage Control */ 
/***********************************************/

/**
 * @brief   Hàm khởi tạo hệ thống điều khiển dòng điện và điện áp
 * @param   void
 * @return  void
 */
void CurrentVoltageControl_Init(void);    

/**
 * @brief   Hàm cảnh báo quá tải hoặc vượt ngưỡng nguy hiểm
 * @param   current: giá trị dòng hiện tại
 * @param   voltage: giá trị điện áp hiện tại
 * @return  WarningStatus_t
 */
WarningStatus_t CheckWarningSystem(float current, float voltage);

/**
 * @brief   Hàm đọc giá trị cảm biến dòng điện và điện áp
 * @param   current_actual     Con trỏ tới biến lưu giá trị dòng điện thực tế
 * @param   voltage_actual     Con trỏ tới biến lưu giá trị điện áp thực tế
 * @return  Std_ReturnType
 */
Std_ReturnType Read_CurrentVoltageSensor(float* current_actual, float* voltage_actual);

/**
 * @brief   Hàm cập nhật giá trị dòng điện và điện áp 
 * @param   void
 * @return  void
 */
void CurrentVoltageControl_Update(void); 

/**
 * @brief   hàm kiểm tra có tải
 * @param   void
 * @return  uint8_t
 */
uint8_t CheckLoadStatus(void);

#endif // CURRENT_AND_VOLTAGE_CONTROL_H
