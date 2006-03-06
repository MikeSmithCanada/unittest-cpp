#include "../UnitTest++.h"

using namespace UnitTest;

namespace {


struct MockTest : public Test
{
    MockTest() : Test("", "", 0) {}
    virtual void RunImpl(TestResults& ) {}
};

TEST (RegistrarAddTestToList)
{
    Test* testListHead = 0;;
    Test* testListTail = 0;
    
    MockTest test;
    TestRegistrar registrar(testListHead, testListTail, &test);
    CHECK (testListHead == &test);
    CHECK (testListTail == &test);
}

TEST (TestsAreAddedToListInOrderOfDeclaration)
{
    Test* testListHead = 0;;
    Test* testListTail = 0;
    
    MockTest test1;
    TestRegistrar registrar1(testListHead, testListTail, &test1);
    MockTest test2;
    TestRegistrar registrar2(testListHead, testListTail, &test2);
    
    CHECK (testListHead == &test1);
    CHECK (testListHead->next == &test2);
    CHECK (testListTail == &test2);
}



}
