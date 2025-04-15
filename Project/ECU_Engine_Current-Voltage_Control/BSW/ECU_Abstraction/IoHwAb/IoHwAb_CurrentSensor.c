#include <stdio.h>
#include "IoHwAb_CurrentSensor.h"
#include "IoHwAb_VoltageSensor.h"
#include "Adc.h"    // Gọi API từ MCAL để đọc giá trị từ ADC

/**
 * @brief   Giả lập cấu hình của cảm biến dòng điện 
 * @details Khai báo đối tượng cho cấu hình cảm biến dòng điện
 */
static CurrentSensor_ConfigType CurrentSensor_CurrentConfig;

/**
 * @brief   Hàm khởi tạo cảm biến dòng điện
 * @details Khởi tạo cảm biến dòng điện và cấu hình kênh ADC và giá trị lớn nhất cho cảm biến dòng điện
 * @param   ConfigPtr
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi khi gửi lệnh xuống bộ điều khiển
 */
Std_ReturnType IoHwAb_CurrentSensor_Init(const CurrentSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_CurrentSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến dòng điện vào biến toàn cục
    CurrentSensor_CurrentConfig.CurrentSensor_Channel = ConfigPtr->CurrentSensor_Channel;
    CurrentSensor_CurrentConfig.CurrentSensor_MaxValue = ConfigPtr->CurrentSensor_MaxValue;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Adc_Channel = ConfigPtr->CurrentSensor_Channel;
    Adc_Init(&adcConfig);

    // In ra thông tin cấu hình cảm biến dòng điện
    printf("Current Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", CurrentSensor_CurrentConfig.CurrentSensor_Channel);
    printf(" - Max Load Value: %d kg\n", CurrentSensor_CurrentConfig.CurrentSensor_MaxValue);
    return E_OK;
}

/**
 * @brief   Hàm đọc giá trị từ cảm biến dòng điện
 * @details đọc giá trị cảm biến dòng điện từ kênh ADC và tính toán chuyển đổi giá trị ADC sang dòng điện
 * @param   CurrentValue
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi khi gửi lệnh xuống bộ điều khiển
 */
Std_ReturnType IoHwAb_CurrentSensor_Read(float* CurrentValue) {
    if (CurrentValue == NULL) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị ADC từ MCAL
    uint16_t adcValue = 0;
    if (Adc_ReadChannel(CurrentSensor_CurrentConfig.CurrentSensor_Channel, &adcValue) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Tính toán dòng điện từ điện áp đọc được
    *CurrentValue = (Voltage_ADC_Value - VOLTAGE_HALL_OFFSET) / HALL_SENSITIVITY;   // (Vout - Voffset) / K

    // In ra giá trị dòng điện
    printf("Current Sensor (ADC Channel %d): Current = %.2f (A)\n",
        CurrentSensor_CurrentConfig.CurrentSensor_Channel, *CurrentValue);

    return E_OK;
}

/**
 * @brief   Hàm điều chỉnh dòng điện bộ điều khiển
 * @details ghi giá trị dòng điện yêu cầu từ SWC -> RTE đến bộ điêu khiển dòng điện ở BSW 
 * @param   CurrentValue
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi khi gửi lệnh xuống bộ điều khiển
 */
Std_ReturnType IoHwAb_CurrentControl_SetCurrent(float CurrentValue) {
    // Kiểm tra giá trị mô-men xoắn hợp lệ
    if (CurrentValue < 0.0f || CurrentValue > CurrentSensor_CurrentConfig.CurrentSensor_MaxValue) {
        printf("Error: Current value %.2f (A) out of range (Max: %d (A)).\n", CurrentValue, CurrentSensor_CurrentConfig.CurrentSensor_MaxValue);
        return E_NOT_OK;
    }

    // // Tính toán tỷ lệ nhiệm vụ (duty cycle) dựa trên mô-men xoắn
    // uint16_t dutyCycle = (uint16_t)((CurrentValue / CurrentSensor_CurrentConfig.CurrentSensor_MaxValue) * 100);

    // // Gọi API từ MCAL để cài đặt duty cycle của PWM
    // Pwm_SetDutyCycle(CurrentSensor_CurrentConfig.CurrentSensor_Channel, dutyCycle);

    // // In ra giá trị mô-men xoắn đã đặt
    // printf("Setting Motor Torque to %.2f Nm on Channel %d\n", CurrentValue, CurrentSensor_CurrentConfig.CurrentSensor_Channel);

    return E_OK;
}
