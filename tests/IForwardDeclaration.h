class A;
class B;


namespace A {
class A;
class B;
}

namespace A {
namespace B {
 class A;
 class B;
}}



class IForwardDeclaration1
{
public:
	virtual void method( const int arg1, int arg2, int arg3 ) = 0;
};

namespace A {
class IForwardDeclaration2
{
public:
	virtual void method( const int arg1, int arg2, int arg3 ) = 0;
};
}
