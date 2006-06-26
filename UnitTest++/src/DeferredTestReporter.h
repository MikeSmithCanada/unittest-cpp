#ifndef UNITTEST_DEFERREDTESTREPORTER_H
#define UNITTEST_DEFERREDTESTREPORTER_H

#include "TestReporter.h"
#include "DeferredTestResult.h"

#include <vector>

namespace UnitTest
{

class DeferredTestReporter : public TestReporter
{
public:
    virtual void ReportTestStart(TestDetails const& details);
    virtual void ReportFailure(TestDetails const& details, char const* file, int line, char const* failure);
    virtual void ReportTestFinish(TestDetails const& details, float secondsElapsed);

    virtual void ReportSummary(int testCount, int failureCount, float secondsElapsed) = 0;

	typedef std::vector< DeferredTestResult > DeferredTestResultList;
	DeferredTestResultList& GetResults();

private:
    DeferredTestResultList m_results;
};

}

#endif //UNITTEST_DEFERREDTESTREPORTER_H
