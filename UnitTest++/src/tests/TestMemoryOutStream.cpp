#include "../UnitTest++.h"
#include "../MemoryOutStream.h"

using namespace UnitTest;

namespace {

TEST (DefaultIsEmptyString)
{
    MemoryOutStream stream;
    CHECK (stream.GetText() != 0);
    CHECK_EQUAL ("", stream.GetText());
}

TEST (StreamingTextCopiesCharacters)
{
    MemoryOutStream stream;
    stream << "Lalala";
    CHECK_EQUAL ("Lalala", stream.GetText());
}

TEST (StreamingMultipleTimesConcatenatesResult)
{
    MemoryOutStream stream;
    stream << "Bork" << "Foo" << "Bar";
    CHECK_EQUAL ("BorkFooBar", stream.GetText());
}

TEST (StreamingIntWritesCorrectCharacters)
{
    MemoryOutStream stream;
    stream << 123;
    CHECK_EQUAL ("123", stream.GetText());
}

TEST (StreamingFloatWritesCorrectCharacters)
{
    MemoryOutStream stream;
    stream << 3.1415f;
    CHECK (std::strstr(stream.GetText(), "3.1415"));
}

TEST (WritingStringLongerThanAvailableMemoryTruncatesString)
{
    char txt[64] = {'z'};
    MemoryOutStream stream(txt, 8);
    stream << "0123456789ABCDEF";
    CHECK_EQUAL ("0123456", stream.GetText());
}

TEST (WritingIntLongerThanAvailableMemoryTruncatesString)
{
    char txt[64] = {'z'};
    MemoryOutStream stream(txt, 8);
    stream << "aaaa" << 123456;;
    CHECK_EQUAL ("aaaa123", stream.GetText());
}

TEST (WritingFloatLongerThanAvailableMemoryTruncatesString)
{
    char txt[64] = {'z'};
    MemoryOutStream stream(txt, 8);
    stream << "aaaa" << 123456.0f;;
    CHECK_EQUAL ("aaaa123", stream.GetText());
}

}
