#ifndef NOTSUPPORTEDINTERFACE_H
#define	NOTSUPPORTEDINTERFACE_H

class NotSupportedInterface
{
public:
    virtual void canNotSetPointer2(int *arg) = 0;
    virtual void canNotSetPointer3(int&arg) = 0;

    virtual void canNotSetReference2(int &arg) = 0;
    virtual void canNotSetReference3(int&arg) = 0;

    virtual ~NotSupportedInterface(){}
};


#endif	/* NOTSUPPORTEDINTERFACE_H */

