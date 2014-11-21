#ifndef __cxxmock__EXCEPTIONS_H
#define __cxxmock__EXCEPTIONS_H
#include <string>

namespace CxxMock
{

using namespace std;

class AssertException : public std::exception
{
	std::string _msg;
public:
	AssertException (const std::string& msg): _msg(msg)
	{
	}
	virtual ~AssertException () throw()
	{
	}
	const char* what() const throw()
	{
		return _msg.c_str();
	}
};

struct InvalidArgumentException : public AssertException
{
	InvalidArgumentException (const std::string& msg): AssertException(msg)
	{
	}
};

struct AssertArgumentException : public AssertException
{
	AssertArgumentException (const std::string& msg): AssertException(msg)
	{
	}
};

struct AssertUnexpectedCallException : public AssertException
{
	AssertUnexpectedCallException (const std::string& msg): AssertException(msg)
	{
	}
};
struct AssertExpectationsFailed : public AssertException
{
	AssertExpectationsFailed (const std::string& msg): AssertException(msg)
	{
	}
};
struct AssertInvalidOperation : public AssertException
{
	AssertInvalidOperation (const std::string& msg): AssertException(msg)
	{
	}
};


}

#endif // __cxxmock__EXCEPTIONS_H
