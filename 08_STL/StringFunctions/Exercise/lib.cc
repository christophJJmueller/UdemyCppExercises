#include <algorithm>

#include "lib.h"

namespace mystd
{

bool is_palindrom(std::string_view str)
{
    std::string temp{};
    std::copy(str.crbegin(), str.crend(), std::back_inserter(temp));

    return std::equal(str.begin(), str.end(), temp.begin());
}

bool starts_with(std::string_view str, std::string_view substr)
{
    return std::equal(substr.begin(), substr.end(), str.begin());
}

bool ends_with(std::string_view str, std::string_view substr)
{
    return std::equal(substr.rbegin(), substr.rend(), str.rbegin());
}

bool contains(std::string_view str, std::string_view substr)
{
    auto substr_length = substr.length();

    for (auto it = str.begin(); it < str.end() - substr_length +1; it++)
    {
        auto found = std::equal(substr.begin(), substr.end(), it);
        if (found == true)
            return true;
    }
    return false;
}

std::size_t num_occurences(std::string_view str, std::string_view substr)
{
    std::size_t counter = 0;

    auto substr_length = substr.length();

    for (auto it = str.begin(); it < str.end() - substr_length +1; it++)
    {
        auto found = std::equal(substr.begin(), substr.end(), it);
        if (found == true)
            counter++;
    }

    return counter;
}

} // namespace mystd
