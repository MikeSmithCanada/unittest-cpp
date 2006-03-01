#ifndef TEST_REPORTER_H
#define TEST_REPORTER_H

#include <string>

namespace UnitTest
{

class TestReporter
{
public:
    virtual ~TestReporter();

    virtual void ReportFailure(char const* file, int line, const char* testName, std::string failure) = 0;
    virtual void ReportSingleResult(const std::string& testName, bool failed) = 0;
    virtual void ReportSummary(int testCount, int failureCount) = 0;

protected:
    TestReporter();
};

}
#endif

