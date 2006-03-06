#ifndef TEST_LAUNCHER_H
#define TEST_LAUNCHER_H

#include "Test.h"

namespace UnitTest
{
class TestResults;
class TestRegistry;

class TestLauncher
{
public:
    TestLauncher(Test*& listHead, Test* test);
};



}

#endif

