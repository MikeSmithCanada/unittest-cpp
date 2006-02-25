#include "../UnitTest++.h"
#include "../AssertException.h"
#include "../ReportAssert.h"

namespace UnitTest { namespace {

TEST(CallingAssertThrowsAssertException)
{
	bool caught = false;

	int const lineNumber = 12345;
	char const* description = "description";
	char const* filename = "filename";

	try
	{
		ReportAssert(description, filename, lineNumber);
	}
	catch(AssertException const& e)
	{
		CHECK_EQUAL(std::string(e.what()), description);
		CHECK_EQUAL(e.Filename(), filename);
		CHECK_EQUAL(e.LineNumber(), lineNumber);

		caught = true;
	}

	CHECK(caught == true);
}

}}
