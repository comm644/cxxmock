#ifndef __cxxmock__CXXTESTEQUALS_H
#define __cxxmock__CXXTESTEQUALS_H
#include <string>


namespace CxxTest
{

inline bool equals( char* x, char* y)
{
	return std::string(x) == std::string(y);
}
inline bool equals( const char* x, const char* y)
{
	return std::string(x) == std::string(y);
}
inline bool equals( char* x, const char* y)
{
	return std::string(x) == std::string(y);
}
inline bool equals( const char* x, char* y)
{
	return std::string(x) == std::string(y);
}

}

#endif // __cxxmock__CXXTESTEQUALS_H
