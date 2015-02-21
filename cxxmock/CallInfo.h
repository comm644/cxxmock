#ifndef __cxxmock__CALLINFO_H
#define __cxxmock__CALLINFO_H
#include <string>
#include <map>
#include <list>


#include <cxxmock/Exceptions.h>
#include <cxxmock/IArgument.h>
#include <cxxmock/Argument.h>
#include <cxxmock/Action.h>



namespace CxxMock
{
typedef std::map<std::string, ArgList>  ExpectedCall;  // funcname( args )


class CallInfo;
class MockObject;

class Repeat
{
	friend class CallInfo;
	friend class MockObject;
private:
	int _count;
	CallInfo* parent;
	Repeat( CallInfo* info ) : _count( 1 ), parent( info ) {}

	void touch() {
		if( _count > 0 ) {
			_count--;
		}
	}
	int getCount()
	{
		return _count;
	}


public:
	CallInfo& any() { _count = -1; return *parent; }
	CallInfo& twice() { _count = 2; return *parent; }
	CallInfo& count( int count ) { _count = count; return *parent; }
};



class MockObject;
class CallInfo
{
	friend class MockObject;

private:

	std::string _method;
	bool        _ignoreArguments;
	Repeat      _repeat;
	IAction* _action;


	CallInfo(const CallInfo&):
		_ignoreArguments( false ),
		_repeat(this), 
		_action(NULL),
		defaultResult(0),
		Result(&defaultResult)
	{
	}

	bool canRemove()
	{
		_repeat.touch();
		return _repeat.getCount() == 0;
	}


	template< typename R>
	const Argument<R>& getResult() const
	{
		if ( !Result ) {
			throw new AssertArgumentException(string("Return value for ") + method() + " is not defined" );
		}

		Argument<R>* ptr = dynamic_cast<Argument<R>* >(Result);
		if ( !ptr ) {
			throw AssertArgumentException(
						string("Return value have incompatible type in \n") + method() + ".\n"
						+ "Expected: " + typeid(R).name() + "\n"
						+ "  Actual: " + Result->typeName() + "\n");
		}

		return *ptr;
	}

public:
	ArgList inValues;
	ArgList outValues;

	Argument<int> defaultResult;
	IArgumentPtr Result;

	CallInfo( std::string method ) :
		_method(method),
		_ignoreArguments( false ),
		_repeat(this), 
		_action(NULL),
		defaultResult(0),
		Result(&defaultResult)
	{
		static const std::string prefix ="cxxmocks_impl_";

		_method = method.erase( method.find(prefix), prefix.length());
	}

	~CallInfo()
	{
		if ( Result != &defaultResult) {
			delete Result;
		}
	}

	const std::string& method() const
	{
		return _method;
	}


	template<typename R>
	CallInfo& returns(R value )
	{
		if ( Result != &defaultResult) {
			delete Result;
		}
		Result = new Argument<R>(value);
		return *this;
	}

	template<typename A>
	CallInfo& outVal( int argNumber, A arg )
	{
		outValues[argNumber] = IArgumentPtr( new Argument<A>(arg) );
		return *this;
	}

	template<typename A>
	CallInfo& arg(const A value )
	{
		inValues[ inValues.size() ] = new Argument<A>(value);
		return *this;
	}


	void compare(const CallInfo& actual)
	{
		if ( _ignoreArguments ) {
			return;
		}
		if ( inValues.size() != actual.inValues.size() ) {
			expectationFailed();

			std::stringstream ss ;
			ss << "Argument list mismatch\nExpected: " << inValues.size() << " was " << actual.inValues.size();
			
			throw AssertArgumentException(ss.str());
		}

		size_t count = inValues.size();
		for( size_t i=0; i < count; ++i ) {
			ArgList::const_iterator inVal = inValues.find(i);
			ArgList::const_iterator actualVal = actual.inValues.find(i);
			if ( inVal->second->compare( *actualVal->second ) ) {
				continue;
			}

			expectationFailed();

			std::stringstream ss;

			ss << "\nIn " << _method << " not expected argument #" << i << "\n"
				  "Expected value: " << inVal->second->toString() << "\n"
				  "Actual value  : " << actualVal->second->toString() <<"\n";
			

			throw AssertArgumentException(ss.str());
		}

		if (_action != NULL ) {
			_action->call( Result, actual.inValues );
		}
	}


	CallInfo& ignoreArguments()
	{
		_ignoreArguments = true;
		return( *this );
	}

	Repeat& repeat() {
		return _repeat;
	}



	template< typename Sender, typename T>
	CallInfo& action( Sender* sender, T method )
	{
	    _action = new Action<Sender, T>(sender, method );

	    return *this;
        }
 
	void expectationFailed();

};
typedef CallInfo*  CallInfoPtr;
typedef std::list< CallInfoPtr >  CallInfoCollection;
typedef std::map<std::string, CallInfoCollection> ExpectedCallsCollection;

}

#endif // __cxxmock__CALLINFO_H
