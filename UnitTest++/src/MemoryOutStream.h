#ifndef UNITTEST_MEMORYOUTSTREAM_H
#define UNITTEST_MEMORYOUTSTREAM_H

#include "Config.h"

#ifdef UNITTEST_USE_CUSTOM_STREAMS

	#include <cstddef>

	namespace UnitTest {

	class MemoryOutStream
	{
	public:
		explicit MemoryOutStream(int const size = 256);
		~MemoryOutStream();
	    
		char const* GetText() const;

		MemoryOutStream& operator << (char const* txt);
		MemoryOutStream& operator << (int n);
		MemoryOutStream& operator << (long n);
		MemoryOutStream& operator << (unsigned long n);
		MemoryOutStream& operator << (float f);
		MemoryOutStream& operator << (double d);
		MemoryOutStream& operator << (void const* p);
		MemoryOutStream& operator << (unsigned int s);

		enum { GROW_CHUNK_SIZE = 32 };
		int GetCapacity() const;
	    
	private:
		void operator= (MemoryOutStream const&);
		void GrowBuffer(int capacity);
	    
		int m_capacity;
		char* m_buffer;
	};
	}

#else

	#include <sstream>

	namespace UnitTest {

	class MemoryOutStream : public std::ostringstream
	{
	public:
		char const* GetText() const 
		{ 
			m_text = this->str();
			return m_text.c_str();
		}

	private:
		mutable std::string m_text;
	};

	}

#endif

#endif
