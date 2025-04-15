#include "Rte_CurrentVoltageControl.h"   // Bao gồm interface của RTE cho Current and Voltage Control
#include "Rte_TorqueControl.h"  // Bao gồm interface của RTE cho Torque Control
#include "Current_and_Voltage_Control.h"
#include "Torque_Control.h"
#include <stdio.h>  // Thư viện cho printf
#include <stdlib.h>

/**
 * @brief   Hàm khởi tạo hệ thống điều khiển dòng điện và điện áp
 * @param   void
 * @return  void
 */
void CurrentVoltageControl_Init(void)
{
    // Khởi tạo các cảm biến dòng điện, điện áp
    Std_ReturnType status;

    printf("Khởi tạo hệ thống Current and Voltage Control....\n");

    // khởi tạo cảm biến dòng điện
    status = Rte_Call_RpCurrentSensor_Init();
    if(status == E_OK)
    {
        printf("Cảm biến dòng điện đã khởi tạo thành công.\n");
    }
    else
    {
        printf("Lỗi khi khởi tạo cảm biến dòng điện.\n");
        return;
    }

    // khởi tạo cảm biến điện áp
    status = Rte_Call_RpVoltageSensor_Init();
    if(status == E_OK)
    {
        printf("Cảm biến điện áp đã khởi tạo thành công.\n");
    }
    else
    {
        printf("Lỗi khi khởi tạo cảm biến điện áp.\n");
        return;
    }
    printf("Hệ thống điều khiển dòng điện điện áp đã khởi tạo thành công\n");
}    

/**
 * @brief   Hàm cảnh báo quá tải hoặc vượt ngưỡng nguy hiểm
 * @param   current: giá trị dòng hiện tại
 * @param   voltage: giá trị điện áp hiện tại
 * @return  WarningStatus_t
 */
WarningStatus_t CheckWarningSystem(float current, float voltage)
{
    if(current >= CURRENT_CRITICAL || voltage >= VOLTAGE_CRITICAL)
    {
        printf("Hệ thống vượt ngưỡng nguy hiểm\n");
        printf("SHUT DOWN !!!!!!!!\n");
        return WARNING_CRITICAL;
    }
    else if(current >= CURRENT_OVERLOAD || voltage >= VOLTAGE_OVERLOAD)
    {
        printf("Hệ thống quá tải - cảnh báo!\n");
        return WARNING_OVERLOAD;
    }
    return WARNING_NONE;
}

/**
 * @brief   Hàm đọc giá trị cảm biến dòng điện và điện áp
 * @param   current_actual     Con trỏ tới biến lưu giá trị dòng điện thực tế
 * @param   voltage_actual     Con trỏ tới biến lưu giá trị điện áp thực tế
 * @return  Std_ReturnType
 */
Std_ReturnType Read_CurrentVoltageSensor(float* current_actual, float* voltage_actual)
{
    Std_ReturnType status = E_OK;

    // Kiểm tra con trỏ NULL
    if (current_actual == NULL || voltage_actual == NULL) {
        printf("Lỗi: con trỏ NULL được truyền vào hàm đọc giá trị cảm biến!\n");
        return E_NOT_OK;
    }

    // đọc dữ liệu từ cảm biến dòng điện 
    if(Rte_Read_CurrentSensor(current_actual) == E_OK)
    {
        printf("Giá trị dòng điện thực tế\n", *current_actual);
    }
    else{
        printf("Lỗi khi đọc cảm biến dòng điện!\n");
        status = E_NOT_OK;
    }
    
    // đọc dữ liệu từ cảm biến điện áp
    if(Rte_Read_VoltageSensor(voltage_actual) == E_OK)
    {
        printf("Giá trị điện áp thực tế\n", *voltage_actual);
    }
    else{
        printf("Lỗi khi đọc cảm biến điện áp!\n");
        status = E_NOT_OK;
    }
    return status;
} 
/**
 * @brief   Hàm cập nhật giá trị dòng điện và điện áp 
 * @param   void
 * @return  void
 */
void CurrentVoltageControl_Update(void)
{
    float desired_current = 0;
    float desired_voltage = 0;

    float current_actual = 0;
    float voltage_actual = 0;

    if(Read_CurrentVoltageSensor(&current_actual, &voltage_actual) == E_OK)
    {
        WarningStatus_t status = CheckWarningSystem(current_actual, voltage_actual);
        if(status == WARNING_CRITICAL)      // ngưỡng nguy hiểm
        {
            desired_current = 0;        
            desired_voltage = 0;
        }
        else if(status == WARNING_OVERLOAD)     // ngưỡng cảnh báo
        {
            desired_current = current_actual * 0.95;    // MAX= 3.0 * 0.95 = 2.85
            desired_voltage = voltage_actual  * 0.95;    // MAX= 14.2 * 0.95 = 13.49
        }
        else
        {
            float throttle_simu = (rand() % 61 + 40); // từ 40 đến 100
            float throttle =  throttle_simu / 100.0f;
            // tính toan dòng điện và điện áp yêu cầu (nội suy tuyến tính)
            desired_current = MIN_CURRENT + (MAX_CURRENT - MIN_CURRENT) * throttle;
            desired_voltage = MIN_VOLTAGE + (MAX_VOLTAGE - MIN_VOLTAGE) * throttle;

            // giới hạn dòng điện trong phạm vi an toàn
            if(desired_current > MAX_CURRENT)
            {
                desired_current = MAX_CURRENT;
            }
            else if(desired_current < MIN_CURRENT)
            {
                desired_current = MIN_CURRENT;
            }
            // giới hạn điện áp trong phạm vi an toàn
            if(desired_voltage > MAX_VOLTAGE)
            {
                desired_voltage = MAX_VOLTAGE;
            }
            else if(desired_voltage < MIN_VOLTAGE)
            {
                desired_voltage = MIN_VOLTAGE;
            }
        }

        // in ra dòng điện và điện áp yêu cầu
        printf("Dòng điện yêu cầu: %f (A)\n", desired_current);
        printf("Điện áp yêu cầu: %f (V)\n", desired_voltage);

        // Ghi mô-men xoắn yêu cầu tới bộ điều khiển động cơ  (gửi dữ liệu xuống)
        if (Rte_Write_PpCurrentControl_SetCurrent(desired_current) == E_OK) {
            printf("Đã gửi dòng điện yêu cầu tới bộ điều khiển dòng điện.\n");
        } else {
            printf("Lỗi khi gửi dòng điện tới bộ điều khiển dòng điện!\n");
        }

        // Ghi mô-men xoắn yêu cầu tới bộ điều khiển động cơ  (gửi dữ liệu xuống)
        if (Rte_Write_PpVoltageControl_SetVoltage(desired_voltage) == E_OK) {
            printf("Đã gửi điện áp yêu cầu tới bộ điều khiển điện áp.\n");
        } else {
            printf("Lỗi khi gửi điện áp tới bộ điều khiển điện áp!\n");
        }
    }
}

/**
 * @brief   hàm kiểm tra có tải
 * @param   void
 * @return  uint8_t
 */
uint8_t CheckLoadStatus(void);

