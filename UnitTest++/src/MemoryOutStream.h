#ifndef UNITTEST_MEMORYOUTSTREAM_H
#define UNITTEST_MEMORYOUTSTREAM_H

#include <cstddef>

namespace UnitTest {

class MemoryOutStream
{
public:
    MemoryOutStream(int const size = 256);
    ~MemoryOutStream();
    
    char const* GetText() const;

    MemoryOutStream& operator << (char const* txt);
    MemoryOutStream& operator << (int const n);
    MemoryOutStream& operator << (float const f);
    MemoryOutStream& operator << (void const* p);
    MemoryOutStream& operator << (size_t const s);

    enum { GROW_CHUNK_SIZE = 32 };
    int GetCapacity() const;
    
private:
    void operator= (MemoryOutStream const&);
    void GrowBuffer(int capacity);
    
    int m_capacity;
    char* m_buffer;
};

}

#endif
