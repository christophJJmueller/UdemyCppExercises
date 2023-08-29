#include <cstdint>
#include <iostream>
#include <cmath>

#include "lib.h"

double calculate_pi(const std::uint32_t num_iterations)
{
    double result = 0.0;

    for (std::uint32_t i = 0; i < (num_iterations); i++)
    {
        result += (1.0/(4.0*i+1.0)) - (1.0/(4.0*i+3.0));
    }

    return result*4.0;

}

void print_dec_to_bin(std::uint8_t value)
{
    for (std::int8_t i = 7; i >= 0; i--)
    {
        if ((value >= pow(2,i)))
        {
            std::cout << "1";
            value -= pow(2,i);
        }
        else
            std::cout << "0";

    }
    std::cout << "\n";

}
