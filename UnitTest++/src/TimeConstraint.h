#ifndef UNITTEST_TIMECONSTRAINT_H
#define UNITTEST_TIMECONSTRAINT_H

#include "TimeHelpers.h"

namespace UnitTest {

class TestResults;
class TestDetails;

class TimeConstraint
{
public:
    TimeConstraint(int ms, TestResults& result, char const* filename, int lineNumber,
                    TestDetails const& details);
    ~TimeConstraint();

private:
	void operator=(const TimeConstraint&); 

    TestResults& m_result;
    int const m_maxMs;
    char const* const m_filename;
    int const m_lineNumber;
    TestDetails const& m_details;
    Timer m_timer;
};


#define UNITTEST_TIME_CONSTRAINT(ms) TimeConstraint const timeConstraint_##__FILE__##__LINE__##(ms, testResults_, __FILE__,__LINE__, m_details)
#define UNITTEST_TIME_CONSTRAINT_EXEMPT() m_timeConstraintExempt = true

}

#endif
