#ifndef __cxxmock__ARGUMENT_H
#define __cxxmock__ARGUMENT_H
#include <typeinfo>
#include <sstream>
#include <iostream>

//#include <cxxmock/CxxTestEquals.h> //3.10.1
#include <cxxmock/IArgument.h>

#ifdef  QT_VERSION 
#include <QString>
#endif

#include <cxxmock/IArgument.h>

namespace CxxMock
{

template <typename T>
class Argument : public IArgument
{
	std::string _typeName;

	std::string convertToString(int arg ) const          { std::stringstream ss; ss << arg; return ss.str(); }
	std::string convertToString(unsigned int arg ) const { std::stringstream ss; ss << arg; return ss.str(); }
	std::string convertToString(float arg ) const	     { std::stringstream ss; ss << arg; return ss.str(); }
	std::string convertToString(double arg ) const	     { std::stringstream ss; ss << arg; return ss.str(); }
	std::string convertToString(const char* arg ) const	 { return std::string( arg ); }
#ifdef  QT_VERSION 
	std::string convertToString(const QString& arg )const{ return arg.toStdString(); }
#endif

	//template<typename TVal>
	//std::string convertToString(TVal arg ) const         { std::stringstream ss; ss << std::hex << reinterpret_cast<void*>(&arg); return ss.str(); }

	template<typename TVal>
	std::string convertToString(TVal arg ) const         { return CxxTest::ValueTraits<T>( arg ).asString();  }

public:
	T Value;

	Argument( T arg ) :  Value(arg)
	{
		_typeName = (typeid(T).name());
	}

	const std::string  typeName() const
	{
		return _typeName;
	}

	const std::string toString() const
	{
		return convertToString( Value );
	}

	bool compare( const IArgument& other ) const
	{
		const Argument<T> *arg = dynamic_cast< const Argument<T>* >( &other );

		return CxxTest::equals( Value, arg->Value);
	}
};


}

#endif // __cxxmock__ARGUMENT_H
