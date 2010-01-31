
#include "Utility.h"

namespace UnitTest
{
    std::string GetFileBasename(const std::string& filename)
    {
        const std::string::size_type last_slash = filename.find_last_of ("/\\");
        if (last_slash == std::string::npos)
            return filename;
        else if (last_slash == filename.size() - 1)
            return "";
        else
            return filename.substr(last_slash + 1, filename.size ());
    }
}
