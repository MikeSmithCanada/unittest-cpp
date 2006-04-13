#ifndef UNITTEST_TIMECONSTRAINT_H
#define UNITTEST_TIMECONSTRAINT_H

#include "TimeHelpers.h"

namespace UnitTest {

class TestResults;


class TimeConstraint
{
public:
    TimeConstraint(int ms, TestResults& result, char const* filename, int lineNumber,
                    char const* testName);
    ~TimeConstraint();

private:
	void operator=(const TimeConstraint&); 

    TestResults& m_result;
    int const m_maxMs;
    char const* const m_filename;
    int const m_lineNumber;
    char const* const m_testName;
    Timer m_timer;
};


#define UNITTEST_TIME_CONSTRAINT(ms) TimeConstraint t__(ms,testResults_,__FILE__,__LINE__,m_testName)
#define UNITTEST_TIME_CONSTRAINT_EXEMPT() m_timeConstraintExempt = true

}

#endif
