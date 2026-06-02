#include "class.h"

bool operator<(const Dog& d1, const Dog& d)
{
    return d1.name < d.name;
}

std::ostream& operator<<(std::ostream& out, const Dog& d)
{
    out << d.name;
    return out;
}
