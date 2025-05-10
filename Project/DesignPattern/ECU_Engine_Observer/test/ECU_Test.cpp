/**
 * @file    ECU_Test.cpp
 * @brief   Triển khai thiết kế Observer cho hệ thống ô tô.
 * @details Test Code 1
 * @author  Nta
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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
         * @param   speed Tốc độ động cơ được cập nhật.
         * @param   temperature Nhiệt độ động cơ được cập nhật.
         * @return  void
         */
        virtual void update(int speed, float temperature) = 0;
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
         * @param   o   Đối tượng quan sát (Observer) sẽ nhận thông báo.
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
        double temperature = 0.0f;
        int speed = 0;
        vector <IObserver *> observers;
    protected:
        /**
         * @brief   Thông báo cho tất cả các đối tượng quan sát về thay đổi trạng thái.
         * @param   o   Đối tượng quan sát (Observer) sẽ nhận thông báo.
         * @return  void
         */
        void notifyObservers() 
        {
            for(const auto & ob : observers)
            {
                ob->update(temperature, speed);
            }
        }
    public:
        /**
         * @brief   Gỡ bỏ một đối tượng quan sát khỏi danh sách theo dõi.
         * @param   o   Đối tượng quan sát cần gỡ bỏ.
         * @return  void
         */
        void removeObserver(IObserver * o) 
        {
            // observers.remove(observer);

            // tìm ra đối tượng => xóa
            auto observer = find(observers.begin(), observers.end(), o);

            if(observer != observers.end())
            {
                observers.erase(observer);
            }
        }

        /**
         * @brief   Thêm một đối tượng quan sát (Observer) vào danh sách theo dõi.
         * @param   o   Đối tượng quan sát cần thêm.
         * @return  void
         */
        void addObserver(IObserver * o)
        {
            observers.push_back(o);
        }

        /**
         * @brief   Đặt trạng thái động cơ và thông báo cho các quan sát viên.
         * @param   _speed Tốc độ động cơ.
         * @param   _temperature Nhiệt độ động cơ.
         * @return  void
         */
        void setEngineState(int _speed, float _temperature)
        {
            speed = _speed;
            temperature = _temperature;
            notifyObservers();
        }

        /**
         * @brief   Lấy trạng thái hiện tại của động cơ.
         * @details Trả về trạng thái hiện tại của động cơ (tốc độ và nhiệt độ).
         * @return  void
         */
        void getState()
        {
            cout << "Display: speed: " << speed << " " << "- temperature: " << temperature << endl;
        }

        /**
         * @brief   mô phỏng chương trình
         * @details hàm này set thời gian để hệ thống hoạt động
         * @return  void
         */
        void simulateEngine()
        {
            srand(static_cast<unsigned>(time(0)));
            for(int i = 0; i < 10; ++i)
            {
                int randomSpeed = rand() % 8000;
                float randomTemp = (rand() % 150) + (rand() % 100) / 100.0;
                setEngineState(randomSpeed, randomTemp);
                getState();
            }
        }

        /**
         * @brief   điều chỉnh tham số của hệ thống
         * @details Khi có sự thay đổi nhỏ không ảnh hưởng đến trạng thái tổng thể của động cơ 
         *          (ví dụ: thay đổi nhỏ trong khoảng nhiệt độ an toàn), 
         *          hệ thống không cần thông báo cho các đối tượng quan sát để tránh quá tải 
         *          và xử lý không cần thiết).
         * @return  void
         */
        void adjustParameters(float& k_rpm, float& k_temp)
        {
            if(speed >= 1500 && speed <= 3000) k_rpm = 1.5f;
            else if(speed <= 5000) k_rpm = 2.0f;
            else if(speed > 5000) k_rpm = 2.5f;

            if(temperature < 90.0f) k_temp = 1.2f;
            else if(temperature > 100.0f) k_temp = 0.8f;
        }
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
        void update(int speed, float temperature)
        {
            if(temperature >= 90)
            {
                cout << "Cooling System is running ON" << endl;
            }
        }
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
        void update(int speed, float temperature)
        {
            if(speed >= 6000 && temperature >= 100)
            {
                cout << "WARNING: Temperature is too high and speed is too fast!" << endl;
            }
            else if(speed >= 6000)
            {
                cout << "WARNING: Speed exceeds the limit (limit = 6000 RPM)!" << endl;
            }
            else if(temperature >= 100)
            {
                cout << "WARNING: Temperature exeeds the limit (limit = 100 oC)!" << endl;
            }
        }
};

/**
 * @class   EngineControlUnit
 * @brief   Hệ thống điều khiển hộp số
 * @details Điều chỉnh các tham số hiệu suất và nhiên liệu khi tốc độ 
 *          hoặc nhiệt độ động cơ thay đổi.
 */
class EngineControlUnit : public IObserver
{
    void update(int speed, float temperature) 
    {
        cout << "Transmission Control: Adjusting engine parameters." << endl;
    }
};

/**
 * @class   FuelInjectionSystem
 * @brief   Hệ thống điều khiển nhiên liệu.
 */
class FuelInjectionSystem : public IObserver
{
    public:
        void update(int speed, float temperature)
        {
            float k_rpm = 1.0f, k_temp = 1.0f;
            EngineManager engine;
            engine.adjustParameters(k_rpm, k_temp);
            cout << "Fuel Injection: Fuel adjustment with RPM factor: " << k_rpm << " | Temperature: " << k_temp << endl;

        }
};

/**
 * @brief   Chương trình chính 
 */
int main(int argc, char const *argv[])
{

    EngineManager engine;

    CoolingSystem coolingSystem;
    WarningSystem warningSystem;
    FuelInjectionSystem fuelSystem;
    EngineControlUnit transmissionControl;

    engine.addObserver(&coolingSystem);
    engine.addObserver(&warningSystem);
    engine.addObserver(&fuelSystem);
    engine.addObserver(&transmissionControl);

    engine.simulateEngine();

    return 0;
}
