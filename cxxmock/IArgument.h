#ifndef __cxxmock__IARGUMENT_H
#define __cxxmock__IARGUMENT_H

#include <string>

namespace CxxMock
{

class IArgument
{
public:
	virtual const std::string typeName() const = 0;
	virtual const std::string toString() const = 0;

	virtual bool compare( const IArgument& other ) const = 0;
	virtual void setValue( const IArgument& other ) = 0;
	virtual ~IArgument(){}
};

}

#endif // __cxxmock__IARGUMENT_H
