#include "Rte_TorqueControl.h"
// #include "IoHwAb_ThrottleSensor.h"  // API IoHwAb để đọc cảm biến bàn đạp ga
// #include "IoHwAb_SpeedSensor.h"     // API IoHwAb để đọc cảm biến tốc độ
// #include "IoHwAb_LoadSensor.h"      // API IoHwAb để đọc cảm biến tải trọng
// #include "IoHwAb_TorqueSensor.h"    // API IoHwAb để đọc mô-men xoắn thực tế
// #include "IoHwAb_MotorDriver.h"     // API IoHwAb để điều khiển mô-men xoắn động cơ
#include "IoHwAb_CurrentSensor.h"
#include "IoHwAb_VoltageSensor.h"
#include "Std_Types.h"


/**
 * @brief   API khởi tạo cảm biến dòng điện 
 * @details cấu hình kênh ADC tương ứng với cảm biến dòng điện và gọi API khởi tạo từ lớp IoHwAb
 * @return  Std_ReturnType
 */
Std_ReturnType Rte_Call_RpCurrentSensor_Init(void) {
    // Cấu hình cho cảm biến dòng điện
    CurrentSensor_ConfigType CurrentSensorConfig = {
        .CurrentSensor_Channel = 1,        // Kênh ADC cho cảm biến tốc độ
        .CurrentSensor_MaxValue = 3.0f     // dòng điện tối đa giả lập (200 km/h)
    };
    // Gọi API từ IoHwAb để khởi tạo cảm biến dòng điện
    return IoHwAb_CurrentSensor_Init(&CurrentSensorConfig);  
}

/**
 * @brief   API khởi tạo cảm biến điện áp 
 * @details cấu hình kênh ADC tương ứng với cảm biến điện áp và gọi API khởi tạo từ lớp IoHwAb
 * @return  Std_ReturnType
 */
Std_ReturnType Rte_Call_RpVoltageSensor_Init(void)
{
    // Cấu hình cho cảm biến điện áp
    VoltageSensor_ConfigType VoltageSensorConfig = {
        .VoltageSensor_Channel = 1,        // Kênh ADC cho cảm biến điện áp
        .VoltageSensor_MaxValue = 14.2f    // điện áp tối đa giả lập (200 km/h)
    };
    // Gọi API từ IoHwAb để khởi tạo cảm biến điện áp 
    return IoHwAb_VoltageSensor_Init(&VoltageSensorConfig);  
}

/**
 * @brief   API để đọc dữ liệu từ cảm biến đòng điện
 * @details Gọi API từ IoHwAb để đọc giá trị từ cảm biến dòng điện
 * @param[out]  CurrentValue    con trỏ đến biến lưu giá trị dòng điện
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi con trỏ NULL hoặc không đọc được giá trị
 */
Std_ReturnType Rte_Read_CurrentSensor(float* CurrentValue)
{
    if(CurrentValue == NULL)
    {
        return E_NOT_OK;
    }
    // gọi API từ IoHwAb để đọc giá trị từ cảm biến dòng điện
    return IoHwAb_CurrentSensor_Read(CurrentValue);
}

/**
 * @brief   API để đọc dữ liệu từ cảm biến điện áp
 * @details Gọi API từ IoHwAb để đọc giá trị từ cảm biến điện áp
 * @param[out]  VoltageValue    con trỏ đến biến lưu giá trị điện áp
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi con trỏ NULL hoặc không đọc được giá trị
 */
Std_ReturnType Rte_Read_VoltageSensor(float* VoltageValue)
{
    if(VoltageValue == NULL)
    {
        return E_NOT_OK;
    }
    // gọi API từ IoHwAb để đọc giá trị từ cảm biến dòng điện
    return IoHwAb_VoltageSensor_Read(VoltageValue);
}

/**
 * @brief   API để ghi dữ liệu dòng điện yêu cầu tới bộ điều khiển dòng điện
 * @details Gọi API từ IoHwAb để đặt giá trị dòng điện yêu cầu xuống bộ điều khiển dòng điện
 * @param[in]  CurrentValue    con trỏ đòng điện cần đặt
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi khi gửi lệnh xuống bộ điều khiển
 */
Std_ReturnType Rte_Write_PpCurrentControl_SetCurrent(float CurrentValue) {
    return IoHwAb_CurrentControl_SetCurrent(CurrentValue);  // Gọi API từ IoHwAb để ghi điện áp yêu cầu tới bộ điều khiển 
}

/**
 * @brief   API để ghi dữ liệu điện áp yêu cầu tới bộ điều khiển điện áp
 * @details Gọi API từ IoHwAb để đặt giá trị điện áp yêu cầu xuống bộ điều khiển điện áp
 * @param[in]  VoltageValue    con trỏ điện áp cần đặt
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi khi gửi lệnh xuống bộ điều khiển
 */
Std_ReturnType Rte_Write_PpVoltageControl_SetVoltage(float VoltageValue) {
    return IoHwAb_VoltageControl_SetVoltage(VoltageValue);  // Gọi API từ IoHwAb để ghi điện áp yêu cầu tới bộ điều khiển 
}