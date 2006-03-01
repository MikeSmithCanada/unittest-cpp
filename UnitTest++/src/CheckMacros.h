#ifndef CHECK_MACROS_H 
#define CHECK_MACROS_H

#include "Checks.h"
#include "AssertException.h"

#define CHECK(value) \
    try { \
        if (!UnitTest::Check(value)) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), #value); \
    } \
    catch (...) { \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), "Unhandled exception: crash!"); \
    }

#define CHECK_NULL(ptr) \
    if (!UnitTest::CheckNull(ptr)) \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), #ptr " is not NULL.");

#define CHECK_NOT_NULL(ptr) \
    if (UnitTest::CheckNull(ptr)) \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), #ptr " is NULL.");

#define CHECK_EQUAL(expected, actual) \
    try { \
        if (!UnitTest::CheckEqual(expected, actual)) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), UnitTest::BuildFailureString(expected, actual)); \
    } \
    catch (...) { \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), "Unhandled exception: crash!"); \
    }

#define CHECK_CLOSE(expected, actual, tolerance) \
    try { \
        if (!UnitTest::CheckClose(expected, actual, tolerance)) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), UnitTest::BuildFailureString(expected, actual)); \
    } \
    catch (...) { \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), "Unhandled exception: crash!"); \
    }

#define CHECK_ARRAY_EQUAL(expected, actual, count) \
    if (!UnitTest::CheckArrayEqual(expected, actual, count)) \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), UnitTest::BuildFailureString(expected, actual, count));

#define CHECK_ARRAY_CLOSE(expected, actual, count, tolerance) \
    if (!UnitTest::CheckArrayClose(expected, actual, count, tolerance)) \
        testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), UnitTest::BuildFailureString(expected, actual, count));

#define CHECK_THROW(expression, ExpectedExceptionType) \
    { \
        bool caught_ = false; \
        \
        try { expression; } \
        catch (ExpectedExceptionType const&) { caught_ = true; } \
        \
        if (!caught_) \
            testResults_.ReportFailure(__FILE__, __LINE__, m_testName.c_str(), "Expected exception: \"" #ExpectedExceptionType "\" not thrown"); \
    }

#define CHECK_ASSERT(expression) \
    CHECK_THROW(expression, UnitTest::AssertException);

#endif

