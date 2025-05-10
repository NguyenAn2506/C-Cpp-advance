/**
 * @file    ECU_Test.cpp
 * @brief   Triển khai thiết kế Observer cho hệ thống ô tô.
 * @author  Nta
 */

#include "../inc/ecu.hpp"

/**
 * **********************************************************
 * @note    Triển khai các phương thức của ISubject 
 * **********************************************************
 */  

#define MAX_TEMP                120
#define MAX_RPM                 6000
#define WARNING_TEMP            100
#define WARNING_RPM             6000
#define MAX_PEDAL_APPLY         100
#define OPTIMAL_TEMP            85    // nhiệt độ lý tưởng
#define BASE_FUEL               10

/**
 * @brief   Tạo dữ liệu cho các thành phần của động cơ
 * @details Tạo các dữ liệu ngẫu nhiên cho các thành phần nhiệt độ, tốc độ, và nhiên liệu
 * @return  void
 */
void EngineManager::generateRandomData()
{
    this->speed =  rand() % (MAX_RPM + 1);
    this->temperature = 40 + rand() % 81;
    this->throttle_input = rand() % (MAX_PEDAL_APPLY + 1);
}

/**
 * @brief   Khởi tạo đối tượng EngineManager.
 * @details Thiết lập giá trị mặc định cho các tham số của động cơ như nhiệt độ, tốc độ và độ mở bàn đạp ga.
 */
EngineManager::EngineManager()
{   
    temperature = OPTIMAL_TEMP;
    speed = 0;
    throttle_input = 0.0f;
    cout << "ECU Initialized with default parameters" << endl;
}

/**
 * @brief   Thông báo cho tất cả các đối tượng quan sát về thay đổi trạng thái.
 * @param   o   Đối tượng quan sát (Observer) sẽ nhận thông báo.
 * @return  void
 */
void EngineManager::notifyObservers() 
{
    for(const auto & ob : observers)
    {
        ob->update(speed, temperature, throttle_input);
    }
}       
        
/**
 * @brief   Gỡ bỏ một đối tượng quan sát khỏi danh sách theo dõi.
 * @param   o   Đối tượng quan sát cần gỡ bỏ.
 * @return  void
 */
void EngineManager::removeObserver(IObserver * o) 
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
void EngineManager::addObserver(IObserver * o)
{
    observers.push_back(o);
}

/**
 * @brief   Đặt trạng thái động cơ và thông báo cho các quan sát viên.
 * @return  void
 */
void EngineManager::setEngineState()
{
    generateRandomData();
    notifyObservers();
}

/**
 * @brief   Lấy trạng thái hiện tại của động cơ.
 * @details Trả về trạng thái hiện tại của động cơ (tốc độ và nhiệt độ).
 * @return  void
 */
void EngineManager::getState()
{
    cout << "Display: speed: " << speed << " " << "- temperature: " << temperature << endl;
}

/**
 * ************************************************
 * @note    Triển khai các Observer 
 * ************************************************
 */  

/**
 * @brief   Theo dõi nhiệt độ động cơ. 
 * @details Khi nhiệt độ vượt ngưỡng an toàn (ví dụ: 90 độ C), hệ thống sẽ bật quạt làm mát.
 * @return  void
 */
void CoolingSystem::update(const int&,const float& temperature,const float&) 
{
    if(temperature > WARNING_TEMP){
        cout << "Cooling System is running ON" << endl;
    }
    else
    {
        cout << "Cooling System is running OFF" << endl;
    }
}


/**
 * @brief   Hệ thống cảnh báo
 * @details Kích hoạt cảnh báo trên bảng điều khiển khi nhiệt độ vượt quá 100 độ C 
 *          hoặc tốc độ vượt quá 6000 RPM.
 */
void WarningSystem::update(const int & speed, const float & temperature, const float &)
{
    if(speed >= WARNING_RPM && temperature >= WARNING_TEMP)
    {
        cout << "WARNING: Temperature is too high and speed is too fast!" << endl;
    }
    else if(speed >= WARNING_RPM)
    {
        cout << "WARNING: Speed exceeds the limit (Limit = 6000 RPM)!" << endl;
    }
    else if(temperature >= WARNING_TEMP)
    {
        cout << "WARNING: Temperature exeeds the limit (Limit = 100 oC)!" << endl;
    }
}

/**
 * @brief   Hệ thống điều khiển hộp số
 * @details Điều chỉnh các tham số hiệu suất và nhiên liệu khi tốc độ 
 *          hoặc nhiệt độ động cơ thay đổi.
 */
void EngineControlUnit :: update(const int & speed, const float & temperature, const float & throttle_position)
{
    float fuel_rate_adjusted = calculateFuelInjectionRate(speed,temperature,throttle_position);
    float Power = calculateEnergyOutput(speed,temperature);
    float efficiency = calculateEfficiency(Power,fuel_rate_adjusted);

    cout << "Transmission Control: Adjusting engine parameters." << endl;
    //cout << "throttle_input: " << throttle_input << " %" << endl;
    cout << "Corrected fuel level: " << fuel_rate_adjusted << " %" << endl;
    cout << "Efficiency: " << efficiency << " %" << endl;  
};

/**
 * @brief   Cập nhật trạng thái hệ thống phun nhiên liệu.
 */
void  FuelInjectionSystem :: update(const int&,const float&,const float&)
{
    float read_fuel = ECUbase->getFuelRate();
    cout << "fuel injection with";
    if(read_fuel < 30)  cout << " small capacity";
    else if(read_fuel >= 30 && read_fuel < 60) cout << " average capacity";
    else cout << " high capacity";
    cout << " at fuel level " << read_fuel << " %" << endl;
};

/**
 * @brief   Cập nhật trạng thái hệ thống điều khiển hộp số.
 */
void TransmissionControlUnit::update(const int& rpm,const float& ,const float&){

    Gear gear = getGearForRpm(rpm);
    cout << "Adjust automatic transmission -> Gear:";

    switch (gear)
    {
        case Gear::NEUTRAL:
            cout << " Neutral";
            break;
        case Gear::FIRST:
            cout << " First";
            break;
        case Gear::SECOND:
            cout << " Second";
            break;
        case Gear::THIRD:
            cout << " Third";
            break;
        case Gear::FOURTH:
            cout << " Fourth";
            break;
        case Gear::FIFTH:
            cout << " Fifth";
            break;
        case Gear::SIXTH:
            cout << " Sixth";
            break;
    }
    cout << endl;
}

/**
 * @brief   Tính toán lượng nhiên liệu nạp vào động cơ.
 * @details Hàm này sẽ tính toán lượng nhiên liệu nạp vào động cơ dựa trên 
 *          tốc độ động cơ, nhiệt độ và độ mở chân ga. Hệ số điều chỉnh 
 *          sẽ được áp dụng để đảm bảo hiệu suất tối ưu của động cơ.
 */
float EngineControlUnit::calculateFuelInjectionRate(const int& rpm ,const float& temperature,const float& throttle_input)
{
    float k_rpm = 0.0f , k_temp = 0.0f;
    //lambda để cài đặt các hệ số tốc độ và nhiệt độ ảnh hưởng tới điều chỉnh mức nhiên liệu
    auto AdjustFactor = [=](float& k_rpm,float& k_temp)
    {
        //điều chỉnh hệ số nhiên liệu dựa trên tốc độ
        if(rpm >= 1500 && rpm <= 3000)
        {
            k_rpm = 1.5f;  // tăng nhẹ đối với tốc độ vừa phải
        }
        else if(rpm <= 5000)
        {
            k_rpm = 2.0f; //tăng mạnh đối với tốc độ cao
        }
        else if(rpm > 5000)
        {
            k_rpm = 2.5f;
        }
        //điều chỉnh hệ số nhiên liệu dựa trên nhiệt độ
        if(temperature < OPTIMAL_TEMP)
        {
            k_temp = 1.2f; //tăng mức nhiên liệu khi nhiệt độ dưới mức lý tưởng
        }
        else if(temperature > WARNING_TEMP)
        {
            k_temp = 0.8f; //giảm mức nhiên liệu khi nhiệt độ quá cao
        }
    };
    
    AdjustFactor(k_rpm,k_temp);
    
    float fuel_rate = throttle_input + k_rpm * (rpm /MAX_RPM) + k_temp * (temperature / MAX_TEMP);
    
    if(fuel_rate < BASE_FUEL) fuel_rate = BASE_FUEL;
    setFuelRate(fuel_rate);
    return fuel_rate;
}

/**
 * @brief   Tính toán công suất đầu ra của động cơ.
 * @details Công suất được tính toán dựa trên mô-men xoắn và tốc độ của động cơ.
 *          Các yếu tố hao phí như ma sát và nhiệt độ sẽ được tính vào để cho 
 *          ra giá trị công suất thực tế.
 */
float EngineControlUnit::calculateEnergyOutput(const int& rpm,const float& temperature)
{
    //tính toán mo-men xoắn ở các giá trị rpm khác nhau
    auto torque = [](const int& rpm)
    {
        #define MAX_TORQUE 300
        if (rpm <= 3000) { // Dưới 50% maxRPM, mô-men xoắn tăng dần
            return MAX_TORQUE * (0.5 + 0.5 * (rpm / 3000.0));
        } else { // Sau 50% maxRPM, mô-men xoắn giảm dần
            return MAX_TORQUE * (1.0 - 0.5 * ((rpm - 3000.0) / (6000 - 3000.0)));
        }
    };
    //tính toán tổng thất năng lượng ở các mức tốc độ và nhiệt độ
    auto loss_energy = [](const int& rpm,const float& temperature,const float& raw_energy)
    {
        //he so ton that do ma sat
        float friction_loss_factor = 0.1f + (rpm/MAX_RPM) * 0.05f;
        //he so ton that nhiet
        float thermal_loss_factor = 0.3f + (temperature / 120.0f) * 0.2f;
        //he so ton that bom
        float pumping_loss_factor = 0.05f + ((MAX_RPM - rpm) / MAX_RPM) * 0.05f;
        //ton that nang luong
        float sum_factor = friction_loss_factor + thermal_loss_factor + pumping_loss_factor;

        //giới hạn giá trị hệ số tổng tiêu hao năng lượng
        if(sum_factor > 1.0f) sum_factor = 1.0f;
        return sum_factor*raw_energy;
    };
    
    //Công suất đầu ra chưa tính hao phí 
    float raw_energy = (torque(rpm) * rpm)/ 5252; 
    float loss = loss_energy(rpm,temperature,raw_energy);
        
    
    //giới hạn giá trị năng lượng tiêu hao trong mức an toàn
    if(raw_energy < loss) raw_energy = loss;

    return raw_energy - loss;  // Công suất đầu ra thực tế sau khi loại bỏ hao phí
}

/**
 * @brief   Tính toán hiệu suất của động cơ.
 * @details Hiệu suất được tính toán dựa trên tỉ lệ giữa công suất đầu ra 
 *          và năng lượng đầu vào. Đây là chỉ số quan trọng để đánh giá 
 *          mức độ hiệu quả của động cơ. 
 */
float EngineControlUnit::calculateEfficiency(const float& Power,const float& input_energy)
{
    if(input_energy == 0) return 0;
    return (Power / input_energy) * 100; //Hiệu suất % 
}

/**
 * @brief   Lấy trạng thái số tương ứng với tốc độ động cơ (RPM).\
 * @details Hàm để lấy hệ số truyền động dựa trên tốc độ
 */
Gear TransmissionControlUnit::getGearForRpm(const int& rpm)
{
    //bản đồ ánh xạ giá trị tốc độ tương ứng với các số tương ứng
    const map<int, Gear> speedToGear = {
        {0, Gear::NEUTRAL},
        {1000, Gear::FIRST},
        {2000, Gear::SECOND},
        {3000, Gear::THIRD},
        {4000, Gear::FOURTH},
        {5000, Gear::FIFTH},
        {6000, Gear::SIXTH} // Giá trị lớn nhất
    };
    //tìm kiếm và trả về giá trị enum biểu diển cho tốc độ
    for(const auto& it : speedToGear){
        if(rpm <= it.first){
            return it.second;
        }
    }
    return Gear::SIXTH;
}