#include "Lib.h"

//nur gültig für std::vector

namespace mystd
{
void advance(It &it, DifferenceType n)
{
    while (n > 0)
    {
        ++it;
        --n;
    }

    while (n < 0)
    {
        --it;
        ++n;
    }
}

DifferenceType distance(It first, It last)
{
    auto dist = DifferenceType{0};

    while (first != last)
    {
        ++first;
        ++dist;
    }

    return dist;

}

It next(It it, DifferenceType n)
{
    mystd::advance(it, n);
    return it;
}

It prev(It it, DifferenceType n)
{
    mystd::advance(it, -n);
    return it;
}
} // namespace mystd
