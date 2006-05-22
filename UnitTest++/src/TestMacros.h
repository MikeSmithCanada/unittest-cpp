#ifndef UNITTEST_TESTMACROS_H
#define UNITTEST_TESTMACROS_H


#ifdef TEST
    #error UnitTest++ redefines TEST
#endif

#define TEST_EX(Name, Suite, List)                                                 \
    class Test##Suite##Name : public UnitTest::Test                               \
    {                                                                      \
    public:                                                                \
        Test##Suite##Name() : Test(#Name, #Suite, __FILE__, __LINE__) {}                  \
    private:                                                               \
        virtual void RunImpl(UnitTest::TestResults& testResults_) const;   \
    } test##Suite##Name##Instance;                                                \
    UnitTest::ListAdder adder##Suite##Name (List, &test##Suite##Name##Instance);         \
    void Test##Suite##Name::RunImpl(UnitTest::TestResults& testResults_) const

#define TEST(Name) TEST_EX(Name, DefaultSuite, UnitTest::Test::GetTestList())
#define TEST_SUITE(Name, Suite) TEST_EX(Name, Suite, UnitTest::Test::GetTestList())


#define TEST_FIXTURE_EX(Fixture, Name, Suite, List)                                         \
    struct Fixture##Suite##Name##Helper : public Fixture {                                  \
        Fixture##Suite##Name##Helper(UnitTest::TestDetails const& details) : m_details(details) {}    \
        void RunTest(UnitTest::TestResults& testResults_);                           \
        UnitTest::TestDetails const& m_details;                                      \
    private:                                                                         \
        Fixture##Suite##Name##Helper(Fixture##Suite##Name##Helper const&);                         \
        Fixture##Suite##Name##Helper& operator =(Fixture##Suite##Name##Helper const&);             \
    };                                                                               \
    class Test##Fixture##Suite##Name : public UnitTest::Test                                \
    {                                                                                \
    public:                                                                          \
        Test##Fixture##Suite##Name() : Test(#Name, #Suite, __FILE__, __LINE__) {}                   \
    private:                                                                         \
        virtual void RunImpl(UnitTest::TestResults& testResults_) const;             \
    } test##Fixture##Suite##Name##Instance;                                                 \
    UnitTest::ListAdder adder##Fixture##Suite##Name (List, &test##Fixture##Suite##Name##Instance); \
    void Test##Fixture##Suite##Name::RunImpl(UnitTest::TestResults& testResults_) const {   \
        try {                                                                        \
            Fixture##Suite##Name##Helper mt(m_details);                              \
            mt.RunTest(testResults_);                                                \
        }                                                                            \
        catch (...) {                                                                \
            testResults_.OnTestFailure(m_details, __FILE__, __LINE__, \
                    "Unhandled exception in fixture " #Fixture);                     \
        }                                                                            \
    }                                                                                \
    void Fixture##Suite##Name##Helper::RunTest(UnitTest::TestResults& testResults_)

#define TEST_FIXTURE(Fixture,Name) TEST_FIXTURE_EX(Fixture, Name, DefaultSuite, UnitTest::Test::GetTestList())
#define TEST_FIXTURE_SUITE(Fixture,Name,Suite) TEST_FIXTURE_EX(Fixture, Name, Suite, UnitTest::Test::GetTestList())

#endif
