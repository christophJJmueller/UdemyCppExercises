#include <iostream>

#include "AirConditioner.h"

float AirConditioner::measure()
{
    auto measured_temp = get_rand_float(-20.0F, 45.0F);
    std::cout << "Measured Temp: " << measured_temp << ", current setting: " << target_temp << std::endl;
    return measured_temp;
}

int AirConditioner::activate(float curr_temp)
{
    current_temp = curr_temp;
    if ((current_temp < -20.0F) || (current_temp > 45.0F))
        return -1;
    else
    {
        auto temp_diff = target_temp - current_temp;
        if (temp_diff > 0)
        {
            int heat_time = std::round(temp_diff * 2);
            heat(heat_time);
            return heat_time;
        }
        else if (temp_diff < 0)
        {
            int cool_time = std::round(temp_diff);
            cool(cool_time);
            return cool_time;
        }
        else
            return 0;
    }
}

bool AirConditioner::heat(int duration)
{
    do
    {
        for (std::size_t i = 0; i < duration; i++)
        {
            if(i%2==0 && i != 0)
                current_temp++;
            std::cout << "The current temp is: " << current_temp << ". Remaining heating time: " << duration << std::endl;
            duration--;
        }

    } while (duration >= 0);
    return duration >= 0;

}

bool AirConditioner::cool(int duration)
{
    do
    {
        for (std::size_t i = 0; i < duration; i++)
        {
            current_temp--;
            std::cout << "The current temp is: " << current_temp << ". Remaining heating time: " << duration << std::endl;
            duration--;
        }

    } while (duration >= 0);
    return duration >= 0;
}
