#ifndef IOHWAB_VOLTAGESENSOR_H
#define IOHWAB_VOLTAGESENSOR_H

#include "Std_Types.h"

/**
 * @brief   Giả lập cấu hình của cảm biến điện áp 
 * @details Khai báo đối tượng cho cấu hình cảm biến điện áp 
 */
typedef struct {
    uint8_t VoltageSensor_Channel;   // Kênh ADC để đọc giá trị từ cảm biến
    uint16_t VoltageSensor_MaxValue; // Giá trị điện áp tối đa mà cảm biến có thể đọc
} VoltageSensor_ConfigType;

/**
 * @brief   Hàm khởi tạo cảm biến điện áp
 * @details Khởi tạo cảm biến điện áp và cấu hình kênh ADC và giá trị lớn nhất cho cảm biến điện áp
 * @param   ConfigPtr
 * @return  Std_ReturnType
 */
Std_ReturnType IoHwAb_VoltageSensor_Init(const VoltageSensor_ConfigType* ConfigPtr);

/**
 * @brief   Giả lập giá trị của cảm biến điện áp
 * @details khai báo biến extern để đưa giá trị sang thư viện dòng điện
 */
extern uint16_t Voltage_ADC_Value;

/**
 * @brief   Hàm đọc giá trị từ cảm biến điện áp
 * @details đọc giá trị cảm biến điện áp từ kênh ADC và tình toán chuyển đổi giá trị ADC sang điện áp
 * @param   VoltageValue
 * @return  Std_ReturnType
 */
Std_ReturnType IoHwAb_VoltageSensor_Read(float* VoltageValue);

/**
 * @brief   Hàm điều chỉnh điện áp bộ điều khiển
 * @details ghi giá trị điện áp yêu cầu từ SWC -> RTE đến bộ điêu khiển điện áp ở BSW 
 * @param   VoltageValue
 * @return  Std_ReturnType
 */
Std_ReturnType IoHwAb_VoltageControl_SetVoltage(float VoltageValue);

#endif /* IOHWAB_VOLTAGESENSOR_H */
