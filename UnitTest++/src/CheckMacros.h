#ifndef UNITTEST_CHECKMACROS_H 
#define UNITTEST_CHECKMACROS_H

#include "Checks.h"
#include "AssertException.h"


#define CHECK(value) \
    try { \
        if (!UnitTest::Check(value)) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName, #value); \
    } \
    catch (...) { \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName, \
                "Unhandled exception in CHECK(" #value ")"); \
    }

#define CHECK_NULL(ptr) \
    if (!UnitTest::CheckNull(ptr)) \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName, #ptr " is not NULL.");

#define CHECK_NOT_NULL(ptr) \
    if (UnitTest::CheckNull(ptr)) \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName, #ptr " is NULL.");

#define CHECK_EQUAL(expected, actual) \
    try { \
        if (!UnitTest::CheckEqual(expected, actual)) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName, \
                UnitTest::BuildFailureString(expected, actual).c_str()); \
    } \
    catch (...) { \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName, \
                "Unhandled exception in CHECK_EQUAL(" #expected ", " #actual ")"); \
    }

#define CHECK_CLOSE(expected, actual, tolerance) \
    try { \
        if (!UnitTest::CheckClose(expected, actual, tolerance)) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName, \
                UnitTest::BuildFailureString(expected, actual, tolerance).c_str()); \
    } \
    catch (...) { \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName, \
                "Unhandled exception in CHECK_CLOSE(" #expected ", " #actual ")"); \
    }

#define CHECK_ARRAY_EQUAL(expected, actual, count) \
    try { \
        if (!UnitTest::CheckArrayEqual(expected, actual, count)) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName, \
                        UnitTest::BuildFailureString(expected, actual, count).c_str()); \
    } \
    catch (...) { \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName, \
                "Unhandled exception in CHECK_ARRAY_EQUAL(" #expected ", " #actual ")"); \
    }

#define CHECK_ARRAY_CLOSE(expected, actual, count, tolerance) \
    try { \
        if (!UnitTest::CheckArrayClose(expected, actual, count, tolerance)) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName, \
                    UnitTest::BuildFailureString(expected, actual, count, tolerance).c_str()); \
    } \
    catch (...) { \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName, \
                "Unhandled exception in CHECK_ARRAY_CLOSE(" #expected ", " #actual ")"); \
    }

#define CHECK_THROW(expression, ExpectedExceptionType) \
    { \
        bool caught_ = false; \
        \
        try { expression; } \
        catch (ExpectedExceptionType const&) { caught_ = true; } \
        \
        if (!caught_) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName, "Expected exception: \"" #ExpectedExceptionType "\" not thrown"); \
    }

#define CHECK_ASSERT(expression) \
    CHECK_THROW(expression, UnitTest::AssertException);

#endif

