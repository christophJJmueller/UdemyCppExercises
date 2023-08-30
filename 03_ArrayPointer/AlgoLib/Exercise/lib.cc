#include <cstddef>
#include <cstdint>

#include "lib.h"

bool all_of(const std::int32_t *array,
            const std::size_t length,
            const std::int32_t value)
{
    if (array == nullptr || length == 0)
    {
        return false;
    }

    bool is_all_of = false;

    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            is_all_of = true;
        }
        else
            is_all_of = false;

    }

    return is_all_of;

}

bool any_of(const std::int32_t *array,
            const std::size_t length,
            const std::int32_t value)
{
    if (array == nullptr || length == 0)
    {
        return false;
    }

    bool is_any_of = false;

    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            is_any_of = true;
        }

    }

    return is_any_of;

}

bool none_of(const std::int32_t *array,
             const std::size_t length,
             const std::int32_t value)
{
    if (array == nullptr || length == 0)
    {
        return false;
    }

    bool is_none_of = true;

    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            is_none_of = false;
        }

    }

    return is_none_of;

}

std::size_t count(const std::int32_t *array,
                  const std::size_t length,
                  const std::int32_t value)
{
    if (array == nullptr || length == 0)
    {
        return 0;
    }

    std::size_t counter = 0;

    for (std::size_t i = 0; i < length; i++)
    {
        if (array[i] == value)
        {
            counter += 1;
        }

    }


    return counter;
}
