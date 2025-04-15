#include <stdio.h>
#include "IoHwAb_VoltageSensor.h"
#include "Adc.h"    // Gọi API từ MCAL để đọc giá trị từ ADC

/**
 * @brief   Giả lập giá trị của cảm biến điện áp 
 * @details khai báo biến extern để đưa giá trị sang thư viện dòng điện
 */
uint16_t Voltage_ADC_Value = 0;

/**
 * @brief   Giả lập cấu hình của cảm biến điện áp 
 * @details Khai báo đối tượng cho cấu hình cảm biến điện áp 
 */
static VoltageSensor_ConfigType VoltageSensor_VoltageConfig;

/**
 * @brief   Hàm khởi tạo cảm biến điện áp
 * @details Khởi tạo cảm biến điện áp và cấu hình kênh ADC và giá trị lớn nhất cho cảm biến điện áp
 * @param   ConfigPtr
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi khi gửi lệnh xuống bộ điều khiển
 */
Std_ReturnType IoHwAb_VoltageSensor_Init(const VoltageSensor_ConfigType* ConfigPtr) {
    if (ConfigPtr == NULL) {
        printf("Error: Null configuration pointer passed to IoHwAb_VoltageSensor_Init.\n");
        return E_NOT_OK;
    }

    // Lưu cấu hình cảm biến điện áp vào biến toàn cục
    VoltageSensor_VoltageConfig.VoltageSensor_Channel = ConfigPtr->VoltageSensor_Channel;
    VoltageSensor_VoltageConfig.VoltageSensor_MaxValue = ConfigPtr->VoltageSensor_MaxValue;

    // Gọi API từ MCAL để khởi tạo ADC
    Adc_ConfigType adcConfig;
    adcConfig.Adc_Channel = ConfigPtr->VoltageSensor_Channel;
    Adc_Init(&adcConfig);

    // In ra thông tin cấu hình cảm biến điện áp
    printf("Voltage Sensor Initialized with Configuration:\n");
    printf(" - ADC Channel: %d\n", VoltageSensor_VoltageConfig.VoltageSensor_Channel);
    printf(" - Max Load Value: %d kg\n", VoltageSensor_VoltageConfig.VoltageSensor_MaxValue);
    return E_OK;
}

/**
 * @brief   Hàm đọc giá trị từ cảm biến điện áp
 * @details đọc giá trị cảm biến điện áp từ kênh ADC và tình toán chuyển đổi giá trị ADC sang điện áp
 * @param   VoltageValue
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi khi gửi lệnh xuống bộ điều khiển
 */
Std_ReturnType IoHwAb_VoltageSensor_Read(float* VoltageValue) {
    if (VoltageValue == NULL) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Đọc giá trị ADC từ MCAL
    uint16_t adcValue = 0;
    if (Adc_ReadChannel(VoltageSensor_VoltageConfig.VoltageSensor_Channel, &adcValue) != E_OK) {
        printf("Error: Failed to read ADC value.\n");
        return E_NOT_OK;
    }

    // Chuyển đổi giá trị ADC sang giá trị điện áp (Vol)
    *VoltageValue = ((float)adcValue * 3.3) / 4095.0f;

    // In ra giá trị điện áp
    printf("Voltage Sensor (ADC Channel %d): Voltage = %.2f (V)\n",
        VoltageSensor_VoltageConfig.VoltageSensor_Channel, *VoltageValue);
    
    //  gán giá trị cho biến extern để đưa sang thư viện khác
    Voltage_ADC_Value = (uint16_t)*VoltageValue;

    return E_OK;
}

/**
 * @brief   Hàm điều chỉnh điện áp bộ điều khiển
 * @details ghi giá trị điện áp yêu cầu từ SWC -> RTE đến bộ điêu khiển điện áp ở BSW 
 * @param   VoltageValue
 * @return  Std_ReturnType
 *          E_OK:   Thành công
 *          E_NOT_OK: lỗi khi khi gửi lệnh xuống bộ điều khiển
 */
Std_ReturnType IoHwAb_VoltageControl_SetVoltage(float VoltageValue) {
    // Kiểm tra giá trị điện áp hợp lệ
    if (VoltageValue < 0.0f || VoltageValue > VoltageSensor_VoltageConfig.VoltageSensor_MaxValue) {
        printf("Error: Voltage value %.2f (V) out of range (Max: %d (V)).\n", VoltageValue, VoltageSensor_VoltageConfig.VoltageSensor_MaxValue);
        return E_NOT_OK;
    }

    // // Tính toán tỷ lệ nhiệm vụ (duty cycle) dựa trên điện áp
    // uint16_t dutyCycle = (uint16_t)((VoltageValue / VoltageSensor_VoltageConfig.VoltageSensor_MaxValue) * 100);

    // // Gọi API từ MCAL để cài đặt duty cycle của PWM
    // Pwm_SetDutyCycle(VoltageSensor_VoltageConfig.VoltageSensor_Channel, dutyCycle);

    // // In ra giá trị điện áp đã đặt
    // printf("Setting Motor Torque to %.2f Nm on Channel %d\n", VoltageValue, VoltageSensor_VoltageConfig.VoltageSensor_Channel);

    return E_OK;
}

