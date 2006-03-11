#ifndef UNITTEST_TESTRUNNER_H
#define UNITTEST_TESTRUNNER_H


namespace UnitTest
{
class TestReporter;
class TestList;

class TestRunner
{
public:
    int RunAllTests(TestReporter& reporter, const TestList& list);
    
};


int DefaultRun();


}

#endif

