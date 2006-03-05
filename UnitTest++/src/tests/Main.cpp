#include "../UnitTest++.h"
#include "../PrintfTestReporter.h"

int main(int, char const *[])
{
    UnitTest::PrintfTestReporter reporter;
    return UnitTest::TestRunner(reporter).RunAllTests();
}

