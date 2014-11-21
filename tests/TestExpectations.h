#ifndef TEST_EXPECTATIONS_H_
#define	TEST_EXPECTATIONS_H_
#include <cxxtest/TestSuite.h>
#include "mocks.gen.h"

class TestExpectations : public CxxTest::TestSuite
{
public:
        CxxMock::Repository* mocks;
	void setUp()
	{
		mocks = new CxxMock::Repository();
	}
	void tearDown()
	{
		//mocks->verify(); //caused exception
		delete mocks;
	}


    void testArgumentMismatch()
    {
        ISample* sample = mocks->create<ISample> ();

        TS_EXPECT_CALL_VOID( sample->setValue(10));

        mocks->replay();
        
        sample->setValue( 20 );

	mocks->verify();
    }

    void testArgumentMismatchGet()
    {
        ISample* sample = mocks->create<ISample> ();

        TS_EXPECT_CALL( sample->processValue(10)).returns( 1 );

        mocks->replay();
        
        sample->processValue( 20 );
    }
    void testUnexpectedCall()
    {
        ISample* sample = mocks->create<ISample> ();

        mocks->replay();
        
        sample->processValue( 20 );

        mocks->verify();

    }
    void testExpectationFailed()
    {
        ISample* sample = mocks->create<ISample> ();

        TS_EXPECT_CALL( sample->processValue(10)).returns( 1 );

        mocks->replay();

	mocks->verify();	
    }
 
};

class TestExpectationsStack : public CxxTest::TestSuite
{
public:
    void testArgumentMismatchStack()
    {
        CxxMock::Repository mocks;
        ISample* sample = mocks.create<ISample> ();

        TS_EXPECT_CALL_VOID( sample->setValue(10));

        mocks.replay();
        
        sample->setValue( 20 );

	mocks.verify();
    }
};

#endif
