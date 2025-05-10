#include "../inc/ecu.hpp"
#include "../inc/record.hpp"
#include "../inc/os.hpp"

int main()
{
    uint32_t sample_period = 250; //chu kỳ lấy mẫu
    uint32_t sample_time = 100; // số lần lấy mẫus
    EngineControlUnit *ECU1 = EngineControlUnit::ECU_Init();
    simulation(ECU1, sample_period, sample_time);
}