#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <sstream>

#include "Lib.h"

void clean_text(std::string &text)
{
    // const auto search_str = ".,!?\n\t";

    // while (text.find_first_of(search_str) != std::string::npos)
    // {
    //     auto idx = text.find_first_of(search_str);
    //     text.replace(idx, 1, "");
    // }
    replace_all(text, ".", "");
    replace_all(text, ",", "");
    replace_all(text, "!", "");
    replace_all(text, "?", "");
    replace_all(text, "\n", "");
    replace_all(text, "\t", "");
}

void replace_all(std::string &text,
                 std::string_view what,
                 std::string_view with)
{
    for (std::size_t pos = 0; pos != std::string::npos; pos += with.length())
    {
        pos = text.find(what.data(), pos, what.length());

        if (pos != std::string::npos)
        {
            text.replace(pos, what.length(), with.data(), with.length());
        }
    }
}

std::vector<std::string> split_text(const std::string &text, char delimiter)
{
    auto words = std::vector<std::string>{};

    auto iss = std::istringstream{text};
    auto item = std::string{};

    while (std::getline(iss, item, delimiter))
    {
        words.push_back(item);
    }

    return words;
}
