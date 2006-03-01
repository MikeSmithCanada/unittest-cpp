COMPILER = g++
CCFLAGS = -g -ansi -Wall -DLINUX
.SUFFIXES: .o .cpp

lib = TestUnit++.a
test = TestTestUnit++

src = src/AssertException.cpp \
	src/HTMLTestReporter.cpp \
	src/PrintfTestReporter.cpp \
	src/ReportAssert.cpp \
	src/Test.cpp \
	src/TestLauncher.cpp \
	src/TestReporter.cpp \
	src/TestResults.cpp \
	src/TestRunner.cpp \
	src/Linux/SignalTranslator.cpp

test_src = src/tests/Main.cpp \
	src/tests/TestAssertHandler.cpp \
	src/tests/TestChecks.cpp \
	src/tests/TestUnitTestCpp.cpp \
	src/tests/TestTest.cpp \
	src/tests/TestTestResults.cpp \
	src/tests/TestTestRunner.cpp \
	src/tests/TestTypedTestLauncher.cpp \
	src/tests/TestCheckMacros.cpp


objects = $(patsubst %.cpp, %.o, $(src))
test_objects = $(patsubst %.cpp, %.o, $(test_src))

all: $(test)


$(lib): $(objects) 
	@echo Creating $(lib) library...
	@ar cr $(lib) $(objects)
    
$(test): $(lib) $(test_objects)
	@echo Linking $(test)...
	@$(COMPILER) -o $(test) $(test_objects) $(lib)
	@echo Running unit tests...
	@./$(test)

clean:
	@rm $(objects) $(test_objects) $(test) $(lib) 2> /dev/null

%.o : %.cpp
	@echo $<
	@$(COMPILER) $(CCFLAGS) -c $< -o $(patsubst %.cpp, %.o, $<)
