#include "XmlTestReporter.h"
#include "Config.h"

#include <iostream>
#include <sstream>
#include <string>

using std::string;
using std::ostringstream;
using std::ostream;

namespace {

void ReplaceChar(string& str, char c, string const& replacement)
{
    for (size_t pos = str.find(c); pos != string::npos; pos = str.find(c, pos + 1))
        str.replace(pos, 1, replacement);
}

string XmlEscape(string const& value)
{
    string escaped = value;

    ReplaceChar(escaped, '&', "&amp;");
    ReplaceChar(escaped, '<', "&lt;");
    ReplaceChar(escaped, '>', "&gt;");
    ReplaceChar(escaped, '\'', "&apos;");
    ReplaceChar(escaped, '\"', "&quot;");
 
    return escaped;
}

string BuildFailureMessage(string const& file, int line, string const& message)
{
    ostringstream failureMessage;
    failureMessage << file << "(" << line << ") : " << message;
    return failureMessage.str();
}

}

namespace UnitTest {

XmlTestReporter::XmlTestReporter(ostream& ostream)
    : m_ostream(ostream)
{
}

void XmlTestReporter::ReportSummary(int totalTestCount, int failedTestCount,
                                    int failureCount, float secondsElapsed)
{
    AddXmlElement(m_ostream, NULL);

    BeginResults(m_ostream, totalTestCount, failedTestCount, failureCount, secondsElapsed);

    DeferredTestResultList const& results = GetResults();
    for (DeferredTestResultList::const_iterator i = results.begin(); i != results.end(); ++i)
    {
        BeginTest(m_ostream, *i);

        if (i->failed)
            AddFailure(m_ostream, *i);

        EndTest(m_ostream, *i);
    }

    EndResults(m_ostream);
}

void XmlTestReporter::AddXmlElement(ostream& os, char const* encoding)
{
    os << "<?xml version=\"1.0\"";

    if (encoding != NULL)
        os << " encoding=\"" << encoding << "\"";

    os << "?>\n";
}

void XmlTestReporter::BeginResults(std::ostream& os, int totalTestCount, int failedTestCount, 
                                   int failureCount, float secondsElapsed)
{
   os << "<unittest-results"
       << " tests=\"" << totalTestCount << "\"" 
       << " failedtests=\"" << failedTestCount << "\"" 
       << " failures=\"" << failureCount << "\"" 
       << " time=\"" << secondsElapsed << "\""
       << ">\n";
}

void XmlTestReporter::EndResults(std::ostream& os)
{
    os << "</unittest-results>";
}

void XmlTestReporter::BeginTest(std::ostream& os, DeferredTestResult const& result)
{
    os << "\t<test"
        << " suite=\"" << result.suiteName << "\"" 
        << " name=\"" << result.testName << "\""
        << " time=\"" << result.timeElapsed << "\"";
}

void XmlTestReporter::EndTest(std::ostream& os, DeferredTestResult const& result)
{
    if (result.failed)
        os << "\t</test>";
    else
        os << "/>";

	os << "\n";
}

void XmlTestReporter::AddFailure(std::ostream& os, DeferredTestResult const& result)
{
    os << ">\n"; // close <test> element

	typedef DeferredTestResult::FailureVec::const_iterator FailureIterator;

    for (FailureIterator it = result.failures.begin(); it != result.failures.end(); ++it)
    {
        string const escapedMessage = XmlEscape(it->second);
        string const message = BuildFailureMessage(result.failureFile, it->first, escapedMessage);

        os << "\t\t<failure" << " message=\"" << message << "\"" << "/>\n";
    }
}

}
