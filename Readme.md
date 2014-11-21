![status](https://travis-ci.org/comm644/cxxmock.svg?branch=master)

About 
==================================

The CxxMock framework provides easy-to-use Mock objects for C++ unit-testing. I've tried to implement Rhino.Mocks idea. It works!


Quick start
===================================

1. Generate mocks
--------------------------

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
:::bash
python cxxmockgen.py <header.h> <header.h>.... >generated_mocks.h
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


2. Use in unit-tests.
--------------------------------

~~~~~~~~~~~~~~~~~~~~~~
:::C++
#include "generated_mocks.h"
...
...
... in test case:


//Declare repository.
CxxMock::Repository mocks;

//Gets interface mock.
IMyCoolInterface* mock = mocks.create<IMyCoolInterface>();

//record expectations.
TS_EXPECT_CALL( mock->method(10) ).returns( 5 );

//or void:
TS_EXPECT_CALL_VOID( mock->voidMethod() );

//start replaying recorded calls.
mocks.replay();

//run subsystem wich used mock interfaces:
TS_ASSERT_EQUALS( 5, mock->method(10) );
mock->voidMethod();


//verify not called methods.
mocks.verify();
~~~~~~~~~~~~~~~~~~~~~~


[Examples]
