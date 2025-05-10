#ifndef __ECU_HPP
#define __ECU_HPP

#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <fstream>      // working with file
#include <vector>
#include <ctime>        // working with time
#include <iomanip>      // working with real numbers
#include "../inc/record.hpp"
// #include "../inc/os.hpp"

using namespace std;

#define PATH "../ECU_Engine_Singleton/database/ECU_data.csv"

#define MAX_RPM 6000        // sô vòng quay tối đa
#define MAX_TEMP 120        // nhiệt độ cao nhất
#define WARNING_TEMP 100    // nhiệt độ cảnh báo
#define OPTIMAL_TEMP 80     // nhiệt độ lý tưởng
#define MAX_PEDAL 100       // mức bàn đạp tối đa
#define BASE_FUEL 10        // mức nhiên liệu cơ bản

/**
 * @enum brake_status
 * @brief Trạng thái của hệ thống phanh.
 * 
 * Enum này định nghĩa các trạng thái khác nhau của bàn đạp phanh trong xe:
 * - Nhả phanh
 * - Nhấn phanh
 * - Giới hạn trạng thái (sử dụng để kiểm tra biên/tránh lỗi logic)
 */
typedef enum {
    release,             /**< Nhả phanh - không tác động lực lên phanh */
    press,               /**< Nhấn phanh - đang tác động lực phanh */
    limit_brake_status   /**< Giá trị giới hạn để kiểm tra tính hợp lệ */
} brake_status;

/**
 * @class   EngineControlUnit
 * @brief   Các phương thức điều khiển hệ thông của xe bao gồm
 * - nhiệt độ
 * - tốc độ
 * - nhiên liệu
 * - phanh và bàn đạp ga
 * - chẩn đoán giá trị
 * - lưu dữ liệu vào database
 */
class EngineControlUnit
{
    private:
        static EngineControlUnit* instance;

        int rpm;                    // tốc độ -> só vòng quay
        float temperature;          // nhiệt độ
        float fuel_rate;            // mức nhiên liệu cung cấp
        float throttle_input;       // phản hồi bàn đạp ga
        float brake_input;          // phản hồi bàn đạp phanh
        brake_status isbrake;       // trạng thái phanh

        vector<int> rpm_history;    // biến lưu trữ tốc độ
        vector<float> temp_history; // biến lưu trữ nhiệt độ

        // Private constructor ngăn chặn việc khởi tạo bên ngoài
        EngineControlUnit();        // dùng để khởi tạo đối tượng duy nhất và các thông số mặc định ban đầu

/**
 * @note Các hàm sau đây được gọi bới GenerateRandomData ở public để cài đặt các thuộc tính tương ứng 
 */
        /**
         * @brief       Hàm thiết lập tốc độ động cơ (RPM)
         * @details     Hàm kiểm tra và thiết lập tốc độ vòng quay của động cơ. 
         *              Giá trị hợp lệ nằm trong khoảng từ 0 đến 6000 RPM. 
         *              Nếu hợp lệ, giá trị sẽ được lưu vào biến `rpm` và thêm vào vector `rpm_history`.
         *              Nếu không hợp lệ, sẽ in ra cảnh báo.
         * @param[in]   speed    Giá trị tốc độ vòng quay cần thiết lập (truyền theo tham chiếu hằng).
         * @return      void
         */
        void setEngineSpeed(const int& speed);

        /**
         * @brief       Hàm thiết lập nhiệt độ động cơ (Celsius)
         * @details     Hàm kiểm tra và thiết lập nhiệt độ động cơ, chỉ chấp nhận giá trị 
         *              nằm trong khoảng từ -20.0 đến 120.0 độ C để mô phỏng phạm vi nhiệt độ thực tế. 
         *              Nếu hợp lệ, giá trị được gán cho biến `temperature` và lưu vào vector `temp_history`.
         *              Nếu không hợp lệ, sẽ in ra cảnh báo.
         * @param[in]   temp    Giá trị nhiệt độ cần thiết lập (float, truyền theo tham chiếu hằng).
         * @return      void
         */
        void setEngineTemperature(const float& temp);

        /**
         * @brief       Thiết lập trạng thái phanh (brake) của xe.
         * @details     Hàm này dùng để cập nhật trạng thái phanh hiện tại, ví dụ như đang phanh hay không.
         *              Trạng thái này có thể là một enum hoặc kiểu dữ liệu định nghĩa người dùng (user-defined type).
         * @param[in]   _isbrake    Trạng thái phanh cần được cập nhật.
         * @return      void
         */
        void setBrakeStatus(const brake_status& _isbrake) { isbrake = _isbrake; }

        /**
         * @brief       Thiết lập vị trí bàn đạp ga (throttle).
         * @details     Vị trí ga là một giá trị phần trăm từ 0.0 đến 100.0 thể hiện mức độ người lái đạp ga.
         *              Dữ liệu này thường đến từ cảm biến bàn đạp ga.
         * @param[in]   position    Giá trị vị trí bàn đạp ga (đơn vị: phần trăm).
         * @return      void
         */
        void setThrottlePosition(const float& position) { throttle_input = position; }

        /**
         * @brief       Thiết lập vị trí bàn đạp phanh (brake).
         * @details     Vị trí phanh là một giá trị phần trăm từ 0.0 đến 100.0 thể hiện lực phanh tác dụng lên hệ thống.
         *              Dữ liệu này thường đến từ cảm biến bàn đạp phanh.
         * @param[in]   position    Giá trị vị trí bàn đạp phanh (đơn vị: phần trăm).
         * @return      void
         */
        void setBrakePosition(const float& position) { brake_input = position; }


/**
 * @note    Các hàm dưới đây được sử dụng để truy xuất thông tin cảm biến: tốc độ, mức nhiên liệu và trạng thái phanh.
 */
        /**
         * @brief       Hàm hiển thị giá trị tốc độ hiện tại động cơ (RPM)
         * @return      int
         */
        int getEngineSpeed () const { return rpm; }

        /**
         * @brief       Hàm hiển thị giá trị nhiệt độ hiện tại động cơ (Celsius)
         * @return      int
         */
        int getEngineTemperature () const { return temperature; }


        /**
         * @brief       Hàm hiển thị mức nhiên liệu của xe
         * @return      float
         */
        float getFuelRate() const { return fuel_rate; }

        /**
         * @brief       Hàm hiển thị về trạng thái phanh
         * @return      brake_status
         */
        brake_status getBrakeStatus() const { return isbrake; }

/**
 * @note    Các hàm sau đây được gọi bởi CalculateFuelRate ở public
 */
        /**
         * @brief       Thiết lập mức tiêu thụ nhiên liệu của xe.
         * @details     Gán giá trị tiêu thụ nhiên liệu đầu vào cho biến nội tại của ECU.
         * @param[in]   rate    Giá trị mức tiêu thụ nhiên liệu (đơn vị: lít/giờ hoặc lít/100km tùy hệ thống).
         * @return      void
         */
        void setFuelRate(const float& rate) { fuel_rate = rate; }

        /**
         * @brief       Điều chỉnh hệ số hiệu chỉnh cho RPM và nhiệt độ.
         * @details     Hàm này cho phép cập nhật hai hệ số hiệu chỉnh được sử dụng trong các thuật toán tính toán RPM và nhiệt độ.
         *              Có thể dùng để tuning hệ thống trong quá trình mô phỏng hoặc kiểm tra.
         * @param[in,out]   k_rpm      Tham chiếu đến hệ số hiệu chỉnh RPM, sẽ được cập nhật trong hàm.
         * @param[in,out]   k_temp     Tham chiếu đến hệ số hiệu chỉnh nhiệt độ, sẽ được cập nhật trong hàm.
         * @return          void
         */
        void AdjustFactor(float& k_rpm, float& k_temp);

/**
 * @note    Hàm sau đây được gọi bởi setFuelInjectionRate ở public
 */
        /**
         * @brief   Tính toán mức nhiên liệu hiệu chỉnh
         * @details Hàm này giúp tính toán và hiệu chỉnh mức nhiên liệu
         */
        void CalculateFuelRate();

        /**
         * @brief  Giới hạn nhiên liệu qua thông số của phanh 
         */
        void LimitFuelByBrake(const brake_status& isbrake);

/**
 * @note    Hàm sau đây được gọi bởi ECU_Read ở public
 */
        /**
         * @brief       Hàm kiểm tra động cơ quá nhiệt
         * @details     Kiểm tra quá nhiệt của động cơ và cảnh báo      
         * @return      bool
         */
        bool IsOverHeating();   

        /**
         * @brief   Hàm tạo ngẫu nhiên các giá trị mô phỏng đọc dữ liệu cảm biến
         * @return  void
         */
        void GenerateRandomData();

    public:

        /**
         * @brief       Trả về con trỏ đến thể hiện duy nhất của lớp EngineControlUnit
         * @details     Đây là phương thức khởi tạo "lười" (lazy initialization). Nếu đối tượng chưa tồn tại, nó sẽ được cấp phát
         *              bộ nhớ động và khởi tạo. Nếu đã tồn tại, sẽ trả về con trỏ hiện có.
         *              Giúp đảm bảo rằng chỉ có một thể hiện duy nhất của ECU được sử dụng trong toàn chương trình.
         * @return      Con trỏ đến thể hiện duy nhất của EngineControlUnit
         */
        // static EngineControlUnit *getInstance()
        static EngineControlUnit *ECU_Init()
        {
            if(!instance)
            {
                instance = new EngineControlUnit();
                // bổ sung thêm tính năng nếu cần
            }
            return instance;
        }

        /**
         * @brief       Giải phóng bộ nhớ đã cấp phát cho đối tượng EngineControlUnit
         * @details     Phương thức này nên được gọi ở cuối chương trình để tránh rò rỉ bộ nhớ.
         *              Sau khi giải phóng, con trỏ instance được gán lại nullptr để đảm bảo an toàn.
         * @return      void
         */
        // static void freeInstance()
        static void freeECU()
        {
            if (instance != nullptr)
            {
                delete instance;
                instance = nullptr;
            }
        }

        /**
         * @brief       Hàm đọc các giá trị của tốc độ và nhiệt độ của động cơ       
         * @return      void
         */
        void ECU_Read();

        /**
         * @brief       Hàm lưu trữ tốc độ và nhiệt độ của động cơ vào file csv   
         * @return      void
         */
        void ECU_SaveData();

        /**
         * @brief       Hàm in ra chuẩn đoán các giá trị đã lưu trong file csv của các lần chạy      
         * @return      void
         */
        void ECU_Diagnostics();

        /**
         * @brief   Hàm cài đặt mức nhiên liệu dựa trên mức độ đạp ga và tỉ lệ hòa khí
         * @return  void
         */
        void setFuelInjectionRate();

        /**
         * @brief   Hàm để tương tác với hệ thống phanh dựa vào mức độ đạp phanh 
         *          và điều chỉnh lại mức nhiên liệu thực tế cung cấp cho xe
         * @return  void
         */
        void BrakeControlInteraction();
};

#endif // __ECU_HPP