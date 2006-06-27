#ifndef UNITTEST_CHECKMACROS_H 
#define UNITTEST_CHECKMACROS_H

#include "Checks.h"
#include "AssertException.h"
#include "MemoryOutStream.h"

#ifdef CHECK
    #error UnitTest++ redefines CHECK
#endif

#define CHECK(value) \
    try { \
        if (!UnitTest::Check(value)) \
            testResults_.OnTestFailure(m_details, __FILE__, __LINE__, #value); \
    } \
    catch (...) { \
        testResults_.OnTestFailure(m_details, __FILE__, __LINE__, \
                "Unhandled exception in CHECK(" #value ")"); \
    }

#define CHECK_EQUAL(expected, actual) \
    try { \
        UnitTest::CheckEqual(testResults_, expected, actual, m_details, __FILE__, __LINE__); \
    } \
    catch (...) { \
        testResults_.OnTestFailure(m_details, __FILE__, __LINE__, \
                "Unhandled exception in CHECK_EQUAL(" #expected ", " #actual ")"); \
    }

#define CHECK_CLOSE(expected, actual, tolerance) \
    try { \
        UnitTest::CheckClose(testResults_, expected, actual, tolerance, m_details, __FILE__, __LINE__); \
    } \
    catch (...) { \
        testResults_.OnTestFailure(m_details, __FILE__, __LINE__, \
                "Unhandled exception in CHECK_CLOSE(" #expected ", " #actual ")"); \
    }

#define CHECK_ARRAY_EQUAL(expected, actual, count) \
    try { \
        UnitTest::CheckArrayEqual(testResults_, expected, actual, count, m_details, __FILE__, __LINE__); \
    } \
    catch (...) { \
        testResults_.OnTestFailure(m_details, __FILE__, __LINE__, \
                "Unhandled exception in CHECK_ARRAY_EQUAL(" #expected ", " #actual ")"); \
    }

#define CHECK_ARRAY_CLOSE(expected, actual, count, tolerance) \
    try { \
        UnitTest::CheckArrayClose(testResults_, expected, actual, count, tolerance, m_details, __FILE__, __LINE__); \
    } \
    catch (...) { \
        testResults_.OnTestFailure(m_details, __FILE__, __LINE__, \
                "Unhandled exception in CHECK_ARRAY_CLOSE(" #expected ", " #actual ")"); \
    }

#define CHECK_ARRAY2D_CLOSE(expected, actual, rows, columns, tolerance) \
    try { \
        UnitTest::CheckArray2DClose(testResults_, expected, actual, rows, columns, tolerance, m_details, __FILE__, __LINE__); \
    } \
    catch (...) { \
        testResults_.OnTestFailure(m_details, __FILE__, __LINE__, \
                "Unhandled exception in CHECK_ARRAY_CLOSE(" #expected ", " #actual ")"); \
    }



#define CHECK_THROW(expression, ExpectedExceptionType) \
    { \
        bool caught_ = false; \
        try { expression; } \
        catch (ExpectedExceptionType const&) { caught_ = true; } \
        if (!caught_) \
            testResults_.OnTestFailure(m_details, __FILE__, __LINE__, "Expected exception: \"" #ExpectedExceptionType "\" not thrown"); \
    }

#define CHECK_ASSERT(expression) \
    CHECK_THROW(expression, UnitTest::AssertException);

#endif
