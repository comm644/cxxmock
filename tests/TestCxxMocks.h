#ifndef TESTMOCKOBJECT_H
#define TESTMOCKOBJECT_H
#include <cxxtest/TestSuite.h>
#include <cxxmock/cxxmock.h>

namespace MyMocks {

    class MyInterface
    {
    public:
        virtual int method(int a) = 0;
        virtual void voidMethod()=0;

        virtual ~MyInterface()
        {
        }
    };

    class CXXMOCK_DECL(MyInterface)
    {
    public:

        int method(int a)
        {
            return CXXMOCK(int, a);
        }

        int otherMethod(int a, int b)
        {
            return CXXMOCK(int, a, b);
        }
        void voidMethod()
        {
            CXXMOCK_GET(int);
        }
    };

    CXXMOCK_IMPL(MyInterface)



} //end namespace

class TestMockObject : public CxxTest::TestSuite
{
public:

    void testUseCase()
    {
        CxxMock::Repository mocks;

        MyMocks::MyInterface* mock = mocks.create<MyMocks::MyInterface > ();

        TS_EXPECT_CALL( mock->method(10) ).returns(5);

        mocks.replay();
        TS_ASSERT_EQUALS(5, mock->method(10));

    }

    void testWhenResultValueAssignedToArgumentList()
    {
        CxxMock::Repository mocks;

        MyMocks::MyInterface* mock = mocks.create<MyMocks::MyInterface > ();

        TS_EXPECT_CALL( mock->method(10) ).returns(5);
        TS_EXPECT_CALL( mock->method(11) ).returns(6);

        mocks.replay();
        TS_ASSERT_EQUALS(5, mock->method(10));
        TS_ASSERT_EQUALS(6, mock->method(11));

        mocks.verify();
    }

    void testWhenExpectationsNotCaused()
    {
        CxxMock::Repository mocks;

        MyMocks::MyInterface* mock = mocks.create<MyMocks::MyInterface > ();

        TS_EXPECT_CALL( mock->method(10) ).returns(5);
        mocks.replay();

        bool isOk = false;
        try {
            mocks.verify();
        }
        catch (CxxMock::AssertExpectationsFailed& e) {
            isOk = true;
        }
        TSM_ASSERT_EQUALS("expected exception. expected method not called",
                true, isOk);

    }

    void testWhenArgumentListMismatch()
    {
        CxxMock::Repository mocks;

        MyMocks::MyInterface* mock = mocks.create<MyMocks::MyInterface > ();

        TS_EXPECT_CALL( mock->method(10) ).returns(5);
        mocks.replay();



        bool isOk = false;
        try {
            mock->method(20);
        }
        catch (CxxMock::AssertArgumentException& e) {
            isOk = true;
        }
        TSM_ASSERT_EQUALS("Argument exception expected.",
                true, isOk);

        isOk = false;
        try {
            mocks.verify();
        }
        catch (CxxMock::AssertExpectationsFailed& e) {
            isOk = true;
        }
        TSM_ASSERT_EQUALS("When exception failed then verification must be ignored.",
                false, isOk);
    }
    
    
    void testWhenVerifyWasNotCalled()
    {
        bool isOk = false;
        try
        {
            CxxMock::Repository mocks;

            MyMocks::MyInterface* mock = mocks.create<MyMocks::MyInterface > ();

            TS_EXPECT_CALL( mock->method(10)).returns(5);
            TS_EXPECT_CALL( mock->method(11)).returns(6);

            mocks.replay();
        }
        catch (CxxMock::AssertExpectationsFailed& e) {
            isOk = true;
        }

        TSM_ASSERT_EQUALS("verify() will not be called in destructor.",
                false, isOk);
    }
    
    void testWhenExpectedMethodReturnsVoid()
    {
        CxxMock::Repository mocks;

        MyMocks::MyInterface* mock = mocks.create<MyMocks::MyInterface > ();
        
        TS_EXPECT_CALL_VOID( mock->voidMethod() );

        mocks.replay();
        
        //call method anywhere.
        mock->voidMethod();
    }
};

#endif // TESTMOCKOBJECT_H
