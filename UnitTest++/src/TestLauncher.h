#ifndef TEST_LAUNCHER_H
#define TEST_LAUNCHER_H

namespace UnitTest
{
class TestResults;
class TestRegistry;

class TestLauncher
{
public:
    virtual void Launch(TestResults& results_) const = 0;

    static TestLauncher** GetHeadAddr();
    TestLauncher const* GetNext() const;

protected:
    TestLauncher(TestLauncher** listHead, char const* filename, int line, char const* testName);
    virtual ~TestLauncher();

    char const* const m_filename;
    const int m_line;
    char const* const m_testName;
    
private:
    TestLauncher const* m_next;

    // revoked
    TestLauncher();
    TestLauncher(TestLauncher const&);
    TestLauncher& operator =(TestLauncher const&);    
};
}

#endif

