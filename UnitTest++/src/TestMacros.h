#ifndef TEST_MACROS_H
#define TEST_MACROS_H

//----------------------------
#define TEST(Name) \
    class Test##Name : public UnitTest::Test \
    { \
    public: \
        Test##Name() : Test(#Name, __FILE__, __LINE__) {} \
    private: \
        virtual void RunImpl(UnitTest::TestResults& testResults_); \
    }; \
    UnitTest::TypedTestLauncher< Test##Name > \
        staticInitTest##Name##Creator(UnitTest::TestLauncher::GetHeadAddr()); \
    \
    void Test##Name::RunImpl(UnitTest::TestResults& testResults_)

//----------------------------
#define TEST_FIXTURE(Fixture, Name) \
    class Test##Name : public UnitTest::Test, public Fixture \
    { \
    public: \
        Test##Name() : Test(#Name, __FILE__, __LINE__) {} \
    private: \
        virtual void RunImpl(UnitTest::TestResults& testResults_); \
    }; \
    UnitTest::TypedTestLauncher< Test##Name > \
        staticInitTest##Name##Creator(UnitTest::TestLauncher::GetHeadAddr()); \
    \
    void Test##Name::RunImpl(UnitTest::TestResults& testResults_)

//----------------------------
#define TEST_FIXTURE_CTOR(Fixture, CtorParams, Name) \
    class Test##Name : public UnitTest::Test, public Fixture \
    { \
    public: \
        Test##Name() : Test(#Name, __FILE__, __LINE__), Fixture CtorParams {} \
    private: \
        virtual void RunImpl(UnitTest::TestResults& testResults_); \
    }; \
    UnitTest::TypedTestLauncher< Test##Name > \
        staticInitTest##Name##Creator(UnitTest::TestLauncher::GetHeadAddr()); \
    \
    void Test##Name::RunImpl(UnitTest::TestResults& testResults_)


#endif

