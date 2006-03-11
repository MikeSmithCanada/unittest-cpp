#ifndef UNITTEST_BUILDFAILURESTRING_H
#define UNITTEST_BUILDFAILURESTRING_H


#include <sstream>


namespace UnitTest {

    
    template< typename Expected, typename Actual>
    std::string BuildFailureString(Expected const expected, Actual const actual)
    {
        std::stringstream failureStr;
        failureStr << "Expected " << expected << " but was " << actual;
        return failureStr.str();
    }

    template< typename Expected, typename Actual, typename Tolerance>
    std::string BuildFailureString(Expected const expected, Actual const actual, Tolerance const tolerance)
    {
        std::stringstream failureStr;
        failureStr << "Expected " << expected << " +/- " << tolerance << " but was " << actual;
        return failureStr.str();
    }

    template< typename Expected, typename Actual>
    std::string BuildFailureString(Expected const expected, Actual const actual, int const count)
    {
        std::stringstream failureStr;
        int i;

        failureStr << "Expected [ ";

        for (i = 0; i < count; ++i)
            failureStr << expected[i] << ' ';

        failureStr << "] but was [ ";

        for (i = 0; i < count; ++i)
            failureStr << actual[i] << ' ';

        failureStr << ']';

        return failureStr.str();
    }

    template< typename Expected, typename Actual, typename Tolerance >
    std::string BuildFailureString(Expected const expected, Actual const actual, 
                                    int const count, Tolerance const tolerance)
    {
        std::stringstream failureStr;
        int i;

        failureStr << "Expected [ ";

        for (i = 0; i < count; ++i)
            failureStr << expected[i] << ' ';

        failureStr << "] +/- " << tolerance << " but was [ ";

        for (i = 0; i < count; ++i)
            failureStr << actual[i] << ' ';

        failureStr << ']';

        return failureStr.str();
    }
    

}
    
        
#endif
