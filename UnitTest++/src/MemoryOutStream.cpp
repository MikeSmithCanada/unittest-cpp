#include "MemoryOutStream.h"
#include <cstring>
#include <cstdio>


namespace UnitTest {

MemoryOutStream::MemoryOutStream(int const size)
    : m_bufferSize (size)
    , m_buffer (new char[size])

{
    std::strcpy(m_buffer, "");
}

MemoryOutStream::~MemoryOutStream()
{
    delete [] m_buffer;
}

char const* MemoryOutStream::GetText() const
{
    return m_buffer;
}

MemoryOutStream& MemoryOutStream::operator << (char const* txt)
{
    size_t const bytesLeft = m_bufferSize - std::strlen(m_buffer);
    std::strncat(m_buffer, txt, bytesLeft-1);
    return *this;
}

MemoryOutStream& MemoryOutStream::operator << (int const n)
{
    char txt[32];
    std::sprintf(txt, "%i", n);
    *this << txt;
    return *this;
}

MemoryOutStream& MemoryOutStream::operator << (float const f)
{
    char txt[32];
    std::sprintf(txt, "%f", f);
    *this << txt;
    return *this;
}

MemoryOutStream& MemoryOutStream::operator << (void* p)
{
    char txt[32];
    std::sprintf(txt, "%p", p);
    *this << txt;
    return *this;
}


}
