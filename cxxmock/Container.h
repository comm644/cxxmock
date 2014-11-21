#ifndef __cxxmock__CONTAINER_H
#define __cxxmock__CONTAINER_H
#include <cxxmock/Factory.h>

namespace CxxMock {

template<class Interface, class Impl>
class Container : public Factory<Interface>
{
public:
		Container()
		{
				Repository::instance().registerFactory( this );
		}
		Interface* create()
		{
				return new Impl();
		}
};

}

#endif // __cxxmock__CONTAINER_H
