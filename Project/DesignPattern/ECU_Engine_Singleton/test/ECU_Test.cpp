#include <iostream>
#include <cstdlib>
#include <fstream>      // work with file
#include <vector>
#include <ctime>        // work with time
#include <iomanip>      // working with real numbers

using namespace std;

#define MAX_RPM 6000        // sô vòng quay tối đa
#define MAX_TEMP 120        // nhiệt độ cao nhất
#define WARNING_TEMP 100    // nhiệt độ cảnh báo
#define OPTIMAL_TEMP 80     // nhiệt độ lý tưởng

class EngineControlUnit
{
    private:
        // Private constructor ngăn chặn việc khởi tạo bên ngoài
        EngineControlUnit()    // dùng để khởi tạo đối tượng duy nhất và các thông số mặc định ban đầu
        {
            ECU_Init();
        }

        static EngineControlUnit* instance;
        int rpm;                // tốc độ -> só vòng quay
        float temperature;      // nhiệt độ
        vector<int> rpm_history;
        vector<float> temp_history;

        /**
         * @brief       Hàm thiết lập tốc độ động cơ (RPM)
         * @details     Cấu hình giá trị tốc độ phải nằm trong khoảng từ 0 đến 6000 RPM để đảm bảo an toàn 
         * @param       int
         * @param[out]  speed    biến lưu giá trị tốc độ thiết lập
         * @return      void
         */
        void setEngineSpeed(int speed)
        {
            if(speed >= 0 && speed <= MAX_RPM)
            {
                rpm = speed;
                rpm_history.push_back(speed);
            }
            else
            {
                cout << "Warning Invalid RPM: " << speed << endl;
            }
        }

        /**
         * @brief       Hàm thiết lập nhiệt độ động cơ (Celsius)
         * @details     Giá trị nhiệt độ phải nằm trong khoảng từ -20 đến 120 độ C để mô phỏng phạm vi nhiệt độ thực tế của động cơ
         * @param       float
         * @param[out]  temp    biến lưu giá trị nhiệt độ thiết lập
         * @return      void
         */
        void setEngineTemperature(float temp)
        {
            if(temp >= -20.0f || temp <= MAX_TEMP)
            {
                temperature = temp;
                temp_history.push_back(temp);
            }
            else 
            {
                cout << "Warning: Invalid engine temperature: " << temp << endl;
            }
        }

        /**
         * @brief       Hàm hiển thị giá trị tốc độ hiện tại động cơ (RPM)
         * @param       
         * @return      int
         */
        int getEngineSpeed () const 
        { 
            return rpm;
        }

        /**
         * @brief       Hàm hiển thị giá trị nhiệt độ hiện tại động cơ (Celsius)
         * @param       
         * @return      float
         */
        float getEngineTemperature() const 
        { 
            return temperature; 
        }

        /**
         * @brief       Hàm kiểm tra động cơ quá nhiệt
         * @param       
         * @return      bool
         */
        bool IsOverHeating()
        {
            if(temperature >= WARNING_TEMP)
            {
                cout << "Warning Over Heating\n";
                return true;
            }
            return false;
        }

        

    public:
        static EngineControlUnit *getInstance()
        {
            if(!instance)
            {
                instance = new EngineControlUnit();
                // bổ sung thêm tính năng
            }
            return instance;
        }

        static void freeInstance()
        {
            if (instance != nullptr)
            {
                delete instance;
                instance = nullptr;
            }
        }

        void ECU_Init()
        {
            rpm = 0.0f;
            temperature = OPTIMAL_TEMP;
            rpm_history.clear();
            temp_history.clear();
            cout << "ECU initialized successfully with default sensor parameters\n";
        }

        /**
         * @brief       hàm tạo ngẫu nhiên các giá trị mô phỏng 
         * @param       
         * @return      void
         */
        void GenerateRandomData()
        {
            int random_rpm = rand() % (MAX_RPM + 1);
            float random_temp = ((rand() % 1401) - 200) / 10.0f; // -20.0 to 120.0
            setEngineSpeed(random_rpm);
            setEngineTemperature(random_temp);
        } 

        /**
         * @brief       Hàm đọc các giá trị của tốc độ và nhiệt độ của động cơ
         * @param       
         * @return      void
         */
        void ECU_Read()
        {
            /**
             * #include <iomanip>
             * fixed: dùng để yêu câu hiển thị số thực ở dạng thập phân cố định
             * setprecision(2): là chỉ định số lượng chữ số thập phân sau dấu . (nếu đã dùng fixed)
             */
            cout << fixed << setprecision(2);
            cout << "[Sensor] RPM: " << rpm << " | Temperature: " << temperature << " C\n";
        }

        /**
         * @brief       Hàm lưu trữ tốc độ và nhiệt độ của động cơ vào file csv
         * @details     vừa lưu trữ vừa run chương trình
         * @param       
         * @return      void
         */
        void ECU_SaveData()
        {
            ofstream file("ECU_data.csv", ios::app);

            if (file.is_open())
            {
                file << rpm << "," << fixed << setprecision(2) << temperature << "," << "\n";
                file.close();
            }
            else
            {
                cout << "[Error] Could not open file to save data.\n";
            }
        }

        /**
         * @brief       Hàm in ra chuẩn đoán các giá trị đã lưu trong file csv của các lần chạy
         * @param       
         * @return      void
         */
        void ECU_Diagnostics()
        {
            cout << "\n[Diagnostics Report]\n";
            for (size_t i = 0; i < rpm_history.size(); ++i)
            {
                cout << "#" << i + 1 << " -> RPM: " << rpm_history[i]
                    << ", Temp: " << fixed << setprecision(2) << temp_history[i];
                if (temp_history[i] > WARNING_TEMP)
                    cout << " [!! Overheat Warning !!]";
                cout << endl;
            }
        }


};

// khởi tạo giá trị ban đầu cho biến static instance
EngineControlUnit* EngineControlUnit::instance = nullptr;

int main()
{
    srand(time(0));
    EngineControlUnit *ECU = EngineControlUnit::getInstance();

    for (int i = 0; i < 10; ++i)
    {
        ECU->GenerateRandomData();
        ECU->ECU_Read();
        ECU->ECU_SaveData();
    }

    ECU->ECU_Diagnostics();

    /**
     * @note        Sau khi sử dụng xong instance, nên gọi freeInstance() để tránh rò rỉ bộ nhớ.
     */
    EngineControlUnit::freeInstance();
    return 0;
}
