#ifndef UNITTEST_TESTMACROS_H
#define UNITTEST_TESTMACROS_H


#define TEST(Name) \
    class Test##Name : public UnitTest::Test                                            \
    {                                                                                   \
    public:                                                                             \
        Test##Name() : Test(#Name, __FILE__, __LINE__) {}                               \
    private:                                                                            \
        virtual void RunImpl(UnitTest::TestResults& testResults_) const;                      \
    } test##Name##Instance;                                                             \
    UnitTest::ListAdder adder##Name (UnitTest::Test::s_list, &test##Name##Instance);    \
    void Test##Name::RunImpl(UnitTest::TestResults& testResults_) const
    
    
#define TEST_FIXTURE(Fixture, Name)                                                 \
    struct Fixture##Name##Helper : public Fixture {                                 \
        Fixture##Name##Helper(char const* testName) : m_testName(testName) {}       \
        void RunTest(UnitTest::TestResults& testResults_);                          \
        char const* const m_testName;                                               \
	private:																		\
		Fixture##Name##Helper(Fixture##Name##Helper const&);						\
		Fixture##Name##Helper& operator =(Fixture##Name##Helper const&);			\
    };                                                                              \
    class Test##Fixture##Name : public UnitTest::Test                               \
    {                                                                               \
    public:                                                                         \
        Test##Fixture##Name() : Test(#Name, __FILE__, __LINE__) {}                  \
    private:                                                                        \
        virtual void RunImpl(UnitTest::TestResults& testResults_) const;                  \
    } test##Fixture##Name##Instance;                                                \
    UnitTest::ListAdder adder##Fixture##Name (UnitTest::Test::s_list, &test##Fixture##Name##Instance); \
    void Test##Fixture##Name::RunImpl(UnitTest::TestResults& testResults_) const {  \
        Fixture##Name##Helper mt(m_testName);                                       \
        mt.RunTest(testResults_);                                                   \
    }                                                                               \
    void Fixture##Name##Helper::RunTest(UnitTest::TestResults& testResults_)
    

#endif

