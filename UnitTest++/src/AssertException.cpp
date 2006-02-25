#include "AssertException.h"

namespace UnitTest {

AssertException::AssertException(char const* description, char const* filename, int const lineNumber)
	: m_description(description)
	, m_filename(filename)
	, m_lineNumber(lineNumber)
{
}

AssertException::~AssertException() throw()
{
}

char const* AssertException::what() const throw()
{
	return m_description.c_str();
}

std::string const& AssertException::Filename() const
{
	return m_filename;
}

int AssertException::LineNumber() const
{
	return m_lineNumber;
}

}
