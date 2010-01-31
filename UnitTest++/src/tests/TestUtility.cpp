
#include "../UnitTest++.h"

#include "../Utility.h"

using namespace UnitTest;

SUITE(Utility)
{
    TEST(BastnameWin32Path)
    {
        std::string path = "C:\\foo\\moo\\file.txt";
        CHECK_EQUAL("file.txt", GetFileBasename(path));
    }
    
    TEST(BasenamePosixPath)
    {
        std::string path = "/stuff/someplace/file.txt";
        CHECK_EQUAL("file.txt", GetFileBasename(path));
    }
}
