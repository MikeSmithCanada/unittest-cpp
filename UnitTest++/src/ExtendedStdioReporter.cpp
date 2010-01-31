
#include "ExtendedStdioReporter.h"

#include <iostream>
#include <iomanip>

#define LINE "----------------------------------------------------------------------"
#define LINE2 "======================================================================"

namespace UnitTest
{    
    ExtendedStdioReporter::ExtendedStdioReporter() {}
            
    void ExtendedStdioReporter::ReportTestStart(const TestDetails& test)
    {
        std::cout << LINE << std::endl;
        std::cout << "START:  " << test.testName << "  [" << GetFileBasename(test.filename) << "]" << std::endl;
    }

    void ExtendedStdioReporter::ReportFailure(const TestDetails& td, char const* failure)
    {
        std::cout << "    *** " << td.testName  << " (line: " << td.lineNumber << "): " << failure << std::endl;
        
        failureDetails.push_back(td);
    }

    void ExtendedStdioReporter::ReportTestFinish(const TestDetails& test, float secondsElapsed)
    {
        std::cout << "FINISH: " << test.testName << " (" << secondsElapsed << " s)" << std::endl;
    }

    void ExtendedStdioReporter::ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed)
    {
        std::cout << LINE2 << std::endl; 
        
        if (failureCount == 0)
        {
            std::cout << "  PASSED (" << totalTestCount << " tests, " << secondsElapsed << " s)" << std::endl;
        }       
        else
        {
            std::cout << "  FAILURES (" << failedTestCount << " tests/" << failureCount << " failures in a total of " << totalTestCount << " test(s)" << ") ***" << std::endl << std::endl;   
            
            std::cout << std::setfill(' ') << std::left;
            
            unsigned int i = 0;
            while (i < failureDetails.size())
            {
                std::string suiteName = failureDetails[i].suiteName;
                std::cout << "  " << suiteName << ":" << std::endl
                          << "  {" << std::endl;
                
                while ((i < failureDetails.size()) && (failureDetails[i].suiteName == suiteName))
                {
                    std::string testName = failureDetails[i].testName;
                    std::string fileName = failureDetails[i].filename;
                    
                    unsigned int failureCount = 0;
                    while ((i < failureDetails.size()) && (failureDetails[i].testName == testName))
                    {
                        failureCount++;
                        i++;
                    }
                    std::cout << "    " << std::setw(3) << failureCount << std::setw(15) << testName << "(" << fileName << ")" << std::endl;
                }
                          
                std::cout << "  }" << std::endl;                     
            }
            std::cout << "  *** FAILURES ***" << std::endl;
        }
        
        std::cout << LINE2 << std::endl;
    }               
}
