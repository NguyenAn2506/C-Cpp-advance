#ifndef IOHWAB_CURRENTSENSOR_H
#define IOHWAB_CURRENTSENSOR_H

#include "Std_Types.h"

/**
 * @brief   giả lập cấu hình cho cảm biến Hall (cảm biến dòng điện)
 * @details khai báo các giá trị cần thiết cho cảm biến Hall
 */
#define HALL_SENSITIVITY        0.185f  // hệ số K: Độ nhạy cảm biến Hall (185mV/A), tùy vào cảm biến
#define VOLTAGE_HALL_OFFSET     2.5f    // Điện áp offset (thường là 2.5V)

/**
 * @brief   Giả lập cấu hình của cảm biến dòng điện 
 * @details Khai báo đối tượng cho cấu hình cảm biến dòng điện
 */
typedef struct {
    uint8_t CurrentSensor_Channel;   // Kênh ADC để đọc giá trị từ cảm biến
    uint16_t CurrentSensor_MaxValue; // Giá trị dòng điện tối đa mà cảm biến có thể đọc
} CurrentSensor_ConfigType;

/**
 * @brief   Khởi tạo cảm biến dòng điện
 * @details Khởi tạo cảm biến điện áp và cấu hình kênh ADC và giá trị lớn nhất cho cảm biến điện áp
 * @param   ConfigPtr
 * @return  Std_ReturnType
 */
Std_ReturnType IoHwAb_CurrentSensor_Init(const CurrentSensor_ConfigType* ConfigPtr);

/**
 * @brief   Hàm đọc giá trị từ cảm biến dòng điện
 * @details đọc giá trị cảm biến dòng điện từ kênh ADC và tình toán chuyển đổi giá trị ADC sang dòng điện
 * @param   CurrentValue
 * @return  Std_ReturnType
 */
Std_ReturnType IoHwAb_CurrentSensor_Read(float* CurrentValue);

/**
 * @brief   Hàm điều chỉnh dòng điện bộ điều khiển
 * @details ghi giá trị dòng điện yêu cầu từ SWC -> RTE đến bộ điêu khiển dòng điện ở BSW 
 * @param   CurrentValue
 * @return  Std_ReturnType
 */
Std_ReturnType IoHwAb_CurrentControl_SetCurrent(float CurrentValue);

#endif /* IOHWAB_CURRENTSENSOR_H */
