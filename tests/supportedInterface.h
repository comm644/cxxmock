#ifndef __INTERFACE_H_
#define __INTERFACE_H_

class ForwardClass;

class Type
{
private:
    int _a;
    
public:
    Type(): _a(0){}
    
    bool operator ==(const Type& another) const
    {
        return _a == another._a;
    }
};


class ISample
{
public:
	~ISample(){}
	virtual void setValue(int a) = 0;
	virtual int processValue(int a) = 0;
};

class Interface
{
public:
	virtual void setValue( Type arg ) = 0;	
	virtual Type getValue() = 0;
	
    virtual Type& canGetReference() = 0;

    virtual Type* canGetPointer() = 0;
    
	virtual void canSetPointer( Type* arg ) = 0;
    virtual void canSetReference(Type& arg) = 0;

    virtual void canParseCompressed(Type arg1, Type arg2) = 0;

    virtual int canParseHakerCode(Type arg1, Type arg2) = 0;

    virtual Type canParseReference(const Type &arg) = 0;

    virtual void canSetConstParam(const Type* arg) = 0;

    virtual void voidMethod() = 0;
    
    virtual ~Interface()
    {
    }
};

namespace NS1 {
namespace NS2 
{

namespace NS4 { namespace NS5 {
    
class Interface2
{
public:
	 virtual void method()=0;
	 virtual ~Interface2(){};
};
class interface3 
{
     virtual int method() = 0;
};

}}

class interface4 {
     virtual int method() = 0;
    
};
}
}


#endif