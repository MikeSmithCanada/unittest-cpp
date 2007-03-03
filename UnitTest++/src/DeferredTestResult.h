#ifndef UNITTEST_DEFERREDTESTRESULT_H
#define UNITTEST_DEFERREDTESTRESULT_H

#include <string>

namespace UnitTest
{

struct DeferredTestResult
{
	DeferredTestResult();
    DeferredTestResult(char const* suite, char const* test);

    std::string suiteName;
    std::string testName;
    std::string failureFile;
    std::string failureMessage;
    int failureLine;
    float timeElapsed;
	bool failed;
};

}

#endif //UNITTEST_DEFERREDTESTRESULT_H
