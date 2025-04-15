#ifndef RTE_CURRENTVOLATGECONTROL_H
#define RTE_CURRENTVOLATGECONTROL_H

#include "Std_Types.h"  // Bao gồm các kiểu dữ liệu tiêu chuẩn
#include <stddef.h>  // Định nghĩa NULL

/**
 * @brief   API khởi tạo cảm biến dòng điện 
 * @details cấu hình kênh ADC tương ứng với cảm biến dòng điện và gọi API khởi tạo từ lớp IoHwAb
 * @return  Std_ReturnType
 */
Std_ReturnType Rte_Call_RpCurrentSensor_Init(void);

/**
 * @brief   API khởi tạo cảm biến điện áp 
 * @details cấu hình kênh ADC tương ứng với cảm biến điện áp và gọi API khởi tạo từ lớp IoHwAb
 * @return  Std_ReturnType
 */
Std_ReturnType Rte_Call_RpVoltageSensor_Init(void);

/**
 * @brief   API để đọc dữ liệu từ cảm biến đòng điện
 * @details Gọi API từ IoHwAb để đọc giá trị từ cảm biến dòng điện
 * @param[out]  CurrentValue    con trỏ đến biến lưu giá trị dòng điện
 * @return  Std_ReturnType
 */
Std_ReturnType Rte_Read_CurrentSensor(float* CurrentValue);

/**
 * @brief   API để đọc dữ liệu từ cảm biến điện áp
 * @details Gọi API từ IoHwAb để đọc giá trị từ cảm biến điện áp
 * @param[out]  VoltageValue    con trỏ đến biến lưu giá trị điện áp
 * @return  Std_ReturnType
 */
Std_ReturnType Rte_Read_VoltageSensor(float* VoltageValue);

/**
 * @brief   API để ghi dữ liệu dòng điện yêu cầu tới bộ điều khiển dòng điện
 * @details Gọi API từ IoHwAb để đặt giá trị dòng điện yêu cầu xuống bộ điều khiển dòng điện
 * @param[in]  CurrentValue    con trỏ đòng điện cần đặt
 * @return  Std_ReturnType
 */
Std_ReturnType Rte_Write_PpCurrentControl_SetCurrent(float CurrentValue);

/**
 * @brief   API để ghi dữ liệu điện áp yêu cầu tới bộ điều khiển điện áp
 * @details Gọi API từ IoHwAb để đặt giá trị điện áp yêu cầu xuống bộ điều khiển điện áp
 * @param[in]  VoltageValue    con trỏ điện áp cần đặt
 * @return  Std_ReturnType
 */
Std_ReturnType Rte_Write_PpVoltageControl_SetVoltage(float VoltageValue);

#endif // RTE_CURRENTVOLATGECONTROL_H
