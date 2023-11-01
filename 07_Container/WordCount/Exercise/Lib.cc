#include <filesystem>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "Lib.h"

void clean_text(std::string &text)
{
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

WordVector split_text(const std::string &text, char delimiter)
{
    auto words = WordVector{};

    auto iss = std::istringstream{text};
    auto item = std::string{};

    while (std::getline(iss, item, delimiter))
    {
        words.push_back(item);
    }

    return words;
}

CountedWordsMap count_words(const WordVector &words)
{
    //Vector(String) -> Map
    /*
    1) Vector Element lesen
    2) Vorhandensein in Map prüfen
        2.1) JA: Zähler +1
        2.2) NEIN: neu anlegen, Zähler = 1
    3) nächstes Vector Element
    */

   auto WordMap = CountedWordsMap{};

   for (auto it_vec = words.begin(); it_vec != words.end(); it_vec++)
   {
        auto current_word = WordCountPair(*it_vec, 1);

        if (!WordMap.contains(*it_vec))
        {
            WordMap.insert(current_word);
        }
        else
        {
            WordMap[*it_vec] += 1;
        }
   }

   return WordMap;

}

WordCountVec map_to_vector(const CountedWordsMap &counted_words)
{
    //Map(Pairs) -> Vector(Pairs)
    auto WordVec = WordCountVec{};

    for (auto it_map = counted_words.begin(); it_map != counted_words.end(); it_map++)
    {
        WordVec.push_back(*it_map);
    }

    return WordVec;

}

bool compare(WordCountPair &pair1, WordCountPair &pair2)
{
    return pair1.second > pair2.second;
}

void sort_word_counts(WordCountVec &word_counts)
{
    //Sort Vector(Pairs)
    std::sort(word_counts.begin(), word_counts.end(), compare);

}
