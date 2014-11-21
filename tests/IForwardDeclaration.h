class classA;
class classB;


namespace Ans {
class classA;
class classB;
}

namespace A {
namespace B {
 class classA;
 class classB;
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
