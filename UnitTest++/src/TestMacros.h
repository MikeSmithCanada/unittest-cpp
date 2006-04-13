#ifndef UNITTEST_TESTMACROS_H
#define UNITTEST_TESTMACROS_H


#ifdef TEST
    #error UnitTest++ redefines TEST
#endif

#define TEST_EX(Name,List)                                                 \
    class Test##Name : public UnitTest::Test                               \
    {                                                                      \
    public:                                                                \
        Test##Name() : Test(#Name, __FILE__, __LINE__) {}                  \
    private:                                                               \
        virtual void RunImpl(UnitTest::TestResults& testResults_) const;   \
    } test##Name##Instance;                                                \
    UnitTest::ListAdder adder##Name (List, &test##Name##Instance);         \
    void Test##Name::RunImpl(UnitTest::TestResults& testResults_) const

#define TEST(Name) TEST_EX(Name,UnitTest::Test::GetTestList())


#define TEST_FIXTURE_EX(Fixture, Name, List)                                         \
    struct Fixture##Name##Helper : public Fixture {                                  \
        Fixture##Name##Helper(char const* testName) : m_testName(testName) {}        \
        void RunTest(UnitTest::TestResults& testResults_);                           \
        char const* const m_testName;                                                \
    private:                                                                         \
        Fixture##Name##Helper(Fixture##Name##Helper const&);                         \
        Fixture##Name##Helper& operator =(Fixture##Name##Helper const&);             \
    };                                                                               \
    class Test##Fixture##Name : public UnitTest::Test                                \
    {                                                                                \
    public:                                                                          \
        Test##Fixture##Name() : Test(#Name, __FILE__, __LINE__) {}                   \
    private:                                                                         \
        virtual void RunImpl(UnitTest::TestResults& testResults_) const;             \
    } test##Fixture##Name##Instance;                                                 \
    UnitTest::ListAdder adder##Fixture##Name (List, &test##Fixture##Name##Instance); \
    void Test##Fixture##Name::RunImpl(UnitTest::TestResults& testResults_) const {   \
        try {                                                                        \
            Fixture##Name##Helper mt(m_testName);                                    \
            mt.RunTest(testResults_);                                                \
        }                                                                            \
        catch (...) {                                                                \
            testResults_.OnTestFailure(__FILE__, __LINE__, m_testName,               \
                    "Unhandled exception in fixture " #Fixture);                     \
        }                                                                            \
    }                                                                                \
    void Fixture##Name##Helper::RunTest(UnitTest::TestResults& testResults_)

#define TEST_FIXTURE(Fixture,Name) TEST_FIXTURE_EX(Fixture,Name,UnitTest::Test::GetTestList())        

#endif

