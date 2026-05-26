#include "class.h"

bool operator<(const Dog& d1, const Dog& d)
{
    return d1.name < d.name;
}

ostream& operator<<(ostream& out, const Dog& d)
{
    out << d.name << " : " << d.chs;
    return out;
}
