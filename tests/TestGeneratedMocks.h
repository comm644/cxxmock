#ifndef TESTGENERATEDMOCKS_H
#define	TESTGENERATEDMOCKS_H
#include <cxxtest/TestSuite.h>
#include "mocks.gen.h"

class testGeneratedMocks : public CxxTest::TestSuite
{
public:

    void testSetterSupported()
    {
        CxxMock::Repository mocks;

        Interface* mock = mocks.create<Interface > ();

        Type arg;
        
        TS_EXPECT_CALL_VOID( mock->setValue(arg));
        
        mocks.replay();
        
        mock->setValue(arg);
    }

    void testGetterSupported()
    {
        CxxMock::Repository mocks;

        Interface* mock = mocks.create<Interface > ();

        Type arg;
        
        TS_EXPECT_CALL( mock->getValue()).returns(arg);

        mocks.replay();
        
        TS_ASSERT_EQUALS( arg, mock->getValue());
    }
    
    void testGetPointerSupported()
    {
        CxxMock::Repository mocks;

        Interface* mock = mocks.create<Interface > ();

        Type arg;
        
        TS_EXPECT_CALL( mock->canGetPointer()).returns(&arg);

        mocks.replay();
        
        TS_ASSERT_EQUALS( &arg, mock->canGetPointer());
    }
    void testSetPointerSupported()
    {
        CxxMock::Repository mocks;

        Interface* mock = mocks.create<Interface > ();

        Type arg;
        
        TS_EXPECT_CALL_VOID( mock->canSetPointer(&arg));

        mocks.replay();
        
        mock->canSetPointer(&arg);
    }
    
    void testVoidMethodSupported()
    {
        CxxMock::Repository mocks;

        Interface* mock = mocks.create<Interface > ();

        TS_EXPECT_CALL_VOID( mock->voidMethod());

        mocks.replay();
        
        mock->voidMethod();
    }
    void testNamespaceSupported()
    {
        CxxMock::Repository mocks;

        NS1::NS2::NS4::NS5::Interface2* mock = mocks.create<NS1::NS2::NS4::NS5::Interface2 > ();

        TS_EXPECT_CALL_VOID( mock->method());

        mocks.replay();
        
        mock->method();
    }
	void testSeveralArguments()
	{
		CxxMock::Repository mocks;
		ISeveralArguments* mock = mocks.create<ISeveralArguments > ();
		mock->method(1, 2, 3);
	}
};


#endif	/* TESTGENERATEDMOCKS_H */

