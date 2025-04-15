#ifndef TORQUE_CONTROL_H
#define TORQUE_CONTROL_H

/**
 * Định nghĩa mô-men xoắn tối đa và tối thiểu
 * MAX_TORQUE: Mômen tối đa
 * MIN_TORQUE: Momen tối thiểu
 */
#define MAX_TORQUE 100.0f
#define MIN_TORQUE 0.0f

/***********************************************/
/* Khai báo các hàm chính cho Torque Control */ 
/***********************************************/

/**
 * @brief   Hàm khởi tạo hệ thống điều khiển mô-men xoắn
 * @param   void
 * @return  void
 */
void TorqueControl_Init(void);   

/**
 * @brief   Hàm cập nhật hệ thống điều khiển mô-men xoắn
 * @param   void
 * @return  void
 */
void TorqueControl_Update(void); 

#endif // TORQUE_CONTROL_H
