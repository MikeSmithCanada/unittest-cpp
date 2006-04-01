#ifndef UNITTEST_MEMORYOUTSTREAM_H
#define UNITTEST_MEMORYOUTSTREAM_H


namespace UnitTest {

class MemoryOutStream
{
public:
    MemoryOutStream(int size = 256);
    ~MemoryOutStream();
    
    char const* GetText() const;

    MemoryOutStream& operator << (char const* txt);
    MemoryOutStream& operator << (int n);
    MemoryOutStream& operator << (float f);
    MemoryOutStream& operator << (void* p);

private:
    void operator= (MemoryOutStream const&);
    
    int const m_bufferSize;
    char* const m_buffer;
};


}

#endif
