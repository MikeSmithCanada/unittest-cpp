#ifndef HTML_TEST_REPORTER_H
#define HTML_TEST_REPORTER_H

#include "TestReporter.h"
#include <vector>

namespace UnitTest
{

class HTMLTestReporter : public TestReporter
{
public:
    virtual void ReportFailure(char const* file, int line, const char* testName, std::string failure);
    virtual void ReportSingleResult(const std::string& testName, bool failed);
    virtual void ReportSummary(int testCount, int failureCount);

private:
    typedef std::vector<std::string> MessageList;

    struct ResultRecord 
    {
        std::string testName;
        bool failed;
        MessageList failureMessages;
    };

    MessageList m_failureMessages;

    typedef std::vector<ResultRecord> ResultList;
    ResultList m_results;
};

}

#endif //HTML_TEST_REPORTER

