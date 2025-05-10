#ifndef __ECU_HPP
#define __ECU_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <map>

using namespace std;

/**
 * @class   IObserver
 * @brief   Interface for Observers
 * @details Giao diện cho chủ thể (Subject) - Động cơ 
 *          Các hệ thống như CoolingSystem, WarningSystem, và EngineControlUnit
 *          sẽ đăng ký để nhận thông báo khi trạng thái của động cơ thay đổi.
 */
class IObserver
{
    public:
        /**
         * @brief   Phương thức cập nhật khi có sự thay đổi từ Subject.
         * @details Phương thức được gọi bởi Engine khi có sự thay đổi về tốc độ hoặc nhiệt độ.
         * @param   speed Tốc độ động cơ .
         * @param   temperature Nhiệt độ động cơ .
         * @param   throttle_position throttle_position Vị trí chân ga.
         * @note    Phương thức thuần ảo (virtual). Lớp con kế thừa triển khai phương thức này.
         * @return  void
         */
        virtual void update(const int & speed, const float & temperature, const float &throttle_position) = 0;
        
        /**
         * @brief Destructor cho lớp IObserver.
         * @note Destructor ảo để đảm bảo hủy đúng cách các đối tượng dẫn xuất.
         */
        virtual ~IObserver() {}     // Destructor
}; 

/**
 * @class   ISubject
 * @brief   Interface for Subject in the Observer Pattern
 * @details Lớp này đóng vai trò là chủ thể theo dõi và thông báo cho các hệ thống khác
 *          về thay đổi trạng thái (ví dụ: nhiệt độ hoặc tốc độ động cơ).
 *          Nó khai báo các phương thức cơ bản cho một chủ thể trong mô hình Observer bao gồm.
 * - Thêm đối tượng quan sát vào danh sách theo dõi
 * - gỡ bỏ 1 đối tượng quan sát khỏi danh sách theo dõi
 * - thông báo cho các đối tượng quan sát
 * - thay đổi trạng thái của động cơ và thông báo
 * - trả về trạng thái hiện tại của động cơ
 */
class ISubject 
{
    protected:
        /**
         * @brief   Thông báo cho tất cả các đối tượng quan sát về thay đổi trạng thái.
         * @return  void
         */
        virtual void notifyObservers() = 0;
    public:
        /**
         * @brief   Gỡ bỏ một đối tượng quan sát khỏi danh sách theo dõi.
         * @param   o   Đối tượng quan sát cần gỡ bỏ.
         * @return  void
         */
        virtual void removeObserver(IObserver * o) = 0;
        /**
         * @brief   Thêm một đối tượng quan sát (Observer) vào danh sách theo dõi.
         * @param   o   Đối tượng quan sát cần thêm.
         * @return  void
         */
        virtual void addObserver(IObserver * o) = 0;
};     

/**
 * **********************************************************
 * @note    Triển khai các phương thức của ISubject 
 * **********************************************************
 */  

/**
 * @class   EngineManager
 * @brief   Quản lý ECU
 * @details Lớp này sẽ đóng vai trò là chủ thể theo dõi và thông báo cho các hệ thống khác 
 *          về thay đổi trạng thái (ví dụ: nhiệt độ hoặc tốc độ động cơ).
 *          Triển khai các phương thức quản lý ECU (ISubject)
 */
class EngineManager : public ISubject
{
    private:
        float temperature;      /** Nhiệt độ của động cơ (oC) */
        int speed;              /** Tốc độ của động cơ (RPM) */
        float throttle_input;   /** Độ mở chân ga (throttle) tính theo phần trăm (0% - 100%). */

        /**
         * @brief Danh sách các đối tượng quan sát (Observer).
         * @details Các đối tượng này sẽ được thông báo khi trạng thái động cơ thay đổi.
         */
        vector <IObserver *> observers;

        /**
         * @brief   Tạo dữ liệu cho các thành phần của động cơ
         * @details Tạo các dữ liệu ngẫu nhiên cho các thành phần nhiệt độ, tốc độ, và nhiên liệu
         * @return  void
         */
        void generateRandomData();

        /**
         * @brief   Thông báo cho tất cả các đối tượng quan sát về thay đổi trạng thái.
         * @return  void
         */
        void notifyObservers();        

    public:
        /**
         * @brief   Khởi tạo đối tượng EngineManager.
         * @details Thiết lập giá trị mặc định cho các tham số của động cơ như nhiệt độ, tốc độ và độ mở bàn đạp ga.
         */
        EngineManager();

        /**
         * @brief   Gỡ bỏ một đối tượng quan sát khỏi danh sách theo dõi.
         * @param   o   Đối tượng quan sát cần gỡ bỏ.
         * @return  void
         */
        void removeObserver(IObserver * o);
       
        /**
         * @brief   Thêm một đối tượng quan sát (Observer) vào danh sách theo dõi.
         * @param   o   Đối tượng quan sát cần thêm.
         * @return  void
         */
        void addObserver(IObserver * o);

        /**
         * @brief   Đặt trạng thái động cơ và thông báo cho các quan sát viên.
         * @details Hàm này gán giá trị cho các thành phần của động cơ và thông báo
         * @return  void
         */
        void setEngineState();

        /**
         * @brief   Lấy trạng thái hiện tại của động cơ.
         * @details Trả về trạng thái hiện tại của động cơ (tốc độ và nhiệt độ).i
         * @return  void
         */
        void getState();
};

/**
 * ************************************************
 * @note    Triển khai các Observer 
 * ************************************************
 */  

/**
 * @class   CoolingSystem
 * @brief   Theo dõi nhiệt độ động cơ. 
 * @details Khi nhiệt độ vượt ngưỡng an toàn (ví dụ: 90 độ C), hệ thống sẽ bật quạt làm mát.
 */
class CoolingSystem : public IObserver
{
    public: 
        /**
         * @brief   Cập nhật trạng thái hệ thống làm mát dựa trên nhiệt độ động cơ.
         * @param   speed          Không sử dụng (để tương thích với interface).
         * @param   temperature    Nhiệt độ hiện tại của động cơ.
         * @param   throttle_input Không sử dụng (để tương thích với interface).
         * @details Hệ thống làm mát sẽ bật nếu nhiệt độ động cơ vượt quá ngưỡng cảnh báo.
         */
        void update(const int & speed, const float & temperature, const float &) override;
};

/**
 * @class   WarningSystem
 * @brief   Hệ thống cảnh báo
 * @details Kích hoạt cảnh báo trên bảng điều khiển khi nhiệt độ vượt quá 100 độ C 
 *          hoặc tốc độ vượt quá 6000 RPM.
 */
class WarningSystem : public IObserver
{        
    public: 
        /**
         * @brief   Kích hoạt cảnh báo dựa trên tốc độ và nhiệt độ của động cơ.
         * @param   speed          Tốc độ hiện tại của động cơ (RPM).
         * @param   temperature    Nhiệt độ hiện tại của động cơ (°C).
         * @param   throttle_input Không sử dụng (để tương thích với interface).
         * @details Kích hoạt cảnh báo khi nhiệt độ hoặc tốc độ vượt ngưỡng giới hạn.
         */
        void update(const int & speed, const float & temperature, const float &) override;
};

/**
 * @class   EngineControlUnit
 * @brief   Hệ thống điều khiển hộp số
 * @details Điều chỉnh các tham số hiệu suất và nhiên liệu khi tốc độ 
 *          hoặc nhiệt độ động cơ thay đổi.
 */
class EngineControlUnit : public IObserver
{
    private:
        float fuel_energy_input;        /** Năng lượng nhiên liệu đầu vào */

        /**
         * @brief   Đặt giá trị mức nhiên liệu đầu vào cho động cơ.
         * @details Hàm này thiết lập giá trị nhiên liệu đầu vào của hệ thống động cơ.
         *          Giá trị này sẽ được sử dụng trong các tính toán liên quan đến 
         *          hiệu suất và công suất của động cơ.
         * @param   fuel_rate Mức nhiên liệu đầu vào (đơn vị: %).
         * @return  void
         */
        void setFuelRate(const float & fuel_rate)
        {
            fuel_energy_input = fuel_rate;
        } 

        /**
         * @brief   Tính toán lượng nhiên liệu nạp vào động cơ.
         * @details Hàm này sẽ tính toán lượng nhiên liệu nạp vào động cơ dựa trên 
         *          tốc độ động cơ, nhiệt độ và độ mở chân ga. Hệ số điều chỉnh 
         *          sẽ được áp dụng để đảm bảo hiệu suất tối ưu của động cơ.
         * @param   speed Tốc độ quay của động cơ (RPM).
         * @param   temperature Nhiệt độ động cơ (°C).
         * @param   throttle_position Độ mở chân ga (0-100%).
         * @return  float Lượng nhiên liệu nạp vào (đơn vị: %).
         */
        float calculateFuelInjectionRate(const int & speed, const float & temperature, const float & throttle_position);
        
        /**
         * @brief   Tính toán công suất đầu ra của động cơ.
         * @details Công suất được tính toán dựa trên mô-men xoắn và tốc độ của động cơ.
         *          Các yếu tố hao phí như ma sát và nhiệt độ sẽ được tính vào để cho 
         *          ra giá trị công suất thực tế.
         * @param   rpm Tốc độ quay của động cơ (RPM).
         * @param   temperature Nhiệt độ động cơ (°C).
         * @return  float Công suất đầu ra của động cơ (đơn vị: kW).
         */        
        float calculateEnergyOutput(const int& rpm,const float& temperature); 

        /**
         * @brief   Tính toán hiệu suất của động cơ.
         * @details Hiệu suất được tính toán dựa trên tỉ lệ giữa công suất đầu ra 
         *          và năng lượng đầu vào. Đây là chỉ số quan trọng để đánh giá 
         *          mức độ hiệu quả của động cơ. 
         * @param   Power Công suất đầu ra thực tế (kW).
         * @param   input_energy Năng lượng đầu vào (đơn vị: %).
         * @return  float Hiệu suất của động cơ (đơn vị: %).
         */        
        float calculateEfficiency(const float& Power,const float& input_energy); //tính toán hiệu suất

    public: 
        /**
         * @brief   Lấy giá trị mức nhiên liệu đầu vào của động cơ.
         * @return  float Giá trị mức nhiên liệu đầu vào (%).
         */
        float getFuelRate()
        {
            return fuel_energy_input;
        }
        /**
         * @brief   Cập nhật giá trị tham số đã được tính toán
         * @details Điều chỉnh các tham số hiệu suất và nhiên liệu khi tốc độ 
         *          hoặc nhiệt độ động cơ thay đổi.
         * @param   speed          Tốc độ hiện tại của động cơ (RPM).
         * @param   temperature    Nhiệt độ hiện tại của động cơ (°C).
         * @param   throttle_position Vị trí hiện tại của bàn đạp ga (%)
         * @return  void
         */
        void update(const int & speed, const float & temperature, const float & throttle_position) override;
};

/**
 * @class   FuelInjectionSystem
 * @brief   Hệ thống điều khiển nhiên liệu.
 */
class FuelInjectionSystem : public IObserver
{
    private:
        EngineControlUnit* ECUbase;     /** Con trỏ đến đơn vị điều khiển động cơ */
    public:
        /**
         * @brief   Khởi tạo hệ thống phun nhiên liệu với đối tượng ECU.
         * @param   ECU Con trỏ tới đối tượng EngineControlUnit.
         */
        //FuelInjectionSystem();
        FuelInjectionSystem(EngineControlUnit* ECU) : ECUbase(ECU){}

        /**
         * @brief   Cập nhật trạng thái hệ thống phun nhiên liệu.
         * @param   speed           Tốc độ động cơ (không sử dụng trong hệ thống này).
         * @param   temperature     Nhiệt độ động cơ (không sử dụng trong hệ thống này).
         * @param   throttle_input  Độ mở bướm ga.
         * @return  void
         */
        void update(const int&,const float&,const float&) override;
};

/**
 * @enum    Gear
 * @brief   Định nghĩa các cấp số của xe (số sàn).
 * @details Enum biểu diễn các trạng thái vào số của xe
 */
enum class Gear
{
    NEUTRAL, // Xe ở trạng thái trung lập
    FIRST,   // Số 1
    SECOND,  // Số 2
    THIRD,   // Số 3
    FOURTH,  // Số 4
    FIFTH,   // Số 5
    SIXTH    // Số 6 (nếu có)
};

/**
 * @class   TransmissionControlUnit
 * @brief   Hệ thống điều khiển hộp số tự động.
 */
class TransmissionControlUnit : public IObserver{
    private:
        /**
         * @brief   Lấy trạng thái số tương ứng với tốc độ động cơ (RPM).\
         * @details Hàm để lấy hệ số truyền động dựa trên tốc độ
         * @param   rpm Giá trị vòng tua động cơ (RPM).
         * @return  Gear Trạng thái số tương ứng.
         */
        Gear getGearForRpm(const int& rpm);
    public:
        /**
         * @brief   Cập nhật trạng thái hệ thống điều khiển hộp số.
         * @param   rpm             Tốc độ động cơ (vòng tua).
         * @param   temperature     Nhiệt độ động cơ (không sử dụng trong hệ thống này).
         * @param   throttle_input  Độ mở bướm ga (không sử dụng trong hệ thống này).
         * @return  void
         */
        void update(const int& rpm,const float& ,const float&) override;
};

#endif // __ECU_HPP   