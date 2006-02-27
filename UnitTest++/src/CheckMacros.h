#ifndef CHECK_MACROS_H 
#define CHECK_MACROS_H

#include "Checks.h"
#include "AssertException.h"

#define CHECK(value) \
    if (!UnitTest::Check(value)) \
        testResults_.ReportFailure(__FILE__, __LINE__, #value);

#define CHECK_NULL(ptr) \
    if (!UnitTest::CheckNull(ptr)) \
        testResults_.ReportFailure(__FILE__, __LINE__, #ptr " is not NULL.");

#define CHECK_NOT_NULL(ptr) \
    if (UnitTest::CheckNull(ptr)) \
        testResults_.ReportFailure(__FILE__, __LINE__, #ptr " is NULL.");

#define CHECK_EQUAL(expected, actual) \
    if (!UnitTest::CheckEqual(expected, actual)) \
        testResults_.ReportFailure(__FILE__, __LINE__, UnitTest::BuildFailureString(expected, actual));

#define CHECK_CLOSE(expected, actual, tolerance) \
    if (!UnitTest::CheckClose(actual, expected, tolerance)) \
        testResults_.ReportFailure(__FILE__, __LINE__, UnitTest::BuildFailureString(expected, actual));

#define CHECK_ARRAY_EQUAL(expected, actual, count) \
    if (!UnitTest::CheckArrayEqual(actual, expected, count)) \
        testResults_.ReportFailure(__FILE__, __LINE__, UnitTest::BuildFailureString(expected, actual, count));

#define CHECK_ARRAY_CLOSE(expected, actual, count, tolerance) \
    if (!UnitTest::CheckArrayClose(actual, expected, count, tolerance)) \
        testResults_.ReportFailure(__FILE__, __LINE__, UnitTest::BuildFailureString(expected, actual, count));

#define CHECK_THROW(expression, ExpectedExceptionType) \
    { \
        bool caught_ = false; \
        \
        try { expression; } \
        catch (ExpectedExceptionType const&) { caught_ = true; } \
        \
        if (!caught_) \
            testResults_.ReportFailure(__FILE__, __LINE__, "Expected exception: \"" #ExpectedExceptionType "\" not thrown"); \
    }

#define CHECK_ASSERT(expression) \
    CHECK_THROW(expression, UnitTest::AssertException);

#endif

