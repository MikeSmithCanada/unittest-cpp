#include "../UnitTest++.h"

using namespace UnitTest;


namespace {

TEST(CheckCloseTrue)
{
    CHECK (CheckClose(3.001f, 3.0f, 0.1f));
}

TEST(CheckCloseFalse)
{
    CHECK (false == CheckClose(3.12f, 3.0f, 0.1f));
}

TEST(CheckArrayEqualTrue)
{
    const int array[3] = { 1, 2, 3 };
    CHECK (CheckArrayEqual(array, array, 3));
}

TEST(CheckArrayEqualFalse)
{
    const int array1[3] = { 1, 2, 3 };
    const int array2[3] = { 1, 2, 2 };
    CHECK (false == CheckArrayEqual(array1, array2, 3));
}

TEST(CheckArrayCloseTrue)
{
    const float array1[3] = { 1.0f, 1.5f, 2.0f };
    const float array2[3] = { 1.01f, 1.51f, 2.01f };
    CHECK (CheckArrayClose(array1, array2, 3, 0.02f));
}

TEST(CheckArrayCloseFalse)
{
    const float array1[3] = { 1.0f, 1.5f, 2.0f };
    const float array2[3] = { 1.01f, 1.51f, 2.01f };
    CHECK (false == CheckArrayClose(array1, array2, 3, 0.001f));
}

}

