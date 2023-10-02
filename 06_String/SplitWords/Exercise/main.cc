#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "Lib.h"
#include "utils.hpp"

int main()
{
    auto text = readFile("C:/Users/much1/Documents/ComputerVision/UdemyCPPExercises/UdemyCppExercises/06_String/SplitWords/Exercise/text.txt");
    std::cout << text << '\n' << '\n';

    clean_text(text);
    std::cout << text << '\n' << '\n';

    const auto splittedText = split_text(text, ' ');
    print_vector(splittedText);

    return 0;
}
