#include "Checks.h"
#include <cstring>

namespace UnitTest {

bool CheckEqual(char const* expected, char const* actual)
{
    return (!std::strcmp(expected, actual));
}

bool CheckEqual(char* expected, char* actual)
{
    return (!std::strcmp(expected, actual));
}

bool CheckEqual(char* expected, char const* actual)
{
    return (!std::strcmp(expected, actual));
}

bool CheckEqual(char const* expected, char* actual)
{
    return (!std::strcmp(expected, actual));
}


}
