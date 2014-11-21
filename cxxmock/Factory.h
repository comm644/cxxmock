#ifndef __cxxmock__FACTORY_H
#define __cxxmock__FACTORY_H
#include <cxxmock/Handle.h>

namespace CxxMock {


template <class Interface>
struct Factory : public Handle
{
		typedef Interface TargetType;
		virtual Interface* create() = 0;
};

}


#endif // __cxxmock__FACTORY_H
