#ifndef UNITTEST_MEMORYOUTSTREAM_H
#define UNITTEST_MEMORYOUTSTREAM_H


namespace UnitTest
{

class MemoryOutStream
{
public:
    MemoryOutStream();
    MemoryOutStream(char* buffer, int size);
    char const* GetText() const;

    MemoryOutStream& operator << (char const* txt);
    MemoryOutStream& operator << (int n);
    MemoryOutStream& operator << (float f);

private:
    char m_localBuffer[256];
    char* m_buffer;
    int m_bufferSize;
};


}

#endif
