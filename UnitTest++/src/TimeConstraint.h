#ifndef UNITTEST_TIMECONSTRAINT_H
#define UNITTEST_TIMECONSTRAINT_H

#include "TimeHelpers.h"

namespace UnitTest {

class TestResults;
class TestDetails;

class TimeConstraint
{
public:
    TimeConstraint(int ms, TestResults& result, TestDetails const& details);
    ~TimeConstraint();

private:
    void operator=(const TimeConstraint&); 

    TestResults& m_result;
    int const m_maxMs;
    TestDetails const& m_details;
    Timer m_timer;
};


#define UNITTEST_TIME_CONSTRAINT(ms) TimeConstraint t__(ms, testResults_, UnitTest::TestDetails(m_details, __LINE__))
#define UNITTEST_TIME_CONSTRAINT_EXEMPT() m_timeConstraintExempt = true

}

#endif
