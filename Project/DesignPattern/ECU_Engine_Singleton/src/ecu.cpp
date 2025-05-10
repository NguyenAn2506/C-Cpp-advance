#include "../inc/ecu.hpp"

// khởi tạo giá trị ban đầu cho biến static instance
EngineControlUnit* EngineControlUnit::instance = nullptr;

EngineControlUnit::EngineControlUnit()
{
    throttle_input = 0.0f;
    brake_input = 0.0f;
    isbrake = brake_status::release;
    rpm = 0;
    temperature = OPTIMAL_TEMP;
    rpm_history.clear();
    temp_history.clear();
    cout << "ECU initialized successfully with default sensor parameters\n";
}

/* PUBLIC INTERFACE */

void EngineControlUnit::GenerateRandomData()
{
    int random_rpm = rand() % (MAX_RPM + 1);
    float random_temp = ((rand() % 1401) - 200) / 10.0f; // simulation temperature from -20.0 to 120.0
    float random_throttle_position = rand() % (MAX_PEDAL + 1);
    float random_brake_position = rand() % (MAX_PEDAL + 1);
    brake_status isbrake = static_cast<brake_status>(rand() % static_cast<int>(limit_brake_status));

    setEngineSpeed(random_rpm);
    setEngineTemperature(random_temp);
    setThrottlePosition(random_throttle_position);
    setBrakePosition(random_brake_position);
    setBrakeStatus(isbrake);
}

void EngineControlUnit::ECU_Diagnostics()
{
    cout << "\n[Diagnostics Report]\n";
    if(dataRead(PATH) == FAIL)
    {
        cout << "Read data failed" << endl;
        return;
    }
    else
    {
        for (size_t i = 0; i < rpm_history.size(); ++i)
        {
            cout << "#" << i + 1 << " -> RPM: " << rpm_history[i]
                << ", Temp: " << fixed << setprecision(2) << temp_history[i];
            if (temp_history[i] > WARNING_TEMP)
                cout << " [!! Overheat Warning !!]";
            cout << endl;
        }
    }
}

void EngineControlUnit::ECU_SaveData()
{
    if((dataRecord(PATH, rpm_history, temp_history)) == FAIL)
    {
        cout<< "Reserve data failed" << endl;
        return;
    }
    // else
    // {
    //     ofstream file("ECU_data.csv", ios::app);

    //     if (file.is_open())
    //     {
    //         file << rpm << "," << fixed << setprecision(2) << temperature << "," << "\n";
    //         file.close();
    //     }
    //     else
    //     {
    //         cout << "[Error] Could not open file to save data.\n";
    //     }
    // }
}

void EngineControlUnit::ECU_Read()
{
    GenerateRandomData();
    cout << "Speed: " << getEngineSpeed() << "rpm\ttemperature: " << getEngineTemperature() << " oC" << endl;
    if(IsOverHeating())
    {
        cout << "!! Overheat Warning !! " << endl;
    }
}

void EngineControlUnit::setFuelInjectionRate()
{
    CalculateFuelRate();
    cout << "Fuel level: " << getFuelRate() << " %" << endl;
}

void EngineControlUnit::BrakeControlInteraction()
{
    auto isbrake = getBrakeStatus();
    LimitFuelByBrake(isbrake);
    if(isbrake == brake_status::press) 
    {
        cout << "is braking" << endl;
    }
    else if (isbrake == brake_status::release)
    {
        cout << "brake release" << endl;
    }
}

/* PRIVATE INTERFACE */

void EngineControlUnit::CalculateFuelRate()
{
    // các hệ số điều chỉnh nhiên liệu tốc độ và nhiệt độ
    float k_rpm = 0.0f, k_temp = 0.0f;
    
    // hiệu chỉnh tốc độ
    AdjustFactor(k_rpm, k_temp);

    // tính toán mức nhiên liệu
    float fuel_Adjust = throttle_input + k_rpm * (rpm/MAX_RPM) + k_temp  * (temperature / MAX_TEMP);

    // duy trì mức nhiên liệu ở mức tối thiểu khi tốc độ giảm về 0
    if(fuel_rate < BASE_FUEL)
    {
        fuel_rate = BASE_FUEL;
    }
    setFuelRate(fuel_Adjust);
}

void EngineControlUnit::LimitFuelByBrake(const brake_status& isbrake)
{
    if(isbrake == brake_status::press)
    {
        if(getEngineSpeed() < 1500)
        {
            float fuel_reduction = 1.0f - (brake_input / MAX_PEDAL);
            fuel_rate -= fuel_reduction;
        }
        else
        {
            cout << "The brakes have been applied to slow down." << endl;
        }
    }
}

void EngineControlUnit::AdjustFactor(float& k_rpm, float& k_temp)
{
    // điều chỉnh hệ số nhiên liệu dựa trên tốc độ
    if(rpm >= 1500 && rpm <= 3000)
    {
        k_rpm = 1.5f;   //tăng nhẹ đối với tốc độ vừa phải
    }
    else if(rpm <= 5000)
    {
        k_rpm = 2.0f;   // tăng mạnh với tốc độ cao
    }
    else if(rpm > 5000){
        k_rpm = 2.5f;   
    }
    //điều chỉnh hệ số nhiên liệu dựa trên nhiệt độ
    if(temperature < OPTIMAL_TEMP){
        k_temp = 1.2f; //tăng mức nhiên liệu khi nhiệt độ dưới mức lý tưởng
    }
    else if(temperature > WARNING_TEMP){
        k_temp = 0.8f; //giảm mức nhiên liệu khi nhiệt độ quá cao
    }
}

void EngineControlUnit::setEngineSpeed(const int& speed)
{
    rpm = speed;
    rpm_history.push_back(speed);
    if(speed > MAX_RPM)
    {
        cout << "Warning Invalid RPM: " << speed << " speed must be less than 6000 " << endl;
    }
}

void EngineControlUnit::setEngineTemperature(const float& temp)
{
    temperature = temp;
    temp_history.push_back(temp);
    if (temp > 120 || temp < -20)
    {
        cout << "CẢNH BÁO, NHIỆT ĐỘ PHẢI NẰM TRONG KHOẢNG TỪ -20 - 120 °C" << endl;
    }
}
bool EngineControlUnit::IsOverHeating()
{
    if (temperature > WARNING_TEMP)
    {
        return true;
    }        
    return false;
}
