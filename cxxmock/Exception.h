#ifndef __cxxmock__Exception_H
#define __cxxmock__Exception_H

namespace CxxMock
{
struct IException 
{
	virtual void throwException() = 0;
	virtual ~IException();
}

template <typename T>
class Exception : public IException
{
public:
	T Value;

	Exception( T arg ) :  Value(arg)
	{
	}

	void throwException()
	{
		throw Value;
	}
};

}

#endif // __cxxmock__Exception_H
