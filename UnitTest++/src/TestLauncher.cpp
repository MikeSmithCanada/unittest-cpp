#include "TestLauncher.h"

namespace UnitTest
{


TestLauncher::TestLauncher(Test*& listHead, Test* test)
{
    test->next = listHead;
    listHead = test;
}


}

