
#include "../UnitTest++.h"

#include "../ExtendedStdioReporter.h"

#include <iostream>
#include <sstream>

using namespace UnitTest;

SUITE(ExtendedStdioReporter)
{
    struct StdIoFixture
    {
        std::stringstream coutStream;
        std::streambuf* tmpCoutBuf;
        
        StdIoFixture()
        : tmpCoutBuf(NULL) {}
        
        void CaptureStdio()
        {
            tmpCoutBuf = std::cout.rdbuf();
            std::cout.rdbuf(coutStream.rdbuf());
        }
        
        void RestoreStdio()
        {
            if (tmpCoutBuf != NULL)
                std::cout.rdbuf(tmpCoutBuf);
        }
        
        ~StdIoFixture()
        {
            RestoreStdio();    
        }
    };
    
    TEST(IsDefaultCostructible)
    {
        ExtendedStdioReporter reporter;
    }
    
    TEST_FIXTURE(StdIoFixture, Output)
    {
        const TestDetails details("Test", "Suite", "File.txt", 1337);
        
        CaptureStdio();
        
        ExtendedStdioReporter reporter;
        reporter.ReportTestStart(details);
        reporter.ReportFailure(details, "message");
        reporter.ReportTestFinish(details, 1.0F);
        
        RestoreStdio();
        
        std::string result = coutStream.str();
        std::string reference =
            "----------------------------------------------------------------------\n"
            "START:  Test  [File.txt]\n"
            "    *** Test (line: 1337): message\n"
            "FINISH: Test (1 s)\n";   
        
        CHECK_EQUAL(reference, result);
    }
    
    TEST_FIXTURE(StdIoFixture, OutputSumarySuccess)
    {
        const TestDetails details1("Test1", "Suite", "File.txt", 1337);
        const TestDetails details2("Test2", "Suite", "File.txt", 1338);
        const TestDetails details3("Test3", "Suite", "File.txt", 1339);
        const TestDetails details4("Test3", "Suite", "File.txt", 1340);
        
        CaptureStdio();
        
        ExtendedStdioReporter reporter;
        
        reporter.ReportTestStart(details1);
        reporter.ReportTestFinish(details1, 1.1F);
        
        reporter.ReportTestStart(details2);
        reporter.ReportTestFinish(details2, 1.2F);
        
        reporter.ReportTestStart(details3);
        reporter.ReportTestFinish(details3, 1.3F);
        
        reporter.ReportSummary(3, 0, 0, 4.5f);
        
        RestoreStdio();
        
        std::string result = coutStream.str();
        std::string reference =
            "----------------------------------------------------------------------\n"
            "START:  Test1  [File.txt]\n"
            "FINISH: Test1 (1.1 s)\n"
            "----------------------------------------------------------------------\n"
            "START:  Test2  [File.txt]\n"
            "FINISH: Test2 (1.2 s)\n"
            "----------------------------------------------------------------------\n"
            "START:  Test3  [File.txt]\n"
            "FINISH: Test3 (1.3 s)\n"
            "======================================================================\n"
            "  PASSED (3 tests, 4.5 s)\n"
            "======================================================================\n";   
                
        CHECK_EQUAL(reference, result);
    }
    
    TEST_FIXTURE(StdIoFixture, OutputSumary)
    {
        const TestDetails details1("Test1", "MySuite", "File.txt", 1337);
        const TestDetails details2("Test2", "MySuite ", "File.txt", 1338);
        const TestDetails details3("Test3", "MySuite", "File.txt", 1339);
        const TestDetails details4("Test3", "MySuite", "File.txt", 1340);
        
        CaptureStdio();
        
        ExtendedStdioReporter reporter;
        
        reporter.ReportTestStart(details1);
        reporter.ReportTestFinish(details1, 1.1F);
        
        reporter.ReportTestStart(details2);
        reporter.ReportFailure(details2, "Ouch!");
        reporter.ReportTestFinish(details2, 1.2F);
        
        reporter.ReportTestStart(details3);
        reporter.ReportFailure(details3, "An error.");
        reporter.ReportFailure(details4, "An other one.");
        reporter.ReportTestFinish(details3, 1.3F);
        
        reporter.ReportSummary(3, 1, 2, 4.5f);
        
        RestoreStdio();
        
        std::string result = coutStream.str();
        std::string reference =
            "----------------------------------------------------------------------\n"
            "START:  Test1  [File.txt]\n"
            "FINISH: Test1 (1.1 s)\n"
            "----------------------------------------------------------------------\n"
            "START:  Test2  [File.txt]\n"
            "    *** Test2 (line: 1338): Ouch!\n"
            "FINISH: Test2 (1.2 s)\n"
            "----------------------------------------------------------------------\n"
            "START:  Test3  [File.txt]\n"
            "    *** Test3 (line: 1339): An error.\n"
            "    *** Test3 (line: 1340): An other one.\n"
            "FINISH: Test3 (1.3 s)\n"
            "======================================================================\n"
            "  FAILURES (1 tests/2 failures in a total of 3 test(s)) ***\n"
            "\n"
            "  MySuite :\n"
            "  {\n"
            "    1  Test2          (File.txt)\n"
            "  }\n"
            "  MySuite:\n"
            "  {\n"
            "    2  Test3          (File.txt)\n"
            "  }\n"
            "  *** FAILURES ***\n"
            "======================================================================\n";               
                
        CHECK_EQUAL(reference, result);
    }
}
