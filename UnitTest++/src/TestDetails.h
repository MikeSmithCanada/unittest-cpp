#ifndef UNITTEST_TESTDETAILS_H
#define UNITTEST_TESTDETAILS_H

namespace UnitTest {

class TestDetails
{
public:
    explicit TestDetails(char const* testName, char const* suiteName = "DefaultSuite", 
        char const* filename = "", int lineNumber = 0);

    char const* const suiteName;
    char const* const testName;
    char const* const filename;
    int const lineNumber;

private:
    TestDetails(TestDetails const&);
    TestDetails& operator=(TestDetails const&);
};

}

#endif
