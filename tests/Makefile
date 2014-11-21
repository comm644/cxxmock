
TESTSUITE = ./testsuite
HEADERS   = TestCxxMocks.h TestGeneratedMocks.h

FAIL_TESTSUITE = ./testsuite_fail
FAIL_TESTS =  TestExpectations.h


.PHONY:  all clean prebuild

all: prebuild $(TESTSUITE) $(FAIL_TESTSUITE)


prebuild: mocks.gen.h


$(TESTSUITE).cpp: $(HEADERS)
	python cxxtest/cxxtestgen.py --error-printer --have-eh  --have-std --abort-on-fail -o $@ $^
	
$(TESTSUITE): $(TESTSUITE).cpp
	g++ -Wall -Werror -g -o $@ $^ -Icxxtest -I ../
	$(TESTSUITE)

$(FAIL_TESTSUITE): $(FAIL_TESTSUITE).cpp
	g++ -Wall -Werror -g -o $@ $^ -Icxxtest -I ../
	-$(FAIL_TESTSUITE)

$(FAIL_TESTSUITE).cpp: $(FAIL_TESTS)
	python cxxtest/cxxtestgen.py --error-printer --have-eh  --have-std --abort-on-fail -o $@ $^


mocks.gen.h: supportedInterface.h ISeveralArguments.h IForwardDeclaration.h
	python  ../cxxmockgen.py -o $@ $^


clean:
	$(RM) $(TESTSUITE).cpp $(TESTSUITE) mocks.gen.h $(FAIL_TESTSUITE) $(FAIL_TESTSUITE).cpp

