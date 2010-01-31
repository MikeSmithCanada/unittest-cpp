
#ifndef UNITTEST_EXTENDEDSTDIOREPORTER_H
#define UNITTEST_EXTENDEDSTDIOREPORTER_H

#include <vector>
#include <string>

#include "UnitTest++.h"
#include "TestReporter.h"
#include "Utility.h"

namespace UnitTest
{
    /**
     * Extended Command Line Reporter
     *
     * This reporter print to STDIO status information while running.   
     **/
    class ExtendedStdioReporter : public TestReporter
    {
    public:
        ExtendedStdioReporter();
        
        virtual void ReportTestStart(const TestDetails& test);

        virtual void ReportFailure(const TestDetails& td, const char* failure);
        
        virtual void ReportTestFinish(const TestDetails& test, float secondsElapsed);

        void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed);

    private:    
        std::vector<TestDetails> failureDetails;
        
        ExtendedStdioReporter(const ExtendedStdioReporter &);
        const ExtendedStdioReporter & operator = (const ExtendedStdioReporter &);
    };

}

#endif
