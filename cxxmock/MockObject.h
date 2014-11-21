#ifndef __cxxmock__MOCKOBJECT_H
#define __cxxmock__MOCKOBJECT_H
#include <string>
#include <map>
#include <list>
#include <sstream>

#include <cxxmock/Exceptions.h>
#include <cxxmock/CallInfo.h>


namespace CxxMock
{
class CallInfo;
class Repository;

class MockObject
{
	friend class Repository;

private:
	ExpectedCallsCollection _expected;
	ExpectedCallsCollection _actual;

	void verify();

private:

	CallInfo& getExpected( const CallInfo& actual )
	{
		ExpectedCallsCollection::iterator it = _expected.find( actual.method());
		if ( it == _expected.end() ) {
			throw AssertUnexpectedCallException( string("Not expected call: ") + actual.method());
		}
		if ( !it->second.size() ) {
			//unexpected call
			throw AssertUnexpectedCallException( string("Not expected call: ") + actual.method());
		}

		CallInfoPtr item = it->second.front();
		item->compare( actual );

		if ( item->canRemove()  ) {
			it->second.pop_front();
			//delete item
		}

		return *item;
	}

	template <typename R>
	R processCall( CallInfo& info )
	{
		if ( Repository::instance().isRecording()  ) {
			_expected[ info.method() ].push_back( &info );
			R r= R();
			return r;
		}

		_actual[ info.method() ].push_back( &info );

		CallInfo& expected = getExpected(info);
		Argument<R> rc = expected.getResult<R>();
		return rc.Value;
	}


	CallInfo& method( std::string funcname )
	{
		CallInfoPtr ptr = new CallInfo(funcname);
		Repository::instance().setLastCall( ptr );
		return *ptr;
	}

public:

	MockObject()
	{
		Repository::instance().registerMock( this );
	}
	~MockObject()
	{
		Repository::instance().unregisterMock( this );
	}



	template <typename R>
	R mock( const std::string& funcname )
	{
		return this->processCall<R>(  method(funcname) );
	}

	template <typename R, typename  A1>
	R mock( const std::string& funcname, A1 a1)
	{
		return this->processCall<R>(  method(funcname).arg( a1 ) );
	}

	template <typename R, typename  A1, typename A2>
	R mock( const std::string& funcname, A1 a1, A2 a2)
	{
		return this->processCall<R>(  method(funcname).arg( a1 ).arg( a2 ) );
	}

	template <typename R, typename  A1, typename A2, typename A3 >
	R mock( const std::string& funcname, A1 a1, A2 a2, A3 a3)
	{
		return this->processCall<R>(  method(funcname).arg( a1 ).arg( a2 ).arg( a3 ) );
	}

	template <typename R, typename  A1, typename A2, typename A3, typename A4 >
	R mock( const std::string& funcname, A1 a1, A2 a2, A3 a3, A4 a4)
	{
		return this->processCall<R>(  method(funcname).arg( a1 ).arg( a2 ).arg( a3 ).arg( a4 ) );
	}
	template <typename R, typename  A1, typename A2, typename A3, typename A4, typename A5 >
	R mock( const std::string& funcname, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
	{
		return this->processCall<R>(  method(funcname).arg( a1 ).arg( a2 ).arg( a3 ).arg( a4 ).arg( a5 ) );
	}
	template <typename R, typename  A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
	R mock( const std::string& funcname, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
	{
		return this->processCall<R>(  method(funcname).arg( a1 ).arg( a2 ).arg( a3 ).arg( a4 ).arg( a5 ).arg( a6 ) );
	}
	template <typename R, typename  A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
	R mock( const std::string& funcname, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
	{
		return this->processCall<R>(  method(funcname).arg( a1 ).arg( a2 ).arg( a3 ).arg( a4 ).arg( a5 ).arg( a6 ).arg( a7 ) );
	}
	template <typename R, typename  A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >                                                    
        R mock( const std::string& funcname, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)                                                                                 
        {                                                                                                                                                                     
                return this->processCall<R>(  method(funcname).arg( a1 ).arg( a2 ).arg( a3 ).arg( a4 ).arg( a5 ).arg( a6 ).arg( a7 ).arg( a8 ) );                                       
        } 
	template <typename R, typename  A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9 >                                                    
        R mock( const std::string& funcname, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)                                                                                 
        {                                                                                                                                                                     
                return this->processCall<R>(  method(funcname).arg( a1 ).arg( a2 ).arg( a3 ).arg( a4 ).arg( a5 ).arg( a6 ).arg( a7 ).arg( a8 ).arg( a9 ) );                                       
        }
	template <typename R, typename  A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10 >                                                    
        R mock( const std::string& funcname, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)                                                                                 
        {                                                                                                                                                                     
                return this->processCall<R>(  method(funcname).arg( a1 ).arg( a2 ).arg( a3 ).arg( a4 ).arg( a5 ).arg( a6 ).arg( a7 ).arg( a8 ).arg( a9 ).arg( a10 ) );                                       
        } 
};


} //end of namespace

#endif // __cxxmock__MOCKOBJECT_H
