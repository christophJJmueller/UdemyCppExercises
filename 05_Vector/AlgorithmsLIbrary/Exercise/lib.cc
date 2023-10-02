#include <cstddef>
#include <cstdint>
#include <vector>

#include "lib.h"

bool all_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
{
    bool is_all_of = false;

    for (auto &i : vector)
    {
        if(i == value)
            is_all_of = true;
        else
            is_all_of = false;
    }

    return is_all_of;
}

bool any_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
{
    bool is_any_of = false;

    for (auto &i : vector)
    {
        if(i == value)
            is_any_of = true;
    }

    return is_any_of;
}

bool none_of(const std::vector<std::int32_t> &vector, const std::int32_t value)
{
    bool is_none_of = true;

    for (auto &i : vector)
    {
        if(i == value)
            is_none_of = false;
    }

    return is_none_of;
}

std::size_t count(const std::vector<std::int32_t> &vector,
                  const std::int32_t value)
{
    std::size_t counter = 0;

    for (auto &i : vector)
    {
        if(i == value)
            counter++;
    }

    return counter;
}
