#include "MemoryOutStream.h"
#include <cstring>
#include <cstdio>


namespace UnitTest
{

MemoryOutStream::MemoryOutStream()
    : m_buffer(m_localBuffer)
    , m_bufferSize(sizeof(m_localBuffer))
{
    std::strcpy(m_buffer, "");
}

MemoryOutStream::MemoryOutStream(char* buffer, int size)
    : m_buffer(buffer)
    , m_bufferSize(size)
{
    std::strcpy(m_buffer, "");
}


char const* MemoryOutStream::GetText() const
{
    return m_buffer;
}

MemoryOutStream& MemoryOutStream::operator << (char const* txt)
{
    int const bytesLeft = m_bufferSize - std::strlen(m_buffer);
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

}
