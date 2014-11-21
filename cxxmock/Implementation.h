#ifndef __cxxmock__IMPLEMENTATION_H
#define __cxxmock__IMPLEMENTATION_H

namespace CxxMock {

template <class Interface>
class Implementaton : public Interface
{
protected:
	virtual ~Implementaton(){}
	mutable MockObject cxxmock_object;
};

}

#endif // __cxxmock__IMPLEMENTATION_H
