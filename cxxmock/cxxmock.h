#ifndef __cxxmock__CXXMOCK_H
#define __cxxmock__CXXMOCK_H

#include <typeinfo>
#include <iostream>
#include <map>
#include <list>
#include <stdlib.h>

#include <memory>


#ifdef __GNUC__
#define MOCK_FUNCID  __PRETTY_FUNCTION__
#else
#define MOCK_FUNCID  __FUNCDNAME__
#endif

#define MOCK_FUNCNAME __FUNCTION__

#pragma GCC diagnostic ignored "-Wuninitialized"


#include <cxxmock/Repository.h>
#include <cxxmock/MockObject.h>
#include <cxxmock/Implementation.h>
#include <cxxmock/Container.h>
#include <cxxmock/CallInfo.h>
#include <map>

namespace CxxMock
{
void Repository::verify()
{
	if ( _isRecording ) {
		throw AssertInvalidOperation("Invalid operation. Mock repository in recording state.");
	}
	if ( _isVerified ) {
		return;
	}

	_isVerified = true;
	for( MocksInUseList::iterator it = _mocks.begin(); it != _mocks.end(); ++it) {
		(*it)->verify();
	}
}

void MockObject::verify()
{
	typedef std::pair<const std::string, CallInfoCollection > MapPair;
	for( ExpectedCallsCollection::iterator it = _expected.begin(); it != _expected.end(); ++it) {
		MapPair pair = *it;
		CallInfoCollection calls = pair.second;
		for( CallInfoCollection::iterator call = calls.begin(); call != calls.end(); ++call ){
			CallInfoPtr info = *call;
			if( info->repeat().getCount() < 0) {
				continue;
			}
			std::stringstream ss;
			ss << "Expected call " << info->method() << " but not called";
			throw AssertExpectationsFailed(ss.str());
		}
	}
}

void CallInfo::expectationFailed()
{
	Repository::instance().expectionFailed();
}

}


#define CXXMOCK_DECL( interface )  cxxmocks_impl_##interface : public CxxMock::Implementaton< interface >
#define CXXMOCK_IMPL( interface )  CxxMock::Container<interface, cxxmocks_impl_##interface> cxxmocks_instance_##interface;

#define CXXMOCK_VOID( method ) ({method; 0})

//mock method macro should be used in mock method
#ifndef _MSC_VER
#define CXXMOCK( RetType, args... )  cxxmock_object.mock<RetType>(MOCK_FUNCID, args);
#else
#define CXXMOCK( RetType, ... )  cxxmock_object.mock<RetType>(MOCK_FUNCID, __VA_ARGS__);
#endif

//mock set property or void-return method
#define CXXMOCK_GET( RetType )       cxxmock_object.mock<RetType>(MOCK_FUNCID)

//mock get property
#ifndef _MSC_VER
#define CXXMOCK_SET( args... )       cxxmock_object.mock<int>(MOCK_FUNCID, args);
#else
#define CXXMOCK_SET( ... )       cxxmock_object.mock<int>(MOCK_FUNCID, __VA_ARGS__);
#endif

#define TS_EXPECT_CALL_VOID( method )  method; CxxMock::Repository::instance().expectCall( 0 )
#define TS_EXPECT_CALL( method )  CxxMock::Repository::instance().expectCall(  method )

#endif
