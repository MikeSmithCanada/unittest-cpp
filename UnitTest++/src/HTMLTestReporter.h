#ifndef UNITTEST_HTMLTESTREPORTER_H
#define UNITTEST_HTMLTESTREPORTER_H

#include "TestReporter.h"
#include <vector>

namespace UnitTest
{

class HTMLTestReporter : public TestReporter
{
public:
    virtual void ReportFailure(char const* file, int line, char const* testName, char const* failure);
    virtual void ReportSingleResult(const std::string& testName, bool failed);
    virtual void ReportSummary(int testCount, int failureCount, float secondsElapsed);

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

#endif

